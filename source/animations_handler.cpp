// ***************************************************************************************
// *
// *    Core       | Everything within this document is proprietary to Core Dynamics.
// *    Dynamics   | Any unauthorized duplication will be subject to prosecution.
// *
// *    Department : (R+D)^2                        Name: animations_handler.cpp
// *       Sub Dept: Programming
// *    Location ID: 856-45B
// *                                                      (c) 2856 - 2858 Core Dynamics
// ***************************************************************************************

#ifndef ANIMATIONS_HANDLER_CPP
#define ANIMATIONS_HANDLER_CPP

#include "animations_handler.h"

// -------------------------------------------------------------------------------------
// 

void ANIMATION_HANDLER::create_events(system_data &sdSysData)
{
  int count = 0;

  for(int system = 0; system < sdSysData.CONFIG.LED_MAIN.size(); system++)
  {
    // For Every Strip in Group in System
    for(int group = 0; group < sdSysData.CONFIG.LED_MAIN[system].vLED_GROUPS.size(); group++)
    {
      // For Every Strip in Strip in Group
      for(int strip = 0; strip < sdSysData.CONFIG.LED_MAIN[system].vLED_GROUPS[group].vLED_STRIPS.size(); strip++)
      {
        timed_event tmp_event;
        EVENTS.push_back(tmp_event);

        EVENTS[count].create(sdSysData.CONFIG.LED_MAIN[system].vLED_GROUPS[group].vLED_STRIPS[strip].led_count());
        EVENTS[count].create(sdSysData.CONFIG.LED_MAIN[system].vLED_GROUPS[group].vLED_STRIPS[strip].intCHANNEL = count);
        count++;
      }
    }
  }

  sdSysData.CONFIG.CHANNELS = count;

}

bool ANIMATION_HANDLER::load_collections(string Directory, string Filename)
{
  return LIBRARY.load_collections(Directory, Filename);
}

void ANIMATION_HANDLER::call_animation(Console &cons, system_data &sdSysData, 
                    unsigned long tmeCurrentTime,                   
                    string Collection_Name, string Animation_Name)

{
  int collection_pos = 0;
  int animation_pos = 0;
  int channel = 0;

  collection_pos = LIBRARY.get_collection_pos(Collection_Name);
  animation_pos = LIBRARY.get_animation_pos(collection_pos, Animation_Name);

  // Determine which groups and strips to run on.

  sdSysData.ALERTS.add_generic_alert("Animation started");

  // For Every Event in storage Collection/Animation
  if (collection_pos > -1 && animation_pos > -1)
  {

    sdSysData.ALERTS.add_generic_alert("Animation found");

    for (int event = 0; 
        event < LIBRARY.COLLECTION[collection_pos].ANIMATIONS[animation_pos].EVENTS.size(); 
        event++)
    {
      sdSysData.ALERTS.add_generic_alert("Stepping trough events");

      // For Every System
      for(int system = 0; system < sdSysData.CONFIG.LED_MAIN.size(); system++)
      {

        sdSysData.ALERTS.add_generic_alert("Stepping trough Systems");

        // For Every Strip in Group in System
        for(int group = 0; group < sdSysData.CONFIG.LED_MAIN[system].vLED_GROUPS.size(); group++)
        {

          sdSysData.ALERTS.add_generic_alert("Stepping trough Groups");

          // For Every Strip in Strip in Group
          for(int strip = 0; strip < sdSysData.CONFIG.LED_MAIN[system].vLED_GROUPS[group].vLED_STRIPS.size(); strip++)
          {
            // Determine the event channel to receive the event.
            channel = sdSysData.CONFIG.LED_MAIN[system].vLED_GROUPS[group].vLED_STRIPS[strip].intCHANNEL;

            int from_start = sdSysData.CONFIG.LED_MAIN[system].vLED_GROUPS[group].vLED_STRIPS[strip].fs(0);
            int from_end = sdSysData.CONFIG.LED_MAIN[system].vLED_GROUPS[group].vLED_STRIPS[strip].fe(0);

            EVENTS[channel].set("Hazard", tmeCurrentTime, 1000, 500, 10, AnEvSweep, AnPiFadeDith, false, 
                                  CRGB(0, 0, 0), CRGB(64, 0, 0), CRGB(0, 0, 0), CRGB(0, 64, 0), 
                                  from_start, from_end, true, false, false);

            EVENTS[channel].set("Channel Light Pulse Color", tmeCurrentTime, 0, 0, 0, 
                                AnEvSchedule, AnTavdPowerAnimation, false, CRGB(35, 35, 35), 
                                CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), 0, 0, false, true, false);  

            sdSysData.ALERTS.add_generic_alert( to_string(EVENTS[channel].teDATA.size()) );
            
          }
        }
      }
    }
  }
  else
  {
    if (collection_pos == -1)
    {
      sdSysData.ALERTS.add_generic_alert("Colection not found (" + Collection_Name + ") Collection Size: " + 
                                          to_string(LIBRARY.COLLECTION.size()));
    }
    if (collection_pos > -1 && animation_pos == -1)
    {
      sdSysData.ALERTS.add_generic_alert("Animation not found (" + Collection_Name + ":" + Animation_Name + ") Animations Size: " + 
                                          to_string(LIBRARY.COLLECTION[collection_pos].ANIMATIONS.size()));

      sdSysData.ALERTS.add_generic_alert(" (" + LIBRARY.COLLECTION[collection_pos].ANIMATIONS[0].LABEL + ")");
    }
    
  }
}

#endif