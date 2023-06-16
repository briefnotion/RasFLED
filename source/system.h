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
#include <string>
#include <deque>

// RASFled related header files
#include "configuration.h"
#include "helper.h"
#include "commands.h"
#include "hardware_status.h"

#include "aircraft_coordinator.h"
#include "alert_system.h"
#include "comport.h"
#include "auto.h"

using namespace std;

// ***************************************************************************************
// STRUCTURES AND CLASSES
// ***************************************************************************************


class SECTION_STATUS
{
  private:

  bool Value = false;

  public:

  void on(bool &Needs_Refresh);

  void off(bool &Needs_Refresh);

  bool value();
};

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
    float min   = 0;    // Unfinished?
    float max   = 0;    // Unfinished?
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
  STAT_DATA_DOUBLE dblCOMPUTETIME;   // Loop time spent while only proceessing.
  STAT_DATA_DOUBLE dblSLEEPTIME;     // Calculated time needed to sleep.
  STAT_DATA_DOUBLE dblCYCLETIME;     // Amount of time to complete an entire cycle.
  STAT_DATA_DOUBLE dblPREVSLEEPTIME; // Stored value returned on pref sleep cycle.

  ALERT_SYSTEM ALERTS;

  // For Debuging Gadgets
  //bool DEBUG_COUNTER = false;

  // Door Module Support
  deque<bool> boolDOOR_SENSOR_STATUS;

  int   intDoorsOpen = 0;           // Amount of doors open.
  bool  booPulsesRunning = false;   // Are exta anims running.
  bool  booOverheadRunning = false; // Are exta anims running.
  bool  booHazardRunning = false;   // Are exta anims running.

  CRGB PULSE_COLOR;
  CRGB TMP_PASSTHRU_COLOR;
  
  // Timer and Color Schemes
  countdown_timer cdTIMER;
  running_colors running_color_list;

  // Hardware Status Indicators
  HARDWARE_STATUS hsHardware_Status;

  // Lights on or off
  BOOL_BOUNCE Lights_On;

  // Day Mode Active
  bool Day_On = false;
  BOOL_WITH_OVERRIDE Day_On_With_Override;

  // Files
  bool booRunning_State_File_Dirty = false;

  // Event System
  deque<int> intCHANNEL_GROUP_EVENTS_COUNTS;

  COMMAND_THREAD Command_Thread;

  // Radio Variables
  AIRCRAFT_COORDINATOR AIRCRAFT_COORD;

  // Test Mode
  int t_group = 0;
  int t_strip = 0;

  // Communications Port
  COMPORT COMMS;
  AUTOMOBILE CAR_INFO;

  // -------------------------------------------------------------------------------------

  void init();

  void store_Current_Frame_Time(unsigned long tmeCurrent_Time_millis);

  // Reference to the door values
  void store_door_switch_states();

  void init_running_color_list();

  CRGB get_running_color();

  string get_running_color_str();

  CRGB get_countdown_color();

  void set_running_color(CRGB Running_Color, string strColor);

  void start_timer(int Seconds);

  double store_sleep_time(double tmeSleep);
  
  double get_sleep_time(double Current_Time, unsigned long Wake_Time);

  void read_hardware_status(int Milis_Frequency);

  // reset monitor times.
  void refresh();
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
    bool CARRAGE_RETURN = false;
  };

  public:
  Letter Chars[256];      // Full array of all letters
  CommandLine Command;    // Command Line Reference.

  void cmdClear();

  bool cmdPressed();
  
  bool cmdCleared();

  string cmdRead();

  void cmdIn(int c);

  void cmdInString(string cmd);

  void set(int letter, int size);

  void in(int c);

  int get(int c);

  int getnoreset(int c);

  // returns true false value of letter, reset pressed (clean)
  bool getTF(int c);

  // returns pressed value (clean or dirty)
  bool pressed(int c);
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

  //MEVENT MOUSE_EVENT

  int XDOWN = 0;
  int YDOWN = 0;

  int XCLICK = 0;
  int YCLICK = 0;

  bool CLICKED = false;

  public:

  int x();   // X Pos
  
  int y();   // Y Pos
  
  //MEVENT mouse_event()   // B Pos
  int b(); // B Pos;

  int x_clicked();   // Clicked X pos

  int y_clicked();   // Clicked Y pos

  void check_click();
  // Do stuff on click down and click up.

  //void store(int x, int y, MEVENT &mouse_event)
  void store(int x, int y, int b);
  // Put mouse changes into storage.

  bool Clicked();
// Check Clicked status.  If true clear click status.
};
// -------------------------------------------------------------------------------------

// -------------------------------------------------------------------------------------
// Screen Status Variables
class ScreenStatus
{
  public:
  // Main Refresh Indicator
  bool Needs_Refresh = false;

  SECTION_STATUS Window_CYBR;
  SECTION_STATUS Window_Status;
  SECTION_STATUS Window_Buttons;
  SECTION_STATUS Window_Debug;
  SECTION_STATUS Window_Timer;
  SECTION_STATUS Window_CPicker;
  SECTION_STATUS Window_Tabs;
  SECTION_STATUS Window_Console;
  SECTION_STATUS Window_Automobile_Screen;
  SECTION_STATUS Window_Player;
  SECTION_STATUS Window_ADS_B_Buttons;
  SECTION_STATUS Window_ADS_B_Screen;
  SECTION_STATUS Window_Log_Screen;
  SECTION_STATUS Window_Alerts_Screen;
};
// -------------------------------------------------------------------------------------



#endif