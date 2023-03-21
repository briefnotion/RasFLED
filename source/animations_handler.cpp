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

void ANIMATION_HANDLER::add_to_schedule_list(string Collection_Name, string Animation_Name)
{
  bool found = false;

  for(int pos = 0; pos < SCHEDULE_LIST.size() && found == false; pos ++)
  {
    if (SCHEDULE_LIST[pos].Collection_Name == Collection_Name &&
        SCHEDULE_LIST[pos].Animation_Name == Animation_Name)
    {
      found = true;
    }
  }

  if (found == false)
  {
    SCHEDULED_THING_TO_MAKE_BETTER_WHEN_NEEDED new_thing;
    new_thing.Collection_Name = Collection_Name;
    new_thing.Animation_Name = Animation_Name;
    SCHEDULE_LIST.push_back(new_thing);
  }
}

void ANIMATION_HANDLER::EvClear(int Channel_Num, int Event_Num)
{
  EVENTS[Channel_Num].teDATA[Event_Num].booCOMPLETE = true;
  EVENTS[Channel_Num].ClearAll(EVENTS[Channel_Num].teDATA[Event_Num].intSTARTPOS,
                            EVENTS[Channel_Num].teDATA[Event_Num].intENDPOS);
}

void ANIMATION_HANDLER::EvClearRunning(int Channel_Num, int Event_Num, unsigned long tmeCurrentTime)
{
  EVENTS[Channel_Num].teDATA[Event_Num].booCOMPLETE = true;
            
  for (int eventscan = 0; eventscan < EVENTS[Channel_Num].teDATA.size(); eventscan++)
  {
    if(tmeCurrentTime >= EVENTS[Channel_Num].teDATA[eventscan].tmeSTARTTIME)
    {
      if( (is_within(  EVENTS[Channel_Num].teDATA[Event_Num].intSTARTPOS, 
                        EVENTS[Channel_Num].teDATA[eventscan].intSTARTPOS, EVENTS[Channel_Num].teDATA[eventscan].intENDPOS))
                          ||
          (is_within(  EVENTS[Channel_Num].teDATA[Event_Num].intENDPOS, 
                        EVENTS[Channel_Num].teDATA[eventscan].intSTARTPOS, EVENTS[Channel_Num].teDATA[eventscan].intENDPOS))  )
      {
        if (Event_Num != eventscan)
        {
          EVENTS[Channel_Num].teDATA[eventscan].booCOMPLETE = true;
        }
      }
    }
  }
}

void ANIMATION_HANDLER::EvSetToEnd(int Channel_Num, int Event_Num, unsigned long tmeCurrentTime)
{
  //cons.printwait("Event: AnEvSetToEnd");
  // Clear the Event whether the event ran or not.
  EVENTS[Channel_Num].teDATA[Event_Num].booCOMPLETE = true;   

  // Step through each event in this channel. 
  for (int eventscan = 0; eventscan < EVENTS[Channel_Num].teDATA.size(); eventscan++)
  {
    // Has the event started running yet, or do we plan on ending future scheduled events also?
    //  Continue with event removal if (event is active) or (clear on end is true)
    if((EVENTS[Channel_Num].teDATA[eventscan].tmeSTARTTIME <= tmeCurrentTime) || (EVENTS[Channel_Num].teDATA[Event_Num].booCLEARONEND == true))
    {
      // is the event we are currently looking at within, or overlapping, the targeted event range.
      if (  ((EVENTS[Channel_Num].teDATA[eventscan].intSTARTPOS >= EVENTS[Channel_Num].teDATA[Event_Num].intSTARTPOS)  
            && (EVENTS[Channel_Num].teDATA[eventscan].intSTARTPOS <= EVENTS[Channel_Num].teDATA[Event_Num].intENDPOS))
                  ||
            ((EVENTS[Channel_Num].teDATA[eventscan].intENDPOS >= EVENTS[Channel_Num].teDATA[Event_Num].intSTARTPOS)  
            && (EVENTS[Channel_Num].teDATA[eventscan].intENDPOS <= EVENTS[Channel_Num].teDATA[Event_Num].intENDPOS))  )
      {
        bool cont = false;  // Continue with the event removal process.

        bool booCheckColor = true;
        bool booCheckIdent = true;

        // Are we targeting only specific events to end or all events.

        // Check for specific Targeted Color or Targeted Identifier.  
        // We are targeting events with any color by passing CRGB(0,0,0), and any Identifier by passing "" 
        // continue on.

        // Warning: This is not an AND condition, even though it probably should be. Not needed at this time 
        //            so I didn't implement it.  There are just too many other things to do.

        // Figure out what we are checking.
        if (EVENTS[Channel_Num].teDATA[Event_Num].crgbCOLORSTART1 == CRGB(0,0,0))
        {
          booCheckColor = false;
        }
        if (EVENTS[Channel_Num].teDATA[Event_Num].strIdent == "")
        {
          booCheckIdent = false;
        }

        // Look for matches
        if ((booCheckColor == false) && (booCheckIdent == false))
        {
          // Nothing targeted. Continue with STE.
          cont = true;
        }
        else if (booCheckColor == true)
        {
          //We are only targeting events with specific color.  Need a match on any.
          if (EVENTS[Channel_Num].teDATA[Event_Num].crgbCOLORSTART1 == EVENTS[Channel_Num].teDATA[eventscan].crgbCOLORSTART1)
          {
            cont = true;
          }
          else if (EVENTS[Channel_Num].teDATA[Event_Num].crgbCOLORSTART1 == EVENTS[Channel_Num].teDATA[eventscan].crgbCOLORSTART2)
          {
            cont = true;
          }
          else if (EVENTS[Channel_Num].teDATA[Event_Num].crgbCOLORSTART1 == EVENTS[Channel_Num].teDATA[eventscan].crgbCOLORDEST1)
          {
            cont = true;
          }
          else if (EVENTS[Channel_Num].teDATA[Event_Num].crgbCOLORSTART1 == EVENTS[Channel_Num].teDATA[eventscan].crgbCOLORDEST2)
          {
            cont = true;
          }
        }
        else if (booCheckIdent == true)
        {
          //We are only targeting events with specific Identification.  Need a match on any.
          if (EVENTS[Channel_Num].teDATA[Event_Num].String_Var_1 == EVENTS[Channel_Num].teDATA[eventscan].strIdent)
          {
            cont = true;
          }
        }

        // Only continue with setting the event to end if it passed the above criteria.
        if (cont == true)
        {
          // If the event hasn't started yet, set it to complete.
          // *********

          // Check the event we are stopping to make sure its not the event calling the SetToEnd.
          if (Event_Num != eventscan)
          {

            // End Animations

            // Manage the Fade Animations to End.
            if (  (EVENTS[Channel_Num].teDATA[eventscan].bytLEDANIMATION == AnPiFade)     ||
                  (EVENTS[Channel_Num].teDATA[eventscan].bytLEDANIMATION == AnPiFadeDith)  )
            {
              // Stop the event.
              EVENTS[Channel_Num].teDATA[eventscan].booREPEAT = false;
              EVENTS[Channel_Num].teDATA[eventscan].booCLEARONEND = true;
              
              EVENTS[Channel_Num].teDATA[eventscan].intDURATION = EVENTS[Channel_Num].teDATA[Event_Num].intDURATION;
              EVENTS[Channel_Num].teDATA[eventscan].tmeSTARTTIME = tmeCurrentTime;

              //EVENTS[channel].teDATA[eventscan].intSPEED =  EVENTS[channel].teDATA[Event_Num].intSPEED;
              EVENTS[Channel_Num].teDATA[eventscan].intSPEED =  0;
              // The above two lines will need to be addressed at a future date. 
              //  Problem occurs when an event current time is before the start 
              //  pixel update begins. This mean that the start color will not be set until current 
              //  time is past start time.  Need to choose: apples or oranges during 
              //  the crgb_anim_color and event routine.

              if (EVENTS[Channel_Num].teDATA[Event_Num].booREPEAT == false)
              {
                EVENTS[Channel_Num].teDATA[eventscan].crgbCOLORSTART1 = EVENTS[Channel_Num].teDATA[eventscan].crgbCOLORDEST1;
                EVENTS[Channel_Num].teDATA[eventscan].crgbCOLORSTART2 = EVENTS[Channel_Num].teDATA[eventscan].crgbCOLORDEST2;
              }
              else
              {
                EVENTS[Channel_Num].teDATA[eventscan].crgbCOLORSTART1 = EVENTS[Channel_Num].teDATA[eventscan].crgbCOLORDEST1;
                EVENTS[Channel_Num].teDATA[eventscan].crgbCOLORSTART2 = EVENTS[Channel_Num].teDATA[eventscan].crgbCOLORDEST2;
                EVENTS[Channel_Num].teDATA[eventscan].crgbCOLORDEST1 = EVENTS[Channel_Num].teDATA[Event_Num].crgbCOLORDEST1;
                EVENTS[Channel_Num].teDATA[eventscan].crgbCOLORDEST2 = EVENTS[Channel_Num].teDATA[Event_Num].crgbCOLORDEST2;
              }
            }

            // and
            // End Pusles

            // Manage the Pulse Animations to End
            if (  (EVENTS[Channel_Num].teDATA[eventscan].bytLEDANIMATION == AnPiPulse)    ||
                  (EVENTS[Channel_Num].teDATA[eventscan].bytLEDANIMATION == AnPiPulseTo)  )
            {
              // Tell the pulse to stop.
              if (EVENTS[Channel_Num].teDATA[Event_Num].booREPEAT == false)
              {
                // For now, we will just kill it and hope another animation clears the artifacts.
                // It would be nice to have a gracreful end and let the pixel end its animation,
                // but, thats for another time.
                
                // Stop the event.
                EVENTS[Channel_Num].teDATA[eventscan].booREPEAT = false;
                EVENTS[Channel_Num].teDATA[eventscan].booCLEARONEND = true;
                
                EVENTS[Channel_Num].teDATA[eventscan].booCOMPLETE = true;
              }
              else
              {
                // Pulse will end on its on at end of animation.
                EVENTS[Channel_Num].teDATA[eventscan].booREPEAT = false;
                EVENTS[Channel_Num].teDATA[eventscan].booCLEARONEND = true;
              }
            }

            // and
            // End Scheduled Events

            if (EVENTS[Channel_Num].teDATA[eventscan].bytANIMATION == AnEvSchedule)
            {
              // Stop the event.
              EVENTS[Channel_Num].teDATA[eventscan].booREPEAT = false;
              EVENTS[Channel_Num].teDATA[eventscan].booCLEARONEND = true;

              EVENTS[Channel_Num].teDATA[eventscan].booCOMPLETE = true;
            }

          } // End Event not Self 
        } // End If Event in Search Criteria
      } // End If Event in Range
    } // End If Time Start
  } // End For Event Check  
}

void ANIMATION_HANDLER::EvSchedule(int Channel_Num, int Event_Num, unsigned long tmeCurrentTime)
{
  // Clear the Event whether the event ran or not.
  if(EVENTS[Channel_Num].teDATA[Event_Num].booREPEAT == false)
  {
    EVENTS[Channel_Num].teDATA[Event_Num].booCOMPLETE = true;
  }
  else
  {
    EVENTS[Channel_Num].teDATA[Event_Num].tmeSTARTTIME = tmeCurrentTime + 
    EVENTS[Channel_Num].teDATA[Event_Num].intDURATION;
  }

  add_to_schedule_list(EVENTS[Channel_Num].teDATA[Event_Num].String_Var_1, 
                        EVENTS[Channel_Num].teDATA[Event_Num].String_Var_2);
}

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

void ANIMATION_HANDLER::call_animation(system_data &sdSysData, 
                    unsigned long tmeCurrentTime, 
                    string Collection_Name, string Animation_Name)

{
  int collection_pos = -1;
  int animation_pos = -1;
  int channel = 0;

  collection_pos = LIBRARY.get_collection_pos(Collection_Name);
  if(collection_pos > -1)
  {
    animation_pos = LIBRARY.get_animation_pos(collection_pos, Animation_Name);
  }

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

            string Label = LIBRARY.COLLECTION[collection_pos].ANIMATIONS[animation_pos].EVENTS[event].Label;
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
            string String_Var_1 = LIBRARY.COLLECTION[collection_pos].ANIMATIONS[animation_pos].EVENTS[event].String_Var_1;
            string String_Var_2 = LIBRARY.COLLECTION[collection_pos].ANIMATIONS[animation_pos].EVENTS[event].String_Var_2;

            EVENTS[channel].set(Label, tmeCurrentTime, Start_Delay_Time, Duration_Of_Brighness, Speed_Of_LED_Walk, 
                                Animation_Walk_Type, Animation_Of_LED, Invert_Color, 
                                Start_1, Dest_1, Start_2, Dest_2, 
                                LED_Start_Pos, LED_End_Pos, Repeat, Clear_On_End, Off_During_Day, 
                                String_Var_1, String_Var_2);



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
      sdSysData.ALERTS.add_generic_alert("Collection not found (" + Collection_Name + ") Collection Size: " + 
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

void ANIMATION_HANDLER::process_events(system_data &sdSysData, unsigned long tmeCurrentTime)
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
            EvClear(channel, event);
            break;
          }

          // ---------------------------------------------------------------------------------------

          case AnEvClearRunning:  // Clear all active events if event is within Start and End Position.
          {                       // Possible problem if InTime is set to 0.
            EvClearRunning(channel, event, tmeCurrentTime);
            break;
          }

          // ---------------------------------------------------------------------------------------

          case AnEvSchedule:  //  Schedule an animation
          {
            EvSchedule(channel, event, tmeCurrentTime);
            break;
          }

          // ---------------------------------------------------------------------------------------

          case AnEvSetToEnd:  // Schedules an animation to end. Fades out and stops repeat on Pulses.
          {                   // Possible problem if InTime is set to 0.
            EvSetToEnd(channel, event, tmeCurrentTime);
            break;
          }

          // ---------------------------------------------------------------------------------------
        }
      }
    }
  }

  // Check Schedule list and call requested animations.
  if (SCHEDULE_LIST.size() >= 0)
  {
    for(int pos = 0; pos < SCHEDULE_LIST.size(); pos ++)
    {
      call_animation(sdSysData, tmeCurrentTime, SCHEDULE_LIST[pos].Collection_Name, SCHEDULE_LIST[pos].Animation_Name);
    }
  }

  SCHEDULE_LIST.clear();

}

#endif