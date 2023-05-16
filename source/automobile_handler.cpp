// ***************************************************************************************
// *
// *    Core       | Everything within this document is proprietary to Core Dynamics.
// *    Dynamics   | Any unauthorized duplication will be subject to prosecution.
// *
// *    Department : (R+D)^2                        Name: automobile_handler.cpp
// *       Sub Dept: Programming
// *    Location ID: 856-45B
// *                                                      (c) 2856 - 2858 Core Dynamics
// ***************************************************************************************

#ifndef AUTOMOBILE_HANDLER_CPP
#define AUTOMOBILE_HANDLER_CPP

#include "automobile_handler.h"

using namespace std;

// -------------------------------------------------------------------------------------

void AUTOMOBILE_HANDLER::update_events(system_data &sdSysData, ANIMATION_HANDLER &Animations, unsigned long tmeCurrentTime)
{

  // Check for changes in the automobile availability
  if ((set_bool_with_change_notify(sdSysData.CAR_INFO.active(), AUTO_ACTIVE) == true))
  {
    if (sdSysData.CAR_INFO.active() == false)
    {
      // if automobile is no longer available, make sure all related lights are off.
      Animations.call_animation(sdSysData, tmeCurrentTime, "Car", "Automobile - Gear Select_Park_Off");
      Animations.call_animation(sdSysData, tmeCurrentTime, "Car", "Automobile - Gear Select_Revrese_Off");
    }
  }

  if (sdSysData.CAR_INFO.active() == true)
  {

    // Gear Selection

    // Park
    if (set_bool_with_change_notify(sdSysData.CAR_INFO.STATUS.GEAR.gear_selection_park(), GEAR_PARK) == true)
    {
      if (GEAR_PARK == true)
      {
        // Call animation to turn on park color.
        Animations.call_animation(sdSysData, tmeCurrentTime, "Car", "Automobile - Gear Select_Park_On");
      }
      else
      {
        // Call animation to turn off park color.
        Animations.call_animation(sdSysData, tmeCurrentTime, "Car", "Automobile - Gear Select_Park_Off");        
      }
    }

    // Revrese
    if (set_bool_with_change_notify(sdSysData.CAR_INFO.STATUS.GEAR.gear_selection_reverse(), GEAR_REVERSE) == true)
    {
      if (GEAR_REVERSE == true)
      {
        // Call animation to turn on park color.
        Animations.call_animation(sdSysData, tmeCurrentTime, "Car", "Automobile - Gear Select_Reverse_On");
      }
      else
      {
        // Call animation to turn off park color.
        Animations.call_animation(sdSysData, tmeCurrentTime, "Car", "Automobile - Gear Select_Reverse_Off");        
      }
    }

  }
}

// -------------------------------------------------------------------------------------

#endif
