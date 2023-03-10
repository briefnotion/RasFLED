// ***************************************************************************************
// *
// *    Core       | Everything within this document is proprietary to Core Dynamics.
// *    Dynamics   | Any unauthorized duplication will be subject to prosecution.
// *
// *    Department : (R+D)^2                        Name: animations_storage.h
// *       Sub Dept: Programming
// *    Location ID: 856-45B
// *                                                      (c) 2856 - 2858 Core Dynamics
// ***************************************************************************************

#ifndef ANIMATIONS_STORAGE_H
#define ANIMATIONS_STORAGE_H

// Standard Header Files
#include <string>
#include <deque>

// RASFled related header files
#include "helper.h"
#include "json_interface.h"
#include "LEDstuff.h"

// -------------------------------------------------------------------------------------
// Animations

class ANIMATIONS_EVENT
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
  CRGB Start_Pos_Start_Color;
  CRGB End_Pos_Start_Color;
  CRGB Start_Pos_End_Color;
  CRGB End_Pos_End_Color;
  int LED_Start_Pos = 0;
  int LED_End_Pos = 0;
  bool Repeat = false;
  bool Clear_On_End = false;
  bool Off_During_Day = false;
};

class ANIMATIONS_ANIMATION
{
  public:

  string LABEL = "";
  deque<ANIMATIONS_EVENT> EVENTS;
};

class ANIMATIONS_COLLECTION
{
  public:

  string LABEL = "";
  deque<ANIMATIONS_ANIMATION> ANIMATIONS;
};

class ANIMATIONS_STORAGE
{
  private:

  deque<ANIMATIONS_COLLECTION> COLLECTION;

  public:

  bool load_collections(string Directory, string Filename);
};




#endif