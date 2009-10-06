#ifndef VECTORCLASS
#define VECTORCLASS // <-- same string as above line


#include <cstdlib>
#include <cstdio>
#include <math.h>
#include <libplayerc++/playerc++.h>

class Vector
{
	private:  
		//Private variables
	double xIntensityData;
	double yIntensityData;
		// End Prizvate Variables
		
	public:  
    Vector(double xOrigin, double yOrigin, double xEnd, double yEnd);
	Vector(double xIntensity, double yIntensity);
	Vector(double distance, double angle, bool isDegrees);
	
	double getAngle();
	double getDistance();
	double getXIntensity();
	double getYIntensity();
	double getAngle(double localReferenceAngle);	
	void debugIntensity();
	void debug();
	void add(Vector &newVector);
	void resetVector(double xIntensity, double yIntnesity);
	void invertVector();
	void multiplyBy(double multiple);
};

#endif

