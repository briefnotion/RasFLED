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
// *  PROJECTID: gi6$b*E>*q%;    Revision: 00000000.11A
// *  TEST CODE:                 QACODE: A565              CENSORCODE: EQK6}Lc`:Eg>
// *
// ***************************************************************************************

#ifndef API_H
#define API_H

// Standard Header Files
#include <fstream>
#include <iostream>
#include <string.h>

// vvvv --- Change these things to customize the API --- vvvv
// rtl_airband Classes

//#include "squelch.h"    // Commented in or out.

// Boost libraries
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>

// New Classes
#include "api_rtlairband.h"

using namespace std;
using namespace boost::interprocess;
//using namespace boost::filesystem;

class API_CHANNEL_MEM
// Control communications to and from another program.
{
  private:

  int SIZE_TEXT_MAX = 50;

  void put(SILLY_STRING &Destination, char *Source)
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

  string get(SILLY_STRING &Source)
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

  public:

  // Start or Stop the API.
  bool PAUSE = false;

  #ifndef RASFLED
  // Copy information to shared variables

  // rtl_airband Routines
  void rtl_airband_send_squelch(mapped_region &region_scan, freq_t *fparms)
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
        (*SQUELCH).FREQUENCY = fparms->frequency;
        put((*SQUELCH).LABEL, fparms->label);
        (*SQUELCH).NOISE_LEVEL = level_to_dBFS(fparms->squelch.noise_level());
        (*SQUELCH).SIGNAL_LEVEL = level_to_dBFS(fparms->squelch.signal_level());
        (*SQUELCH).SIGNAL_OUTSIDE_FILTER = fparms->squelch.signal_outside_filter();
        (*SQUELCH).IS_OPEN = fparms->squelch.is_open();

        (*SQUELCH).CHANGED = true;

        (*SQUELCH).HANDOFF = 1;
      }
    }
  }

  // rtl_airband Routines
  void rtl_airband_send_squelch_2(mapped_region &region_scan, API_SQUELCH_SOURCE &API_Squelch, int &Send_Command)
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
        (*SQUELCH) = API_Squelch;

        (*SQUELCH).DEVICE.COMMAND = Send_Command;

        (*SQUELCH).CHANGED = true;

        (*SQUELCH).HANDOFF = 1;
      }
    }
  }

  void rtl_airband_send_device(mapped_region &region_scan, int Device, float Gain)
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
  int rasfled_receive(mapped_region &region_scan, API_SQUELCH_DESTINATION &API_Squelch, int &Send_Command)
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
        if ((*SQUELCH).DEVICE.CHANGED == true)
        {
          // Device Information
          API_Squelch.DEVICE = (*SQUELCH).DEVICE;

          API_Squelch.DEVICE.CHANGED = true;
          (*SQUELCH).DEVICE.CHANGED = false;
        }

        // Frequency Information
        if ((*SQUELCH).CHANGED == true)
        {
          API_Squelch.FREQUENCY = (*SQUELCH).FREQUENCY;

          string not_silly = get((*SQUELCH).LABEL);
          API_Squelch.LABEL = not_silly;
          
          API_Squelch.NOISE_LEVEL = (*SQUELCH).NOISE_LEVEL;
          API_Squelch.SIGNAL_LEVEL = (*SQUELCH).SIGNAL_LEVEL;
          API_Squelch.SIGNAL_OUTSIDE_FILTER = (*SQUELCH).SIGNAL_OUTSIDE_FILTER;
          API_Squelch.IS_OPEN = (*SQUELCH).IS_OPEN;

          API_Squelch.CHANGED = true;
          (*SQUELCH).CHANGED = false;
        }

        // Set Send Command
        (*SQUELCH).DEVICE.COMMAND = Send_Command;

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

  int get_binds(mapped_region &region_scan)
  // Returns the number of programs suspected accessing the API.
  {
    API_SQUELCH_SOURCE *SQUELCH = static_cast<API_SQUELCH_SOURCE*>(region_scan.get_address());

    return (*SQUELCH).MANAGER.BINDS;
  }

  void open(mapped_region &region_scan)
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

  void close(mapped_region &region_scan)
// Tell API access has ended to track when memory should be cleared.
  {
    API_SQUELCH_SOURCE *SQUELCH = static_cast<API_SQUELCH_SOURCE*>(region_scan.get_address());
    (*SQUELCH).MANAGER.BINDS--;
  }
};



#endif