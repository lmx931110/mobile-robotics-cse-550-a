// driveForward.cpp
//
// Sean Reynolds, September 2009
//
// A simple Player C++ client program that uses the laser rangefinder
// to do a simple drive forward.

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


// Robot control code parameters
const double g_obstacle_threshold = .5;
const double g_speed = 1;


int main(int argc, char **argv) {
	// Seed the random number generator.  This is a common trick that
	// uses the system time as the seed.  As long as we don't do this
	// more than once a second (the resolution of the time() call), we
	// will get a unique sequence of random numbers.
	srand48(time(NULL));
	
	// Put all of the Player code inside a try block, since Player will
	// throw an exception if something goes wrong.
	try {
		// Connect to the player server using the default settings.  This
		// means that, if you're using Stage to simulate a robot, it has
		// to be running on the same machine.  Also, you should make sure
		// that no other pieces of Player code are running on this machine
		// on the same port, since this will lead to strange behaviour.
		PlayerClient robot(PLAYER_HOSTNAME, 3213);
		
		// Create a position proxy, which gives us access to the robots
		// wheels, so that we can move it around.
		Position2dProxy position(&robot, 0);
		
		// Create a laser proxy, which will give us access to the readings
		// from the robot's laseer range-finder.
		LaserProxy laser(&robot, 0);
		
		// Spin for a while, until we get some data from the laser device.
		// This is necessary, since it sometimes takes a little while for
		// the data from the laser to work it's way back to the Read()
		// call.  If we don't do this, then we might end up with bogus
		// data at the start, which might cause the robot to do the wrong
		// thing.
		while (laser.GetCount() == 0)
			robot.Read();
		
		// Get ready to move the robot.
		position.SetMotorEnable(true);
		
		//======================================================================
		// This is the logic of the control program
		//======================================================================
		
		
		bool obstacle = false;
		double new_speed = g_speed;
		double closest_object = 10;
		
		// We're going to loop forever in this code.  If you want to stop
		// the robot, a ctrl-c should do the trick.
		while (true) {
			// Read the sensors.  If we don't do this, we don't get any new
			// data.
			robot.Read();
			
			// Is there an obstacle in front of us?
			obstacle = false;
			//the robot to drive forwards at one meter per second, until it detects something directly in front of it
			if(laser[180] < 8){
				//Use the laser range sensor to detect objects, and stop the robot when there is an obstacle within 50cm of it. 
				closest_object = 10;
				for(unsigned int i = 0; i < laser.GetCount(); ++i) {
					if (closest_object > laser[i]){
						closest_object = laser[i];
					}
					if (laser[i] <= g_obstacle_threshold){
						obstacle = true;
					}else {
					
					//cout << i<< ":"<< laser[i] << ", ";
					}
				}
				
				cout<< closest_object<< endl;
				//detection speed
				new_speed = (closest_object - g_obstacle_threshold) * (closest_object - g_obstacle_threshold);
				
				if(new_speed < .01){
					new_speed = .01;
				}else if (new_speed > 1) {
					new_speed = 1;
				}
				
			}else{
				new_speed = 1;
			}
			//cout<<endl;
			
			// If there's an obstacle then stop.
			if (obstacle) {
				new_speed = 0;
			} 			
			// Finally, write out the commands to the robot.  We need to do
			// this in order to get the robot to actually move.
			position.SetSpeed(new_speed, 0);
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
