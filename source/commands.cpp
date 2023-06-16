// ***************************************************************************************
// *
// *    Core       | Everything within this document is proprietary to Core Dynamics.
// *    Dynamics   | Any unauthorized duplication will be subject to prosecution.
// *
// *    Department : (R+D)^2                        Name: commands.cpp
// *       Sub Dept: Programming
// *    Location ID: 856-45B
// *                                                      (c) 2856 - 2858 Core Dynamics
// ***************************************************************************************

#ifndef COMMANDS_CPP
#define COMMANDS_CPP

#include "commands.h"

using namespace std;

// ***************************************************************************************
// STRUCTURES AND CLASSES
// ***************************************************************************************

// Source: https://raspberry-projects.com/pi/programming-in-c/console/using-console-commands-in-code

void COMMANDS::shutdown_now()
// Shut down the entire system.
{
  system(SHUTDOWN_NOW.c_str());
}

void COMMANDS::reboot()
// Shut down the entire system.
{
  system(REBOOT.c_str());
}

bool COMMAND_THREAD::running()
{
  if(THREAD_RUNNING == true)
  // Check to see if output thread was started before checking the completion status.
  {
    if(THREAD.wait_for(0ms) == future_status::ready)
    // Check to verify thte thread is complete before allowing the console to be updated again. 
    {
      THREAD_RUNNING = false;
    }
  }
  
  return THREAD_RUNNING;
}

void COMMAND_THREAD::run_command(string Command)
{
  COMMAND = Command;

  if (running() == false)
  {
    THREAD = async(system, COMMAND.c_str());
    THREAD_RUNNING = true;
  }
}




#endif