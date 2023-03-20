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

  ANIMATIONS_STORAGE LIBRARY;

  public:

  deque<timed_event> EVENTS;

  int determine_strip_animation(string Animation_Walk_Type);

  int determine_led_animation(string Animation_Of_LED);

  int determine_led_pos(string LED_Position, v_profile_strip Strip_Info);

  void create_events(system_data &sdSysData);

  bool load_collections(string Directory, string Filename);

  void call_animation(Console &cons, system_data &sdSysData, unsigned long tmeCurrentTime,               
                      string Collection_Name, string Animation_Name);
  
  void process_events(unsigned long tmeCurrentTime);
};


#endif