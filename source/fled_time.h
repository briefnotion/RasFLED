// ***************************************************************************************
// *
// *    Core       | Everything within this document is proprietary to Core Dynamics.
// *    Dynamics   | Any unauthorized duplication will be subject to prosecution.
// *
// *    Department : (R+D)^2                        Name: fled_time.h
// *       Sub Dept: Programming
// *    Location ID: 856-45B
// *                                                      (c) 2856 - 2858 Core Dynamics
// ***************************************************************************************
// *
// *  PROJECTID: gi6$b*E>*q%;    Revision: 00000000.01A
// *  TEST CODE:                 QACODE: A565              CENSORCODE: EQK6}Lc`:Eg>
// *
// ***************************************************************************************

#ifndef FLED_TIME_H
#define FLED_TIME_H

// Standard Header Files
#include <chrono>
#include <ctime>

using namespace std;

// -------------------------------------------------------------------------------------
// Time Variable
class FLED_TIME_VAR
{
  private:
  // time starts at jan 1 1970
  unsigned long SECONDS = 0;
  int MICRO_SECONDS = 0;   // 1*10^-6 Seconds

  time_t THE_TIME;
  tm *PTM;
  bool TIME_UPDATED = false;

  void update_time();

  public:
  void put_seconds(unsigned long Seconds);

  void put_deciseconds(int Deciseconds);

  void put_miliseconds(int Miliseconds);

  unsigned long get_seconds();

  int get_deciseconds();

  int get_miliseconds();

  int get_year();

  int get_month();

  int get_day();

  int get_hour();

  int get_minute();
  
  int get_second();
};


// -------------------------------------------------------------------------------------
// Keeps track of timing variables
class FledTime
{
  private:
  std::chrono::time_point<std::chrono::system_clock> tmeStart;
  std::chrono::time_point<std::chrono::system_clock> tmeFrame;

  bool first_run = true;

  void set();

  public:

  double tmeFrameMillis;

  double now();

  void setframetime();

  double tmeFrameElapse();
};

// ---------------------------------------------------------------------------------------
class TIMED_IS_READY
// Class to manage conditions of when something needs to be ran.
{
  private:
  unsigned long TRIGGERED_TIME  = 0;  //  Most recent time the ready was activated
  unsigned long LAST_ASKED_TIME = 0;  //  Most recent time the variable was asked if was ready.
  unsigned long READY_TIME      = 0;  //  Calculated time of when variable will be ready.
  int           INTREVAL        = 0;  //  Time in miliseconds between ready.

  public:

  bool is_set();

  void set(unsigned long current_time, int delay);

  void set(int delay);

  unsigned long get_ready_time();

  bool is_ready(unsigned long current_time);
  
  bool is_ready_no_reset(unsigned long current_time);
  
  void set_earliest_ready_time(unsigned long current_time);
};

// ---------------------------------------------------------------------------------------
class TIMED_PING
// Class to manage conditions of when something needs to be ran.
//  Simplified version of is_ready_timer.
{
  private:
  unsigned long READY_TIME      = 0;  //  Calculated time of when variable will be ready.
  bool          ENABLED         = false;  // Determine if the timer is active.
  bool          BLIP_POS        = false;
  
  public:

  bool enabled();
  // Retruns enabled;

  void ping_up(unsigned long current_time, int delay);
  // Like, sending a ping signal out.
  // Start the timer for the event that needs to be triggered.
  // If already running, resets the trigger time.

  bool ping_down(unsigned long current_time);
  // Like, did the sent signal get back yet.
  // Check for the event triggered time.
  // Returns true if interval time has not passed, and ping is enabled.
  //  Disables after returning false.
  // Returns false if not enabled or time is passed.

  bool blip_visible(unsigned long current_time);
  // Check for the event triggered time.
  // Returns true if interval time has not passed, and ping is enabled.
  // Returns false if not enabled or time is passed.
  
  bool blip_moved(unsigned long current_time);
  // Check to see if return ping has changed from false to true or true to false.
  // Returns true if changed.
  // Returns false if not changed or not enabled.
};

// -------------------------------------------------------------------------------------
// Functions

#endif