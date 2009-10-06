#ifndef POSECLASS
#define POSECLASS // <-- same string as above line


#include <cstdlib>
#include <cstdio>
#include <math.h>
#include <libplayerc++/playerc++.h>

class Pose
{
	private:  
		//Private variables
	double x;
	double y;
	double angleInDegrees;
		// End Prizvate Variables
		
	public:  
	Pose();
    	Pose(double newX, double newY, double newAngleInDegrees);
	double getX();
	double getY();
	double getAngle();
};

#endif

