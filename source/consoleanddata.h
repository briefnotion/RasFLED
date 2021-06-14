// ***************************************************************************************
// *
// *    Core       | Everything within this document is proprietary to Core Dynamics.
// *    Dynamics   | Any unauthorized duplication will be subject to prosecution.
// *
// *    Department : (R+D)^2                        Name: consoleanddata.h
// *       Sub Dept: Programming
// *    Location ID: 856-45B
// *                                                      (c) 2856 - 2858 Core Dynamics
// ***************************************************************************************

#ifndef CONSOLEANDDATA_H
#define CONSOLEANDDATA_H

// Standard Header Files
#include <stdio.h>
#include <ncurses.h>

// RASFled related header files
#include "definitions.h"
#include "helper.h"


// ***************************************************************************************
// STRUCTURES AND CLASSES
// ***************************************************************************************
//sdSystem.CONFIG.i
class configuration
{
  public:
  // -------------------------------------------------------------------------------------
  int iLED_Size_Test_Strip                = 63;

  int iLED_Size_Door_Back_Driver          = 70;
  int iLED_Size_Door_Back_Passenger       = 70;
  int iLED_Size_Door_Front_Driver         = 66;
  int iLED_Size_Door_Front_Passenger      = 66;

  int iLED_Size_Overhead_Back_Driver      = 52;
  int iLED_Size_Overhead_Back_Passenger   = 52;
  int iLED_Size_Overhead_Front_Driver     = 52;
  int iLED_Size_Overhead_Front_Passenger  = 52;

  // Computed LED Count
  int iLED_Count_Back_Driver = 0;
  int iLED_Count_Front_Driver = 0;
  int iLED_Count_Back_Passenger = 0;
  int iLED_Count_Front_Passenger = 0;

  
  // -------------------------------------------------------------------------------------
  // Hardware to Software definitions
  // -------------------------------------------------------------------------------------
  
  // -------------------------------------------------------------------------------------
  // Raspberry Pi switch pin for doors and switches. Defined as WiringPi id.
  // console: gpio -v       (check installation)
  // console: gpio readall  (check wiring pin numbers)

  // On off buttons, door sensors, switches.
  int iSWITCH_PINs0       = 22;      // GPIO.22 - Pin 31 - Hardware Open Close Door Sensor 0
  int iSWITCH_PINs1       = 23;      // GPIO.23 - Pin 33 - Hardware Open Close Door Sensor 1
  int iSWITCH_PINs2       = 24;      // GPIO.24 - Pin 35 - Hardware Open Close Door Sensor 2
  int iSWITCH_PINs3       = 25;      // GPIO.25 - Pin 37 - Hardware Open Close Door Sensor 3

  int iAUXDRLINGERFRT     = 15000;    // How long the Front Door lights stay on after close
  int iAUXDRLINGERBCK     = 25000;    // How long the Back Door lights stay on after close

  // -------------------------------------------------------------------------------------
  // Door Switch Reference
  int iNUM_CHANNELS       = 4;   // Amount of LED strips we will be controlling.
  int iNUM_TIMED_EVENTS   = 50;  // Untill I can remember how LL, this is being
  //  Also, total number of this will be multiplied by the
  //  amount of LED strips you have setup.  Watch your memory.
  int iNUM_SWITCHES       = 4;   

  int iBRIGHTNESS         = 96;  //96  Using Example Code.  Max unknown
  int iFRAMES_PER_SECOND  = 50; // Will not be necessary, but keeping, for now, just in 
  //  case.

  // -------------------------------------------------------------------------------------
  // Door Switch Reference
  int iDoor_Back    = 0; // Back Door Switch
  int iDoor_Front   = 1; // Front Door Switch
  int iDoor_Aux     = 2; // Aux Door Switch 
};


// -------------------------------------------------------------------------------------
// All variables to keep track of the interface and program status.  All psssive.
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

  class running_colors
  {
    public:
    // array for now. ll in future if necessary.
    int size = 4;
    std::string strRunningColor = "";  // 
    CRGB color[4];
  };

  public:
  unsigned long tmeCURRENT_FRAME_TIME = 0;

  configuration CONFIG;

  stat_data fltCOMPUTETIME;   // Loop time spent while only proceessing.
  stat_data fltSLEEPTIME;     // Calculated time needed to sleep.
  stat_data fltCYCLETIME;     // Amount of time to complete an entire cycle.
  stat_data fltPREVSLEEPTIME; // Stored value returned on pref sleep cycle.

  std::string strLEDRANGE  = "";    // Text showing what LEDs will be Displayed.
  std::string strLEDLIMITS = "";    // Text showing what LEDd, upper or lower, displayed.

  int   intDoorsOpen = 0;           // Amount of doors open.
  bool  booPulsesRunning = false;   // Are exta anims running.
  bool  booOverheadRunning = false; // Are exta anims running.
  bool  booHazardRunning = false;   // Are exta anims running.

  // PrintBufferData - temparory fix to print things when the console cant be accessed.
  bool        booprintbuffer = false;
  std::string strprintbuffer = "";
  /* Usage:
      booprintbuffer = true;
      strprintbuffer = std::to_string(section_elaped_time) + "       ";
    Does not clean up after itself */

  // Timer and Running Colors
  countdown_timer cdTIMER;

  running_colors running_color_list;

  // store copies of displayed system data
  bool *boolDOORSENSORS = (bool*) malloc(CONFIG.iNUM_SWITCHES * sizeof(bool));;
  int  *intEVENTCOUNTS = (int*) malloc(CONFIG.iNUM_SWITCHES * sizeof(int));;

  // Files
  bool booRunning_State_File_Dirty = false;

  void store_Current_Frame_Time(unsigned long tmeCurrent_Time_millis)
  {
    tmeCURRENT_FRAME_TIME = tmeCurrent_Time_millis;
    if (cdTIMER.is_active())
    {
      cdTIMER.trigger_check(tmeCurrent_Time_millis);
    }

    if(cdTIMER.is_active() == true)
    {
      booprintbuffer = true;
      strprintbuffer =  std::to_string(cdTIMER.elapsed_time(tmeCurrent_Time_millis)) + "  " + std::to_string(cdTIMER.is_triggered()) + "  " +  std::to_string(cdTIMER.is_checked()) + "  ";
    }
  }

  // Reference to the door values
  void store_door_switch_states(bool switches[])
  {
    for(int x=0; x < CONFIG.iNUM_SWITCHES; x++)
    {
      boolDOORSENSORS[x] = switches[x];
    }
  }

  void init_running_color_list()
  {
    running_color_list.strRunningColor = "Blank";
    running_color_list.color[0] = CRGB(0,0,0);
    running_color_list.color[1] = CRGB(0,64,0);  // Green
    running_color_list.color[2] = CRGB(48,48,0); // Yellow
    running_color_list.color[3] = CRGB(64,0,0);  // Red
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
      int section = 0;
      float section_size = 1 / (float)running_color_list.size;

      section = running_color_list.size;
      for (int x = 0; x < running_color_list.size; x++)
      {
        if ((pos >= x * section_size) && (pos < (x+1) * section_size))
        {
          section = x;
        }
      }

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

  void set_running_color(CRGB Running_Color, std::string strColor)
  {
    running_color_list.color[0] = Running_Color;
    running_color_list.strRunningColor = strColor;
    booRunning_State_File_Dirty = true;
  }

  void start_timer(int Seconds)
  {
    cdTIMER.set_timer(tmeCURRENT_FRAME_TIME, Seconds);
  }

  // Reference for the amount for events running.
  void store_event_counts(int EventCount0, int EventCount1, int EventCount2, int EventCount3)
  {
    intEVENTCOUNTS[0] = EventCount0;
    intEVENTCOUNTS[1] = EventCount1;
    intEVENTCOUNTS[2] = EventCount2;
    intEVENTCOUNTS[3] = EventCount3;
  }

  // Reference for the time (elapsed) since program start.
  void store_compute_time(float fltComputeTime)
  {
    fltCOMPUTETIME.data = fltComputeTime;
  }

  void store_cycle_time(float fltCycleTime)
  {
    fltCYCLETIME.data = fltCycleTime;
    if (fltCycleTime > fltCYCLETIME.max)
    {
      fltCYCLETIME.max = fltCycleTime;
    }
  }

  // Reference since sleep started and wake up time elapsed. 
  float getsleeptime(int intFPS)
  {
    // Return, in milliseconds, the amount of time required to sleep 
    //  before returning to the next cycle. 
    float sleeptime = (1000 / intFPS) - fltCOMPUTETIME.data;
    
    if (sleeptime < 0)
    {
      sleeptime = 0;
    }

    fltPREVSLEEPTIME.data = sleeptime;
    return (sleeptime);
  }

  // reset monitor times.
  void refresh()
  {
    fltCOMPUTETIME.min  = 0;
    fltCOMPUTETIME.max  = 0;
    fltSLEEPTIME.min    = 0;
    fltSLEEPTIME.max    = 0;
    fltCYCLETIME.min    = 0;
    fltCYCLETIME.max    = 0;
  }

};


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
    std::string COMMANDLINE = "";
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

  std::string cmdRead()
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
// NCurses Console.  Responsible for all screen and user interfaces.
class Console  
{
  private:

  // Keyboard input variable
  int key = -1;

  // NCurses Variables
  int YMax = 0;
  int XMax = 0;
  int Xmid = 0;
  
  WINDOW * winTop;
  WINDOW * winBot;
  std::vector<std::string> ou;

  std::string strBotLine;

  // Display Variables
  int YSeperator = 0;
  int YConOut = 0;

  unsigned long Update_Time = 0;
  
  public:
  Keys keywatch;

  void set(int intSeperator)
  {
    getmaxyx(stdscr, YMax, XMax);

    YSeperator = intSeperator;
    Xmid = XMax / 2;
  
    winTop = newwin(YSeperator, XMax, 0, 0);
    winBot = newwin(YMax - YSeperator, XMax, YSeperator, 0);
    refresh();

    //wborder(winTop,'|','|','-','-','/','\\','\\','/') ;
    //wborder(winBot,'|','|','-','-','/','\\','\\','/') ;
    
    //wborder(winTop,' ',' ','_','_','┌','┐','└','┘') ;
    //wborder(winBot,' ',' ','_','_','┌','┐','└','┘') ;

    wborder(winTop,' ',' ',' ','_',' ',' ',' ',' ') ;
    wborder(winBot,' ',' ',' ','_',' ',' ',' ',' ') ;

    wrefresh(winBot);
    wrefresh(winTop);
    
    strBotLine = "";
    strBotLine = strBotLine.append(XMax-1, '_');
    // cbreak();
	  // raw();
	  noecho();
  }

  void printout()
  // Print out console.
  {
    std::string strTemp;

    while(ou.size() > 0)
    {
      if ((YConOut > YMax - YSeperator - 2) || (YConOut < 1) )
      {
        YConOut = 1;
      }

      wmove(winBot, YConOut,0);
      wclrtoeol(winBot);
      mvwprintw(winBot, YConOut, 0, "%s", ou[0].c_str());

      wmove(winBot, YConOut +1,0);
      wclrtoeol(winBot);
      mvwprintw(winBot, YConOut +1 , 0, "%s", strBotLine.c_str());

      ou.erase(ou.begin());
      YConOut++;

      wrefresh(winBot);      
    }
  }

  void printi (std::string in)
  // Print to console immediatly to console without waiting for refresh.
  {
    ou.push_back(in);
    printout();
  }

  void printwait (std::string in)
  // Print out a line to console during next refresh.
  {
    ou.push_back(in);
  }

  bool isready(unsigned long time, int intmsWaitTime)
  {
    //Check to see if enough time has passed to refresh the console. (wait is in ms)
    if(time > Update_Time + intmsWaitTime)
    {
      return true;
    }
    else
    {
      return false;
    }
  }

  void readkeyboardinput()
  // read keyboard for keypresses.  Just exit if nothing is being pressed.
  {
    key = wgetch(stdscr);
    if (key != -1)
    {
      // Check for special characters first.
      if (key == KEY_RESIZE)
      {
        keywatch.in(KEYRESIZE);
      }
      else
      {
        // Put all remaining input into the Command Line.
        keywatch.cmdIn(key); 
      }
    }
  }

  void processkeyboadinput()
  // Run through this routine before before the console is refreshed.
  {
    // Check for screen resize.
    if (keywatch.get(KEYRESIZE) == 1)
    {
      printwait("RESIZING SCREEN");
      keywatch.Chars[KEYRESIZE].VALUE = 0;
      set(CONSOLESPLITSIZE);
    }
  }

  void update_displayed_time(unsigned long time)
  // Set the consoles last redraw time, a now should be passed in.
  {
    Update_Time = time;
  }

  // Draw the console, starting with status window, then update console with pending
  // console prints.
  void output(system_data sdSysData)
  {
    bool RedrawTestParts = false;

    // Check to see if we have just toggled the debug mode.  
    // If we have toggled DEBUG, then we will need to clean up things on the screan.
    if (keywatch.pressed(KEYDEBUG) == true)
    {
      RedrawTestParts = true;
    }
        
    // Debug Stuff: Display Compute Times
    if (keywatch.get(KEYDEBUG) == 1)
    {
      mvwprintw(winTop, 2, 26, "Compute: %fms", sdSysData.fltCOMPUTETIME.data);
      mvwprintw(winTop, 3, 26, "  Sleep: %fms", sdSysData.fltPREVSLEEPTIME.data);
      mvwprintw(winTop, 4, 26, "  Cycle: %fms", sdSysData.fltCYCLETIME.data);

      mvwprintw(winTop, 4, 47, "(m:%fms)", sdSysData.fltCYCLETIME.max);
      if (sdSysData.booprintbuffer == true)
      {
        mvwprintw(winTop, 4, 1, ":%s", sdSysData.strprintbuffer.c_str());
      }
    }
    else if ( RedrawTestParts == true )
    // If exiting debug mode, clean out what was printed in when in debug mode.
    {
      mvwprintw(winTop, 2, 26, "                       ");
      mvwprintw(winTop, 3, 26, "                       ");
      mvwprintw(winTop, 4, 26, "                       ");

      mvwprintw(winTop, 2, 47, "                      ");
      mvwprintw(winTop, 3, 47, "                      ");
      mvwprintw(winTop, 4, 47, "                      ");
    }
    
    // Debug stuff: Display Range and Seleced Strips to Diplay
    if(keywatch.get(KEYDEBUG) == 1)
    {
      // Display LED range selected to display.
      std::string strRange;
      std::string strLevel;

      // Displaying LEDs selected to be displayed CYCLE selected.
      switch (keywatch.get(KEYLEDDRCYCL))
      {
        case 0:   // Show all lights.  This is normal.
        {
          strRange = "A ";
          break;
        }
        case 1:   // Show only Light Set 1
        {
          strRange = "D1";
          break;
        }
        case 2:   // Show only Light Set 2
        {
          strRange = "D2";
          break;
        }
        case 3:   // Show only Light Set 3
        {
          strRange = "D3";
          break;
        }
        case 4:   // Show only Light Set 4
        {
          strRange = "D4";
          break;
        }

      }    

      // Check for Upper or Lower Range
      if (keywatch.get(KEYLEDUPLW) == 0)
      {
        strLevel = "L";
      }
      else
      {
        strLevel = "U";
      }

      // Draw RANGE and UPPER OR LOWER VALUES selected.
      mvwprintw(winTop, 2, 19, "RNG:%s", strRange.c_str());
      mvwprintw(winTop, 3, 19, "LVL:%s", strLevel.c_str());
    }    
    else if ( RedrawTestParts == true )
    // If exiting debug mode, clean out what was printed in when in debug mode.
      {
        mvwprintw(winTop, 2, 19, "      ");
        mvwprintw(winTop, 3, 19, "      ");
      }
    // ------

    //Display Door Statuses, highlighting values that are on (doors open)
    if (sdSysData.boolDOORSENSORS[0] == true) {wattron(winTop, A_REVERSE);}
    mvwprintw(winTop, 3, 7, "D1");
    if (sdSysData.boolDOORSENSORS[0] == true) {wattroff(winTop, A_REVERSE);}
    
    if (sdSysData.boolDOORSENSORS[1] == true) {wattron(winTop, A_REVERSE);}
    mvwprintw(winTop, 2, 7, "D2");
    if (sdSysData.boolDOORSENSORS[1] == true) {wattroff(winTop, A_REVERSE);}
    
    if (sdSysData.boolDOORSENSORS[2] == true) {wattron(winTop, A_REVERSE);}
    mvwprintw(winTop, 3, 10, "D3");
    if (sdSysData.boolDOORSENSORS[2] == true) {wattroff(winTop, A_REVERSE);}

    if (sdSysData.boolDOORSENSORS[3] == true) {wattron(winTop, A_REVERSE);}
    mvwprintw(winTop, 2, 10, "D4");
    if (sdSysData.boolDOORSENSORS[3] == true) {wattroff(winTop, A_REVERSE);}


    // Debug stuff: Display the amount of events, assoicated to each door, runnng .
    if (keywatch.get(KEYDEBUG) == 1)
    {
      mvwprintw(winTop, 3, 1, "%03d:E", sdSysData.intEVENTCOUNTS[0]);
      mvwprintw(winTop, 2, 1, "%03d:E", sdSysData.intEVENTCOUNTS[1]);
      mvwprintw(winTop, 3, 13, "E:%03d", sdSysData.intEVENTCOUNTS[2]);
      mvwprintw(winTop, 2, 13, "E:%03d", sdSysData.intEVENTCOUNTS[3]);
    }
    else if ( RedrawTestParts == true )
    // If exiting debug mode, clean out what was printed in when in debug mode.
    {
      mvwprintw(winTop, 3, 1, "     ");
      mvwprintw(winTop, 2, 1, "     ");
      mvwprintw(winTop, 3, 13, "     ");
      mvwprintw(winTop, 2, 13, "     ");
    }

    // Display Status
    if (RedrawTestParts == true)
    {
      if (keywatch.get(KEYDEBUG) == 1)
      {
        wattron(winTop, A_REVERSE);
        mvwprintw(winTop, 0, XMax - 5, "DIAG");
        wattroff(winTop, A_REVERSE);
      }
      else
      {
        mvwprintw(winTop, 0, XMax - 5, "    ");
      }
    }    

    mvwprintw(winTop, 0, 18, "REPEAT");
    mvwprintw(winTop, 0, 26, "DOORAWARE");

    // ----------------------------
    // Display Command Line
    if (keywatch.cmdPressed() == true)
    {
      if (keywatch.cmdCleared() == true)
      {
        // Blank out the line before redraw.
        wmove(winTop, 0, 1);
        //wclrtoeol(winTop);
        mvwprintw(winTop, 0, 1, "CMD: __________");
      }
      mvwprintw(winTop, 0, 1, "CMD: %s", keywatch.cmdRead().c_str());
    }
    
    // ----------------------------

    // Commit all our changes to the status portion of the screen (winTop)
    wrefresh(winTop);

    // Now that we are finished drawing the Console Status part of the screen, 
    // we needd to go to the console portion of the screen and update it.
    printout();
  }
};



#endif