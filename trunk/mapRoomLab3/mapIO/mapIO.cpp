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
#include "mapApi.h"
#include "pose.h"

// Player header file.  We need this for all player programs.
#include <libplayerc++/playerc++.h>
double x = 0;
double y = 0;
// Open up namespaces
using namespace std;
using namespace PlayerCc;
	


const static double closenessCutOff = 1.25;
const static double maxSpeed = .25;
const static double angleDampener = 7.5;
const static double sensorFunction = 3;
const static double robotFunction = 1;
const static double targetPath = 50000;




int main(int argc, char **argv) 
{
	int size = 0;
	Pose * allPoses;
	if (argc > 3) {
		//cout << "Atleast once arg" << argv[1] << endl;
		size = atoi(argv[1]);
		allPoses = new Pose[size];
		for(int index = 0; index < size && argc > (index * 2) + 3; index ++ ){
			x = atoi(argv[(index * 2) + 2]);
			y = atoi(argv[(index * 2) + 3]);
			Pose eachPose(x, y, 0);
			allPoses[index] = eachPose;
		}
	}else if(argc > 2) {
		size = 1;
		x = atoi(argv[1]);
		y = atoi(argv[2]);
		
		allPoses = new Pose[1];	
		allPoses = new Pose(x, y, 0);
	}
	try 
	{
		
		PlayerClient robot(PLAYER_HOSTNAME, 3213);
		Position2dProxy position(&robot, 0);
		LaserProxy laser(&robot, 0);


		while (laser.GetCount() == 0)
		  robot.Read();

		position.SetMotorEnable(true);
		
			

	//======================================================================
	// This is the logic of the control program
	//======================================================================
	//while(true){
	MapWorldApi worldView(&laser, 160, 160, 1);
	for(int index = 0; index < size; index ++){
		RobotMove robotDriver(&position, &robot, &laser, &worldView, maxSpeed, angleDampener, closenessCutOff, sensorFunction, robotFunction);

		robotDriver.GoToPose(allPoses[index]);
		//(*robotDriver.GetCurrentMap()).DrawPicture();
		//worldView.writeTestMapFile();
		//worldView.ReadMapIO();
		//worldView.WriteMapIO();
	}
	//}
		
		
		
		
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






