// ***************************************************************************************
// *
// *    Core       | Everything within this document is proprietary to Core Dynamics.
// *    Dynamics   | Any unauthorized duplication will be subject to prosecution.
// *
// *    Department : (R+D)^2                        Name: automobile_handler.h
// *       Sub Dept: Programming
// *    Location ID: 856-45B
// *                                                      (c) 2856 - 2858 Core Dynamics
// ***************************************************************************************

#ifndef AUTOMOBILE_HANDLER_H
#define AUTOMOBILE_HANDLER_H

// Standard Header Files
#include <stdio.h>
//#include <ncurses.h>
//#include <string>
//#include <deque>

#include "auto.h"
#include "animations_handler.h"
//#include "stringthings.h"
//#include "system.h"
//#include "gadgets.h"
//#include "helper_ncurses.h"
//#include "auto.h"
//#include "helper.h"
//#include "symbols.h"

using namespace std;

// -------------------------------------------------------------------------------------
//  

class AUTOMOBILE_HANDLER
{
  private:
  // 

  bool AUTO_ACTIVE = false;

  bool GEAR_PARK = true;
  bool GEAR_REVERSE = true;

  public:

  void update_events(system_data &sdSysData, ANIMATION_HANDLER &Animations, unsigned long tmeCurrentTime);
};

// -------------------------------------------------------------------------------------

#endif