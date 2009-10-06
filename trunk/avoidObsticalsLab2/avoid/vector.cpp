#include "vector.h"

using namespace std;
using namespace PlayerCc;

//private:  
//Private variables
//double xIntensityData;
//double yIntensityData;
// End Prizvate Variables

//public:  
//constructors
Vector::Vector(double xOrigin, double yOrigin, double xEnd, double yEnd)
{
	xIntensityData = xEnd - xOrigin;
	yIntensityData = yEnd - yOrigin;
}
Vector::Vector(double xIntensity, double yIntensity)
{
	xIntensityData = xIntensity;
	yIntensityData = yIntensity;
}
Vector::Vector(double distance, double angle, bool isDegrees)
{
	if(isDegrees){
		xIntensityData = cos(dtor(angle)) * distance;
		yIntensityData = sin(dtor(angle)) * distance;
	}else {
		xIntensityData = cos(angle) * distance;
		yIntensityData = sin(angle) * distance;
	}

}



double Vector::getAngle()
{
	double angle;
	angle = rtod(atan2(yIntensityData, xIntensityData));
	return angle;	
}
double Vector::getDistance()
{
	return sqrt(pow(xIntensityData, 2.0) + pow(yIntensityData, 2.0));
}
double Vector::getXIntensity(){
	return xIntensityData;
}
double Vector::getYIntensity(){
	return yIntensityData;
}
double Vector::getAngle(double localReferenceAngle){
	return getAngle() + localReferenceAngle;
}

void Vector::add(Vector & newVector){
	xIntensityData += newVector.getXIntensity();
	yIntensityData += newVector.getYIntensity();
}
void Vector::debugIntensity(){
 cout << "Xintensity:" << xIntensityData << ", Yintensity:" << yIntensityData;
}
void Vector::debug(){
	cout <<  "angle:" << getAngle() << " Distance:" << getDistance();
}
void Vector::resetVector(double xIntensity, double yIntensity){
	xIntensityData = xIntensity;
	yIntensityData = yIntensity;
}
void Vector::invertVector(){
	xIntensityData *= -1;
	yIntensityData *= -1;
}
void Vector::multiplyBy(double multiple){
	xIntensityData *= multiple;
	yIntensityData *= multiple;
}
