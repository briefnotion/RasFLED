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

bool ALERT_SYSTEM::check_exist()
{
  bool alert_exist = false;

  for (int swi = 0; swi < PROP.SWITCH_COUNT; swi++)
  {
    if (SWITCHES[swi] == true)
    {
      alert_exist = true;
    }
  }

  return alert_exist;
}

void ALERT_SYSTEM::trigger()
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

void ALERT_SYSTEM::create()
{
  bool tmp_switch = false;

  for (int swi = 0; swi < PROP.SWITCH_COUNT; swi++)
  {
    SWITCHES.push_back(tmp_switch);
  }

  CHANGED = true;
}

bool ALERT_SYSTEM::changed()
{
  if (CHANGED == true)
  {
    CHANGED = false;
    return true;
  }
  else
  {
    return false;
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
      trigger();
    }

    CHANGED = true;
  }
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

bool ALERT_SYSTEM::alert_cleared()
{
  if (ALERT == true)
  {
    if (check_exist() == true)
    {
      return false;
    }
    else
    {
      ALERT = false;
      ALERTED = false;
      return true;
    }
  }
  else
  {
    return false;
  }
}

void ALERT_SYSTEM::add_generic_alert(string Text)
{
  ALERT_TYPE_GENERIC tmp_alert;

  tmp_alert.TEXT = Text;

  GENERIC_ALERTS.push_back(tmp_alert);
  
  trigger();
}



#endif