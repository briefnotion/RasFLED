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
// *  PROJECTID: gi6$b*E>*q%;    Revision: 00000000.04A
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

// To place in calling program:
  // Prepare Shared Memory Space.
  //shared_memory_object shdmem{open_or_create, "Boost", read_write};
  //shdmem.truncate(1024);
  //mapped_region region{shdmem, read_write};

// ^^^^ --- Change these things to customize the API --- ^^^^

using namespace std;
using namespace boost::interprocess;
//using namespace boost::filesystem;

class API_CHANNEL_MEM
{
  private:

  bool FIRST_RUN = true;

  void prep()
  {
    // Preperations have been made.
    FIRST_RUN = false;    
  }

  void int_set_if_changed(int &Store, int &Receive, bool &Changed)
  {
    if(Store != Receive)
    {
      Store = Receive;
      Changed = true;
    }
  }

  void float_set_if_changed(float &Store, float &Receive, bool &Changed)
  {
    if(Store != Receive)
    {
      Store = Receive;
      Changed = true;
    }
  }

  void bool_set_if_changed(bool &Store, bool &Receive, bool &Changed)
  {
    if(Store != Receive)
    {
      Store = Receive;
      Changed = true;
    }
  }

  public:

  // Start or Stop the API.
  bool PAUSE = false;

  // Copy information to shared variables

  /*
  // rtl_airband Routines
  void rtl_airband_send(mapped_region &region, freq_t *fparms)
  {
    if (PAUSE == false)
    {
      // Prepare memory space, if not done so.
      if (FIRST_RUN == true)
      {
        // First start routines.
        prep();
      }

      // Get the address of the data
      API_SQUELCH *SQUELCH = static_cast<API_SQUELCH*>(region.get_address());

      if ((*SQUELCH).HOLD == false)
      // Prevent data being read if the packet hasn't been completely written.
      {
        (*SQUELCH).HOLD = true;

        (*SQUELCH).FREQUENCY = fparms->frequency;
        //(*SQUELCH).LABEL = fparms->label;
        (*SQUELCH).NOISE_LEVEL = level_to_dBFS(fparms->squelch.noise_level());
        (*SQUELCH).SIGNAL_LEVEL = level_to_dBFS(fparms->squelch.signal_level());
        (*SQUELCH).SIGNAL_OUTSIDE_FILTER = fparms->squelch.signal_outside_filter();
        (*SQUELCH).IS_OPEN = fparms->squelch.is_open();

        (*SQUELCH).CHANGED = true;

        (*SQUELCH).HOLD = false;
      }
    }
  }
  */

  
  // Ras_FLED Routines
  void rasfled_receive(mapped_region &region, API_SQUELCH &API_Squelch)
  {
    if (PAUSE == false)
    {
      // Prepare memory space, if not done so.
      if (FIRST_RUN == true)
      {
        // First start routines.
        prep();
      }

      // Get the address of the data
      API_SQUELCH *SQUELCH = static_cast<API_SQUELCH*>(region.get_address());

      if ((*SQUELCH).HOLD == false)
      // Prevent data being read if the packet hasn't been completely written.
      {
        (*SQUELCH).HOLD = true;

        int_set_if_changed(API_Squelch.FREQUENCY, (*SQUELCH).FREQUENCY, API_Squelch.CHANGED);
        float_set_if_changed(API_Squelch.NOISE_LEVEL, (*SQUELCH).NOISE_LEVEL, API_Squelch.CHANGED);
        float_set_if_changed(API_Squelch.SIGNAL_LEVEL, (*SQUELCH).SIGNAL_LEVEL, API_Squelch.CHANGED);
        bool_set_if_changed(API_Squelch.SIGNAL_OUTSIDE_FILTER, (*SQUELCH).SIGNAL_OUTSIDE_FILTER, API_Squelch.CHANGED);
        bool_set_if_changed(API_Squelch.IS_OPEN, (*SQUELCH).IS_OPEN, API_Squelch.CHANGED);

        (*SQUELCH).CHANGED = false;

        (*SQUELCH).HOLD = false;
      }
    }
  }
  
};



#endif