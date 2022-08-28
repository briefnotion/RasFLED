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
#include "definitions.h"
#include "api_rtlairband.h"

using namespace std;
using namespace boost::interprocess;

class API_CHANNEL_MEM
// Control communications to and from another program.
{
  private:

  int SIZE_TEXT_MAX = 50;

  void put(SILLY_STRING &Destination, char *Source);

  string get(SILLY_STRING &Source);

  public:

  // Start or Stop the API.
  bool PAUSE = false;

  #ifndef RASFLED
  // Copy information to shared variables

  // rtl_airband Routines
  void rtl_airband_get_squelch(API_SQUELCH_SOURCE &API_Squelch, freq_t *fparms);

  // rtl_airband Routines
  void rtl_airband_send_squelch(mapped_region &region_scan, API_SQUELCH_SOURCE &API_Squelch, API_COMMAND &Command_Send, API_COMMAND &Command_Recv);

  void rtl_airband_send_device(mapped_region &region_scan, int Device, float Gain);
  #endif

  // Ras_FLED Routines
  int rasfled_receive(mapped_region &region_scan, API_SQUELCH_DESTINATION &API_Squelch, API_COMMAND &Command_Send, API_COMMAND &Command_Recv);

  int get_binds(mapped_region &region_scan);

  void open(mapped_region &region_scan);

  void close(mapped_region &region_scan);
};



#endif