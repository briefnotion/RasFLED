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
#include <deque>

// RASFled related header files
#include "definitions.h"
#include "helper.h"
#include "consoleanddata.h"
#include "fledcore.h"
#include "json_interface.h"


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
// Animations

class ANIMATION_EVENT
{
  public:

  string Label;
  unsigned long Current_Time = 0;
  int Start_Delay_Time = 0;
  int Duration_Of_Brighness = 0;
  int Speed_Of_LED_Walk = 0;
  char Animation_Walk_Type;
  char Animation_Of_LED;
  bool Invert_Color = false;
  CRGB Start_Color_1;
  CRGB Dest_Color_1;
  CRGB Start_Color_2;
  CRGB Dest_Color_2;
  int LED_Start_Pos = 0;
  int LED_End_Pos = 0;
  bool Repeat = false;
  bool Clear_On_End = false;
  bool Off_During_Day = false;
};

class ANIMATION
{
  public:

  string LABEL = "";
  deque<ANIMATION_EVENT> EVENTS;

  void add_event(ANIMATION_EVENT Event);
};

class ANIMATIONS_LIST
{
  private:

  deque<ANIMATION> LIST;

  int find_pos_of_animation(string Label);

  public:

  void create_animation(string Label);

  void add_event_to_animation(string Animation_Label, ANIMATION_EVENT Event);

  void load_animations(string Directory, string Filename);
};

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

void vdPacificaishAnimationADVColor_Door(Console &cons, v_profile_strip strip, timed_event teEvent[], unsigned long tmeCurrentTime, CRGB crgbColor);
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