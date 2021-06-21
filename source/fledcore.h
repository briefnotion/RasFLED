// ***************************************************************************************
// *
// *    Core       | Everything within this document is proprietary to Core Dynamics.
// *    Dynamics   | Any unauthorized duplication will be subject to prosecution.
// *
// *    Department : (R+D)^2                        Name: fledcore.h
// *       Sub Dept: Programming
// *    Location ID: 856-45B
// *                                                      (c) 2856 - 2858 Core Dynamics
// ***************************************************************************************

#ifndef FLEDCORE_H
#define FLEDCORE_H

// Standard Header Files
#include <chrono>


// ***************************************************************************************
// STRUCTURES AND CLASSES
// ***************************************************************************************

// -------------------------------------------------------------------------------------
//  Contains info on strip behavior
class profile_strip
{
  private:
  int intBOTTOM_OFFSET  =0;
  int intTOP_OFFSET     =0;

  bool booFORWARD       = true;
  bool booBOT_AT_START  = true;

  std::string           strPOSITION = "";

  public:
  //CRGB*                 crgbARRAY;
  std::string           Status = "";
  int intCHANNEL        = -1;

  int intSTARTPOS       = 0;
  int intSIZE           = 0;

  void set(int channel, int start_pos, int size, bool forward, bool bot_at_start, std::string strPosition)
  {
    //crgbARRAY       = new CRGB[size];
    intCHANNEL      = channel;
    intSIZE         = size;
    booFORWARD      = forward;
    booBOT_AT_START = bot_at_start;

    intBOTTOM_OFFSET  = start_pos;
    intTOP_OFFSET     = start_pos + intSIZE - 1;

    strPOSITION = strPosition;
  }

  int fs(int pos)
  // From Start
  {
    return pos + intBOTTOM_OFFSET;
  }
  
  int fe(int pos)
  // From End
  {
    return intTOP_OFFSET - pos;
  }

  int fb(int pos)
  // From Bottom
  {
    if (booBOT_AT_START == true)
    {
      return pos + intBOTTOM_OFFSET;
    }
    else
    {
      return intTOP_OFFSET - pos;
    }
  }

  int ft(int pos)
  // From Bottom
  {
    if (booBOT_AT_START == true)
    {
      return intTOP_OFFSET - pos;
    }
    else
    {
      return pos + intBOTTOM_OFFSET;
    }
  }

  bool position(std::string position)
  {
    if (strPOSITION == position)
    {
      return true;
    }
    else
    {
      return false;
    }
    
  }
  
};

//  Contains info on strip group
//    (I would like this class to be more dytnamicly configurable in the future for a more
//      dynamic setup purposes.)
class profile_strip_group
{
  public:
  profile_strip     pstrDOOR;
  profile_strip     pstrOVERHEAD;
  hardware_monitor  hwSWITCH;

  void set(profile_strip door, profile_strip overhead, hardware_monitor hwswitch)
  {
    // Store Strip Groups
    pstrDOOR      = door;
    pstrOVERHEAD  = overhead;

    // Door Switch
    hwSWITCH      = hwswitch;
  }
};


// -------------------------------------------------------------------------------------
// Keeps track of timing variables
class FledTime
{
  private:
  std::chrono::time_point<std::chrono::system_clock> tmeStart;
  std::chrono::time_point<std::chrono::system_clock> tmeFrame;

  public:

  double tmeFrameMillis;

  void set()
  {
    // Initialize as Start of Program Time.
    tmeStart = std::chrono::system_clock::now();
  }

  double now()
  {
    // Returns now time in milliseconds.
    // Should be Unsigned Long.
    std::chrono::time_point<std::chrono::system_clock> tmeNow = std::chrono::system_clock::now();
    std::chrono::duration<double>  dur = tmeNow - tmeStart;

    double nowtime = dur.count();
    nowtime = nowtime * 1000;
    
    return nowtime;
  }

  void setframetime()
  {
    // Sets the Start of a Frame Time to now. 
    tmeFrame = std::chrono::system_clock::now();
    std::chrono::duration<double>  dur = tmeFrame - tmeStart;

    tmeFrameMillis = dur.count();
    tmeFrameMillis = tmeFrameMillis * 1000;
  }

  double tmeFrameElapse()
  {
    // Returns, in milliseconds, the amount of time passed since frame time.
    double elapsed;
    std::chrono::time_point<std::chrono::system_clock> tmeNow = std::chrono::system_clock::now();
    std::chrono::duration<double>  dur = tmeNow - tmeFrame;
    
    elapsed = dur.count();
    elapsed = elapsed * 1000;

    return elapsed;
  }
};


// -------------------------------------------------------------------------------------
// LedStrip Structures 

/*
// Defines a basic LED Strip
class led_strip
{
  public:
  int Cl = 0; // Channel
  int St = 0; // Start Led Pos
  int Ed = 0; // End Led Pos
  int AnimationStatus = 0;

  void set(int intChannel, int intStart, int intEnd)
  {
    Cl = intChannel;
    St = intStart;
    Ed = intEnd;
  }

  int Ct()
  {
    int count;
    return Ed - St + 1;
  }
};
*/


// -------------------------------------------------------------------------------------
// Timed Event Data Variable

class timed_event_data
// Varibles to control the timed_event.
{
  public:
  std::string strIdent = "";
  unsigned long tmeSTARTTIME = 0;
  int intDURATION = 0;
  int intSPEED= 0;
  char  bytANIMATION = 0;
  char  bytLEDANIMATION = 0;
  CRGB crgbCOLORSTART1 = CRGB(0,0,0);
  CRGB crgbCOLORSTART2 = CRGB(0,0,0);
  CRGB crgbCOLORDEST1 = CRGB(0,0,0);
  CRGB crgbCOLORDEST2 = CRGB(0,0,0);
  int  intSTARTPOS = 0;
  int  intENDPOS = 0;
  bool booINVERTCOLOR = false;
  bool booREPEAT = false;
  bool booCLEARONEND = true;

  bool booCOMPLETE = true;


  void PostCheck(unsigned long tmeCurrent)
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
      }
    }
  }
};


// -------------------------------------------------------------------------------------
// Timed Event Variable

class timed_event
//  Create a Timed LED Event:
//    Controls when a group of LEDs are to begin their individual light path animation.
//    If an event is over written the previous animation will be lost.
{
  public:
  //timed_event_data teDATA[NUM_TIMED_EVENTS];
  std::vector<timed_event_data> teDATA;
  int      intLEDCOUNT;

  void create(int intLedCount)
  // On startup, define the amount of LEDs in this event list.
  {
    intLEDCOUNT = intLedCount;
  }

  void set(std::string strIedntity, unsigned long tmeCurrentTime,
           int tmeStartInTime, int intDuration, int intSpeed, 
           char  bytAnimation, char  bytLEDAnimation, bool booInvertColor, 
           CRGB crgbStart1, CRGB crgbDest1, CRGB crgbStart2, CRGB crgbDest2, 
           int intStartPos, int intEndPos, bool booRepeat, bool booClearOnEnd)
  
  // Prepare an animation to start at a specific time.
  {

    bool booCreated = false;

    unsigned long tmeStartTime = tmeCurrentTime + tmeStartInTime;

    timed_event_data newteDATA;

    newteDATA.strIdent = strIedntity;
    newteDATA.tmeSTARTTIME = tmeStartTime;
    newteDATA.intDURATION = intDuration;
    newteDATA.intSPEED = intSpeed;
    newteDATA.bytANIMATION = bytAnimation;
    newteDATA.bytLEDANIMATION = bytLEDAnimation;

    newteDATA.booINVERTCOLOR = booInvertColor;

    newteDATA.crgbCOLORSTART1 = crgbStart1;
    newteDATA.crgbCOLORSTART2 = crgbStart2;
    newteDATA.crgbCOLORDEST1 = crgbDest1;
    newteDATA.crgbCOLORDEST2 = crgbDest2;

    newteDATA.intSTARTPOS = intStartPos;
    newteDATA.intENDPOS = intEndPos;
    newteDATA.booREPEAT = booRepeat;
    newteDATA.booCLEARONEND = booClearOnEnd;

    newteDATA.booCOMPLETE = false;

    teDATA.push_back(newteDATA);

    booCreated = true;
  }

  // -------------------------------------------------------------------------------------
  // Clear events in channel

  void ClearAll(int intStartPos, int intEndPos)
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
        //printf("Cleared Event: E%d S%d E%d\n", x, intStartPos, intEndPos);
      }
    }
  }

  // -------------------------------------------------------------------------------------
  // Timed Event LED Animations

  bigCRGB crgb_anim_color(stupid_random sRND, unsigned long tmeCurrentTime, unsigned long tmeAnimTime,
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

  bool execute(Console &cons, stupid_random sRND, CRGB hwLEDArray[], unsigned long tmeCurrentTime)
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
    bool booPixelColorChanged;
    int activeeventcount;
    
    bool booEventActive[teDATA.size()];
    bool booEventComplete[teDATA.size()];
    
    bigCRGB bigcrgbNewColor;
    bigCRGB tempColor;

    bool booChanged = false;
    unsigned long tmeStartAnim;

    // Process Event Animations  
    // Prepare Arrays
    if (teDATA.size() > 0)
    {
    for (int e = 0; e < teDATA.size(); e++) //Duplicate
      {
        // Prepare Temporary Complete Array With Events That May Run
        if (tmeCurrentTime >= teDATA[e].tmeSTARTTIME  && teDATA[e].booCOMPLETE == false)
        {
          booEventComplete[e] = true;
        }

        // Clear Active Event Array
        booEventActive[e] = false;
      }
      // Process LEDs, one by one.
      for (int led = 0; led < intLEDCOUNT; led++)
      {
        //  Attempt to restrict the amount of times the activity tracker routine is ran.
        activeeventcount = 0;

        // Clear the value of the new LED color.  Should only update when it has changed.
        bigcrgbNewColor.r = 0;
        bigcrgbNewColor.g = 0;
        bigcrgbNewColor.b = 0;

        booPixelColorChanged = false;

        // Process each event, one by one.
        for (int event = 0; event < teDATA.size(); event++)
        {
          // Clear the tmp colors, in case they have data in them at the start of each 
          //  event process.
          tempColor.r = 0;
          tempColor.g = 0;
          tempColor.b = 0;

          // Only continue processing the event if the event hasnt been completed.
          if (teDATA[event].booCOMPLETE == false)
          {
            // Is the LED we are processing within the event?
            if (((led >= teDATA[event].intSTARTPOS) && (led <= teDATA[event].intENDPOS))
                || ((led <= teDATA[event].intSTARTPOS) && (led >= teDATA[event].intENDPOS)))
            {
              // OK, so an event is schedule, but is it ready to start?
              if (tmeCurrentTime >= teDATA[event].tmeSTARTTIME)
              {
                // Collision Tracker
                activeeventcount++;   //  Attempt to restrict the amount of times this 
                                      //    routine is ran.
                booEventActive[event] = true;

                // Figure out when the LED is suposed to start doing something.
                tmeStartAnim = teDATA[event].tmeSTARTTIME
                              + (abs((led - teDATA[event].intSTARTPOS))
                                  * teDATA[event].intSPEED);

                // The Pixel on this Event is ready to change.
                if ((tmeCurrentTime >= tmeStartAnim))
                {
                  // -------------------------------------------------------------------
                  // This Routine can be applied to all animation types. Its just not
                  //  implemented until needed.  Also kept seperate becuase it uses
                  //  a few more clock cycles. e.g. PulseDither and PulseToDither 
                  //  can be created.  But not the Twinkle.  Twinkle is passing direct
                  //  colors. 
                  /*
                  // Preprocess Dest 2 for dynamic DEST2 on Pixel Fade.
                  if (teDATA[event].bytLEDANIMATION == AnPiFadeDith)
                  {
                    // Yep, still thinking about this.  
                    // Not here anymore, but still here.  In Limbo.
                  }*/
                  // -------------------------------------------------------------------

                  switch (teDATA[event].bytANIMATION)
                  {
                    case AnEvSweep:
                      {
                        // Calculate how much this Event will chaange the pixel.
                        //  Breaking the norm, but also passing the led ID and
                        //  original 4 colors to ... (consider rewrite)
                        tempColor = crgb_anim_color(sRND, tmeCurrentTime, tmeStartAnim, 
                                                    led, event, teDATA[event]);

                        //  Update the events completeness if its still active.
                        if (tempColor.complete == false)
                        {
                          booEventComplete[event] = false;
                        }

                        // Check for inverted color and invert if necessary.
                        if (teDATA[event].booINVERTCOLOR == false)
                        {
                          bigcrgbNewColor.r = bigcrgbNewColor.r + tempColor.r;
                          bigcrgbNewColor.g = bigcrgbNewColor.g + tempColor.g;
                          bigcrgbNewColor.b = bigcrgbNewColor.b + tempColor.b;
                        }
                        else
                        {
                          bigcrgbNewColor.r = bigcrgbNewColor.r - tempColor.r;
                          bigcrgbNewColor.g = bigcrgbNewColor.g - tempColor.g;
                          bigcrgbNewColor.b = bigcrgbNewColor.b - tempColor.b;
                        }

                        booPixelColorChanged = true;
                        break;
                      } // End Case AnEvSweep
                  } // End Switch Statement
                }  // tmeCurrentTime >= tmeStartAnim
              } // End Time Check
            } // End LED Postion Check
          } // End Expiration Check
        } // End For Event Loop

        // Now that all event are processeds, update the Main LED to the new value.
        // But only if it changed.
        if (booPixelColorChanged == true)
        {
          // Calclulate the color of LED by adding the colors together.

          // If the lights are out range, either put them at full on or full off.
          if (bigcrgbNewColor.r > 255)
          {
            bigcrgbNewColor.r = 255;
          }
          if (bigcrgbNewColor.g > 255)
          {
            bigcrgbNewColor.g = 255;
          }
          if (bigcrgbNewColor.b > 255)
          {
            bigcrgbNewColor.b = 255;
          }
          if (bigcrgbNewColor.r  < 0)
          {
            bigcrgbNewColor.r = 0;
          }
          if (bigcrgbNewColor.g  < 0)
          {
            bigcrgbNewColor.g = 0;
          }
          if (bigcrgbNewColor.b  < 0)
          {
            bigcrgbNewColor.b = 0;
          }

          // Set the color of the LED on the strip.
          hwLEDArray[led].r = (char)bigcrgbNewColor.r;
          hwLEDArray[led].g = (char)bigcrgbNewColor.g;
          hwLEDArray[led].b = (char)bigcrgbNewColor.b;

          booChanged = true;
        }
      } // End For LED Loop

      // All Leds Processed

      //  Check to see if any events expire or repeats.
      int e = 0;
      while ( e < teDATA.size() )
      {

        if (booEventActive[e] == true && booEventComplete[e] == true)
        {
          teDATA[e].booCOMPLETE = true;
          teDATA[e].PostCheck(tmeCurrentTime);
        }
        e++;
      }

      e = 0;
      while ( e < teDATA.size() )
      {
        if (teDATA[e].booCOMPLETE == true)
        {
          teDATA.erase(teDATA.begin() + e);
        }
        else
        {
          e++;
        }
      }

    } // End teDATA size check.

  return booChanged;
  
  }
};



#endif