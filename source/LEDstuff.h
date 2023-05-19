// ***************************************************************************************
// *
// *    Core       | Everything within this document is proprietary to Core Dynamics.
// *    Dynamics   | Any unauthorized duplication will be subject to prosecution.
// *
// *    Department : (R+D)^2                        Name: LEDstuff.h
// *       Sub Dept: Programming
// *    Location ID: 856-45B
// *                                                      (c) 2856 - 2858 Core Dynamics
// ***************************************************************************************

#ifndef LEDSTUFF_H
#define LEDSTUFF_H

// Standard Header Files
#include <string>
#include <deque>

#include "helper.h"
#include "stringthings.h"

using namespace std;

// ***************************************************************************************
// STRUCTURES AND CLASSES
// ***************************************************************************************

// -------------------------------------------------------------------------------------
// Color class RGB byte, byte, byte

class CRGB
// RGB varible.
{
public: 
  char r = 0;
  char g = 0;
  char b = 0;

  CRGB();
  
  // cRGB override for passing non varible to varible. 
  CRGB(char R,char G,char B);
  
  //Compare two cRGB values.
  bool operator== (CRGB color);

  string CRGBtoString();

  CRGB StringtoCRGB(string strCRGB);
  
  CRGB brightness(float Multiplier);

};

class bigCRGB
// Color class RGB int, int, int

// This color class is used for preprocessing byte RGB values so computation can be 
// negative or more than 256.  Not displayable but useful in calculations.
{
  public:
  int r = 0;
  int g = 0;
  int b = 0;
  bool complete = true;
};

// -------------------------------------------------------------------------------------
// Strip Variable Containers
//  - Set commands are unnecessay and can be atted to the "add_###" commands in the 
//      future

// LED Strip
class v_profile_strip
{
  private:

  int intLED_COUNT      = 0;

  public:

  int     intID         = 0;
  string  strNAME       = "";
  string  strPOSITION   = "";

  bool booFORWARD       = true;
  bool booBOT_AT_START  = true;

  CRGB *crgbARRAY;
  bool booARRAY_UPDATED = false;

  int intLED_START_POS  = 0;

  string Status         = "";
  int intCHANNEL = 0;

  // -------------------------------------------------------------------------------------

  void set(int intId, string strName, string strPosition, int intStart_Pos, bool forward, bool bot_at_start);

  void create(int size);

  int led_count();
  int fs(int pos);
  
  int fe(int pos);

  int fb(int pos);

  int ft(int pos);

  bool position(string position);
};

// LED Strip Group
class v_profile_strip_group
{
  private:

  int intLED_COUNT        = 0;

  public:

  int intID               = 0;
  string strNAME          = "";

  int intGROUP_START_POS  = 0;
  string Status         = "";

  deque<v_profile_strip>  vLED_STRIPS;

  int find(string strName);

  string status(string strName);

  void status_set(string strName, string strStatus);

  void set(int intId, string strName, int intStart_Pos);

  int led_count();

  void add_strip(int intID, string strName, string strPosition, int size, bool forward, bool bot_at_start);
};

// LED Main Container
class v_profile_strip_main
{
  private:

  stupid_2d GROUP_MAP;

  public:

  int intID         = 0;
  string strNAME    = "";

  int int_START_POS = 0;
  deque<v_profile_strip_group> vLED_GROUPS;

  int g_size();           // not needed

  int s_size(int group);  // not needed

  int led_count();

  void set(int intId, string strName);

  void add_group(int intId, string strName);

  void update_start_positions();

  v_profile_strip strip_info(int intGroup, int intStrip);
};



// ***************************************************************************************
// FUNCTION AND PROCEDURES
// ***************************************************************************************


// -------------------------------------------------------------------------------------
// Common routines to find pixel color values from 2 seperate pixel colors.

// Compute from Power of pixel with from time start to time end.
float ComputePower(float fltElapsed, float FltDuration);

// Compute from Power of pixel with from time start to time end.
//  For pixels that are split to behave differently on first half of time.
//  Compute First half or Bottom half value.
float ComputePowerHalfBot(float fltElapsed, float FltDuration);

// Compute from Power of pixel with from time start to time end.
//  For pixels that are split to behave differently on first half of time.
//  Compute Second half or Top half value.
float ComputePowerHalfTop(float fltElapsed, float FltDuration);

// Merge two pixel colors based on Power.  Returns the bigCRGB value from CRGB.
bigCRGB Dither(float fltPower, CRGB crgbColor1, CRGB crgbColor2);         

// Merge two pixel colors based on Power.  Returns the bigCRGB value from CRGB.
CRGB DitherSmall(float fltPower, CRGB crgbColor1, CRGB crgbColor2);  



#endif