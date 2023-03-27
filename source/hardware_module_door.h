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
#include "animations_handler.h"

// ***************************************************************************************
// STRUCTURES AND CLASSES
// ***************************************************************************************


// ***************************************************************************************
// FUNCTION AND PROCEDURES
// ***************************************************************************************

void v_DoorMonitorAndAnimationControlModule2(Console &cons, system_data &sdSysData, ANIMATION_HANDLER &Animations, unsigned long tmeCurrentTime);




#endif