// ***************************************************************************************
// *
// *    Core       | Everything within this document is proprietary to Core Dynamics.
// *    Dynamics   | Any unauthorized duplication will be subject to prosecution.
// *
// *    Department : (R+D)^2                        Name: animations_bright.h
// *       Sub Dept: Programming
// *    Location ID: 856-45B
// *                                                      (c) 2856 - 2858 Core Dynamics
// ***************************************************************************************

#ifndef ANIMATIONS_BRIGHT_H
#define ANIMATIONS_BRIGHT_H

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
//bool booDAYNIGHT;


// -------------------------------------------------------------------------------------
// Calculate time it takes for an animation event to run.

int intAnTmDly(int intTm, int intDur, int intCt, int intSp);
// Calculate and return the next delay time based on duration of event, number of pixels,
//  and animation speed of each pixel.
//  Value in return statement is buffer time.

// -------------------------------------------------------------------------------------
// Advanced Animations

void vdTestPattern(Console &cons, v_profile_strip strip, timed_event teEvent[], unsigned long tmeCurrentTime);
// Turn Additional Lights On on to show the door is open.
// Pulseating yellow light, brightest at center.

// -------------------------------------------------------------------------------------
// Front Door Mask
void vdFront_Overhead_Mask(Console &cons, v_profile_strip strip, timed_event teEvent[], unsigned long tmeCurrentTime, string strIdentity);
// Turn Additional Lights On on to show the door is open.
// Pulseating yellow light, brightest at center.

// -------------------------------------------------------------------------------------
// Advanced Animations

void vdChannelLightFlashColor00(Console &cons, v_profile_strip strip, timed_event teEvent[], unsigned long tmeCurrentTime, CRGB crgbColor);
// Turn Color Pulse on Full Channel. Strip Length Aware. 
// AnTaChannelPulseColor

// -------------------------------------------------------------------------------------

void vdChannelLightPulseSimple01(Console &cons, v_profile_strip strip, timed_event teEvent[], unsigned long tmeCurrentTime, CRGB crgbColor);
// Multiple small pulses forward and backward. Strip Length Aware. 
// AnTaChannelPulseColor

void vdChannelLightPulseColor01(Console &cons, v_profile_strip strip, timed_event teEvent[], unsigned long tmeCurrentTime, CRGB crgbColor);
// Turn Color Pulse on Full Channel.
// AnTaChannelPulseColor

void vdChannelLightPulseColorCountdown01(Console &cons, v_profile_strip strip, timed_event teEvent[], unsigned long tmeCurrentTime, CRGB crgbColor);
// Turn Color Pulse on Full Channel.
// AnTaChannelPulseColor

// -------------------------------------------------------------------------------------

void vdOverheadIllum(Console &cons, v_profile_strip strip, timed_event teEvent[], unsigned long tmeCurrentTime, CRGB crgbColor);
// An overhead light.  Called by the Overhead command from the console.

// -------------------------------------------------------------------------------------

void vdHazard(Console &cons, v_profile_strip strip, timed_event teEvent[], unsigned long tmeCurrentTime);
// Hazard Lights. Called by the Hazard command from the console. 
// Runs on entire channel. 

// -------------------------------------------------------------------------------------

void vdPacificaishAnimationADVColor(Console &cons, v_profile_strip strip, timed_event teEvent[], unsigned long tmeCurrentTime, CRGB crgbColor);
// Blue Waves. Much more interesting than the old version of this.

// -------------------------------------------------------------------------------------

void vdDoorOpenAnimationADV00(Console &cons, v_profile_strip strip, timed_event teEvent[], unsigned long tmeCurrentTime);
// Prepare red backgrounds and puddle lights for the caution lights, and start shimmer effect.

// -------------------------------------------------------------------------------------

void vdDoorCloseRunningADV(Console &cons, v_profile_strip strip, timed_event teEvent[], unsigned long tmeCurrentTime);
// Effect to run on doors when all doors are closed. Animation will start then end, leaving lights in final state without proceessing anything else.

// -------------------------------------------------------------------------------------

void vdDoorCloseActiveADV00(Console &cons, v_profile_strip strip, timed_event teEvent[], unsigned long tmeCurrentTime);
// Effect to run on doors when all closed doors at least one other door is open.

// -------------------------------------------------------------------------------------

void vdPacificaishAnimationADV(Console &cons, v_profile_strip strip, timed_event teEvent[], unsigned long tmeCurrentTime);
// Blue Waves. Much more interesting than the old version of this.

// -------------------------------------------------------------------------------------

void vdCloseOverADV(Console &cons, v_profile_strip strip, timed_event teEvent[], unsigned long tmeCurrentTime);
// Overhead Lights Off

// -------------------------------------------------------------------------------------

void vdCoADV01(Console &cons, v_profile_strip strip, timed_event teEvent[], unsigned long tmeCurrentTime);
// Conviencance Lights On then Off.

// -------------------------------------------------------------------------------------

void vdAdditionalOpenADV01(Console &cons, v_profile_strip strip, timed_event teEvent[], unsigned long tmeCurrentTime);
// Turn Additional Lights On on to show the door is open.
// Pulseating yellow light, brightest at center.

// -------------------------------------------------------------------------------------

void vdAdditionalOpenADV02(Console &cons, v_profile_strip strip, timed_event teEvent[], unsigned long tmeCurrentTime);
// Turn Additional Lights On on to show the door is open.
// Slow Walking Yellow Lights.

// -------------------------------------------------------------------------------------

void vdAdditionalCloseADV00(Console &cons, v_profile_strip strip, timed_event teEvent[], unsigned long tmeCurrentTime);
// Turn (force) Additional Lights Off on a Strip




#endif