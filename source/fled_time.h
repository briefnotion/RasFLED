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

// Standard Header Files
#include <chrono>

using namespace std;

// -------------------------------------------------------------------------------------
// Keeps track of timing variables
class FledTime
{
  private:
  std::chrono::time_point<std::chrono::system_clock> tmeStart;
  std::chrono::time_point<std::chrono::system_clock> tmeFrame;

  bool first_run = true;

  void set()
  {
    // Initialize as Start of Program Time.
    tmeStart = std::chrono::system_clock::now();
    first_run = false;
  }

  public:

  double tmeFrameMillis;


  double now()
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

  void setframetime()
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

  double tmeFrameElapse()
  {
    // Returns, in milliseconds, the amount of time passed since frame time.
    double elapsed;
    std::chrono::time_point<std::chrono::system_clock> tmeNow = std::chrono::system_clock::now();
    std::chrono::duration<double>  dur = tmeNow - tmeFrame;
    
    elapsed = dur.count();
    elapsed = elapsed * 1000;

    return elapsed;
  }
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

  bool is_set()
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

  void set(unsigned long current_time, int delay)
  // Prep the TIMED_IS_READY varable
  // delay is measured in ms.
  {
    TRIGGERED_TIME  = current_time;
    INTREVAL        = delay;
  }

  void set(int delay)
  // Prep the TIMED_IS_READY varable
  //  If current time isn't available
  // delay is measured in ms.
  {
    TRIGGERED_TIME  = 0;
    INTREVAL        = delay;
  }

  unsigned long get_ready_time()
  // Return the time value of when the variable will be ready. 
  {
    return READY_TIME;
  }

  int get_interval()
  // Return the time value of how long the interval was set for.  
  {
    return INTREVAL;
  }

  bool is_ready(unsigned long current_time)
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
  
  bool is_ready_no_reset(unsigned long current_time)
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
  
  void set_earliest_ready_time(unsigned long current_time)
  // Manually set the ready time of the variable. 
  // Does not change time if time to set is later than the already set time.
  {
    if (current_time < READY_TIME)
    {
      READY_TIME = current_time;
    }
  }
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

  void ping_up(unsigned long current_time, int delay)
  // Start the timer for the event that needs to be triggered.
  {
    READY_TIME      = current_time + delay;
    ENABLED         = true;
  }

  bool ping_down(unsigned long current_time)
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

  bool blip_visible(unsigned long current_time)
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
  
  bool blip_moved(unsigned long current_time)
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
};




#endif