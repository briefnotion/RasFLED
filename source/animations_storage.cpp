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

bool ANIMATIONS_STORAGE::load_collections(string Directory, string Filename)
{
  JSON_INTERFACE animations_json;

  bool ret_success = false;

  string str_animations_json = file_to_string(Directory + Filename, ret_success);

  if (ret_success == true)
  {
    ret_success = animations_json.load_json_from_string(str_animations_json);

    // Clear current animations
    COLLECTION.clear();

    // Parse Animations and store into memory

    // Collections
    for (int collection = 0; collection < animations_json.ROOT.DATA.size(); collection++)
    {

      ANIMATIONS_COLLECTION tmp_collection;
      tmp_collection.LABEL = animations_json.ROOT.DATA[collection].label();

      // Animations
      for (int animation = 0; animation < animations_json.ROOT.DATA[collection].DATA[0].DATA.size(); animation++)
      {
        ANIMATIONS_ANIMATION tmp_animation;
        tmp_animation.LABEL = animations_json.ROOT.DATA[collection].DATA[0].DATA[animation].label();

        // Events
        for (int event = 0; event < animations_json.ROOT.DATA[collection].DATA[0].DATA[animation].DATA.size(); event++)
        {
          ANIMATIONS_EVENT tmp_event;
          // Event items
          for (int item = 0; item < animations_json.ROOT.DATA[collection].DATA[0].DATA[animation].DATA[event].DATA.size(); item++)
          {
            // Run on conditions
            animations_json.ROOT.DATA[collection].DATA[0].DATA[animation].DATA[event].DATA[item].get_if_is("Run_On_LED_Strip_ID", tmp_animation.Run_On_LED_Strip_ID);
            animations_json.ROOT.DATA[collection].DATA[0].DATA[animation].DATA[event].DATA[item].get_if_is("Run_On_LED_LED_Strip_Name", tmp_animation.Run_On_LED_LED_Strip_Name);
            animations_json.ROOT.DATA[collection].DATA[0].DATA[animation].DATA[event].DATA[item].get_if_is("Run_On_Position", tmp_animation.Run_On_Position);

            // Event details
            animations_json.ROOT.DATA[collection].DATA[0].DATA[animation].DATA[event].DATA[item].get_if_is("Label", tmp_event.Label);
            animations_json.ROOT.DATA[collection].DATA[0].DATA[animation].DATA[event].DATA[item].get_if_is("Start_Delay_Time", tmp_event.Start_Delay_Time);
            animations_json.ROOT.DATA[collection].DATA[0].DATA[animation].DATA[event].DATA[item].get_if_is("Duration_Of_Brighness", tmp_event.Duration_Of_Brighness);
            animations_json.ROOT.DATA[collection].DATA[0].DATA[animation].DATA[event].DATA[item].get_if_is("Speed_Of_LED_Walk", tmp_event.Speed_Of_LED_Walk);
            animations_json.ROOT.DATA[collection].DATA[0].DATA[animation].DATA[event].DATA[item].get_if_is("Animation_Walk_Type", tmp_event.Animation_Walk_Type);
            animations_json.ROOT.DATA[collection].DATA[0].DATA[animation].DATA[event].DATA[item].get_if_is("Animation_Of_LED", tmp_event.Animation_Of_LED);
            animations_json.ROOT.DATA[collection].DATA[0].DATA[animation].DATA[event].DATA[item].get_if_is("Invert_Color", tmp_event.Invert_Color);
            animations_json.ROOT.DATA[collection].DATA[0].DATA[animation].DATA[event].DATA[item].get_if_is("Start_1", tmp_event.Start_1);
            animations_json.ROOT.DATA[collection].DATA[0].DATA[animation].DATA[event].DATA[item].get_if_is("Dest_1", tmp_event.Dest_1);
            animations_json.ROOT.DATA[collection].DATA[0].DATA[animation].DATA[event].DATA[item].get_if_is("Start_2", tmp_event.Start_2);
            animations_json.ROOT.DATA[collection].DATA[0].DATA[animation].DATA[event].DATA[item].get_if_is("Dest_2", tmp_event.Dest_2);
            animations_json.ROOT.DATA[collection].DATA[0].DATA[animation].DATA[event].DATA[item].get_if_is("LED_Start_Pos", tmp_event.LED_Start_Pos);
            animations_json.ROOT.DATA[collection].DATA[0].DATA[animation].DATA[event].DATA[item].get_if_is("LED_End_Pos", tmp_event.LED_End_Pos);
            animations_json.ROOT.DATA[collection].DATA[0].DATA[animation].DATA[event].DATA[item].get_if_is("Repeat", tmp_event.Repeat);
            animations_json.ROOT.DATA[collection].DATA[0].DATA[animation].DATA[event].DATA[item].get_if_is("Clear_On_End", tmp_event.Clear_On_End);
            animations_json.ROOT.DATA[collection].DATA[0].DATA[animation].DATA[event].DATA[item].get_if_is("Off_During_Day", tmp_event.Off_During_Day);
            animations_json.ROOT.DATA[collection].DATA[0].DATA[animation].DATA[event].DATA[item].get_if_is("String_Var_1", tmp_event.String_Var_1);
            animations_json.ROOT.DATA[collection].DATA[0].DATA[animation].DATA[event].DATA[item].get_if_is("String_Var_2", tmp_event.String_Var_2);

            animations_json.ROOT.DATA[collection].DATA[0].DATA[animation].DATA[event].DATA[item].get_if_is("Velocity", tmp_event.Velocity);
          }
        
          tmp_animation.EVENTS.push_back(tmp_event);

        }

        tmp_collection.ANIMATIONS.push_back(tmp_animation);

      }

      COLLECTION.push_back(tmp_collection);

    }

  }
  
  return ret_success;
}

int ANIMATIONS_STORAGE::get_collection_pos(string Name)
{
  int ret_pos = -1;

  for (int pos = 0; pos < COLLECTION.size() && ret_pos == -1; pos++)
  {
    if (COLLECTION[pos].LABEL == Name)
    {
      ret_pos = pos;
    }
  }

  return ret_pos;
}

int ANIMATIONS_STORAGE::get_animation_pos(int Collection_Pos ,string Name)
{
  int ret_pos = -1;

  for (int pos = 0; pos < COLLECTION[Collection_Pos].ANIMATIONS.size() && ret_pos == -1; pos++)
  {
    if (COLLECTION[Collection_Pos].ANIMATIONS[pos].LABEL == Name)
    {
      ret_pos = pos;
    }
  }

  return ret_pos;
}



#endif