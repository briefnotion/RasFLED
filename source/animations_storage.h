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
#include "definitions.h"
#include "helper.h"
#include "consoleanddata.h"
#include "fledcore.h"
#include "json_interface.h"
#include "LEDstuff.h"

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

  bool load_animations(string Directory, string Filename);
};




#endif