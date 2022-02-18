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
#include <string.h>
#include <deque>

// RASFled related header files
#include "definitions.h"
#include "helper.h"
#include "system.h"
#include "screen2.h"

using namespace std;

// ***************************************************************************************
// STRUCTURES AND CLASSES
// ***************************************************************************************

// -------------------------------------------------------------------------------------
// All variables to keep track of the interface and program status.  All psssive.

// -------------------------------------------------------------------------------------
// NCurses Console.  Responsible for all screen and user interfaces.
class Console  
{
  private:

  int key = -1;

  ConsoleLineList clou;
  unsigned long Update_Time = 0;
  
  // Mouse position and button position
  TheMouse mouse;

  public:

  Screen2 Screen;

  Keys keywatch;

  ScreenStatus ScrStat;

  void printi (string in)
  // Print to console immediately to console without waiting for refresh.
  {
    // console line time is inaccurate.  Will only refect previous console update time
    //  and not actual time printed.  Current time is not global.  This is a filler.
    clou.add(Update_Time,in);         // Add line to console line list.
    Screen.printout(clou);  // Immediately display the line onto the screen.
  }

  void deb(string strPrintI)
  {
    printi("DEBUG: " + strPrintI);
  }

  void printwait (string in)
  // Print out a line to console during next refresh.
  {
    // console line time is inaccurate.  Will only refect previous console update time
    //  and not actual time printed.  Current time is not global.  This is a filler.
    clou.add(Update_Time,in);         // Add line to console line list.
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

  void readkeyboardinput2()
  // read keyboard for keypresses.  Just exit if nothing is being pressed.
  {
    key = wgetch(stdscr);

    char buffer[512];
    size_t max_size = sizeof(buffer);
    
    if (key != ERR)
    {
      // Check for Mouse Events.
      if (key == KEY_MOUSE)
      {
        MEVENT event;
        if (getmouse(&event) ==OK)
        {
          mouse.store(event.x, event.y, event.bstate);
          
          // -------- Remove    Debug routine to print mouse position int the console. 
          //printi(to_string(mouse.x()) + " " + to_string(mouse.y()) + " " + to_string(mouse.b()));
          //if (mouse.Clicked() == true)
          //{
          //  printi("Clicked at " + to_string(mouse.x_clicked()) + " " + to_string(mouse.y_clicked()));
          //}
          // ----------
        }
      }
      // Check for Resize Screen.
      else if (key == KEY_RESIZE)
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
  // Run through this routine before the console is refreshed.
  {
    // Check for screen resize.
    if (keywatch.get(KEYRESIZE) == 1)
    {
      printwait("RESIZING SCREEN");
      keywatch.Chars[KEYRESIZE].VALUE = 0;

      //set(CONSOLESPLITSIZE);
      Screen.set(CONSOLESPLITSIZE);
    }
  }

  void update_displayed_time(unsigned long time)
  // Set the consoles last redraw time, a now should be passed in.
  {
    Update_Time = time;
  }
  
  void output(system_data sdSysData)
  // Screen Update
  {
    // Check screen redraw variables.
    //  Set Debug
    if (keywatch.get(KEYDEBUG) == 1)
    {
      ScrStat.Debug = true;
    }
    else 
    {
      ScrStat.Debug = false;
    }

    //  Set Debug Refresh
    if (keywatch.get(KEYDEBUG) == true)
    {
      ScrStat.Debug_Refresh = true;
    }

    // Screen Update
    Screen.output(sdSysData, keywatch, clou, ScrStat, mouse);
    
    /*  Debug routine to verify console not in redisplay loop cycle.
    if(clou.avail()==true)
    {
      printi("Printed not cleared.");
    }
    */

  }

};



#endif