// ***************************************************************************************
// *
// *    Core       | Everything within this document is proprietary to Core Dynamics.
// *    Dynamics   | Any unauthorized duplication will be subject to prosecution.
// *
// *    Department : (R+D)^2                        Name: consoleanddata.cpp
// *       Sub Dept: Programming
// *    Location ID: 856-45B
// *                                                      (c) 2856 - 2858 Core Dynamics
// ***************************************************************************************

#ifndef CONSOLEANDDATA_CPP
#define CONSOLEANDDATA_CPP

#include "consoleanddata.h"

using namespace std;

// ***************************************************************************************
// STRUCTURES AND CLASSES
// ***************************************************************************************

// -------------------------------------------------------------------------------------
// All variables to keep track of the interface and program status.  All psssive.

// -------------------------------------------------------------------------------------
// NCurses Console.  Responsible for all screen and user interfaces.
void Console::update_ADS_B_gadgets(unsigned long &tmeCurrentMillis, system_data &sdSysData)
{
  if(sdSysData.AIRCRAFT_COORD.DATA.CHANGED == true || Screen.ADSB_Grid.PROP.NEEDS_REFRESH_DATA == true)
  {
    Screen.ADSB_Grid.update(sdSysData, tmeCurrentMillis);
  }
}

void Console::update_automobile_gadgets(unsigned long &tmeCurrentMillis, system_data &sdSysData)
{
  sdSysData.CAR_INFO.translate(tmeCurrentMillis);

  if(sdSysData.CAR_INFO.CHANGED == true)
  {  
    Screen.AUTOMOBILE_OVERVIEW_PANEL.update(sdSysData, tmeCurrentMillis);
    Screen.AUTOMOBILE_PANEL.update(sdSysData, tmeCurrentMillis);
    sdSysData.CAR_INFO.CHANGED = false;
  }
}

bool Console::load_reel(fstream &fsPlayer, string filename)
// Loads next film into the player. 
//  This is basiclly a pass through routine to keep calls 
//  in the main console area.
// Returns false if anything goes wrong.
{
  bool success = false;
  success = the_player.load_reel(fsPlayer, filename);
  
  if (success == true)
  {
    printwait("Film Loaded: " + filename);
  }
  else
  {
    printwait("FAILED Film Load: " + filename);
  }
  return success;
}

bool Console::play_next_movie(fstream &fsPlayer)
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

bool Console::print_movie_frame(fstream &fsPlayer)
// This is the primary routine of the player. 
//  If everything is ok, and the time is at or past the next movie scheduled
//  display time, then the next frame is loaded into the frame buffer and 
//  passed over to the screen routine to be displayed, however it likes.
// If the current movie has reached its end, then the next one in the playlist 
//  is loaded.
// Returns false if anything goes wrong.
{
  if (the_player.booSkip == true)
  // I dont want this here, quick and dirty.
  {
    the_player.booSkip = false;
    the_player.ftqFilm.close_the_file(fsPlayer);
  }

  if (the_player.ftqFilm.booEOF == true)
  {
    Screen.window_player_clear();
    play_next_movie(fsPlayer);
  }

  if (the_player.booSucess == true)
  {
    if (ScrStat.Window_Player.value() == true)
    {
      if (the_player.get_frame(fsPlayer) == false)
      {
        printwait("Dropped Frame");
      }
      else
      {
        Screen.window_player_draw_frame(the_player.qFrame);
      }
    }
  }

  return the_player.booSucess;
}

void Console::set_screen(system_data &sdSysData)
// Before drawing and initializing the screen, set the display to how it should look. 
{
  ScrStat.Window_CYBR.on(ScrStat.Needs_Refresh);
  ScrStat.Window_Status.on(ScrStat.Needs_Refresh);
  ScrStat.Window_Buttons.on(ScrStat.Needs_Refresh);
  ScrStat.Window_Debug.off(ScrStat.Needs_Refresh);
  ScrStat.Window_Console.on(ScrStat.Needs_Refresh);
  ScrStat.Window_CPicker.off(ScrStat.Needs_Refresh);
  ScrStat.Window_Tabs.on(ScrStat.Needs_Refresh);

  Screen.set(sdSysData, ScrStat);
}

void Console::printi(string in)
// Print to console immediately to console without waiting for refresh.
{
  // console line time is inaccurate.  Will only refect previous console update time
  //  and not actual time printed.  Current time is not global.  This is a filler.

  if (ScrStat.Window_Console.value() == true)
  {       
    Screen.tbConsole.add_line(Update_Time, in); // Add line to console line list. 
    Screen.printout(ScrStat);  // Immediately display the line onto the screen.
  }
  else
  {
    printwait(in);
  }
}

void Console::printwait(string in)
// Print out a line to console during next refresh.
{
  // console line time is inaccurate.  Will only refect previous console update time
  //  and not actual time printed.  Current time is not global.  This is a filler.
  Screen.tbConsole.add_line(Update_Time, in); // Add line to console line list.
}

void Console::readkeyboardinput2()
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

void Console::processkeyboadinput(system_data &sdSysData)
// Run through this routine before the console is refreshed.
{
  // Check for screen resize.
  if (keywatch.get(KEYRESIZE) == 1)
  {
    //printwait("RESIZING SCREEN");
    keywatch.Chars[KEYRESIZE].VALUE = 0;
    ScrStat.Needs_Refresh = true;

    Screen.reset(sdSysData, ScrStat);
  }
}

void Console::tab_open_console(system_data &sdSysData)
{
  printi("Tab Console");
  ScrStat.Window_Console.on(ScrStat.Needs_Refresh);        // Console
  ScrStat.Window_Player.off(ScrStat.Needs_Refresh);        // Player

  ScrStat.Window_Automobile_Screen.off(ScrStat.Needs_Refresh);  // Automobile

  ScrStat.Window_ADS_B_Buttons.off(ScrStat.Needs_Refresh);  // ADS_B
  ScrStat.Window_ADS_B_Screen.off(ScrStat.Needs_Refresh);

  ScrStat.Window_Log_Screen.off(ScrStat.Needs_Refresh);    // Log

  ScrStat.Window_Alerts_Screen.off(ScrStat.Needs_Refresh);   // Alerts

  the_player.pause();
}

void Console::tab_open_player(system_data &sdSysData)
{
  printi("Tab Player");
  ScrStat.Window_Console.off(ScrStat.Needs_Refresh);       // Console
  ScrStat.Window_Player.on(ScrStat.Needs_Refresh);         // Player

  ScrStat.Window_Automobile_Screen.off(ScrStat.Needs_Refresh);  // Automobile

  ScrStat.Window_ADS_B_Buttons.off(ScrStat.Needs_Refresh);  // ADS_B
  ScrStat.Window_ADS_B_Screen.off(ScrStat.Needs_Refresh);

  ScrStat.Window_Log_Screen.off(ScrStat.Needs_Refresh);    // Log

  ScrStat.Window_Alerts_Screen.off(ScrStat.Needs_Refresh);   // Alerts

  the_player.play();
}

void Console::tab_open_automobile(system_data &sdSysData)
{
  printi("Tab Automobile");
  ScrStat.Window_Console.off(ScrStat.Needs_Refresh);       // Console
  ScrStat.Window_Player.off(ScrStat.Needs_Refresh);        // Player
  
  ScrStat.Window_Automobile_Screen.on(ScrStat.Needs_Refresh);  // Automobile

  ScrStat.Window_ADS_B_Buttons.off(ScrStat.Needs_Refresh);  // ADS_B
  ScrStat.Window_ADS_B_Screen.off(ScrStat.Needs_Refresh);

  ScrStat.Window_Log_Screen.off(ScrStat.Needs_Refresh);    // Log

  ScrStat.Window_Alerts_Screen.off(ScrStat.Needs_Refresh);   // Alerts

  the_player.pause();
}

void Console::tab_open_radio(system_data &sdSysData)
{
  printi("Tab Radio");
  ScrStat.Window_Console.off(ScrStat.Needs_Refresh);       // Console
  ScrStat.Window_Player.off(ScrStat.Needs_Refresh);        // Player
  
  ScrStat.Window_Automobile_Screen.off(ScrStat.Needs_Refresh);  // Automobile

  ScrStat.Window_ADS_B_Buttons.off(ScrStat.Needs_Refresh);  // ADS_B
  ScrStat.Window_ADS_B_Screen.off(ScrStat.Needs_Refresh);

  ScrStat.Window_Log_Screen.off(ScrStat.Needs_Refresh);    // Log

  ScrStat.Window_Alerts_Screen.off(ScrStat.Needs_Refresh);   // Alerts

  the_player.pause();
}

void Console::tab_open_many_radio(system_data &sdSysData)
{
  printi("Tab Radio Multi");
  ScrStat.Window_Console.off(ScrStat.Needs_Refresh);       // Console
  ScrStat.Window_Player.off(ScrStat.Needs_Refresh);        // Player

  ScrStat.Window_Automobile_Screen.off(ScrStat.Needs_Refresh);  // Automobile

  ScrStat.Window_ADS_B_Buttons.off(ScrStat.Needs_Refresh);  // ADS_B
  ScrStat.Window_ADS_B_Screen.off(ScrStat.Needs_Refresh);

  ScrStat.Window_Log_Screen.off(ScrStat.Needs_Refresh);    // Log

  ScrStat.Window_Alerts_Screen.off(ScrStat.Needs_Refresh);   // Alerts

  the_player.pause();
}

void Console::tab_open_ads_b_screen(system_data &sdSysData)
{
  printi("Tab ADS_B");
  ScrStat.Window_Console.off(ScrStat.Needs_Refresh);       // Console
  ScrStat.Window_Player.off(ScrStat.Needs_Refresh);        // Player

  ScrStat.Window_Automobile_Screen.off(ScrStat.Needs_Refresh);  // Automobile

  ScrStat.Window_ADS_B_Buttons.on(ScrStat.Needs_Refresh);   // ADS_B
  ScrStat.Window_ADS_B_Screen.on(ScrStat.Needs_Refresh);

  ScrStat.Window_Log_Screen.off(ScrStat.Needs_Refresh);    // Log

  ScrStat.Window_Alerts_Screen.off(ScrStat.Needs_Refresh);   // Alerts

  the_player.pause();
}

void Console::tab_open_log_screen(system_data &sdSysData)
{
  printi("Tab Log");
  ScrStat.Window_Console.off(ScrStat.Needs_Refresh);       // Console
  ScrStat.Window_Player.off(ScrStat.Needs_Refresh);        // Player

  ScrStat.Window_Automobile_Screen.off(ScrStat.Needs_Refresh);  // Automobile

  ScrStat.Window_ADS_B_Buttons.off(ScrStat.Needs_Refresh);  // ADS_B
  ScrStat.Window_ADS_B_Screen.off(ScrStat.Needs_Refresh);

  ScrStat.Window_Log_Screen.on(ScrStat.Needs_Refresh);     // Log

  ScrStat.Window_Alerts_Screen.off(ScrStat.Needs_Refresh);   // Alerts

  the_player.pause();
}

void Console::tab_open_alerts(system_data &sdSysData)
{
  printi("Tab Alerts");
  ScrStat.Window_Console.off(ScrStat.Needs_Refresh);       // Console
  ScrStat.Window_Player.off(ScrStat.Needs_Refresh);        // Player

  ScrStat.Window_Automobile_Screen.off(ScrStat.Needs_Refresh);  // Automobile

  ScrStat.Window_ADS_B_Buttons.off(ScrStat.Needs_Refresh);  // ADS_B
  ScrStat.Window_ADS_B_Screen.off(ScrStat.Needs_Refresh);

  ScrStat.Window_Log_Screen.off(ScrStat.Needs_Refresh);     // Log

  ScrStat.Window_Alerts_Screen.on(ScrStat.Needs_Refresh);   // Alerts

  the_player.pause();
}

void Console::tab_handler(string Button_Name, system_data &sdSysData)
{
  if (Button_Name == "TABCONSOLE")
  // Turn on Tab
  {
    tab_open_console(sdSysData);
  }

  if (Button_Name == "TABPLAYER")
  // Turn on Tab
  {
    tab_open_player(sdSysData);
  }

  if (Button_Name == "TAB_AUTOMOBILE")
  // Turn on Tab
  {
    tab_open_automobile(sdSysData);
  }

  if (Button_Name == "TABRADIO")
  // Turn on Tab
  {
    tab_open_radio(sdSysData);
  }

  if (Button_Name == "TAB_ADS_B_SCREEN")
  // Turn on Tab
  {
    tab_open_ads_b_screen(sdSysData);
  }

  if (Button_Name == "TAB_LOG_SCREEN")
  // Turn on Tab
  {
    tab_open_log_screen(sdSysData);
  }

  if (Button_Name == "TAB_ALERTS_SCREEN")
  // Turn on Tab
  {
    tab_open_alerts(sdSysData);
  }
}

void Console::processmouseinput(system_data &sdSysData)
{
  if (mouse.Clicked() == true)
  {
    // -----------------------------------
    // Check to see if any main buttons are clicked.
    if (Screen.bzButtons.check_click(mouse.x_clicked(),mouse.y_clicked()) == true)
    // Check for any clicked buttons or if it was just empty space.
    //  If anything was clicked, the list in the bzButtons will be updated.
    {
      // If a Main Button is clicked, dont need the Color Picker
      //  Close it if it was opened.
      ScrStat.Window_CPicker.off(ScrStat.Needs_Refresh);

      // Get name and value of button in list that was clicked, then set it 
      //  as unclicked.
      string name = "";
      int value = 0;
      name = Screen.bzButtons.get_clicked_name();
      value = Screen.bzButtons.get_clicked_value(name);
      
      if (name == "MENUCONTROL")
      // Load System Buttons
      {
        Screen.buttons_menu_control(sdSysData);
      }

      if (name == "MENUSYSTEM")
      // Load System Buttons
      {
        Screen.buttons_menu_system(sdSysData);
      }
      
      else if (name == "MENUHOME")
      // Load Home Buttons
      {
        Screen.buttons_menu_home(sdSysData);
      }

      else if (name == "MENUOVERHEAD")
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

      else if(name == "EXIT")
      // Exit RasFLED
      {
        keywatch.cmdInString("X");
      }

      else if(name == "SHUTDOWN_NOW")
      // Shutdown the entire system
      {
        keywatch.cmdInString(" comshutd");
      }

      else if(name == "REBOOT")
      // Shutdown the entire system
      {
        keywatch.cmdInString(" reboot");
      }

      else if (name == "DAYNIGHT")
      // Day Night Mode
      {
        if (sdSysData.Day_On_With_Override.value() == false)
        {
          keywatch.cmdInString("dayon");
          Screen.bzButtons.set_label("DAYNIGHT", "\nDay\nMode");
          Screen.buttons_menu_home(sdSysData);
        }
        else
        {
          keywatch.cmdInString("dayoff");
          Screen.bzButtons.set_label("DAYNIGHT", "\nNight\nMode");
          Screen.buttons_menu_home(sdSysData);
        }
      }

      else if(name == "LIGHTSOFF")
      // Turn Lights On or Off
      {
        if(sdSysData.Lights_On.value() == true)
        {
          keywatch.cmdInString(" lightsoff");
        }
        else
        {
          keywatch.cmdInString(" lightson");
        }
      }

      else if(name == "TIMER")
      // Start / Stop Timer
      if (sdSysData.cdTIMER.is_active() == false)
      {
        keywatch.cmdInString("  ");
      }
      else
      {
        keywatch.cmdInString(" `");
      }

      else if(name == "OVERHEAD")
      // Start Overhead Lights
      {
        keywatch.cmdInString("oo");
        Screen.buttons_menu_home(sdSysData);
      }

      else if(name == "FLASH")
      // Flash Lights
      {
        keywatch.cmdInString("ff");
      }

      else if(name == "CLEARANIMS")
      // Clear Most Animations
      {
        keywatch.cmdInString("``");
        Screen.buttons_menu_home(sdSysData);
      }

      else if(name == "HAZARD")
      // Start Hazard Lights or turn off.
      {
        if (sdSysData.booHazardRunning == false)
        {
          keywatch.cmdInString("hh");
        }
        else
        {
          keywatch.cmdInString("h`");
          Screen.buttons_menu_home(sdSysData);
        }
      }

      else if(name == "DEBUG")
      // Start Hazard Lights
      {
        keywatch.cmdInString("/");
        Screen.buttons_menu_home(sdSysData);
      }

      else if(name == "RUNNINGCOLOR")
      // Start Hazard Lights
      {
        keywatch.cmdIn('r');
        ScrStat.Window_CPicker.on(ScrStat.Needs_Refresh);
      }

      else if(name == "CHOSECOLOR")
      {
        ScrStat.Window_CPicker.on(ScrStat.Needs_Refresh);
      }
    }

    // Check to see if any Tab buttons are clicked.
    if (Screen.bzTabs.check_click(mouse.x_clicked(),mouse.y_clicked()) == true)
    // Check for any clicked buttons or if it was just empty space.
    //  If anything was clicked, the list in the bzTabs will be updated.
    {
      tab_handler(Screen.bzTabs.get_clicked_name(), sdSysData);
    }

    // -----------------------------------
    // Check to see if any color picker buttons are clicked.
    if (Screen.bzCPicker.check_click(mouse.x_clicked(),mouse.y_clicked()) == true)
    // Check for any clicked buttons or if it was just empty space.
    //  If anything was clicked, the list in the bzCPicker will be updated.
    {
      string name = Screen.bzCPicker.get_clicked_name();
    
      //Color Picker Window
      if(name == "EXITCOLOR")
      // Start Hazard Lights
      {
        ScrStat.Window_CPicker.off(ScrStat.Needs_Refresh);
      }
      else if(name == "RED")
      // Start Hazard Lights
      {
        keywatch.cmdIn('r');
        ScrStat.Window_CPicker.off(ScrStat.Needs_Refresh);
        Screen.buttons_menu_home(sdSysData);
      }
      else if(name == "GREEN")
      // Start Hazard Lights
      {
        keywatch.cmdIn('g');
        ScrStat.Window_CPicker.off(ScrStat.Needs_Refresh);
        Screen.buttons_menu_home(sdSysData);
      }
      else if(name == "BLUE")
      // Start Hazard Lights
      {
        keywatch.cmdIn('b');
        ScrStat.Window_CPicker.off(ScrStat.Needs_Refresh);
        Screen.buttons_menu_home(sdSysData);
      }
      else if(name == "PURPLE")
      // Start Hazard Lights
      {
        keywatch.cmdIn('u');
        ScrStat.Window_CPicker.off(ScrStat.Needs_Refresh);
        Screen.buttons_menu_home(sdSysData);
      }
      else if(name == "YELLOW")
      // Start Hazard Lights
      {
        keywatch.cmdIn('y');
        ScrStat.Window_CPicker.off(ScrStat.Needs_Refresh);
        Screen.buttons_menu_home(sdSysData);
      }
      else if(name == "CYAN")
      // Start Hazard Lights
      {
        keywatch.cmdIn('c');
        ScrStat.Window_CPicker.off(ScrStat.Needs_Refresh);
        Screen.buttons_menu_home(sdSysData);
      }
      else if(name == "ORANGE")
      // Start Hazard Lights
      {
        keywatch.cmdIn('n');
        ScrStat.Window_CPicker.off(ScrStat.Needs_Refresh);
        Screen.buttons_menu_home(sdSysData);
      }
      else if(name == "WHITE")
      // Start Hazard Lights
      {
        keywatch.cmdIn('w');
        ScrStat.Window_CPicker.off(ScrStat.Needs_Refresh);
        Screen.buttons_menu_home(sdSysData);
      }
    }

    // -----------------------------------
    if(ScrStat.Window_ADS_B_Screen.value() == true)
    {
      if (Screen.bzADS_B.check_click(mouse.x_clicked(),mouse.y_clicked()) == true)
      // Check for any clicked buttons or if it was just empty space.
      //  If anything was clicked, the list in the bzzADS_B will be updated.
      {
        string name = Screen.bzADS_B.get_clicked_name();
      
        if(name == "ADS_BON")
        // Turn On ADS_B Receiver
        {
          if(sdSysData.AIRCRAFT_COORD.is_active() == false)
          {
            keywatch.cmdInString(" absbon");
          }
          else
          {
            keywatch.cmdInString(" absboff");
          }
        }
        else if(name == "ADS_B_SNAPSHOT")
        // Turn Off ADS_B Receiver
        {
          keywatch.cmdInString(" adsbsnap");
        }
      }
    }
  }
}  

void Console::update_displayed_time(unsigned long &time)
// Set the consoles last redraw time, a now should be passed in.
{
  Update_Time = time;
}

void Console::output(system_data &sdSysData)
// Screen Update
{
  // Check screen redraw variables.
  //  Set Debug
  if (keywatch.get(KEYDEBUG) == 1)
  {
    ScrStat.Window_Debug.on(ScrStat.Needs_Refresh);
    //ScrStat.Needs_Refresh = true;
  }
  else 
  {
    ScrStat.Window_Debug.off(ScrStat.Needs_Refresh);
    //ScrStat.Needs_Refresh = true;
  }

  // Screen Update
  Screen.output(sdSysData, keywatch, ScrStat, mouse);
  
  /*  Debug routine to verify console not in redisplay loop cycle.
  if(clou.avail()==true)
  {
    printi("Printed not cleared.");
  }
  */
}

void Console::display(fstream &fsPlayer, system_data &sdSystem, unsigned long tmeCurrentMillis)
{
  // Designed for keeping times of things printed to the console.  
  //  NEEDS TO BE REMOVED IN LUE OF A BETTER ACURATE SOLUTION.
  //  For future log file.
  update_displayed_time(tmeCurrentMillis);
  
  // Dont refresh the Console (output) every time a new frame is drawn with the 
  //  movie player. 
  if (Console_Display.is_ready(tmeCurrentMillis) == true)
  {
    if (sdSystem.ALERTS.triggered() == true)
    {
      tab_open_alerts(sdSystem);
      printwait("ALERT");
    }
    else if (sdSystem.ALERTS.alert_cleared() == true)
    {
      tab_handler(Screen.bzTabs.get_name_of_button_with_value(1), sdSystem);
      printwait("ALERT CLEARED");
    }

    // Update display screen.
    output(sdSystem);

    // Reset mins and max time values displayed in the console.
    //  Currently, not being stored, calculated or displayed.
    sdSystem.refresh();
  }
  
  // Player
  if(the_player.is_ready_to_draw_frame(tmeCurrentMillis) == true)
  {
    // Load next movie frame and send it to the screen.
    print_movie_frame(fsPlayer);
  }
}




#endif