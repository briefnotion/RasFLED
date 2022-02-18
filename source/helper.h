// ***************************************************************************************
// *
// *    Core       | Everything within this document is proprietary to Core Dynamics.
// *    Dynamics   | Any unauthorized duplication will be subject to prosecution.
// *
// *    Department : (R+D)^2                        Name: definitions.h
// *       Sub Dept: Programming
// *    Location ID: 856-45B
// *                                                      (c) 2856 - 2858 Core Dynamics
// ***************************************************************************************

#ifndef HELPER_H
#define HELPER_H

#include <deque>

using namespace std;

// ***************************************************************************************
// STRUCTURES AND CLASSES
// ***************************************************************************************

// -------------------------------------------------------------------------------------
// Simple 2D Ref Map

class stupid_2d
// does nothing but keep track of x with y value.
// x cant change.  just increases everytime an add of y is put into it.
// this thing is just easier to mananage than a mallaloced x,y dimed array.
{
  private:
  deque<int> X;

  public:

  void add(int y)
  {
    X.push_back(y);
  }

  int x_size()
  {
    return X.size();
  }

  int y(int x)
  {
    return X.at(x);
  }

  void clear()
  {
    X.clear();
  }
};



// -------------------------------------------------------------------------------------
// Countdown Timer

class countdown_timer
{
  private:
  bool ACTIVE = false;
  bool TRIGGERED = false;
  bool CHECKED = false;

  unsigned long TIME_START;
  unsigned long TIME_END;
  unsigned long DURATION;

  public:
  void set_timer(unsigned long Current_Time_millis, int Seconds)
  {
    TIME_START = Current_Time_millis;
    DURATION = Seconds * 1000;
    TIME_END = Current_Time_millis + DURATION;

    TRIGGERED = false;
    CHECKED = false;

    ACTIVE = true;
  }

  bool is_active()
  {
    return ACTIVE;
  }

  void trigger_check(unsigned long Current_Time_millis)
  {
    if (elapsed_time(Current_Time_millis) >= DURATION)
    {
      if (TRIGGERED == false)
      {
        TRIGGERED = true;
      }
    }
  }

  bool is_triggered()
  {
    return TRIGGERED;
  }

  void check()
  {
    CHECKED = true;
  }

  bool is_checked()
  {
    return CHECKED;
  }

  void end()
  {
    ACTIVE = false;
    TRIGGERED = false;
    CHECKED = false;
    TIME_START = 0;
    TIME_END = 0;
    DURATION = 0;
  }

  unsigned long duration()
  {
    return DURATION;
  }

  long elapsed_time(unsigned long Current_Time_millis)
  {
    return Current_Time_millis - TIME_START;
  }

  float timer_position(unsigned long Current_Time_millis)
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
};

// -------------------------------------------------------------------------------------

// -------------------------------------------------------------------------------------
// Stupid Random Generator Structure
class stupid_random
//  This is a simple solution to random numbers not being randomly generated.
//    Generate a string of random numbers to be used and referenced throughout the
//    entirity of the program run.
{
  private:
  char  stupidnumbers[StuRNDsize];

  public:
  void set()
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
  char getB(unsigned long seed, int size)
  {
    int pos = (seed % StuRNDsize);

    return (stupidnumbers[pos] % size);  
    
   }

  // Return random unsigned long from list based on seed.
  //  Number will evenly distributed from other numbers 
  //    based on list size.  Precision is way off, but should
  //    be random
  // Size is the Upper Limit. Lower Limit is 0.
  unsigned long getUL(unsigned long seed, int size)
  {
    int pos = (seed % StuRNDsize);

    return (stupidnumbers[pos] % size) * (size / StuRNDsize);
  }
};


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



// ---------------------------------------------------------------------------------------
// Hardware Monitor Class

class switch_map
// A simple switch to pin reference map
{
  // Referenced only by position in list.
  public:

  int     pin = 0;          // Hardware PIN Number
  string  SWITCH_NAME = ""; // Switch Name
  bool    value = false;    // 
};

class hardware_monitor
// Create a hardware switch or button varable type.
{
  public:
  // External
  bool booVALUE = false;
  unsigned long tmeTOGGLEDTIME = 0;
  bool ISHARDWARE = false;

  private:
  // Internal
  unsigned long tmeCHANGEDETECTEDTIME = 0;
  bool booPREVCHANGEDETECTED = false;
  unsigned int tmeLEEWAY = 0;
  bool booFIRSTRUN = true;

  public:
  void set(bool booValue, unsigned long tmeCheckTime, int tmeLeeWay, bool isHardware)
  // Prepare the switch.
  {
    tmeCHANGEDETECTEDTIME = tmeCheckTime;
    tmeLEEWAY = tmeLeeWay;
    booVALUE = booValue;
    booPREVCHANGEDETECTED = false;
    ISHARDWARE = isHardware;
  }

  bool changed(bool booValue, unsigned long tmeCheckTime)
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
};


// -------------------------------------------------------------------------------------
// Screen Status Variables
class ScreenStatus
{
  public:
  bool Refresh = false;
  bool Debug = false;
  bool Debug_Refresh = false;

  void clear()
  {
    Refresh       = false;
    Debug_Refresh = false;
  }
};


#endif