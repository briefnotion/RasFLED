// ***************************************************************************************
// *
// *    Core       | Everything within this document is proprietary to Core Dynamics.
// *    Dynamics   | Any unauthorized duplication will be subject to prosecution.
// *
// *    Department : (R+D)^2                        Name: radio_channel_coordinator.cpp
// *       Sub Dept: Programming
// *    Location ID: 856-45B
// *                                                      (c) 2856 - 2858 Core Dynamics
// ***************************************************************************************

#ifndef RADIO_CHANNEL_COORDINATOR_CPP
#define RADIO_CHANNEL_COORDINATOR_CPP

#include "radio_channel_coordinator.h"

using namespace std;

int RADIO_CHANNEL_COORDINATOR::size()
// Returns size, or amount, of Channels stred in the Channels deque.
{
  return CHANNELS.size();
  //return 2;
}

void RADIO_CHANNEL_COORDINATOR::process_command_received(API_COMMAND &Command_Received)
// Process command recieved into radio coordinator
{
  if (Command_Received.CHANGED == true)
  {

    if (Command_Received.COMMAND == 1 || Command_Received.COMMAND == 2 || Command_Received.COMMAND == 4)
    {

      int pos_found = -1;

      // Seach the Channels for existing Squelch Channel
      for (int pos = 0; (pos < CHANNELS.size()) && (pos_found == -1); pos++)
      {
        if (radio_translate_to_frequency_6(CHANNELS[pos].FREQUENCY.FREQUENCY) == Command_Received.PARAMETER)
        {
          pos_found = pos;
        }
      }

      if (pos_found > -1)
      {
        if (Command_Received.COMMAND == 1)
        {
          CHANNELS[pos_found].PROP.SKIP = true;
          CHANNELS[pos_found].PROP.CHANGED = true;
        }
        else if (Command_Received.COMMAND == 2)
        {
          CHANNELS[pos_found].PROP.HELD = true;
          CHANNELS[pos_found].PROP.CHANGED = true;
        }          
        else if (Command_Received.COMMAND == 4)
        {
          CHANNELS[pos_found].PROP.SKIP = false;
          CHANNELS[pos_found].PROP.HELD = false;
          CHANNELS[pos_found].PROP.CHANGED = true;
        }
      }
    }
    else if (Command_Received.COMMAND == 3)
    {
      // Seach the Channels for existing Squelch Channel
      for (int pos = 0; pos < CHANNELS.size(); pos++)
      {
        CHANNELS[pos].PROP.SKIP = false;
        CHANNELS[pos].PROP.HELD = false;
        CHANNELS[pos].PROP.CHANGED = true;
      }
    }

    Command_Received.CHANGED = false;
  }
}

void RADIO_CHANNEL_COORDINATOR::process(API_SQUELCH_DESTINATION &Received_Squelch)
// Stores fresh frequency squelch received into CHANNELS deque.
//  If freqency data already exist, replaces.
//  If freqency data doesn't exist, add to end of deque.
{
  if (PLAY == true)
  {
    LAST_READ_BIND_COUNT = Received_Squelch.MANAGER.BINDS;

    if (Received_Squelch.DEVICE.CHANGED == true)
    {
      // Store Status
      DEVICE_STATUS.ACTIVE = Received_Squelch.DEVICE.ACTIVE;
      DEVICE_STATUS.DEVICE = Received_Squelch.DEVICE.DEVICE;
      DEVICE_STATUS.GAIN = Received_Squelch.DEVICE.GAIN;

      DEVICE_STATUS.CHANGED = true;

      Received_Squelch.DEVICE.CHANGED = false;
    }

    if (Received_Squelch.FREQUENCY.CHANGED == true)
    {
      int pos_found = -1;

      // Seach the Channels for existing Squelch Channel
      for (int pos = 0; (pos < CHANNELS.size()) && (pos_found == -1); pos++)
      {
        if (CHANNELS[pos].FREQUENCY.FREQUENCY == Received_Squelch.FREQUENCY.FREQUENCY)
        {
          pos_found = pos;
        }
      }
      
      if (pos_found >= 0) // If found, change the data.
      {
        CHANNELS[pos_found].FREQUENCY = Received_Squelch.FREQUENCY;
      }
      else if (Received_Squelch.FREQUENCY.FREQUENCY != 0)  // If not found, add it. 
      // Only add if not empty frequency.
      {
        CHANNELS.push_back(Received_Squelch);
      }
      
      Received_Squelch.FREQUENCY.CHANGED = false;
    }
  }
}

void RADIO_CHANNEL_COORDINATOR::pause()
{
  PLAY = false;
}

void RADIO_CHANNEL_COORDINATOR::play()
{
  PLAY = true;
}

bool RADIO_CHANNEL_COORDINATOR::is_paused()
{
  return PLAY;
}

void RADIO_CHANNEL_COORDINATOR::command_send(int Command, int Parameter)
{
  COMMAND_TO_RADIO.COMMAND = Command;
  COMMAND_TO_RADIO.PARAMETER = Parameter;
  COMMAND_TO_RADIO.CHANGED = true;
}




#endif