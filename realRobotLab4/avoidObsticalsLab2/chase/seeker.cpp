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
	


const static double closenessCutOff = 3;
const static double maxSpeed = .25;
const static double angleDampener = 6;
const static double sensorFunction = 3;
double robotFunction;
const static double targetPath = 50000;
 
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
		
		PlayerClient robot(PLAYER_HOSTNAME, 3214);
		Position2dProxy position(&robot, 0);
		LaserProxy laser(&robot, 0);
 

		PlayerClient robotToCatch(PLAYER_HOSTNAME, 3213);
		Position2dProxy positionToCatch(&robotToCatch, 0);
		LaserProxy laserToCatch(&robotToCatch, 0);


		while (laser.GetCount() == 0)
		  robot.Read();

		position.SetMotorEnable(true);
		
		while (laserToCatch.GetCount() == 0)
		  robotToCatch.Read();

		positionToCatch.SetMotorEnable(true);
		
		

		

	//======================================================================
	// This is the logic of the control program
	//======================================================================
		
		SensorScan sensors(&laser, &position, sensorFunction, targetPath);
		RobotMove robotDriver(&position, &robot, maxSpeed, angleDampener);
		while (true) {				//cout << "Setup";
			robot.Read();
			robotToCatch.Read();			
			sensors.ReadSensors();
			Vector sensorVector = sensors.VectorSum();
			sensorVector.invertVector();
			//sensorVector.debugIntensity();

			Vector avoidVector(sensorVector.getDistance(), dtor(sensorVector.getAngle()) + position.GetYaw() , false);
			
			Vector driveVector(position.GetXPos(), position.GetYPos(), positionToCatch.GetXPos(), positionToCatch.GetYPos());


			
			if(driveVector.getDistance() > closenessCutOff){

				robotFunction = 1;
				TargetFunction(driveVector);
				//cout << endl << "AvoidVector       : ";
				//avoidVector.debug();avoidVector.debugIntensity();
				//cout << endl << "Drive Vector      : ";
				//driveVector.debug();driveVector.debugIntensity();

				driveVector.add(avoidVector);

				//cout << endl << "Resulting Vector  : " << endl;
				//driveVector.debug();driveVector.debugIntensity();
				robotDriver.DriveToVector(driveVector, &position);
			//}else{
				//robotFunction = 3;
				//TargetFunction(driveVector);
				//cout << endl << "AvoidVector       : ";
				//avoidVector.debug();avoidVector.debugIntensity();
				//cout << endl << "Drive Vector      : ";
				//driveVector.debug();driveVector.debugIntensity();

				//driveVector.add(avoidVector);

				//cout << endl << "Resulting Vector  : " << endl;
				//driveVector.debug();driveVector.debugIntensity();
				//robotDriver.DriveToVector(driveVector, &position);
			}	
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






