// ***************************************************************************************
// *
// *    Core       | Everything within this document is proprietary to Core Dynamics.
// *    Dynamics   | Any unauthorized duplication will be subject to prosecution.
// *
// *    Department : (R+D)^2                        Name: alert_system.cpp
// *       Sub Dept: Programming
// *    Location ID: 856-45B
// *                                                      (c) 2856 - 2858 Core Dynamics
// ***************************************************************************************

#ifndef ALERT_SYSTEM_CPP
#define ALERT_SYSTEM_CPP

#include "alert_system.h"

using namespace std;

// -------------------------------------------------------------------------------------
//  Alert Class

void ALERT_SYSTEM::create()
{
  bool tmp_switch = false;

  for (int swi = 0; swi < PROP.SWITCH_COUNT; swi++)
  {
    SWITCHES.push_back(tmp_switch);
  }
}

bool ALERT_SYSTEM::switch_value(int Switch)
{
  return SWITCHES[Switch];
}

void ALERT_SYSTEM::update_switch(int Switch, bool Value)
{
  if (SWITCHES[Switch] != Value)
  {
    SWITCHES[Switch] = Value;

    if (Value == true)
    {
      ALERT = true;

      if (ALERTED == false)
      {
        if (TRIGGERED == false)
        {
          TRIGGERED = true;
        }
      }
    }

    //CHANGED = true;
  }
}

void ALERT_SYSTEM::check_clear()
{
  bool alert_exist = false;

  for (int swi = 0; swi < PROP.SWITCH_COUNT; swi++)
  {
    if (SWITCHES[swi] == true)
    {
      alert_exist = true;
    }
  }

  if (alert_exist != ALERT)
  {
    if (alert_exist == true)
    {
      ALERT = true;
    }
    else
    {
      ALERT = false;
      ALERTED = false;
      TRIGGERED = false;
    }
  }
  //else
  //{
  //  CHANGED = false;
  //}
}

bool ALERT_SYSTEM::triggered()
{
  if (TRIGGERED == false)
  {
    return false;
  }
  else
  {
    TRIGGERED = false;
    return true;
  }
}



#endif