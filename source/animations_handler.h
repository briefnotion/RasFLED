// ***************************************************************************************
// *
// *    Core       | Everything within this document is proprietary to Core Dynamics.
// *    Dynamics   | Any unauthorized duplication will be subject to prosecution.
// *
// *    Department : (R+D)^2                        Name: animations_handler.h
// *       Sub Dept: Programming
// *    Location ID: 856-45B
// *                                                      (c) 2856 - 2858 Core Dynamics
// ***************************************************************************************

#ifndef ANIMATIONS_HANDLER_H
#define ANIMATIONS_HANDLER_H

// Standard Header Files
#include <string>
#include <deque>

// RASFled related header files
#include "animations_definitions.h"
#include "animations_storage.h"
#include "fledcore.h"

#include "consoleanddata.h"

// RASFled related header files

// -------------------------------------------------------------------------------------
// 

class ANIMATION_HANDLER
{
  private:

  class SCHEDULED_THING_TO_MAKE_BETTER_WHEN_NEEDED
  {
    public:
    string Collection_Name = "";  // Needed.
    string Animation_Name = "";   // Needed.  Only animations can be called.
    int Assigned_Group = -1;      // Not a parameter, will alwayays keep same 
                                  //  group/channel.
  };
  
  ANIMATIONS_STORAGE LIBRARY;

  deque<SCHEDULED_THING_TO_MAKE_BETTER_WHEN_NEEDED> SCHEDULE_LIST;

  void add_to_schedule_list(string Collection_Name, string Animation_Name, int Assigned_Group);

  void EvClear(int Channel_Num, int Event_Num);

  void EvClearRunning(int Channel_Num, int Event_Num, unsigned long tmeCurrentTime);

  void EvSetToEnd(int Channel_Num, int Event_Num, unsigned long tmeCurrentTime);

  void EvSchedule(int Channel_Num, int Event_Num, unsigned long tmeCurrentTime);

  int determine_strip_animation(string Animation_Walk_Type);

  int determine_led_animation(string Animation_Of_LED);

  int determine_led_pos(string LED_Position, v_profile_strip Strip_Info);

  CRGB determine_led_color(system_data &sdSysData, string Color_or_Var);

  public:

  deque<timed_event> EVENTS;

  void create_events(system_data &sdSysData);

  bool load_collections(string Directory, string Filename);

  void call_animation(system_data &sdSysData, unsigned long tmeCurrentTime,               
                      string Collection_Name, string Animation_Name, int On_Group, 
                      string String_Var_1, string String_Var_2);

  void call_animation(system_data &sdSysData, unsigned long tmeCurrentTime,               
                      string Collection_Name, string Animation_Name);

  void call_animation(system_data &sdSysData, unsigned long tmeCurrentTime,               
                      string Collection_Name, string Animation_Name,
                      int On_Group);

  void call_animation(system_data &sdSysData, unsigned long tmeCurrentTime,               
                      string Collection_Name, string Animation_Name, 
                      string String_Var_1, string String_Var_2);

  void process_events(system_data &sdSysData, unsigned long tmeCurrentTime);
};


#endif