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
//bool booDAYNIGHT;


// -------------------------------------------------------------------------------------
// Calculate time it takes for an animation event to run.

int intAnTmDly(int intTm, int intDur, int intCt, int intSp);

void show_anim_info(Console &cons, v_profile_strip strip, string strDescription);

// -------------------------------------------------------------------------------------
// Advanced Animations

void vdPower_Animation(Console &cons, v_profile_strip strip, timed_event teEvent[], unsigned long tmeCurrentTime, CRGB crgbColor);

void vdTestPattern(Console &cons, v_profile_strip strip, timed_event teEvent[], unsigned long tmeCurrentTime, CRGB crgbColor);

void vdTestPattern_backup_01(Console &cons, v_profile_strip strip, timed_event teEvent[], unsigned long tmeCurrentTime);

// -------------------------------------------------------------------------------------
// Front Door Mask
void vdFront_Overhead_Mask(Console &cons, v_profile_strip strip, timed_event teEvent[], unsigned long tmeCurrentTime, string strIdentity);

// -------------------------------------------------------------------------------------
// Advanced Animations

void vdChannelLightFlashColor00(Console &cons, v_profile_strip strip, timed_event teEvent[], unsigned long tmeCurrentTime, CRGB crgbColor);

// -------------------------------------------------------------------------------------

void vdChannelLightPulseSimple01(Console &cons, v_profile_strip strip, timed_event teEvent[], unsigned long tmeCurrentTime, CRGB crgbColor);

void vdChannelLightPulseColor01(Console &cons, v_profile_strip strip, timed_event teEvent[], unsigned long tmeCurrentTime, CRGB crgbColor);

void vdChannelLightPulseColorCountdown01(Console &cons, v_profile_strip strip, timed_event teEvent[], unsigned long tmeCurrentTime, CRGB crgbColor);

// -------------------------------------------------------------------------------------

void vdOverheadIllum(Console &cons, v_profile_strip strip, timed_event teEvent[], unsigned long tmeCurrentTime, CRGB crgbColor);

// -------------------------------------------------------------------------------------

void vdHazard(Console &cons, v_profile_strip strip, timed_event teEvent[], unsigned long tmeCurrentTime);

// -------------------------------------------------------------------------------------

void vdPacificaishAnimationADVColor(Console &cons, v_profile_strip strip, timed_event teEvent[], unsigned long tmeCurrentTime, CRGB crgbColor);

// -------------------------------------------------------------------------------------

void vdDoorOpenAnimationADV00(Console &cons, v_profile_strip strip, timed_event teEvent[], unsigned long tmeCurrentTime);

// -------------------------------------------------------------------------------------

void vdDoorCloseRunningADV(Console &cons, v_profile_strip strip, timed_event teEvent[], unsigned long tmeCurrentTime);

// -------------------------------------------------------------------------------------

void vdDoorCloseActiveADV00(Console &cons, v_profile_strip strip, timed_event teEvent[], unsigned long tmeCurrentTime);

// -------------------------------------------------------------------------------------

void vdPacificaishAnimationADV(Console &cons, v_profile_strip strip, timed_event teEvent[], unsigned long tmeCurrentTime);

// -------------------------------------------------------------------------------------

void vdCloseOverADV(Console &cons, v_profile_strip strip, timed_event teEvent[], unsigned long tmeCurrentTime);

// -------------------------------------------------------------------------------------

void vdCoADV01(Console &cons, v_profile_strip strip, timed_event teEvent[], unsigned long tmeCurrentTime);

// -------------------------------------------------------------------------------------

void vdAdditionalOpenADV01(Console &cons, v_profile_strip strip, timed_event teEvent[], unsigned long tmeCurrentTime);

// -------------------------------------------------------------------------------------

void vdAdditionalOpenADV02(Console &cons, v_profile_strip strip, timed_event teEvent[], unsigned long tmeCurrentTime);

// -------------------------------------------------------------------------------------

void vdAdditionalCloseADV00(Console &cons, v_profile_strip strip, timed_event teEvent[], unsigned long tmeCurrentTime);




#endif