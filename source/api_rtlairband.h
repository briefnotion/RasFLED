// ***************************************************************************************
// *
// *    Core       | Everything within this document is proprietary to Core Dynamics.
// *    Dynamics   | Any unauthorized duplication will be subject to prosecution.
// *
// *    Department : (R+D)^2                        Name: api_rtlairband.h
// *       Sub Dept: Programming
// *    Location ID: 856-45B
// *                                                      (c) 2856 - 2858 Core Dynamics
// ***************************************************************************************
// *
// *  PROJECTID: gi6$b*E>*q%;    Revision: 00000000.03A
// *  TEST CODE:                 QACODE: A565              CENSORCODE: EQK6}Lc`:Eg>
// *
// ***************************************************************************************

#ifndef API_RTLAIRBAND_H
#define API_RTLAIRBAND_H

// Standard Header Files
#include <string.h>

using namespace std;
//using namespace boost::filesystem;

class API_SQUELCH
{
  public:

  // Hold variable prevents reading or writing, in case another program is accessing  
  //  the data and a delay has occured. 

  bool HOLD = false;

  // Information to Send
  // Channel Info
  int FREQUENCY = 0;  // needs / 1000000.0
  string label = "";

  // Channel Squelch Info
  float NOISE_LEVEL = 0;
  float SIGNAL_LEVEL = 0;

  bool SIGNAL_OUTSIDE_FILTER = false;

  // Is Channel Open
  bool IS_OPEN = false;
};


#endif