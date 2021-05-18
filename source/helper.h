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


// ***************************************************************************************
// STRUCTURES AND CLASSES
// ***************************************************************************************

// -------------------------------------------------------------------------------------
// Color class RGB byte, byte, byte

class CRGB
// RGB varible.
{
public: 
  char r = 0;
  char g = 0;
  char b = 0;

  CRGB()
  {
	  char r = 0;
	  char g = 0;
	  char b = 0;
  }
  
  // cRGB override for passing non varible to varible. 
  CRGB(char R,char G,char B)
  {
	  r = R;
	  g = G;
	  b = B;
  }
  
  //Compare two cRGB values.
  bool operator== (CRGB color)
  {
    if ((r == color.r) && (g == color.g) && (b == color.b))
      return true;
    else
      return false;
  }
};

class bigCRGB
// Color class RGB int, int, int

// This color class is used for preprocessing byte RGB values so computation can be 
// negative or more than 256.  Not displayable but useful in calculations.
{
  public:
  int r = 0;
  int g = 0;
  int b = 0;
  bool complete = true;
};


// -------------------------------------------------------------------------------------
// Countdown Timer

class countdown_timer
{
  private:
  bool ACTIVE = false;
  bool TRIGGERED = false;
  bool JUST_TRIGGERED = false;

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
    JUST_TRIGGERED = false;

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
        JUST_TRIGGERED = true;
      }
    }
  }

  bool is_triggered()
  {
    return TRIGGERED;
  }

  bool just_triggered()
  {
    if (JUST_TRIGGERED == true)
    {
      JUST_TRIGGERED = false;
      return true;
    }
    else
    {
      return false;
    }
  }

  void end()
  {
    ACTIVE = false;
    TRIGGERED = false;
    JUST_TRIGGERED = false;
    TIME_START = 0;
    TIME_END = 0;
    DURATION = 0;
  }

  unsigned long dur()
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


// -------------------------------------------------------------------------------------
// Common routines to find pixel color values from 2 seperate pixel colors.

// Compute from Power of pixel with from time start to time end.
float ComputePower(float fltElapsed, float FltDuration)
{
return (fltElapsed / FltDuration);
}

// Compute from Power of pixel with from time start to time end.
//  For pixels that are split to behave differently on first half of time.
//  Compute First half or Bottom half value.
float ComputePowerHalfBot(float fltElapsed, float FltDuration)
{
return (fltElapsed * 2 / FltDuration);
}

// Compute from Power of pixel with from time start to time end.
//  For pixels that are split to behave differently on first half of time.
//  Compute Second half or Top half value.
float ComputePowerHalfTop(float fltElapsed, float FltDuration)
{
//1 - (((float)((tmeElapsed * 2) - EventInfo.intDURATION) / (float)EventInfo.intDURATION));
return (1 - (((fltElapsed *2 ) - FltDuration) / FltDuration));
}

// Merge two pixel colors based on Power.  Returns the bigCRGB value from CRGB.
bigCRGB Dither(float fltPower, CRGB crgbColor1, CRGB crgbColor2)
{
bigCRGB tmpColor;

tmpColor.r = (fltPower * crgbColor2.r) + ((1 - fltPower) * crgbColor1.r);
tmpColor.g = (fltPower * crgbColor2.g) + ((1 - fltPower) * crgbColor1.g);
tmpColor.b = (fltPower * crgbColor2.b) + ((1 - fltPower) * crgbColor1.b);

return tmpColor;
}            

// Merge two pixel colors based on Power.  Returns the bigCRGB value from CRGB.
CRGB DitherSmall(float fltPower, CRGB crgbColor1, CRGB crgbColor2)
{
CRGB tmpColor;

tmpColor.r = (fltPower * crgbColor2.r) + ((1 - fltPower) * crgbColor1.r);
tmpColor.g = (fltPower * crgbColor2.g) + ((1 - fltPower) * crgbColor1.g);
tmpColor.b = (fltPower * crgbColor2.b) + ((1 - fltPower) * crgbColor1.b);

return tmpColor;
}      


// ---------------------------------------------------------------------------------------
// Hardware Monitor Class

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



#endif