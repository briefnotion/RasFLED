// ***************************************************************************************
// *
// *    Core       | Everything within this document is proprietary to Core Dynamics.
// *    Dynamics   | Any unauthorized duplication will be subject to prosecution.
// *
// *    Department : (R+D)^2                        Name: fledcore.h
// *       Sub Dept: Programming
// *    Location ID: 856-45B
// *                                                      (c) 2856 - 2858 Core Dynamics
// ***************************************************************************************

#ifndef FLEDCORE_H
#define FLEDCORE_H

#include "animations_definitions.h"

// Standard Header Files
#include <deque>

#include "LEDstuff.h"
#include "consoleanddata.h"


// ***************************************************************************************
// STRUCTURES AND CLASSES
// ***************************************************************************************

// -------------------------------------------------------------------------------------
// LedStrip Structures 

/*
// Defines a basic LED Strip
class led_strip
{
  public:
  int Cl = 0; // Channel
  int St = 0; // Start Led Pos
  int Ed = 0; // End Led Pos
  int AnimationStatus = 0;

  void set(int intChannel, int intStart, int intEnd)
  {
    Cl = intChannel;
    St = intStart;
    Ed = intEnd;
  }

  int Ct()
  {
    int count;
    return Ed - St + 1;
  }
};
*/


// -------------------------------------------------------------------------------------
// Timed Event Data Variable

class timed_event_data
// Varibles to control the timed_event.
{
  public:
  // standard attributes defined by json
  std::string strIdent = "";
  unsigned long tmeSTARTTIME = 0;
  int intDURATION = 0;
  int intSPEED= 0;
  char  bytANIMATION = 0;
  char  bytLEDANIMATION = 0;
  CRGB crgbCOLORSTART1 = CRGB(0,0,0);
  CRGB crgbCOLORSTART2 = CRGB(0,0,0);
  CRGB crgbCOLORDEST1 = CRGB(0,0,0);
  CRGB crgbCOLORDEST2 = CRGB(0,0,0);
  int  intSTARTPOS = 0;
  int  intENDPOS = 0;
  bool booINVERTCOLOR = false;
  bool booREPEAT = false;
  bool booCLEARONEND = true;
  bool booOFFDURINGDAY = false;
  string String_Var_1 = "";
  string String_Var_2 = "";
  int Assigned_Group = -1;

  // Velocity
  bool VELOCITY = false;
  float VELOCITY_VALUE = 0;
  unsigned long PREV_TIME_STAMP = 0;

  bool booCOMPLETE = true;


  void PostCheck(unsigned long tmeCurrent);
};


// -------------------------------------------------------------------------------------
// Timed Event Variable

class timed_event
//  Create a Timed LED Event:
//    Controls when a group of LEDs are to begin their individual light path animation.
//    If an event is over written the previous animation will be lost.
{
  public:
  std::deque<timed_event_data> teDATA;
  int      intLEDCOUNT;

  void create(int intLedCount);

  void set(std::string strIdentity, unsigned long tmeCurrentTime,
           int tmeStartInTime, int intDuration, int intSpeed, 
           char  bytAnimation, char  bytLEDAnimation, bool booInvertColor, 
           CRGB crgbStart1, CRGB crgbDest1, CRGB crgbStart2, CRGB crgbDest2, 
           int intStartPos, int intEndPos, bool booRepeat, bool booClearOnEnd,
           bool booOffDuringDay, string String_Var_1, string String_Var_2, int Assigned_Group);

  void set_timed_event(timed_event_data newteDATA);

  // -------------------------------------------------------------------------------------
  // Clear events in channel

  void ClearAll(int intStartPos, int intEndPos);

  // -------------------------------------------------------------------------------------
  // Timed Event LED Animations

  bigCRGB crgb_anim_color(stupid_random sRND, unsigned long tmeCurrentTime, unsigned long tmeAnimTime,
                          int intLED, int intEvent, timed_event_data &EventInfo);

  // -------------------------------------------------------------------------------------

  void process_led_light(int &led, timed_event_data &teDATA, system_data &sdSysData, stupid_random &sRND, unsigned long &tmeCurrentTime, 
                          bigCRGB bigcrgbNewColor[], bool &booEventComplete, bool &booPixelColorChanged); // return

  bool execute2(Console &cons, system_data &sdSysData, stupid_random sRND, CRGB hwLEDArray[], unsigned long tmeCurrentTime);
};



#endif