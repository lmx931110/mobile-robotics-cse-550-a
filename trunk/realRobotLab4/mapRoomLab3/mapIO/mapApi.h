#ifndef MapWorldApiCLASS
#define MapWorldApiCLASS // <-- same string as above line



// C++ header files
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include "vector.h"
#include "pose.h"
#include <fstream>
#include <string>
#include <vector>


// Player header file.  We need this for all player programs.
#include <libplayerc++/playerc++.h>


using namespace PlayerCc;


class MapWorldApi
{
private:  
	//Private variables  
	int* gridTotals;
	int* gridSummationTemp;
	int rowCount;
	int columnCount;
	int resolutionPerMeter;
	void totalSummations();
	void addSensorReadingToMap(double x, double y);    
	LaserProxy* laser;
	
	//void StringSplit(string str, string delim, vector<string> &results);
	
public:  
	MapWorldApi(LaserProxy* newLaser, int newRowCount, int newColumnCount, int resolution);
	
	void writeTestMapFile();
	void writeTestImgFile();
	
	void ReadSensor(Pose & currentPose);
	
	
	Vector NextUnknownMapLocations (int resolution);
	
	void ReadMapIO();
	void WriteMapIO();
	void DrawPicture();

};
 
#endif
