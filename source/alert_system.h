// ***************************************************************************************
// *
// *    Core       | Everything within this document is proprietary to Core Dynamics.
// *    Dynamics   | Any unauthorized duplication will be subject to prosecution.
// *
// *    Department : (R+D)^2                        Name: alert_system.h
// *       Sub Dept: Programming
// *    Location ID: 856-45B
// *                                                      (c) 2856 - 2858 Core Dynamics
// ***************************************************************************************

#ifndef ALERT_SYSTEM_H
#define ALERT_SYSTEM_H

// Standard Header Files
#include <stdio.h>
//#include <ncurses.h>
#include <string.h>
#include <deque>

using namespace std;

// -------------------------------------------------------------------------------------
//  Alert Class

class ALERT_TYPE_GENERIC
{
  private:

  public:
};

class ALERT_SYSTEM_PROPERTIES
{
  public:
  
  int SWITCH_COUNT = 0;
};

class ALERT_SYSTEM
{
  private:
  bool ALERT = false;
  bool ALERTED = false;
  bool TRIGGERED = false;

  deque<bool> SWITCHES;

  //bool CHANGED = false;

  public:

  ALERT_SYSTEM_PROPERTIES PROP;

  void create();

  bool switch_value(int Switch);

  void update_switch(int Switch, bool Value);

  void check_clear();

  bool triggered();
};



#endif