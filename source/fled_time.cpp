// ***************************************************************************************
// *
// *    Core       | Everything within this document is proprietary to Core Dynamics.
// *    Dynamics   | Any unauthorized duplication will be subject to prosecution.
// *
// *    Department : (R+D)^2                        Name: fled_time.cpp
// *       Sub Dept: Programming
// *    Location ID: 856-45B
// *                                                      (c) 2856 - 2858 Core Dynamics
// ***************************************************************************************
// *
// *  PROJECTID: gi6$b*E>*q%;    Revision: 00000000.01A
// *  TEST CODE:                 QACODE: A565              CENSORCODE: EQK6}Lc`:Eg>
// *
// ***************************************************************************************

#ifndef FLED_TIME_CPP
#define FLED_TIME_CPP

#include "fled_time.h"

using namespace std;

// -------------------------------------------------------------------------------------
// Time Variable

void FLED_TIME_VAR::update_time()
{
  THE_TIME = (time_t)SECONDS;
  PTM = localtime(&THE_TIME);
  TIME_UPDATED = true;
}

void FLED_TIME_VAR::put_seconds(unsigned long Seconds)
{
  SECONDS = Seconds;
  TIME_UPDATED = false;
}

void FLED_TIME_VAR::put_deciseconds(int Deciseconds)
{
  MICRO_SECONDS = Deciseconds *100000;
  TIME_UPDATED = false;
}

void FLED_TIME_VAR::put_miliseconds(int Miliseconds)
{
  MICRO_SECONDS = Miliseconds *1000;
  TIME_UPDATED = false;
}

unsigned long FLED_TIME_VAR::get_seconds()
{
  return SECONDS;
}

int FLED_TIME_VAR::get_deciseconds()
{
  return MICRO_SECONDS / 100000;
}

int FLED_TIME_VAR::get_miliseconds()
{
  return MICRO_SECONDS / 1000;
}

int FLED_TIME_VAR::get_year()
{
  int return_int = 0;

  if (TIME_UPDATED == false)
  {
    update_time();
  }

  return (1900 + PTM->tm_year);
}

int FLED_TIME_VAR::get_month()
{
  int return_int = 0;

  if (TIME_UPDATED == false)
  {
    update_time();
  }

  return (PTM->tm_mon +1);
}

int FLED_TIME_VAR::get_day()
{
  if (TIME_UPDATED == false)
  {
    update_time();
  }

  return (PTM->tm_mday);
}

int FLED_TIME_VAR::get_hour()
{
  if (TIME_UPDATED == false)
  {
    update_time();
  }

  return (PTM->tm_hour);
}

int FLED_TIME_VAR::get_minute()
{
  if (TIME_UPDATED == false)
  {
    update_time();
  }

  return (PTM->tm_min);
}

int FLED_TIME_VAR::get_second()
{
  if (TIME_UPDATED == false)
  {
    update_time();
  }

  return (PTM->tm_sec);
}

// -------------------------------------------------------------------------------------
// Keeps track of timing variables

void FledTime::set()
{
  // Initialize as Start of Program Time.
  tmeStart = std::chrono::system_clock::now();
  first_run = false;
}

double FledTime::now()
{
  if (first_run == true)
  {
    set();
  }

  // Returns now time in milliseconds.
  // Should be Unsigned Long.
  std::chrono::time_point<std::chrono::system_clock> tmeNow = std::chrono::system_clock::now();
  std::chrono::duration<double>  dur = tmeNow - tmeStart;

  double nowtime = dur.count();
  nowtime = nowtime * 1000;
  
  return nowtime;
}

void FledTime::setframetime()
{
  if (first_run == true)
  {
    set();
  }

  // Sets the Start of a Frame Time to now. 
  tmeFrame = std::chrono::system_clock::now();
  std::chrono::duration<double>  dur = tmeFrame - tmeStart;

  tmeFrameMillis = dur.count();
  tmeFrameMillis = tmeFrameMillis * 1000;
}

double FledTime::tmeFrameElapse()
{
  // Returns, in milliseconds, the amount of time passed since frame time.
  double elapsed;
  std::chrono::time_point<std::chrono::system_clock> tmeNow = std::chrono::system_clock::now();
  std::chrono::duration<double>  dur = tmeNow - tmeFrame;
  
  elapsed = dur.count();
  elapsed = elapsed * 1000;

  return elapsed;
}
  
// ---------------------------------------------------------------------------------------

bool TIMED_IS_READY::is_set()
{
  if (TRIGGERED_TIME == 0)
  {
    return false;
  }
  else
  {
    return true;
  }
}

void TIMED_IS_READY::set(unsigned long current_time, int delay)
// Prep the TIMED_IS_READY varable
// delay is measured in ms.
{
  TRIGGERED_TIME  = current_time;
  INTREVAL        = delay;
}

void TIMED_IS_READY::set(int delay)
// Prep the TIMED_IS_READY varable
//  If current time isn't available
// delay is measured in ms.
{
  TRIGGERED_TIME  = 0;
  INTREVAL        = delay;
}

unsigned long TIMED_IS_READY::get_ready_time()
// Return the time value of when the variable will be ready. 
{
  return READY_TIME;
}

bool TIMED_IS_READY::is_ready(unsigned long current_time)
{
  // Check to see if enough time has passed.
  //  Returns true if interval time has passed.
  //    Resets timer if returned true.
  //  Returns false if time has not elapsed.
  //    Stores last asked time.
  if(current_time >= READY_TIME)
  {
    TRIGGERED_TIME = current_time;
    READY_TIME = current_time + INTREVAL;
    return true;
  }
  else
  {
    LAST_ASKED_TIME = current_time;
    return false;
  }
}

bool TIMED_IS_READY::is_ready_no_reset(unsigned long current_time)
{
  // Check to see if enough time has passed.
  //  Returns true if interval time has passed.
  //    Does not resets timer if returned true.
  //  Returns false if time has not elapsed.
  //    Stores last asked time.
  if(current_time >= READY_TIME)
  {
    LAST_ASKED_TIME = current_time;
    return true;
  }
  else
  {
    LAST_ASKED_TIME = current_time;
    return false;
  }
}

void TIMED_IS_READY::set_earliest_ready_time(unsigned long current_time)
// Manually set the ready time of the variable. 
// Does not change time if time to set is later than the already set time.
{
  if (current_time < READY_TIME)
  {
    READY_TIME = current_time;
  }
}

// ---------------------------------------------------------------------------------------

bool TIMED_PING::enabled()
{
  return ENABLED;
}

void TIMED_PING::ping_up(unsigned long current_time, int delay)
// Start the timer for the event that needs to be triggered.
{
  READY_TIME      = current_time + delay;
  ENABLED         = true;
}

bool TIMED_PING::ping_down(unsigned long current_time)
{
  // Check for the event triggered time.
  // Returns true if interval time has not passed, and ping is enabled.
  //  Disables after returning false.
  // Returns false if not enabled or time is passed.
  if (ENABLED == true)
  {
    if (current_time < READY_TIME)
    {
      return true;
    }
    else
    {
      ENABLED = false;
      return false;
    }
  }
  else
  {
    return false;
  }
}

bool TIMED_PING::blip_visible(unsigned long current_time)
{
  // Check for the event triggered time.
  // Returns true if interval time has not passed, and ping is enabled.
  // Returns false if not enabled or time is passed.
  if (ENABLED == true)
  {
    return (current_time < READY_TIME);
  }
  else
  {
    return false;
  }
}

bool TIMED_PING::blip_moved(unsigned long current_time)
// Check to see if return ping has changed from false to true or true to false.
// Returns true if changed.
// Returns false if not changed or not enabled.
{
  if (ENABLED == true)
  {
    bool new_blip_pos = blip_visible(current_time);

    if (new_blip_pos != BLIP_POS)
    {
      BLIP_POS = new_blip_pos;
      return true;
    }
    else
    {
      return false;
    }
  }
  else 
  {
    return false;
  }
}

// -------------------------------------------------------------------------------------
// Functions


#endif