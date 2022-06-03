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
// *  PROJECTID: gi6$b*E>*q%;    Revision: 00000000.08A
// *  TEST CODE:                 QACODE: A565              CENSORCODE: EQK6}Lc`:Eg>
// *
// ***************************************************************************************

#ifndef API_RTLAIRBAND_H
#define API_RTLAIRBAND_H

// Standard Header Files
#include <string.h>

using namespace std;
//using namespace boost::filesystem;

class SILLY_STRING
{
  private:

  public:
  
  int SIZE = 0;
  char TEXT[50];
};

class API_MANAGER
// API Management variables.
{
  public:

  int BINDS = 0;
};

class API_SQUELCH_DESTINATION
// Sanitized API packet.
{
  public:

  // Information to Send
  // Channel Info
  int FREQUENCY = 0;  // needs / 1000000.0

  // Channel Label
  string LABEL;

  // Channel Squelch Info
  float NOISE_LEVEL = 0;
  float SIGNAL_LEVEL = 0;

  bool SIGNAL_OUTSIDE_FILTER = false;

  // Is Channel Open
  bool IS_OPEN = false;
  
  // Has Changed
  bool CHANGED = false;
};

class API_SQUELCH_SOURCE
// API packet.
{
  public:
 
  // API Manager
  API_MANAGER MANAGER;
  
  // Hold variable prevents reading or writing, in case another program is accessing  
  //  the data and a delay has occured. 

  int HANDOFF = 0;

  // Information to Send
  // Channel Info
  int FREQUENCY = 0;  // needs / 1000000.0

  // Channel Label
  SILLY_STRING LABEL;

  // Channel Squelch Info
  float NOISE_LEVEL = 0;
  float SIGNAL_LEVEL = 0;

  bool SIGNAL_OUTSIDE_FILTER = false;

  // Is Channel Open
  bool IS_OPEN = false;
  
  // Has Changed
  bool CHANGED = false;
};


#endif