// ***************************************************************************************
// *
// *    Core       | Everything within this document is proprietary to Core Dynamics.
// *    Dynamics   | Any unauthorized duplication will be subject to prosecution.
// *
// *    Department : (R+D)^2                        Name: hardware_module_door.cpp
// *       Sub Dept: Programming
// *    Location ID: 856-45B
// *                                                      (c) 2856 - 2858 Core Dynamics
// ***************************************************************************************

#ifndef HARDWARE_MODULE_DOOR_CPP
#define HARDWARE_MODULE_DOOR_CPP

#include "hardware_module_door.h"

// ***************************************************************************************
// STRUCTURES AND CLASSES
// ***************************************************************************************


// ***************************************************************************************
// FUNCTION AND PROCEDURES
// ***************************************************************************************

void v_DoorMonitorAndAnimationControlModule2(Console &cons, system_data &sdSysData, ANIMATION_HANDLER &Animations, unsigned long tmeCurrentTime)
// This routine is designed to scan all the doors or switches.  If anthing is open, opened 
//  closed or closed (odd twist of english there) then set the appropriate or maintain
//  animations.  
// Works like this.  If any door is open then make sure the overhead lights are on.  
//  If all the doors are closed, turn all the lights off.  Run door animations like 
//  normal.
{
  using namespace std;

  int opencount = 0;
  bool changedetected = false;

  // Scan Through Doors and Check for Changes

  // DO NOT CLEAR ANIMATIONS HERE!  CLEAR ANIMATIONS IN ANIMATION SCRIPT!
  //              (easier to track and debug that way)

  // Switch value of true = open

  // Check for newly opened and run animation on them.

  // Door mini map.
  int door_mini[sdSysData.CONFIG.vhwDOORS.size()];
  int changes = 0;
  int prev_open_door_count = 0;
  int recent_opened_door_count = 0;
  int recent_closed_door_count = 0;

  for (int door=0; door < sdSysData.CONFIG.vhwDOORS.size(); door++)
  {

    if(sdSysData.CONFIG.vhwDOORS.at(door).booVALUE == true)
    {
      door_mini[door] = 1;
      prev_open_door_count++;
    }
    else
    {
      door_mini[door] = 0;
    }

    if(sdSysData.CONFIG.vhwDOORS.at(door).changed(sdSysData.CONFIG.vSWITCH_PIN_MAP.at(door).value, tmeCurrentTime) == true)
    {
      if(sdSysData.CONFIG.vhwDOORS.at(door).booVALUE == true)
      {
        door_mini[door] = 2;
        recent_opened_door_count++;
      }
      else
      {
        door_mini[door] = -1;
        recent_closed_door_count++;
      }
    }

  }

  // Count number of changes. if non then do nothing.
  for (int pos = 0; pos < sdSysData.CONFIG.vhwDOORS.size(); pos++)
  {
    if (door_mini[pos] == -1 || door_mini[pos] == 2)
    {
      changes++;
    }
  }

  if (changes > 0)
  {
    // Update system open doors count var so other routines can check door status.
    sdSysData.intDoorsOpen = prev_open_door_count + recent_opened_door_count - recent_closed_door_count;

    //cons.printwait("prev_open_door_count:" + to_string(prev_open_door_count) +
    //               " recent_opened_door_count:" + to_string(recent_opened_door_count) +
    //               " recent_closed_door_count:" + to_string(recent_closed_door_count));

    // Condition - All Doors Closed and one is opened.                   
    if (prev_open_door_count == 0)
    {
      //"A Door Opened - Overhead"
      cons.printwait("A Door Opened - Overhead");
      Animations.call_animation(sdSysData, tmeCurrentTime, "Car", "A Door Opened - Overhead");

      // Step through door status and turn on extteriors of newly opened door and running anim on
      //  the doors that are still closed
      for(int pos = 0; pos < sdSysData.CONFIG.vhwDOORS.size(); pos++)
      {
        if (door_mini[pos] == -1)
        {
          cons.printwait("Door:" + to_string(pos +1) + " This Door Closed - Exterior");
        }

        if (door_mini[pos] == 2)
        {
          cons.printwait("Door:" + to_string(pos +1) + " This Door Opened - Exterior");
          Animations.call_animation(sdSysData, tmeCurrentTime, "Car", "This Door Opened - Exterior", pos);
          Animations.call_animation(sdSysData, tmeCurrentTime, "Car", "This Door Opened - Overhead", pos);
        }

        if (door_mini[pos] == 0)
        {
          cons.printwait("Door:" + to_string(pos +1) + " A Door is Opened - Exterior");
          Animations.call_animation(sdSysData, tmeCurrentTime, "Car", "A Door is Opened - Exterior", pos);
        }
      }
    }
    // Condition - One or more Doors are open and now they are all closed.
    else if (prev_open_door_count + recent_opened_door_count - recent_closed_door_count == 0)
    {
      //"All Doors Closed - Overhead"
      cons.printwait("All Doors Closed - Overhead");
      Animations.call_animation(sdSysData, tmeCurrentTime, "Car", "All Doors Closed - Overhead");
      cons.printwait("All Doors Closed - Exterior");
      Animations.call_animation(sdSysData, tmeCurrentTime, "Car", "All Doors Closed - Exterior");
      Animations.call_animation(sdSysData, tmeCurrentTime, "Car", "This Door Closed - Overhead");

      // Run recently closed door anims
      for(int pos = 0; pos < sdSysData.CONFIG.vhwDOORS.size(); pos++)
      {
        if ((tmeCurrentTime - sdSysData.CONFIG.vhwDOORS.at(pos).tmeTOGGLEDTIME) < 15000)
        {
          Animations.call_animation(sdSysData, tmeCurrentTime, "Car", "This Door Recently Closed - Overhead", pos);
        }
      }
    }    
    // Condition - More than 2 doors are open and one is closed.
    //    or
    // Condition - More than 1 doors is open and another is opened.
    else if (prev_open_door_count >0 && recent_closed_door_count > 0 ||
              prev_open_door_count >0 && recent_opened_door_count > 0)
    {
      for(int pos = 0; pos < sdSysData.CONFIG.vhwDOORS.size(); pos++)
      {
        if (door_mini[pos] == -1)
        {
          cons.printwait("Door:" + to_string(pos +1) + " This Door Closed - Exterior");
          Animations.call_animation(sdSysData, tmeCurrentTime, "Car", "This Door Closed and Another Open - Exterior", pos);
          Animations.call_animation(sdSysData, tmeCurrentTime, "Car", "This Door Closed - Overhead", pos);
        }

        if (door_mini[pos] == 2)
        {
          cons.printwait("Door:" + to_string(pos +1) + " This Door Opened - Exterior");
          Animations.call_animation(sdSysData, tmeCurrentTime, "Car", "This Door Opened and Another Open - Exterior", pos);
          Animations.call_animation(sdSysData, tmeCurrentTime, "Car", "This Door Opened - Overhead", pos);
        }
      }
    }
  }
}

#endif