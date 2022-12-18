// ***************************************************************************************
// *
// *    Core       | Everything within this document is proprietary to Core Dynamics.
// *    Dynamics   | Any unauthorized duplication will be subject to prosecution.
// *
// *    Department : (R+D)^2                        Name: helper.h
// *       Sub Dept: Programming
// *    Location ID: 856-45B
// *                                                      (c) 2856 - 2858 Core Dynamics
// ***************************************************************************************

#ifndef HELPER_H
#define HELPER_H

#include <deque>
#include <string>
#include <math.h>

#include "definitions.h"

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

  void add(int y);

  int x_size();

  int y(int x);

  void clear();
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
  void set_timer(unsigned long Current_Time_millis, int Seconds);

  bool is_active();

  void trigger_check(unsigned long Current_Time_millis);

  bool is_triggered();

  void check();

  bool is_checked();

  void end();

  unsigned long duration();

  long elapsed_time(unsigned long Current_Time_millis);

  float timer_position(unsigned long Current_Time_millis);
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
  void set();

  // Return random char from list based on seed.
  char getB(unsigned long seed, int size);

  // Return random unsigned long from list based on seed.
  //  Number will evenly distributed from other numbers 
  //    based on list size.  Precision is way off, but should
  //    be random
  // Size is the Upper Limit. Lower Limit is 0.
  unsigned long getUL(unsigned long seed, int size);
};

class VAR_CHANGE_MON
// Check to see if a value of an integer has changed.
// Return true and reset if it has.
// Retrun false if it is the same.
{
  private:

  int PREV_VALUE = 0;

  bool switched(int Value);
};

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
  void set(bool booValue, unsigned long tmeCheckTime, int tmeLeeWay, bool isHardware);

  bool changed(bool booValue, unsigned long tmeCheckTime);

  void read(bool booValue, unsigned long tmeCheckTime);
};
// ---------------------------------------------------------------------------------------

class STAT_DATA_DOUBLE
// Provide minor min max stats over time of resets.
// If real stats ever necessary, then weighted average 
//  routine needed.
{
  private:

  bool set = true;

  double DATA  = 0;
  double MIN   = 0;
  double MAX   = 0;

  public:
  void set_data(double data);

  double get_data();

  double get_min();

  double get_max();

  void reset_minmax();
};
// ---------------------------------------------------------------------------------------

class EFFICIANTCY_TIMER
// Measures time passed between calls. 
{
  private:
  double LAST_ASKED_TIME = 0;
  double TIMER_STARTED   = 0;

  public:

  void start_timer(double dblCurrent_Time);

  double elapsed_timer_time(double dblCurrent_Time);

  double elapsed_time(double dblCurrent_Time);
};



// ***************************************************************************************
// FUNCTION AND PROCEDURES
// ***************************************************************************************

// ---------------------------------------------------------------------------------------
// Random Number

int intRandomHD(int intBase);

// Some time display type things
int millis_to_time_minutes(long millis_time);

int millis_to_time_seconds(long millis_time);

int get_frame_interval(int Frames_Per_Second);

int radio_translate_to_frequency_6(float Frequency);

int position_of_scale(int size, int scale, int value);
// Calculate position of value on scale (eg 100%) with size.
//  Will not return anything larger than size.


#endif