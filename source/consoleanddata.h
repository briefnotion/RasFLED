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
#include "screen3.h"

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

  Screen3 Screen;

  Keys keywatch;

  ScreenStatus ScrStat;

  void set_screen(system_data &sdSysData)
  {
    ScrStat.Window_Status_On();
    ScrStat.Window_Buttons_On();
    ScrStat.Window_Debug_Off();
    ScrStat.Window_Console_On();

    Screen.set(sdSysData, ScrStat);
  }

  void printi(string in)
  // Print to console immediately to console without waiting for refresh.
  {
    // console line time is inaccurate.  Will only refect previous console update time
    //  and not actual time printed.  Current time is not global.  This is a filler.
    clou.add(Update_Time,in);         // Add line to console line list.
    Screen.printout(clou, ScrStat);  // Immediately display the line onto the screen.
  }

  void deb(string strPrintI)
  {
    printi("DEBUG: " + strPrintI);
  }

  void printwait(string in)
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
      //printwait("RESIZING SCREEN");
      keywatch.Chars[KEYRESIZE].VALUE = 0;
      clou.RefreshConsole = true;
      ScrStat.Needs_Refresh = true;

      Screen.reset(ScrStat);
    }
  }

  void processmouseinput(system_data &sdSysData)
  {
    if (mouse.Clicked() == true)
    {
      // Get Clicked Button Name and Value
      int id = -1;
      string name = "";
      int value = 0;

      if (Screen.bzButtons.check_click(mouse.x_clicked(),mouse.y_clicked()) == true)
      // Check for any clicked buttons or if it was just empty space.
      //  If anything was clicked, the list in the bzButtons will be updated.
      {
        // Go through all the buttons in the screen and update their values, 
        //  this will also update their values in the bzButtons list.

        Screen.update_buttons();

        // If a Main Button is clicked, dont need the Color Picker
        //  Close it if it was opened.
        ScrStat.Window_CPicker_Off();

        // Next time the screen is refreshed, redraw the button.
        //ScrStat.Buttons_Refresh = true;

        // Get name and value of button in list that was clicked, then set it 
        //  as unclicked.
        string name = "empty";
        int value = 0;
        name = Screen.bzButtons.get_clicked_name();
        value = Screen.bzButtons.get_clicked_value(name);

        // ---debug
        // Print Returned Value
        //printi("");
        //printi("returned " + to_string(value) + " " + name);

        /* ---debug
        // Print Zones
        printi("");
        for(int pos=0; pos < Screen.bzButtons.size(); pos++)
        {
          printi(Screen.bzButtons.name(pos));
        }
        printi("");
        */
        
        if (name.compare("MENUCONTROL") == 0)
        // Load System Buttons
        {
          Screen.buttons_menu_control(sdSysData);
        }

        if (name.compare("MENUSYSTEM") == 0)
        // Load System Buttons
        {
          Screen.buttons_menu_system(sdSysData);
        }
        
        else if (name.compare("MENUHOME") == 0)
        // Load Home Buttons
        {
          Screen.buttons_menu_home(sdSysData);
        }

        else if (name.compare("MENUOVERHEAD") == 0)
        // Load Home Buttons
        {
          Screen.buttons_menu_overhead_color(sdSysData);
          keywatch.cmdIn('o');
        }

        else if(name.compare("EXIT") == 0)
        // Exit RasFLED
        {
          keywatch.cmdInString("X");
        }

        else if (name.compare("DAYNIGHT") == 0)
        // Day Night Mode
        {
          if (value == 1)
          {
            keywatch.cmdInString("dayon");
            Screen.bzButtons.change_label("DAYNIGHT", "%%Day");
          }
          else
          {
            keywatch.cmdInString("dayoff");
            Screen.bzButtons.change_label("DAYNIGHT", "%%Night");
          }
        }

        else if(name.compare("TIMER") == 0)
        // Start Timer
        {
          keywatch.cmdInString("  ");
        }

        else if(name.compare("OVERHEAD") == 0)
        // Start Overhead Lights
        {
          keywatch.cmdInString("oo");
          Screen.buttons_menu_home(sdSysData);
        }

        else if(name.compare("FLASH") == 0)
        // Flash Lights
        {
          keywatch.cmdInString("ff");
        }

        else if(name.compare("CLEARANIMS") == 0)
        // Clear Most Animations
        {
          keywatch.cmdInString("``");
        }

        else if(name.compare("HAZARD") == 0)
        // Start Hazard Lights
        {
          keywatch.cmdInString("hh");
        }

        else if(name.compare("DEBUG") == 0)
        // Start Hazard Lights
        {
          keywatch.cmdInString("/");
        }

        else if(name.compare("RUNNINGCOLOR") == 0)
        // Start Hazard Lights
        {
          keywatch.cmdIn('r');
          ScrStat.Window_CPicker_On();
        }

        else if(name.compare("CHOSECOLOR") == 0)
        {
          ScrStat.Window_CPicker_On();
        }

        // Update changes to buttons
        Screen.update_buttons();

      }

      // -----------------------------------

      if (Screen.bzCPicker.check_click(mouse.x_clicked(),mouse.y_clicked()) == true)
      // Check for any clicked buttons or if it was just empty space.
      //  If anything was clicked, the list in the bzButtons will be updated.
      {
        string name = "empty";
        int value = 0;
        name = Screen.bzCPicker.get_clicked_name();
        value = Screen.bzCPicker.get_clicked_value(name);
      
        //Color Picker Window
        if(name.compare("EXITCOLOR") == 0)
        // Start Hazard Lights
        {
          ScrStat.Window_CPicker_Off();
        }
        else if(name.compare("RED") == 0)
        // Start Hazard Lights
        {
          keywatch.cmdIn('r');
          ScrStat.Window_CPicker_Off();
          Screen.buttons_menu_home(sdSysData);
        }
        else if(name.compare("GREEN") == 0)
        // Start Hazard Lights
        {
          keywatch.cmdIn('g');
          ScrStat.Window_CPicker_Off();
          Screen.buttons_menu_home(sdSysData);
        }
        else if(name.compare("BLUE") == 0)
        // Start Hazard Lights
        {
          keywatch.cmdIn('b');
          ScrStat.Window_CPicker_Off();
          Screen.buttons_menu_home(sdSysData);
        }
        else if(name.compare("PURPLE") == 0)
        // Start Hazard Lights
        {
          keywatch.cmdIn('u');
          ScrStat.Window_CPicker_Off();
          Screen.buttons_menu_home(sdSysData);
        }
        else if(name.compare("YELLOW") == 0)
        // Start Hazard Lights
        {
          keywatch.cmdIn('y');
          ScrStat.Window_CPicker_Off();
          Screen.buttons_menu_home(sdSysData);
        }
        else if(name.compare("CYAN") == 0)
        // Start Hazard Lights
        {
          keywatch.cmdIn('c');
          ScrStat.Window_CPicker_Off();
          Screen.buttons_menu_home(sdSysData);
        }
        else if(name.compare("ORANGE") == 0)
        // Start Hazard Lights
        {
          keywatch.cmdIn('n');
          ScrStat.Window_CPicker_Off();
          Screen.buttons_menu_home(sdSysData);
        }
        else if(name.compare("WHITE") == 0)
        // Start Hazard Lights
        {
          keywatch.cmdIn('w');
          ScrStat.Window_CPicker_Off();
          Screen.buttons_menu_home(sdSysData);
        }
      }

    }
  }

  

  void update_displayed_time(unsigned long time)
  // Set the consoles last redraw time, a now should be passed in.
  {
    Update_Time = time;
  }
  
  void output(system_data &sdSysData)
  // Screen Update
  {
    // Check screen redraw variables.
    //  Set Debug
    if (keywatch.get(KEYDEBUG) == 1)
    {
      ScrStat.Window_Debug_On();
      //ScrStat.Needs_Refresh = true;
    }
    else 
    {
      ScrStat.Window_Debug_Off();
      //ScrStat.Needs_Refresh = true;
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