// ***************************************************************************************
// *
// *    Core       | Everything within this document is proprietary to Core Dynamics.
// *    Dynamics   | Any unauthorized duplication will be subject to prosecution.
// *
// *    Department : (R+D)^2                        Name: interface.cpp
// *       Sub Dept: Programming
// *    Location ID: 856-45B
// *                                                      (c) 2856 - 2858 Core Dynamics
// ***************************************************************************************

#ifndef INTERFACE_CPP
#define INTERFACE_CPP

#include "interface.h"

// ***************************************************************************************
// STRUCTURES AND CLASSES
// ***************************************************************************************


// ***************************************************************************************
// FUNCTION AND PROCEDURES
// ***************************************************************************************

void command_desc(Console &cons, string strDescription)
{
  //cons.printwait(linemerge_left_justify("________________________________________________", 
  //                                      "__" + strDescription));
  cons.printwait("  " + strDescription);
}

// -------------------------------------------------------------------------------------
// Console Commands

// -------------------------------------------------------------------------------------
// Procedures related to the Command Line.

// Display the help screen.
void consoleprinthelp(Console &cons)
{
  cons.printwait("");
  cons.printwait("HELP SCREEN ------------");
  cons.printwait("");
  cons.printwait("'X' or 'exit' - Safely exits the RasFLED.");
  cons.printwait("' restart'    - Restart RasFLED.");
  cons.printwait("");
  cons.printwait("'help'    - Prints this help screen.");
  cons.printwait("' events' - Prints all active events.");
  cons.printwait("' config' - Prints some configuration data.");
  cons.printwait("");
  cons.printwait("     hh - Hazard Lights      '  ' - Start Timer");
  cons.printwait("     h` - Hazard Lights Off  ' '' - End Timer");
  cons.printwait("");
  cons.printwait("     `` - End Most Repeating Lights");
  cons.printwait("");
  cons.printwait(" dd - Toggle Day/Night Mode");
  cons.printwait("");
  cons.printwait("Colors:");
  cons.printwait(" r - Red    u - Purple  n - Orange");
  cons.printwait(" g - Green  y - Yellow  w - White");
  cons.printwait(" b - Blue   c - Cyan    ` - End");
  cons.printwait("");
  cons.printwait("rX  - Set Running Color  (X is the color)");
  cons.printwait("");
  cons.printwait("pX  - Pulse Anim         (X is the color)");
  cons.printwait("oX  - Overhead Anim      (X is the color)");
  cons.printwait("fX  - Flash Anim      (X is the color)");
  cons.printwait("X`  - End Command (X is the Animation)");
  cons.printwait("  Double animations will be with Running Color.");
  cons.printwait("");
  //cons.printwait("  Not all colors implemented for all commands.");
  //cons.printwait("");
  cons.printwait("'\' - Turn on and off diagnosis mode.");
  cons.printwait("t - Cycle Strips  c - Test LEDs   a - not specified");
  cons.printwait("");
}

// Display all running events.
void consoleprintevents(Console &cons, system_data &sdSysData, timed_event teEvent[])
{
  cons.printwait("Channel Count:" + std::to_string(sdSysData.CONFIG.iNUM_CHANNELS));
  for (int channel = 0; channel < sdSysData.CONFIG.iNUM_CHANNELS; channel++)
  {
    cons.printwait("Channel " + std::to_string(channel));
    if (teEvent[channel].teDATA.size() == 0)
    {
      cons.printwait("  No Events");
    }
    else
    {
      for (int event = 0; event < teEvent[channel].teDATA.size(); event++)
      {
        cons.printwait("  C" + to_string(channel)
                        + " ID:\"" + teEvent[channel].teDATA[event].strIdent
                        + "\" Anim:" + std::to_string(teEvent[channel].teDATA[event].bytANIMATION)  
                        + " LEDanim:" + std::to_string(teEvent[channel].teDATA[event].bytLEDANIMATION) 
                        + " Strt:" + std::to_string(teEvent[channel].teDATA[event].intSTARTPOS) 
                        + " End:" + std::to_string(teEvent[channel].teDATA[event].intENDPOS));
      }
    }
  }
}

// Display all running events.
void consoleprintconfig(Console &cons, system_data &sdSysData, timed_event teEvent[])
{
  cons.printwait("Configuration");
  cons.printwait("");

  cons.printwait("Switch Pin Information");
  cons.printwait("  Number of Switches - " + to_string(sdSysData.CONFIG.iNUM_SWITCHES));
  for(int x=0; x<sdSysData.CONFIG.iNUM_SWITCHES; x++)
  {
    cons.printwait("    Switch Id (" + to_string(x) + ") - " + to_string(sdSysData.CONFIG.vSWITCH_PIN_MAP.at(x).pin));
  }
  cons.printwait("");

  cons.printwait("LED Information and Strtip Order");
  cons.printwait("  Unit(" + to_string(sdSysData.CONFIG.LED_MAIN.at(0).intID) + "): "
                  + sdSysData.CONFIG.LED_MAIN.at(0).strNAME);
  cons.printwait("  Number of Groups - " + to_string(sdSysData.CONFIG.LED_MAIN.at(0).vLED_GROUPS.size()));
  cons.printwait("  LED Count - " + to_string(sdSysData.CONFIG.LED_MAIN.at(0).led_count()));


  for(int group=0; group<sdSysData.CONFIG.LED_MAIN.at(0).g_size(); group++)
  {
    cons.printwait("    Group(" + to_string(sdSysData.CONFIG.LED_MAIN.at(0).vLED_GROUPS.at(group).intID) + "): "
                    + sdSysData.CONFIG.LED_MAIN.at(0).vLED_GROUPS.at(group).strNAME
                    + "   Status: \"" + sdSysData.CONFIG.LED_MAIN.at(0).vLED_GROUPS.at(group).Status + "\"");
    cons.printwait("    Number of LED Strips - " + to_string(sdSysData.CONFIG.LED_MAIN.at(0).vLED_GROUPS.at(group).vLED_STRIPS.size()));
    cons.printwait("    LED Count:" + to_string(sdSysData.CONFIG.LED_MAIN.at(0).vLED_GROUPS.at(group).led_count()));

    for(int strip=0; strip<sdSysData.CONFIG.LED_MAIN.at(0).s_size(group); strip++)
    {
      cons.printwait("      C" + to_string(sdSysData.CONFIG.LED_MAIN.at(0).vLED_GROUPS.at(group).vLED_STRIPS.at(strip).intCHANNEL) 
                      + " G" + to_string(group) + " S" + to_string(strip) 
                      + "  Strip(" + to_string(sdSysData.CONFIG.LED_MAIN.at(0).vLED_GROUPS.at(group).vLED_STRIPS.at(strip).intID) + "): "
                      + sdSysData.CONFIG.LED_MAIN.at(0).vLED_GROUPS.at(group).vLED_STRIPS.at(strip).strNAME + " "
                      + sdSysData.CONFIG.LED_MAIN.at(0).vLED_GROUPS.at(group).vLED_STRIPS.at(strip).strPOSITION );

      cons.printwait("        LED: Count:" + to_string(sdSysData.CONFIG.LED_MAIN.at(0).vLED_GROUPS.at(group).vLED_STRIPS.at(strip).led_count()) 
                      + "   Start:" + to_string(sdSysData.CONFIG.LED_MAIN.at(0).vLED_GROUPS.at(group).vLED_STRIPS.at(strip).fs(0))
                      + "   End:" + to_string(sdSysData.CONFIG.LED_MAIN.at(0).vLED_GROUPS.at(group).vLED_STRIPS.at(strip).fe(0) )
                      + "   forward:" + to_string(sdSysData.CONFIG.LED_MAIN.at(0).vLED_GROUPS.at(group).vLED_STRIPS.at(strip).booFORWARD)
                      + "   standing:" + to_string(sdSysData.CONFIG.LED_MAIN.at(0).vLED_GROUPS.at(group).vLED_STRIPS.at(strip).booBOT_AT_START)
                      + "   Status: \"" + sdSysData.CONFIG.LED_MAIN.at(0).vLED_GROUPS.at(group).vLED_STRIPS.at(strip).Status + "\"");
    }
  }
}

// -------------------------------------------------------------------------------------
// Test Animation

void processtestanimation(Console &cons, system_data &sdSysData, unsigned long tmeCurrentTime, timed_event teEvent[], CRGB cRGBpulsecolor)
{
  for (int channel = 0; channel < sdSysData.CONFIG.iNUM_CHANNELS; channel++)
  {
    teEvent[channel].set("Channel Light Pulse Color", tmeCurrentTime, 100, 0, 0, AnEvSchedule, AnTavdTestAnimation, false, cRGBpulsecolor, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), 0, 0, false, true, false, "", "");  
  }
  sdSysData.booPulsesRunning = true;
}

void process_power_animation(Console &cons, system_data &sdSysData, unsigned long tmeCurrentTime, timed_event teEvent[], CRGB cRGBpulsecolor)
{
  for (int channel = 0; channel < sdSysData.CONFIG.iNUM_CHANNELS; channel++)
  {
    teEvent[channel].set("Channel Light Pulse Color", tmeCurrentTime, 0, 0, 0, AnEvSchedule, AnTavdPowerAnimation, false, cRGBpulsecolor, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), 0, 0, false, true, false, "", "");  
  }
  sdSysData.booPulsesRunning = true;
}

// -------------------------------------------------------------------------------------
// Pulses

// Set To End All Pulses
void processcommandpulseend(Console &cons, system_data &sdSysData, unsigned long tmeCurrentTime, timed_event teEvent[])
{
  for (int channel = 0; channel < sdSysData.CONFIG.iNUM_CHANNELS; channel++)
  {
    teEvent[channel].set("Channel Light Pulse Color", tmeCurrentTime, 5, 1000, 80, AnEvSetToEnd, 0, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), 0, 255, true, true, false, "", "");
  }
  sdSysData.booPulsesRunning = false;
}

// Flash Color All Channels
void processcommandflash(Console &cons, system_data &sdSysData, unsigned long tmeCurrentTime, timed_event teEvent[], CRGB cRGBflashcolor)
{
  for (int channel = 0; channel < sdSysData.CONFIG.iNUM_CHANNELS; channel++)
  {
    teEvent[channel].set("Channel Light Pulse Color", tmeCurrentTime, 100, 0, 0, AnEvSchedule, AnTaChannelFlashColor, false, cRGBflashcolor, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), 0, 0, false, true, false, "", "");  
  }
  //sdSysData.booPulsesRunning = true;
}

// Pulse Color All Channels
void processcommandpulse(Console &cons, system_data &sdSysData, unsigned long tmeCurrentTime, timed_event teEvent[], CRGB cRGBpulsecolor)
{
  for (int channel = 0; channel < sdSysData.CONFIG.iNUM_CHANNELS; channel++)
  {
    teEvent[channel].set("Channel Light Pulse Color", tmeCurrentTime, 100, 0, 0, AnEvSchedule, AnTaChannelPulseColor, false, cRGBpulsecolor, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), 0, 0, false, true, false, "", "");  
  }
  sdSysData.booPulsesRunning = true;
}

// Pulse Color All Channels
void processcommandpulsecountdown(Console &cons, system_data &sdSysData, unsigned long tmeCurrentTime, timed_event teEvent[])
{
  for (int channel = 0; channel < sdSysData.CONFIG.iNUM_CHANNELS; channel++)
  {
    teEvent[channel].set("Channel Light Pulse Color", tmeCurrentTime, 100, 0, 0, AnEvSchedule, AnTaChannelPulseColorCountdown, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), 0, 0, false, true, false, "", "");  
  }
  sdSysData.booPulsesRunning = true;
}

// -------------------------------------------------------------------------------------
// Overhead Illum

// Set To End All Overhead Illumination
void processcommandoverheadillumend(Console &cons, system_data &sdSysData, unsigned long tmeCurrentTime, timed_event teEvent[])
{
  for (int channel = 0; channel < sdSysData.CONFIG.iNUM_CHANNELS; channel++)
  {
    teEvent[channel].set("Overhead Illumination", tmeCurrentTime, 0, 1000, 80, AnEvSetToEnd, 0, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), 0, 255, true, true, false, "", "");
  }
  sdSysData.booOverheadRunning = false;
}

// -------------------------------------------------------------------------------------
// Overhead Illumination Color
void processcommandoverheadillum(Console &cons, system_data &sdSysData, unsigned long tmeCurrentTime, timed_event teEvent[], CRGB cRGBpulsecolor)
{
  for (int channel = 0; channel < sdSysData.CONFIG.iNUM_CHANNELS; channel++)
  {
    teEvent[channel].set("Overhead Illumination", tmeCurrentTime, 100, 0, 0, AnEvSchedule, AnTaOverheadIllumColor, false, cRGBpulsecolor, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), 0, 0, false, true, false, "", "");  
  }
  sdSysData.booOverheadRunning = true;
}

//  Overhead Illumination Pacificaish Color
void processcommandpacificaishcolor(Console &cons, system_data &sdSysData, unsigned long tmeCurrentTime, timed_event teEvent[], CRGB cRGBpulsecolor)
{
  for (int channel = 0; channel < sdSysData.CONFIG.iNUM_CHANNELS; channel++)
  {
    teEvent[channel].set("Overhead Illumination", tmeCurrentTime, 100, 0, 0, AnEvSchedule, AnTaPacificaishColor, false, cRGBpulsecolor, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), 0, 0, false, true, false, "", "");  
  }
  sdSysData.booOverheadRunning = true;
}

// -------------------------------------------------------------------------------------
// Hazard

// Set To End All Hazard
void processcommandhazardend(Console &cons, system_data &sdSysData, unsigned long tmeCurrentTime, timed_event teEvent[])
{
  for (int channel = 0; channel < sdSysData.CONFIG.iNUM_CHANNELS; channel++)
  {
    teEvent[channel].set("Hazard", tmeCurrentTime, 0, 1000, 80, AnEvSetToEnd, 0, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), 0, 255, true, true, false, "", "");
  }
  sdSysData.booHazardRunning = false;
}

// Hazard
void processcommandhazard(Console &cons, system_data &sdSysData, unsigned long tmeCurrentTime, timed_event teEvent[], CRGB cRGBpulsecolor)
{
  for (int channel = 0; channel < sdSysData.CONFIG.iNUM_CHANNELS; channel++)
  {
    teEvent[channel].set("Hazard", tmeCurrentTime, 100, 0, 0, AnEvSchedule, AnTavdOverhead_Mask, false, cRGBpulsecolor, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), 0, 0, false, true, false, "", "");  
    teEvent[channel].set("Hazard", tmeCurrentTime, 100, 0, 0, AnEvSchedule, AnTaHazard, false, cRGBpulsecolor, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), 0, 0, false, true, false, "", "");  
  }
  sdSysData.booHazardRunning = true;
}

// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------

bool check_command(Console &cons, string command, string description)
// Check the cons command with the parameter command
//  If matched, print command entered, description, and clears cons.command.
//  Only print description if one is provideded, not equal to "".
//  Else, just return false.
{
  if (cons.keywatch.Command.COMMANDLINE == command)
  {
    //cons.printwait("CMD: " + cons.keywatch.Command.COMMANDLINE);
    cons.printwait(linemerge_left_justify("________________________________________________", 
                    "CMD: " + cons.keywatch.Command.COMMANDLINE));

    if (description == "")
    {
      // do nothing
    }
    else
    {
      command_desc(cons, description);
    }

    cons.keywatch.cmdClear();
    return true;
  }
  else
  {
    return false;
  }

}

bool check_command_with_num_param(Console &cons, string command, string description, int num_start, int num_len, int &Parameter)
{
  bool boo_return = false;
  if (cons.keywatch.Command.COMMANDLINE.length() == command.length())
  {
    if(cons.keywatch.Command.COMMANDLINE.substr(0,num_start) == command.substr(0,num_start))
    {
      try
      {
        Parameter = stoi(cons.keywatch.Command.COMMANDLINE.substr(num_start, num_len));
        boo_return = check_command(cons, cons.keywatch.Command.COMMANDLINE, description);
      }
      catch(const std::exception& e)
      {
        cons.keywatch.cmdClear();
      }
    }
  }

  return boo_return;  
}

void run_test(Console &cons, system_data &sdSysData, unsigned long tmeCurrentTime, timed_event teEvent[])
{
  cons.printwait("Test ...");

  cons.printwait("------------------");
  cons.printwait("no test code prepared.");
  cons.printwait("------------------");
}

// Process and call routines as entered on the command line.
void processcommandlineinput(Console &cons, system_data &sdSysData, unsigned long tmeCurrentTime, 
                              timed_event teEvent[], ANIMATION_HANDLER &Animations)
{
  COMMANDS command;
  int parameter = 0;
          
  if(cons.keywatch.cmdPressed() == true)
  {
    // Color Palettes
    CRGB crgbWhite  = CRGB(32,32,32); // W
    CRGB crgbRed    = CRGB(64,0,0);   // R
    CRGB crgbGreen  = CRGB(0,64,0);   // G
    CRGB crgbBlue   = CRGB(0,0,64);   // B

    CRGB crgbPurple = CRGB(32,0,64);  // U
    CRGB crgbYellow = CRGB(48,48,0);  // Y
    CRGB crgbCyan   = CRGB(0,48,48);  // C

    CRGB crgbOrange = CRGB(64,16,0);  // N

    
    // Call routines that match the info on the command line.

    // Test Routine
    if(cons.keywatch.Command.COMMANDLINE == " test")
    {
      // Keep values below 128
      cons.printwait("CMD: " + cons.keywatch.Command.COMMANDLINE);
      run_test(cons, sdSysData, tmeCurrentTime, teEvent);
      cons.keywatch.cmdClear();
    }

    if (check_command(cons," sev1", "Event System 1"))
    {
      sdSysData.ACTIVE_EVENT_SYSTEM = 1;
      cons.keywatch.cmdClear();
    }

    if (check_command(cons," sev2", "Event System 2"))
    {
      sdSysData.ACTIVE_EVENT_SYSTEM = 2;
      cons.keywatch.cmdClear();
    }

    if (check_command(cons," animt", "Event System 2 Test Animation"))
    {
      Animations.call_animation(sdSysData, tmeCurrentTime, "Car", "test");
      cons.keywatch.cmdClear();
    }
    
    // Program Exit
    if (check_command(cons,"X", "Program Exit") || check_command(cons, "exit", "Program Exit"))
    {
      cons.keywatch.in(KEYEXIT);
    }

    // Program Restart
    if (check_command(cons, " restart", "Restart Program"))
    {
      sdSysData.booREBOOT = true;
      cons.keywatch.in(KEYEXIT);
    }

    // print help
    if (check_command(cons, "help", "Help and Instructions"))
    {
      consoleprinthelp(cons);
    }

    // print event list
    if (check_command(cons, " events", "All Currently Running Events"))
    {
      consoleprintevents(cons, sdSysData, teEvent);
    }

    // print configuration data
    if (check_command(cons, " config", "Current Configuration and Settings"))
    {
      consoleprintconfig(cons, sdSysData, teEvent);
    }

    // End All Extra Repeating Lights and Countdown Timer
    if (check_command(cons, "``", "End Most Pulse Animations"))
    {
      // end Countdown Timer
      sdSysData.cdTIMER.end();

      processcommandpulseend(cons, sdSysData, tmeCurrentTime, teEvent);
      processcommandoverheadillumend(cons, sdSysData, tmeCurrentTime, teEvent);
      processcommandhazardend(cons, sdSysData, tmeCurrentTime, teEvent);
    }

    // -------------------------------------------------------------------------------------
    // Animations Load or Reload

    if (check_command(cons, " animld", "Reload Animations"))
    {
      string Working_Directory = FILES_DIRECTORY;
      string Animations_Library_JSON = FILES_ANIMATIONS;
      string Running_State_Filename = Working_Directory + FILES_RUNNING_STATE_SAVE;

      if (Animations.load_collections(Working_Directory, Animations_Library_JSON) == true)
      {
        cons.printi("  Animations file loaded.");
      }
      else
      {
        cons.printi("    Animations file not loaded.");
      }
    }

    // -------------------------------------------------------------------------------------
    // DAY NIGHT MODE

    // Toggle Day Night
    if (check_command(cons, "dd", ""))
    {
      if (sdSysData.booDay_On == true)
      {
        command_desc(cons, "Toggle DAY mode OFF.");
        sdSysData.booDay_On = false;
      }
      else
      {
        command_desc(cons, "Toggle DAY mode ON.");
        sdSysData.booDay_On = true;
      }
    }

    // Toggle Lights Off
    if (check_command(cons, " lightsoff", "Lights Off."))
    {
      sdSysData.Lights_On = false;
    }

    // Toggle Lights On
    if (check_command(cons, " lightson", "Lights ON."))
    {
      sdSysData.Lights_On = true;
    }

    // Toggle Day Mode On
    if (check_command(cons, "dayon", "DAY mode ON."))
    {
      sdSysData.booDay_On = true;
    }

    // Toggle Day Mode Off
    if (check_command(cons, "dayoff", "DAY mode OFF."))
    {
      sdSysData.booDay_On = false;
    }
    
    // -------------------------------------------------------------------------------------
    // TERMINAL COMMANDS
 
    // Command Line (sudo shutdown now)
    if (check_command(cons, " comshutd", "Shutdown Started"))
    {
      command_desc(cons, "Shutting System Down.");
      
      // Call Shutdown command.
      command.shutdown_now();

      // Start Power Down Animation
      process_power_animation(cons, sdSysData, tmeCurrentTime, teEvent, CRGB(25, 0, 0));

      // Set system to exit
      cons.keywatch.in(KEYEXIT);
    }

    // -------------------------------------------------------------------------------------
    // Threadable Commands with from command prompt   

    // Radio -------------
    // Command Line (load air_m)
    if (check_command(cons, " airstop", "Airband Stop"))
    { 
      // Call command.
      sdSysData.Command_Thread.run_command("/home/pi/rtlsdr/ras_airstop.sh");

      // Start Power Down Animation
      process_power_animation(cons, sdSysData, tmeCurrentTime, teEvent, CRGB(25, 0, 0));
    }

    // Command Line (load air_m)
    if (check_command(cons, " lafm", "Airband Lafayette Multi"))
    {
      // Call command.
      sdSysData.Command_Thread.run_command("/home/pi/rtlsdr/ras_lafm.sh");

      // Start Power Down Animation
      process_power_animation(cons, sdSysData, tmeCurrentTime, teEvent, CRGB(25, 0, 0));
    }

    // Radio Call Airband Lafayette Scan Script Command
    if (check_command(cons, " lafs", "Airband Lafayette Scan"))
    {
      // Call command.
      sdSysData.Command_Thread.run_command("/home/pi/rtlsdr/ras_lafs.sh");

      // Start Power Down Animation
      process_power_animation(cons, sdSysData, tmeCurrentTime, teEvent, CRGB(25, 0, 0));
    }

    // Radio Call CB Channel Scan Script Command
    if (check_command(cons, " cbs", "CB Channel Scan"))
    {
      // Call command.
      sdSysData.Command_Thread.run_command("/home/pi/rtlsdr/ras_cbs.sh");

      // Start Power Down Animation
      process_power_animation(cons, sdSysData, tmeCurrentTime, teEvent, CRGB(25, 0, 0));
    }

    // Radio Call NOAA Channel Scan Script Command
    if (check_command(cons, " rnoaa", "NOAA Channel Scan"))
    {
      // Call command.
      sdSysData.Command_Thread.run_command("/home/pi/rtlsdr/ras_noaa.sh");

      // Start Power Down Animation
      process_power_animation(cons, sdSysData, tmeCurrentTime, teEvent, CRGB(25, 0, 0));
    }

    // Radio Call Emergency Channel Scan Script Command
    if (check_command(cons, " remergenc", "Emergency Channel Scan"))
    {
      // Call command.
      sdSysData.Command_Thread.run_command("/home/pi/rtlsdr/ras_emergency.sh");

      // Start Power Down Animation
      process_power_animation(cons, sdSysData, tmeCurrentTime, teEvent, CRGB(25, 0, 0));
    }

    // Radio Shutdown Channel Command
    if (check_command(cons, " radoff", "Turn Off Radio"))
    {
      // Call command.
      sdSysData.RADIO_COORD.command_send(-1, 0);

      // Start Power Down Animation
      process_power_animation(cons, sdSysData, tmeCurrentTime, teEvent, CRGB(25, 0, 0));
    }

    // Radio Shutdown Channel Command
    if (check_command(cons, " rclear", "Radio Clear Holds and Skips"))
    {
      // Call command.
      sdSysData.RADIO_COORD.command_send(3, 0);

      // Start Power Down Animation
      process_power_animation(cons, sdSysData, tmeCurrentTime, teEvent, CRGB(25, 0, 0));
    }

    // Radio Skip Channel Command
    if (check_command_with_num_param(cons, " rs######", "Radio Skip Channel", 3, 6, parameter))
    {
      // Call command.
      sdSysData.RADIO_COORD.command_send(1, parameter);
      cons.printi("Skip Channel: " + to_string(parameter)); // eg  rs118500
    }

    // Radio Hold Channel Command
    if (check_command_with_num_param(cons, " rh######", "Radio Hold Channel", 3, 6, parameter))
    {
      // Call command.
      sdSysData.RADIO_COORD.command_send(2, parameter);
      cons.printi("Hold Channel: " + to_string(parameter)); // eg  rh122950
    }

    // Radio Clear Channel Command
    if (check_command_with_num_param(cons, " rc######", "Radio Hold Channel", 3, 6, parameter))
    {
      // Call command.
      sdSysData.RADIO_COORD.command_send(4, parameter);
      cons.printi("Hold Channel: " + to_string(parameter)); // eg  rh122950
    }

    /*
    // -------------------------------------------------------------------------------------
    // For Deguging Gadgets
    // Debug Counter On
    if (check_command(cons, " debugcon", "Debug Counter On"))
    {
      sdSysData.DEBUG_COUNTER = true;
    }

    // Debug Counter Off
    if (check_command(cons, " debugcoff", "Debug Counter On"))
    {
      sdSysData.DEBUG_COUNTER = false;
    }
    */

    // -------------------------------------------------------------------------------------
    // ABS-B -------------
    // Command Line (load fastart.sh)
    if (check_command(cons, " absbon", "ABS-B On"))
    { 
      // Call command.
      sdSysData.Command_Thread.run_command("/home/pi/flightaware/fastart.sh");

      // Start Power Down Animation
      process_power_animation(cons, sdSysData, tmeCurrentTime, teEvent, CRGB(15, 15, 0));
    }

    // Command Line (load fastop.sh)
    if (check_command(cons, " absboff", "ABS-B Off"))
    {
      // Call command.
      sdSysData.Command_Thread.run_command("/home/pi/flightaware/fastop.sh");

      // Start Power Down Animation
      process_power_animation(cons, sdSysData, tmeCurrentTime, teEvent, CRGB(15, 15, 0));
    }
    
    // Command Line (load copy direcory)
    if (check_command(cons, " adsbsnap", "ADS-B Snapshot"))
    {
      // Call command.
      //cons.printwait("cp -r /run/dump1090-fa/ ~/flightaware/snapshot." + to_string(tmeCurrentTime));
      sdSysData.Command_Thread.run_command("cp -r /run/dump1090-fa/ /home/pi/flightaware/snapshot." + sdSysData.AIRCRAFT_COORD.DATA.NOW.get_str_value());

      // Start Power Down Animation
      process_power_animation(cons, sdSysData, tmeCurrentTime, teEvent, CRGB(0, 30, 0));
    }
    // -------------------------------------------------------------------------------------
    // PLAYLIST

    // Print out the current playlist.
    if (check_command(cons, " playlist", "Current Playlist:"))
    {
      for (int x=0; x < cons.the_player.Play_List.size(); x++)
      {
        cons.printwait("  " + cons.the_player.Play_List.MOVIE_LIST[x]);
      }
    }

    // Skip to the next film in the playlist.
    if (check_command(cons, " skip", "Play Next in Playlist:"))
    {
      cons.the_player.booSkip = true;
    }

    // -------------------------------------------------------------------------------------
    // FLASH

    // flash Running
    if (check_command(cons, "ff", "Flash All LEDs with Running Color"))
    {
      processcommandflash(cons, sdSysData, tmeCurrentTime, teEvent, sdSysData.get_running_color());
    }

    // flash White
    if (check_command(cons, "fw", "Flash White All LEDs"))
    {
      processcommandflash(cons, sdSysData, tmeCurrentTime, teEvent, crgbWhite);
    }

    // flash Red
    if (check_command(cons, "fr", "Flash Red All LEDs"))
    {
      processcommandflash(cons, sdSysData, tmeCurrentTime, teEvent, crgbRed);
    }

    // flash Green
    if (check_command(cons, "fg", "Flash Green All LEDs"))
    {
      processcommandflash(cons, sdSysData, tmeCurrentTime, teEvent, crgbGreen);
    }

    // flash Blue
    if (check_command(cons, "fb", "Flash Blue All LEDs"))
    {
      processcommandflash(cons, sdSysData, tmeCurrentTime, teEvent, crgbBlue);
    }

    // flash Purple
    if (check_command(cons, "fu", "Flash Purple All LEDs"))
    {
      processcommandflash(cons, sdSysData, tmeCurrentTime, teEvent, crgbPurple);
    }
  
    // flash Yellow
    if (check_command(cons, "fy", "Flash Yellow All LEDs"))
    {
      processcommandflash(cons, sdSysData, tmeCurrentTime, teEvent, crgbYellow);
    }
    
    // flash Cyan
    if (check_command(cons, "fc", "Flash Cyan All LEDs"))
    {
      processcommandflash(cons, sdSysData, tmeCurrentTime, teEvent, crgbCyan);
    }

    // flash Orange
    if (check_command(cons, "fn", "Flash Orange All LEDs"))
    {
      processcommandflash(cons, sdSysData, tmeCurrentTime, teEvent, crgbOrange);
    }

    // -------------------------------------------------------------------------------------
    // PULSES

    // pulse end
    if (check_command(cons, "p`", "End Most Pulse Animations"))
    {
      processcommandpulseend(cons, sdSysData, tmeCurrentTime, teEvent);
    }

    // pulse Running Timer
    if (check_command(cons, "  ", "5 minute Pulse Timer Started with Running Color"))
    {
      sdSysData.start_timer(DEFAULTTIMER * 60);
      processcommandpulsecountdown(cons, sdSysData, tmeCurrentTime, teEvent);
    }

    // pulse Running Timer end
    if (check_command(cons, " `", "Pulse Timer Stop"))
    {
      sdSysData.cdTIMER.end();
      processcommandpulseend(cons, sdSysData, tmeCurrentTime, teEvent);
    }

    // pulse Running Color
    if (check_command(cons, "pp", "Pulse Running Color All LEDs"))
    {
      processcommandpulse(cons, sdSysData, tmeCurrentTime, teEvent, sdSysData.get_running_color());
    }

    // pulse White
    if (check_command(cons, "pw", "Pulse White All LEDs"))
    {
      processcommandpulse(cons, sdSysData, tmeCurrentTime, teEvent, crgbWhite);
    }

    // pulse Red
    if (check_command(cons, "pr", "Pulse Red All LEDs"))
    {
      processcommandpulse(cons, sdSysData, tmeCurrentTime, teEvent, crgbRed);
    }

    // pulse Green
    if (check_command(cons, "pg", "Pulse Green All LEDs"))
    {
      processcommandpulse(cons, sdSysData, tmeCurrentTime, teEvent, crgbGreen);
    }

    // pulse Blue
    if (check_command(cons, "pb", "Pulse Blue All LEDs"))
    {
      processcommandpulse(cons, sdSysData, tmeCurrentTime, teEvent, crgbBlue);
    }

    // pulse Purple
    if (check_command(cons, "pu", "Pulse Purple All LEDs"))
    {
      processcommandpulse(cons, sdSysData, tmeCurrentTime, teEvent, crgbPurple);
    }

    // pulse Yellow
    if (check_command(cons, "py", "Pulse Yellow All LEDs"))
    {
      processcommandpulse(cons, sdSysData, tmeCurrentTime, teEvent, crgbYellow);
    }

    // pulse Cyan
    if (check_command(cons, "pc", "Pulse Cyan All LEDs"))
    {
      processcommandpulse(cons, sdSysData, tmeCurrentTime, teEvent, crgbCyan);
    }

    // pulse Orange
    if (check_command(cons, "pn", "Pulse Orange All LEDs"))
    {
      processcommandpulse(cons, sdSysData, tmeCurrentTime, teEvent, crgbOrange);
    }

    // -------------------------------------------------------------------------------------
    // Overhead Illumination
    
    // pulse end overhead illum
    if (check_command(cons, "o`", "Turn Off Overhead Illumination Lights"))
    {
      processcommandoverheadillumend(cons, sdSysData, tmeCurrentTime, teEvent);
    }

    // Overhead Running
    if (check_command(cons,"oo", "Turn On Overhead Illumination Lights with Running Color") || 
        check_command(cons,"zz", "Turn On Overhead Illumination Lights with Running Color"))
    {
      processcommandpacificaishcolor(cons, sdSysData, tmeCurrentTime, teEvent, sdSysData.get_running_color());
    }

    // Overhead White
    if (check_command(cons, "ow", "Turn On White Overhead Illumination Lights"))
    {
      processcommandpacificaishcolor(cons, sdSysData, tmeCurrentTime, teEvent, crgbWhite);
    }

    // Overhead Red
    if (check_command(cons, "or", "Turn On Red Overhead Illumination Lights"))
    {
      processcommandpacificaishcolor(cons, sdSysData, tmeCurrentTime, teEvent, crgbRed);
    }

    // Overhead Green
    if (check_command(cons, "og", "Turn On Green Overhead Illumination Lights"))
    {
      processcommandpacificaishcolor(cons, sdSysData, tmeCurrentTime, teEvent, crgbGreen);
    }

    // Overhead Blue
    if (check_command(cons, "ob", "Turn On Blue Overhead Illumination Lights"))
    {
      processcommandpacificaishcolor(cons, sdSysData, tmeCurrentTime, teEvent, crgbBlue);
    }

    // Overhead Purple
    if (check_command(cons, "ou", "Turn On Purple Overhead Illumination Lights"))
    {
      processcommandpacificaishcolor(cons, sdSysData, tmeCurrentTime, teEvent, crgbPurple);
    }

    // Overhead Yellow
    if (check_command(cons, "oy", "Turn On Yellow Overhead Illumination Lights"))
    {
      processcommandpacificaishcolor(cons, sdSysData, tmeCurrentTime, teEvent, crgbYellow);
    }

    // Overhead Cyan
    if (check_command(cons, "oc", "Turn On Cyan Overhead Illumination Lights"))
    {
      processcommandpacificaishcolor(cons, sdSysData, tmeCurrentTime, teEvent, crgbCyan);
    }

    // Overhead Orange
    if (check_command(cons, "on", "Turn On Orange Overhead Illumination Lights"))
    {
      processcommandpacificaishcolor(cons, sdSysData, tmeCurrentTime, teEvent, crgbOrange);
    }

    // Set Running Color
    if (check_command(cons, "rw", "Set Running Color to White"))
    {
      sdSysData.set_running_color(crgbWhite, "White");
    }

    if (check_command(cons, "rr", "Set Running Color to Red"))
    {
      sdSysData.set_running_color(crgbRed, "Red");
    }

    if (check_command(cons, "rg", "Set Running Color to Green"))
    {
      sdSysData.set_running_color(crgbGreen, "Green");
    }

    if (check_command(cons, "rb", "Set Running Color to Blue"))
    {
      sdSysData.set_running_color(crgbBlue, "Blue");
    }

    if (check_command(cons, "ru", "Set Running Color to Purple"))
    {
      sdSysData.set_running_color(crgbPurple, "Purple");
    }

    if (check_command(cons, "ry", "Set Running Color to Yellow"))
    {
      sdSysData.set_running_color(crgbYellow, "Yellow");
    }

    if (check_command(cons, "rc", "Set Running Color to Cyan"))
    {
      sdSysData.set_running_color(crgbCyan, "Cyan");
    }

    if (check_command(cons, "rn", "Set Running Color to Orange"))
    {
      sdSysData.set_running_color(crgbOrange, "Orange");
    }


    /*
    // -------------------------------------------------------------------------------------
    // Overhead Pacificaish White
    if(cons.keywatch.Command.COMMANDLINE == "ott")
    {
      // Keep values below 128
      cons.printwait("CMD: " + cons.keywatch.Command.COMMANDLINE);
      processcommandpacificaishcolor(cons, sdSysData, tmeCurrentTime, teEvent, crgbWhite);
      cons.keywatch.cmdClear();
    }

    // Overhead Pacificaish Blue
    if(cons.keywatch.Command.COMMANDLINE == "otb")
    {
      // Keep values below 128
      cons.printwait("CMD: " + cons.keywatch.Command.COMMANDLINE);
      processcommandpacificaishcolor(cons, sdSysData, tmeCurrentTime, teEvent, crgbBlue);
      cons.keywatch.cmdClear();
    }
    */

    // -------------------------------------------------------------------------------------
    // Hazard
    
    // Hazard illum end
    if (check_command(cons, "h`", "HAZARD LIGHTS OFF"))
    {
      processcommandhazardend(cons, sdSysData, tmeCurrentTime, teEvent);
    }

    // Hazard
    if (check_command(cons, "hh", "HAZARD LIGHTS ON ('h`' to turn off"))
    {
      processcommandhazard(cons, sdSysData, tmeCurrentTime, teEvent, crgbWhite);
    }

    // -------------------------------------------------------------------------------------
    // Debug Characters only active when debug mode is on
    // debug
    if (check_command(cons, "/", "Debug mode On/Off Toggle"))
    {
      cons.keywatch.in(KEYDEBUG);
    }

    // Only accept debug keys if debug is on.
    if (cons.keywatch.getnoreset(KEYDEBUG) == 1)
    {
      // Run Test Animation
      if(cons.keywatch.Command.COMMANDLINE[0] == KEYTESTANIM)
      {
        cons.printwait("CMD: " + cons.keywatch.Command.COMMANDLINE);
        //processtestanimation(cons, sdSysData, tmeCurrentTime, teEvent, crgbWhite);
        //process_power_animation(cons, sdSysData, tmeCurrentTime, teEvent, crgbWhite);
        process_power_animation(cons, sdSysData, tmeCurrentTime, teEvent, CRGB(0, 0, 25));
        cons.keywatch.cmdClear();
      }

      // LED DOOR CYCLE
      if(cons.keywatch.Command.COMMANDLINE[0] == KEYLEDDRCYCL)
      {
        cons.printwait("CMD: " + cons.keywatch.Command.COMMANDLINE);
        cons.keywatch.in(KEYLEDDRCYCL);
        cons.keywatch.cmdClear();
      }

      // LED TEST toggle all lights on to static value.
      if(cons.keywatch.Command.COMMANDLINE[0] == KEYLEDTEST)
      {
        cons.printwait("CMD: " + cons.keywatch.Command.COMMANDLINE);
        cons.keywatch.in(KEYLEDTEST);
        cons.keywatch.cmdClear();
      }

      // Toggle door open or closed.
      if(cons.keywatch.Command.COMMANDLINE[0] == '1')
      {
        cons.printwait("CMD: " + cons.keywatch.Command.COMMANDLINE);
        cons.keywatch.in('1');
        cons.keywatch.cmdClear();
      }

      // Toggle door open or closed.
      if(cons.keywatch.Command.COMMANDLINE[0] == '2')
      {
        cons.printwait("CMD: " + cons.keywatch.Command.COMMANDLINE);
        cons.keywatch.in('2');
        cons.keywatch.cmdClear();
      }

      // Toggle door open or closed.
      if(cons.keywatch.Command.COMMANDLINE[0] == '3')
      {
        cons.printwait("CMD: " + cons.keywatch.Command.COMMANDLINE);
        cons.keywatch.in('3');
        cons.keywatch.cmdClear();
      }

      // Toggle door open or closed.
      if(cons.keywatch.Command.COMMANDLINE[0] == '4')
      {
        cons.printwait("CMD: " + cons.keywatch.Command.COMMANDLINE);
        cons.keywatch.in('4');
        cons.keywatch.cmdClear();
      }
    }

    // -------------------------------------------------------------------------------------
    // Turn on and off debug. Deactivate debug keys when off.
    // Store behavior values for debug info.
    if (cons.keywatch.pressed(KEYDEBUG) == true)
    {
      if (cons.keywatch.getnoreset(KEYDEBUG) == 0)
      {
        // Draw values for debug LED CYCLE through displayed range (all, Door #)
        cons.keywatch.Chars[KEYLEDDRCYCL].VALUE = 0;
        cons.keywatch.Chars[KEYLEDDRCYCL].ACTIVE = false;

        // Draw values for debug LED TEST toggle all lights on to static value.
        cons.keywatch.Chars[KEYLEDTEST].VALUE = 0;
        cons.keywatch.Chars[KEYLEDTEST].ACTIVE = false;

        // Draw values for toggle door open or closed.
        cons.keywatch.Chars['1'].VALUE = 0;
        cons.keywatch.Chars['1'].ACTIVE = false;
        
        // Draw values for toggle door open or closed.
        cons.keywatch.Chars['2'].VALUE = 0;
        cons.keywatch.Chars['2'].ACTIVE = false;

        // Draw values for toggle door open or closed.
        cons.keywatch.Chars['3'].VALUE = 0;
        cons.keywatch.Chars['3'].ACTIVE = false;

        // Draw values for toggle door open or closed.
        cons.keywatch.Chars['4'].VALUE = 0;
        cons.keywatch.Chars['4'].ACTIVE = false;
      }
      else
      {
        // Reset console debug values to default values if debug turned off.
        cons.keywatch.Chars[KEYLEDDRCYCL].ACTIVE = true;
        cons.keywatch.Chars[KEYLEDTEST].ACTIVE = true;
        cons.keywatch.Chars['1'].ACTIVE = true;
        cons.keywatch.Chars['2'].ACTIVE = true;
        cons.keywatch.Chars['3'].ACTIVE = true;
        cons.keywatch.Chars['4'].ACTIVE = true;
      }
    }
  }
}

// If a door is opened and DOORAWARE is on, we want to end these animations when the door
//  has been opened.
void extraanimationdoorcheck(Console &cons, system_data &sdSysData, unsigned long tmeCurrentTime, timed_event teEvent[] )
{
  if ( (sdSysData.intDoorsOpen > 0)  && ((sdSysData.booPulsesRunning == true) || (sdSysData.booOverheadRunning == true)) )
  {
    // End pulses when door is opened and end countdown timer.
    sdSysData.cdTIMER.end();
    processcommandpulseend(cons, sdSysData, tmeCurrentTime, teEvent);
    processcommandoverheadillumend(cons, sdSysData, tmeCurrentTime, teEvent);
  }
}




#endif