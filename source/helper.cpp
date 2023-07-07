// ****************************************HELPER_CPP***********************************************
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

void countdown_timer::update(unsigned long Current_Time_millis)
{
  if (ACTIVE == true)
  {
    if (elapsed_time(Current_Time_millis) >= DURATION)
    {
      if (TRIGGERED == false)
      {
        TRIGGERED = true;
      }
    }
  }
}

bool countdown_timer::is_triggered()
{
  if (ACTIVE == true)
  {
    if (TRIGGERED == true && TRIGGER_REPORTED == false)
    {
      TRIGGER_REPORTED = true;
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

void countdown_timer::end()
{
  ACTIVE = false;
  TRIGGERED = false;
  TRIGGER_REPORTED = false;
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
  if (ACTIVE == true)
  {
    return Current_Time_millis - TIME_START;
  }
  else
  {
    return 0;
  }
}

float countdown_timer::timer_position(unsigned long Current_Time_millis)
{
  if (ACTIVE == true)
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
  else
  {
    return 0;
  }
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

  void FALSE_CATCH::catch_false(bool Value)
// Sets HAS_TRUTH = true if Value is true.
{
  if (Value == false)
  {
    HAS_FALSE = true;
  }
}

bool FALSE_CATCH::has_false()
// Returns true a true value was caught in the catch truth routine.
//  Resets HAS_TRUTH = false after called.
// Returns if all catch_truths were false.
{
  if (HAS_FALSE == true)
  {
    HAS_FALSE = false;
    return true;
  }
  else
  {
    return false;
  }
}

void BOOL_WITH_OVERRIDE::set(bool Override_Condition, bool Override_Value, bool Redundant_Value)
{
  if (Override_Condition == true)
  {
    VALUE = Override_Value;
    OVERRIDDEN = true;
  }
  else
  {
    VALUE = Redundant_Value;
    OVERRIDDEN = false;
  }
}

bool BOOL_WITH_OVERRIDE::value()
{
  return VALUE;
}

bool BOOL_WITH_OVERRIDE::overridden()
{
  return OVERRIDDEN;
}

void BOOL_BOUNCE::set(bool Value)
{
  VALUE = Value;
  CHANGED = true;
}

bool BOOL_BOUNCE::value()
{
  return VALUE;
}

bool BOOL_BOUNCE::bounce()
{
  if (CHANGED == true)
  {
    CHANGED = false;
    return true;
  }
  else
  {
    return false;
  }
}

// ---------------------------------------------------------------------------------------
// Min Max Time Classes

void MIN_MAX_TIME_SLICE::store_value(float Value)
{
  VALUE = VALUE + Value;
  SAMPLES++;

  if (ACTIVE == false)
  {
    MIN_VALUE = Value;
    MAX_VALUE = Value;
    ACTIVE = true;
  }
  else
  {
    if (Value < MIN_VALUE)
    {
      MIN_VALUE = Value;
    }
    if (Value > MAX_VALUE)
    {
      MAX_VALUE = Value;
    }
  }
}

float MIN_MAX_TIME_SLICE::total()
{
  return VALUE;
}

int MIN_MAX_TIME_SLICE::samples()
{
  return SAMPLES;
}

float MIN_MAX_TIME_SLICE::mean()
{
  if (SAMPLES > 0)
  {
    return VALUE / SAMPLES;
  }
  else
  {
    return 0;
  }
}

float MIN_MAX_TIME_SLICE::min()
{
  return MIN_VALUE;
}

float MIN_MAX_TIME_SLICE::max()
{
  return MAX_VALUE;
}

// ---------------------------------------------------------------------------------------

void MIN_MAX_TIME::create()
{
  if (PROP.SLICES > 0 && (PROP.TIME_SPAN > 0  || PROP.SAMPLE_LIMITED_SPANS == true))
  {
    SLICE_TIME = PROP.TIME_SPAN / PROP.SLICES;
    ENABLED = true;
  }
}

int MIN_MAX_TIME::slice_size()
{
  return TIME_SLICES.size();
}

int MIN_MAX_TIME::slice_size_max()
{
  return PROP.SLICES;
}

void MIN_MAX_TIME::put_value(float Value, unsigned long tmeFrame_Time)
{
  // If no slices, create new slice.
  if (TIME_SLICES.size() == 0)
  {
    MIN_MAX_TIME_SLICE new_time_slice;
    TIME_SLICES.push_back(new_time_slice);
    ENABLED = true;
    
    TIME_SLICE_CREATED_FRAME_TIME = tmeFrame_Time;  
  }

  if (PROP.SAMPLE_LIMITED_SPANS == false)
  {
    // Slices are time based, new slice created at when time elapsed.
    if (tmeFrame_Time > TIME_SLICE_CREATED_FRAME_TIME + SLICE_TIME)
    {
      if (TIME_SLICES.size() >= PROP.SLICES)
      {
        // New slice needed and max num reached. pop top and create new in back.
        TIME_SLICES.pop_front();
        MIN_MAX_TIME_SLICE new_time_slice;
        create();
        TIME_SLICES.push_back(new_time_slice);
      }
      else if (TIME_SLICES.size() < PROP.SLICES)
      {
        // New slice needed and max num not reached. create new in back.
        MIN_MAX_TIME_SLICE new_time_slice;
        create();
        TIME_SLICES.push_back(new_time_slice);
      }

      TIME_SLICE_CREATED_FRAME_TIME = tmeFrame_Time;  
    }
  }
  else
  {
    // Slices disregard time and instead based on sample size.
    if (TIME_SLICES.back().samples() > PROP.SAMPLE_LIMIT)
    {
      if (TIME_SLICES.size() < PROP.SLICES)
      {
        MIN_MAX_TIME_SLICE new_time_slice;
        TIME_SLICES.push_back(new_time_slice);
      }
      else
      {
        TIME_SLICES.pop_front();
        MIN_MAX_TIME_SLICE new_time_slice;
        TIME_SLICES.push_back(new_time_slice);
      }
      
      TIME_SLICE_CREATED_FRAME_TIME = tmeFrame_Time;  
    }
  }

  if (PROP.SLICES > 0)
  {
    TIME_SLICES.back().store_value(Value);
  }
}

float MIN_MAX_TIME::min_float()
{
  float min = 0;

  if (ENABLED == true)
  {
    if (TIME_SLICES.size()> 0)
    {
      min = TIME_SLICES[0].min();

      for (int x = 1; x < TIME_SLICES.size(); x++)
      {
        if (min > TIME_SLICES[x].min())
        {
          min = TIME_SLICES[x].min();
        }
      }
    }
  }
  else
  {
    min = -1;
  }

  return min;
}

int MIN_MAX_TIME::min()
{
  return (int)min_float();
}

float MIN_MAX_TIME::max_float()
{
  float max = 0;

  if (ENABLED == true)
  {
    if (TIME_SLICES.size()> 0)
    {
      max = TIME_SLICES[0].max();

      for (int x = 1; x < TIME_SLICES.size(); x++)
      {
        if (max < TIME_SLICES[x].max())
        {
          max = TIME_SLICES[x].max();
        }
      }
    }
  }
  else
  {
    max = -1;
  }

  return max;
}

int MIN_MAX_TIME::max()
{
  return (int)max_float();
}

float MIN_MAX_TIME::mean_float()
{
  float mean = 0;

  float total_total = 0;
  int total_samples = 0;

  if (ENABLED == true)
  {
    if (TIME_SLICES.size()> 0)
    {
      for (int x = 0; x < TIME_SLICES.size(); x++)
      {
        total_total = total_total + TIME_SLICES[x].total();
        total_samples = total_samples + TIME_SLICES[x].samples();
      }

      mean = total_total / total_samples;

    }
  }
  else
  {
    mean = -1;
  }

  return mean;
}

int MIN_MAX_TIME::direction()
{
  int ret_direction = 0;

  float value_difference = 0;

  if (ENABLED == true)
  {
    if (TIME_SLICES.size()> 0)
    {
      for (int x = 1; x < TIME_SLICES.size(); x++)
      {
        value_difference = value_difference + (TIME_SLICES[x].mean() - TIME_SLICES[x-1].mean());
      }

      if (value_difference > (PROP.DIRECTION_NUTRAL_RANGE * (TIME_SLICES.size() -1)))
      {
        ret_direction = 1;
      }
      else if (value_difference < (-1) * (PROP.DIRECTION_NUTRAL_RANGE * (TIME_SLICES.size() -1)))
      {
        ret_direction = -1;
      }
    }
  }
  else
  {
    ret_direction = -1;
  }

  return ret_direction;
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

float velocity_translate_kmph_to_mph(float kmph)
{
  return kmph * 0.6213711922;
}

float velocity_translate_Miph_to_mps(float Miph)
{
  return Miph * 0.447;
}

float velocity_translate_kmph_to_meters_per_second(float kmph)
{
  return kmph * 0.2777777778;
}

float velocity_translate_meters_per_second_to_kmph(float mps)
{
  return mps * 3.6;
}

float pressure_translate_kPa_to_inHg(float kPa)
{
  return kPa * (1 / 3.386389);
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

bool is_within(int Value, int Number_1, int Number_2)
{
  if (Number_1 <= Number_2)
  {
    if (Number_1 <= Value && Value <= Number_2)
    {
      return true;
    }
    else
    {
      return false;
    }
  }
  else
  {
    if (Number_2 <= Value && Value <= Number_1)
    {
      return true;
    }
    else
    {
      return false;
    }
  }
}

bool set_bool_with_change_notify(bool Set_Value, bool &Bool_Variable)
{
  if (Bool_Variable == Set_Value)
  {
    return false;
  }
  else
  {
    Bool_Variable = Set_Value;
    return true;
  }
}

int get_1_pos_of_int(int Number)
{
  return Number % 10;
}

int get_2_pos_of_int(int Number)
{
  return (Number % 100 - Number % 10) / 10;
}

float mod_decimal_remainder(float Value, int Mod_Value)
{
  int upper = (int)Value / Mod_Value;
  int lower = (int)Value % Mod_Value;
  return (Value - ((float)upper * 33 + (float)lower));
}

bool get_bit_value(int baseline, int bit_set_compare)
{
  bool ret_bit_on = false;

  ret_bit_on = (baseline & bit_set_compare) == bit_set_compare;

  return ret_bit_on;
}

int two_byte_complement_signed(unsigned char byte1, unsigned char byte2) 
{
  // thank you chat gpt.
  
  // Combine the two bytes into a 16-bit value
  int value = (static_cast<int>(byte1) << 8) | byte2;

  // Check if the value is negative
  if (value & 0x8000)
  {
    // Perform two's complement conversion
    value = -((value ^ 0xFFFF) + 1);
  }

  return value;
}

string file_format_system_time()
{
  FLED_TIME_VAR time; 
  string ret_date_time = "";

  std::chrono::time_point<std::chrono::system_clock> tmeNow = std::chrono::system_clock::now();
  std::chrono::duration<double>  dur = tmeNow.time_since_epoch();

  time.put_seconds((unsigned long)dur.count());

  ret_date_time = linemerge_right_justify(4, "0000", to_string(time.get_year())) + 
                  linemerge_right_justify(2, "00", to_string(time.get_month())) + 
                  linemerge_right_justify(2, "00", to_string(time.get_day())) + 
                  "_" + 
                  linemerge_right_justify(2, "00", to_string(time.get_hour())) + 
                  "." + 
                  linemerge_right_justify(2, "00", to_string(time.get_minute())) + 
                  "." + 
                  linemerge_right_justify(2, "00", to_string(time.get_second()));

  return ret_date_time;
}

string file_format_system_date()
{
  FLED_TIME_VAR time; 
  string ret_date_time = "";

  std::chrono::time_point<std::chrono::system_clock> tmeNow = std::chrono::system_clock::now();
  std::chrono::duration<double>  dur = tmeNow.time_since_epoch();

  time.put_seconds((unsigned long)dur.count());

  ret_date_time = linemerge_right_justify(4, "0000", to_string(time.get_year())) + 
                  linemerge_right_justify(2, "00", to_string(time.get_month())) + 
                  linemerge_right_justify(2, "00", to_string(time.get_day()));

  return ret_date_time;
}

string file_format_system_hour_minutes_seconds()
{
  FLED_TIME_VAR time; 
  string ret_date_time = "";

  std::chrono::time_point<std::chrono::system_clock> tmeNow = std::chrono::system_clock::now();
  std::chrono::duration<double>  dur = tmeNow.time_since_epoch();

  time.put_seconds((unsigned long)dur.count());

  ret_date_time = linemerge_right_justify(2, "00", to_string(time.get_hour())) + 
                  "." + 
                  linemerge_right_justify(2, "00", to_string(time.get_minute())) + 
                  "." + 
                  linemerge_right_justify(2, "00", to_string(time.get_second()));

  return ret_date_time;
}



#endif