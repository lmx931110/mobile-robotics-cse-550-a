#include "robotMove.h"

		
	// Robot control code parameters


	void RobotMove::debugCode(){
		cout<< "debug";
		cout<<(*position).GetXPos()<<", "<<(*position).GetYPos()<<", "<< (*position).GetYaw()<< endl;
		cout << "AngularDistance: " << rtod(angularDistence);
		cout << " Starting Angle: "<< startingAngle << " Robot Angle: " << rtod((*position).GetYaw()) << endl;
		cout << " Distance: " << distanceToGo << endl;
	}

double RobotMove::fixAngle(double angle){
	while(angle > dtor(180)){
		angle -= dtor(360);
	}
	while(angle < dtor(-180)){
		angle += dtor(360);
	}
	return angle;
}

void RobotMove::DriveToVector(Vector &whereToGo, Position2dProxy * position){ 

	startingAngle = whereToGo.getAngle();
	
	startingAngle = fixAngle(dtor(startingAngle));
	
	distanceToGo = whereToGo.getDistance();
	speed = whereToGo.getDistance();
	angularDistence = fixAngle(startingAngle - (*position).GetYaw());
	speed = abs(speed - abs(angularDistence / dtor(90)));
	if(speed > maxSpeed) speed = maxSpeed;
	(*position).SetSpeed(speed, angularDistence / angleDampener); 
		
	
	}
	
RobotMove::RobotMove(Position2dProxy * newPosition, PlayerClient * newRobot, LaserProxy* newLaser, MapWorldApi* newWorldView, double newMaxSpeed, double newAngleDampener, double newClosenessCutOff, double newSensorFunction, double newRobotFunction){
	position = newPosition;
	robot = newRobot;
	maxSpeed = newMaxSpeed;
	angleDampener = newAngleDampener;
	closenessCutOff = newClosenessCutOff;
	laser = newLaser;
	sensorFunction = newSensorFunction;
	worldView = newWorldView;
	robotFunction = newRobotFunction;
}	

void RobotMove::GoToPose(Pose newPose){
	xDestination = newPose.getX();
	yDestination = newPose.getY();
	//Vector worldCoordinateVector(xDestination + (*position).GetXPos(), yDestination + (*position).GetYPos());
	//Vector localCoordinateVector(worldCoordinateVector.getDistance(), dtor(worldCoordinateVector.getAngle()) + (*position).GetYaw(), false);
	//xDestination = localCoordinateVector.getXIntensity();//x + (*position).GetXPos();
	//yDestination = localCoordinateVector.getYIntensity();//y + (*position).GetYPos();

	SensorScan sensors(&(*laser), &(*position), &(*worldView), sensorFunction, 1000.0);
	double distance = closenessCutOff;
	while (distance >= closenessCutOff) {				//cout << "Setup";
		(*robot).Read();			
		sensors.ReadSensors();
		Vector sensorVector = sensors.VectorSum();
		sensorVector.invertVector();
		//sensorVector.debugIntensity();
		Vector avoidVector(sensorVector.getDistance(), dtor(sensorVector.getAngle()) + (*position).GetYaw() , false);
		
		Vector driveVector((*position).GetXPos(), (*position).GetYPos(), xDestination, yDestination);
		distance = driveVector.getDistance();
		TargetFunction(driveVector);
		
		//TargetFunction(driveVector);
		//cout << endl << "AvoidVector       : ";
		//avoidVector.debug();avoidVector.debugIntensity();
		//cout << endl << "Drive Vector      : ";
		//cout << closenessCutOff << endl;
		//driveVector.debug();
		//driveVector.debugIntensity();
		//cout << endl;
		driveVector.add(avoidVector);
		//cout << endl << "Resulting Vector  : " << endl;
		//driveVector.debug();driveVector.debugIntensity();
		DriveToVector(driveVector, &(*position));
	}
	Vector directionVector(.1, newPose.getAngle(), true);
	//while (abs((*position).GetYaw() - dtor(newPose.getAngle())) > closenessCutOff) {
	//	DriveToVector(directionVector, &(*position));
	//}
	(*position).SetSpeed(0,0);
	

}

MapWorldApi * RobotMove::GetCurrentMap(){
	return worldView;
}


void RobotMove::SquareTargetFunction(Vector & startingFunction){
	startingFunction.multiplyBy(startingFunction.getDistance() * .1);
}

void RobotMove::FullSpeedFunction(Vector & startingFunction){
	startingFunction.multiplyBy(10000);
}
void RobotMove::CubeTargetFunction(Vector & startingFunction){
	startingFunction.multiplyBy(startingFunction.getDistance() * startingFunction.getDistance());
}
void RobotMove::TargetFunction (Vector & startingTargetFunction){
	if(robotFunction == 1){
		SquareTargetFunction(startingTargetFunction);
	}else if(robotFunction == 2){
		CubeTargetFunction(startingTargetFunction);
	}else if(robotFunction == 3){
		FullSpeedFunction(startingTargetFunction);
	}
	
}
