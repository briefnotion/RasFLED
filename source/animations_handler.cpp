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

int ANIMATION_HANDLER::determine_strip_animation(string Animation_Walk_Type)
{
  int ret_stripanim = -1;

  if (Animation_Walk_Type == "AnEvSweep")
  {
    ret_stripanim =  AnEvSweep;
  }
  else if (Animation_Walk_Type == "AnEvClear")
  {
    ret_stripanim =  AnEvClear;
  }
  else if (Animation_Walk_Type == "AnEvClearRunning")
  {
    ret_stripanim =  AnEvClearRunning;
  }
  else if (Animation_Walk_Type == "AnEvSchedule")
  {
    ret_stripanim =  AnEvSchedule;
  }
  else if (Animation_Walk_Type == "AnEvSetToEnd")
  {
    ret_stripanim =  AnEvSetToEnd;
  }

  return ret_stripanim;
}

int ANIMATION_HANDLER::determine_led_animation(string Animation_Of_LED)
{
  int ret_ledanim = -1;

  if (Animation_Of_LED == "AnPiFade")
  {
    ret_ledanim =  AnPiFade;
  }
  else if (Animation_Of_LED == "AnPiFadeDith")
  {
    ret_ledanim =  AnPiFadeDith;
  }
  else if (Animation_Of_LED == "AnPiPulse")
  {
    ret_ledanim =  AnPiPulse;
  }
  else if (Animation_Of_LED == "AnPiPulseTo")
  {
    ret_ledanim =  AnPiPulseTo;
  }
  else if (Animation_Of_LED == "AnPiTwinkle")
  {
    ret_ledanim =  AnPiTwinkle;
  }

  return ret_ledanim;
}

int ANIMATION_HANDLER::determine_led_pos(string LED_Position, v_profile_strip Strip_Info)
{
  int ret_pos = -1;

  string left = "";
  string right = "";

  if (left_of_char(LED_Position, '|', left) == true)
  {
    if (left == "from_start")
    {
      if (right_of_char(LED_Position, '|', right) == true)
      {
        ret_pos = Strip_Info.fs(string_to_int(right));
      }
    }
    else if (left == "from_end")
    {
      if (right_of_char(LED_Position, '|', right) == true)
      {
        ret_pos = Strip_Info.fe(string_to_int(right));
      }
    }
  }
  else
  {
    ret_pos = string_to_int(LED_Position);
  }

  return ret_pos;
}

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
        sdSysData.CONFIG.LED_MAIN[system].vLED_GROUPS[group].vLED_STRIPS[strip].intCHANNEL = count;
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

  // For Every Event in storage Collection/Animation
  if (collection_pos > -1 && animation_pos > -1)
  {
    for (int event = 0; 
        event < LIBRARY.COLLECTION[collection_pos].ANIMATIONS[animation_pos].EVENTS.size(); 
        event++)
    {
      // For Every System
      for(int system = 0; system < sdSysData.CONFIG.LED_MAIN.size(); system++)
      {
        // For Every Strip in Group in System
        for(int group = 0; group < sdSysData.CONFIG.LED_MAIN[system].vLED_GROUPS.size(); group++)
        {
          // For Every Strip in Strip in Group
          for(int strip = 0; strip < sdSysData.CONFIG.LED_MAIN[system].vLED_GROUPS[group].vLED_STRIPS.size(); strip++)
          {
            // Determine the event channel to receive the event.
            channel = sdSysData.CONFIG.LED_MAIN[system].vLED_GROUPS[group].vLED_STRIPS[strip].intCHANNEL;

            string Label = LIBRARY.COLLECTION[collection_pos].ANIMATIONS[animation_pos].EVENTS[event].Label;;
            int Start_Delay_Time = LIBRARY.COLLECTION[collection_pos].ANIMATIONS[animation_pos].EVENTS[event].Start_Delay_Time;
            int Duration_Of_Brighness = LIBRARY.COLLECTION[collection_pos].ANIMATIONS[animation_pos].EVENTS[event].Duration_Of_Brighness;
            int Speed_Of_LED_Walk = LIBRARY.COLLECTION[collection_pos].ANIMATIONS[animation_pos].EVENTS[event].Speed_Of_LED_Walk;
            int Animation_Walk_Type = determine_strip_animation(LIBRARY.COLLECTION[collection_pos].ANIMATIONS[animation_pos].EVENTS[event].Animation_Walk_Type);
            int Animation_Of_LED = determine_led_animation(LIBRARY.COLLECTION[collection_pos].ANIMATIONS[animation_pos].EVENTS[event].Animation_Of_LED);          
            bool Invert_Color = LIBRARY.COLLECTION[collection_pos].ANIMATIONS[animation_pos].EVENTS[event].Invert_Color;
            CRGB Start_1 = LIBRARY.COLLECTION[collection_pos].ANIMATIONS[animation_pos].EVENTS[event].Start_1;
            CRGB Dest_1 = LIBRARY.COLLECTION[collection_pos].ANIMATIONS[animation_pos].EVENTS[event].Dest_1;
            CRGB Start_2 = LIBRARY.COLLECTION[collection_pos].ANIMATIONS[animation_pos].EVENTS[event].Start_2;
            CRGB Dest_2 = LIBRARY.COLLECTION[collection_pos].ANIMATIONS[animation_pos].EVENTS[event].Dest_2;
            int LED_Start_Pos = determine_led_pos(LIBRARY.COLLECTION[collection_pos].ANIMATIONS[animation_pos].EVENTS[event].LED_Start_Pos, 
                                                  sdSysData.CONFIG.LED_MAIN[system].vLED_GROUPS[group].vLED_STRIPS[strip]);
            int LED_End_Pos = determine_led_pos(LIBRARY.COLLECTION[collection_pos].ANIMATIONS[animation_pos].EVENTS[event].LED_End_Pos, 
                                                sdSysData.CONFIG.LED_MAIN[system].vLED_GROUPS[group].vLED_STRIPS[strip]);
            bool Repeat = LIBRARY.COLLECTION[collection_pos].ANIMATIONS[animation_pos].EVENTS[event].Repeat;
            bool Clear_On_End = LIBRARY.COLLECTION[collection_pos].ANIMATIONS[animation_pos].EVENTS[event].Clear_On_End;
            bool Off_During_Day = LIBRARY.COLLECTION[collection_pos].ANIMATIONS[animation_pos].EVENTS[event].Off_During_Day;

            EVENTS[channel].set(Label, tmeCurrentTime, Start_Delay_Time, Duration_Of_Brighness, Speed_Of_LED_Walk, 
                                Animation_Walk_Type, Animation_Of_LED, Invert_Color, 
                                Start_1, Dest_1, Start_2, Dest_2, 
                                LED_Start_Pos, LED_End_Pos, Repeat, Clear_On_End, Off_During_Day);



            //EVENTS[channel].set("Hazard", tmeCurrentTime, 100, 900, 0, AnEvSweep, AnPiPulse, false, CRGB(0, 0, 0), CRGB(128, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), from_start, from_end, false, true, false);


            //EVENTS[channel].set("Hazard", tmeCurrentTime, 100, 80, 10, AnEvSweep, AnPiPulse, false, CRGB(64, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), 
            //                      from_start, from_end, false, true, false);

            //sdSysData.ALERTS.add_generic_alert( to_string(EVENTS[channel].teDATA.size()) );
            
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

void ANIMATION_HANDLER::process_events(unsigned long tmeCurrentTime)
{
  for (int channel = 0; channel < EVENTS.size(); channel++)
  {
    for (int event = 0; event < EVENTS[channel].teDATA.size(); event++)
    {
      if (tmeCurrentTime >= EVENTS[channel].teDATA[event].tmeSTARTTIME && 
          EVENTS[channel].teDATA[event].booCOMPLETE == false)
      {
        switch (EVENTS[channel].teDATA[event].bytANIMATION)
        {
          
          // ---------------------------------------------------------------------------------------
          
          case AnEvClear:   // Clear all events, whether running or not, if event is within Start and End Position.
          {
              EVENTS[channel].teDATA[event].booCOMPLETE = true;
              EVENTS[channel].ClearAll(EVENTS[channel].teDATA[event].intSTARTPOS,
                                        EVENTS[channel].teDATA[event].intENDPOS);
            break;
          }

          // ---------------------------------------------------------------------------------------

          case AnEvClearRunning:  // Clear all active events if event is within Start and End Position.
          {                       // Possible problem if InTime is set to 0.
            EVENTS[channel].teDATA[event].booCOMPLETE = true;
            
            for (int eventscan = 0; eventscan < EVENTS[channel].teDATA.size(); eventscan++)
            {
              if(tmeCurrentTime >= EVENTS[channel].teDATA[eventscan].tmeSTARTTIME)
              {
                if( (is_within(  EVENTS[channel].teDATA[event].intSTARTPOS, 
                                  EVENTS[channel].teDATA[eventscan].intSTARTPOS, EVENTS[channel].teDATA[eventscan].intENDPOS))
                                    ||
                    (is_within(  EVENTS[channel].teDATA[event].intENDPOS, 
                                  EVENTS[channel].teDATA[eventscan].intSTARTPOS, EVENTS[channel].teDATA[eventscan].intENDPOS))  )
                {
                  if (event != eventscan)
                  {
                    EVENTS[channel].teDATA[eventscan].booCOMPLETE = true;
                  }
                }
              }
            }

            break;
          }

          // ---------------------------------------------------------------------------------------

          case AnEvSchedule:  //  Schedule an animation
          {

            break;
          }

          // ---------------------------------------------------------------------------------------

          case AnEvSetToEnd:  // Schedules an animation to end. Fades out and stops repeat on Pulses.
          {                   // Possible problem if InTime is set to 0.

            break;
          }

          // ---------------------------------------------------------------------------------------
        }
      }
    }
  }
}

#endif