// ***************************************************************************************
// *
// *    Core       | Everything within this document is proprietary to Core Dynamics.
// *    Dynamics   | Any unauthorized duplication will be subject to prosecution.
// *
// *    Department : (R+D)^2                        Name: fledcore.h
// *       Sub Dept: Programming
// *    Location ID: 856-45B
// *                                                      (c) 2856 - 2858 Core Dynamics
// ***************************************************************************************

#ifndef LEDSTUFF_H
#define LEDSTUFF_H

// Standard Header Files
#include <string.h>
#include <deque>

using namespace std;

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

  string CRGBtoString()
  {
    return (to_string(r) + "," + to_string(g) + "," + to_string(b));
  }

  CRGB StringtoCRGB(string strCRGB)
  {
    // Expected input: string with 3 numbers seperated by commas.
    int c1, c2;
    int r, g, b = 0;

    c1 = strCRGB.find(",");
    if (c1!=string::npos)
    {
      c2 = strCRGB.find(",",c1+1);
      if (c2!=string::npos);
      {
        r = atoi(strCRGB.substr(0,c1).c_str()); 
        g = atoi(strCRGB.substr(c1+1,c2-c1-1).c_str());
        b = atoi(strCRGB.substr(c2+1,strCRGB.length()-1).c_str());
      }
    }
    return CRGB(r,g,b);
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
// Strip Variable Containers
//  - Set commands are unnecessay and can be atted to the "add_###" commands in the 
//      future

// LED Strip
class v_profile_strip
{
  private:

  int intLED_COUNT      = 0;

  public:

  int     intID         = 0;
  string  strNAME       = "";
  string  strPOSITION   = "";

  bool booFORWARD       = true;
  bool booBOT_AT_START  = true;

  CRGB *crgbARRAY;
  bool booARRAY_UPDATED = false;

  int intLED_START_POS  = 0;

  string Status         = "";
  int intCHANNEL = 0;

  // -------------------------------------------------------------------------------------

  void set(int intId, string strName, string strPosition, int intStart_Pos, bool forward, bool bot_at_start)
  {
    intID       = intId;
    strNAME     = strName;
    strPOSITION = strPosition;

    int intGROUP_START_POS  = intStart_Pos;
    booFORWARD              = forward;
    booBOT_AT_START         = bot_at_start;
  }

  void create(int size)
  // Allocate static array into memory.
  {
    intLED_COUNT = size;
    crgbARRAY = (CRGB*)malloc(sizeof(CRGB) * intLED_COUNT);
  }

  int led_count()
  // Returns all led count in Strip
  {
    return intLED_COUNT;
  }

  int fs(int pos)
  // From Start
  {
    return pos;
  }
  
  int fe(int pos)
  // From End
  {
    return intLED_COUNT - 1 - pos;
  }

  int fb(int pos)
  // From Bottom
  {
    if (booBOT_AT_START == true)
    {
      return pos;
    }
    else
    {
      return intLED_COUNT - 1 - pos;
    }
  }

  int ft(int pos)
  // From Bottom
  {
    if (booBOT_AT_START == true)
    {
      return intLED_COUNT - 1 - pos;
    }
    else
    {
      return pos;
    }

  }

  bool position(string position)
  {
    if (strPOSITION == position)
    {
      return true;
    }
    else
    {
      return false;
    }
  }
  
};

// LED Strip Group
class v_profile_strip_group
{
  private:

  int intLED_COUNT        = 0;

  public:

  int intID               = 0;
  string strNAME          = "";

  int intGROUP_START_POS  = 0;
  string Status         = "";

  deque<v_profile_strip>  vLED_STRIPS;

  int find(string strName)
  {
    int ret = -1;
    for(int x=0; x < vLED_STRIPS.size(); x++)
    {
      if(vLED_STRIPS.at(x).strNAME == strName)
      {
        ret = x;
      }
    }
    return ret;
  }

  string status(string strName)
  {
    return vLED_STRIPS.at(find(strName)).Status;
  }

  void status_set(string strName, string strStatus)
  {
    for (int s=0; s < vLED_STRIPS.size(); s++)
    {
      if(vLED_STRIPS.at(s).strNAME == strName)
      {
        vLED_STRIPS.at(s).Status = strStatus;
      }
    }
  }

  void set(int intId, string strName, int intStart_Pos)
  {
    intID                   = intId;
    strNAME                 = strName;
    int intGROUP_START_POS  = intStart_Pos;
  }

  int led_count()
  // Returns all led count in Group
  {
    int count = 0;
    for(int x=0; x<vLED_STRIPS.size(); x++)
    {
      count = count + vLED_STRIPS.at(x).led_count();
    }
    return count;
  }

  void add_strip(int intID, string strName, string strPosition, int size, bool forward, bool bot_at_start)
  // Creates new strip
  {
    v_profile_strip tmp_profile_strip;

    // Get Start Pos
    int startpos = 0;

    tmp_profile_strip.set(intID, strName, strPosition, startpos, forward, bot_at_start);
    tmp_profile_strip.create(size);
    vLED_STRIPS.push_back(tmp_profile_strip);
  }
};

// LED Main Container
class v_profile_strip_main
{
  private:

  stupid_2d GROUP_MAP;

  public:

  int intID         = 0;
  string strNAME    = "";

  int int_START_POS = 0;
  deque<v_profile_strip_group> vLED_GROUPS;

  int g_size()
  {
    return GROUP_MAP.x_size();
  }

  int s_size(int group)
  {
    return GROUP_MAP.y(group);
  }

  int led_count()
  // Returns all led count in Main group
  {
    int count = 0;
    for(int x=0; x<vLED_GROUPS.size(); x++)
    {
      count = count + vLED_GROUPS.at(x).led_count();
    }
    return count;
  }

  void set(int intId, string strName)
  {
    intID   = intId;
    strNAME = strName;
  }

  void add_group(int intId, string strName)
  // Creates new group profile
  {
    v_profile_strip_group tmp_led_group;

    tmp_led_group.set(intId, strName, 0);
    vLED_GROUPS.push_back(tmp_led_group);
  }

  void update_start_positions()
  // Recalculate start position of all LED strips if LED sizes change.
  {
    int pos = 0;

    GROUP_MAP.clear();

    int_START_POS = pos;

    for(int x=0; x<vLED_GROUPS.size(); x++)
    {
      GROUP_MAP.add(vLED_GROUPS.at(x).vLED_STRIPS.size());
      
      vLED_GROUPS.at(x).intGROUP_START_POS = pos;
      for(int y=0; y<vLED_GROUPS.at(x).vLED_STRIPS.size(); y++)
      {
        vLED_GROUPS.at(x).vLED_STRIPS.at(y).intLED_START_POS = pos;
        pos = pos + vLED_GROUPS.at(x).vLED_STRIPS.at(y).led_count();
      }
    }
  }

  v_profile_strip strip_info(int intGroup, int intStrip)  
  {
    return vLED_GROUPS.at(intGroup).vLED_STRIPS.at(intStrip);
  }
};



// ***************************************************************************************
// FUNCTION AND PROCEDURES
// ***************************************************************************************


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




#endif