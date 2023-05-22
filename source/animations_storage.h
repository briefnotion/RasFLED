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

// Guide: (tmeCurrentTime, tmeStartInTime, intDuration, intSpeed, bytAnimation, bytLEDAnimation, 
//          crgbStart1, crgbDest1, crgbStart2, crgbDest2, intStartPos, intEndPos, booRepeat, booClearOnEnd, )

class ANIMATIONS_EVENT
{
  public:

  string Label;
  unsigned long Current_Time = 0;
  int Start_Delay_Time = 0;
  int Duration_Of_Brighness = 0;
  int Speed_Of_LED_Walk = 100;
  string Animation_Walk_Type = "";
  string Animation_Of_LED = "";
  bool Invert_Color = false;
  string Start_1 = "0,0,0";
  string Dest_1 = "0,0,0";
  string Start_2 = "0,0,0";
  string Dest_2 = "0,0,0";
  string LED_Start_Pos = "from_start|0";
  string LED_End_Pos = "from_end|0";
  bool Repeat = false;
  bool Clear_On_End = true;
  bool Off_During_Day = false;
  string String_Var_1 = "";
  string String_Var_2 = "";

  // Velocity
  bool Velocity = false;
  
  //  Extra carry over info
  int Assigned_Group = -1;
};

class ANIMATIONS_ANIMATION
{
  public:

  string LABEL = "";

  int Run_On_LED_Strip_ID = -1;
  string Run_On_LED_LED_Strip_Name = "";
  string Run_On_Position = "";
  string Run_On_LED_Direction = "";
  string Run_On_LED_Type = "";

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

  public:

  deque<ANIMATIONS_COLLECTION> COLLECTION;

  bool load_collections(string Directory, string Filename);

  int get_collection_pos(string Name);

  int get_animation_pos(int Collection_Pos ,string Name);
};




#endif