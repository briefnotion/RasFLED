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
#include <string>
#include <deque>

using namespace std;

// -------------------------------------------------------------------------------------
//  Alert Class

class ALERT_TYPE_GENERIC
{
  private:

  public:

  string TEXT = "";
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

  bool check_exist();

  void trigger();
  // Sets the trigger status to alert active state.

  bool CHANGED = false;
  
  public:
  
  deque<ALERT_TYPE_GENERIC> GENERIC_ALERTS;

  ALERT_SYSTEM_PROPERTIES PROP;

  void create();
  // Preps the alert system on first run or setup.
  // Preps the switchs.

  bool changed();
  // Change value will be reset to false after being read.

  bool switch_value(int Switch);
  // Returns value of switch value in alert system.

  void update_switch(int Switch, bool Value);
  // Update value of switches to alert system
  // Triggers alerts if switch value changed.

  bool triggered();
  // Returns True if a new alert is triggered.

  bool alert_cleared();
  // Returns True if all alerts are cleared.

  void add_generic_alert(string Text);
};



#endif