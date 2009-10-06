#ifndef SENSORCLASS
#define SENSORCLASS // <-- same string as above line



// C++ header files
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include "vector.h"
#include "mapApi.h"

// Player header file.  We need this for all player programs.
#include <libplayerc++/playerc++.h>


using namespace PlayerCc;

class SensorScan
{
private:  
	//Private variables
        //PlayerClient robot(PLAYER_HOSTNAME, 0);      
	LaserProxy* laser;//(NULL,0);
	Position2dProxy* position;//(NULL, 0);
	Vector* currentRelativeVector; // = new Vector(0,0);
	MapWorldApi* currentWorldView;
	// End Prizvate Variables
	void addToCurrentVector(Vector newVector);
	Vector convertToGlobalReference(Vector relativeVector); 
	void debugSensor();
	double vectorFunction(double inputValue);
	double inverseSquare(double inputValue);
	double inverseLargeRoot(double inputValue);
	double inverseCube(double inputValue);
	bool inFrontOfRobot(Vector &ObjectVector);
	int countOfRelativeVectors;
	double functionChoice;
	double targetPath;
public:  
    SensorScan(LaserProxy * newLaser, Position2dProxy * newPosition, MapWorldApi* newCurrentWorldView, double newFunctionChoice, double newTargetPath);
	
	void ReadSensors();
	Vector VectorSum();
	double RelavantTargets();
	
	
};

#endif
