// ***************************************************************************************
// *
// *    Core       | Everything within this document is proprietary to Core Dynamics.
// *    Dynamics   | Any unauthorized duplication will be subject to prosecution.
// *
// *    Department : (R+D)^2                        Name: radio_channel_coordinator.h
// *       Sub Dept: Programming
// *    Location ID: 856-45B
// *                                                      (c) 2856 - 2858 Core Dynamics
// ***************************************************************************************

#ifndef RADIO_CHANNEL_COORDINATOR_H
#define RADIO_CHANNEL_COORDINATOR_H

#include <deque>

#include "api_rtlairband.h"

using namespace std;

class RADIO_CHANNEL_COORDINATOR
{
  private:

  public:

  // Stores all the frequencies observed and parsed into frequencies.
  deque<API_SQUELCH> CHANNELS;
  
  int size()
  // Returns size, or amount, of Channels stred in the Channels deque.
  {
    return CHANNELS.size();
    //return 2;
  }

  void process(API_SQUELCH Received_Squelch)
  // Stores fresh frequency squelch received into CHANNELS deque.
  //  If freqency data already exist, replaces.
  //  If freqency data doesn't exist, add to end of deque.
  {
    //if (Received_Squelch.CHANGED == true)
    {
      int pos_found = -1;

      // Seach the Channels for existing Squelch Channel
      for (int pos = 0; (pos < CHANNELS.size()) && (pos_found == -1); pos++)
      {
        if (CHANNELS[pos].FREQUENCY == Received_Squelch.FREQUENCY)
        {
          pos_found = pos;
        }
      }
      
      if (pos_found >= 0) // If found, change the data.
      {
        CHANNELS[pos_found].FREQUENCY = Received_Squelch.FREQUENCY;
        CHANNELS[pos_found].NOISE_LEVEL = Received_Squelch.NOISE_LEVEL;
        CHANNELS[pos_found].SIGNAL_LEVEL = Received_Squelch.SIGNAL_LEVEL;
        CHANNELS[pos_found].SIGNAL_OUTSIDE_FILTER = Received_Squelch.SIGNAL_OUTSIDE_FILTER;
        CHANNELS[pos_found].IS_OPEN = Received_Squelch.IS_OPEN;
        CHANNELS[pos_found].CHANGED = true;
      }
      else  // If not found, add it. 
      {
        CHANNELS.push_back(Received_Squelch);
      }
      Received_Squelch.CHANGED = false;
    }
  }

};



#endif