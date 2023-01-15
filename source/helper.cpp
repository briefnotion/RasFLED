// ***************************************************************************************
// *
// *    Core       | Everything within this document is proprietary to Core Dynamics.
// *    Dynamics   | Any unauthorized duplication will be subject to prosecution.
// *
// *    Department : (R+D)^2                        Name: helper.cpp
// *       Sub Dept: Programming
// *    Location ID: 856-45B
// *                                                      (c) 2856 - 2858 Core Dynamics
// ***************************************************************************************

#ifndef HELPER_CPP
#define HELPER_CPP

#include "helper.h"

using namespace std;

// ***************************************************************************************
// STRUCTURES AND CLASSES
// ***************************************************************************************

// -------------------------------------------------------------------------------------
// Simple 2D Ref Map
void stupid_2d::add(int y)
{
  X.push_back(y);
}

int stupid_2d::x_size()
{
  return X.size();
}

int stupid_2d::y(int x)
{
  return X.at(x);
}

void stupid_2d::clear()
{
  X.clear();
}

// -------------------------------------------------------------------------------------
// Countdown Timer

  void countdown_timer::set_timer(unsigned long Current_Time_millis, int Seconds)
  {
    TIME_START = Current_Time_millis;
    DURATION = Seconds * 1000;
    TIME_END = Current_Time_millis + DURATION;

    TRIGGERED = false;
    CHECKED = false;

    ACTIVE = true;
  }

  bool countdown_timer::is_active()
  {
    return ACTIVE;
  }

  void countdown_timer::trigger_check(unsigned long Current_Time_millis)
  {
    if (elapsed_time(Current_Time_millis) >= DURATION)
    {
      if (TRIGGERED == false)
      {
        TRIGGERED = true;
      }
    }
  }

  bool countdown_timer::is_triggered()
  {
    return TRIGGERED;
  }

  void countdown_timer::check()
  {
    CHECKED = true;
  }

  bool countdown_timer::is_checked()
  {
    return CHECKED;
  }

  void countdown_timer::end()
  {
    ACTIVE = false;
    TRIGGERED = false;
    CHECKED = false;
    TIME_START = 0;
    TIME_END = 0;
    DURATION = 0;
  }

  unsigned long countdown_timer::duration()
  {
    return DURATION;
  }

  long countdown_timer::elapsed_time(unsigned long Current_Time_millis)
  {
    return Current_Time_millis - TIME_START;
  }

  float countdown_timer::timer_position(unsigned long Current_Time_millis)
  {
    
    if (DURATION <= 0)
      return 0;

    unsigned long elapsed = Current_Time_millis - TIME_START;
    float pos = (float)elapsed / (float)DURATION;

    if (pos > 1)
      return 1;
    else
      return pos;
  }

// -------------------------------------------------------------------------------------

// -------------------------------------------------------------------------------------
// Stupid Random Generator Structure
  void stupid_random::set()
  {
    long number;
    int pos = 0;
    bool found = false;

    // Create seed onece.
    srand((unsigned int)time(NULL));

    // Clear Array.
    for (int x = 0; x < StuRNDsize; x++)
    {
      stupidnumbers[x] = 255;
    }
    
    // Fill the array with random numbers.
    while(pos < StuRNDsize)
    {
      // Get a number.
      number = rand() % StuRNDsize;
      number = floor(number);

      found = false;

      // If number already in list then seach for a new
      //  random number.
      for (int x = 0; x <= pos; x++)
      {
        if (number == (int)(stupidnumbers[x]))
        {
          found = true;
        }
      }

      // If number not in list then add it.
      if (found == false)
      {
        stupidnumbers[pos] =(char )(number);
        pos ++;
      }
    }
  }

  // Return random char from list based on seed.
  char stupid_random::getB(unsigned long seed, int size)
  {
    int pos = (seed % StuRNDsize);

    return (stupidnumbers[pos] % size);  
    
   }

  // Return random unsigned long from list based on seed.
  //  Number will evenly distributed from other numbers 
  //    based on list size.  Precision is way off, but should
  //    be random
  // Size is the Upper Limit. Lower Limit is 0.
  unsigned long stupid_random::getUL(unsigned long seed, int size)
  {
    int pos = (seed % StuRNDsize);

    return (stupidnumbers[pos] % size) * (size / StuRNDsize);
  }


  bool VAR_CHANGE_MON::switched(int Value)
  {
    if (Value == PREV_VALUE)
    {
      return false;
    }
    else
    {
      PREV_VALUE = Value;
      return true;
    }
  }

// ---------------------------------------------------------------------------------------
// Hardware Monitor Class

  void hardware_monitor::set(bool booValue, unsigned long tmeCheckTime, int tmeLeeWay, bool isHardware)
  // Prepare the switch.
  {
    tmeCHANGEDETECTEDTIME = tmeCheckTime;
    tmeLEEWAY = tmeLeeWay;
    booVALUE = booValue;
    booPREVCHANGEDETECTED = false;
    ISHARDWARE = isHardware;
  }

  bool hardware_monitor::changed(bool booValue, unsigned long tmeCheckTime)
  // Return true if the switch state change from on to off or off to on.
  {
    unsigned long tmeTme = tmeCheckTime;

    // If the switch was just activated then run any set up its initial state and run
    //  any special routines.
    if (booFIRSTRUN == true)
    {
      booVALUE = booValue;
      booPREVCHANGEDETECTED = false;
      tmeCHANGEDETECTEDTIME = tmeTme;
      booFIRSTRUN = false;

      if (BOOTEST == false)
      {
        return booValue;  // Comment this line out when testing
        //return false;   // Comment this line out when not testing
      }
      else
      {
        //return booValue;// Comment this line out when testing
        return false;     // Comment this line out when not testing
      }
    }
    else if (booVALUE == booValue)
    {
      booPREVCHANGEDETECTED = false;
      return false;
    }
    else if (booPREVCHANGEDETECTED == false)
    {
      tmeCHANGEDETECTEDTIME = tmeTme;
      booPREVCHANGEDETECTED = true;
      return  false;
    }
    // Only report change of status when Leeway time is passed.  This is a essentially a
    //  debouncer.
    else if (tmeTme < (tmeCHANGEDETECTEDTIME + tmeLEEWAY))
    {
      return false;
    }
    else
    {
      booVALUE = booValue;
      booPREVCHANGEDETECTED = false;
      tmeCHANGEDETECTEDTIME = tmeTme;
      tmeTOGGLEDTIME = tmeTme;
      return true;
    }
  }

  void hardware_monitor::read(bool booValue, unsigned long tmeCheckTime)
  {
    changed(booValue, tmeCheckTime);
  }
// ---------------------------------------------------------------------------------------


  void STAT_DATA_DOUBLE::set_data(double data)
  // Provide minor min max stats over time of resets.
  // I real stats ever necessary, then weighted average 
  //  routine needed.
  {
    DATA = data;
    
    if (set == false)
    {
      set = true;
      MIN = DATA;
      MAX = DATA;
    }
    else if (data < MIN)
    {
      MIN = data;
    }
    else if (data > MAX)
    {
      MAX = data;
    }
  }

  double STAT_DATA_DOUBLE::get_data()
  {
    return DATA;
  }

    double STAT_DATA_DOUBLE::get_min()
  {
    return MIN;
  }

    double STAT_DATA_DOUBLE::get_max()
  {
    return MAX;
  }
  
  void STAT_DATA_DOUBLE::reset_minmax()
  {
    set = false;
    MIN = DATA;
    MAX = DATA;
  }
// ---------------------------------------------------------------------------------------


  void EFFICIANTCY_TIMER::start_timer(double dblCurrent_Time)
  // Start the timer (stopwatch) by setting its the stopwatch time.
  //  The timer is a simple and can be considered always active. 
  {
    TIMER_STARTED = dblCurrent_Time;
  }

  double EFFICIANTCY_TIMER::elapsed_timer_time(double dblCurrent_Time)
  //  Returns the amount of time passed since the reset. 
  {
    return dblCurrent_Time - TIMER_STARTED;
  }

  double EFFICIANTCY_TIMER::elapsed_time(double dblCurrent_Time)
  // Measures the amount of time elaspeds since the privious time the function was 
  //  called, then returns the value, then resets for next time. 
  {
    double time_elapsed = dblCurrent_Time - LAST_ASKED_TIME;
    LAST_ASKED_TIME = dblCurrent_Time;
    return time_elapsed;
  }
// ---------------------------------------------------------------------------------------

  // Simple Variable to track if a TRUE value has entered.

  void TRUTH_CATCH::catch_truth(bool Value)
  // Sets HAS_TRUTH = true if Value is true.
  {
    if (Value == true)
    {
      HAS_TRUTH = true;
    }
  }

  bool TRUTH_CATCH::has_truth()
  // Returns true a true value was caught in the catch truth routine.
  //  Resets HAS_TRUTH = false after called.
  // Returns if all catch_truths were false.
  {
    if (HAS_TRUTH == true)
    {
      HAS_TRUTH = false;
      return true;
    }
    else
    {
      return false;
    }
  }

// ***************************************************************************************
// FUNCTION AND PROCEDURES
// ***************************************************************************************

// ---------------------------------------------------------------------------------------
// Random Number

int intRandomHD(int intBase)
// Generate a random number between half and double of the base
{
  int intLowerOffset = intBase / 2;
  int intUpperOffset = (intBase * 2) - intLowerOffset;
  return ((rand() % intUpperOffset) + intLowerOffset);
}

// Some time display type things
int millis_to_time_minutes(long millis_time)
// Returns minutes portion of time.
{
  return abs(millis_time/60000);
}

int millis_to_time_seconds(long millis_time)
// Returns seconds portion of time.
{
  return abs((millis_time % 60000)/1000);
}

int get_frame_interval(int Frames_Per_Second)
{
  return (1000 / Frames_Per_Second);
}

int radio_translate_to_frequency_6(float Frequency)
{
  return (int)round(Frequency / 1000.0);
}

int position_of_scale(int size, int scale, int value)
// Calculate position of value on scale (eg 100%) with size.
//  Will not return anything larger than size.
{
  int pos = size * value / scale;

  if (pos > size)
  {
    return size;
  }
  else
  {
    return pos;
  }
}




#endif