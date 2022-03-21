// ***************************************************************************************
// *
// *    Core       | Everything within this document is proprietary to Core Dynamics.
// *    Dynamics   | Any unauthorized duplication will be subject to prosecution.
// *
// *    Department : (R+D)^2                        Name: interface.h
// *       Sub Dept: Programming
// *    Location ID: 856-45B
// *                                                      (c) 2856 - 2858 Core Dynamics
// ***************************************************************************************

#ifndef INTERFACE_H
#define INTERFACE_H

// Standard Header Files
#include <string>

// RASFled related header files
#include "consoleanddata.h"
#include "timedeventsystem.h"
#include "commands.h"


// ***************************************************************************************
// STRUCTURES AND CLASSES
// ***************************************************************************************


// ***************************************************************************************
// FUNCTION AND PROCEDURES
// ***************************************************************************************

void command_desc(Console &cons, string strDescription)
{
  cons.printwait("__________________________");
  cons.printwait(strDescription);
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
  cons.printwait("'x' or 'exit' - Safely exits the RasFLED.");
  cons.printwait("' restart'    - Restart RasFLED.");
  cons.printwait("");
  cons.printwait("'help'    - Prints this help screen.");
  cons.printwait("' events' - Prints all active events.");
  cons.printwait("' config' - Prints some configuration data.");
  cons.printwait("");
  cons.printwait("     hh - Hazard Lights");
  cons.printwait("     h` - Hazard Lights Off");
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
  cons.printwait("\\   - Turn on and off diagnosis mode.");
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
    teEvent[channel].set("Channel Light Pulse Color", tmeCurrentTime, 100, 0, 0, AnEvSchedule, AnTavdTestAnimation, false, cRGBpulsecolor, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), 0, 0, false, true, false);  
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
    teEvent[channel].set("Channel Light Pulse Color", tmeCurrentTime, 5, 1000, 80, AnEvSetToEnd, 0, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), 0, 255, true, true, false);
  }
  sdSysData.booPulsesRunning = false;
}

// Flash Color All Channels
void processcommandflash(Console &cons, system_data &sdSysData, unsigned long tmeCurrentTime, timed_event teEvent[], CRGB cRGBflashcolor)
{
  for (int channel = 0; channel < sdSysData.CONFIG.iNUM_CHANNELS; channel++)
  {
    teEvent[channel].set("Channel Light Pulse Color", tmeCurrentTime, 100, 0, 0, AnEvSchedule, AnTaChannelFlashColor, false, cRGBflashcolor, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), 0, 0, false, true, false);  
  }
  //sdSysData.booPulsesRunning = true;
}

// Pulse Color All Channels
void processcommandpulse(Console &cons, system_data &sdSysData, unsigned long tmeCurrentTime, timed_event teEvent[], CRGB cRGBpulsecolor)
{
  for (int channel = 0; channel < sdSysData.CONFIG.iNUM_CHANNELS; channel++)
  {
    teEvent[channel].set("Channel Light Pulse Color", tmeCurrentTime, 100, 0, 0, AnEvSchedule, AnTaChannelPulseColor, false, cRGBpulsecolor, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), 0, 0, false, true, false);  
  }
  sdSysData.booPulsesRunning = true;
}

// Pulse Color All Channels
void processcommandpulsecountdown(Console &cons, system_data &sdSysData, unsigned long tmeCurrentTime, timed_event teEvent[])
{
  for (int channel = 0; channel < sdSysData.CONFIG.iNUM_CHANNELS; channel++)
  {
    teEvent[channel].set("Channel Light Pulse Color", tmeCurrentTime, 100, 0, 0, AnEvSchedule, AnTaChannelPulseColorCountdown, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), 0, 0, false, true, false);  
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
    teEvent[channel].set("Overhead Illumination", tmeCurrentTime, 0, 1000, 80, AnEvSetToEnd, 0, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), 0, 255, true, true, false);
  }
  sdSysData.booOverheadRunning = false;
}

// -------------------------------------------------------------------------------------
// Overhead Illumination Color
void processcommandoverheadillum(Console &cons, system_data &sdSysData, unsigned long tmeCurrentTime, timed_event teEvent[], CRGB cRGBpulsecolor)
{
  for (int channel = 0; channel < sdSysData.CONFIG.iNUM_CHANNELS; channel++)
  {
    teEvent[channel].set("Overhead Illumination", tmeCurrentTime, 100, 0, 0, AnEvSchedule, AnTaOverheadIllumColor, false, cRGBpulsecolor, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), 0, 0, false, true, false);  
  }
  sdSysData.booOverheadRunning = true;
}

//  Overhead Illumination Pacificaish Color
void processcommandpacificaishcolor(Console &cons, system_data &sdSysData, unsigned long tmeCurrentTime, timed_event teEvent[], CRGB cRGBpulsecolor)
{
  for (int channel = 0; channel < sdSysData.CONFIG.iNUM_CHANNELS; channel++)
  {
    teEvent[channel].set("Overhead Illumination", tmeCurrentTime, 100, 0, 0, AnEvSchedule, AnTaPacificaishColor, false, cRGBpulsecolor, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), 0, 0, false, true, false);  
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
    teEvent[channel].set("Hazard", tmeCurrentTime, 0, 1000, 80, AnEvSetToEnd, 0, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), 0, 255, true, true, false);
  }
  sdSysData.booHazardRunning = false;
}

// Hazard
void processcommandhazard(Console &cons, system_data &sdSysData, unsigned long tmeCurrentTime, timed_event teEvent[], CRGB cRGBpulsecolor)
{
  for (int channel = 0; channel < sdSysData.CONFIG.iNUM_CHANNELS; channel++)
  {
    teEvent[channel].set("Hazard", tmeCurrentTime, 100, 0, 0, AnEvSchedule, AnTavdOverhead_Mask, false, cRGBpulsecolor, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), 0, 0, false, true, false);  
    teEvent[channel].set("Hazard", tmeCurrentTime, 100, 0, 0, AnEvSchedule, AnTaHazard, false, cRGBpulsecolor, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), 0, 0, false, true, false);  
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
    cons.printwait("CMD: " + cons.keywatch.Command.COMMANDLINE);
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


// Process and call routines as entered on the command line.
void processcommandlineinput(Console &cons, system_data &sdSysData, unsigned long tmeCurrentTime, timed_event teEvent[])
{
  COMMANDS command;
          
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
      processcommandpulseend(cons, sdSysData, tmeCurrentTime, teEvent);
      processcommandoverheadillumend(cons, sdSysData, tmeCurrentTime, teEvent);
      processcommandhazardend(cons, sdSysData, tmeCurrentTime, teEvent);
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
      command.shutdown_now();
      command_desc(cons, "Shutdown likely to have failed.");
    }

    // -------------------------------------------------------------------------------------
    // PLAYLIST

    if (check_command(cons, " playlist", "Current Playlist:"))
    {
      for (int x=0; x < cons.the_player.Play_List.size(); x++)
      {
        cons.printwait("  " + cons.the_player.Play_List.MOVIE_LIST[x]);
      }
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

    // pulse Running
    if (check_command(cons, "  ", "5 minute Pulse Timer Started with Running Color"))
    {
      sdSysData.start_timer(DEFAULTTIMER * 60);
      processcommandpulsecountdown(cons, sdSysData, tmeCurrentTime, teEvent);
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
    if(cons.keywatch.Command.COMMANDLINE == "o`")
    {
      // end all pulses on all strips
      cons.printwait("CMD: " + cons.keywatch.Command.COMMANDLINE);
      command_desc(cons, "Turn Off Overhead Illumination Lights");
      processcommandoverheadillumend(cons, sdSysData, tmeCurrentTime, teEvent);
      cons.keywatch.cmdClear();
    }

    // Overhead Running
    if((cons.keywatch.Command.COMMANDLINE == "oo") || (cons.keywatch.Command.COMMANDLINE == "zz"))
    {
      // Keep values below 128
      cons.printwait("CMD: " + cons.keywatch.Command.COMMANDLINE);
      command_desc(cons, "Turn On Overhead Illumination Lights with Running Color");
      processcommandpacificaishcolor(cons, sdSysData, tmeCurrentTime, teEvent, sdSysData.get_running_color());
      cons.keywatch.cmdClear();
    }

    // Overhead White
    if(cons.keywatch.Command.COMMANDLINE == "ow")
    {
      // Keep values below 128
      cons.printwait("CMD: " + cons.keywatch.Command.COMMANDLINE);
      command_desc(cons, "Turn On White Overhead Illumination Lights");
      processcommandpacificaishcolor(cons, sdSysData, tmeCurrentTime, teEvent, crgbWhite);
      cons.keywatch.cmdClear();
    }

    // Overhead Red
    if(cons.keywatch.Command.COMMANDLINE == "or")
    {
      // Keep values below 128
      cons.printwait("CMD: " + cons.keywatch.Command.COMMANDLINE);
      command_desc(cons, "Turn On Red Overhead Illumination Lights");
      processcommandpacificaishcolor(cons, sdSysData, tmeCurrentTime, teEvent, crgbRed);
      cons.keywatch.cmdClear();
    }

    // Overhead Green
    if(cons.keywatch.Command.COMMANDLINE == "og")
    {
      // Keep values below 128
      cons.printwait("CMD: " + cons.keywatch.Command.COMMANDLINE);
      command_desc(cons, "Turn On Green Overhead Illumination Lights");
      processcommandpacificaishcolor(cons, sdSysData, tmeCurrentTime, teEvent, crgbGreen);
      cons.keywatch.cmdClear();
    }

    // Overhead Blue
    if(cons.keywatch.Command.COMMANDLINE == "ob")
    {
      // Keep values below 128
      cons.printwait("CMD: " + cons.keywatch.Command.COMMANDLINE);
      command_desc(cons, "Turn On Blue Overhead Illumination Lights");
      processcommandpacificaishcolor(cons, sdSysData, tmeCurrentTime, teEvent, crgbBlue);
      cons.keywatch.cmdClear();
    }

    // Overhead Purple
    if(cons.keywatch.Command.COMMANDLINE == "ou")
    {
      // Keep values below 128
      cons.printwait("CMD: " + cons.keywatch.Command.COMMANDLINE);
      command_desc(cons, "Turn On Purple Overhead Illumination Lights");
      processcommandpacificaishcolor(cons, sdSysData, tmeCurrentTime, teEvent, crgbPurple);
      cons.keywatch.cmdClear();
    }

    // Overhead Yellow
    if(cons.keywatch.Command.COMMANDLINE == "oy")
    {
      // Keep values below 128
      cons.printwait("CMD: " + cons.keywatch.Command.COMMANDLINE);
      command_desc(cons, "Turn On Yellow Overhead Illumination Lights");
      processcommandpacificaishcolor(cons, sdSysData, tmeCurrentTime, teEvent, crgbYellow);
      cons.keywatch.cmdClear();
    }

    // Overhead Cyan
    if(cons.keywatch.Command.COMMANDLINE == "oc")
    {
      // Keep values below 128
      cons.printwait("CMD: " + cons.keywatch.Command.COMMANDLINE);
      command_desc(cons, "Turn On Cyan Overhead Illumination Lights");
      processcommandpacificaishcolor(cons, sdSysData, tmeCurrentTime, teEvent, crgbCyan);
      cons.keywatch.cmdClear();
    }

    // Overhead Orange
    if(cons.keywatch.Command.COMMANDLINE == "on")
    {
      // Keep values below 128
      cons.printwait("CMD: " + cons.keywatch.Command.COMMANDLINE);
      command_desc(cons, "Turn On Orange Overhead Illumination Lights");
      processcommandpacificaishcolor(cons, sdSysData, tmeCurrentTime, teEvent, crgbOrange);
      cons.keywatch.cmdClear();
    }

    // Set Running Color
    if(cons.keywatch.Command.COMMANDLINE == "rw")
    {
      sdSysData.set_running_color(crgbWhite, "White");
      cons.printwait("CMD: " + cons.keywatch.Command.COMMANDLINE);
      command_desc(cons, "Set Running Color to White");
      cons.keywatch.cmdClear();
    }

    if(cons.keywatch.Command.COMMANDLINE == "rr")
    {
      sdSysData.set_running_color(crgbRed, "Red");
      cons.printwait("CMD: " + cons.keywatch.Command.COMMANDLINE);
      command_desc(cons, "Set Running Color to Red");
      cons.keywatch.cmdClear();
    }
    
    if(cons.keywatch.Command.COMMANDLINE == "rg")
    {
      sdSysData.set_running_color(crgbGreen, "Green");
      cons.printwait("CMD: " + cons.keywatch.Command.COMMANDLINE);
      command_desc(cons, "Set Running Color to Green");
      cons.keywatch.cmdClear();
    }
    
    if(cons.keywatch.Command.COMMANDLINE == "rb")
    {
      sdSysData.set_running_color(crgbBlue, "Blue");
      cons.printwait("CMD: " + cons.keywatch.Command.COMMANDLINE);
      command_desc(cons, "Set Running Color to Blue");
      cons.keywatch.cmdClear();
    }
    
    if(cons.keywatch.Command.COMMANDLINE == "ru")
    {
      sdSysData.set_running_color(crgbPurple, "Purple");
      cons.printwait("CMD: " + cons.keywatch.Command.COMMANDLINE);
      command_desc(cons, "Set Running Color to Purple");
      cons.keywatch.cmdClear();
    }
    
    if(cons.keywatch.Command.COMMANDLINE == "ry")
    {
      sdSysData.set_running_color(crgbYellow, "Yellow");
      cons.printwait("CMD: " + cons.keywatch.Command.COMMANDLINE);
      command_desc(cons, "Set Running Color to Yellow");
      cons.keywatch.cmdClear();
    }
    
    if(cons.keywatch.Command.COMMANDLINE == "rc")
    {
      sdSysData.set_running_color(crgbCyan, "Cyan");
      cons.printwait("CMD: " + cons.keywatch.Command.COMMANDLINE);
      command_desc(cons, "Set Running Color to Cyan");
      cons.keywatch.cmdClear();
    }
    
    if(cons.keywatch.Command.COMMANDLINE == "rn")
    {
      sdSysData.set_running_color(crgbOrange, "Orange");
      cons.printwait("CMD: " + cons.keywatch.Command.COMMANDLINE);
      command_desc(cons, "Set Running Color to Orange");
      cons.keywatch.cmdClear();
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
    if(cons.keywatch.Command.COMMANDLINE == "h`")
    {
      // end all pulses on all strips
      cons.printwait("CMD: " + cons.keywatch.Command.COMMANDLINE);
      command_desc(cons, "HAZARD LIGHTS ON ('h`' to turn off");
      processcommandhazardend(cons, sdSysData, tmeCurrentTime, teEvent);
      cons.keywatch.cmdClear();
    }

    // Hazard
    if(cons.keywatch.Command.COMMANDLINE == "hh")
    {
      // Keep values below 128
      cons.printwait("CMD: " + cons.keywatch.Command.COMMANDLINE);
      command_desc(cons, "HAZARD LIGHTS OFF");
      processcommandhazard(cons, sdSysData, tmeCurrentTime, teEvent, crgbWhite);
      cons.keywatch.cmdClear();
    }
  
    // -------------------------------------------------------------------------------------
    // Debug Characters only active when debug mode is on
    // debug
    if(cons.keywatch.Command.COMMANDLINE[0] == KEYDEBUG)
    {
      cons.printwait("CMD: " + cons.keywatch.Command.COMMANDLINE);
      command_desc(cons, "Debug mode On/Off Toggle");
      cons.keywatch.in(KEYDEBUG);
      cons.keywatch.cmdClear();
    }

    // Only accept debug keys if debug is on.
    if (cons.keywatch.getnoreset(KEYDEBUG) == 1)
    {
      // Run Test Animation
      if(cons.keywatch.Command.COMMANDLINE[0] == KEYTESTANIM)
      {
        cons.printwait("CMD: " + cons.keywatch.Command.COMMANDLINE);
        processtestanimation(cons, sdSysData, tmeCurrentTime, teEvent, crgbWhite);
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