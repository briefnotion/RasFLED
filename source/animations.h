// ***************************************************************************************
// *
// *    Core       | Everything within this document is proprietary to Core Dynamics.
// *    Dynamics   | Any unauthorized duplication will be subject to prosecution.
// *
// *    Department : (R+D)^2                        Name: animations.h
// *       Sub Dept: Programming
// *    Location ID: 856-45B
// *                                                      (c) 2856 - 2858 Core Dynamics
// ***************************************************************************************

#ifndef ANIMATIONS_H
#define ANIMATIONS_H

// Standard Header Files
#include <string.h>

// RASFled related header files
#include "definitions.h"
#include "helper.h"
#include "consoleanddata.h"
#include "fledcore.h"


// ***************************************************************************************
// FUNCTION AND PROCEDURES
// ***************************************************************************************

// PARAMETER REFFERENCE

//  Reference:
//TIMED EVENT  PARAMETERS
//light_path lpLightPaths[],
//unsigned long tmeCurrentTime,
//unsigned long tmeStartInTime,
//unsigned int intDuration,
//unsigned int intSpeed,
//char  bytAnimation,
//char  bytLEDAnimation,
//CRGB crgbColor,
//int intStartPos,
//int intEndPos,
//bool booRepeat,
//bool booClearOnEnd,


// -------------------------------------------------------------------------------------
// Calculate time it takes for an animation event to run.

int intAnTmDly(int intTm, int intDur, int intCt, int intSp)
// Calculate and return the next delay time based on duration of event, number of pixels,
//  and animation speed of each pixel.
//  Value in return statement is buffer time.
{
  //return (1 + (RESTTIME) + intTm + intDur + (intSp * intCt));
  return (1 + intTm + intDur + (intSp * intCt));
}


// --- ANIMATIONS ------------------------------------------------------------------------

/*
// -------------------------------------------------------------------------------------
void vdTESTFLASHAnimation(Console &cons, led_strip lsStrips[], led_strip lsSt, timed_event teEvent[], unsigned long tmeCurrentTime)
{
  int intTm;
  int intDur;
  int intCt;
  int intSp;

  intDur = 500; intSp = 50; intCt = lsStrips[intStripID].Ct();
  teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, 50, intDur, intSp, AnEvSweep, AnPiPulseTo, CRGB(20, 20, 20), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, true);
}
*/

// -------------------------------------------------------------------------------------
// Animations and Animation Scripts
// -------------------------------------------------------------------------------------

// Normal Animations (Main Procedures)


/*
void vdOpenDoorNormal(Console &cons, led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// AnTavdOpenDoorNormal
{
  teEvent[lsStrips[intStripID].Cl].set("vdOpenDoor", tmeCurrentTime, 10, 0, 0, AnEvSchedule, AnTaDoorOpen00, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
}

void vdOpenOverNormal(Console &cons, led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// AnTavdOpenOverNormal
{
  teEvent[lsStrips[intStripID].Cl].set("Overhead Open Anim", tmeCurrentTime, 10, 0, 0, AnEvSchedule, AnTavdPacificaish, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
}

void vdCloseDoorNormal(Console &cons, led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// AnTavdCloseDoorNormal
{
  teEvent[lsStrips[intStripID].Cl].set("Door Close Anim", tmeCurrentTime, 100, 0, 0, AnEvSchedule, AnTaChannelPulseColor, false, CRGB(125,125,0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
}

void vdCloseOverNormal(Console &cons, led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// AnTavdCloseOverNormal
{
  teEvent[lsStrips[intStripID].Cl].set("Overhead Close Anim", tmeCurrentTime, 10, 0, 0, AnEvSchedule, AnTaStripOverOff, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
}

void vdCloseOverCoNormal(Console &cons, led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// AnTavdCloseOve2Normal
{
  int intTm;
  int intDur;
  int intSp;

  //Restore the privouse Blue to fade out
  intTm = 200; intDur = 6000; intSp = 5;

  teEvent[lsStrips[intStripID].Cl].set("Overhead Close Convenience Anim", tmeCurrentTime, intTm , intDur, intSp, AnEvSweep, AnPiPulse, false, CRGB(0, 0, 60), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].Ed, lsStrips[intStripID].St, false, true);
  teEvent[lsStrips[intStripID].Cl].set("Overhead Close Convenience Anim", tmeCurrentTime, 10, 0, 0, AnEvSchedule, AnTavdPaAnimClose, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
}
*/

// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------

/*
// Halloween Animations (Main Procedures)

void vdOpenOverHallow(Console &cons, led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// AnTavdOpenOverHallow
{
  //teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, 10, 0, 0, AnEvSchedule, AnTavdCloud, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
  teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, 10, 0, 0, AnEvSchedule, AnTavdCeilingLight, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
  teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, 10, 0, 0, AnEvSchedule, AnTavdLightning, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
}

void vdCloseOverHallow(Console &cons, led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// AnTavdCloseOverHallow
{
  teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, 10, 0, 0, AnEvSchedule, AnTavdChannelLightning, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
}

void vdHallowClose2(Console &cons, led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// Halloween Overhead Close 2 - Orange Ambiant and Off Routine
{
  // AnTavdHallowClose2

  // Stop the animation.
  // Schedule clear animation events ahead of time in case animations don't get completed.
  teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, AUXDRLINGERBCK + 2000, 0, 0, AnEvClearRunning, 0, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, false);
  teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, AUXDRLINGERBCK + 2100, 3000, 30, AnEvSweep, AnPiFade, CRGB(4, 6, 10), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, false);

  teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, 10, 0, 0, AnEvSchedule, AnTavdChannelLightning, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
  teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, 50, 0, 0, AnEvSchedule, AnTavdCloud, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[lsStrips[intStripID].Cl].St, lsStrips[lsStrips[intStripID].Cl].Ed, false, true);
}


// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------


// Thanksgiving Animations (Main Procedures)

void vdOpenOverThanks(Console &cons, led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// AnTavdOpenOverThanks
{
  teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, 10, 0, 0, AnEvSchedule, AnTavdBlueSky, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
}

void vdCloseOverThanks(Console &cons, led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// AnTavdCloseOverThanks
{
  //teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, 10, 0, 0, AnEvSchedule, AnTaStripOverOffThanks, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
  teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, 100, 0, 0, AnEvSchedule, AnTaChannelPulseColor, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
}

void vdCloseOverThanksCo(Console &cons, led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// AnTavdCloseOverThanksCo
{
  teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, 10, 0, 0, AnEvSchedule, AnTavdNightSkyClose, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
}

void vdAddOpenThanks(Console &cons, led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// AnTavd----  // Simple
{
  teEvent[lsStrips[intStripID +1].Cl].set("Nothing", tmeCurrentTime, 4000, 1000, 40, AnEvSweep, AnPiFadeDith, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(125,125,0), lsStrips[intStripID +1].St, lsStrips[intStripID +1].Ed, false, false);
}

void vdAddCloseThanks(Console &cons, led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// AnTavd----  // Simple
{
  teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, 4000, 1000, 40, AnEvSweep, AnPiFade, CRGB(0, 0, 0), CRGB(0, 0, 30), CRGB(0, 0, 0), CRGB(0, 0, 30), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, false);
  teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, intRandomHD(2000), intRandomHD(10000), intRandomHD(125), AnEvSweep, AnPiPulse, CRGB(30, 30, 30), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, true);
}
*/


// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------

// Christmas Animations (Main Procedures)

// Normal Animations (Main Procedures)

/*
void vdOpenDoorChristmas(Console &cons, led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// ---
{
  teEvent[lsStrips[intStripID].Cl].set("vdOpenDoor", tmeCurrentTime, 10, 0, 0, AnEvSchedule, AnTaDoorOpen00Christmas, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
}

void vdOpenOverChristmas(Console &cons, led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// ---
{
  teEvent[lsStrips[intStripID].Cl].set("Overhead Open Anim", tmeCurrentTime, 10, 0, 0, AnEvSchedule, AnTavdChristmasTree, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
}

void vdCloseDoorChristmas(Console &cons, led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// ---
{
  teEvent[lsStrips[intStripID].Cl].set("Door Close Anim", tmeCurrentTime, 100, 0, 0, AnEvSchedule, AnTaChannelPulseColor, false, CRGB(64,64,0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
}

void vdCloseOverChristmas(Console &cons, led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// ---
{
  teEvent[lsStrips[intStripID].Cl].set("Overhead Close Anim", tmeCurrentTime, 100, 0, 0, AnEvSchedule, AnTaChannelPulseColor, false, CRGB(64,64,0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
}

void vdCloseOverCoChristmas(Console &cons, led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// ---
{
  teEvent[lsStrips[intStripID].Cl].set("Overhead Close Anim", tmeCurrentTime, 10, 0, 0, AnEvSchedule, AnTavdChristmasTreeCo, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);  
}

void vdAddOpenChristmas(Console &cons, led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// AnTavd----  // Simple
{
  teEvent[lsStrips[intStripID].Cl].set("Open Additional Anim", tmeCurrentTime, 500, 0, 0, AnEvSchedule, AnTavdAddOpenChristm, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);  
}

void vdAddCloseChristmas(Console &cons, led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// AnTavd----  // Simple
{
  teEvent[lsStrips[intStripID].Cl].set("Door Open Anim", tmeCurrentTime, 500, 0, 0, AnEvSchedule, AnTavdAddCloseChristm, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);    
 }
*/

// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------

// Test Animations (Main Procedures)

/*
void vdOpenDoorTest(Console &cons, led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// AnTavdOpenDoorNormal
{
  //teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, 500, 8000, 0, AnEvSweep, AnPiTwinkle, CRGB(128, 0, 0), CRGB(0, 128, 0), CRGB(0, 0, 128), CRGB(1, 90, 3), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, false);
  //teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, 1500, 8000, 0, AnEvSweep, AnPiTwinkle, CRGB(64, 64, 0), CRGB(64, 0, 64), CRGB(0, 64, 64), CRGB(1, 90, 3), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, false);

  teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, 500, 8000, 0, AnEvSweep, AnPiTwinkle, false, CRGB(64, 64, 64), CRGB(64, 0, 64), CRGB(0, 64, 64), CRGB(4, 90, 1), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, false);

  //teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, 400, 350, 0, AnEvSweep, AnPiTwinkle, CRGB(128, 0, 0), CRGB(0, 128, 0), CRGB(0, 0, 128), CRGB(4, 0, 3), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, false);
  //teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, 500, 475, 0, AnEvSweep, AnPiTwinkle, CRGB(128, 0, 0), CRGB(0, 128, 0), CRGB(0, 0, 128), CRGB(4, 0, 3), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, false);
  //teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, 600, 525, 0, AnEvSweep, AnPiTwinkle, CRGB(128, 0, 0), CRGB(0, 128, 0), CRGB(0, 0, 128), CRGB(4, 0, 3), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, false);

  //teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, 500, 4000, 0, AnEvSweep, AnPiTwinkle, CRGB(128, 0, 0), CRGB(0, 128, 0), CRGB(0, 0, 128), CRGB(2, 0, 3), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, false);
  //teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, 400, 6237, 0, AnEvSweep, AnPiTwinkle, CRGB(128, 0, 0), CRGB(0, 128, 0), CRGB(0, 0, 128), CRGB(2, 0, 3), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, false);
  //teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, 300, 8713, 0, AnEvSweep, AnPiTwinkle, CRGB(128, 0, 0), CRGB(0, 128, 0), CRGB(0, 0, 128), CRGB(20, 0, 3), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, false);
  //teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, 200, 11031, 0, AnEvSweep, AnPiTwinkle, CRGB(128, 0, 0), CRGB(0, 128, 0), CRGB(0, 0, 128), CRGB(20, 0, 3), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, false);
}
*/

// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------

// Standard Animations and Effects 

/*
void vdPowerOnAnimation(Console &cons, led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// Just to show the lights work when the program starts.
{
  // Update Animation Status 
  lsStrips[Driver_Back_Door].AnimationStatus = Unknown;
  lsStrips[Driver_Back_Over].AnimationStatus = Unknown;
  lsStrips[Driver_Front_Door].AnimationStatus = Unknown;
  lsStrips[Driver_Front_Over].AnimationStatus = Unknown;
  lsStrips[Passenger_Back_Door].AnimationStatus = Unknown;
  lsStrips[Passenger_Back_Over].AnimationStatus = Unknown;
  lsStrips[Passenger_Front_Door].AnimationStatus = Unknown;
  lsStrips[Passenger_Front_Over].AnimationStatus = Unknown;


  int intTm;
  int intDur;
  int intCt;
  int intSp;

  intDur = 250; intSp = 5; intCt = 118;
  // Pulse Front Door
  teEvent[1].set("Nothing", tmeCurrentTime, 50, intDur, intSp, AnEvSweep, AnPiPulseTo, false,  CRGB(125, 125, 125),CRGB(0, 0, 25), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[Front_Over].Ed, lsStrips[Front_Door].St, false, true);
  // Pulse Back Door
  teEvent[0].set("Nothing", tmeCurrentTime, 640, intDur, intSp, AnEvSweep, AnPiPulseTo, false, CRGB(125, 125, 125), CRGB(0, 0, 25), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[Back_Over].Ed, lsStrips[Back_Door].St, false, true);


  intDur = 2000; intSp = 15; intCt = 71;
  // Clear Front Door
  teEvent[1].set("Nothing", tmeCurrentTime, 890, intDur, intSp, AnEvSweep, AnPiFade, false, CRGB(0, 0, 25), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[Front_Over].Ed, lsStrips[Front_Door].St, false, true);
  // Clear Back Door
  teEvent[0].set("Nothing", tmeCurrentTime, 1480, intDur, intSp, AnEvSweep, AnPiFade, false, CRGB(0, 0, 25), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[Back_Over].Ed, lsStrips[Back_Door].St, false, true);
}
*/

// -------------------------------------------------------------------------------------

/*
// Pulse strip Color then fade out.

void vdStripOverOff(Console &cons, profile_strip_group strip_group, timed_event teEvent[], unsigned long tmeCurrentTime)
// Turn (force) Lights Off ona Strip
{
  int intTm;
  int intDurW;
  int intDurG;
  int intSp;

  int intDelay;

  // Clear and Pulse colors background to color then ending in color, starting with the center.
  intTm = 50; intDurW = 200; intDurG = 1500; intSp = 5;
  intDelay = intAnTmDly(intTm, 0, strip_group.pstrDOOR.intSIZE, intSp);

  // Door White
  //teEvent[lsStrips[intStripID].Cl].set("vdStripOverOff", tmeCurrentTime, intTm + 50, intDurW, intSp, AnEvSweep, AnPiPulse, CRGB(64, 128, 64), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[lsStrips[intStripID].Cl].St, lsStrips[lsStrips[intStripID].Cl].Ed, false, true);
  // Overhead White
  teEvent[strip_group.pstrDOOR.intCHANNEL].set("vdStripOverOff", tmeCurrentTime, intTm + intDelay + 50, intDurW, intSp, AnEvSweep, AnPiPulse, false, CRGB(64, 128, 64), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), strip_group.pstrOVERHEAD.ft(0), strip_group.pstrOVERHEAD.fb(0), false, true);
 
  // Door Green Fadeout
  //teEvent[lsStrips[intStripID].Cl].set("vdStripOverOff", tmeCurrentTime, intTm, intDurG, intSp, AnEvSweep, AnPiPulse, CRGB(0, 128, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[lsStrips[intStripID].Cl].St, lsStrips[lsStrips[intStripID].Cl].Ed, false, true);
  // Overhead Green Fadeout
  teEvent[strip_group.pstrDOOR.intCHANNEL].set("vdStripOverOff", tmeCurrentTime, intTm + intDelay, intDurG, intSp, AnEvSweep, AnPiPulse, false, CRGB(0, 128, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), strip_group.pstrOVERHEAD.ft(0), strip_group.pstrOVERHEAD.fb(0), false, true);
}
*/

// -------------------------------------------------------------------------------------

// Console Called Animations 

void vdChannelLightFlashColor00(Console &cons, profile_strip_group strip_group, timed_event teEvent[], unsigned long tmeCurrentTime, CRGB crgbColor)
// Turn Color Pulse on Full Channel. Strip Length Aware. 
// AnTaChannelPulseColor
{
  cons.printwait("Flash Color (CL: " + std::to_string(strip_group.pstrDOOR.intCHANNEL));
  int intTm;
  int intDurW;
  int intDurG;
  int intCt;

  int intDelay;

  // Set the fadeout color 
  CRGB crgbColor4;
  crgbColor4.r = crgbColor.r / 3;
  crgbColor4.g = crgbColor.g / 3;
  crgbColor4.b = crgbColor.b / 3;

  // Clear and Pulse colors background to bright then param color, starting with the center.
  intTm = 50; intDurW = 2000; intDurG = 5000; 
  
  int intSpBack = 0; 
  int intSpAntiPuls = 15; 
  int intDurAnti = 150;
  
  intCt = 36;
  //intDelay = intAnTmDly(intTm, 0, strip_group.pstrDOOR.intSIZE, intSp);

  // 1
  // Door Color with White
  teEvent[strip_group.pstrDOOR.intCHANNEL].set("Channel Light Pulse Color", tmeCurrentTime, intTm + 50, intDurW, intSpBack, AnEvSweep, AnPiPulse, false, CRGB(0, 0, 0), crgbColor, CRGB(0, 0, 0), CRGB(0, 0, 0), strip_group.pstrDOOR.ft(0), strip_group.pstrDOOR.fb(0), false, true);
  teEvent[strip_group.pstrOVERHEAD.intCHANNEL].set("Channel Light Pulse Color", tmeCurrentTime, intTm + 50, intDurW, intSpBack, AnEvSweep, AnPiPulse, false, CRGB(0, 0, 0), crgbColor, CRGB(0, 0, 0), CRGB(0, 0, 0), strip_group.pstrOVERHEAD.ft(0), strip_group.pstrOVERHEAD.fb(0), false, true);

  // Forward ---
  // Anti Red
  teEvent[strip_group.pstrDOOR.intCHANNEL].set("Channel Light Pulse Color", tmeCurrentTime, intTm + 50 + (1*intDurAnti), intDurAnti, intSpAntiPuls, AnEvSweep, AnPiPulse, true, CRGB(0, 0, 0), CRGB(0, 128, 128), CRGB(0, 0, 0), CRGB(0, 0, 0), strip_group.pstrDOOR.ft(0), strip_group.pstrDOOR.fb(0), false, true);
  teEvent[strip_group.pstrOVERHEAD.intCHANNEL].set("Channel Light Pulse Color", tmeCurrentTime, intTm + 50 + (1*intDurAnti), intDurAnti, intSpAntiPuls, AnEvSweep, AnPiPulse, true, CRGB(0, 0, 0), CRGB(0, 128, 128), CRGB(0, 0, 0), CRGB(0, 0, 0), strip_group.pstrOVERHEAD.ft(0), strip_group.pstrOVERHEAD.fb(0), false, true);

  // Anti Green
  teEvent[strip_group.pstrDOOR.intCHANNEL].set("Channel Light Pulse Color", tmeCurrentTime, intTm + 50 + (2*intDurAnti), intDurAnti, intSpAntiPuls, AnEvSweep, AnPiPulse, true, CRGB(0, 0, 0), CRGB(128, 0, 128), CRGB(0, 0, 0), CRGB(0, 0, 0), strip_group.pstrDOOR.ft(0), strip_group.pstrDOOR.fb(0), false, true);
  teEvent[strip_group.pstrOVERHEAD.intCHANNEL].set("Channel Light Pulse Color", tmeCurrentTime, intTm + 50 + (2*intDurAnti), intDurAnti, intSpAntiPuls, AnEvSweep, AnPiPulse, true, CRGB(0, 0, 0), CRGB(128, 0, 128), CRGB(0, 0, 0), CRGB(0, 0, 0), strip_group.pstrOVERHEAD.ft(0), strip_group.pstrOVERHEAD.fb(0), false, true);

  // Anti Blue
  teEvent[strip_group.pstrDOOR.intCHANNEL].set("Channel Light Pulse Color", tmeCurrentTime, intTm + 50 + (3*intDurAnti), intDurAnti, intSpAntiPuls, AnEvSweep, AnPiPulse, true, CRGB(0, 0, 0), CRGB(128, 128, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), strip_group.pstrDOOR.ft(0), strip_group.pstrDOOR.fb(0), false, true);
  teEvent[strip_group.pstrOVERHEAD.intCHANNEL].set("Channel Light Pulse Color", tmeCurrentTime, intTm + 50 + (3*intDurAnti), intDurAnti, intSpAntiPuls, AnEvSweep, AnPiPulse, true, CRGB(0, 0, 0), CRGB(128, 128, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), strip_group.pstrOVERHEAD.ft(0), strip_group.pstrOVERHEAD.fb(0), false, true);

  // Backward ---
  // Anti Red
  teEvent[strip_group.pstrDOOR.intCHANNEL].set("Channel Light Pulse Color", tmeCurrentTime, intTm + 50 + (1*intDurAnti), intDurAnti, intSpAntiPuls, AnEvSweep, AnPiPulse, true, CRGB(0, 0, 0), CRGB(0, 128, 128), CRGB(0, 0, 0), CRGB(0, 0, 0), strip_group.pstrDOOR.fb(0), strip_group.pstrDOOR.ft(0), false, true);
  teEvent[strip_group.pstrOVERHEAD.intCHANNEL].set("Channel Light Pulse Color", tmeCurrentTime, intTm + 50 + (1*intDurAnti), intDurAnti, intSpAntiPuls, AnEvSweep, AnPiPulse, true, CRGB(0, 0, 0), CRGB(0, 128, 128), CRGB(0, 0, 0), CRGB(0, 0, 0), strip_group.pstrOVERHEAD.fb(0), strip_group.pstrOVERHEAD.ft(0), false, true);

  // Anti Green
  teEvent[strip_group.pstrDOOR.intCHANNEL].set("Channel Light Pulse Color", tmeCurrentTime, intTm + 50 + (2*intDurAnti), intDurAnti, intSpAntiPuls, AnEvSweep, AnPiPulse, true, CRGB(0, 0, 0), CRGB(128, 0, 128), CRGB(0, 0, 0), CRGB(0, 0, 0), strip_group.pstrDOOR.fb(0), strip_group.pstrDOOR.ft(0), false, true);
  teEvent[strip_group.pstrOVERHEAD.intCHANNEL].set("Channel Light Pulse Color", tmeCurrentTime, intTm + 50 + (2*intDurAnti), intDurAnti, intSpAntiPuls, AnEvSweep, AnPiPulse, true, CRGB(0, 0, 0), CRGB(128, 0, 128), CRGB(0, 0, 0), CRGB(0, 0, 0), strip_group.pstrOVERHEAD.fb(0), strip_group.pstrOVERHEAD.ft(0), false, true);

  // Anti Blue
  teEvent[strip_group.pstrDOOR.intCHANNEL].set("Channel Light Pulse Color", tmeCurrentTime, intTm + 50 + (3*intDurAnti), intDurAnti, intSpAntiPuls, AnEvSweep, AnPiPulse, true, CRGB(0, 0, 0), CRGB(128, 128, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), strip_group.pstrDOOR.fb(0), strip_group.pstrDOOR.ft(0), false, true);
  teEvent[strip_group.pstrOVERHEAD.intCHANNEL].set("Channel Light Pulse Color", tmeCurrentTime, intTm + 50 + (3*intDurAnti), intDurAnti, intSpAntiPuls, AnEvSweep, AnPiPulse, true, CRGB(0, 0, 0), CRGB(128, 128, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), strip_group.pstrOVERHEAD.fb(0), strip_group.pstrOVERHEAD.ft(0), false, true);
}

void vdChannelLightPulseColor(Console &cons, profile_strip_group strip_group, timed_event teEvent[], unsigned long tmeCurrentTime, CRGB crgbColor)
// Turn Color Pulse on Full Channel. Strip Length Aware. 
// AnTaChannelPulseColor
{
  cons.printwait("Pulse Color (CL: " + std::to_string(strip_group.pstrDOOR.intCHANNEL));
  int intTm;
  int intDurW;
  int intDurG;
  int intSp;

  int intDelay;
  int intDelayGlitchAnti;

  // Set the fadeout color 
  CRGB crgbColor4;
  crgbColor4.r = crgbColor.r + 128;
  crgbColor4.g = crgbColor.g + 128;
  crgbColor4.b = crgbColor.b + 128;

  // Clear and Pulse colors background to bright then param color, starting with the center.
  intTm = 100; intDurW = 500; intDurG = 1500; intSp = 30; 

  intDelay = intAnTmDly(intTm, 0, strip_group.pstrDOOR.intSIZE, intSp);
  intDelayGlitchAnti = intAnTmDly(intTm + intDelay, intDurW/8, strip_group.pstrOVERHEAD.intSIZE, intSp/4);

  // Door Color with White and Trail Color
  teEvent[strip_group.pstrDOOR.intCHANNEL].set("Channel Light Pulse Color", tmeCurrentTime, intTm, intDurW, intSp, AnEvSweep, AnPiPulse, false, CRGB(0, 0, 0), crgbColor4, CRGB(0, 0, 0), CRGB(0, 0, 0), strip_group.pstrDOOR.ft(0), strip_group.pstrDOOR.fb(0), false, true);
  teEvent[strip_group.pstrDOOR.intCHANNEL].set("Channel Light Pulse Color", tmeCurrentTime, intTm, intDurG, intSp, AnEvSweep, AnPiPulse, false, CRGB(0, 0, 0), crgbColor, CRGB(0, 0, 0), CRGB(0, 0, 0), strip_group.pstrDOOR.ft(0), strip_group.pstrDOOR.fb(0), false, true);
  // Glitch
  teEvent[strip_group.pstrDOOR.intCHANNEL].set("Channel Light Pulse Color", tmeCurrentTime, intTm - 20, 50, intSp, AnEvSweep, AnPiPulse, false, CRGB(0, 0, 0), CRGB(96, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), strip_group.pstrDOOR.ft(0), strip_group.pstrDOOR.fb(0), false, true);
  teEvent[strip_group.pstrDOOR.intCHANNEL].set("Channel Light Pulse Color", tmeCurrentTime, intTm - 40, 50, intSp, AnEvSweep, AnPiPulse, false, CRGB(0, 0, 0), CRGB(0, 0, 96), CRGB(0, 0, 0), CRGB(0, 0, 0), strip_group.pstrDOOR.ft(0), strip_group.pstrDOOR.fb(0), false, true);
  teEvent[strip_group.pstrDOOR.intCHANNEL].set("Channel Light Pulse Color", tmeCurrentTime, intDelayGlitchAnti, intDurW/8, intSp/4, AnEvSweep, AnPiPulse, true, CRGB(0, 0, 0), crgbColor4, CRGB(0, 0, 0), CRGB(0, 0, 0), strip_group.pstrDOOR.ft(0), strip_group.pstrDOOR.fb(0), false, true);

  // Overhead Color with White and Trail Color
  teEvent[strip_group.pstrOVERHEAD.intCHANNEL].set("Channel Light Pulse Color", tmeCurrentTime, intTm + intDelay, intDurW, intSp, AnEvSweep, AnPiPulse, false, CRGB(0, 0, 0), crgbColor4, CRGB(0, 0, 0), CRGB(0, 0, 0), strip_group.pstrOVERHEAD.fe(0), strip_group.pstrOVERHEAD.fs(0), false, true);
  teEvent[strip_group.pstrOVERHEAD.intCHANNEL].set("Channel Light Pulse Color", tmeCurrentTime, intTm + intDelay, intDurG, intSp, AnEvSweep, AnPiPulse, false, CRGB(0, 0, 0), crgbColor, CRGB(0, 0, 0), CRGB(0, 0, 0), strip_group.pstrOVERHEAD.fe(0), strip_group.pstrOVERHEAD.fs(0), false, true);
  // Glitch
  teEvent[strip_group.pstrOVERHEAD.intCHANNEL].set("Channel Light Pulse Color", tmeCurrentTime, intTm - 20 + intDelay, 50, intSp, AnEvSweep, AnPiPulse, false, CRGB(0, 0, 0), CRGB(96, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), strip_group.pstrOVERHEAD.fe(0), strip_group.pstrOVERHEAD.fs(0), false, true);
  teEvent[strip_group.pstrOVERHEAD.intCHANNEL].set("Channel Light Pulse Color", tmeCurrentTime, intTm - 40 + intDelay, 50, intSp, AnEvSweep, AnPiPulse, false, CRGB(0, 0, 0), CRGB(0, 0, 96), CRGB(0, 0, 0), CRGB(0, 0, 0), strip_group.pstrOVERHEAD.fe(0), strip_group.pstrOVERHEAD.fs(0), false, true);
  teEvent[strip_group.pstrOVERHEAD.intCHANNEL].set("Channel Light Pulse Color", tmeCurrentTime, intTm + intDelay, intDurW/8, intSp/4, AnEvSweep, AnPiPulse, true, CRGB(0, 0, 0), crgbColor4, CRGB(0, 0, 0), CRGB(0, 0, 0), strip_group.pstrOVERHEAD.fe(0), strip_group.pstrOVERHEAD.fs(0), false, true);

  // Set the pulse to timed repeat
  teEvent[strip_group.pstrDOOR.intCHANNEL].set("Channel Light Pulse Color", tmeCurrentTime, 1500, 0, 0, AnEvSchedule, AnTaChannelPulseColor, false, crgbColor, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), 0, 0, false, true);  

  // for later
  //teEvent[strip_group.pstrDOOR.intCHANNEL].set("Channel Light Pulse Color", tmeCurrentTime, intTm + 50, intDurG, 0, AnEvSweep, AnPiTwinkle, false, CRGB(200, 0, 0), CRGB(0, 200, 0), CRGB(0, 0, 200), CRGB(8, 0, 3), strip_group.pstrDOOR.ft(0), strip_group.pstrDOOR.fb(0), false, true);
}

// ---- NEEDS CONSOLIDATION ----
void vdChannelLightPulseColorCountdown(Console &cons, profile_strip_group strip_group, timed_event teEvent[], unsigned long tmeCurrentTime, CRGB crgbColor)
// Turn Color Pulse on Full Channel. Strip Length Aware. 
// AnTaChannelPulseColor
{
  cons.printwait("Pulse Countdown Timer Color (CL: " + std::to_string(strip_group.pstrDOOR.intCHANNEL));
  int intTm;
  int intDurW;
  int intDurG;
  int intSp;
  int intDelayGlitchAnti;

  int intDelay;

  // Set the fadeout color 
  CRGB crgbColor4;
  crgbColor4.r = crgbColor.r + 128;
  crgbColor4.g = crgbColor.g + 128;
  crgbColor4.b = crgbColor.b + 128;

  // Clear and Pulse colors background to bright then param color, starting with the center.
  intTm = 100; intDurW = 500; intDurG = 1500; intSp = 30; 

  intDelay = intAnTmDly(intTm, 0, strip_group.pstrDOOR.intSIZE, intSp);
  intDelayGlitchAnti = intAnTmDly(intTm + intDelay, intDurW/8, strip_group.pstrOVERHEAD.intSIZE, intSp/4);

  // Door Color with White and Trail Color
  teEvent[strip_group.pstrDOOR.intCHANNEL].set("Channel Light Pulse Color", tmeCurrentTime, intTm, intDurW, intSp, AnEvSweep, AnPiPulse, false, CRGB(0, 0, 0), crgbColor4, CRGB(0, 0, 0), CRGB(0, 0, 0), strip_group.pstrDOOR.ft(0), strip_group.pstrDOOR.fb(0), false, true);
  teEvent[strip_group.pstrDOOR.intCHANNEL].set("Channel Light Pulse Color", tmeCurrentTime, intTm, intDurG, intSp, AnEvSweep, AnPiPulse, false, CRGB(0, 0, 0), crgbColor, CRGB(0, 0, 0), CRGB(0, 0, 0), strip_group.pstrDOOR.ft(0), strip_group.pstrDOOR.fb(0), false, true);
  // Glitch
  teEvent[strip_group.pstrDOOR.intCHANNEL].set("Channel Light Pulse Color", tmeCurrentTime, intTm - 20, 50, intSp, AnEvSweep, AnPiPulse, false, CRGB(0, 0, 0), CRGB(96, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), strip_group.pstrDOOR.ft(0), strip_group.pstrDOOR.fb(0), false, true);
  teEvent[strip_group.pstrDOOR.intCHANNEL].set("Channel Light Pulse Color", tmeCurrentTime, intTm - 40, 50, intSp, AnEvSweep, AnPiPulse, false, CRGB(0, 0, 0), CRGB(0, 0, 96), CRGB(0, 0, 0), CRGB(0, 0, 0), strip_group.pstrDOOR.ft(0), strip_group.pstrDOOR.fb(0), false, true);
  teEvent[strip_group.pstrDOOR.intCHANNEL].set("Channel Light Pulse Color", tmeCurrentTime, intDelayGlitchAnti, intDurW/8, intSp/4, AnEvSweep, AnPiPulse, true, CRGB(0, 0, 0), crgbColor4, CRGB(0, 0, 0), CRGB(0, 0, 0), strip_group.pstrDOOR.ft(0), strip_group.pstrDOOR.fb(0), false, true);

  // Overhead Color with White and Trail Color
  teEvent[strip_group.pstrOVERHEAD.intCHANNEL].set("Channel Light Pulse Color", tmeCurrentTime, intTm + intDelay, intDurW, intSp, AnEvSweep, AnPiPulse, false, CRGB(0, 0, 0), crgbColor4, CRGB(0, 0, 0), CRGB(0, 0, 0), strip_group.pstrOVERHEAD.fe(0), strip_group.pstrOVERHEAD.fs(0), false, true);
  teEvent[strip_group.pstrOVERHEAD.intCHANNEL].set("Channel Light Pulse Color", tmeCurrentTime, intTm + intDelay, intDurG, intSp, AnEvSweep, AnPiPulse, false, CRGB(0, 0, 0), crgbColor, CRGB(0, 0, 0), CRGB(0, 0, 0), strip_group.pstrOVERHEAD.fe(0), strip_group.pstrOVERHEAD.fs(0), false, true);
  // Glitch
  teEvent[strip_group.pstrOVERHEAD.intCHANNEL].set("Channel Light Pulse Color", tmeCurrentTime, intTm - 20 + intDelay, 50, intSp, AnEvSweep, AnPiPulse, false, CRGB(0, 0, 0), CRGB(96, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), strip_group.pstrOVERHEAD.fe(0), strip_group.pstrOVERHEAD.fs(0), false, true);
  teEvent[strip_group.pstrOVERHEAD.intCHANNEL].set("Channel Light Pulse Color", tmeCurrentTime, intTm - 40 + intDelay, 50, intSp, AnEvSweep, AnPiPulse, false, CRGB(0, 0, 0), CRGB(0, 0, 96), CRGB(0, 0, 0), CRGB(0, 0, 0), strip_group.pstrOVERHEAD.fe(0), strip_group.pstrOVERHEAD.fs(0), false, true);
  teEvent[strip_group.pstrOVERHEAD.intCHANNEL].set("Channel Light Pulse Color", tmeCurrentTime, intTm + intDelay, intDurW/8, intSp/4, AnEvSweep, AnPiPulse, true, CRGB(0, 0, 0), crgbColor4, CRGB(0, 0, 0), CRGB(0, 0, 0), strip_group.pstrOVERHEAD.fe(0), strip_group.pstrOVERHEAD.fs(0), false, true);

  // -------- Call Pulse Countdown Timer Again
  teEvent[strip_group.pstrDOOR.intCHANNEL].set("Channel Light Pulse Color", tmeCurrentTime, 1500, 0, 0, AnEvSchedule, AnTaChannelPulseColorCountdown, false, crgbColor, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), 0, 0, false, true);  
}

// -------------------------------------------------------------------------------------

void vdOverheadIllum(Console &cons, profile_strip_group strip_group, timed_event teEvent[], unsigned long tmeCurrentTime, CRGB crgbColor)
// An overhead light.  Called by the Overhead command from the console. 
{
  cons.printwait("Overhead Illumination Color (CL: " + std::to_string(strip_group.pstrDOOR.intCHANNEL));
  
  // Set the background color.
  teEvent[strip_group.pstrOVERHEAD.intCHANNEL].set("Overhead Illumination", tmeCurrentTime, 1000, 500, 30, AnEvSweep, AnPiFade, false, CRGB(0, 0, 0), crgbColor, CRGB(0, 0, 0), CRGB(0, 0, 0), strip_group.pstrOVERHEAD.fs(0), strip_group.pstrOVERHEAD.fe(0), false, false);
}

// -------------------------------------------------------------------------------------

void vdHazard(Console &cons, profile_strip_group strip_group, timed_event teEvent[], unsigned long tmeCurrentTime)
// Hazard Lights. Called by the Hazard command from the console. 
// Runs on entire channel. 
{
  cons.printwait("Hazard (CL: " + std::to_string(strip_group.pstrDOOR.intCHANNEL));
  
  /*
  // Position Mask
  if (strip_group.pstrOVERHEAD.position("Front"))
  {
    // Mask
    CRGB Color_M = CRGB(128,128,128); 
    teEvent[strip_group.pstrOVERHEAD.intCHANNEL].set("Hazard", tmeCurrentTime, 1000, 500, 30, AnEvSweep, AnPiFadeDith, true, CRGB(0, 0, 0), Color_M, CRGB(0, 0, 0), CRGB(0, 0, 0), strip_group.pstrOVERHEAD.fb(0), strip_group.pstrOVERHEAD.fb(20), false, false);
  }
  */

  // Pulse Red.
  teEvent[strip_group.pstrDOOR.intCHANNEL].set("Hazard", tmeCurrentTime, 100, 900, 0, AnEvSweep, AnPiPulse, false, CRGB(0, 0, 0), CRGB(128, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), strip_group.pstrDOOR.fs(0), strip_group.pstrDOOR.fe(0), false, true);
  teEvent[strip_group.pstrOVERHEAD.intCHANNEL].set("Hazard", tmeCurrentTime, 100, 900, 0, AnEvSweep, AnPiPulse, false, CRGB(0, 0, 0), CRGB(128, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), strip_group.pstrOVERHEAD.ft(0), strip_group.pstrOVERHEAD.fb(0), false, true);

  // Set the hazard to timed repeat
  teEvent[strip_group.pstrDOOR.intCHANNEL].set("Hazard", tmeCurrentTime, 1500, 0, 0, AnEvSchedule, AnTaHazard, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), 0, 0, false, true);  
}

// -------------------------------------------------------------------------------------

void vdPacificaishAnimationADVColor(Console &cons, profile_strip_group strip_group, timed_event teEvent[], unsigned long tmeCurrentTime, CRGB crgbColor)
// Blue Waves. Much more interesting than the old version of this.
{
  cons.printwait("Pacificaish Color (CL: " + std::to_string(strip_group.pstrOVERHEAD.intCHANNEL) + " ID:"+ " S:" + std::to_string(strip_group.pstrOVERHEAD.fs(0)) + " E:" + std::to_string(strip_group.pstrOVERHEAD.fe(0)) + ")");

  
  int R = (2 * crgbColor.r) / 3;
  int G = (2 * crgbColor.g) / 3;
  int B = (2 * crgbColor.b) / 3;
  
  // Color Definitions

  // Background
  CRGB Color_B = CRGB(R,G,B); 

  // Forground
  CRGB Color_1 = CRGB(R, G, B);
  CRGB Color_2 = CRGB(20+(2*R), 10+G, 15+(B/2));  
  CRGB Color_3 = CRGB(15+(R/2), 20+(2*G), 10+B);
  CRGB Color_4 = CRGB(10+R, 15+(G/2), 20+(2*B));

  // Shadow
  CRGB Color_S1 = CRGB(R, G, B);
  CRGB Color_S2 = CRGB(30+(2*R), 20+G, 25+(B/2));
  CRGB Color_S3 = CRGB(25+(R/2), 30+(2*G), 20+B);
  CRGB Color_S4 = CRGB(20+R, 25+(G/2), 30+(2*B));

  // Position Mask
  if (strip_group.pstrOVERHEAD.position("Front"))
  {
    // Mask
    CRGB Color_M = CRGB(128,128,128); 
    teEvent[strip_group.pstrOVERHEAD.intCHANNEL].set("Overhead Illumination", tmeCurrentTime, 1000, 500, 30, AnEvSweep, AnPiFadeDith, true, CRGB(0, 0, 0), Color_M, CRGB(0, 0, 0), CRGB(0, 0, 0), strip_group.pstrOVERHEAD.fb(0), strip_group.pstrOVERHEAD.fb(20), false, false);
  }

  // Set the background color.
  teEvent[strip_group.pstrOVERHEAD.intCHANNEL].set("Overhead Illumination", tmeCurrentTime, 1000, 500, 30, AnEvSweep, AnPiFade, false, CRGB(0, 0, 0), Color_B, CRGB(0, 0, 0), CRGB(0, 0, 0), strip_group.pstrOVERHEAD.ft(0), strip_group.pstrOVERHEAD.fb(0), false, false);

  // The waves.
  teEvent[strip_group.pstrOVERHEAD.intCHANNEL].set("Overhead Illumination", tmeCurrentTime, intRandomHD(2000), intRandomHD(3500), intRandomHD(125), AnEvSweep, AnPiPulse, false, CRGB(0, 0, 0), Color_1, CRGB(0, 0, 0), CRGB(0, 0, 0), strip_group.pstrOVERHEAD.fe(0), strip_group.pstrOVERHEAD.fs(0), true, true);
  teEvent[strip_group.pstrOVERHEAD.intCHANNEL].set("Overhead Illumination", tmeCurrentTime, intRandomHD(2000), intRandomHD(1500), intRandomHD(75), AnEvSweep, AnPiPulse, false, CRGB(0, 0, 0), Color_2, CRGB(0, 0, 0), CRGB(0, 0, 0), strip_group.pstrOVERHEAD.fe(0), strip_group.pstrOVERHEAD.fs(0), true, true);
  teEvent[strip_group.pstrOVERHEAD.intCHANNEL].set("Overhead Illumination", tmeCurrentTime, intRandomHD(2000), intRandomHD(3600), intRandomHD(135), AnEvSweep, AnPiPulse, false, CRGB(0, 0, 0), Color_3, CRGB(0, 0, 0), CRGB(0, 0, 0), strip_group.pstrOVERHEAD.fe(0), strip_group.pstrOVERHEAD.fs(0), true, true);
  teEvent[strip_group.pstrOVERHEAD.intCHANNEL].set("Overhead Illumination", tmeCurrentTime, intRandomHD(2000), intRandomHD(3200), intRandomHD(100), AnEvSweep, AnPiPulse, false, CRGB(0, 0, 0), Color_4, CRGB(0, 0, 0), CRGB(0, 0, 0), strip_group.pstrOVERHEAD.fe(0), strip_group.pstrOVERHEAD.fs(0), true, true);

  teEvent[strip_group.pstrOVERHEAD.intCHANNEL].set("Overhead Illumination", tmeCurrentTime, intRandomHD(2000), intRandomHD(3500), intRandomHD(125), AnEvSweep, AnPiPulse, false, CRGB(0, 0, 0), Color_1, CRGB(0, 0, 0), CRGB(0, 0, 0), strip_group.pstrOVERHEAD.fe(0), strip_group.pstrOVERHEAD.fs(0), true, true);
  teEvent[strip_group.pstrOVERHEAD.intCHANNEL].set("Overhead Illumination", tmeCurrentTime, intRandomHD(2000), intRandomHD(1500), intRandomHD(75), AnEvSweep, AnPiPulse, false, CRGB(0, 0, 0), Color_2, CRGB(0, 0, 0), CRGB(0, 0, 0), strip_group.pstrOVERHEAD.fe(0), strip_group.pstrOVERHEAD.fs(0), true, true);
  teEvent[strip_group.pstrOVERHEAD.intCHANNEL].set("Overhead Illumination", tmeCurrentTime, intRandomHD(2000), intRandomHD(3600), intRandomHD(135), AnEvSweep, AnPiPulse, false, CRGB(0, 0, 0), Color_3, CRGB(0, 0, 0), CRGB(0, 0, 0), strip_group.pstrOVERHEAD.fe(0), strip_group.pstrOVERHEAD.fs(0), true, true);
  teEvent[strip_group.pstrOVERHEAD.intCHANNEL].set("Overhead Illumination", tmeCurrentTime, intRandomHD(2000), intRandomHD(3200), intRandomHD(100), AnEvSweep, AnPiPulse, false, CRGB(0, 0, 0), Color_4, CRGB(0, 0, 0), CRGB(0, 0, 0), strip_group.pstrOVERHEAD.fe(0), strip_group.pstrOVERHEAD.fs(0), true, true);

  // Counter waves.
  teEvent[strip_group.pstrOVERHEAD.intCHANNEL].set("Overhead Illumination", tmeCurrentTime, intRandomHD(2000), intRandomHD(3500), intRandomHD(125), AnEvSweep, AnPiPulse, true, CRGB(0, 0, 0), Color_S1, CRGB(0, 0, 0), CRGB(0, 0, 0), strip_group.pstrOVERHEAD.fe(0), strip_group.pstrOVERHEAD.fs(0), true, true);
  teEvent[strip_group.pstrOVERHEAD.intCHANNEL].set("Overhead Illumination", tmeCurrentTime, intRandomHD(2000), intRandomHD(1500), intRandomHD(75), AnEvSweep, AnPiPulse, true, CRGB(0, 0, 0), Color_S2, CRGB(0, 0, 0), CRGB(0, 0, 0), strip_group.pstrOVERHEAD.fe(0), strip_group.pstrOVERHEAD.fs(0), true, true);
  teEvent[strip_group.pstrOVERHEAD.intCHANNEL].set("Overhead Illumination", tmeCurrentTime, intRandomHD(2000), intRandomHD(3600), intRandomHD(135), AnEvSweep, AnPiPulse, true, CRGB(0, 0, 0), Color_S3, CRGB(0, 0, 0), CRGB(0, 0, 0), strip_group.pstrOVERHEAD.fe(0), strip_group.pstrOVERHEAD.fs(0), true, true);
  teEvent[strip_group.pstrOVERHEAD.intCHANNEL].set("Overhead Illumination", tmeCurrentTime, intRandomHD(2000), intRandomHD(3200), intRandomHD(100), AnEvSweep, AnPiPulse, true, CRGB(0, 0, 0), Color_S4, CRGB(0, 0, 0), CRGB(0, 0, 0), strip_group.pstrOVERHEAD.fe(0), strip_group.pstrOVERHEAD.fs(0), true, true);
}



// -------------------------------------------------------------------------------------
// Advanced Animations
// -------------------------------------------------------------------------------------

/*
void vdEndAllAnimationsADV(Console &cons, led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// Run this routine on all Doors after all doors are closed to ensure no lingering animations have not been ended for whatever reason.
{
  // Shouldn't ever need to call this. 
  cons.printwait("vdEndAllAnimationsADV (CL: " + std::to_string(lsStrips[intStripID].Cl) + " ID:"+ std::to_string(intStripID) + " S:" + std::to_string(lsStrips[intStripID].St) + " E:" + std::to_string(lsStrips[intStripID].Ed) + ")");
  teEvent[lsStrips[intStripID].Cl].set("", tmeCurrentTime, 20000, 1000, 80, AnEvSetToEnd, 0, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID + 1].Ed, true, true);
}
*/


void vdDoorOpenAnimationADV00(Console &cons, profile_strip strip, timed_event teEvent[], unsigned long tmeCurrentTime)
// Prepare red backgrounds and puddle lights for the caution lights, and start shimmer effect.
{
  cons.printwait("Door Open Safety (CL: " + std::to_string(strip.intCHANNEL) + " ID:"+ /*std::to_string(intStripID) + " S:" + std::to_string(lsStrips[intStripID].St) + " E:" + std::to_string(lsStrips[intStripID].Ed) +*/ ")");
  int intTm;
  int intDur;
  int intCt;
  int intSp;

  // Give strip a fresh start.
  // Clear any animations that may be running and this should replace.
  teEvent[strip.intCHANNEL].set("Door Close Anim", tmeCurrentTime, 200, 999, 80, AnEvSetToEnd, 0, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fs(0), strip.fe(0), true, true);
  teEvent[strip.intCHANNEL].set("Door Close Active Anim", tmeCurrentTime, 200, 999, 80, AnEvSetToEnd, 0, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fs(0), strip.fe(0), true, true);

  CRGB lead = CRGB(20, 20, 20);
  CRGB shadow = CRGB(50 ,50, 50);

  // Door Open Animation
  intTm = 100; intDur = 500; intSp = 10; intCt = strip.intSIZE;

  // Clear set background to door open colors.
  teEvent[strip.intCHANNEL].set("vdOpenDoor", tmeCurrentTime, intTm, intDur, intSp, AnEvSweep, AnPiFadeDith, false, CRGB(0, 0, 0), CRGB(255, 255, 255), CRGB(0, 0, 0), CRGB(255, 64, 64), strip.fs(0), strip.fs(4), false, false);
  teEvent[strip.intCHANNEL].set("vdOpenDoor", tmeCurrentTime, intTm, intDur, intSp, AnEvSweep, AnPiFadeDith, false, CRGB(0, 0, 0), CRGB(255, 64, 64), CRGB(0, 0, 0), CRGB(25, 0, 0), strip.fs(5), strip.fs(10), false, false);
  teEvent[strip.intCHANNEL].set("vdOpenDoor", tmeCurrentTime, intTm + 500, intDur, intSp, AnEvSweep, AnPiFadeDith, false, CRGB(0, 0, 0), CRGB(25, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fs(11), strip.fe(0), false, false);

  // Shimmer
  teEvent[strip.intCHANNEL].set("vdOpenDoor", tmeCurrentTime, intTm, 10000, 500, AnEvSweep, AnPiPulse, false, CRGB(0, 0, 0), CRGB(15, 20, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fs(0), strip.fe(0), true, false);
  teEvent[strip.intCHANNEL].set("vdOpenDoor", tmeCurrentTime, intTm, 6000, 280, AnEvSweep, AnPiPulse, false, CRGB(0, 0, 0), CRGB(15, 20, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fs(0), strip.fe(0), true, false);

  intTm = intAnTmDly(intTm, intDur, intCt, intSp);
  
  // Reverse Shadow Blink
  teEvent[strip.intCHANNEL].set("vdOpenDoor", tmeCurrentTime, intTm + intDur, intDur, intSp, AnEvSweep, AnPiPulse, true, CRGB(0, 0, 0), shadow, CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fe(0), strip.fs(0), true, true);

  // Caution Door Open Flash
  intDur = 50; intSp = 1; intCt = strip.intSIZE;
  teEvent[strip.intCHANNEL].set("vdOpenDoor", tmeCurrentTime, intTm, 50, intSp, AnEvSweep, AnPiPulse, false, lead, lead, CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fe(0), strip.fs(0), false, true);
  teEvent[strip.intCHANNEL].set("vdOpenDoor", tmeCurrentTime, intTm, intDur, intSp, AnEvSweep, AnPiPulse, false, CRGB(80, 80, 0), CRGB(80, 80, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fe(0), strip.fs(0), false, true);
  
  intTm = intAnTmDly(intTm, intDur, intCt, intSp);

  intDur = 100; intSp = 2; intCt = strip.intSIZE;
  teEvent[strip.intCHANNEL].set("vdOpenDoor", tmeCurrentTime, intTm, 50, intSp, AnEvSweep, AnPiPulse, false, lead, lead, CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fe(0), strip.fs(0), false, true);
  teEvent[strip.intCHANNEL].set("vdOpenDoor", tmeCurrentTime, intTm, intDur, intSp, AnEvSweep, AnPiPulse, false, CRGB(80, 80, 0), CRGB(80, 80, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fe(0), strip.fs(0), false, true);
  
  intTm = intAnTmDly(intTm, intDur, intCt, intSp);

  intDur = 200; intSp = 4; intCt = strip.intSIZE;
  teEvent[strip.intCHANNEL].set("vdOpenDoor", tmeCurrentTime, intTm, 50, intSp, AnEvSweep, AnPiPulse, false, lead, lead, CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fe(0), strip.fs(0), false, true);
  teEvent[strip.intCHANNEL].set("vdOpenDoor", tmeCurrentTime, intTm, intDur, intSp, AnEvSweep, AnPiPulse, false, CRGB(80, 80, 0), CRGB(80, 80, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fe(0), strip.fs(0), false, true);
  
  intTm = intAnTmDly(intTm, intDur, intCt, intSp);

  intDur = 400; intSp = 8; intCt = strip.intSIZE;
  teEvent[strip.intCHANNEL].set("vdOpenDoor", tmeCurrentTime, intTm, 50, intSp, AnEvSweep, AnPiPulse, false, lead, lead, CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fe(0), strip.fs(0), false, true);
  teEvent[strip.intCHANNEL].set("vdOpenDoor", tmeCurrentTime, intTm, intDur, intSp, AnEvSweep, AnPiPulse, false, CRGB(80, 80, 0), CRGB(80, 80, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fe(0), strip.fs(0), false, true);
  
  intTm = intAnTmDly(intTm, intDur, intCt, intSp);

  intDur = 800; intSp = 16; intCt = strip.intSIZE;
  teEvent[strip.intCHANNEL].set("vdOpenDoor", tmeCurrentTime, intTm, 100, intSp, AnEvSweep, AnPiPulse, false, lead, lead, CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fe(0), strip.fs(0), false, true);
  teEvent[strip.intCHANNEL].set("vdOpenDoor", tmeCurrentTime, intTm, intDur, intSp, AnEvSweep, AnPiPulse, false, CRGB(128, 128, 0), CRGB(128, 128, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fe(0), strip.fs(0), false, true);
  
  // Repeat Red Pulse
  intDur = 1500; intSp = 125; intCt = strip.intSIZE;
  int intMid = strip.intSIZE / 2;
  int intTm2Off = (intMid * intSp + intDur) /2;
  
  // Pulse Yellow up to mid
  teEvent[strip.intCHANNEL].set("vdOpenDoor", tmeCurrentTime, intTm, intDur, intSp, AnEvSweep, AnPiPulse, false, CRGB(128, 128, 0), CRGB(128, 128, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fs(0), strip.fe(intMid), true, true);
  teEvent[strip.intCHANNEL].set("vdOpenDoor", tmeCurrentTime, intTm + intTm2Off, intDur, intSp, AnEvSweep, AnPiPulse, false, CRGB(128, 128, 0), CRGB(128, 128, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fs(0), strip.fe(intMid), true, true);

  // Pulse Yellow down to mid
  teEvent[strip.intCHANNEL].set("vdOpenDoor", tmeCurrentTime, intTm, intDur, intSp, AnEvSweep, AnPiPulse, false, CRGB(128, 128, 0), CRGB(128, 128, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fe(0), strip.fs(intMid), true, true);
  teEvent[strip.intCHANNEL].set("vdOpenDoor", tmeCurrentTime, intTm + intTm2Off, intDur, intSp, AnEvSweep, AnPiPulse, false, CRGB(128, 128, 0), CRGB(128, 128, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fe(0), strip.fs(intMid), true, true);
}


void vdDoorCloseRunningADV(Console &cons, profile_strip strip, timed_event teEvent[], unsigned long tmeCurrentTime)
// Effect to run on doors when all doors are closed. Animation will start then end, leaving lights in final state without proceessing anything else.
{
  cons.printwait("Running Side Lights (CL: " + std::to_string(strip.intCHANNEL) + " S:" + " E:" + std::to_string(strip.fe(0)) + ")");

  // Give strip a fresh start.
  // Clear any animations that may be running and this should replace.
  teEvent[strip.intCHANNEL].set("Door Close Active Anim", tmeCurrentTime, 200, 999, 80, AnEvSetToEnd, 0, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fs(0), strip.fe(0), true, true);
  teEvent[strip.intCHANNEL].set("vdOpenDoor", tmeCurrentTime, 200, 999, 80, AnEvSetToEnd, 0, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fs(0), strip.fe(0), true, true);

  int intTm;
  int intDur;
  int intCt;
  int intSp;

  CRGB running_light = CRGB(25, 5, 0);

  intTm = 600; intDur = 5000; intSp = 50; intCt = strip.intSIZE;

  // Clear set background colors.
  //  What? Running with Blue LEDs are illegal in my state? Grrr.
  //teEvent[strip.intCHANNEL].set("Door Close Anim", tmeCurrentTime, intTm, intDur, intSp, AnEvSweep, AnPiFadeDith, false, CRGB(0, 0, 0), CRGB(0, 0, 32), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, strip.fe(0), false, false);
  
  // Side lights like big trucks should be ok.
  teEvent[strip.intCHANNEL].set("Door Close Running Lights", tmeCurrentTime, intTm, intDur, intSp, AnEvSweep, AnPiFadeDith, false, CRGB(0, 0, 0), running_light, CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fs(0), strip.fs(12), false, false);

  // Tell this animation to stop running on itsself after all prev animations should be done.
  // Basicly, put itself to sleep.
  teEvent[strip.intCHANNEL].set("Door Close Anim", tmeCurrentTime, 29000, 5000, 0, AnEvSetToEnd, 0, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fs(0), strip.fe(0), true, true);
  teEvent[strip.intCHANNEL].set("Door Close Running Lights", tmeCurrentTime, 29000, 5000, 0, AnEvSetToEnd, 0, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fs(0), strip.fe(0), true, true);
  
  // Same as above
  teEvent[strip.intCHANNEL].set("Door Close Running Lights (non continue)", tmeCurrentTime, 30000, 15000, 0, AnEvSweep, AnPiFadeDith, false, CRGB(0, 0, 0), running_light, CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fs(0), strip.fs(12), false, true);
}


void vdDoorCloseActiveADV00(Console &cons, profile_strip strip, timed_event teEvent[], unsigned long tmeCurrentTime)
// Effect to run on doors when all closed doors at least one other door is open.
{
  cons.printwait("Door Close Safety (CL: " + std::to_string(strip.intCHANNEL) + " ID:" + " S:" + std::to_string(strip.fs(0)) + " E:" + std::to_string(strip.fe(0)) + ")");

  // Give strip a fresh start.
  // Clear any animations that may be running and this should replace.
  teEvent[strip.intCHANNEL].set("Door Close Anim", tmeCurrentTime, 200, 999, 80, AnEvSetToEnd, 0, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0),strip.fs(0), strip.fe(0), true, true);
  teEvent[strip.intCHANNEL].set("vdOpenDoor", tmeCurrentTime, 200, 999, 80, AnEvSetToEnd, 0, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fs(0), strip.fe(0), true, true);

  int intTm;
  int intDur;
  int intSp;

  CRGB lead = CRGB(20, 20, 20);

  // Door Open Animation
  intTm = 100; intDur = 5000; intSp = 5;

  // Clear set background to door open colors.
  teEvent[strip.intCHANNEL].set("Door Close Active Anim", tmeCurrentTime, intTm, intDur, intSp, AnEvSweep, AnPiFadeDith, false, CRGB(0, 0, 0), CRGB(40, 8, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fs(0), strip.fe(0), false, false);

  // Pulse to white (accumulation of prev color and this color = CRGP(70, 70, 70) then back to original color.
  teEvent[strip.intCHANNEL].set("Door Close Active Anim", tmeCurrentTime, intTm, intDur, intSp, AnEvSweep, AnPiPulse, false,  CRGB(0, 0, 0), CRGB(30, 62, 70) , CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fs(0), strip.fe(0), true, false);
}


void vdPacificaishAnimationADV(Console &cons, profile_strip strip, timed_event teEvent[], unsigned long tmeCurrentTime)
// Blue Waves. Much more interesting than the old version of this.
{
  cons.printwait("Pacificaish (CL: " + std::to_string(strip.intCHANNEL) + " ID:"+ " S:" + std::to_string(strip.fs(0)) + " E:" + std::to_string(strip.fe(0)) + ")");

  // Give strip a fresh start.
  // Clear any animations that may be running and this should replace.
  teEvent[strip.intCHANNEL].set("Overhead Close Convenience Anim", tmeCurrentTime, 200, 999, 80, AnEvSetToEnd, 0, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fs(0), strip.fe(0), true, true);
  
  // Position Mask
  if (strip.position("Front"))
  {
    // Mask
    CRGB Color_M = CRGB(128,128,128); 
    teEvent[strip.intCHANNEL].set("Overhead Open Anim", tmeCurrentTime, 1000, 500, 30, AnEvSweep, AnPiFadeDith, true, CRGB(0, 0, 0), Color_M, CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fb(0), strip.fb(20), false, false);
  }

  // Set the background color.
  teEvent[strip.intCHANNEL].set("Overhead Open Anim", tmeCurrentTime, 1000, 500, 30, AnEvSweep, AnPiFade, false, CRGB(0, 0, 0), CRGB(0, 0, 60), CRGB(0, 0, 0), CRGB(0, 0, 0), strip.ft(0), strip.fb(0), false, false);

  // The waves.
  teEvent[strip.intCHANNEL].set("Overhead Open Anim", tmeCurrentTime, intRandomHD(2000), intRandomHD(3500), intRandomHD(125), AnEvSweep, AnPiPulse, false, CRGB(0, 0, 0), CRGB(20, 100, 80), CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fe(0), strip.fs(0), true, true);
  teEvent[strip.intCHANNEL].set("Overhead Open Anim", tmeCurrentTime, intRandomHD(2000), intRandomHD(1500), intRandomHD(75), AnEvSweep, AnPiPulse, false, CRGB(0, 0, 0), CRGB(40, 50, 40), CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fe(0), strip.fs(0), true, true);
  teEvent[strip.intCHANNEL].set("Overhead Open Anim", tmeCurrentTime, intRandomHD(2000), intRandomHD(3600), intRandomHD(135), AnEvSweep, AnPiPulse, false, CRGB(0, 0, 0), CRGB(10, 30, 90), CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fe(0), strip.fs(0), true, true);
  teEvent[strip.intCHANNEL].set("Overhead Open Anim", tmeCurrentTime, intRandomHD(2000), intRandomHD(3200), intRandomHD(100), AnEvSweep, AnPiPulse, false, CRGB(0, 0, 0), CRGB(30, 40, 70), CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fe(0), strip.fs(0), true, true);

  teEvent[strip.intCHANNEL].set("Overhead Open Anim", tmeCurrentTime, intRandomHD(2000), intRandomHD(3500), intRandomHD(125), AnEvSweep, AnPiPulse, false, CRGB(0, 0, 0), CRGB(20, 100, 80), CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fe(0), strip.fs(0), true, true);
  teEvent[strip.intCHANNEL].set("Overhead Open Anim", tmeCurrentTime, intRandomHD(2000), intRandomHD(1500), intRandomHD(75), AnEvSweep, AnPiPulse, false, CRGB(0, 0, 0), CRGB(40, 50, 40), CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fe(0), strip.fs(0), true, true);
  teEvent[strip.intCHANNEL].set("Overhead Open Anim", tmeCurrentTime, intRandomHD(2000), intRandomHD(3600), intRandomHD(135), AnEvSweep, AnPiPulse, false, CRGB(0, 0, 0), CRGB(10, 30, 90), CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fe(0), strip.fs(0), true, true);
  teEvent[strip.intCHANNEL].set("Overhead Open Anim", tmeCurrentTime, intRandomHD(2000), intRandomHD(3200), intRandomHD(100), AnEvSweep, AnPiPulse, false, CRGB(0, 0, 0), CRGB(30, 40, 70), CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fe(0), strip.fs(0), true, true);

  // Counter waves.
  teEvent[strip.intCHANNEL].set("Overhead Open Anim", tmeCurrentTime, intRandomHD(2000), intRandomHD(3500), intRandomHD(125), AnEvSweep, AnPiPulse, true, CRGB(0, 0, 0), CRGB(40, 100, 80), CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fe(0), strip.fs(0), true, true);
  teEvent[strip.intCHANNEL].set("Overhead Open Anim", tmeCurrentTime, intRandomHD(2000), intRandomHD(1500), intRandomHD(75), AnEvSweep, AnPiPulse, true, CRGB(0, 0, 0), CRGB(50, 50, 40), CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fe(0), strip.fs(0), true, true);
  teEvent[strip.intCHANNEL].set("Overhead Open Anim", tmeCurrentTime, intRandomHD(2000), intRandomHD(3600), intRandomHD(135), AnEvSweep, AnPiPulse, true, CRGB(0, 0, 0), CRGB(20, 30, 90), CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fe(0), strip.fs(0), true, true);
  teEvent[strip.intCHANNEL].set("Overhead Open Anim", tmeCurrentTime, intRandomHD(2000), intRandomHD(3200), intRandomHD(100), AnEvSweep, AnPiPulse, true, CRGB(0, 0, 0), CRGB(40, 40, 70), CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fe(0), strip.fs(0), true, true);
}


void vdCloseOverADV(Console &cons, profile_strip strip, timed_event teEvent[], unsigned long tmeCurrentTime)
// Overhead Lights Off
{
  cons.printwait("Overhead Lights Off (CL: " + std::to_string(strip.intCHANNEL) + " ID:"+ " S:" + std::to_string(strip.fs(0)) + " E:" + std::to_string(strip.fe(0)) + ")");

  // Just set all the current over head lights to fade away.
  teEvent[strip.intCHANNEL].set("Overhead Open Anim", tmeCurrentTime, 0, 1000, 80, AnEvSetToEnd, 0, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fs(0), strip.fe(0), true, true);
}

void vdCoADV(Console &cons, profile_strip strip, timed_event teEvent[], unsigned long tmeCurrentTime)
// Conviencance Lights On then Off.
{
  cons.printwait("Conviencance Lights (CL: " + std::to_string(strip.intCHANNEL) + " ID:"+ " S:" + std::to_string(strip.fs(0)) + " E:" + std::to_string(strip.fe(0)) + ")");
  int intTm;
  int intDur;
  int intSp;

  int bgonedly;

  // Background Color Fade out.

  // Set the background color.
  CRGB background = CRGB(40, 8, 0);
  CRGB backgroundbgone = CRGB(20, 4, 0);
  
  intTm = 500; intDur = 3000; intSp = 250;

  // Clear any animations that may be running and this should replace.
  teEvent[strip.intCHANNEL].set("Overhead Open Anim", tmeCurrentTime, 200, 999, 80, AnEvSetToEnd, 0, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fs(0), strip.fe(0), true, true);

  // Position Mask
  if (strip.position("Front"))
  {
    // Mask
    CRGB Color_M = CRGB(128,128,128); 
    teEvent[strip.intCHANNEL].set("Overhead Close Convenience Anim", tmeCurrentTime, 1000, 500, 30, AnEvSweep, AnPiFadeDith, true, CRGB(0, 0, 0), Color_M, CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fb(0), strip.fb(20), false, false);
  }

  //Set All the animations to end after the code 4 lines down, is finished fading away  
  bgonedly = (strip.intSIZE * intSp + intDur);
  teEvent[strip.intCHANNEL].set("Overhead Close Convenience Anim", tmeCurrentTime, bgonedly, 1000, 80, AnEvSetToEnd, 0, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fs(0), strip.fe(0), true, true);

  // Fading away by writing a color as background, then slowly sweeping in the same color in reverse color, to make it disappear slowly. 
  teEvent[strip.intCHANNEL].set("Overhead Close Convenience Anim", tmeCurrentTime, 500, 500, 0, AnEvSweep, AnPiFade, false,  CRGB(0, 0, 0), background, CRGB(0, 0, 0), CRGB(0, 0, 0), strip.ft(0), strip.fb(0), false, false);
  teEvent[strip.intCHANNEL].set("Overhead Close Convenience Anim", tmeCurrentTime, intTm, intDur, intSp, AnEvSweep, AnPiFade, true,  CRGB(0, 0, 0), background, CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fb(0), strip.ft(0), false, false);

  // The Pulses.  Timed according to their own speed.
  intTm = 500; intSp = 30;
  intDur = intSp * 6;

  bgonedly = (strip.intSIZE * intSp + intDur) /3;
  teEvent[strip.intCHANNEL].set("Overhead Close Convenience Anim", tmeCurrentTime, intTm + (0 * bgonedly), intDur, intSp, AnEvSweep, AnPiPulse, false,  CRGB(0, 0, 0), backgroundbgone, CRGB(0, 0, 0), CRGB(0, 0, 0), strip.ft(0), strip.fb(0), true, false);
  teEvent[strip.intCHANNEL].set("Overhead Close Convenience Anim", tmeCurrentTime, intTm + (1 * bgonedly), intDur, intSp, AnEvSweep, AnPiPulse, false,  CRGB(0, 0, 0), backgroundbgone, CRGB(0, 0, 0), CRGB(0, 0, 0), strip.ft(0), strip.fb(0), true, false);
  teEvent[strip.intCHANNEL].set("Overhead Close Convenience Anim", tmeCurrentTime, intTm + (2 * bgonedly), intDur, intSp, AnEvSweep, AnPiPulse, false,  CRGB(0, 0, 0), backgroundbgone, CRGB(0, 0, 0), CRGB(0, 0, 0), strip.ft(0), strip.fb(0), true, false);
  
  // teEvent[strip.intCHANNEL].set("Overhead Close Convenience Anim", tmeCurrentTime, AUXDRLINGERBCK - 6000, 9000, 0, AnEvSetToEnd, 0, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fs(0), strip.fe(0), true, false);
  // !!! Need to get AUXDRLINGERBACK back into the code.
}

void vdCoADV01(Console &cons, profile_strip strip, timed_event teEvent[], unsigned long tmeCurrentTime)
// Conviencance Lights On then Off.
{
  cons.printwait("Conviencance Lights (CL: " + std::to_string(strip.intCHANNEL) + " ID:"+ " S:" + std::to_string(strip.fs(0)) + " E:" + std::to_string(strip.fe(0)) + ")");

  // Clear any animations that may be running and this should replace.
  teEvent[strip.intCHANNEL].set("Overhead Open Anim", tmeCurrentTime, 200, 999, 80, AnEvSetToEnd, 0, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fs(0), strip.fe(0), true, true);

  // Position Mask
  if (strip.position("Front"))
  {
    // Mask
    CRGB Color_M = CRGB(128,128,128); 
    teEvent[strip.intCHANNEL].set("Overhead Close Convenience Anim", tmeCurrentTime, 1000, 500, 30, AnEvSweep, AnPiFadeDith, true, CRGB(0, 0, 0), Color_M, CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fb(0), strip.fb(20), false, false);
  }

  //-------------------------
  //Set All the animations to end after the code 4 lines down, is finished fading away  
  int bgonedly = 20000;
  teEvent[strip.intCHANNEL].set("Overhead Close Convenience Anim", tmeCurrentTime, bgonedly, 1000, 80, AnEvSetToEnd, 0, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fs(0), strip.fe(0), true, true);

  //-------------------------=
  int intTm, intDur, intSp, intCt;
  int intDelay = 0; 

  CRGB crgbPulseColor = CRGB(128, 128, 0);
  CRGB crgbOrange     = CRGB(40, 8, 0);
  CRGB crgbRed        = CRGB(0, 96, 96);
  CRGB crgbGreen      = CRGB(96, 0, 96);
  CRGB crgbBlue       = CRGB(96, 96, 0);
  CRGB crgbCounterColor  = CRGB(128, 128, 128);

  int counterdur = 50;
  int countersp  = 20;

  int intSpAntiPuls = 15; 
  int intDurAnti = 150;

  // Repeat Pulse
  intTm = 50; intDur = 500; intSp = 0; intCt = strip.intSIZE;
  int intMid = strip.intSIZE / 2;
  int intTm2Off = (intMid * intSp + intDur) /2;
  //int IntTrlDly = intDur*2/3;

  // Glitch Yellow Fade Away
  intTm = intAnTmDly(intTm, intDur, strip.intSIZE, intSp);
  intDur = 500; intSp = 0;

  teEvent[strip.intCHANNEL].set("Overhead Close Convenience Anim", tmeCurrentTime, intTm, intDurAnti, intSpAntiPuls, AnEvSweep, AnPiPulse, true, CRGB(0, 0, 0), crgbRed, CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fs(0), strip.fe(0), false, true);
  teEvent[strip.intCHANNEL].set("Overhead Close Convenience Anim", tmeCurrentTime, intTm, counterdur, countersp, AnEvSweep, AnPiPulse, true, CRGB(0, 0, 0), crgbCounterColor, CRGB(0, 0, 0), CRGB(0, 0, 0), strip.ft(0), strip.fb(0), false, true);

  intTm = intAnTmDly(intTm, intDur, strip.intSIZE, intSp);
  intDur = 500; intSp = 0;

  teEvent[strip.intCHANNEL].set("Overhead Close Convenience Anim", tmeCurrentTime, intTm, intDurAnti, intSpAntiPuls, AnEvSweep, AnPiPulse, true, CRGB(0, 0, 0), crgbGreen, CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fs(0), strip.fe(0), false, true);
  teEvent[strip.intCHANNEL].set("Overhead Close Convenience Anim", tmeCurrentTime, intTm, counterdur, countersp, AnEvSweep, AnPiPulse, true, CRGB(0, 0, 0), crgbCounterColor, CRGB(0, 0, 0), CRGB(0, 0, 0), strip.ft(0), strip.fb(0), false, true);

  intTm = intAnTmDly(intTm, intDur, strip.intSIZE, intSp);
  intDur = 500; intSp = 0;

  teEvent[strip.intCHANNEL].set("Overhead Close Convenience Anim", tmeCurrentTime, intTm, intDurAnti, intSpAntiPuls, AnEvSweep, AnPiPulse, true, CRGB(0, 0, 0), crgbBlue, CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fs(0), strip.fe(0), false, true);
  teEvent[strip.intCHANNEL].set("Overhead Close Convenience Anim", tmeCurrentTime, intTm, counterdur, countersp, AnEvSweep, AnPiPulse, true, CRGB(0, 0, 0), crgbCounterColor, CRGB(0, 0, 0), CRGB(0, 0, 0), strip.ft(0), strip.fb(0), false, true);

  intDur = 4000; intSp = 0;
  teEvent[strip.intCHANNEL].set("Overhead Close Convenience Anim", tmeCurrentTime, intTm, intDur, intSp, AnEvSweep, AnPiPulse, false, CRGB(0, 0, 0), crgbPulseColor, CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fs(0), strip.fe(0), false, true);
  teEvent[strip.intCHANNEL].set("Overhead Close Convenience Anim", tmeCurrentTime, intTm, counterdur, countersp, AnEvSweep, AnPiPulse, true, CRGB(0, 0, 0), crgbCounterColor, CRGB(0, 0, 0), CRGB(0, 0, 0), strip.ft(0), strip.fb(0), false, true);
  
  //intTm = intAnTmDly(intTm, intDur, strip.intSIZE, intSp);
  intDur = 17000; intSp = 0;
  teEvent[strip.intCHANNEL].set("Overhead Close Convenience Anim", tmeCurrentTime, intTm, intDur, intSp + 1, AnEvSweep, AnPiPulse, false, CRGB(0, 0, 0), crgbOrange, CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fs(0), strip.fe(0), false, true);
  teEvent[strip.intCHANNEL].set("Overhead Close Convenience Anim", tmeCurrentTime, intTm, counterdur, countersp, AnEvSweep, AnPiPulse, true, CRGB(0, 0, 0), crgbCounterColor, CRGB(0, 0, 0), CRGB(0, 0, 0), strip.ft(0), strip.fb(0), true, true);
  teEvent[strip.intCHANNEL].set("Overhead Close Convenience Anim", tmeCurrentTime, intTm - 20, counterdur, countersp, AnEvSweep, AnPiPulse, false, CRGB(0, 0, 0), CRGB(0, 20, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), strip.ft(0), strip.fb(0), true, true);
  teEvent[strip.intCHANNEL].set("Overhead Close Convenience Anim", tmeCurrentTime, intTm - 40, counterdur, countersp, AnEvSweep, AnPiPulse, false, CRGB(0, 0, 0), CRGB(20, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), strip.ft(0), strip.fb(0), true, true);
  teEvent[strip.intCHANNEL].set("Overhead Close Convenience Anim", tmeCurrentTime, intTm - 60, counterdur, countersp, AnEvSweep, AnPiPulse, false, CRGB(0, 0, 0), CRGB(0, 0, 20), CRGB(0, 0, 0), CRGB(0, 0, 0), strip.ft(0), strip.fb(0), true, true);
}


void vdAdditionalOpenADV00(Console &cons, profile_strip strip, timed_event teEvent[], unsigned long tmeCurrentTime)
// Turn Additional Lights On on to show the door is open.
// Pulse multiple yellow lights, followed by black lights, from center to end.
{
  cons.printwait("Door Overhead Alert On(CL: " + std::to_string(strip.intCHANNEL) + " ID:"+ " S:" + std::to_string(strip.fs(0)) + " E:" + std::to_string(strip.fe(0)) + ")");

  int intTm, intDur, intSp, intCt; 

  // Repeat Pulse
  intTm = 50; intDur = 700; intSp = 125; intCt = strip.intSIZE;
  int intMid = strip.intSIZE / 2;
  int intTm2Off = (intMid * intSp + intDur) /2;
  int IntTrlDly = intDur*2/3;

  // Yellow Guide 1
  teEvent[strip.intCHANNEL].set("Open Additional Anim", tmeCurrentTime, intTm, intDur, intSp, AnEvSweep, AnPiPulse, false, CRGB(0, 0, 0), CRGB(254, 254, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fs(0), strip.fe(intMid), true, true);
  teEvent[strip.intCHANNEL].set("Open Additional Anim", tmeCurrentTime, intTm + intTm2Off, intDur, intSp, AnEvSweep, AnPiPulse, false, CRGB(0, 0, 0), CRGB(254, 254, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fs(0), strip.fe(intMid), true, true);
  // Dark Guide 1
  teEvent[strip.intCHANNEL].set("Open Additional Anim", tmeCurrentTime, intTm + IntTrlDly, intDur, intSp, AnEvSweep, AnPiPulse, true, CRGB(0, 0, 0), CRGB(254, 254, 254), CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fs(0), strip.fe(intMid), true, true);
  teEvent[strip.intCHANNEL].set("Open Additional Anim", tmeCurrentTime, intTm + intTm2Off + IntTrlDly, intDur, intSp, AnEvSweep, AnPiPulse, true, CRGB(0, 0, 0), CRGB(254, 254, 254), CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fs(0), strip.fe(intMid), true, true);
  
  // Yellow Guide 2
  teEvent[strip.intCHANNEL].set("Open Additional Anim", tmeCurrentTime, intTm, intDur, intSp, AnEvSweep, AnPiPulse, false, CRGB(0, 0, 0), CRGB(254, 254, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fe(0), strip.fs(intMid), true, true);
  teEvent[strip.intCHANNEL].set("Open Additional Anim", tmeCurrentTime, intTm + intTm2Off, intDur, intSp, AnEvSweep, AnPiPulse, false, CRGB(0, 0, 0), CRGB(254, 254, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fe(0), strip.fs(intMid), true, true);
  // Dark Guide 2
  teEvent[strip.intCHANNEL].set("Open Additional Anim", tmeCurrentTime, intTm + IntTrlDly, intDur, intSp, AnEvSweep, AnPiPulse, true, CRGB(0, 0, 0), CRGB(254, 254, 254), CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fe(0), strip.fs(intMid), true, true);
  teEvent[strip.intCHANNEL].set("Open Additional Anim", tmeCurrentTime, intTm + intTm2Off + IntTrlDly, intDur, intSp, AnEvSweep, AnPiPulse, true, CRGB(0, 0, 0), CRGB(254, 254, 254), CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fe(0), strip.fs(intMid), true, true); 
}

void vdAdditionalOpenADV01(Console &cons, profile_strip strip, timed_event teEvent[], unsigned long tmeCurrentTime)
// Turn Additional Lights On on to show the door is open.
// Pulseating yellow light, brightest at center.
{
  cons.printwait("Door Overhead Alert On(CL: " + std::to_string(strip.intCHANNEL) + " ID:"+ " S:" + std::to_string(strip.fs(0)) + " E:" + std::to_string(strip.fe(0)) + ")");

  int intTm, intDur, intSp, intCt; 

  CRGB crgbPulseColor         = CRGB(128, 128, 0);
  CRGB crgbCounterPulseColor  = CRGB(0, 0, 128);


  // Repeat Pulse
  intTm = 50; intDur = 4000; intSp = 0; intCt = strip.intSIZE;
  int intMid = strip.intSIZE / 2;
  int intTm2Off = (intMid * intSp + intDur) /2;
  //int IntTrlDly = intDur*2/3;

  // Yellow Pulse and Counter Pulse
  teEvent[strip.intCHANNEL].set("Open Additional Anim", tmeCurrentTime, intTm, intDur, intSp, AnEvSweep, AnPiPulse, false, CRGB(0, 0, 0), crgbPulseColor, CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fs(0), strip.fe(0), true, true);
  teEvent[strip.intCHANNEL].set("Open Additional Anim", tmeCurrentTime, intTm, intDur, intSp, AnEvSweep, AnPiPulse, true, CRGB(0, 0, 0), crgbCounterPulseColor, CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fs(0), strip.fe(0), true, true);
}


void vdAdditionalCloseADV00(Console &cons, profile_strip strip, timed_event teEvent[], unsigned long tmeCurrentTime)
// Turn (force) Additional Lights Off on a Strip
{
  cons.printwait("Door Overhead Alert Off (CL: " + std::to_string(strip.intCHANNEL) + " ID:"+ " S:" + std::to_string(strip.fs(0)) + " E:" + std::to_string(strip.fe(0)) + ")");

  // Seach the strip for light colors and set them to end after animation completes.  
  teEvent[strip.intCHANNEL].set("Open Additional Anim", tmeCurrentTime, 50, 1000, 80, AnEvSetToEnd, 0, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fs(0), strip.fe(0), true, true);
}


/*
// -------------------------------------------------------------------------------------
// Halloween Effects
// -------------------------------------------------------------------------------------


// Dim clouds on strip.

void vdCloudAnimation(Console &cons, led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// Halloween Overhead Open - Drifting Grey Clouds.  
{
  // AnTavdCloud
  // Swap sweep start and end, depending on front or back.
  int start;
  int end;
  if (lsStrips[intStripID].Cl == 0)
  {
    start = lsStrips[intStripID].St;
    end = lsStrips[intStripID].Ed;
  }
  else
  {
    start = lsStrips[intStripID].Ed;
    end = lsStrips[intStripID].St;
  }
  
  // Set the background color.
  teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, 1000, 500, 5, AnEvSweep, AnPiFade, CRGB(0, 0, 0), CRGB(4, 6, 10), CRGB(0, 0, 0), CRGB(0, 0, 0), start, end, false, false);

  // The Clouds.
  teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, intRandomHD(2000), intRandomHD(10000), intRandomHD(500), AnEvSweep, AnPiPulse, CRGB(10, 17, 20), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, true);
  teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, intRandomHD(2000), intRandomHD(10000), intRandomHD(1000), AnEvSweep, AnPiPulse, CRGB(10, 20, 20), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, true);
  
  teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, intRandomHD(2000), intRandomHD(10000), intRandomHD(500), AnEvSweep, AnPiPulse, CRGB(10, 27, 33), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].Ed, lsStrips[intStripID].St, true, true);
  teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, intRandomHD(2000), intRandomHD(10000), intRandomHD(1000), AnEvSweep, AnPiPulse, CRGB(10, 22, 31), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].Ed, lsStrips[intStripID].St, true, true);
  }

// -------------------------------------------------------------------------------------

// Dingy yellow light on strip end.

void vdCeilingLightAnimation(Console &cons, led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// Halloween Overhead Open - Simple Light Overhead in Corner
{
  // AnTavdCloud
  // Swap sweep start and end, depending on front or back.
  int start;
  int end;
  if (lsStrips[intStripID].Cl == 0)
  {
    start = lsStrips[intStripID].St;
    end = start + 13;
  }
  else
  {
    start = lsStrips[intStripID].Ed;
    end = start - 13;
  }

  // Set the background color.
  teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, 1000, 500, 20, AnEvSweep, AnPiFadeDith, CRGB(0, 0, 0), CRGB(64, 64, 30), CRGB(0, 0, 0), CRGB(0, 0, 0), start, end, false, false);
  //teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, intTm, intDur, intSp, AnEvSweep, AnPiFadeDith, CRGB(0, 0, 0), CRGB(255, 255, 255), CRGB(0, 0, 0), CRGB(255, 64, 64), lsStrips[intStripID].St, lsStrips[intStripID].St + 4, false, false);
}

// -------------------------------------------------------------------------------------

// Random lightning strike on strip.

void vdLightning(Console &cons, led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// Halloween Overhead Open - Lightning
{
  // AnTavdLightning
  // Ocasional Lightining Flashes.
  int intTm;
  int intDur;
  int intSp;
  int StartTime = intRandomHD(12000);
  int BlinkTime;
  int BlinkInterval = 1000;


  intDur = 150; intSp = 2;

  // Repeat
  teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, StartTime + 5000, 0, 0, AnEvSchedule, AnTavdLightning, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
  
  // Thunder
  teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime,  StartTime + BlinkInterval, 1500, 3, AnEvSweep, AnPiFade, CRGB(32, 32, 49), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);

  // Flash 1
  intSp = intRandomHD(2);
  teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime,  StartTime + BlinkInterval, intDur, intSp, AnEvSweep, AnPiPulse, CRGB(128, 128, 196), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
  
  // Flash 2
  BlinkTime = intRandomHD(BlinkInterval); intSp = intRandomHD(2);
  teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime,  StartTime + BlinkTime, intDur, intSp, AnEvSweep, AnPiPulse, CRGB(128, 128, 196), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);

  // Flash 3
  // BlinkTime = intRandomHD(BlinkInterval); intSp = intRandomHD(2);
  // teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime,  StartTime + BlinkTime, intDur, intSp, AnEvSweep, AnPiPulse, CRGB(128, 128, 196), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
}

// -------------------------------------------------------------------------------------

// Random lightning strike on channel.

void vdChannelLightning(Console &cons, led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// Turn (force) Ligtning on Entire Channel. Strip Length Aware. 
{
  // AnTavdChannelLightning
  int intTm;
  int intCt;
  int intSp;
  int BlinkTime;
  int BlinkInterval;
  int StartTime = 50;

  int intDelay;

    // Swap sweep start and end, depending on front or back.
  int start;
  int end;
  if (lsStrips[intStripID].Cl == 0)
  {
    start = lsStrips[intStripID +1 ].St;
    end = lsStrips[intStripID +1 ].Ed;
  }
  else
  {
    start = lsStrips[intStripID +1 ].Ed;
    end = lsStrips[intStripID +1 ].St;
  }

  // Clear and Pulse colors background to green then ending in blueish, starting with the center.
  intTm = 50; BlinkInterval = 1000;
  intDelay = intAnTmDly(intTm, 0, lsStrips[intStripID].Ct(), intSp);

  // Thunder
  // Door 
  teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime,  StartTime + BlinkInterval, 1500, 3, AnEvSweep, AnPiFade, CRGB(32, 32, 49), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
  // Overhead 
  teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime,  StartTime + BlinkInterval + intDelay, 1500, 3, AnEvSweep, AnPiFade, CRGB(32, 32, 49), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), start, end, false, true);
 
  // Flash 1
  intSp = intRandomHD(2);
  // Door
  teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime,  StartTime + BlinkInterval, 150, intSp, AnEvSweep, AnPiPulse, CRGB(128, 128, 196), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
  // Overhead
  teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime,  StartTime + BlinkInterval + intDelay, 150, intSp, AnEvSweep, AnPiPulse, CRGB(128, 128, 196), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), start, end, false, true);

  // Flash 2
  BlinkTime = intRandomHD(BlinkInterval); intSp = intRandomHD(2);
  // Door
  teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime,  StartTime + BlinkTime, 150, intSp, AnEvSweep, AnPiPulse, CRGB(128, 128, 196), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
  // Overhead
  teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime,  StartTime + BlinkTime + intDelay, 150, intSp, AnEvSweep, AnPiPulse, CRGB(128, 128, 196), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), start, end, false, true);

  // Flash 3
  BlinkTime = intRandomHD(BlinkInterval); intSp = intRandomHD(2);
  // Door
  teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime,  StartTime + BlinkTime, 150, intSp, AnEvSweep, AnPiPulse, CRGB(128, 128, 196), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
  // Overhead
  teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime,  StartTime + BlinkTime + intDelay, 150, intSp, AnEvSweep, AnPiPulse, CRGB(128, 128, 196), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), start, end, false, true);
}


//------------------------------------------------------------------------------------
// Thanksgiving Effects
// -------------------------------------------------------------------------------------

// Blue sky with white clouds

void vdBlueSky(Console &cons, led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// Halloween Overhead Open - Drifting Grey Clouds.  
{
  // AnTavdBlueSky
  // Swap sweep start and end, depending on front or back.
  int start;
  int end;
  if (lsStrips[intStripID].Cl == 0)
  {
    start = lsStrips[intStripID].St;
    end = lsStrips[intStripID].Ed;
  }
  else
  {
    start = lsStrips[intStripID].Ed;
    end = lsStrips[intStripID].St;
  }
  
  // Set the background color.
  teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, 1000, 1000, 40, AnEvSweep, AnPiFade, CRGB(0, 0, 0), CRGB(0, 0, 30), CRGB(0, 0, 0), CRGB(0, 0, 30), start, end, false, false);

  // The Clouds.
  teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, intRandomHD(2000), intRandomHD(10000), intRandomHD(125), AnEvSweep, AnPiPulse, CRGB(30, 30, 30), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, true);
  teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, intRandomHD(2000), intRandomHD(6000), intRandomHD(250), AnEvSweep, AnPiPulse, CRGB(30, 30, 30), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, true);
  //teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, intRandomHD(2000), intRandomHD(10000), intRandomHD(500), AnEvSweep, AnPiPulse, CRGB(10, 27, 33), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].Ed, lsStrips[intStripID].St, true, true);
  //teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, intRandomHD(2000), intRandomHD(10000), intRandomHD(1000), AnEvSweep, AnPiPulse, CRGB(10, 22, 31), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].Ed, lsStrips[intStripID].St, true, true);
  }


// 
void vdNightSkyClose(Console &cons, led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
{

  int intTm;
  int intDur;
  int intSp;


  // Stop the currently running Pacificaish animation.
  // Schedule clear animation events ahead of time in case animations don't get completed.
  //teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, AUXDRLINGERBCK + 2000, 0, 0, AnEvClearRunning, 0, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, false);

  // Schedule Animations to Fade Out
  teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, AUXDRLINGERBCK + 1000, 3000, 0, AnEvSetToEnd, 0, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID -1 ].St, lsStrips[intStripID].Ed, false, false);

  //Restore the privouse Color to fade out
  intTm = 200; intDur = 6000; intSp = 5;

  teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, intTm , intDur, intSp, AnEvSweep, AnPiPulse, CRGB(0, 0, 30), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].Ed, lsStrips[intStripID].St, false, true);
  teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, 50, 0, 0, AnEvSchedule, AnTavdNightSky, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[lsStrips[intStripID].Cl].St, lsStrips[lsStrips[intStripID].Cl].Ed, false, true);
}

// Night Sky

void vdNightSky(Console &cons, led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// Halloween Overhead Open - Drifting Grey Clouds.  
{
  // AnTavdBlueSky
  // Swap sweep start and end, depending on front or back.
  int start;
  int end;

  CRGB Sun = CRGB(130, 130, 0);
  CRGB Set1 = CRGB(40, 10, 5);
  CRGB Set2 = CRGB(20, 5, 0);
  CRGB Set3 = CRGB(10, 2, 0);
  CRGB Set4 = CRGB(0, 0, 5);
  CRGB Set5 = CRGB(10, 10, 10);

  if (lsStrips[intStripID].Cl == 0)
  {
    // Back Door Light Strip
    start = lsStrips[intStripID].St;
    end = lsStrips[intStripID].Ed;
      
    // Set the background color.
    teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, 1000, 8000, 20, AnEvSweep, AnPiFadeDith, CRGB(0, 0, 0), Set3, CRGB(0, 0, 0), Set2, start, end -25, false, false);
    teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, 1000, 8000, 20, AnEvSweep, AnPiFadeDith, CRGB(0, 0, 0), Set2, CRGB(0, 0, 0), Set1, end -24, end -6, false, false);
    teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, 1000, 8000, 20, AnEvSweep, AnPiFade, CRGB(0, 0, 0), Sun, CRGB(0, 0, 0), Sun, end -6, end, false, false);
  }
  else
  {
    // Front Door Light Strip
    start = lsStrips[intStripID].Ed;
    end = lsStrips[intStripID].St;

    teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, 1000, 5000, 20, AnEvSweep, AnPiFadeDith, CRGB(0, 0, 0), Set3, CRGB(0, 0, 0), Set4, start, end + 15, false, false);
    teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, 1000, 5000, 20, AnEvSweep, AnPiFadeDith, CRGB(0, 0, 0), Set4, CRGB(0, 0, 0), Set5, end + 14, end, false, false);
  }

}

// -------------------------------------------------------------------------------------
*/


//------------------------------------------------------------------------------------
// Christmas Effects
// -------------------------------------------------------------------------------------

/*
void vdChristmasTree(Console &cons, led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// Christmas Overhead Open
{
  cons.printwait("vdChristmasTree (CL: " + std::to_string(lsStrips[intStripID].Cl) + " ID:"+ std::to_string(intStripID) + " S:" + std::to_string(lsStrips[intStripID].St) + " E:" + std::to_string(lsStrips[intStripID].Ed) + ")");
  // AnTavdChristmasTree

  // Assign the top and bottom of the strip
  int top;
  int bot;
  if (lsStrips[intStripID].Cl == 0)
  {
    // Back Door
    top = lsStrips[intStripID].St;
    bot = lsStrips[intStripID].Ed;

    // Set the background color.
    teEvent[lsStrips[intStripID].Cl].set("Overhead Open Anim", tmeCurrentTime, 500, 2000, 100, AnEvSweep, AnPiFadeDith, false, CRGB(0, 0, 0), CRGB(0, 45, 20), CRGB(0, 0, 0), CRGB(0, 0, 4), bot, top +15, false, false);

    // Star
    teEvent[lsStrips[intStripID].Cl].set("Overhead Open Anim", tmeCurrentTime, 6000, 10000, 0, AnEvSweep, AnPiFadeDith, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(128, 128, 16), top +5, top, false, false);
  }
  else
  {
    // Front Door
    top = lsStrips[intStripID].Ed;
    bot = lsStrips[intStripID].St;

    // Set the background color.
    teEvent[lsStrips[intStripID].Cl].set("Overhead Open Anim", tmeCurrentTime, 500, 2000, 100, AnEvSweep, AnPiFadeDith, false, CRGB(0, 0, 0), CRGB(0, 45, 20), CRGB(0, 0, 0), CRGB(0, 0, 4), bot, top -15, false, false);

    // Star 
    teEvent[lsStrips[intStripID].Cl].set("Overhead Open Anim", tmeCurrentTime, 10000, 10000, 0, AnEvSweep, AnPiFadeDith, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(128, 128, 16), top -5, top, false, false);
  }
  
  // The Lights.
  teEvent[lsStrips[intStripID].Cl].set("Overhead Open Anim", tmeCurrentTime, 3000, 8000, 0, AnEvSweep, AnPiTwinkle, false, CRGB(200, 0, 0), CRGB(0, 200, 0), CRGB(0, 0, 200), CRGB(2, 75, 3), lsStrips[intStripID].St +6, lsStrips[intStripID].Ed -6, true, false);

  // Variance
  //teEvent[lsStrips[intStripID].Cl].set("Overhead Open Anim", tmeCurrentTime, intRandomHD(2000), intRandomHD(10000), intRandomHD(500), AnEvSweep, AnPiPulse, true, CRGB(20, 20, 20), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), bot, top, true, true);
}

// -------------------------------------------------------------------------------------

void vdChristmasTreeCo(Console &cons, led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// Turn (force) Lights Off ona Strip

// AnTavdChristmasTreeCo

{
  cons.printwait("vdChristmasTreeCo (CL: " + std::to_string(lsStrips[intStripID].Cl) + " ID:"+ std::to_string(intStripID) + " S:" + std::to_string(lsStrips[intStripID].St) + " E:" + std::to_string(lsStrips[intStripID].Ed) + ")");
  int intTm;
  int intDurW;
  int intDurG;
  int intSp;

  int intDelay;

  // Assign the top and bottom of the strip
  int top;
  int bot;
  if (lsStrips[intStripID].Cl == 0)
  {
    // Back Door
    top = lsStrips[intStripID].St;
    bot = lsStrips[intStripID].Ed;

    // Background Color Fade out.
    teEvent[lsStrips[intStripID].Cl].set("Overhead Close Convenience Anim", tmeCurrentTime, 500, 10000, 0, AnEvSweep, AnPiFadeDith, false, CRGB(0, 45, 20), CRGB(0, 0, 0), CRGB(0, 0, 4),CRGB(0, 0, 0),  bot, top +15, false, false);
  
    // Star
    teEvent[lsStrips[intStripID].Cl].set("Overhead Close Convenience Anim", tmeCurrentTime, 500, 0, 0, AnEvSweep, AnPiFadeDith, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(125,124,16), top + lsStrips[intStripID].Ct() /2, top, false, false);
  }
  else
  {
    // Front Door
    top = lsStrips[intStripID].Ed;
    bot = lsStrips[intStripID].St;

    // Background Color Fade out.
    teEvent[lsStrips[intStripID].Cl].set("Overhead Close Convenience Anim", tmeCurrentTime, 500, 10000, 0, AnEvSweep, AnPiFadeDith, false, CRGB(0, 45, 20), CRGB(0, 0, 0), CRGB(0, 0, 4),CRGB(0, 0, 0),  bot, top - 15, false, false);
  
    // Star 
    teEvent[lsStrips[intStripID].Cl].set("Overhead Close Convenience Anim", tmeCurrentTime, 500, 0, 0, AnEvSweep, AnPiFadeDith, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(125,124,16), top - lsStrips[intStripID].Ct() /2, top, false, false);
  }

  // Background Color Fade out.

  // Schedule all lights to turn ahead of time at end of cycle
  teEvent[lsStrips[intStripID].Cl].set("", tmeCurrentTime, AUXDRLINGERBCK - 6000, 9000, 0, AnEvSetToEnd, 0, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, false);

  // The Lights.
  teEvent[lsStrips[intStripID].Cl].set("Overhead Close Convenience Anim", tmeCurrentTime, 500, 15000, 0, AnEvSweep, AnPiTwinkle, false, CRGB(200, 0, 0), CRGB(0, 200, 0), CRGB(0, 0, 200), CRGB(2, 75, 3), lsStrips[intStripID].St +6, lsStrips[intStripID].Ed -6, false, false);
  // with Sparkle
  teEvent[lsStrips[intStripID].Cl].set("Overhead Close Convenience Anim", tmeCurrentTime, 500, 5500, 0, AnEvSweep, AnPiTwinkle, false, CRGB(128, 128, 128), CRGB(64, 0, 64), CRGB(0, 64, 64), CRGB(2, 85, 1), lsStrips[intStripID].St +6, lsStrips[intStripID].Ed -6, true, false);
}

// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------

// -------------------------------------------------------------------------------------
//  Christmas Door Open Animation

void vdDoorOpenAnimation00Christmas(Console &cons, led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// Door Open Stage 0
// Prepare red backgrounds and puddle lights for the caution lights, and start shimmer effect.
{
  cons.printwait("vdDoorOpenAnimation00Christmas (CL: " + std::to_string(lsStrips[intStripID].Cl) + " ID:"+ std::to_string(intStripID) + " S:" + std::to_string(lsStrips[intStripID].St) + " E:" + std::to_string(lsStrips[intStripID].Ed) + ")");

  int intTm;
  int intDur;
  int intCt;
  int intSp;
  // Door Open Animation
  intTm = 100; intDur = 500; intSp = 10; intCt = lsStrips[intStripID].Ct(); // was 60

  // Clear set background to door open colors.
  
  teEvent[lsStrips[intStripID].Cl].set("vdOpenDoor", tmeCurrentTime, intTm, intDur, intSp, AnEvSweep, AnPiFadeDith, false, CRGB(0, 0, 0), CRGB(255, 255, 255), CRGB(0, 0, 0), CRGB(255, 32, 32), lsStrips[intStripID].St, lsStrips[intStripID].St + 10, false, false);
  teEvent[lsStrips[intStripID].Cl].set("vdOpenDoor", tmeCurrentTime, intTm, intDur, intSp, AnEvSweep, AnPiFadeDith, false, CRGB(0, 0, 0), CRGB(255, 32, 32), CRGB(0, 0, 0), CRGB(25, 0, 0), lsStrips[intStripID].St + 5, lsStrips[intStripID].St + 10, false, false);
  teEvent[lsStrips[intStripID].Cl].set("vdOpenDoor", tmeCurrentTime, intTm, intDur, intSp, AnEvSweep, AnPiFade, false, CRGB(0, 0, 0), CRGB(25, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St + 11, lsStrips[intStripID].Ed - 6, false, false);
  teEvent[lsStrips[intStripID].Cl].set("vdOpenDoor", tmeCurrentTime, intTm + 500, intDur, intSp, AnEvSweep, AnPiFadeDith, false, CRGB(0, 0, 0), CRGB(25, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].Ed - 5, lsStrips[intStripID].Ed, false, false);
 
  intTm = intAnTmDly(intTm, intDur, intCt, intSp);
  teEvent[lsStrips[intStripID].Cl].set("vdOpenDoor", tmeCurrentTime, intTm, 0, 0, AnEvSchedule, AnTaDoorOpen01Christmas, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
}

void vdDoorOpenAnimation01Christmas(Console &cons, led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// Door Open Stage 1
{
  cons.printwait("vdDoorOpenAnimation01Christmas (CL: " + std::to_string(lsStrips[intStripID].Cl) + " ID:"+ std::to_string(intStripID) + " S:" + std::to_string(lsStrips[intStripID].St) + " E:" + std::to_string(lsStrips[intStripID].Ed) + ")");
  int intTm = 50;
  int intDur;
  int intCt;
  int intSp;

  // Caution Door Open Flash
  intDur = 100; intSp = 2; intCt = lsStrips[intStripID].Ct();
  teEvent[lsStrips[intStripID].Cl].set("vdOpenDoor", tmeCurrentTime, intTm, intDur, intSp, AnEvSweep, AnPiPulse, false, CRGB(80, 80, 0), CRGB(80, 80, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
  intTm = intAnTmDly(intTm, intDur, intCt, intSp);
  intDur = 600; intSp = 12; intCt = lsStrips[intStripID].Ct();
  teEvent[lsStrips[intStripID].Cl].set("vdOpenDoor", tmeCurrentTime, intTm, intDur, intSp, AnEvSweep, AnPiPulse, false, CRGB(80, 80, 0), CRGB(80, 80, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
  intTm = intAnTmDly(intTm, intDur, intCt, intSp);
  intDur = 1500; intSp = 30; intCt = lsStrips[intStripID].Ct();
  teEvent[lsStrips[intStripID].Cl].set("vdOpenDoor", tmeCurrentTime, intTm, intDur, intSp, AnEvSweep, AnPiPulse, false, CRGB(128, 128, 0), CRGB(128, 128, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);

  intTm = intAnTmDly(intTm, intDur, intCt, intSp);
  teEvent[lsStrips[intStripID].Cl].set("vdOpenDoor", tmeCurrentTime, intTm, 0, 0, AnEvSchedule, AnTaDoorOpen02Christmas, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
}

// -------------------------------------------------------------------------------------

void vdDoorOpenAnimation02Christmas(Console &cons, led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// Door Open Stage 2
{
  cons.printwait("vdDoorOpenAnimation02Christmas (CL: " + std::to_string(lsStrips[intStripID].Cl) + " ID:"+ std::to_string(intStripID) + " S:" + std::to_string(lsStrips[intStripID].St) + " E:" + std::to_string(lsStrips[intStripID].Ed) + ")");
  int intTm = 0;
  int intDur;
  int intCt;
  int intSp;
  int intMid = lsStrips[intStripID].Ct() / 2;

  // Repeat Pulse
  intDur = 1500; intSp = 125; intCt = lsStrips[intStripID].Ct(); // was 36
  teEvent[lsStrips[intStripID].Cl].set("vdOpenDoor", tmeCurrentTime, intTm, intDur, intSp, AnEvSweep, AnPiPulse, false, CRGB(255, 255, 0), CRGB(255, 255, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].St + intMid, true, true);
  teEvent[lsStrips[intStripID].Cl].set("vdOpenDoor", tmeCurrentTime, intTm, intDur, intSp, AnEvSweep, AnPiPulse, false, CRGB(255, 255, 0), CRGB(255, 255, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].Ed, lsStrips[intStripID].Ed - intMid, true, true);

  // Sparkle
  teEvent[lsStrips[intStripID].Cl].set("vdOpenDoor", tmeCurrentTime, 500, 10000, 0, AnEvSweep, AnPiTwinkle, false, CRGB(128, 128, 128), CRGB(64, 0, 64), CRGB(0, 64, 64), CRGB(3, 85, 1), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, false);
  //teEvent[lsStrips[intStripID].Cl].set("vdOpenDoor", tmeCurrentTime, 500, 5500, 0, AnEvSweep, AnPiTwinkle, false, CRGB(128, 128, 128), CRGB(64, 0, 64), CRGB(0, 64, 64), CRGB(2, 95, 1), lsStrips[intStripID].St +20, lsStrips[intStripID].Ed -20, true, false);
}

void vdAddOpenChristm(Console &cons, led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// Turn (force) Lights Off ona Strip

// AnTavdvdAddOpenChristm
{
  int top;
  int bot;
  if (lsStrips[intStripID +1].Cl == 0)
  {
    // Back Door
    top = lsStrips[intStripID +1].St;
    bot = lsStrips[intStripID +1].Ed;

    // Star
    teEvent[lsStrips[intStripID +1].Cl].set("Open Additional Anim", tmeCurrentTime, 1000, 1000, 80, AnEvSweep, AnPiFadeDith, false, CRGB(0, 0, 0), CRGB(125,124,16), CRGB(0, 0, 0), CRGB(0, 0, 0), top, top + lsStrips[intStripID +1].Ct() /2, false, false);
  }
  else
  {
    // Front Door
    top = lsStrips[intStripID +1].Ed;
    bot = lsStrips[intStripID +1].St;
    
    // Star
    teEvent[lsStrips[intStripID +1].Cl].set("Open Additional Anim", tmeCurrentTime, 1000, 1000, 80, AnEvSweep, AnPiFadeDith, false, CRGB(0, 0, 0), CRGB(125,124,16), CRGB(0, 0, 0), CRGB(0, 0, 0), top, top - lsStrips[intStripID +1].Ct() /2, false, false);
  }
}


void vdAddCloseChristm(Console &cons, led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// Turn (force) Lights Off on a Strip

// AnTavdvdAddCloseChristm
{
  // Set the background color.
  //teEvent[lsStrips[intStripID].Cl].set("Door Open Anim", tmeCurrentTime, 500, 200, 100, AnEvSweep, AnPiFade, false, CRGB(0, 0, 0), CRGB(0, 45, 20), CRGB(0, 0, 0), CRGB(0, 0, 4), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, false);

  // The Sparkle.
  //teEvent[lsStrips[intStripID].Cl].set("Door Open Anim", tmeCurrentTime, 3000, 15000, 0, AnEvSweep, AnPiTwinkle, false, CRGB(200, 0, 0), CRGB(0, 200, 0), CRGB(0, 0, 200), CRGB(2, 75, 3), lsStrips[intStripID].St , lsStrips[intStripID].Ed, true, false);
  teEvent[lsStrips[intStripID].Cl].set("Door Open Anim", tmeCurrentTime, 500, 10000, 0, AnEvSweep, AnPiTwinkle, false, CRGB(128, 128, 128), CRGB(64, 0, 64), CRGB(0, 64, 64), CRGB(3, 85, 1), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, false);
  
  // Variance
  //teEvent[lsStrips[intStripID].Cl].set("Door Open Anim", tmeCurrentTime, intRandomHD(2000), intRandomHD(10000), intRandomHD(500), AnEvSweep, AnPiPulse, true, CRGB(20, 20, 20), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, true);

  // Fade out the bright star.
  teEvent[lsStrips[intStripID +1].Cl].set("", tmeCurrentTime, 3000, 1000, 80, AnEvSetToEnd, 0, false, CRGB(125,124,16), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID +1].St, lsStrips[intStripID +1].Ed, false, true);
}
*/



#endif