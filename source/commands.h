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
#include <future>


using namespace std;

// ***************************************************************************************
// STRUCTURES AND CLASSES
// ***************************************************************************************

// Source: https://raspberry-projects.com/pi/programming-in-c/console/using-console-commands-in-code

class COMMANDS
// Commands that can be executed as if from a shell prompt.
{
  private:
  string SHUTDOWN_NOW = "sudo shutdown now";
                    //  "sleep 5 && sudo shutdown now &"

  public:

  void shutdown_now()
  // Shut down the entire system.
  {
    system(SHUTDOWN_NOW.c_str());
  }
};


class COMMAND_THREAD
{
  private:

  future<int> THREAD;
  bool THREAD_RUNNING = false;

  string COMMAND;

  public:

  bool running()
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

  void run_command(string Command)
  {
    COMMAND = Command;

    if (running() == false)
    {
      THREAD = async(system, COMMAND.c_str());
      THREAD_RUNNING = true;
    }
  }

  /*
  void stop_command()
  {
    THREAD.erase();
  }
  */
};




#endif