

// C++ header files
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include "vector.h"

// Player header file.  We need this for all player programs.
#include <libplayerc++/playerc++.h>


using namespace PlayerCc;
using namespace std;

class RobotMove
{
private:  
	double xDestination; 
	double yDestination;

	double startingAngle;
	double distanceToGo;
	double angularDistence;
	double angleDampener;
	double speed;
	double maxSpeed;
	
	Position2dProxy* position;//(NULL, 0);
	PlayerClient* robot;
	
	void debugCode();
	double fixAngle(double angle);
public:  
    	RobotMove(Position2dProxy * newPosition, PlayerClient * newRobot, double newMaxSpeed, double newAngleDampener);
	void DriveToVector(Vector &whereToGo, Position2dProxy * position);
};

