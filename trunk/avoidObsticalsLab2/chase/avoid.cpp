// wander.cpp
//
// Bill Smart, August 2009
//
// A simple Player C++ client program that uses the laser rangefinder
// to do a simple random walk.

// C++ header files
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include "sensorScan.h"
#include "robotMove.h"

// Player header file.  We need this for all player programs.
#include <libplayerc++/playerc++.h>
double x = 0;
double y = 0;
// Open up namespaces
using namespace std;
using namespace PlayerCc;
	


const static double closenessCutOff = 1;
const static double maxSpeed = .25;
const static double angleDampener = 6;
const static double sensorFunction = 3;
const static double robotFunction = 1;
const static double targetPath = 100;
 
void SquareTargetFunction(Vector & startingFunction){
	startingFunction.multiplyBy(startingFunction.getDistance() * .1);
}

void FullSpeedFunction(Vector & startingFunction){
	startingFunction.multiplyBy(10000);
}
void CubeTargetFunction(Vector & startingFunction){
	startingFunction.multiplyBy(startingFunction.getDistance() * startingFunction.getDistance());
}
void TargetFunction (Vector & startingTargetFunction){
	if(robotFunction == 1){
		SquareTargetFunction(startingTargetFunction);
	}else if(robotFunction == 2){
		CubeTargetFunction(startingTargetFunction);
	}else if(robotFunction == 3){
		FullSpeedFunction(startingTargetFunction);
	}
	
}


int main(int argc, char **argv) 
{
	if (argc > 2) {
		//cout << "Atleast once arg" << argv[1] << endl;
		x = atoi(argv[1]);
		y = atoi(argv[2]);
	}	  
	try 
	{
		
		PlayerClient robot(PLAYER_HOSTNAME, 3213);
		Position2dProxy position(&robot, 0);
		LaserProxy laser(&robot, 0);


		PlayerClient robotToAvoid(PLAYER_HOSTNAME, 3214);
		Position2dProxy positionToAvoid(&robotToAvoid, 0);
		LaserProxy laserToAvoid(&robotToAvoid, 0);

		while (laser.GetCount() == 0)
		  robot.Read();

		position.SetMotorEnable(true);
		
		

		while (laserToAvoid.GetCount() == 0)
		  robotToAvoid.Read();

		positionToAvoid.SetMotorEnable(true);
		
		

	//======================================================================
	// This is the logic of the control program
	//======================================================================
		Vector worldCoordinateVector(x + position.GetXPos(), y + position.GetYPos());
		Vector localCoordinateVector(worldCoordinateVector.getDistance(), dtor(worldCoordinateVector.getAngle()) + position.GetYaw(), false);
		x = localCoordinateVector.getXIntensity();//x + position.GetXPos();
		y = localCoordinateVector.getYIntensity();//y + position.GetYPos();

		SensorScan sensors(&laser, &position, sensorFunction, targetPath);
		RobotMove robotDriver(&position, &robot, maxSpeed, angleDampener);
		while (true) {				//cout << "Setup";
			robot.Read();			
			sensors.ReadSensors();
			Vector sensorVector = sensors.VectorSum();
			sensorVector.invertVector();
			//sensorVector.debugIntensity();

			Vector avoidVector(sensorVector.getDistance(), dtor(sensorVector.getAngle()) + position.GetYaw() , false);

			Vector avoidSeeker(position.GetXPos(), position.GetYPos(), positionToAvoid.GetXPos(), positionToAvoid.GetYPos());

			Vector driveVector(position.GetXPos(), position.GetYPos(), x, y);

			
			//if(driveVector.getDistance() > closenessCutOff){
				TargetFunction(driveVector);
				
				//avoidSeeker.invertVector();
				//cout << endl << "AvoidVector       : ";
				//avoidVector.debug();avoidVector.debugIntensity();
				//cout << endl << "Drive Vector      : ";
				//driveVector.debug();driveVector.debugIntensity();

				driveVector.add(avoidVector);
				//driveVector.add(avoidSeeker);

				//cout << endl << "Resulting Vector  : " << endl;
				//driveVector.debug();driveVector.debugIntensity();
				robotDriver.DriveToVector(driveVector, &position);
			//}else{
				//position.SetSpeed(0,0);
			//}	
		}
		  
	//======================================================================
	// End of control program logic
	//======================================================================
	} catch (PlayerError e) {
	  cerr << e << endl;
	  return 1;
	}
  // We'll never get here, but it's good form to put it in anyway.
	return 0;

}






