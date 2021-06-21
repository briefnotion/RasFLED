// ***************************************************************************************
// *
// *    Core       | Everything within this document is proprietary to Core Dynamics.
// *    Dynamics   | Any unauthorized duplication will be subject to prosecution.
// *
// *    Department : (R+D)^2                        Name: timedeventsystem.h
// *       Sub Dept: Programming
// *    Location ID: 856-45B
// *                                                      (c) 2856 - 2858 Core Dynamics
// ***************************************************************************************

#ifndef TIMEDEVENTSYSTEM_H
#define TIMEDEVENTSYSTEM_H

// RASFled related header files
#include "animations.h"



// ***************************************************************************************
// FUNCTION AND PROCEDURES
// ***************************************************************************************


// -------------------------------------------------------------------------------------
// Clear events on a channel 

void vdClearAllTimedEvent(timed_event teEvent[], int intPos, int intStartPos, int intEndPos)
//  Sort through the timed event list a create an event at the first slot available.
{
  teEvent[intPos].ClearAll(intStartPos, intEndPos);
}


// -------------------------------------------------------------------------------------
// System event system for non animations.

void teSystem(Console &cons, system_data &sdSysData, profile_strip_group strip_group[], timed_event teEvent[], unsigned long tmeCurrentTime)
//void teSystem(Console &cons, led_strip lsStripList[], timed_event teEvent[], unsigned long tmeCurrentTime)
// Example:
//  teEvent[0].set(tmeCurrentMillis, X, 0, 0, AnEvSchedule, AnTaDoorCloseBack, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), X, X, false, false);
//    or      ( X is the values that can be set )
//  teEvent[0].set(tmeCurrentMillis, X, X, 0, AnEvSchedule, AnEvSetToEnd, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(X, X, X), CRGB(X, X, X), 0, 0, false, false);
//                  if booRepeat set to true then pulse animations will continue till end of cycle.
//    or 
//  teEvent[0].set(tmeCurrentMillis, X, 0, 0, AnEvClear, 0, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), X, X, false, false);

// Guide: (tmeCurrentTime, tmeStartInTime, intDuration, intSpeed, bytAnimation, bytLEDAnimation, crgbStart1, crgbDest1, crgbStart2, crgbDest2, intStartPos, intEndPos, booRepeat, booClearOnEnd)
{

  for (int channel = 0; channel < sdSysData.CONFIG.iNUM_CHANNELS; channel++)
  {
    if (teEvent[channel].teDATA.size() > 0)
    {
      for (int event = 0; event < teEvent[channel].teDATA.size(); event++)
      {
        if (tmeCurrentTime >= teEvent[channel].teDATA[event].tmeSTARTTIME && teEvent[channel].teDATA[event].booCOMPLETE == false)
        {
          // Process Timed System Events (keeping the LED type event scheduler format for 
          //  now)

          switch (teEvent[channel].teDATA[event].bytANIMATION)
          {
            case AnEvClear:   // Clear all events, whether running or not, if event is within Start and End Position.
            {
              //cons.printwait("Event: AnEvClear");
              teEvent[channel].teDATA[event].booCOMPLETE = true;
              teEvent[channel].ClearAll(teEvent[channel].teDATA[event].intSTARTPOS,teEvent[channel].teDATA[event].intENDPOS);
              break;
            }
            
            case AnEvClearRunning:  // Clear all active events if event is within Start and End Position.
            {                       // Possible problem if InTime is set to 0.
              //cons.printwait("Event: AnEvClearRunning");
              teEvent[channel].teDATA[event].booCOMPLETE = true;

              for (int eventscan = 0; eventscan < teEvent[channel].teDATA.size(); eventscan++)
              {
                if(tmeCurrentTime >= teEvent[channel].teDATA[eventscan].tmeSTARTTIME)
                {
                  if (  ((teEvent[channel].teDATA[eventscan].intSTARTPOS >= teEvent[channel].teDATA[event].intSTARTPOS)  
                        && (teEvent[channel].teDATA[eventscan].intSTARTPOS <= teEvent[channel].teDATA[event].intENDPOS))
                              ||
                        ((teEvent[channel].teDATA[eventscan].intENDPOS >= teEvent[channel].teDATA[event].intSTARTPOS)  
                        && (teEvent[channel].teDATA[eventscan].intENDPOS <= teEvent[channel].teDATA[event].intENDPOS))  )
                  {
                    if (event != eventscan)
                    {
                      teEvent[channel].teDATA[eventscan].booCOMPLETE = true;
                    }
                  }
                }
              } 
              break;
            }

            case AnEvSchedule:
            //  Schedule an animation
            {  
              //cons.printwait("Event: AnEvSchedule");
              // Clear the Event whether the event ran or not.
              if(teEvent[channel].teDATA[event].booREPEAT == false)
              {
                teEvent[channel].teDATA[event].booCOMPLETE = true;
              }
              else
              {
                teEvent[channel].teDATA[event].tmeSTARTTIME = tmeCurrentTime + teEvent[channel].teDATA[event].intDURATION;
              }
              
              switch (teEvent[channel].teDATA[event].bytLEDANIMATION)
              // Activate an Animation Set
              {

                // Special Animations

                /*
                case AnTaPowerOn:
                // Animation on startup
                {
                  vdPowerOnAnimation(cons, lsStripList, 0, teEvent, tmeCurrentTime);
                  break;
                }
                */
                case AnTavdTestAnimation:
                // Color Specific Channel Pulse
                {
                  vdAdditionalOpenADV01(cons, strip_group[channel].pstrOVERHEAD, teEvent, tmeCurrentTime);
                  break;
                }    

                case AnTaChannelFlashColor:
                // Color Specific Channel Pulse
                {
                  vdChannelLightFlashColor00(cons, strip_group[channel], teEvent, tmeCurrentTime, teEvent[channel].teDATA[event].crgbCOLORSTART1);
                  break;
                }

                case AnTaChannelPulseSimple:
                // Color Specific Channel Pulse
                {
                  vdChannelLightPulseSimple01(cons, strip_group[channel], teEvent, tmeCurrentTime, teEvent[channel].teDATA[event].crgbCOLORSTART1);
                  break;
                }

                case AnTaChannelPulseColor:
                // Color Specific Channel Pulse
                {
                  vdChannelLightPulseColor01(cons, strip_group[channel], teEvent, tmeCurrentTime, teEvent[channel].teDATA[event].crgbCOLORSTART1);
                  break;
                }

                case AnTaChannelPulseColorCountdown:
                // Color Specific Channel Pulse
                {
                  vdChannelLightPulseColorCountdown01(cons, strip_group[channel], teEvent, tmeCurrentTime, sdSysData.get_countdown_color());
                  if (sdSysData.cdTIMER.is_triggered() == true)
                  {
                    if(sdSysData.cdTIMER.is_checked() == false)
                    {
                      // Only mark it checked after the last channel is done with it
                      if (channel == sdSysData.CONFIG.iNUM_CHANNELS - 1)
                      {
                        sdSysData.cdTIMER.check();
                      }
                      vdChannelLightFlashColor00(cons, strip_group[channel], teEvent, tmeCurrentTime, CRGB(96,96,96));
                    }
                  }
                  break;
                }

                case AnTaOverheadIllumColor:
                // Color Specific Illumination
                {
                  vdOverheadIllum(cons, strip_group[channel], teEvent, tmeCurrentTime, teEvent[channel].teDATA[event].crgbCOLORSTART1);
                  break;
                }

                case AnTaHazard:
                // Color Specific Illumination
                {
                  vdHazard(cons, strip_group[channel], teEvent, tmeCurrentTime);
                  break;
                }

                case AnTaPacificaishColor:
                // Color Specific Channel Pulse
                {
                  vdPacificaishAnimationADVColor(cons, strip_group[channel], teEvent, tmeCurrentTime, teEvent[channel].teDATA[event].crgbCOLORSTART1);
                  break;
                }                

                // Open Door
                /*
                case AnTaDoorOpen:
                {
                  vdDoorOpenAnimation(cons, lsStripList, channel *2, teEvent, tmeCurrentTime);
                  break;
                }
                case AnTaDoorOpen00:
                {
                  vdDoorOpenAnimation00(cons, lsStripList, channel *2, teEvent, tmeCurrentTime);
                  break;
                }
                case AnTaDoorOpen01:
                {
                  vdDoorOpenAnimation01(cons, lsStripList, channel *2, teEvent, tmeCurrentTime);
                  break;
                }
                case AnTaDoorOpen02:
                {
                  vdDoorOpenAnimation02(cons, lsStripList, channel *2, teEvent, tmeCurrentTime);
                  break;
                }

                // Close Back Door
                case AnTaDoorClose:
                {
                  vdDoorCloseAnimation(cons, lsStripList, channel *2, teEvent, tmeCurrentTime);
                  break;
                }
                case AnTaDoorClose00:
                {
                  vdDoorCloseAnimation00(cons, lsStripList, channel *2, teEvent, tmeCurrentTime);
                  break;
                }
                
                case AnTaStripOverOff:
                {
                  vdStripOverOff(cons, lsStripList, (channel *2) +1, teEvent, tmeCurrentTime);
                  break;
                }
                */

                /*
                case AnTavdPacificaish:
                {
                  vdPacificaishAnimation(cons, lsStripList, (channel *2) +1, teEvent, tmeCurrentTime);
                  break;
                }

                case AnTavdPaAnimClose:
                {
                  vdPacificaishAnimationClose(cons, lsStripList, (channel *2) +1, teEvent, tmeCurrentTime);
                  break;
                }

                case AnTavdPaAnimClose00:
                {
                  vdPacificaishAnimationClose00(cons, lsStripList, (channel *2) +1, teEvent, tmeCurrentTime);
                  break;
                }
                */

                /*
                // Halloween Animations 

                case AnTavdHallowClose2:
                {
                  vdHallowClose2(cons, lsStripList, (channel *2) +1 , teEvent, tmeCurrentTime);
                  break;
                }

                case AnTavdCloud:
                {
                  vdCloudAnimation(cons, lsStripList, (channel *2) +1, teEvent, tmeCurrentTime);
                  break;
                }

                case AnTavdLightning:
                {
                  vdLightning(cons, lsStripList, (channel *2) +1 , teEvent, tmeCurrentTime);
                  break;
                }

                case AnTavdCeilingLight:
                {
                  vdCeilingLightAnimation(cons, lsStripList, (channel *2) +1 , teEvent, tmeCurrentTime);
                  break;
                }

                case AnTavdChannelLightning:
                {
                  vdChannelLightning(cons, lsStripList, (channel *2) , teEvent, tmeCurrentTime);
                  break;
                }

                // Thanksgiving Animations 

                case AnTavdBlueSky:
                {
                  vdBlueSky(cons, lsStripList, (channel *2) +1 , teEvent, tmeCurrentTime);
                  break;
                }

                case AnTavdNightSkyClose:
                {
                  vdNightSkyClose(cons, lsStripList, (channel *2) +1 , teEvent, tmeCurrentTime);
                  break;
                }

                case AnTavdNightSky:
                {
                  vdNightSky(cons, lsStripList, (channel *2) +1 , teEvent, tmeCurrentTime);
                  break;
                }
                
                case AnTaStripOverOffThanks:
                {
                  vdStripOverOffThanks(cons, lsStripList, (channel *2) +1, teEvent, tmeCurrentTime);
                  break;
                }
                */

                /*
                // Christmas Animtions
                case AnTavdChristmasTree:
                {
                  vdChristmasTree(cons, lsStripList, (channel *2) +1, teEvent, tmeCurrentTime);
                  break; 
                }
                case AnTavdChristmasTreeCo:
                {
                  vdChristmasTreeCo(cons, lsStripList, (channel *2) +1, teEvent, tmeCurrentTime);
                  break; 
                }
                // Christmas Door Open Animations 
                case AnTaDoorOpen00Christmas:
                {
                  vdDoorOpenAnimation00Christmas(cons, lsStripList, channel *2, teEvent, tmeCurrentTime);
                  break;
                }
                case AnTaDoorOpen01Christmas:
                {
                  vdDoorOpenAnimation01Christmas(cons, lsStripList, channel *2, teEvent, tmeCurrentTime);
                  break;
                }
                case AnTaDoorOpen02Christmas:
                {
                  vdDoorOpenAnimation02Christmas(cons, lsStripList, channel *2, teEvent, tmeCurrentTime);
                  break;
                }
                case AnTavdAddOpenChristm:
                {
                  vdAddOpenChristm(cons, lsStripList, channel *2, teEvent, tmeCurrentTime);
                  break;
                }
                case AnTavdAddCloseChristm:
                {
                  vdAddCloseChristm(cons, lsStripList, channel *2, teEvent, tmeCurrentTime);
                  break;
                }
                */


              } // End Case Animation Set
              break;
            } // End Case AnEvSchedule

            case AnEvSetToEnd:  // Schedules an animation to end. Fades out and stops repeat on Pulses.
            {                   // Possible problem if InTime is set to 0.  
              //cons.printwait("Event: AnEvSetToEnd");
              // Clear the Event whether the event ran or not.
              teEvent[channel].teDATA[event].booCOMPLETE = true;   

              // Step through each event in this channel. 
              for (int eventscan = 0; eventscan < teEvent[channel].teDATA.size(); eventscan++)
              {
                // Has the event started running yet, or do we plan on ending future scheduled events also?
                //  Continue with event removal if (event is active) or (clear on end is true)
                if((teEvent[channel].teDATA[eventscan].tmeSTARTTIME <= tmeCurrentTime) || (teEvent[channel].teDATA[event].booCLEARONEND == true))
                {
                  // is the event we are currently looking at within, or overlapping, the targeted event range.
                  if (  ((teEvent[channel].teDATA[eventscan].intSTARTPOS >= teEvent[channel].teDATA[event].intSTARTPOS)  
                        && (teEvent[channel].teDATA[eventscan].intSTARTPOS <= teEvent[channel].teDATA[event].intENDPOS))
                              ||
                        ((teEvent[channel].teDATA[eventscan].intENDPOS >= teEvent[channel].teDATA[event].intSTARTPOS)  
                        && (teEvent[channel].teDATA[eventscan].intENDPOS <= teEvent[channel].teDATA[event].intENDPOS))  )
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
                    if (teEvent[channel].teDATA[event].crgbCOLORSTART1 == CRGB(0,0,0))
                    {
                      booCheckColor = false;
                    }
                    if (teEvent[channel].teDATA[event].strIdent == "")
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
                      if (teEvent[channel].teDATA[event].crgbCOLORSTART1 == teEvent[channel].teDATA[eventscan].crgbCOLORSTART1)
                      {
                        cont = true;
                      }
                      else if (teEvent[channel].teDATA[event].crgbCOLORSTART1 == teEvent[channel].teDATA[eventscan].crgbCOLORSTART2)
                      {
                        cont = true;
                      }
                      else if (teEvent[channel].teDATA[event].crgbCOLORSTART1 == teEvent[channel].teDATA[eventscan].crgbCOLORDEST1)
                      {
                        cont = true;
                      }
                      else if (teEvent[channel].teDATA[event].crgbCOLORSTART1 == teEvent[channel].teDATA[eventscan].crgbCOLORDEST2)
                      {
                        cont = true;
                      }
                    }
                    else if (booCheckIdent == true)
                    {
                      //We are only targeting events with specific Identification.  Need a match on any.
                      if (teEvent[channel].teDATA[event].strIdent == teEvent[channel].teDATA[eventscan].strIdent)
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
                      if (event != eventscan)
                      {

                        // End Animations

                        // Manage the Fade Animations to End.
                        if (  (teEvent[channel].teDATA[eventscan].bytLEDANIMATION == AnPiFade)     ||
                              (teEvent[channel].teDATA[eventscan].bytLEDANIMATION == AnPiFadeDith)  )
                        {
                          // Stop the event.
                          teEvent[channel].teDATA[eventscan].booREPEAT = false;
                          teEvent[channel].teDATA[eventscan].booCLEARONEND = true;
                          
                          teEvent[channel].teDATA[eventscan].intDURATION = teEvent[channel].teDATA[event].intDURATION;
                          teEvent[channel].teDATA[eventscan].tmeSTARTTIME = tmeCurrentTime;

                          //teEvent[channel].teDATA[eventscan].intSPEED =  teEvent[channel].teDATA[event].intSPEED;
                          teEvent[channel].teDATA[eventscan].intSPEED =  0;
                          // The above two lines will need to be addressed at a future date. 
                          //  Problem occurs when an event current time is before the start 
                          //  pixel update begins. This mean that the start color will not be set until current 
                          //  time is past start time.  Need to choose: apples or oranges during 
                          //  the crgb_anim_color and event routine.

                          if (teEvent[channel].teDATA[event].booREPEAT == false)
                          {
                            teEvent[channel].teDATA[eventscan].crgbCOLORSTART1 = teEvent[channel].teDATA[eventscan].crgbCOLORDEST1;
                            teEvent[channel].teDATA[eventscan].crgbCOLORSTART2 = teEvent[channel].teDATA[eventscan].crgbCOLORDEST2;
                          }
                          else
                          {
                            teEvent[channel].teDATA[eventscan].crgbCOLORSTART1 = teEvent[channel].teDATA[eventscan].crgbCOLORDEST1;
                            teEvent[channel].teDATA[eventscan].crgbCOLORSTART2 = teEvent[channel].teDATA[eventscan].crgbCOLORDEST2;
                            teEvent[channel].teDATA[eventscan].crgbCOLORDEST1 = teEvent[channel].teDATA[event].crgbCOLORDEST1;
                            teEvent[channel].teDATA[eventscan].crgbCOLORDEST2 = teEvent[channel].teDATA[event].crgbCOLORDEST2;
                            // Unfinished color swap.  Left as is to avoid changing animations before installation.
                            //teEvent[channel].teDATA[eventscan].crgbCOLORDEST1 = teEvent[channel].teDATA[event].crgbCOLORSTART1;
                            //teEvent[channel].teDATA[eventscan].crgbCOLORDEST2 = teEvent[channel].teDATA[event].crgbCOLORSTART2;                             
                          }
                        }

                        // and
                        // End Pusles

                        // Manage the Pulse Animations to End
                        if (  (teEvent[channel].teDATA[eventscan].bytLEDANIMATION == AnPiPulse)    ||
                              (teEvent[channel].teDATA[eventscan].bytLEDANIMATION == AnPiPulseTo)  )
                        {
                          // Tell the pulse to stop.
                          if (teEvent[channel].teDATA[event].booREPEAT == false)
                          {
                            // For now, we will just kill it and hope another animation clears the artifacts.
                            // It would be nice to have a gracreful end and let the pixel end its animation,
                            // but, thats for another time.
                            
                            // Stop the event.
                            teEvent[channel].teDATA[eventscan].booREPEAT = false;
                            teEvent[channel].teDATA[eventscan].booCLEARONEND = true;
                            
                            teEvent[channel].teDATA[eventscan].booCOMPLETE = true;
                          }
                          else
                          {
                            // Pulse will end on its on at end of animation.
                            teEvent[channel].teDATA[eventscan].booREPEAT = false;
                            teEvent[channel].teDATA[eventscan].booCLEARONEND = true;
                          }
                        }

                        // and
                        // End Scheduled Events

                        if (teEvent[channel].teDATA[eventscan].bytANIMATION == AnEvSchedule)
                        {
                          // Stop the event.
                          teEvent[channel].teDATA[eventscan].booREPEAT = false;
                          teEvent[channel].teDATA[eventscan].booCLEARONEND = true;

                          teEvent[channel].teDATA[eventscan].booCOMPLETE = true;
                        }

                      } // End Event not Self 
                    } // End If Event in Search Criteria
                  } // End If Event in Range
                } // End If Time Start
              } // End For Event Check       
              break;
            } // End Case AnEvSetToEnd

          } // End Switch 
        } // End If time check
      } // End FOR event
    } // If datasize >0
  } // End FOR strip
}



#endif