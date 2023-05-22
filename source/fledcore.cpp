// ***************************************************************************************
// *
// *    Core       | Everything within this document is proprietary to Core Dynamics.
// *    Dynamics   | Any unauthorized duplication will be subject to prosecution.
// *
// *    Department : (R+D)^2                        Name: fledcore.cpp
// *       Sub Dept: Programming
// *    Location ID: 856-45B
// *                                                      (c) 2856 - 2858 Core Dynamics
// ***************************************************************************************

#ifndef FLEDCORE_CPP
#define FLEDCORE_CPP

#include "fledcore.h"

// ***************************************************************************************
// STRUCTURES AND CLASSES
// ***************************************************************************************

// -------------------------------------------------------------------------------------
// Timed Event Data Variable

void timed_event_data::PostCheck(unsigned long tmeCurrent)
// Check to see if the event is over, unlock and release Start Colors.
{
  //  (num of led * speed + duration)
  // Grabbing actual current time to process decayed events, because alot could've happened
  // since then.

  if (booCOMPLETE == true)
  {
    // The event repeats, collision is irrelevant.
    if (booREPEAT == true)
    {
      // Keep the event active by resetting its start time and setting it
      //  to be incomplete.
      booCOMPLETE = false;
      tmeSTARTTIME = tmeCurrent;  // Using current time here because we want
      //  to keep the frames the same.

      if (VELOCITY == true)
      {
        PREV_TIME_STAMP = tmeCurrent;
      }
    }
  }
}

// -------------------------------------------------------------------------------------
// Timed Event Variable

void timed_event::create(int intLedCount)
// On startup, define the amount of LEDs in this event list.
{
  intLEDCOUNT = intLedCount;
}

void timed_event::set_timed_event(timed_event_data newteDATA)
{
  teDATA.push_back(newteDATA);
}

// -------------------------------------------------------------------------------------
// Clear events in channel

void timed_event::ClearAll(int intStartPos, int intEndPos)
//Remove all timed event animations on a specific animation strip.
{

  for (int x = 0; x < teDATA.size(); x++)

  if (teDATA[x].booCOMPLETE == false && 
      (  ((teDATA[x].intSTARTPOS >= intStartPos)  
        && (teDATA[x].intSTARTPOS <= intEndPos))
              ||
        ((teDATA[x].intENDPOS >= intStartPos)  
        && (teDATA[x].intENDPOS <= intEndPos))  ) )
  {
    
    {
      teDATA[x].booCOMPLETE = true;
    }
  }
}

// -------------------------------------------------------------------------------------
// Timed Event LED Animations

bigCRGB timed_event::crgb_anim_color(stupid_random sRND, unsigned long tmeCurrentTime, unsigned long tmeAnimTime,
                        int intLED, int intEvent, timed_event_data &EventInfo)
//  Returns a CRGB value of the single LED respective to what its value should
//    be as it is in its time path.

//  LED Animations:
//    0 - Clear:  Clears future animation and sets to no future animation.
//    1 - Fade:   Fades single LED from its initial value to its destination value from
//                  start of animation, and completed and end of its duration.
//    2 - Pulse:  Pulses the LED to desired value.  The LED will have its requested
//                  full value at half duration time, and will return to its origional
//                  value at the end of the duration.
{

  // Only run pixel animation if it is ready.

  unsigned long tmeElapsed = tmeCurrentTime - tmeAnimTime;
  float fltPower;
  bigCRGB tmpColor;

  switch (EventInfo.bytLEDANIMATION)
  {
    case AnPiFade:
      // Fade Animation Path
      {
        // if time is greater than the pixel animation duration then set it to the end color.
        if (tmeCurrentTime >= tmeAnimTime + EventInfo.intDURATION)
        {
          tmpColor.r = EventInfo.crgbCOLORDEST1.r;
          tmpColor.g = EventInfo.crgbCOLORDEST1.g;
          tmpColor.b = EventInfo.crgbCOLORDEST1.b;
          
          tmpColor.complete = EventInfo.booCLEARONEND;

          return tmpColor;
          break;
        }
        else
        // compute the value based on the current time.
        {
          fltPower = ComputePower(tmeElapsed, EventInfo.intDURATION);
          tmpColor = Dither(fltPower, EventInfo.crgbCOLORSTART1, EventInfo.crgbCOLORDEST1);
          
          tmpColor.complete = false;

          return tmpColor;
          break;
        }
      } // END CASE AnPiFade
            
      case AnPiFadeDith:
      // Fade Animation Path (Dither, this is duplicate code!)
      {
        CRGB crgbTempStart;
        CRGB crgbTempDest;

        // Grab Event Data that may change or be processed within this switch 
          //  statement. We will be calculating the change of the pixel color, not 
          //  the actual color.

        // Dither the Dither
        if ((EventInfo.intENDPOS - EventInfo.intSTARTPOS)  == 0)
        {
          fltPower = 0;
        }
        else
        {
          fltPower = ComputePower(abs(intLED - EventInfo.intSTARTPOS), abs(EventInfo.intENDPOS - EventInfo.intSTARTPOS));
        }
        crgbTempStart = DitherSmall(fltPower, EventInfo.crgbCOLORSTART1, EventInfo.crgbCOLORSTART2);
        crgbTempDest = DitherSmall(fltPower, EventInfo.crgbCOLORDEST1, EventInfo.crgbCOLORDEST2);

        // Get value of light based on animation at current time.
        if (tmeCurrentTime >= tmeAnimTime + EventInfo.intDURATION)
        {
          tmpColor.r = crgbTempDest.r;
          tmpColor.g = crgbTempDest.g;
          tmpColor.b = crgbTempDest.b;
          
          tmpColor.complete = EventInfo.booCLEARONEND;

          return tmpColor;
          break;
        }
        else
        {
          fltPower = ComputePower(tmeElapsed, EventInfo.intDURATION);
          tmpColor = Dither(fltPower, crgbTempStart, crgbTempDest);
          
          tmpColor.complete = false;

          return tmpColor;
          break;
        }
      } // END CASE AnPiFadeDith

    case AnPiPulse:
      // Pulse Animation Path
      // This can be done beter with a simple ABS function.
      {
        if (tmeCurrentTime >= tmeAnimTime + EventInfo.intDURATION)
        {
          tmpColor.complete = true;
          
          return tmpColor;
          break;
        }
        else
        {
          if ((tmeElapsed * 2) <= (EventInfo.intDURATION))
          {
            fltPower = ComputePowerHalfBot(tmeElapsed,EventInfo.intDURATION);
          }
          else
          {
            fltPower = ComputePowerHalfTop(tmeElapsed,EventInfo.intDURATION);
          }

          //  Swap to second color at mid point
          tmpColor = Dither(fltPower, CRGB(0,0,0), EventInfo.crgbCOLORDEST1);
          
          tmpColor.complete = false;

          return tmpColor;
          break;
        }
      } // END CASE AnPiPulse

    case AnPiPulseTo:
      // PulseTo Animation Path
      // This can be done beter with a simple ABS function.
      {
        if (tmeCurrentTime >= tmeAnimTime + EventInfo.intDURATION)
        {
          tmpColor.r = EventInfo.crgbCOLORDEST2.r;
          tmpColor.g = EventInfo.crgbCOLORDEST2.g;
          tmpColor.b = EventInfo.crgbCOLORDEST2.b;
          
          tmpColor.complete = EventInfo.booCLEARONEND;

          return tmpColor;
          break;
        }
        else
        {
          CRGB crgbA;
          CRGB crgbB;
          //  Swap to second color and power down at mid point.
          if ((tmeElapsed * 2) <= (EventInfo.intDURATION))
          {
            fltPower = ComputePowerHalfBot(tmeElapsed,EventInfo.intDURATION);

            crgbA = CRGB(0,0,0);
            crgbB = EventInfo.crgbCOLORDEST1;
          }
          else
          {
            fltPower = ComputePowerHalfTop(tmeElapsed,EventInfo.intDURATION);

            crgbA = EventInfo.crgbCOLORDEST2;
            crgbB = EventInfo.crgbCOLORDEST1;
          }

          tmpColor = Dither(fltPower, crgbA, crgbB);
          
          tmpColor.complete = false;

          return tmpColor;
          break;
        }
      } // END CASE AnPiPulseTo

    
    case AnPiTwinkle:
      // Random Sparkling Twinkly Lights 
      {
        if (tmeCurrentTime >= tmeAnimTime + EventInfo.intDURATION)
        {
          tmpColor.complete = true;
          
          return tmpColor;
          break; 
        }
        else
        {
          CRGB crgbTwinkleColor;

          // Using crgbDest2 to pass twinkle parameters.
          int intOdds       = EventInfo.crgbCOLORDEST2.r;  // Chance that the light will twinkle.
          int intTimeReduce = EventInfo.crgbCOLORDEST2.g;  // Percentage of Time Duration Light is On. 
          int intColorCount = EventInfo.crgbCOLORDEST2.b;  // Amount of colors passed through the Event. 

          // We will need a signed Elapsed time.  Half as small, but we need to 
          //  subtract things from it. 
          unsigned long NewTimeStart = 0;
          unsigned long NewElapsedTime = tmeElapsed;
          int NewDuration = EventInfo.intDURATION;

          // Generate Random Number Seed.  The random numbers generated from 
          //  the picked position is sequential from the start. Also, the generated 
          //  random number is time dependant. Neither of these two things help 
          //  when we need to restart this sequence thousands of time within the 
          //  same milisecond. 
          //  randomSeed(tmeAnimTime + intEvent + intLED);

          // Pick 1 of 3 colors and determine if we will turn on the light.
          // unsigned long seed = tmeAnimTime + intLED + intEvent;
          unsigned long seed = (unsigned long)(intLED) + tmeAnimTime;
          char  Odds = sRND.getB(seed, intOdds);

          // Determine if the light was lucky enough to be turned on then assign it 
          //  one of the random colors of the draw. 
          if (Odds == 0)
          {

            // If the light will not be illuminated during its "entire" duration cycle, 
            // then pick a random time it is to start its illumination. 
            if (intTimeReduce != 0)
            {
              // Pick a random delay. 
              NewTimeStart = sRND.getUL(seed, floor(EventInfo.intDURATION * (float)intTimeReduce / 100)); 

              // Calculate how much long the light will on from the percentage of 
              //  of the duration. 
              intTimeReduce = 100 - intTimeReduce;
              NewDuration = (int)(float)(EventInfo.intDURATION) * (float)(intTimeReduce) / 100;

              // Figure out the new time to turn on the light.
              NewElapsedTime = tmeCurrentTime - tmeAnimTime - NewTimeStart;
            }


            char  Color = sRND.getB(seed, intColorCount);
            // Assign 1 of the 3 colors. 
            if (Color == 0)
            {
              crgbTwinkleColor = EventInfo.crgbCOLORSTART1; 
            }
            else if (Color == 1)
            {
              crgbTwinkleColor = EventInfo.crgbCOLORDEST1;
            }
            else
            {
              crgbTwinkleColor = EventInfo.crgbCOLORSTART2;
            }


            // Continue with the lights illumination if it was lucky enough to be 
            //  turned on and if it was lucky enough to fall within the time to be turned on.
            if ((NewElapsedTime >= 0) && (NewElapsedTime <= NewElapsedTime + NewDuration))
            {
              // Modified Pulse Routine ----  Pulse routine used offten.  I should function it. 
              if ((NewElapsedTime * 2) <= (NewDuration))
              { 
                fltPower = ComputePowerHalfBot(NewElapsedTime,NewDuration);
              }
              else
              {
                fltPower = ComputePowerHalfTop(NewElapsedTime,NewDuration);
              }

              // No Negative Colors
              if ( (fltPower > 0) && (fltPower < 1) )
              {
                //  Swap to second color at mid point
                tmpColor = Dither(fltPower, CRGB(0,0,0), crgbTwinkleColor);
              }

              tmpColor.complete = false;
            }
          }

          return tmpColor;  
          break;
        }
      } // END CASE AnPiTwinkle

  } // END SWITCH STATEMENT
  return tmpColor;
}

// -------------------------------------------------------------------------------------

void timed_event::process_led_light(int &led, timed_event_data &teDATA, system_data &sdSysData, stupid_random &sRND, unsigned long &tmeCurrentTime, 
                                    bigCRGB bigcrgbNewColor[], bool &booEventComplete, bool &booPixelColorChanged) // return
{
  bigCRGB tempColor;
  unsigned long tmeStartAnim;

  // Figure out when the LED is suposed to start doing something.
  tmeStartAnim = teDATA.tmeSTARTTIME
                + (abs(led - teDATA.intSTARTPOS)
                    * teDATA.intSPEED);

  if ((tmeCurrentTime >= tmeStartAnim))
  {
    // -------------------------------------------------------------------
    // This Routine can be applied to all animation types. Its just not
    //  implemented until needed.  Also kept seperate becuase it uses
    //  a few more clock cycles. e.g. PulseDither and PulseToDither 
    //  can be created.  But not the Twinkle.  Twinkle is passing direct
    //  colors. 
    // -------------------------------------------------------------------

    switch (teDATA.bytANIMATION)
    {
      case AnEvSweep:
        {
          // Calculate how much this Event will change the pixel.
          //  Breaking the norm, but also passing the led ID and
          //  original 4 colors to ... (consider rewrite)
          tempColor = crgb_anim_color(sRND, tmeCurrentTime, tmeStartAnim, 
                                      led, 0, teDATA);  // Remove event param

          //  Update the events completeness if its still active.
          if (tempColor.complete == false)
          {
            booEventComplete = false;
          }

          // Process the light animation but make no changes if off during day and day set.
          if (teDATA.booOFFDURINGDAY == true && sdSysData.Day_On_With_Override.value() == true)
          {
            // do nothing.
          }
          else
          {
            // Check for inverted color and invert if necessary.
            if (teDATA.booINVERTCOLOR == false)
            {
              bigcrgbNewColor[led].r = bigcrgbNewColor[led].r + tempColor.r;
              bigcrgbNewColor[led].g = bigcrgbNewColor[led].g + tempColor.g;
              bigcrgbNewColor[led].b = bigcrgbNewColor[led].b + tempColor.b;
            }
            else
            {
              bigcrgbNewColor[led].r = bigcrgbNewColor[led].r - tempColor.r;
              bigcrgbNewColor[led].g = bigcrgbNewColor[led].g - tempColor.g;
              bigcrgbNewColor[led].b = bigcrgbNewColor[led].b - tempColor.b;
            }            
          }

          booPixelColorChanged = true;
          break;
        } // End Case AnEvSweep
    } // End Switch Statement
  } // End if tmeCurrentTime >= tmeStartAnim
}

bool timed_event::execute2(Console &cons, system_data &sdSysData, stupid_random sRND, CRGB hwLEDArray[], unsigned long tmeCurrentTime)
//  Sets all requested light paths, start to end position, to begin their animation
//    at a future time.

//  Event Animations:
//    0 - Clear:  Clears future event and sets to no future future.
//    1 - Sweep:  Sets light paths for all LEDs from start to end posion.
//                  Speed is the time difference in miliseconds between each adjacent
//                  light path.
//                  Duration, destination color, and LED animation will also be passed
//                  to its light path.
{
  bool booPixelColorChanged = false;
  CRGB empty_color;
  
  bool booEventComplete = true;

  bigCRGB bigcrgbNewColor[intLEDCOUNT];

  // Process only if events exist.
  if (teDATA.size() > 0)
  {
    // Process each event, one by one.
    for (int event = 0; event < teDATA.size(); event++)
    {
      int led_start = 0;
      int led_end = 0;

      if (teDATA[event].booCOMPLETE == false)
      {

        //Make adjustment if Event is a Velocity
        if (teDATA[event].VELOCITY == true)
        {
          
          if ( teDATA[event].PREV_TIME_STAMP == 0)
          {
             teDATA[event].PREV_TIME_STAMP = tmeCurrentTime;
          }
          else
          {
            int duration = tmeCurrentTime - teDATA[event].PREV_TIME_STAMP;

            teDATA[event].tmeSTARTTIME = teDATA[event].tmeSTARTTIME + duration - (int)((float)duration * teDATA[event].VELOCITY_VALUE);

            // to test at 1 Miph.
            //teDATA[event].tmeSTARTTIME = teDATA[event].tmeSTARTTIME + duration - (int)((float)duration * 1);

            if (teDATA[event].tmeSTARTTIME > 4294967295 - 3600000)
            {
              teDATA[event].tmeSTARTTIME = 0;
            }
            
            teDATA[event].PREV_TIME_STAMP = tmeCurrentTime;
          }
        }

        // OK, so an event is schedule, but is it ready to start?
        if (tmeCurrentTime >= teDATA[event].tmeSTARTTIME)
        {
          
          booEventComplete = true;
          
          // Determin direction of LED animation.
          if(teDATA[event].intSTARTPOS <= teDATA[event].intENDPOS)
          {
            for (int led = teDATA[event].intSTARTPOS; led <= teDATA[event].intENDPOS; led++)
            {
              if (is_within(led, 0, intLEDCOUNT -1))
              {
                process_led_light(led, teDATA[event], sdSysData, sRND, tmeCurrentTime, 
                                  bigcrgbNewColor, booEventComplete, booPixelColorChanged);
              }
            }
          }
          else
          {
            for (int led = teDATA[event].intENDPOS; led <= teDATA[event].intSTARTPOS; led++)
            {
              if (is_within(led, 0, intLEDCOUNT -1))
              {
                process_led_light(led, teDATA[event], sdSysData, sRND, tmeCurrentTime, 
                                  bigcrgbNewColor, booEventComplete, booPixelColorChanged);
              }
            }
          }

          // Only PostCheck Events that are started and marked completed by the 
          //  animation renderer.
          if (booEventComplete == true)
          {
            teDATA[event].booCOMPLETE = true;
            teDATA[event].PostCheck(tmeCurrentTime);
          }
        }
      }
    } // END for event 

    // All events ran. Prep for copy to hwLEDArray.
    // Normalize and Bring big pixels to hwLEDArray
    if (booPixelColorChanged == true)
    {
      for (int led = 0; led < intLEDCOUNT; led++)
      {
        // R
        if (bigcrgbNewColor[led].r < 0)
        {
          hwLEDArray[led].r = 0;
        }
        else if (bigcrgbNewColor[led].r > 255)
        {
          hwLEDArray[led].r = 255;
        }
        else
        {
          hwLEDArray[led].r = bigcrgbNewColor[led].r;
        }
        
        // G
        if (bigcrgbNewColor[led].g < 0)
        {
          hwLEDArray[led].g = 0;
        }
        else if (bigcrgbNewColor[led].g > 255)
        {
          hwLEDArray[led].g = 255;
        }
        else
        {
          hwLEDArray[led].g = bigcrgbNewColor[led].g;
        }
        
        // B
        if (bigcrgbNewColor[led].b < 0)
        {
          hwLEDArray[led].b = 0;
        }
        else if (bigcrgbNewColor[led].b > 255)
        {
          hwLEDArray[led].b = 255;
        }
        else
        {
          hwLEDArray[led].b = bigcrgbNewColor[led].b;
        }
      }
    }
    
    // Erase all completed events
    for(int e = teDATA.size() -1; e >= 0; e-- )
    {
      if (teDATA[e].booCOMPLETE == true)
      {
        teDATA.erase(teDATA.begin() + e);
      }
    }

  } // END if teDATA.size > 0
  
  return booPixelColorChanged;

}




#endif