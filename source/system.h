// ***************************************************************************************
// *
// *    Core       | Everything within this document is proprietary to Core Dynamics.
// *    Dynamics   | Any unauthorized duplication will be subject to prosecution.
// *
// *    Department : (R+D)^2                        Name: system.h
// *       Sub Dept: Programming
// *    Location ID: 856-45B
// *                                                      (c) 2856 - 2858 Core Dynamics
// ***************************************************************************************

#ifndef SYSTEM_H
#define SYSTEM_H

#include <stdio.h>
#include <string.h>
#include <deque>

// RASFled related header files
#include "definitions.h"
#include "helper.h"
#include "commands.h"
#include "hardware_status.h"

#include "api_shared_memory.h"
#include "api_rtlairband.h"
#include "radio_channel_coordinator.h"

using namespace std;

// ***************************************************************************************
// STRUCTURES AND CLASSES
// ***************************************************************************************
class configuration
{
  public:

  // -------------------------------------------------------------------------------------
  // Hardware to Software definitions
  // -------------------------------------------------------------------------------------
  
  // -------------------------------------------------------------------------------------
  // Raspberry Pi switch pin for doors and switches. Defined as WiringPi id.
  // console: gpio -v       (check installation)
  // console: gpio readall  (check wiring pin numbers)

  int iAUXDRLINGERFRT     = 15000;    // How long the Front Door lights stay on after close
  int iAUXDRLINGERBCK     = 25000;    // How long the Back Door lights stay on after close

  // -------------------------------------------------------------------------------------
  // LED rpi_ws281x Variables
  int iBRIGHTNESS         = 96;  //96  Using Example Code.  Max unknown
  int iFRAMES_PER_SECOND  = 50; // Will not be necessary, but keeping, for now, just in 
                                //  case.

  // -------------------------------------------------------------------------------------
  // Events
  int iNUM_CHANNELS       = 0;   // Amount of Event Channels we will be controlling.

  // -------------------------------------------------------------------------------------
  // LED Group List
  deque<v_profile_strip_main> LED_MAIN; // Main LED Profile of Groups

  // -------------------------------------------------------------------------------------
  // New Door Switch Reference
  int iNUM_SWITCHES       = 4;              // Amount of HW switches
  deque<hardware_monitor> vhwDOORS;         // List of HW Monitors
  deque<switch_map>       vSWITCH_PIN_MAP;  // Map of Hardware Circuit Pin ID to 
                                            //  software Pin ID
};
// -------------------------------------------------------------------------------------

// -------------------------------------------------------------------------------------
class system_data
{
  // This is just a repository of data that the program will be accessing and storing 
  //  for displaying only.  Everyting here is very specific and not meant to be 
  //  friendly.  This data and functions is specific for this one program.  Also, 
  //  this class is very likely to fail if not maintained when program main is updated. 
  //  You have been warned.

  private:
  
  struct stat_data
  {
    float data  = 0;
    float min   = 0; 
    float max   = 0;
  };

  struct stat_data_double
  {
    double data  = 0;
    double min   = 0; 
    double max   = 0;
  };

  class running_colors
  {
    public:
    // array for now. ll in future if necessary.
    int size = 6;
    string strRunningColor = "";  // 
    CRGB color[6];
  };

  public:

  // Primary Variables
  unsigned long tmeCURRENT_FRAME_TIME = 0;

  // Main Reset
  bool booREBOOT = false;

  // System
  configuration CONFIG;

  // System Timing
  stat_data_double dblCOMPUTETIME;   // Loop time spent while only proceessing.
  stat_data_double dblSLEEPTIME;     // Calculated time needed to sleep.
  stat_data_double dblCYCLETIME;     // Amount of time to complete an entire cycle.
  stat_data_double dblPREVSLEEPTIME; // Stored value returned on pref sleep cycle.

  // Door Module Support
  deque<bool> boolDOOR_SENSOR_STATUS;

  int   intDoorsOpen = 0;           // Amount of doors open.
  bool  booPulsesRunning = false;   // Are exta anims running.
  bool  booOverheadRunning = false; // Are exta anims running.
  bool  booHazardRunning = false;   // Are exta anims running.
  
  // Timer and Color Schemes
  countdown_timer cdTIMER;
  running_colors running_color_list;

  // Hardware Status Indicators
  HARDWARE_STATUS hsHardware_Status;

  // Day Mode Active
  bool booDay_On = false;

  // Files
  bool booRunning_State_File_Dirty = false;

  // Event System
  deque<int> intCHANNEL_GROUP_EVENTS_COUNTS;

  COMMAND_THREAD Command_Thread;

  // Radio Variables
  API_SQUELCH_DESTINATION RECEIVED_SQUELCH;
  API_CHANNEL_MEM API_CHANNEL;
  RADIO_CHANNEL_COORDINATOR RADIO_COORD;

  // Console Display Variables from other

  // Test Mode
  int t_group = 0;
  int t_strip = 0;

  // PrintBufferData - temparory fix to print things when the console cant be accessed.
  bool booprintbuffer   = false;
  string strprintbuffer = "";
  /* Usage:
      booprintbuffer = true;
      strprintbuffer = to_string(section_elaped_time) + "       ";
    Does not clean up after itself */

  // -------------------------------------------------------------------------------------


  int get_API_info(boost::interprocess::mapped_region &region_scan)
  {
    int return_int = -1;
    return_int = API_CHANNEL.rasfled_receive(region_scan, RECEIVED_SQUELCH);
    RADIO_COORD.process(RECEIVED_SQUELCH);

    return return_int;
  }

  void init()
  {
    for(int x=0; x<CONFIG.iNUM_SWITCHES; x++)
    {
      boolDOOR_SENSOR_STATUS.push_back(false);
    }

    for(int x=0; x<CONFIG.iNUM_CHANNELS; x++)
    {
      intCHANNEL_GROUP_EVENTS_COUNTS.push_back(0);
    }
  }

  void store_Current_Frame_Time(unsigned long tmeCurrent_Time_millis)
  {
    tmeCURRENT_FRAME_TIME = tmeCurrent_Time_millis;
    if (cdTIMER.is_active())
    {
      cdTIMER.trigger_check(tmeCurrent_Time_millis);
      
    // Check for Timer Window
    }
    if(cdTIMER.is_active() == true)
    {
      booprintbuffer = true;
      strprintbuffer =  to_string(cdTIMER.elapsed_time(tmeCurrent_Time_millis)) + "  " + to_string(cdTIMER.is_triggered()) + "  " +  to_string(cdTIMER.is_checked()) + "  ";
    }
  }

  // Reference to the door values
  void store_door_switch_states()
  {
    for(int x=0; x < CONFIG.iNUM_SWITCHES; x++)
    {
      boolDOOR_SENSOR_STATUS.at(x) = CONFIG.vSWITCH_PIN_MAP.at(x).value;
    }
  }

  void init_running_color_list()
  {
    running_color_list.strRunningColor = "Blank";
    running_color_list.color[0] = CRGB(0,0,0);
    running_color_list.color[1] = CRGB(0,64,0);  // Green
    running_color_list.color[2] = CRGB(48,48,0); // Yellow
    running_color_list.color[3] = CRGB(64,16,0); // Orange
    running_color_list.color[4] = CRGB(20,20,20); // White
    running_color_list.color[5] = CRGB(64,0,0);  // Red
  }

  CRGB get_running_color()
  {
    return running_color_list.color[0];
  }

  string get_running_color_str()
  {
    return running_color_list.strRunningColor;
  }

  CRGB get_countdown_color()
  {
    if (cdTIMER.is_active() == false)
    {
      return running_color_list.color[0];
    }
    else
    {
      // Compute the timer color.
      CRGB countdown_color;

      // Get % complete
      float pos = cdTIMER.timer_position(tmeCURRENT_FRAME_TIME);

      // Get Section of Color List
      int section = floor((running_color_list.size -1) * pos);
      
      // Determine size in time of each secion.
      float section_size = 1 / (float)(running_color_list.size -1);

      // Get % Section complete
      unsigned long section_time_removed = section * (cdTIMER.duration() * section_size);
      unsigned long section_elaped_time = cdTIMER.elapsed_time(tmeCURRENT_FRAME_TIME) - section_time_removed;

      float pwr = ComputePower(section_elaped_time, cdTIMER.duration() * section_size);

      // Dither Color and get results
      if (section < running_color_list.size -1)
      {
        bigCRGB big_countdown_color = Dither(pwr, running_color_list.color[section], running_color_list.color[section + 1]);
        
        countdown_color.r = big_countdown_color.r;
        countdown_color.g = big_countdown_color.g;
        countdown_color.b = big_countdown_color.b;
      }
      else
      {
        //cdTIMER.end();
        countdown_color = running_color_list.color[running_color_list.size - 1];
      }

      return countdown_color;
    }
  }

  void set_running_color(CRGB Running_Color, string strColor)
  {
    running_color_list.color[0] = Running_Color;
    running_color_list.strRunningColor = strColor;
    booRunning_State_File_Dirty = true;
  }

  void start_timer(int Seconds)
  {
    cdTIMER.set_timer(tmeCURRENT_FRAME_TIME, Seconds);
  }


  void store_compute_time(double fltComputeTime)
  // Stores the time the program spent actively running, for diag. 
  {
    dblCOMPUTETIME.data = fltComputeTime;
  }

  void store_cycle_time(double fltCycleTime)
  // Stores the time the program spent point to point while running, for diag. 
  {
    dblCYCLETIME.data = fltCycleTime;
    /*
    if (fltCycleTime > fltCYCLETIME.max)
    {
      fltCYCLETIME.max = fltCycleTime;
    }
    */
  }

  double store_sleep_time(double tmeSleep)
  // Pass through variable
  // Stores the Sleep time to be displayed in diag, then returns the same value.
  {
    dblPREVSLEEPTIME.data = tmeSleep;
    return tmeSleep;
  }
  
  double get_sleep_time(double Current_Time, unsigned long Wake_Time)
  {
    // Return, in microseconds, the amount of time required to sleep.
    
    double sleeptime = 0;

    if(Current_Time < Wake_Time)
    {
      sleeptime = (unsigned long)Wake_Time - Current_Time;
    }

    return sleeptime;
  }

  void read_hardware_status(int Milis_Frequency)
  {
    hsHardware_Status.read_hardware_status(tmeCURRENT_FRAME_TIME, Milis_Frequency);
  }

  // reset monitor times.
  void refresh()
  {
    dblCOMPUTETIME.min  = 0;
    dblCOMPUTETIME.max  = 0;
    dblSLEEPTIME.min    = 0;
    dblSLEEPTIME.max    = 0;
    dblCYCLETIME.min    = 0;
    dblCYCLETIME.max    = 0;
  }
 };
// -------------------------------------------------------------------------------------

// -------------------------------------------------------------------------------------
// Tacks all key presses and remembers data associated to whatever key is pressed.
class Keys
{
  private:
  struct Letter
  // For each letter, assign a behavior and type for it.
  {
    int LETTER;           // Letter, keypress, main value
    int COUNT = 0;        // set up how many times the key can be pressed brofor reset.
    int VALUE = 0;        // with every press, this value increases, this is value returned.
    bool PRESSED = true;  // Assume anything could have been press when 
                          //   program starts.
    bool ACTIVE = true ;  // Only process keys that are set to active.
  };

  // Full Command Line value(as is)
  struct CommandLine
  {
    string COMMANDLINE = "";
    bool PRESSED = true;
    bool CLEARED = true;
  };

  public:
  Letter Chars[256];      // Full array of all letters
  CommandLine Command;    // Command Line Reference.

  void cmdClear()
  // Clear Command line
  {
    Command.COMMANDLINE = "";
    Command.PRESSED = true;
    Command.CLEARED = true;
  }

  bool cmdPressed()
  // Return if Command Line Recently Changed.
  {
    return Command.PRESSED;
  }
  
  bool cmdCleared()
  // Return if the Command was cleared. Reset it after read if it was.
  {
    if (Command.CLEARED == false)
    {
      return false;
    }
    else
    {
      Command.CLEARED = false;
      return true;
    }
  }

  string cmdRead()
  // Read Command Line and sets recently changed to false (no longer dirty)
  {
    Command.PRESSED = false;
    return(Command.COMMANDLINE);
  }

  void cmdIn(int c)
  // Add another character to the command line.
  {
    if(c == (char)'\n')
    {
      // If enter pressed, clear the line.
      cmdClear();
    }
    else
    {
      //if( (c>47 && c<57) || (c>65 && c<90) || (c>97 && c<122) )
      if( (c>=32 && c<126) )
      {
        // only accept letters and numbers.
        Command.COMMANDLINE = Command.COMMANDLINE + (char)c;
        Command.PRESSED = true;

        // Limit Command Line Size. Clear when too big.
        if (Command.COMMANDLINE.size() > 10)
        {
          cmdClear();
        }
      }
    }
  }

  void cmdInString(string cmd)
  // Add another character to the command line.
  {
    Command.COMMANDLINE = cmd;
    Command.PRESSED = true;

    if (Command.COMMANDLINE.size() > 10)
    {
      cmdClear();
    }
  }

  void set(int letter, int size)
  // Set behavior of letter to be watched.
  {
    Chars[letter].COUNT = size - 1;
    Chars[letter].VALUE = 0;
  }

  void in(int c)
  // Letter watched is pressed, change its value atnd set pressed (dirty)
  {
    if (Chars[c].ACTIVE == true)
    {
      Chars[c].VALUE++;
      Chars[c].PRESSED = true;
      if (Chars[c].VALUE > Chars[c].COUNT)
      {
        Chars[c].VALUE = 0;
      }
    }
  }

  int get(int c)
  // return value of letter and reset pressed (clean)
  {
    Chars[c].PRESSED = false;
    return Chars[c].VALUE;
  }

  int getnoreset(int c)
  // return value of letter and reset pressed (clean)
  {
    return Chars[c].VALUE;
  }

  // returns true false value of letter, reset pressed (clean)
  bool getTF(int c)
  {
    Chars[c].PRESSED = false;
    if (Chars[c].VALUE == 0)
      return false;
    else
      return true;
  }

  // returns pressed value (clean or dirty)
  bool pressed(int c)
  {
    return (Chars[c].PRESSED);
  }
};
// -------------------------------------------------------------------------------------

// -------------------------------------------------------------------------------------
// Keeps track of mouse stuff.
class TheMouse
{
  private:
  
  int X = 0;
  int Y = 0;
  int B = 0;
  //MEVENT MOUSE_EVENT;

  int XDOWN = 0;
  int YDOWN = 0;

  int XCLICK = 0;
  int YCLICK = 0;

  bool CLICKED = false;

  public:

  int x()   // X Pos
  {
    return X;
  }
  
  int y()   // Y Pos
  {
    return Y;
  }
  
  //MEVENT mouse_event()   // B Pos
  int b() // B Pos
  {
    //return MOUSE_EVENT;
    return B;
  }

  int x_clicked()   // Clicked X pos
  {
    return XCLICK;
  }

  int y_clicked()   // Clicked Y pos
  {
    return YCLICK;
  }

  void check_click()
  // Do stuff on click down and click up.
  {
    //if (MOUSE_EVENT.bstate & (BUTTON1_CLICKED || BUTTON1_RELEASED))
    if (B == 1 || B == 4)
    // Mouse Button Down and Up.
    {
      XCLICK = X;
      YCLICK = Y;
      CLICKED = true;
    }
    //else if (MOUSE_EVENT.bstate & BUTTON1_PRESSED)
    else if (B == 2)
    // Mouse Button Down.
    {
      XDOWN = X;
      YDOWN = Y;
      CLICKED = false;
    }
  }

  //void store(int x, int y, MEVENT &mouse_event)
  void store(int x, int y, int b)
  // Put mouse changes into storage.
  {
    X = x;
    Y = y;
    //MOUSE_EVENT = mouse_event;
    B = b;

    check_click();
  }

  bool Clicked()
  // Check Clicked status.  If true clear click status.
  {
    if (CLICKED == false)
    {
      return false;
    }
    else 
    {
      CLICKED = false;
      return true;
    }
  }
};
// -------------------------------------------------------------------------------------

// -------------------------------------------------------------------------------------
// Screen Status Variables
class ScreenStatus
{
  public:
  // Main Refresh Indicator
  bool Needs_Refresh = false;
  
  //bool Needs_Redraw = false;

  // Windows - Controls to say if a window should be displayed.
  bool Window_Status = false;
  bool Window_Buttons = false;
  bool Window_Debug = false;
  bool Window_Timer = false;
  bool Window_CPicker = false;
  bool Window_Tabs = false;
  bool Window_Console = false;
  bool Window_Player = false;
  bool Window_Craft_Stat = false;
  bool Window_Radio = false;
  
  // Refresh is set to true only if the value 
  //  of displaying the window has changed. 
  //  Yes, too much code for something so redudantly simple. Later.
  void Window_Status_On()
  {
    if (Window_Status == false)
    {
      Window_Status = true;
      Needs_Refresh = true;
    }
  }

  void Window_Status_Off()
  {
    if (Window_Status == true)
    {
      Window_Status = false;
      Needs_Refresh = true;
    }
  }

    void Window_Buttons_On()
  {
    if (Window_Buttons == false)
    {
      Window_Buttons = true;
      Needs_Refresh = true;
    }
  }

  void Window_Buttons_Off()
  {
    if (Window_Buttons == true)
    {
      Window_Buttons = false;
      Needs_Refresh = true;
    }
  }

  void Window_Debug_On()
  {
    if (Window_Debug == false)
    {
      Window_Debug = true;
      Needs_Refresh = true;
    }
  }

  void Window_Debug_Off()
  {
    if (Window_Debug == true)
    {
      Window_Debug = false;
      Needs_Refresh = true;
    }
  }

  void Window_Timer_On()
  {
    if (Window_Timer == false)
    {
      Window_Timer = true;
      Needs_Refresh = true;
    }
  }

  void Window_Timer_Off()
  {
    if (Window_Timer == true)
    {
      Window_Timer = false;
      Needs_Refresh = true;
    }
  }

    void Window_CPicker_On()
  {
    if (Window_CPicker == false)
    {
      Window_CPicker = true;
      Needs_Refresh = true;
    }
  }

  void Window_CPicker_Off()
  {
    if (Window_CPicker == true)
    {
      Window_CPicker = false;
      Needs_Refresh = true;
    }
  }
  
  void Window_Console_On()
  {
    if (Window_Console == false)
    {
      Window_Console = true;
      Needs_Refresh = true;
    }
  }

  void Window_Console_Off()
  {
    if (Window_Console == true)
    {
      Window_Console = false;
      Needs_Refresh = true;
    }
  }

  void Window_Tabs_On()
  {
    if (Window_Tabs == false)
    {
      Window_Tabs = true;
      Needs_Refresh = true;
    }
  }

  void Window_Tabs_Off()
  {
    if (Window_Tabs == true)
    {
      Window_Tabs = false;
      Needs_Refresh = true;
    }
  }

  void Window_Player_On()
  {
    if (Window_Player == false)
    {
      Window_Player = true;
      Needs_Refresh = true;
    }
  }

  void Window_Player_Off()
  {
    if (Window_Player == true)
    {
      Window_Player = false;
      Needs_Refresh = true;
    }
  }

  void Window_Craft_Stat_On()
  {
    if (Window_Craft_Stat == false)
    {
      Window_Craft_Stat = true;
      Needs_Refresh = true;
    }
  }

  void Window_Craft_Stat_Off()
  {
    if (Window_Craft_Stat == true)
    {
      Window_Craft_Stat = false;
      Needs_Refresh = true;
    }
  }

    void Window_Radio_On()
  {
    if (Window_Radio == false)
    {
      Window_Radio = true;
      Needs_Refresh = true;
    }
  }

  void Window_Radio_Off()
  {
    if (Window_Radio == true)
    {
      Window_Radio = false;
      Needs_Refresh = true;
    }
  }
};
// -------------------------------------------------------------------------------------



#endif