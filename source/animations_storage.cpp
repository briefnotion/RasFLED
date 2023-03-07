// ***************************************************************************************
// *
// *    Core       | Everything within this document is proprietary to Core Dynamics.
// *    Dynamics   | Any unauthorized duplication will be subject to prosecution.
// *
// *    Department : (R+D)^2                        Name: animations_storage.cpp
// *       Sub Dept: Programming
// *    Location ID: 856-45B
// *                                                      (c) 2856 - 2858 Core Dynamics
// ***************************************************************************************

#ifndef ANIMATIONS_STORAGE_CPP
#define ANIMATIONS_STORAGE_CPP

#include "animations_storage.h"

// -------------------------------------------------------------------------------------
// Animations

void ANIMATION::add_event(ANIMATION_EVENT Event)
{
  EVENTS.push_back(Event);
}

int ANIMATIONS_LIST::find_pos_of_animation(string Label)
{
  int ret_pos = -1;

  for (int pos = 0; pos < LIST.size(); pos++)
  {
    if (LIST[pos].LABEL == Label)
    {
      ret_pos = pos;
    }
  }

  return ret_pos;
}

void ANIMATIONS_LIST::create_animation(string Label)
{
  ANIMATION tmp_animation;

  tmp_animation.LABEL = Label;

  LIST.push_back(tmp_animation);
}

void ANIMATIONS_LIST::add_event_to_animation(string Animation_Label, ANIMATION_EVENT Event)
{
  int pos = find_pos_of_animation(Animation_Label);

  if (pos > -1)
  {
    LIST[pos].add_event(Event);
  }
}

bool ANIMATIONS_LIST::load_animations(string Directory, string Filename)
{
  JSON_INTERFACE animations_json;

  bool ret_success = false;

  string str_animations_json = file_to_string(Directory + Filename, ret_success);
  
  if (ret_success == true)
  {
    ret_success = animations_json.load_json_from_string(str_animations_json);

    // Parse Animations and store into memory

    // Animations
    for (int animation = 0; animation < animations_json.ROOT.DATA.size(); animation++)
    {
      ANIMATION tmp_animation;
      tmp_animation.LABEL = animations_json.ROOT.DATA[animation].label();


      // Events
      for (int event = 0; event < animations_json.ROOT.DATA[animation].DATA.size(); event++)
      {
        ANIMATION_EVENT tmp_event;

        // Event items
        for (int item = 0; event < animations_json.ROOT.DATA[animation].DATA[event].DATA.size(); event++)
        {
          animations_json.ROOT.DATA[animation].DATA[event].get_if_is("Start_Delay_Time", tmp_event.Start_Delay_Time);
          animations_json.ROOT.DATA[animation].DATA[event].get_if_is("Duration_Of_Brighness", tmp_event.Start_Delay_Time);
          animations_json.ROOT.DATA[animation].DATA[event].get_if_is("Speed_Of_LED_Walk", tmp_event.Start_Delay_Time);
          animations_json.ROOT.DATA[animation].DATA[event].get_if_is("Animation_Walk_Type", tmp_event.Start_Delay_Time);
          animations_json.ROOT.DATA[animation].DATA[event].get_if_is("Animation_Of_LED", tmp_event.Start_Delay_Time);
          animations_json.ROOT.DATA[animation].DATA[event].get_if_is("Invert_Color", tmp_event.Start_Delay_Time);
          animations_json.ROOT.DATA[animation].DATA[event].get_if_is("Start_Pos_Start_Color", tmp_event.Start_Delay_Time);
          animations_json.ROOT.DATA[animation].DATA[event].get_if_is("End_Pos_Start_Color", tmp_event.Start_Delay_Time);
          animations_json.ROOT.DATA[animation].DATA[event].get_if_is("Start_Pos_End_Color", tmp_event.Start_Delay_Time);
          animations_json.ROOT.DATA[animation].DATA[event].get_if_is("End_Pos_End_Color", tmp_event.Start_Delay_Time);
          animations_json.ROOT.DATA[animation].DATA[event].get_if_is("LED_Start_Pos", tmp_event.Start_Delay_Time);
          animations_json.ROOT.DATA[animation].DATA[event].get_if_is("LED_End_Pos", tmp_event.Start_Delay_Time);
          animations_json.ROOT.DATA[animation].DATA[event].get_if_is("Repeat", tmp_event.Start_Delay_Time);
          animations_json.ROOT.DATA[animation].DATA[event].get_if_is("Clear_On_End", tmp_event.Start_Delay_Time);
          animations_json.ROOT.DATA[animation].DATA[event].get_if_is("Off_During_Day", tmp_event.Start_Delay_Time);
        }
      
        tmp_animation.EVENTS.push_back(tmp_event);

      }

      LIST.push_back(tmp_animation);

    }
  }

  return ret_success;
}



#endif