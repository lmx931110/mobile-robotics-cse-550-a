// C++ header files
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <ctime>

// Player header file.  We need this for all player programs.
#include <libplayerc++/playerc++.h>

// Open up namespaces
using namespace std;
using namespace PlayerCc;

#include "sensorScan.h"

//private:  
//Private variables
//LaserProxy &laser;
//Position2dProxy &position;
//Vector currentRelativeVector;
// End Prizvate Variables
void SensorScan::addToCurrentVector(Vector newVector)
{
	
}
Vector SensorScan::convertToGlobalReference(Vector relativeVector){
	 
	return relativeVector;
} 
void SensorScan::debugSensor(){
	
	
	// Is there an obstacle in front of us?
	//obstacle = false;
	//cout<< (*laser).GetCount() << endl;
	//for(unsigned int index = 0; index < (*laser).GetCount(); index++) {
	(*currentRelativeVector).debug();
	(*currentRelativeVector).debugIntensity();
	cout << endl;
		//cout << " Bearing: "<< rtod((*laser).GetBearing(index)) << ": " << (*laser)[index] << endl;
		

}
bool SensorScan::inFrontOfRobot(Vector &ObjectVector){
	
	bool returnInPath = false;
	if(targetPath > ObjectVector.getYIntensity() && ObjectVector.getYIntensity() > (-1 * targetPath)){
		returnInPath = true;
	}
	return returnInPath;
}


//public:  
SensorScan::SensorScan(LaserProxy * newLaser, Position2dProxy * newPosition, double newFunctionChoice, double newTargetPath)
{
	laser = newLaser;
	position = newPosition;

	Vector newVector(0,0);
	currentRelativeVector = &newVector;
	functionChoice = newFunctionChoice;
	targetPath = newTargetPath;
}

void SensorScan::ReadSensors(){
	//(*currentRelativeVector).resetVector(0,0);
	countOfRelativeVectors = 0;
	Vector vectorTemp(0,0);
 	for(unsigned int index = 0; index < (*laser).GetCount(); index++) {
		Vector newVector(vectorFunction((*laser)[index]), (*laser).GetBearing(index), true);
		if(inFrontOfRobot(vectorTemp)){
		        vectorTemp.add(newVector);	
			countOfRelativeVectors++;
		}

	}
	(*currentRelativeVector).resetVector(vectorTemp.getXIntensity(), vectorTemp.getYIntensity());
	//debugSensor();
}

Vector SensorScan::VectorSum(){
	
	return *currentRelativeVector;
}

double SensorScan::vectorFunction(double inputValue){
	if(functionChoice == 1){
		return inverseSquare(inputValue);
	}else if(functionChoice == 2){
		return inverseCube(inputValue);//
	}else if(functionChoice == 3){
		return inverseLargeRoot(inputValue);
	}
	return inverseSquare(inputValue);
}
	
double SensorScan::inverseSquare(double inputValue){
	return (8/(pow(inputValue, 2)));
}


double SensorScan::inverseCube(double inputValue){
	return (8/(pow(inputValue, 3)));
}

double SensorScan::inverseLargeRoot(double inputValue){
	return (10/(pow(inputValue, inputValue)));
}
double SensorScan::RelavantTargets(){
	return countOfRelativeVectors;
}



