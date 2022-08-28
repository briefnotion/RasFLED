// ***************************************************************************************
// *
// *    Core       | Everything within this document is proprietary to Core Dynamics.
// *    Dynamics   | Any unauthorized duplication will be subject to prosecution.
// *
// *    Department : (R+D)^2                        Name: interface.h
// *       Sub Dept: Programming
// *    Location ID: 856-45B
// *                                                      (c) 2856 - 2858 Core Dynamics
// ***************************************************************************************

#ifndef INTERFACE_H
#define INTERFACE_H

// Standard Header Files
#include <string>

// RASFled related header files
#include "stringthings.h"
#include "consoleanddata.h"
#include "timedeventsystem.h"
#include "commands.h"


// ***************************************************************************************
// STRUCTURES AND CLASSES
// ***************************************************************************************


// ***************************************************************************************
// FUNCTION AND PROCEDURES
// ***************************************************************************************

void command_desc(Console &cons, string strDescription);

// -------------------------------------------------------------------------------------
// Console Commands

// -------------------------------------------------------------------------------------
// Procedures related to the Command Line.

// Display the help screen.
void consoleprinthelp(Console &cons);

// Display all running events.
void consoleprintevents(Console &cons, system_data &sdSysData, timed_event teEvent[]);

// Display all running events.
void consoleprintconfig(Console &cons, system_data &sdSysData, timed_event teEvent[]);

// -------------------------------------------------------------------------------------
// Test Animation

void processtestanimation(Console &cons, system_data &sdSysData, unsigned long tmeCurrentTime, timed_event teEvent[], CRGB cRGBpulsecolor);

void process_power_animation(Console &cons, system_data &sdSysData, unsigned long tmeCurrentTime, timed_event teEvent[], CRGB cRGBpulsecolor);

// -------------------------------------------------------------------------------------
// Pulses

// Set To End All Pulses
void processcommandpulseend(Console &cons, system_data &sdSysData, unsigned long tmeCurrentTime, timed_event teEvent[]);

// Flash Color All Channels
void processcommandflash(Console &cons, system_data &sdSysData, unsigned long tmeCurrentTime, timed_event teEvent[], CRGB cRGBflashcolor);

// Pulse Color All Channels
void processcommandpulse(Console &cons, system_data &sdSysData, unsigned long tmeCurrentTime, timed_event teEvent[], CRGB cRGBpulsecolor);
// Pulse Color All Channels
void processcommandpulsecountdown(Console &cons, system_data &sdSysData, unsigned long tmeCurrentTime, timed_event teEvent[]);

// -------------------------------------------------------------------------------------
// Overhead Illum

// Set To End All Overhead Illumination
void processcommandoverheadillumend(Console &cons, system_data &sdSysData, unsigned long tmeCurrentTime, timed_event teEvent[]);

// -------------------------------------------------------------------------------------
// Overhead Illumination Color
void processcommandoverheadillum(Console &cons, system_data &sdSysData, unsigned long tmeCurrentTime, timed_event teEvent[], CRGB cRGBpulsecolor);

//  Overhead Illumination Pacificaish Color
void processcommandpacificaishcolor(Console &cons, system_data &sdSysData, unsigned long tmeCurrentTime, timed_event teEvent[], CRGB cRGBpulsecolor);

// -------------------------------------------------------------------------------------
// Hazard

// Set To End All Hazard
void processcommandhazardend(Console &cons, system_data &sdSysData, unsigned long tmeCurrentTime, timed_event teEvent[]);

// Hazard
void processcommandhazard(Console &cons, system_data &sdSysData, unsigned long tmeCurrentTime, timed_event teEvent[], CRGB cRGBpulsecolor);

// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------

bool check_command(Console &cons, string command, string description);

bool check_command_with_num_param(Console &cons, string command, string description, int num_start, int num_len, int &Parameter);


// Process and call routines as entered on the command line.
void processcommandlineinput(Console &cons, system_data &sdSysData, unsigned long tmeCurrentTime, timed_event teEvent[]);

// If a door is opened and DOORAWARE is on, we want to end these animations when the door
//  has been opened.
void extraanimationdoorcheck(Console &cons, system_data &sdSysData, unsigned long tmeCurrentTime, timed_event teEvent[] );



#endif