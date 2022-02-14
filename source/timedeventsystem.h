// ***************************************************************************************
// *
// *    Core       | Everything within this document is proprietary to Core Dynamics.
// *    Dynamics   | Any unauthorized duplication will be subject to prosecution.
// *
// *    Department : (R+D)^2                        Name: timedeventsystem.h
// *       Sub Dept: Programming
// *    Location ID: 856-45B
// *                                                      (c) 2856 - 2858 Core Dynamics
// ***************************************************************************************

#ifndef TIMEDEVENTSYSTEM_H
#define TIMEDEVENTSYSTEM_H

// RASFled related header files
#include "animations.h"



// ***************************************************************************************
// FUNCTION AND PROCEDURES
// ***************************************************************************************


// -------------------------------------------------------------------------------------
// Clear events on a channel 

void vdClearAllTimedEvent(timed_event teEvent[], int intPos, int intStartPos, int intEndPos)
//  Sort through the timed event list a create an event at the first slot available.
{
  teEvent[intPos].ClearAll(intStartPos, intEndPos);
}


// -------------------------------------------------------------------------------------
// System event system for non animations.

void teSystem(Console &cons, system_data &sdSysData, timed_event teEvent[], unsigned long tmeCurrentTime)
//void teSystem(Console &cons, led_strip lsStripList[], timed_event teEvent[], unsigned long tmeCurrentTime)
// Example:
//  teEvent[0].set(tmeCurrentMillis, X, 0, 0, AnEvSc