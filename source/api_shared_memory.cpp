// ***************************************************************************************
// *
// *    Core       | Everything within this document is proprietary to Core Dynamics.
// *    Dynamics   | Any unauthorized duplication will be subject to prosecution.
// *
// *    Department : (R+D)^2                        Name: api_shared_memory.h
// *       Sub Dept: Programming
// *    Location ID: 856-45B
// *                                                      (c) 2856 - 2858 Core Dynamics
// ***************************************************************************************
// *
// *  PROJECTID: gi6$b*E>*q%;    Revision: 00000000.13A
// *  TEST CODE:                 QACODE: A565              CENSORCODE: EQK6}Lc`:Eg>
// *
// ***************************************************************************************

#include "api_shared_memory.h"

using namespace std;
using namespace boost::interprocess;

void API_CHANNEL_MEM::put(SILLY_STRING &Destination, char *Source)
// Translate a char* string to a fixed size character array at memory location.
{
  int size = 0;

  for (int pos = 0; Source[pos] != 0 && pos < SIZE_TEXT_MAX; pos++)
  {
    size++;
    Destination.TEXT[pos] = Source[pos];
  }

  Destination.SIZE = size;
}

string API_CHANNEL_MEM::get(SILLY_STRING &Source)
// Translate fixed size character array at memory location to a string.
{
  int size = 0;
  string return_string = "";

  size = Source.SIZE;

  for(int pos = 0; pos < size && pos < SIZE_TEXT_MAX; pos++)
  {
    return_string = return_string + Source.TEXT[pos];
  }

  return return_string;
}

// Start or Stop the API.
bool PAUSE = false;

#ifndef RASFLED
// Copy information to shared variables

// rtl_airband Routines
void API_CHANNEL_MEM::rtl_airband_get_squelch(API_SQUELCH_SOURCE &API_Squelch, freq_t *fparms)
// Get freq info.
{

  API_Squelch.FREQUENCY.FREQUENCY = fparms->frequency;
  put(API_Squelch.FREQUENCY.LABEL, fparms->label);
  API_Squelch.FREQUENCY.NOISE_LEVEL = level_to_dBFS(fparms->squelch.noise_level());
  API_Squelch.FREQUENCY.SIGNAL_LEVEL = level_to_dBFS(fparms->squelch.signal_level());
  API_Squelch.FREQUENCY.SIGNAL_OUTSIDE_FILTER = fparms->squelch.signal_outside_filter();
  API_Squelch.FREQUENCY.IS_OPEN = fparms->squelch.is_open();

}

// rtl_airband Routines
void API_CHANNEL_MEM::rtl_airband_send_squelch(mapped_region &region_scan, API_SQUELCH_SOURCE &API_Squelch, API_COMMAND &Command_Send, API_COMMAND &Command_Recv)
// Send freq info.
// Will not send if PAUSE == true.
// Will not send if Destination has not ACKed ready.
{
  if (PAUSE == false)
  {
    // Get the address of the data
    API_SQUELCH_SOURCE *SQUELCH = static_cast<API_SQUELCH_SOURCE*>(region_scan.get_address());

    if ((*SQUELCH).HANDOFF == 0 || (*SQUELCH).HANDOFF == -1)
    // Prevent data being read if the packet hasn't been completely written.
    {
      (*SQUELCH).FREQUENCY.FREQUENCY = API_Squelch.FREQUENCY.FREQUENCY;
      (*SQUELCH).FREQUENCY.LABEL = API_Squelch.FREQUENCY.LABEL;
      (*SQUELCH).FREQUENCY.NOISE_LEVEL = API_Squelch.FREQUENCY.SIGNAL_LEVEL;
      (*SQUELCH).FREQUENCY.SIGNAL_LEVEL = API_Squelch.FREQUENCY.SIGNAL_LEVEL;
      (*SQUELCH).FREQUENCY.SIGNAL_OUTSIDE_FILTER = API_Squelch.FREQUENCY.SIGNAL_OUTSIDE_FILTER;
      (*SQUELCH).FREQUENCY.IS_OPEN = API_Squelch.FREQUENCY.IS_OPEN;

      (*SQUELCH).FREQUENCY.CHANGED = true;

      // Send out command.
      if (Command_Send.CHANGED == true)
      {
        (*SQUELCH).DEVICE.COMMAND_FROM_RADIO.COMMAND = Command_Send.COMMAND;
        (*SQUELCH).DEVICE.COMMAND_FROM_RADIO.PARAMETER = Command_Send.PARAMETER;

        (*SQUELCH).DEVICE.COMMAND_FROM_RADIO.CHANGED = true;
        Command_Send.CHANGED = false
      }

      // Receive Command
      if ((*SQUELCH).DEVICE.COMMAND_TO_RADIO.CHANGED == true)
      {
      Command_Recv.COMMAND = (*SQUELCH).DEVICE.COMMAND_TO_RADIO.COMMAND;
      Command_Recv.PARAMETER = (*SQUELCH).DEVICE.COMMAND_TO_RADIO.PARAMETER;

      Command_Recv.CHANGED = true;
      (*SQUELCH).DEVICE.COMMAND_TO_RADIO.CHANGED = false;
      }

      (*SQUELCH).HANDOFF = 1;
    }
  }

}

void API_CHANNEL_MEM::rtl_airband_send_device(mapped_region &region_scan, int Device, float Gain)
// Send freq info.
// Will not send if PAUSE == true.
// Will not send if Destination has not ACKed ready.
{
  if (PAUSE == false)
  {
    // Get the address of the data
    API_SQUELCH_SOURCE *SQUELCH = static_cast<API_SQUELCH_SOURCE*>(region_scan.get_address());
    
    if ((*SQUELCH).HANDOFF == 0 || (*SQUELCH).HANDOFF == -1)
    // Prevent data being read if the packet hasn't been completely written.
    {
      (*SQUELCH).DEVICE.DEVICE = Device;
      (*SQUELCH).DEVICE.GAIN = Gain;

      (*SQUELCH).DEVICE.ACTIVE = true;

      (*SQUELCH).DEVICE.CHANGED = true;
      
      (*SQUELCH).HANDOFF = 1;
    }
  }
}
#endif


// Ras_FLED Routines
int API_CHANNEL_MEM::rasfled_receive(mapped_region &region_scan, API_SQUELCH_DESTINATION &API_Squelch, API_COMMAND &Command_Send, API_COMMAND &Command_Recv)
// Receive freq info.
// Will not send if PAUSE == true.
// Will not send if Source has not ACKed ready.
{
  int return_int = -1;

  if (PAUSE == false)
  {
    // Get the address of the data
    API_SQUELCH_SOURCE *SQUELCH = static_cast<API_SQUELCH_SOURCE*>(region_scan.get_address());

    if ((*SQUELCH).HANDOFF == 0 || (*SQUELCH).HANDOFF == 1)
    // Prevent data being read if the packet hasn't been completely written.
    {
      API_Squelch.MANAGER.BINDS = (*SQUELCH).MANAGER.BINDS;

      if ((*SQUELCH).DEVICE.CHANGED == true)
      {
        // Device Information
        API_Squelch.DEVICE.DEVICE = (*SQUELCH).DEVICE.DEVICE;
        API_Squelch.DEVICE.ACTIVE = (*SQUELCH).DEVICE.ACTIVE;
        API_Squelch.DEVICE.GAIN = (*SQUELCH).DEVICE.GAIN;

        API_Squelch.DEVICE.CHANGED = true;
        (*SQUELCH).DEVICE.CHANGED = false;
      }

      // Frequency Information
      if ((*SQUELCH).FREQUENCY.CHANGED == true)
      {
        API_Squelch.FREQUENCY.FREQUENCY = (*SQUELCH).FREQUENCY.FREQUENCY;

        string not_silly = get((*SQUELCH).FREQUENCY.LABEL);
        API_Squelch.FREQUENCY.LABEL = not_silly;
        
        API_Squelch.FREQUENCY.NOISE_LEVEL = (*SQUELCH).FREQUENCY.NOISE_LEVEL;
        API_Squelch.FREQUENCY.SIGNAL_LEVEL = (*SQUELCH).FREQUENCY.SIGNAL_LEVEL;
        API_Squelch.FREQUENCY.SIGNAL_OUTSIDE_FILTER = (*SQUELCH).FREQUENCY.SIGNAL_OUTSIDE_FILTER;
        API_Squelch.FREQUENCY.IS_OPEN = (*SQUELCH).FREQUENCY.IS_OPEN;

        API_Squelch.FREQUENCY.CHANGED = true;
        (*SQUELCH).FREQUENCY.CHANGED = false;
      }

      // Receive Command
      if ((*SQUELCH).COMMAND_FROM_RADIO.CHANGED == true)
      {
        Command_Recv.COMMAND = (*SQUELCH).COMMAND_FROM_RADIO.COMMAND;
        Command_Recv.PARAMETER = (*SQUELCH).COMMAND_FROM_RADIO.PARAMETER;
        
        Command_Recv.CHANGED = true;
        (*SQUELCH).COMMAND_FROM_RADIO.CHANGED = false;
      }

      // Send Command
      if (Command_Send.CHANGED == true)
      {
        (*SQUELCH).COMMAND_TO_RADIO.COMMAND = Command_Send.COMMAND;
        (*SQUELCH).COMMAND_TO_RADIO.PARAMETER = Command_Send.PARAMETER;

        (*SQUELCH).COMMAND_TO_RADIO.CHANGED = true;
        Command_Send.CHANGED = false;
      }

      // Return Handoff
      (*SQUELCH).HANDOFF = -1;

      // return ok.
      return_int = 0;
    }    
    else
    {
      // return held.
      return_int = 2;
    }
  }
  else
  {
    // return paused.
    return_int = 1;
  }

  // return signal
  return return_int;
}

int API_CHANNEL_MEM::get_binds(mapped_region &region_scan)
// Returns the number of programs suspected accessing the API.
{
  API_SQUELCH_SOURCE *SQUELCH = static_cast<API_SQUELCH_SOURCE*>(region_scan.get_address());

  return (*SQUELCH).MANAGER.BINDS;
}

void API_CHANNEL_MEM::open(mapped_region &region_scan)
// Tell API access has started to track when memory should be cleared.
{
  API_SQUELCH_SOURCE *SQUELCH = static_cast<API_SQUELCH_SOURCE*>(region_scan.get_address());
  // Prepare memory space, if not done so.

  // First start routines.
  if ((*SQUELCH).MANAGER.BINDS == 0)
  {
    (*SQUELCH).MANAGER.BINDS = 1;
  }
  else
  {
    (*SQUELCH).MANAGER.BINDS = 2;
  }
}

void API_CHANNEL_MEM::close(mapped_region &region_scan)
// Tell API access has ended to track when memory should be cleared.
{
  API_SQUELCH_SOURCE *SQUELCH = static_cast<API_SQUELCH_SOURCE*>(region_scan.get_address());
  (*SQUELCH).DEVICE.ACTIVE = false;
  (*SQUELCH).DEVICE.CHANGED = true;
  
  (*SQUELCH).MANAGER.BINDS--;
}