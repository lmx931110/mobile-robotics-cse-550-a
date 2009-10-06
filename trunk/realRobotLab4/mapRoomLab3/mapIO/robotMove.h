

// C++ header files
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include "vector.h"
#include "sensorScan.h"
#include "mapApi.h"
#include "pose.h"

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
	double closenessCutOff;
	double sensorFunction;
	double robotFunction;
	
	Position2dProxy* position;
	PlayerClient* robot;
	LaserProxy* laser;
	MapWorldApi* worldView;
	
	void debugCode();
	double fixAngle(double angle);
	
	void SquareTargetFunction(Vector & startingFunction);

	void FullSpeedFunction(Vector & startingFunction);
	void CubeTargetFunction(Vector & startingFunction);
	void TargetFunction (Vector & startingTargetFunction);

public:  
	RobotMove(Position2dProxy * newPosition, PlayerClient * newRobot, LaserProxy * laser, MapWorldApi * newWorldView, double newMaxSpeed, double newAngleDampener, double newClosenessCutOff, double newSensorFunction, double newRobotFunction);
	void DriveToVector(Vector &whereToGo, Position2dProxy * position);
	void GoToPose(Pose newPose);
	MapWorldApi * GetCurrentMap();
};

