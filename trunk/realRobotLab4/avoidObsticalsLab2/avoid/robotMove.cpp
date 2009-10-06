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
	
RobotMove::RobotMove(Position2dProxy * newPosition, PlayerClient * newRobot, double newMaxSpeed, double newAngleDampener){
	position = newPosition;
	robot = newRobot;
	maxSpeed = newMaxSpeed;
	angleDampener = newAngleDampener;
}	
