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

void show_anim_info(Console &cons, v_profile_strip strip, string strDescription)
{
  cons.printwait("    C" + to_string(strip.intCHANNEL) + " S" + to_string(strip.intID) + " :" + strDescription); 
}

// -------------------------------------------------------------------------------------
// Advanced Animations

void vdTestPattern(Console &cons, v_profile_strip strip, timed_event teEvent[], unsigned long tmeCurrentTime)
// Turn Additional Lights On on to show the door is open.
// Pulseating yellow light, brightest at center.
{
  show_anim_info(cons, strip, "Test Pattern");

  teEvent[strip.intCHANNEL].set("Hazard", tmeCurrentTime, 1000, 500, 30, AnEvSweep, AnPiFadeDith, false, CRGB(0, 0, 0), CRGB(64, 0, 0), CRGB(0, 0, 0), CRGB(0, 64, 0), strip.fs(0), strip.fe(0), false, false);
}

// -------------------------------------------------------------------------------------
// Front Door Mask
void vdFront_Overhead_Mask(Console &cons, v_profile_strip strip, timed_event teEvent[], unsigned long tmeCurrentTime, string strIdentity)
// Turn Additional Lights On on to show the door is open.
// Pulseating yellow light, brightest at center.
{
  if ((strip.strNAME == "Overhead") && (strip.strPOSITION == "Front"))
  {
    show_anim_info(cons, strip, "Front Door Mask");

    CRGB Color_M = CRGB(128,128,128); 

    teEvent[strip.intCHANNEL].set(strIdentity, tmeCurrentTime, 1000, 500, 30, AnEvSweep, AnPiFadeDith, true, CRGB(0, 0, 0), Color_M, CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fe(0), strip.fe(20), false, false);
  }
}

// -------------------------------------------------------------------------------------
// Advanced Animations

void vdChannelLightFlashColor00(Console &cons, v_profile_strip strip, timed_event teEvent[], unsigned long tmeCurrentTime, CRGB crgbColor)
// Turn Color Pulse on Full Channel. Strip Length Aware. 
// AnTaChannelPulseColor
{
  show_anim_info(cons, strip, "Flash Color");

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
  intTm = 250; intDurW = 2000; intDurG = 5000; 
  
  int intSpBack = 0; 
  int intSpAntiPuls = 15; 
  int intDurAnti = 150;
  
  intCt = 36;

  // Blink
  teEvent[strip.intCHANNEL].set("Channel Light Pulse Color", tmeCurrentTime, intTm - 200, 100, 0, AnEvSweep, AnPiPulse, true, CRGB(0, 0, 0), CRGB(255, 255, 255), CRGB(0, 0, 0), CRGB(0, 0, 0), strip.ft(0), strip.fb(0), false, true);
  teEvent[strip.intCHANNEL].set("Channel Light Pulse Color", tmeCurrentTime, intTm - 100, 100, 0, AnEvSweep, AnPiPulse, true, CRGB(0, 0, 0), CRGB(255, 255, 255), CRGB(0, 0, 0), CRGB(0, 0, 0), strip.ft(0), strip.fb(0), false, true);

  // 1
  // Door Color with White
  teEvent[strip.intCHANNEL].set("Channel Light Pulse Color", tmeCurrentTime, intTm + 50, intDurW, intSpBack, AnEvSweep, AnPiPulse, false, CRGB(0, 0, 0), crgbColor, CRGB(0, 0, 0), CRGB(0, 0, 0), strip.ft(0), strip.fb(0), false, true);

  // Forward ---
  // Anti Red
  teEvent[strip.intCHANNEL].set("Channel Light Pulse Color", tmeCurrentTime, intTm + 50 + (1*intDurAnti), intDurAnti, intSpAntiPuls, AnEvSweep, AnPiPulse, true, CRGB(0, 0, 0), CRGB(0, 128, 128), CRGB(0, 0, 0), CRGB(0, 0, 0), strip.ft(0), strip.fb(0), false, true);

  // Anti Green
  teEvent[strip.intCHANNEL].set("Channel Light Pulse Color", tmeCurrentTime, intTm + 50 + (2*intDurAnti), intDurAnti, intSpAntiPuls, AnEvSweep, AnPiPulse, true, CRGB(0, 0, 0), CRGB(128, 0, 128), CRGB(0, 0, 0), CRGB(0, 0, 0), strip.ft(0), strip.fb(0), false, true);

  // Anti Blue
  teEvent[strip.intCHANNEL].set("Channel Light Pulse Color", tmeCurrentTime, intTm + 50 + (3*intDurAnti), intDurAnti, intSpAntiPuls, AnEvSweep, AnPiPulse, true, CRGB(0, 0, 0), CRGB(128, 128, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), strip.ft(0), strip.fb(0), false, true);

  // Backward ---
  // Anti Red
  teEvent[strip.intCHANNEL].set("Channel Light Pulse Color", tmeCurrentTime, intTm + 50 + (1*intDurAnti), intDurAnti, intSpAntiPuls, AnEvSweep, AnPiPulse, true, CRGB(0, 0, 0), CRGB(0, 128, 128), CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fb(0), strip.ft(0), false, true);

  // Anti Green
  teEvent[strip.intCHANNEL].set("Channel Light Pulse Color", tmeCurrentTime, intTm + 50 + (2*intDurAnti), intDurAnti, intSpAntiPuls, AnEvSweep, AnPiPulse, true, CRGB(0, 0, 0), CRGB(128, 0, 128), CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fb(0), strip.ft(0), false, true);

  // Anti Blue
  teEvent[strip.intCHANNEL].set("Channel Light Pulse Color", tmeCurrentTime, intTm + 50 + (3*intDurAnti), intDurAnti, intSpAntiPuls, AnEvSweep, AnPiPulse, true, CRGB(0, 0, 0), CRGB(128, 128, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fb(0), strip.ft(0), false, true);

  // Blink
  teEvent[strip.intCHANNEL].set("Channel Light Pulse Color", tmeCurrentTime, intTm + 1200, 100, 0, AnEvSweep, AnPiPulse, true, CRGB(0, 0, 0), CRGB(255, 255, 255), CRGB(0, 0, 0), CRGB(0, 0, 0), strip.ft(0), strip.fb(0), false, true);
  teEvent[strip.intCHANNEL].set("Channel Light Pulse Color", tmeCurrentTime, intTm + 1100, 100, 0, AnEvSweep, AnPiPulse, true, CRGB(0, 0, 0), CRGB(255, 255, 255), CRGB(0, 0, 0), CRGB(0, 0, 0), strip.ft(0), strip.fb(0), false, true);

}

// -------------------------------------------------------------------------------------

void vdChannelLightPulseSimple01(Console &cons, v_profile_strip strip, timed_event teEvent[], unsigned long tmeCurrentTime, CRGB crgbColor)
// Multiple small pulses forward and backward. Strip Length Aware. 
// AnTaChannelPulseColor
{
  show_anim_info(cons, strip, "Pulse Color 01");

  int intTm;
  int intDurW;
  int intDurG;
  int intSp;

  int intDelay;
  int intDelayGlitchAnti;

  // Set the fadeout color 
  CRGB crgbColor4;
  crgbColor4.r = crgbColor.r + 64;
  crgbColor4.g = crgbColor.g + 64;
  crgbColor4.b = crgbColor.b + 64;

  // Clear and Pulse colors background to bright then param color, starting with the center.
  intTm = 100; intDurW = 500; intDurG = 3000; intSp = 100; 

  int amount = 4;
  int pos[amount];

  // Door
  int sd = strip.led_count() / amount;

  int stad, endd = 0;
  int stadf, enddf = 0;
  int stadb, enddb = 0;

  int switchdelaydoor = 0;

  // Overhead
  /*
  int so = strip_group.pstrOVERHEAD.intSIZE / amount;

  int stao, endo = 0;
  int staof, endof = 0;
  int staob, endob = 0;
  */

  int counter_symetry = 0;


  for(int x = 0; x < amount; x++)
  {
    // Door numbers
    stad = (sd * x);
    endd = (sd * x) + sd;

    stadf = strip.fs(0) + stad;
    enddf = strip.fs(0) + endd;
    // switchdelaydoor = intAnTmDly(intTm, 0, sd, intSp)  * 2;
    switchdelaydoor = intDurG;
    stadb = strip.fe(0) - stad;
    enddb = strip.fe(0) - endd;

    // Counter Symetry
    counter_symetry = 300 * (amount - x - 1); 

    // Door Animations
    teEvent[strip.intCHANNEL].set("Channel Light Pulse Color", tmeCurrentTime, intTm + (counter_symetry), intDurW, intSp, AnEvSweep, AnPiPulse, false, CRGB(0, 0, 0), crgbColor4, CRGB(0, 0, 0), CRGB(0, 0, 0), stadf, enddf, false, true);
    teEvent[strip.intCHANNEL].set("Channel Light Pulse Color", tmeCurrentTime, intTm + (counter_symetry), intDurG, intSp, AnEvSweep, AnPiPulse, false, CRGB(0, 0, 0), crgbColor, CRGB(0, 0, 0), CRGB(0, 0, 0), stadf, enddf, false, true);

    teEvent[strip.intCHANNEL].set("Channel Light Pulse Color", tmeCurrentTime, switchdelaydoor + (counter_symetry), intDurW, intSp, AnEvSweep, AnPiPulse, false, CRGB(0, 0, 0), crgbColor4, CRGB(0, 0, 0), CRGB(0, 0, 0), stadb, enddb, false, true);
    teEvent[strip.intCHANNEL].set("Channel Light Pulse Color", tmeCurrentTime, switchdelaydoor + (counter_symetry), intDurG, intSp, AnEvSweep, AnPiPulse, false, CRGB(0, 0, 0), crgbColor, CRGB(0, 0, 0), CRGB(0, 0, 0), stadb, enddb, false, true);
  }
}

void vdChannelLightPulseColor01(Console &cons, v_profile_strip strip, timed_event teEvent[], unsigned long tmeCurrentTime, CRGB crgbColor)
// Turn Color Pulse on Full Channel.
// AnTaChannelPulseColor
{
  show_anim_info(cons, strip, "Pulse Color Repeat 01");

  // Set the pulse to timed repeat
  teEvent[strip.intCHANNEL].set("Channel Light Pulse Color", tmeCurrentTime, 100, 6000, 0, AnEvSchedule, AnTaChannelPulseSimple, false, crgbColor, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), 0, 0, true, true);
}

void vdChannelLightPulseColorCountdown01(Console &cons, v_profile_strip strip, timed_event teEvent[], unsigned long tmeCurrentTime, CRGB crgbColor)
// Turn Color Pulse on Full Channel.
// AnTaChannelPulseColor
{
  cons.printwait("Pulse Countdown Timer Color Repeat 01 (CL: "); // + std::to_string(strip_group.pstrDOOR.intCHANNEL));
  teEvent[strip.intCHANNEL].set("Channel Light Pulse Color", tmeCurrentTime, 100, 0, 0, AnEvSchedule, AnTaChannelPulseSimple, false, crgbColor, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), 0, 0, false, true);
  teEvent[strip.intCHANNEL].set("Channel Light Pulse Color", tmeCurrentTime, 6000, 0, 0, AnEvSchedule, AnTaChannelPulseColorCountdown, false, crgbColor, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), 0, 0, false, true);
}

// -------------------------------------------------------------------------------------

void vdOverheadIllum(Console &cons, v_profile_strip strip, timed_event teEvent[], unsigned long tmeCurrentTime, CRGB crgbColor)
// An overhead light.  Called by the Overhead command from the console. 
{
  show_anim_info(cons, strip, "Overhead Illumination Color");

  // Set the background color.
  teEvent[strip.intCHANNEL].set("Overhead Illumination", tmeCurrentTime, 1000, 500, 30, AnEvSweep, AnPiFade, false, CRGB(0, 0, 0), crgbColor, CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fs(0), strip.fe(0), false, false);
}

// -------------------------------------------------------------------------------------

void vdHazard(Console &cons, v_profile_strip strip, timed_event teEvent[], unsigned long tmeCurrentTime)
// Hazard Lights. Called by the Hazard command from the console. 
// Runs on entire channel. 
{
  show_anim_info(cons, strip, "Hazard");

  // Pulse Red.
  teEvent[strip.intCHANNEL].set("Hazard", tmeCurrentTime, 100, 900, 0, AnEvSweep, AnPiPulse, false, CRGB(0, 0, 0), CRGB(128, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fs(0), strip.fe(0), false, true);

  // Set the hazard to timed repeat
  teEvent[strip.intCHANNEL].set("Hazard", tmeCurrentTime, 1500, 0, 0, AnEvSchedule, AnTaHazard, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), 0, 0, false, true);  
}

// -------------------------------------------------------------------------------------

void vdPacificaishAnimationADVColor(Console &cons, v_profile_strip strip, timed_event teEvent[], unsigned long tmeCurrentTime, CRGB crgbColor)
// Blue Waves. Much more interesting than the old version of this.
{
  show_anim_info(cons, strip, "Pacificaish Color");
  
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
  if (strip.position("Front"))
  {
    // Mask
    CRGB Color_M = CRGB(128,128,128); 
    teEvent[strip.intCHANNEL].set("Overhead Illumination", tmeCurrentTime, 1000, 500, 30, AnEvSweep, AnPiFadeDith, true, CRGB(0, 0, 0), Color_M, CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fb(0), strip.fb(20), false, false);
  }

  // Set the background color.
  teEvent[strip.intCHANNEL].set("Overhead Illumination", tmeCurrentTime, 1000, 500, 30, AnEvSweep, AnPiFade, false, CRGB(0, 0, 0), Color_B, CRGB(0, 0, 0), CRGB(0, 0, 0), strip.ft(0), strip.fb(0), false, false);

  // The waves.
  teEvent[strip.intCHANNEL].set("Overhead Illumination", tmeCurrentTime, intRandomHD(2000), intRandomHD(3500), intRandomHD(125), AnEvSweep, AnPiPulse, false, CRGB(0, 0, 0), Color_1, CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fe(0), strip.fs(0), true, true);
  teEvent[strip.intCHANNEL].set("Overhead Illumination", tmeCurrentTime, intRandomHD(2000), intRandomHD(1500), intRandomHD(75), AnEvSweep, AnPiPulse, false, CRGB(0, 0, 0), Color_2, CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fe(0), strip.fs(0), true, true);
  teEvent[strip.intCHANNEL].set("Overhead Illumination", tmeCurrentTime, intRandomHD(2000), intRandomHD(3600), intRandomHD(135), AnEvSweep, AnPiPulse, false, CRGB(0, 0, 0), Color_3, CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fe(0), strip.fs(0), true, true);
  teEvent[strip.intCHANNEL].set("Overhead Illumination", tmeCurrentTime, intRandomHD(2000), intRandomHD(3200), intRandomHD(100), AnEvSweep, AnPiPulse, false, CRGB(0, 0, 0), Color_4, CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fe(0), strip.fs(0), true, true);

  teEvent[strip.intCHANNEL].set("Overhead Illumination", tmeCurrentTime, intRandomHD(2000), intRandomHD(3500), intRandomHD(125), AnEvSweep, AnPiPulse, false, CRGB(0, 0, 0), Color_1, CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fe(0), strip.fs(0), true, true);
  teEvent[strip.intCHANNEL].set("Overhead Illumination", tmeCurrentTime, intRandomHD(2000), intRandomHD(1500), intRandomHD(75), AnEvSweep, AnPiPulse, false, CRGB(0, 0, 0), Color_2, CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fe(0), strip.fs(0), true, true);
  teEvent[strip.intCHANNEL].set("Overhead Illumination", tmeCurrentTime, intRandomHD(2000), intRandomHD(3600), intRandomHD(135), AnEvSweep, AnPiPulse, false, CRGB(0, 0, 0), Color_3, CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fe(0), strip.fs(0), true, true);
  teEvent[strip.intCHANNEL].set("Overhead Illumination", tmeCurrentTime, intRandomHD(2000), intRandomHD(3200), intRandomHD(100), AnEvSweep, AnPiPulse, false, CRGB(0, 0, 0), Color_4, CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fe(0), strip.fs(0), true, true);

  // Counter waves.
  teEvent[strip.intCHANNEL].set("Overhead Illumination", tmeCurrentTime, intRandomHD(2000), intRandomHD(3500), intRandomHD(125), AnEvSweep, AnPiPulse, true, CRGB(0, 0, 0), Color_S1, CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fe(0), strip.fs(0), true, true);
  teEvent[strip.intCHANNEL].set("Overhead Illumination", tmeCurrentTime, intRandomHD(2000), intRandomHD(1500), intRandomHD(75), AnEvSweep, AnPiPulse, true, CRGB(0, 0, 0), Color_S2, CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fe(0), strip.fs(0), true, true);
  teEvent[strip.intCHANNEL].set("Overhead Illumination", tmeCurrentTime, intRandomHD(2000), intRandomHD(3600), intRandomHD(135), AnEvSweep, AnPiPulse, true, CRGB(0, 0, 0), Color_S3, CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fe(0), strip.fs(0), true, true);
  teEvent[strip.intCHANNEL].set("Overhead Illumination", tmeCurrentTime, intRandomHD(2000), intRandomHD(3200), intRandomHD(100), AnEvSweep, AnPiPulse, true, CRGB(0, 0, 0), Color_S4, CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fe(0), strip.fs(0), true, true);
}

// -------------------------------------------------------------------------------------

void vdDoorOpenAnimationADV00(Console &cons, v_profile_strip strip, timed_event teEvent[], unsigned long tmeCurrentTime)
// Prepare red backgrounds and puddle lights for the caution lights, and start shimmer effect.
{
  show_anim_info(cons, strip, "Door Open Safety 00");

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
  intTm = 100; intDur = 500; intSp = 10; intCt = strip.led_count();

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
  intDur = 50; intSp = 1; intCt = strip.led_count();
  teEvent[strip.intCHANNEL].set("vdOpenDoor", tmeCurrentTime, intTm, 50, intSp, AnEvSweep, AnPiPulse, false, lead, lead, CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fe(0), strip.fs(0), false, true);
  teEvent[strip.intCHANNEL].set("vdOpenDoor", tmeCurrentTime, intTm, intDur, intSp, AnEvSweep, AnPiPulse, false, CRGB(80, 80, 0), CRGB(80, 80, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fe(0), strip.fs(0), false, true);
  
  intTm = intAnTmDly(intTm, intDur, intCt, intSp);

  intDur = 100; intSp = 2; intCt = strip.led_count();
  teEvent[strip.intCHANNEL].set("vdOpenDoor", tmeCurrentTime, intTm, 50, intSp, AnEvSweep, AnPiPulse, false, lead, lead, CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fe(0), strip.fs(0), false, true);
  teEvent[strip.intCHANNEL].set("vdOpenDoor", tmeCurrentTime, intTm, intDur, intSp, AnEvSweep, AnPiPulse, false, CRGB(80, 80, 0), CRGB(80, 80, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fe(0), strip.fs(0), false, true);
  
  intTm = intAnTmDly(intTm, intDur, intCt, intSp);

  intDur = 200; intSp = 4; intCt = strip.led_count();
  teEvent[strip.intCHANNEL].set("vdOpenDoor", tmeCurrentTime, intTm, 50, intSp, AnEvSweep, AnPiPulse, false, lead, lead, CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fe(0), strip.fs(0), false, true);
  teEvent[strip.intCHANNEL].set("vdOpenDoor", tmeCurrentTime, intTm, intDur, intSp, AnEvSweep, AnPiPulse, false, CRGB(80, 80, 0), CRGB(80, 80, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fe(0), strip.fs(0), false, true);
  
  intTm = intAnTmDly(intTm, intDur, intCt, intSp);

  intDur = 400; intSp = 8; intCt = strip.led_count();
  teEvent[strip.intCHANNEL].set("vdOpenDoor", tmeCurrentTime, intTm, 50, intSp, AnEvSweep, AnPiPulse, false, lead, lead, CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fe(0), strip.fs(0), false, true);
  teEvent[strip.intCHANNEL].set("vdOpenDoor", tmeCurrentTime, intTm, intDur, intSp, AnEvSweep, AnPiPulse, false, CRGB(80, 80, 0), CRGB(80, 80, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fe(0), strip.fs(0), false, true);
  
  intTm = intAnTmDly(intTm, intDur, intCt, intSp);

  intDur = 800; intSp = 16; intCt = strip.led_count();
  teEvent[strip.intCHANNEL].set("vdOpenDoor", tmeCurrentTime, intTm, 100, intSp, AnEvSweep, AnPiPulse, false, lead, lead, CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fe(0), strip.fs(0), false, true);
  teEvent[strip.intCHANNEL].set("vdOpenDoor", tmeCurrentTime, intTm, intDur, intSp, AnEvSweep, AnPiPulse, false, CRGB(128, 128, 0), CRGB(128, 128, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fe(0), strip.fs(0), false, true);
  
  // Repeat Red Pulse
  intDur = 1500; intSp = 125; intCt = strip.led_count();
  int intMid = strip.led_count() / 2;
  int intTm2Off = (intMid * intSp + intDur) /2;
  
  // Pulse Yellow up to mid
  teEvent[strip.intCHANNEL].set("vdOpenDoor", tmeCurrentTime, intTm, intDur, intSp, AnEvSweep, AnPiPulse, false, CRGB(128, 128, 0), CRGB(128, 128, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fs(0), strip.fe(intMid), true, true);
  teEvent[strip.intCHANNEL].set("vdOpenDoor", tmeCurrentTime, intTm + intTm2Off, intDur, intSp, AnEvSweep, AnPiPulse, false, CRGB(128, 128, 0), CRGB(128, 128, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fs(0), strip.fe(intMid), true, true);

  // Pulse Yellow down to mid
  teEvent[strip.intCHANNEL].set("vdOpenDoor", tmeCurrentTime, intTm, intDur, intSp, AnEvSweep, AnPiPulse, false, CRGB(128, 128, 0), CRGB(128, 128, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fe(0), strip.fs(intMid), true, true);
  teEvent[strip.intCHANNEL].set("vdOpenDoor", tmeCurrentTime, intTm + intTm2Off, intDur, intSp, AnEvSweep, AnPiPulse, false, CRGB(128, 128, 0), CRGB(128, 128, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fe(0), strip.fs(intMid), true, true);
}

// -------------------------------------------------------------------------------------

void vdDoorCloseRunningADV(Console &cons, v_profile_strip strip, timed_event teEvent[], unsigned long tmeCurrentTime)
// Effect to run on doors when all doors are closed. Animation will start then end, leaving lights in final state without proceessing anything else.
{
  show_anim_info(cons, strip, "Running Side Lights");

  // Give strip a fresh start.
  // Clear any animations that may be running and this should replace.
  teEvent[strip.intCHANNEL].set("Door Close Active Anim", tmeCurrentTime, 200, 999, 80, AnEvSetToEnd, 0, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fs(0), strip.fe(0), true, true);
  teEvent[strip.intCHANNEL].set("vdOpenDoor", tmeCurrentTime, 200, 999, 80, AnEvSetToEnd, 0, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fs(0), strip.fe(0), true, true);

  int intTm;
  int intDur;
  int intCt;
  int intSp;

  CRGB running_light = CRGB(25, 5, 0);

  intTm = 600; intDur = 5000; intSp = 50; intCt = strip.led_count();

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

// -------------------------------------------------------------------------------------

void vdDoorCloseActiveADV00(Console &cons, v_profile_strip strip, timed_event teEvent[], unsigned long tmeCurrentTime)
// Effect to run on doors when all closed doors at least one other door is open.
{
  show_anim_info(cons, strip, "Door Close Safety 00");

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

// -------------------------------------------------------------------------------------

void vdPacificaishAnimationADV(Console &cons, v_profile_strip strip, timed_event teEvent[], unsigned long tmeCurrentTime)
// Blue Waves. Much more interesting than the old version of this.
{
  show_anim_info(cons, strip, "Pacificaish");

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

// -------------------------------------------------------------------------------------

void vdCloseOverADV(Console &cons, v_profile_strip strip, timed_event teEvent[], unsigned long tmeCurrentTime)
// Overhead Lights Off
{
  show_anim_info(cons, strip, "Overhead Lights Off");

  // Just set all the current over head lights to fade away.
  teEvent[strip.intCHANNEL].set("Overhead Open Anim", tmeCurrentTime, 0, 1000, 80, AnEvSetToEnd, 0, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fs(0), strip.fe(0), true, true);
}

// -------------------------------------------------------------------------------------

void vdCoADV01(Console &cons, v_profile_strip strip, timed_event teEvent[], unsigned long tmeCurrentTime)
// Conviencance Lights On then Off.
{
  show_anim_info(cons, strip, "Conviencance Lights 01");

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
  intTm = 50; intDur = 500; intSp = 0; intCt = strip.led_count();
  int intMid = strip.led_count() / 2;
  int intTm2Off = (intMid * intSp + intDur) /2;
  //int IntTrlDly = intDur*2/3;

  // Glitch Yellow Fade Away
  intTm = intAnTmDly(intTm, intDur, strip.led_count(), intSp);
  intDur = 500; intSp = 0;

  teEvent[strip.intCHANNEL].set("Overhead Close Convenience Anim", tmeCurrentTime, intTm, intDurAnti, intSpAntiPuls, AnEvSweep, AnPiPulse, true, CRGB(0, 0, 0), crgbRed, CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fs(0), strip.fe(0), false, true);
  teEvent[strip.intCHANNEL].set("Overhead Close Convenience Anim", tmeCurrentTime, intTm, counterdur, countersp, AnEvSweep, AnPiPulse, true, CRGB(0, 0, 0), crgbCounterColor, CRGB(0, 0, 0), CRGB(0, 0, 0), strip.ft(0), strip.fb(0), false, true);

  intTm = intAnTmDly(intTm, intDur, strip.led_count(), intSp);
  intDur = 500; intSp = 0;

  teEvent[strip.intCHANNEL].set("Overhead Close Convenience Anim", tmeCurrentTime, intTm, intDurAnti, intSpAntiPuls, AnEvSweep, AnPiPulse, true, CRGB(0, 0, 0), crgbGreen, CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fs(0), strip.fe(0), false, true);
  teEvent[strip.intCHANNEL].set("Overhead Close Convenience Anim", tmeCurrentTime, intTm, counterdur, countersp, AnEvSweep, AnPiPulse, true, CRGB(0, 0, 0), crgbCounterColor, CRGB(0, 0, 0), CRGB(0, 0, 0), strip.ft(0), strip.fb(0), false, true);

  intTm = intAnTmDly(intTm, intDur, strip.led_count(), intSp);
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

// -------------------------------------------------------------------------------------

void vdAdditionalOpenADV01(Console &cons, v_profile_strip strip, timed_event teEvent[], unsigned long tmeCurrentTime)
// Turn Additional Lights On on to show the door is open.
// Pulseating yellow light, brightest at center.
{
  show_anim_info(cons, strip, "Door Overhead Alert On 01");

  int intTm, intDur, intSp, intCt; 

  CRGB crgbPulseColor         = CRGB(128, 128, 0);
  CRGB crgbCounterPulseColor  = CRGB(0, 0, 128);


  // Repeat Pulse
  intTm = 50; intDur = 4000; intSp = 0; intCt = strip.led_count();
  int intMid = strip.led_count() / 2;
  int intTm2Off = (intMid * intSp + intDur) /2;
  //int IntTrlDly = intDur*2/3;

  // Yellow Pulse and Counter Pulse
  teEvent[strip.intCHANNEL].set("Open Additional Anim", tmeCurrentTime, intTm, intDur, intSp, AnEvSweep, AnPiPulse, false, CRGB(0, 0, 0), crgbPulseColor, CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fs(0), strip.fe(0), true, true);
  teEvent[strip.intCHANNEL].set("Open Additional Anim", tmeCurrentTime, intTm, intDur, intSp, AnEvSweep, AnPiPulse, true, CRGB(0, 0, 0), crgbCounterPulseColor, CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fs(0), strip.fe(0), true, true);
}

// -------------------------------------------------------------------------------------

void vdAdditionalOpenADV02(Console &cons, v_profile_strip strip, timed_event teEvent[], unsigned long tmeCurrentTime)
// Turn Additional Lights On on to show the door is open.
// Slow Walking Yellow Lights.
{
  show_anim_info(cons, strip, "Door Overhead Alert On");

  int intTm, intDur, intSp, intCt; 

  CRGB crgbPulseColor         = CRGB(128, 128, 0);
  CRGB crgbCounterPulseColor  = CRGB(0, 0, 255);

  // Repeat Pulse
  intTm = 50; intDur = 4500; intSp = 1000; intCt = strip.led_count();

  //int intTm2Off = (intMid * intSp + intDur) /2;
  //int IntTrlDly = intDur*2/3;

  int amount = 3;
  int intMid = strip.led_count() / 2;
  int s = intMid / amount;

  int pos[amount];

  int sta, end = 0;

  int stas, ends = 0;
  int stae, ende = 0;

  for(int x = 0; x < amount; x++)
  {
    sta = (s * x);
    end = (s * x) + s;

    stas = strip.fs(0) + sta;
    ends = strip.fs(0) + end;
    stae = strip.fe(0) - sta;
    ende = strip.fe(0) - end;

    // Yellow Pulse and Counter Pulse
    teEvent[strip.intCHANNEL].set("Open Additional Anim", tmeCurrentTime, intTm, intDur, intSp, AnEvSweep, AnPiPulse, false, CRGB(0, 0, 0), crgbPulseColor, CRGB(0, 0, 0), CRGB(0, 0, 0), stas, ends, true, true);
    teEvent[strip.intCHANNEL].set("Open Additional Anim", tmeCurrentTime, intTm, intDur, intSp, AnEvSweep, AnPiPulse, true, CRGB(0, 0, 0), crgbCounterPulseColor, CRGB(0, 0, 0), CRGB(0, 0, 0), stas, ends, true, true);

    teEvent[strip.intCHANNEL].set("Open Additional Anim", tmeCurrentTime, intTm, intDur, intSp, AnEvSweep, AnPiPulse, false, CRGB(0, 0, 0), crgbPulseColor, CRGB(0, 0, 0), CRGB(0, 0, 0), stae, ende, true, true);
    teEvent[strip.intCHANNEL].set("Open Additional Anim", tmeCurrentTime, intTm, intDur, intSp, AnEvSweep, AnPiPulse, true, CRGB(0, 0, 0), crgbCounterPulseColor, CRGB(0, 0, 0), CRGB(0, 0, 0), stae, ende, true, true);
  }
}

// -------------------------------------------------------------------------------------

void vdAdditionalCloseADV00(Console &cons, v_profile_strip strip, timed_event teEvent[], unsigned long tmeCurrentTime)
// Turn (force) Additional Lights Off on a Strip
{
  show_anim_info(cons, strip, "Door Overhead Alert Off 00");

  // Seach the strip for light colors and set them to end after animation completes.  
  teEvent[strip.intCHANNEL].set("Open Additional Anim", tmeCurrentTime, 50, 1000, 80, AnEvSetToEnd, 0, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), strip.fs(0), strip.fe(0), true, true);
}




#endif