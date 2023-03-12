// ***************************************************************************************
// *
// *    Core       | Everything within this document is proprietary to Core Dynamics.
// *    Dynamics   | Any unauthorized duplication will be subject to prosecution.
// *
// *    Department : (R+D)^2                        Name: configuration.h
// *       Sub Dept: Programming
// *    Location ID: 856-45B
// *                                                      (c) 2856 - 2858 Core Dynamics
// ***************************************************************************************

#ifndef CONFIGURATION_H
#define CONFIGURATION_H

// RASFled related header files
#include "definitions.h"
#include "hardware_status.h"
#include "LEDstuff.h"

using namespace std;

// -------------------------------------------------------------------------------------
class configuration
{
  public:

  // -------------------------------------------------------------------------------------
  // Hardware to Software definitions
  // -------------------------------------------------------------------------------------
  
  // -------------------------------------------------------------------------------------
  // Raspberry Pi switch pin for doors and switches. Defined as WiringPi id.
  // console: gpio -v       (check installation)
  // console: gpio readall  (check wiring pin numbers)

  int iAUXDRLINGERFRT     = 15000;    // How long the Front Door lights stay on after close
  int iAUXDRLINGERBCK     = 25000;    // How long the Back Door lights stay on after close

  // -------------------------------------------------------------------------------------
  // LED rpi_ws281x Variables
  int iBRIGHTNESS         = 96;  //96  Using Example Code.  Max unknown
  int iFRAMES_PER_SECOND  = LED_FPS; // Will not be necessary, but keeping, for now, just in 
                                //  case.

  // -------------------------------------------------------------------------------------
  // Events
  int iNUM_CHANNELS       = 0;   // Amount of Event Channels we will be controlling.
  int CHANNELS            = 0;   // Amount of Event Channels we will be controlling.

  // -------------------------------------------------------------------------------------
  // LED Group List
  deque<v_profile_strip_main> LED_MAIN; // Main LED Profile of Groups

  // -------------------------------------------------------------------------------------
  // New Door Switch Reference
  int iNUM_SWITCHES       = 4;              // Amount of HW switches
  deque<hardware_monitor> vhwDOORS;         // List of HW Monitors
  deque<switch_map>       vSWITCH_PIN_MAP;  // Map of Hardware Circuit Pin ID to 
                                            //  software Pin ID
};
// -------------------------------------------------------------------------------------



#endif