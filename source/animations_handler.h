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
#include "LEDstuff.h"

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
  // Storage of all animations to be called.

  deque<SCHEDULED_THING_TO_MAKE_BETTER_WHEN_NEEDED> SCHEDULE_LIST;
  // Simple event list.

  void add_to_schedule_list(string Collection_Name, string Animation_Name, int Assigned_Group);
  // temporaryly stores events to be started after certain processes are complete.

  void EvClear(int Channel_Num, int Event_Num);
  // Erases all events.

  void EvClearRunning(int Channel_Num, int Event_Num, unsigned long tmeCurrentTime);
  // Sets specific event to complete

  void EvSetToEnd(int Channel_Num, int Event_Num, unsigned long tmeCurrentTime);
  // Set Event to End

  void EvSchedule(int Channel_Num, int Event_Num, unsigned long tmeCurrentTime);
  // Schedule new Event

  int determine_strip_animation(string Animation_Walk_Type);
  // Animation Walk Type:
  //  AnEvSweep
  //  AnEvClear
  //  AnEvClearRunning
  //  AnEvSchedule
  //  AnEvSetToEnd


  int determine_led_animation(string Animation_Of_LED);
  // LED Animation Type:
  //  AnPiFade
  //  AnPiFadeDith
  //  AnPiPulse
  //  AnPiPulseTo
  //  AnPiTwinkle - Doesnt Work

  int determine_led_pos(string LED_Position, v_profile_strip Strip_Info);
  // Returns abosolute LED pos value, or
  //  position from:
  //    from_start
  //    from_end
  //    from_top
  //    from_bot
  //    from_1/2
  //    from_1/3
  //    from_2/3
  //    from_1/4
  //    from_3/4
  //  All positions followed by |X where LED number of LEDs away from 

  CRGB determine_led_color(system_data &sdSysData, string Color_or_Var);
  // Returns either a sytem color:
  //  pulse color, countdown color, running color, pass trough color, 
  //  or string rgb color.

  public:

  deque<timed_event> EVENTS;

  void create_events(system_data &sdSysData);
  // Prepares the event system groups.  Must be ran before system accepts events.

  bool load_collections(string Directory, string Filename);
  // Load all animations json file into system memory, LIBRARY, to be duplicated, 
  //  duplicate modified, then duplicate called, when needed.

  void call_animation(system_data &sdSysData, unsigned long tmeCurrentTime,               
                      string Collection_Name, string Animation_Name, int On_Group, 
                      string String_Var_1, string String_Var_2);
  // Primary Call Animation Routine including all parameters
  //  sdSysData - System Data
  //  tmeCurrentTime - Time
  //  Collection_Name - json animations collection name
  //  Animation_Name  - json animations animation from collection
  //  On_Group        - -1 for all groups, or num for specific group
  //  String_Var_1    - For passing data, like collection name, to other events, via the json settings
  //  String_Var_2    - For passing data, like animation name, to other events, via the json settings

  void call_animation(system_data &sdSysData, unsigned long tmeCurrentTime,               
                      string Collection_Name, string Animation_Name);
  // Call Animation Routine with limited parameters
  //  sdSysData - System Data
  //  tmeCurrentTime - Time
  //  Collection_Name - json animations collection name
  //  Animation_Name  - json animations animation from collection
  //  Runs on all groups defined by the json

  void call_animation(system_data &sdSysData, unsigned long tmeCurrentTime,               
                      string Collection_Name, string Animation_Name,
                      int On_Group);
  // Call Animation Routine with limited parameters
  //  sdSysData - System Data
  //  tmeCurrentTime - Time
  //  Collection_Name - json animations collection name
  //  Animation_Name  - json animations animation from collection
  //  Runs on specific group

  void call_animation(system_data &sdSysData, unsigned long tmeCurrentTime,               
                      string Collection_Name, string Animation_Name, 
                      string String_Var_1, string String_Var_2);
  // Call Animation Routine with limited parameters
  //  sdSysData - System Data
  //  tmeCurrentTime - Time
  //  Collection_Name - json animations collection name
  //  Animation_Name  - json animations animation from collection
  //  Runs on all groups defined by the json
  //  String_Var_1    - For passing data, like collection name, to other events, via the json settings
  //  String_Var_2    - For passing data, like animation name, to other events, via the json settings

  void mod_run_anim_color_start_1(string Label, CRGB Color);
  // Search through active animations with Identity and change.

  void mod_run_anim_color_start_2(string Label, CRGB Color);
  // Search through active animations with Identity and change.
  
  void mod_run_anim_color_dest_1(string Label, CRGB Color);
  // Search through active animations with Identity and change.
  
  void mod_run_anim_color_dest_2(string Label, CRGB Color);
  // Search through active animations with Identity and change.
  
  void mod_run_anim_velocity(string Label, float Velocity);
  // Search through active animations with Identity and change.

  void process_events(system_data &sdSysData, unsigned long tmeCurrentTime);
  // Processes
  //  Event Clear
  //  Event Clear Running
  //  Schedule New Event
  //  Set Event To End
};


#endif