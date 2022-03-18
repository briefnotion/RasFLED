// ***************************************************************************************
// *
// *    Core       | Everything within this document is proprietary to Core Dynamics.
// *    Dynamics   | Any unauthorized duplication will be subject to prosecution.
// *
// *    Department : (R+D)^2                        Name: commands.h
// *       Sub Dept: Programming
// *    Location ID: 856-45B
// *                                                      (c) 2856 - 2858 Core Dynamics
// ***************************************************************************************

#ifndef COMMANDS_H
#define COMMANDS_H

// Standard Header Files
#include <stdio.h>
#include <string.h>


using namespace std;

// ***************************************************************************************
// STRUCTURES AND CLASSES
// ***************************************************************************************

// Source: https://raspberry-projects.com/pi/programming-in-c/console/using-console-commands-in-code

class COMMANDS
// Commands that can be executed as if from a shell prompt.
{
  private:
  string TEST = "cp /home/pi/scripts/test /home/pi/scripts/test_success";
  string SHUTDOWN_NOW = "sudo shutdown now";

  public:

  /*
  void test()
  // Test command line functionality for debugging
  {
    system(TEST.c_str());
  }
  */

  void shutdown_now()
  // Shut down the entire system.
  {
    system(SHUTDOWN_NOW.c_str());
  }
};




#endif