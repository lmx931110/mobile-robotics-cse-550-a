#include "pose.h"
	//public:  
	Pose::Pose(){
		x = 0;
		y = 0;
		angleInDegrees = 0;
	}
    	Pose::Pose(double newX, double newY, double newAngleInDegrees){
		x = newX;
		y = newY;
		angleInDegrees = newAngleInDegrees;
	}
	
	double Pose::getX(){
		return x;
	}
	double Pose::getY(){
		return y;
	}
	double Pose::getAngle(){
		return angleInDegrees;
	}
