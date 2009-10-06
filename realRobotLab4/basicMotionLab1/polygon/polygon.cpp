// polygon.cpp
//
// Sean Reynolds, September 2009
//
// A simple robot controller which will drive in a geometric shape.
// the simple polygon will have the number of sides entered as a program argument.
//
// C++ header files
#include <iostream>
#include <cstdlib>
#include <cstdio>


// Player header file.  We need this for all player programs.
#include <libplayerc++/playerc++.h>

// Open up namespaces
using namespace std;
using namespace PlayerCc;


// Robot control code parameters
const double g_speed = 1;
char numberOfSides = 2;
double angleOfSides = 180;


void debugCode(Position2dProxy &position){
	cout<< "debug";
	cout<<position.GetXPos()<<", "<<position.GetYPos()<<", "<<rtod(position.GetYaw())<< endl;
}
double getDistance(double xOrigin, double yOrigin, Position2dProxy & position){
	return sqrt(pow((position.GetXPos() - xOrigin), 2.0) + pow((position.GetYPos() - yOrigin), 2.0));
}

double fixAngle(double angle){
	if(angle >= 180){
		return angle-360;
	}else if(angle<=-180){
		return angle+360;
	}
	return angle;
}

int main(int argc, char **argv) {

	//Write another robot controller that takes a single command line argument, which is a number greater than 2.
	if (argc > 1) {
		//cout << "Atleast once arg" << argv[1] << endl;
		numberOfSides = atoi(argv[1]);
		if (numberOfSides < 2) {
			numberOfSides = 2;
		}
		//cout << numberOfSides << endl;
	}
	angleOfSides = 360 / numberOfSides;
	
	//cout << numberOfSides << " " << angleOfSides << endl;
	// Put all of the Player code inside a try block, since Player will
	// throw an exception if something goes wrong.
	try {
		// Connect to the player server using the default settings. 
		PlayerClient robot(PLAYER_HOSTNAME, 3213);
		
		// Create a position proxy, which gives us access to the robots
		// wheels, so that we can move it around.
		Position2dProxy position(&robot, 0);
		
		// Get ready to move the robot.
		position.SetMotorEnable(true);
		
		//======================================================================
		// This is the logic of the control program
		//======================================================================
		double xOrigin = 0;
		double yOrigin = 0;
		double distance = 0;
		double startingAngle = 0;
		// We're going to loop forever in this code.  If you want to stop
		// the robot, a ctrl-c should do the trick.
		while (true) {
			// 2 itterations of 1 m/s gives 2m
			xOrigin = position.GetXPos();
			yOrigin = position.GetYPos();
			distance = 0;
			while(distance < 2){
				robot.Read();
				position.SetSpeed(.5, 0);
				debugCode(position);
				distance = getDistance(xOrigin, yOrigin, position);
				cout<< distance << endl;
			}


			//robot.Read();
			//position.SetSpeed(.0001, dtor(angleOfSides*2));

			startingAngle = position.GetYaw();

			if(fixAngle(startingAngle + angleOfSides) < startingAngle){
				while(position.GetYaw() > fixAngle(startingAngle - angleOfSides)) {
					robot.Read();
					position.SetSpeed(1, dtor(1));
					debugCode(position);
				}
			}
			while(position.GetYaw() < fixAngle(startingAngle - angleOfSides)) {
				robot.Read();
				position.SetSpeed(1, dtor(1));
				debugCode(position);
			}

		}
		
	} catch (PlayerError e) {
		cerr << e << endl;
		return 1;
	}
	
	//======================================================================
	// End of control program logic
	//======================================================================
	
	// We'll never get here, but it's good form to put it in anyway.
	return 0;
}
