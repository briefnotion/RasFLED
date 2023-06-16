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
#include <string>
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

  string REBOOT = "sudo reboot";
                    //  "sleep 5 && sudo shutdown now &"

  public:

  void shutdown_now();

  void reboot();
};


class COMMAND_THREAD
{
  private:

  future<int> THREAD;
  bool THREAD_RUNNING = false;

  string COMMAND;

  public:

  bool running();

  void run_command(string Command);
};



#endif