// wander.cpp
//
// Bill Smart, August 2009
//
// A simple Player C++ client program that uses the laser rangefinder
// to do a simple random walk.

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
const double g_obstacle_threshold = 0.350;
const double g_speed = 0.2;
const double g_avoid_speed = 0;
const double g_turn_rate = 40.0 / 180.0 * M_PI;
const int g_avoid_time = 15;
const int g_random_turn_time = 20;


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

    // Some parameters to control the behaviour
    int avoid_count = 0;
    int random_turn_count = 0;
    
    bool obstacle = false;
    double new_turn_rate = 0.0;
    double new_speed = 0.0;

    // We're going to loop forever in this code.  If you want to stop
    // the robot, a ctrl-c should do the trick.
    while (true) {
      // Read the sensors.  If we don't do this, we don't get any new
      // data.
      robot.Read();

       // Is there an obstacle in front of us?
      obstacle = false;
      for(unsigned int i = 0; i < laser.GetCount(); ++i) {
	if (laser[i] < g_obstacle_threshold)
	  obstacle = true;
      }    
      
      // If there's an obstacle then avoid things for 15 cycles of the
      // program.  This avoids things for a fixed amount of time,
      // rather than responding to the environment.  In general, this
      // is Considered Harmful, and should be avoided.  However, for
      // the purposes of this code, we'll let it slip through.
      if (obstacle) {
	new_speed = g_avoid_speed;
	
	if (avoid_count > 0) {
	  avoid_count = g_avoid_time;
	  
	  // Turn randomly
	  if (drand48() < 0.5)
	    new_turn_rate = -g_turn_rate;
	  else
	    new_turn_rate = g_turn_rate;
	  
	  --avoid_count;
	}
      } else {
	avoid_count = 0;
	new_speed = g_speed;
	
	// Make a random turn every so often.  The turn rate should be
	// between -20 and 20 degrees per second.  Again, we're turning
	// for a fixed period of time, and not paying attention to the
	// sensor readings.
	if (random_turn_count == 0) {
	  random_turn_count = g_random_turn_time;
	  
	  new_turn_rate = (drand48() * 40 - 20.0) / 180.0 * M_PI;
	}
	
	--random_turn_count;
      }
      
      // Finally, write out the commands to the robot.  We need to do
      // this in order to get the robot to actually move.
      position.SetSpeed(new_speed, new_turn_rate);
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
