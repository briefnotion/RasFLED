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

#include "consoleanddata.h"

using namespace std;

// ***************************************************************************************
// STRUCTURES AND CLASSES
// ***************************************************************************************

// -------------------------------------------------------------------------------------
// All variables to keep track of the interface and program status.  All psssive.

// -------------------------------------------------------------------------------------
// NCurses Console.  Responsible for all screen and user interfaces.

void Console::update_freqency_gadgets_QF(system_data &sdSysData, int pos, Radio_Channel &Gad_Freq)
{ 
  if (sdSysData.RADIO_COORD.CHANNELS[pos].PROP.CHANGED == true)
  // Update channel property changes from coordinator to gadget.
  {
    Gad_Freq.PROP.SKIP = sdSysData.RADIO_COORD.CHANNELS[pos].PROP.SKIP;
    Gad_Freq.PROP.HELD = sdSysData.RADIO_COORD.CHANNELS[pos].PROP.HELD;
    Gad_Freq.PROP.CHANGED = true;
  }

  if (sdSysData.RADIO_COORD.CHANNELS[pos].FREQUENCY.CHANGED == true)
  // Update channel frequency changes from coordinator to gadget.
  {
    Gad_Freq.update_value(sdSysData.RADIO_COORD.CHANNELS[pos], sdSysData.tmeCURRENT_FRAME_TIME);
  }
}

void Console::update_freqency_gadgets(system_data &sdSysData)
// Update all radio gadgets with new frequency information.
{
  //if (ScrStat.Window_Radio == true)
  {
    // Update Radio_Channels with new info
    //for(int pos = 0; pos < Screen.Radio_Channel_Count; pos++)
    for(int pos = 0; pos < sdSysData.RADIO_COORD.size(); pos++)
    {
      if(pos < Screen.Radio_Channels.size())
      {
        update_freqency_gadgets_QF(sdSysData, pos, Screen.Radio_Channels[pos]);
      }
      if(pos < Screen.Many_Radio_Channels.size())
      {
        update_freqency_gadgets_QF(sdSysData, pos, Screen.Many_Radio_Channels[pos]);
      }
      sdSysData.RADIO_COORD.CHANNELS[pos].FREQUENCY.CHANGED = false;
      sdSysData.RADIO_COORD.CHANNELS[pos].PROP.CHANGED = false;
    }
  }

  /*
  //if (ScrStat.Window_Many_Radio == true)
  {
    // Update Many_Radio_Channels with new info
    for(int pos = 0; pos < Screen.Many_Radio_Channel_Count; pos++)
    {
      update_freqency_gadgets_QF(sdSysData, pos, Screen.Many_Radio_Channels[pos]);
    }
  }
  */
}

void Console::update_ADS_B_gadgets(unsigned long &tmeCurrentMillis, system_data &sdSysData)
{
  if(sdSysData.AIRCRAFT_COORD.DATA.CHANGED == true)
  {
    Screen.tbads_b_Data.update(sdSysData);
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
    if (ScrStat.Window_Player == true)
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
  ScrStat.Window_Status_On();
  ScrStat.Window_Buttons_On();
  ScrStat.Window_Debug_Off();
  ScrStat.Window_Console_On();
  ScrStat.Window_CPicker_Off();
  ScrStat.Window_Tabs_On();

  Screen.set(sdSysData, ScrStat);
}

void Console::printi(string in)
// Print to console immediately to console without waiting for refresh.
{
  // console line time is inaccurate.  Will only refect previous console update time
  //  and not actual time printed.  Current time is not global.  This is a filler.

  if (ScrStat.Window_Console == true)
  {       
    Screen.tbConsole.add_line(Update_Time, in); // Add line to console line list. 
    Screen.printout(ScrStat);  // Immediately display the line onto the screen.
  }
  else
  {
    printwait(in);
  }
}

void Console::deb(string strPrintI)
{
  printi("DEBUG: " + strPrintI);
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

void Console::processkeyboadinput()
// Run through this routine before the console is refreshed.
{
  // Check for screen resize.
  if (keywatch.get(KEYRESIZE) == 1)
  {
    //printwait("RESIZING SCREEN");
    keywatch.Chars[KEYRESIZE].VALUE = 0;
    ScrStat.Needs_Refresh = true;

    Screen.reset(ScrStat);
  }
}

void Console::processmouseinput(system_data &sdSysData)
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

      else if(name.compare("LIGHTSOFF") == 0)
      // Turn Lights On or Off
      {
        if(sdSysData.Lights_On == true)
        {
          keywatch.cmdInString(" lightsoff");
        }
        else
        {
          keywatch.cmdInString(" lightson");
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
        ScrStat.Window_Console_On();        // Console
        ScrStat.Window_Player_Off();        // Player

        ScrStat.Window_Radio_Buttons_Off();
        ScrStat.Window_Radio_Off();
        ScrStat.Window_Many_Radio_Off();

        ScrStat.Window_ADS_B_Buttons_Off();  // ADS_B
        ScrStat.Window_ADS_B_Screen_Off();

        ScrStat.Window_Log_Screen_Off();    // Log
        the_player.pause();
        sdSysData.RADIO_COORD.pause();
      }

      if(name.compare("TABPLAYER") == 0)
      // Turn on Tab
      {
        printi("Tab Player");
        ScrStat.Window_Console_Off();       // Console
        ScrStat.Window_Player_On();         // Player

        ScrStat.Window_Radio_Buttons_Off(); // Radio
        ScrStat.Window_Radio_Off();
        ScrStat.Window_Many_Radio_Off();

        ScrStat.Window_ADS_B_Buttons_Off();  // ADS_B
        ScrStat.Window_ADS_B_Screen_Off();

        ScrStat.Window_Log_Screen_Off();    // Log
        the_player.play();
        sdSysData.RADIO_COORD.pause();
      }

      if(name.compare("TABRADIO") == 0)
      // Turn on Tab
      {
        printi("Tab Radio");
        ScrStat.Window_Console_Off();       // Console
        ScrStat.Window_Player_Off();        // Player
        
        ScrStat.Window_Radio_Buttons_On();  // Radio
        ScrStat.Window_Radio_On();
        ScrStat.Window_Many_Radio_Off();

        ScrStat.Window_ADS_B_Buttons_Off();  // ADS_B
        ScrStat.Window_ADS_B_Screen_Off();

        ScrStat.Window_Log_Screen_Off();    // Log
        the_player.pause();
        sdSysData.RADIO_COORD.play();
      }

      if(name.compare("TABMANYRADIO") == 0)
      // Turn on Tab
      {
        printi("Tab Radio Multi");
        ScrStat.Window_Console_Off();       // Console
        ScrStat.Window_Player_Off();        // Player

        ScrStat.Window_Radio_Buttons_On();  // Radio
        ScrStat.Window_Radio_Off();
        ScrStat.Window_Many_Radio_On();

        ScrStat.Window_ADS_B_Buttons_Off();  // ADS_B
        ScrStat.Window_ADS_B_Screen_Off();

        ScrStat.Window_Log_Screen_Off();    // Log
        the_player.pause();
        sdSysData.RADIO_COORD.play();
      }

      if(name.compare("TAB_ADS_B_SCREEN") == 0)
      // Turn on Tab
      {
        printi("Tab ADS_B");
        ScrStat.Window_Console_Off();       // Console
        ScrStat.Window_Player_Off();        // Player

        ScrStat.Window_Radio_Buttons_Off(); // Radio
        ScrStat.Window_Radio_Off();
        ScrStat.Window_Many_Radio_Off();

        ScrStat.Window_ADS_B_Buttons_On();   // ADS_B
        ScrStat.Window_ADS_B_Screen_On();

        ScrStat.Window_Log_Screen_Off();    // Log
        the_player.pause();
        sdSysData.RADIO_COORD.play();
      }

      if(name.compare("TAB_LOG_SCREEN") == 0)
      // Turn on Tab
      {
        printi("Tab Radio Multi");
        ScrStat.Window_Console_Off();       // Console
        ScrStat.Window_Player_Off();        // Player

        ScrStat.Window_Radio_Buttons_Off(); // Radio
        ScrStat.Window_Radio_Off();
        ScrStat.Window_Many_Radio_Off();

        ScrStat.Window_ADS_B_Buttons_Off();  // ADS_B
        ScrStat.Window_ADS_B_Screen_Off();

        ScrStat.Window_Log_Screen_On();     // Log
        the_player.pause();
        sdSysData.RADIO_COORD.play();
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
    //  If anything was clicked, the list in the bzCPicker will be updated.
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

    // -----------------------------------
    if(ScrStat.Window_Radio == true || ScrStat.Window_Many_Radio == true)
    {
      if (Screen.bzRadio.check_click(mouse.x_clicked(),mouse.y_clicked()) == true)
      // Check for any clicked buttons or if it was just empty space.
      //  If anything was clicked, the list in the bzRadio will be updated.
      {
        string name = "empty";
        int value = 0;
        name = Screen.bzRadio.get_clicked_name();
        value = Screen.bzRadio.get_clicked_value(name);
      
        //Color Picker Window
        if(name.compare("AIRSTOP") == 0)
        // Turn Off Radio via kill command
        {
          keywatch.cmdInString(" airstop");
        }
        else if(name.compare("LAFS") == 0)
        // Lafayette Scan Script
        {
          keywatch.cmdInString(" lafs");
        }
        else if(name.compare("LAFM") == 0)
        // Lafayette Multi Script
        {
          keywatch.cmdInString(" lafm");
        }
        else if(name.compare("CBS") == 0)
        // CB Scan Script
        {
          keywatch.cmdInString(" cbs");
        }
        else if(name.compare("RADIOOFF") == 0)
        // 
        {
          keywatch.cmdInString(" radoff");
        }
        else if(name.compare("NOAA") == 0)
        // 
        {
          keywatch.cmdInString(" rnoaa");
        }
        else if(name.compare("EMERGENCY") == 0)
        // 
        {
          keywatch.cmdInString(" remergenc");
        }
      }
    }

    // -----------------------------------
    // Check Gadgets for Clicked
    if(ScrStat.Window_Radio == true)
    // Check the Radio_Frequencies Radio_Channel Gadgets
    {
      string name = "empty";
      for(int pos = 0; pos < Screen.Radio_Channel_Count; pos++)
      {
        if(Screen.Radio_Channels[pos].check_click(mouse.x_clicked(),mouse.y_clicked(), name) == true)
        {
          if(name == "HOLD")
          {
            keywatch.cmdInString(" rh" + (linemerge_right_justify(6, "000000", to_string(((int)round(Screen.Radio_Channels[pos].PROP.VALUE.FREQUENCY.FREQUENCY / 1000.0)))))); //Gotta have the .0
          }
          else if(name == "SKIP")
          {
            keywatch.cmdInString(" rs" + (linemerge_right_justify(6, "000000", to_string(((int)round(Screen.Radio_Channels[pos].PROP.VALUE.FREQUENCY.FREQUENCY / 1000.0))))));
          }
          else if(name == "CLEAR")
          {
            keywatch.cmdInString(" rc" + (linemerge_right_justify(6, "000000", to_string(((int)round(Screen.Radio_Channels[pos].PROP.VALUE.FREQUENCY.FREQUENCY / 1000.0))))));
          }
        }
      }
    }

    if(ScrStat.Window_Many_Radio == true)
    // Check the Radio_Frequencies Radio_Channel Gadgets
    {
      string name = "empty";
      for(int pos = 0; pos < Screen.Many_Radio_Channel_Count; pos++)
      {
        if(Screen.Many_Radio_Channels[pos].check_click(mouse.x_clicked(),mouse.y_clicked(), name) == true)
        {
          if(name == "HOLD")
          {
            keywatch.cmdInString(" rh" + (linemerge_right_justify(6, "000000", to_string(((int)round(Screen.Many_Radio_Channels[pos].PROP.VALUE.FREQUENCY.FREQUENCY / 1000.0))))));
          }
          else if(name == "SKIP")
          {
            keywatch.cmdInString(" rs" + (linemerge_right_justify(6, "000000", to_string(((int)round(Screen.Many_Radio_Channels[pos].PROP.VALUE.FREQUENCY.FREQUENCY / 1000.0))))));
          }
          else if(name == "CLEAR")
          {
            keywatch.cmdInString(" rc" + (linemerge_right_justify(6, "000000", to_string(((int)round(Screen.Many_Radio_Channels[pos].PROP.VALUE.FREQUENCY.FREQUENCY / 1000.0))))));
          }
        }
      }
    }

    // -----------------------------------
    if(ScrStat.Window_ADS_B_Screen == true)
    {
      if (Screen.bzADS_B.check_click(mouse.x_clicked(),mouse.y_clicked()) == true)
      // Check for any clicked buttons or if it was just empty space.
      //  If anything was clicked, the list in the bzzADS_B will be updated.
      {
        string name = "empty";
        int value = 0;
        name = Screen.bzADS_B.get_clicked_name();
        value = Screen.bzADS_B.get_clicked_value(name);
      
        if(name.compare("ADS_BON") == 0)
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
        /*
        else if(name.compare("ADS_BOFF") == 0)
        // Turn Off ADS_B Receiver
        {
          keywatch.cmdInString(" absboff");
        }
        */
        else if(name.compare("ADS_B_SNAPSHOT") == 0)
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
    ScrStat.Window_Debug_On();
    //ScrStat.Needs_Refresh = true;
  }
  else 
  {
    ScrStat.Window_Debug_Off();
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