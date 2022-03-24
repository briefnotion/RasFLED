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
#include "player.h"

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

  PLAYER the_player;

  /*
  bool load_movie_playlist()
  // Original play list loader. Was loading the playlist throught the compiler 
  //  before the playlist was loaded through a file.  This routine is no longer 
  //  needed.  Keeping it just in case.
  {
    the_player.Play_List.add_to_list("/home/pi/movies/loading.txt");
    the_player.Play_List.add_to_list("/home/pi/movies/UBERtandc.txt");
    the_player.Play_List.add_to_list("/home/pi/movies/advert.txt");
    the_player.Play_List.add_to_list("/home/pi/movies/loading.txt");
    the_player.Play_List.add_to_list("/home/pi/movies/asciimation.txt");
    return true;
  }
  */

  bool load_reel(fstream &fsPlayer, string filename)
  // Loads next film into the player. 
  //  This is basiclly a pass through routine to keep calls 
  //  in the main console area.
  // Returns false if anything goes wrong.
  {
    bool success = false;
    success = the_player.load_reel(fsPlayer, filename);
    return success;
  }

  bool play_next_movie(fstream &fsPlayer)
  // Starts playing the next movie in the play list by 
  //  advanceing the playlist and loading the next movie 
  //  file into the file stream.
  // If the file in the playlist returns false, it is removed 
  //  from the playlist and next movie is played.
  // If playlist is empty then the player is disabled.
  // Returns false if anything goes wrong.
  {
    bool success = false;

    if (the_player.Play_List.size() <= 0)
    {
      the_player.booDisable = true;
      the_player.booPlay = false;
      success = false;
    }
    else
    {
      success = load_reel(fsPlayer, the_player.Play_List.get_next_movie());
      if (success == true)
      {
        the_player.booDisable = false;
        the_player.booPlay = true;
      }
      else
      {
        the_player.Play_List.remove_current_movie();
        play_next_movie(fsPlayer);
      }
    }
    return success;
  }

  bool print_movie_frame(fstream &fsPlayer, unsigned long tmeCurrent_Time_millis)
  // This is the primary routine of the player. 
  //  If everything is ok, and the time is at or past the next movie scheduled
  //  display time, then the next frame is loaded into the frame buffer and 
  //  passed over to the screen routine to be displayed, however it likes.
  // If the current movie has reached its end, then the next one in the playlist 
  //  is loaded.
  // Returns false if anything goes wrong.
  {
    if ((the_player.booPlay == true) && (the_player.booDisable == false))
    {
      if (the_player.ftqFilm.booEOF == true)
      {
        play_next_movie(fsPlayer);
      }

      if (the_player.booSucess == true)
      {
        if (ScrStat.Window_Player == true)
        {
          if(tmeCurrent_Time_millis >= the_player.tmeNEXT_FRAME_DRAW_TIME)
          {
            the_player.get_frame(fsPlayer, tmeCurrent_Time_millis);
            Screen.window_player_draw_frame(the_player.qFrame);
          }
        }
      }
      return the_player.booSucess;
    }
    else
    {
      return true;
    }
  }

  void set_screen(system_data &sdSysData)
  // Before drawing and initializing the screen, set the display to how it should look. 
  {
    ScrStat.Window_Status_On();
    ScrStat.Window_Buttons_On();
    ScrStat.Window_Debug_Off();
    ScrStat.Window_Console_On();
    ScrStat.Window_CPicker_Off();
    ScrStat.Window_Tabs_On();

    Screen.set(sdSysData, ScrStat);
  }

  void printi(string in)
  // Print to console immediately to console without waiting for refresh.
  {
    // console line time is inaccurate.  Will only refect previous console update time
    //  and not actual time printed.  Current time is not global.  This is a filler.

    if (ScrStat.Window_Console == true)
    {
      clou.add(Update_Time,in);         // Add line to console line list.      
      Screen.printout(clou, ScrStat);  // Immediately display the line onto the screen.
    }
    else
    {
      printwait(in);
    }
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
      key = wgetch(stdscr);   // Read key

      char buffer[512];
      size_t max_size = sizeof(buffer);
    
    while (key != ERR)        // Continuous loop untill all keys are read
    {

      // Check for Mouse Events.
      if (key == KEY_MOUSE)
      {
        MEVENT event;
        if (getmouse(&event) ==OK)
        {
          mouse.store(event.x, event.y, event.bstate);
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

      key = wgetch(stdscr);   // Read the key again to repeat if not empty.

      char buffer[512];
      size_t max_size = sizeof(buffer);
    
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

      // -----------------------------------
      // Check to see if any main buttons are clicked.
      if (Screen.bzButtons.check_click(mouse.x_clicked(),mouse.y_clicked()) == true)
      // Check for any clicked buttons or if it was just empty space.
      //  If anything was clicked, the list in the bzButtons will be updated.
      {
        // Go through all the buttons in the screen and update their values, 
        //  this will also update their values in the bzButtons list.
        //Screen.update_buttons();

        // If a Main Button is clicked, dont need the Color Picker
        //  Close it if it was opened.
        ScrStat.Window_CPicker_Off();

        // Next time the screen is refreshed, redraw the button.
        //ScrStat.Buttons_Refresh = true;

        // Get name and value of button in list that was clicked, then set it 
        //  as unclicked.
        string name = "";
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
          if(sdSysData.booOverheadRunning == false)
          {
            Screen.buttons_menu_overhead_color(sdSysData);
            keywatch.cmdIn('o');
          }
          else
          {
            keywatch.cmdInString("o`");
          }
        }

        else if(name.compare("EXIT") == 0)
        // Exit RasFLED
        {
          keywatch.cmdInString("X");
        }

        else if(name.compare("SHUTDOWN_NOW") == 0)
        // Shutdown the entire system
        {
          keywatch.cmdInString(" comshutd");
        }

        else if (name.compare("DAYNIGHT") == 0)
        // Day Night Mode
        {
          if (sdSysData.booDay_On == false)
          {
            keywatch.cmdInString("dayon");
            Screen.bzButtons.change_label("DAYNIGHT", "%Day%Mode");
          }
          else
          {
            keywatch.cmdInString("dayoff");
            Screen.bzButtons.change_label("DAYNIGHT", "%Night%Mode");
          }
        }

        else if(name.compare("TIMER") == 0)
        // Start / Stop Timer
        if (sdSysData.cdTIMER.is_active() == false)
        {
          keywatch.cmdInString("  ");
        }
        else
        {
          keywatch.cmdInString(" `");
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
        // Start Hazard Lights or turn off.
        {
          if (sdSysData.booHazardRunning == false)
          {
            keywatch.cmdInString("hh");
          }
          else
          {
            keywatch.cmdInString("h`");
          }
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
        //Screen.update_buttons();

      }

      // Check to see if any Tab buttons are clicked.
      if (Screen.bzTabs.check_click(mouse.x_clicked(),mouse.y_clicked()) == true)
      // Check for any clicked buttons or if it was just empty space.
      //  If anything was clicked, the list in the bzTabs will be updated.
      {

        // Go through all the buttons in the screen and update their values, 
        //  this will also update their values in the bzButtons list.
        //Screen.update_tabs();

        string name = "";
        int value = 0;
        name = Screen.bzTabs.get_clicked_name();
        value = Screen.bzTabs.get_clicked_value(name);

        /* DEBUG STUFFS
        printi("");
        for(int pos=0; pos < Screen.bzTabs.size(); pos++)
        {
          printi(Screen.bzTabs.name(pos));
          printi(to_string(Screen.bzTabs.value(pos)));
        }
        printi("");
        */

        if(name.compare("TABCONSOLE") == 0)
        // Turn on Tab
        {
          printi("Tab Console");
          ScrStat.Window_Console_On();
          ScrStat.Window_Player_Off();
          the_player.pause();
        }

        if(name.compare("TABBLANKSCREEN") == 0)
        // Turn on Tab
        {
          printi("Tab Blank Screen");
          ScrStat.Window_Console_Off();
          ScrStat.Window_Player_Off();
          the_player.pause();
        }

        if(name.compare("TABPLAYER") == 0)
        // Turn on Tab
        {
          printi("Tab Player");
          ScrStat.Window_Console_Off();
          ScrStat.Window_Player_On();
          the_player.play();
        }

        // Update changes to buttons
        //Screen.update_tabs();


        /* DEBUG STUFFS
        printi("");
        for(int pos=0; pos < Screen.bzTabs.size(); pos++)
        {
          printi(Screen.bzTabs.name(pos));
          printi(to_string(Screen.bzTabs.value(pos)));
        }
        printi("");
        */

      }

      // -----------------------------------
      // Check to see if any color picker buttons are clicked.
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
// -------------------------------------------------------------------------------------



#endif