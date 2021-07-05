// ***************************************************************************************
// *
// *    Core       | Everything within this document is proprietary to Core Dynamics.
// *    Dynamics   | Any unauthorized duplication will be subject to prosecution.
// *
// *    Department : (R+D)^2                        Name: hardware_module_door.h
// *       Sub Dept: Programming
// *    Location ID: 856-45B
// *                                                      (c) 2856 - 2858 Core Dynamics
// ***************************************************************************************

#ifndef HARDWARE_MODULE_DOOR_H
#define HARDWARE_MODULE_DOOR_H

// Standard Header Files
#include <string>
#include <deque>

// RASFled related header files
#include "consoleanddata.h"

// ***************************************************************************************
// STRUCTURES AND CLASSES
// ***************************************************************************************


// ***************************************************************************************
// FUNCTION AND PROCEDURES
// ***************************************************************************************

void v_DoorMonitorAndAnimationControlModule(Console &cons, system_data &sdSysData, timed_event teEvents[], unsigned long tmeCurrentTime)
// This routine is designed to scan all the doors or switches.  If anthing is open, opened 
//  closed or closed (odd twist of english there) then set the appropriate or maintain
//  animations.  
// Works like this.  If any door is open then make sure the overhead lights are on.  
//  If all the doors are closed, turn all the lights off.  Run door animations like 
//  normal.
{
  // Routine could use a rewrite to adjust to generic configurable and multiple 
  //  switches per group.
  
  using namespace std;

  int opencount = 0;
  bool changedetected = false;

  // Scan Through Doors and Check for Changes

  // DO NOT CLEAR ANIMATIONS HERE!  CLEAR ANIMATIONS IN ANIMATION SCRIPT!
  //              (easier to track and debug that way)

  // Switch value of true = open

  // Check for newly opened and run animation on them.
  for (int door=0; door < sdSysData.CONFIG.vhwDOORS.size(); door++)
  {
    if (sdSysData.CONFIG.vhwDOORS.at(door).changed(sdSysData.CONFIG.vSWITCH_PIN_MAP.at(door).value, tmeCurrentTime) == true)
    {
      changedetected = true; 
      if (sdSysData.CONFIG.vhwDOORS.at(door).booVALUE)
      {
        // Door Just Opened
        // Start Open Door Animation on This Door
        if (sdSysData.CONFIG.vhwDOORS.at(door).ISHARDWARE == true)  // Only if its real switch (with lights attached to it)
        {
          // Door Animation
          cons.printwait("  Door " + to_string(door) + " Open ... ");
          sdSysData.CONFIG.LED_MAIN.at(0).vLED_GROUPS.at(door).status_set("Door", "Opened Door");

          for(int s=0; s < sdSysData.CONFIG.LED_MAIN.at(0).s_size(door); s++)
          {
            if (sdSysData.CONFIG.LED_MAIN.at(0).vLED_GROUPS.at(door).vLED_STRIPS.at(s).strNAME == "Door")
            {
              cons.printwait("  G" + to_string(door) + " S" + to_string(s) + " :Door Open");
              vdDoorOpenAnimationADV00(cons, sdSysData.CONFIG.LED_MAIN.at(0).vLED_GROUPS.at(door).vLED_STRIPS.at(s), teEvents, tmeCurrentTime);
            }
          }

          // Turn on additional lights overhead
          for(int s=0; s < sdSysData.CONFIG.LED_MAIN.at(0).s_size(door); s++)
          {
            if (sdSysData.CONFIG.LED_MAIN.at(0).vLED_GROUPS.at(door).vLED_STRIPS.at(s).strNAME == "Overhead")
            {
              cons.printwait("  G" + to_string(door) + " S" + to_string(s) + " :Additional Open");
              vdAdditionalOpenADV02(cons, sdSysData.CONFIG.LED_MAIN.at(0).vLED_GROUPS.at(door).vLED_STRIPS.at(s), teEvents, tmeCurrentTime);
            }
          }
        }
      }
      else
      {
        // Door Just Closed
        if (sdSysData.CONFIG.vhwDOORS.at(door).ISHARDWARE == true)  // Only if its real switch (with lights attached to it)
        {
          // Replace Open or Current door animation to closed door animation
          cons.printwait("  Door " + to_string(door) + " Close ... ");
          sdSysData.CONFIG.LED_MAIN.at(0).vLED_GROUPS.at(door).status_set("Door", "Closed Door");

          for(int s=0; s < sdSysData.CONFIG.LED_MAIN.at(0).s_size(door); s++)
          {
            if (sdSysData.CONFIG.LED_MAIN.at(0).vLED_GROUPS.at(door).vLED_STRIPS.at(s).strNAME == "Door")
            {
              cons.printwait("  G" + to_string(door) + " S" + to_string(s) + " :Door Close Active");
              vdDoorCloseActiveADV00(cons, sdSysData.CONFIG.LED_MAIN.at(0).vLED_GROUPS.at(door).vLED_STRIPS.at(s), teEvents, tmeCurrentTime);
            }
          }

          // Turn off additional lights overhead
          cons.printwait("  Add Off Strtip:" + to_string(door));

          for(int s=0; s < sdSysData.CONFIG.LED_MAIN.at(0).s_size(door); s++)
          {
            if (sdSysData.CONFIG.LED_MAIN.at(0).vLED_GROUPS.at(door).vLED_STRIPS.at(s).strNAME == "Overhead")
            {
              cons.printwait("  G" + to_string(door) + " S" + to_string(s) + " :Additional Close");
              vdAdditionalCloseADV00(cons, sdSysData.CONFIG.LED_MAIN.at(0).vLED_GROUPS.at(door).vLED_STRIPS.at(s), teEvents, tmeCurrentTime);
            }
          }
        }
      }
    }
  }

  // Check To See If Any Door Opened or Closed.
  if (changedetected == true)
  {
    // Count the amount of open doors
    for (int door=0; door < sdSysData.CONFIG.iNUM_SWITCHES; door++)
    {
      if (sdSysData.CONFIG.vhwDOORS.at(door).booVALUE  == true)
      {
        opencount = opencount  + 1;
      }
    }
    cons.printwait("Open Door Count: " + to_string(opencount));
    sdSysData.intDoorsOpen = opencount;
    // -----

    if (opencount > 0)
    {
      // There are open Doors
      for (int door=0; door < sdSysData.CONFIG.iNUM_SWITCHES; door++)
      {
        //strip = (door *2); // Determine Strip from Door aka Channel
        if (sdSysData.CONFIG.vhwDOORS.at(door).ISHARDWARE == true)  // Only if its real switch (with lights attached to it)
        {

          // If a door is open
          if (sdSysData.CONFIG.LED_MAIN.at(0).vLED_GROUPS.at(door).status("Door") != "Opened Door" 
              && sdSysData.CONFIG.LED_MAIN.at(0).vLED_GROUPS.at(door).status("Door") != "Closed Door")
          {
            // If this door is not open then make sure the closed door animation is running on it.
            cons.printwait("  Door " + to_string(door) + " Running Active Closed: ");

            // Closed Active Doors animation
            sdSysData.CONFIG.LED_MAIN.at(0).vLED_GROUPS.at(door).status_set("Door", "Closed Door");

            for(int s=0; s < sdSysData.CONFIG.LED_MAIN.at(0).s_size(door); s++) // There has got to be a better way.
            {
              if (sdSysData.CONFIG.LED_MAIN.at(0).vLED_GROUPS.at(door).vLED_STRIPS.at(s).strNAME == "Door")
              {
                cons.printwait("  G" + to_string(door) + " S" + to_string(s) + " :Close Active on Strip");
                vdDoorCloseActiveADV00(cons, sdSysData.CONFIG.LED_MAIN.at(0).vLED_GROUPS.at(door).vLED_STRIPS.at(s), teEvents, tmeCurrentTime);
              }
            }
          }

          // If  a door is open
          if (sdSysData.CONFIG.LED_MAIN.at(0).vLED_GROUPS.at(door).status("Overhead") != "Open Overhead")
          {
            // Make sure this door has the overhead animation running on it.
            cons.printwait("  Door " + to_string(door) + " Running Overhead: ");

            // Normal Overhead Animation 
            sdSysData.CONFIG.LED_MAIN.at(0).vLED_GROUPS.at(door).status_set("Overhead", "Open Overhead");

            for(int s=0; s < sdSysData.CONFIG.LED_MAIN.at(0).s_size(door); s++)
            {
              if (sdSysData.CONFIG.LED_MAIN.at(0).vLED_GROUPS.at(door).vLED_STRIPS.at(s).strNAME == "Overhead")
              {
                cons.printwait("  G" + to_string(door) + " S" + to_string(s) + " :Overhead Animation");
                vdPacificaishAnimationADV(cons, sdSysData.CONFIG.LED_MAIN.at(0).vLED_GROUPS.at(door).vLED_STRIPS.at(s), teEvents, tmeCurrentTime);
              }
            }
          }
        }
      }      
    }
    else 
      {
      // All doors are closed.
      cons.printwait("  All Doors Closed: ");

      for (int door=0; door < sdSysData.CONFIG.iNUM_SWITCHES; door++)
      {
        //strip = (door *2); // Determine Strip from Door aka Channel
          // Strip will be the door strip
          // Strip +1 is the door overhead strip // Try to avoid passing this also. 
          //  Let the Animations handle it.
        
        // Finalize additionall animations on newley closed doors
        if (sdSysData.CONFIG.vhwDOORS.at(door).ISHARDWARE == true)  // Only if its real switch (with lights attached to it)
        {
          //  Guarantee all animations end in 15 seconds. This is a fall back method to
          //    make sure everythings stops in case a clear animation fails to start.
          //vdEndAllAnimationsADV(cons, lsStrips,strip,teEvent,tmeCurrentTime);

          // Start the Doors Running Mode on each door.
          sdSysData.CONFIG.LED_MAIN.at(0).vLED_GROUPS.at(door).status_set("Door", "Closed Door Active");

          for(int s=0; s < sdSysData.CONFIG.LED_MAIN.at(0).s_size(door); s++)
          {
            if (sdSysData.CONFIG.LED_MAIN.at(0).vLED_GROUPS.at(door).vLED_STRIPS.at(s).strNAME == "Door")
            {
              vdDoorCloseRunningADV(cons, sdSysData.CONFIG.LED_MAIN.at(0).vLED_GROUPS.at(door).vLED_STRIPS.at(s), teEvents, tmeCurrentTime);
            }
          }

          //cons.printwait("All Doors Closed HWLVL: D%d AS%d" + to_string(door) + to_string(lsStrips[strip + 1].AnimationStatus));
          
          // Make sure lights are off or turning off and Amber Up the newly closded doors.
          if (sdSysData.CONFIG.LED_MAIN.at(0).vLED_GROUPS.at(door).status("Overhead") == "Open Overhead")
          {
            // Start Overhead Turn On Convenience Animation.
            // See when the door was closed
            // cons.printwait("Door Toggle Time (current time - toggle time): %d - %dms < 1500", tmeCurrentTime, hwmDoor[door].tmeTOGGLEDTIME);
            if ((tmeCurrentTime - sdSysData.CONFIG.vhwDOORS.at(door).tmeTOGGLEDTIME) < 15000)
            {
              // The door was recently closed. Run the Convienance lights on it.
              cons.printwait("  Door " + to_string(door) + " Conviencance Lights On: ");
              
              // Turn on Convienance Lights 
              sdSysData.CONFIG.LED_MAIN.at(0).vLED_GROUPS.at(door).status_set("Overhead", "Closed Overhead Convenince");

              for(int s=0; s < sdSysData.CONFIG.LED_MAIN.at(0).s_size(door); s++)
              {
                if (sdSysData.CONFIG.LED_MAIN.at(0).vLED_GROUPS.at(door).vLED_STRIPS.at(s).strNAME == "Overhead")
                {
                  vdCoADV01(cons, sdSysData.CONFIG.LED_MAIN.at(0).vLED_GROUPS.at(door).vLED_STRIPS.at(s), teEvents, tmeCurrentTime);
                }
              }
            }
            else
            {
              // The door was closed for a while, just turn off the lights.
              // Start the Close Door Overhead Animation
              cons.printwait("  Door " + to_string(door) + " Overhead Lights Off: ");

              // Just turn off the lights.
              sdSysData.CONFIG.LED_MAIN.at(0).vLED_GROUPS.at(door).status_set("Overhead", "Closed Overhead");

              for(int s=0; s < sdSysData.CONFIG.LED_MAIN.at(0).s_size(door); s++)
              {
                if (sdSysData.CONFIG.LED_MAIN.at(0).vLED_GROUPS.at(door).vLED_STRIPS.at(s).strNAME == "Overhead")
                {
                  vdCloseOverADV(cons, sdSysData.CONFIG.LED_MAIN.at(0).vLED_GROUPS.at(door).vLED_STRIPS.at(s), teEvents, tmeCurrentTime);
                }
              }
            }
          }
        }
      }
    }
  }
}




#endif