// ***************************************************************************************
// *
// *    Core       | Everything within this document is proprietary to Core Dynamics.
// *    Dynamics   | Any unauthorized duplication will be subject to prosecution.
// *
// *    Department : (R+D)^2                        Name: screen3.h
// *       Sub Dept: Programming
// *    Location ID: 856-45B
// *                                                      (c) 2856 - 2858 Core Dynamics
// ***************************************************************************************

#ifndef SCREEN3_H
#define SCREEN3_H

// Standard Header Files
#include <stdio.h>
#include <ncurses.h>
#include <string.h>
#include <deque>

#include "helper_ncurses.h"
#include "stringthings.h"
#include "system.h"
#include "consoleanddata.h"
#include "player.h"
#include "gadgets.h"
#include "radio_channel_coordinator.h"

using namespace std;

// ---------------------------------------------------------------------------------------
class Screen3
// Color tty interface with main touch control buttons on right side. Large so they can be 
//  accessed in moving vehicle without difficulty.  Limited access to main program and 
//  communicates through the command line to avoid confusion if a more advanced interface 
//  is created in the futer.
//  Button Control is managed by consoleanddata mouse input.
//  Current screen status is manage through system
{
  private:
  // Keyboard input variable
  int key = -1;

  bool Supports_Color = false;


  // Window Configuration
  //   Y
  //   S   v-----------XMax-------------------v
  //   t  > __________________________________    <
  //   a  ||                            |     |   |
  //   t  ||       winStatus            |  w  |   |
  //   u  ||                            |  i  |   |Y
  //   s  >|____________________________|  n  |   |M
  //      ||                            |  B  |   |a
  //      ||                            |  u  |   |x
  //   Y  ||                            |  t  |   |
  //   C  ||                            |  t  |   |
  //   o  ||      tbConsole             |  o  |   |
  //   n  ||                            |  n  |   |
  //   s  ||                            |  s  |   |
  //   o  ||                            |     |   |
  //   l  ||                            |     |   |
  //   e  >|____________________________|_____|   <
  //                                    ^-----^ XButtons
  //       ^-------XStatus--------------^
  //

  // ----------
  // Title Size
  int TitleSize = 10;

  // Screen Size Variables
  int YMax = 0;
  int XMax = 0;

  // Status Screen Variables --------------------
  int YStatusPos = 0;
  int XStatusPos = 0;
  int YStatusSize = 2;
  int XStatusSize = -1;

  WINDOW * winStatus;
  Title_Bar tiStatus;

  // Buttons Screen Variables --------------------
  int YButtonPos = 0;
  int XButtonPos = 0;
  int YButtonSize = 4;
  int XButtonSize = 8;

  public:
  Button_Zone_Manager bzButtons;
  private:

  // Debug Screen Variables --------------------
  int YDebugPos = -1;
  int XDebugPos = 0;
  int YDebugSize = 3;
  int XDebugSize = -1;

  WINDOW * winDebug;
  Title_Bar tiDebug;

  // Player Debug Counters
  bool Player_Frame_Counter = false;
  int Player_Frame_Count = 0;

  BAR Compute_Time;
  BAR Sleep_Time;
  BAR Cycle_Time;

  // Timer Screen Variables --------------------
  int YTimerPos = -1;
  int XTimerPos = 0;
  int YTimerSize = 3;
  int XTimerSize = -1;

  WINDOW * winTimer;
  Title_Bar tiTimer;

  BAR Countdown_Timer;

  // Color Picker Variables --------------------
  int YCPickerPos = -1;
  int XCPickerPos = -1;
  int YCPickerSize = 3;
  int XCPickerSize = 6;

  WINDOW * winCPicker;

  public:
  Button_Zone_Manager bzCPicker;
  private:

  // Tabs Variables --------------------
  int YTabPos = -1;
  int XTabPos = 0;
  int YTabSize = 2;
  int XTabSize = 12;

  public:
  Button_Zone_Manager bzTabs;
  private:

  // Console Screen Variables --------------------
  int YConsolePos = -1;
  int XConsolePos = 0;
  int YConsoleSize = -1;
  int XConsoleSize = -1;

  public:
  Text_Box tbConsole;
  private:
  Title_Bar tiConsole;

  // Player Screen Variables --------------------
  int YPlayerPos = -1;
  int XPlayerPos = 0;
  int YPlayerSize = -1;
  int XPlayerSize = -1;

  WINDOW * winPlayer;

  // Radio Screen Variables --------------------
  int YRadioPos = -1;
  int XRadioPos = 0;
  int YRadioSize = -1;
  int XRadioSize = -1;

  int YBRadioSize = 4; // Radio Button Standard Sizes
  int XBRadioSize = 8;

  int YGadChannelSize = 4;  // Frequency Gadges Size
  int XGadChannelSize = -1;
  int YGadChannelPos = 0;  // Frequency Gadges Start Position
  int XGadChannelPos = 8;

  int YTRadio_LogSize = 5;

  WINDOW * winRadio;
  Title_Bar tiRadio;

  public:
  Button_Zone_Manager bzRadio;
  Text_Box            tbRadio_Log;

  Radio_Channel       Radio_Channel_0;
  Radio_Channel       Radio_Channel_1;
  Radio_Channel       Radio_Channel_2;
  Radio_Channel       Radio_Channel_3;
  Radio_Channel       Radio_Channel_4;
  Radio_Channel       Radio_Channel_5;

  // Radio Status
  int YRadioStatusPos = -1;
  int XRadioStatusPos = 0;
  int YRadioStatusSize = 1;
  int XRadioStatusSize = -1;

  WINDOW * winRadioStatus;

  private:
  
  // --------------------
  // NCurses Window Variables
  string strBotLine;
  
  // Monitor these varibles for changes to update their corres buttons.
  VAR_CHANGE_MON vcmTIMER;
  VAR_CHANGE_MON vcmMENUOVERHEAD;

  string strBuffer = "";      // Buffer string containing a movie frame to be printed.
  
  public:

  bool buffer_active = false; // Set to true when a buffer has a new movie frame. 


  void buttons_menu_home(system_data &sdSysData)
  // Define control buttons and load them to the 
  //  button zone.
  // Main Buttons (Top)
  {
    bzButtons.modify(0, "TIMER", "%Start%Timer", int(sdSysData.cdTIMER.is_active()), 1, CRT_get_color_pair(COLOR_YELLOW, COLOR_WHITE), 0);
    bzButtons.modify(1, "", "", 0, -1, 6, 0);
    //bzButtons.modify(2, "MENUOVERHEAD", "Over%Head%Lights", 0, 0, CRT_get_color_pair(COLOR_YELLOW, COLOR_WHITE), 0);
    bzButtons.modify(2, "MENUOVERHEAD", "Over%Head%Lights", int(sdSysData.booOverheadRunning), 1, CRT_get_color_pair(COLOR_YELLOW, COLOR_WHITE), 0);
    bzButtons.modify(3, "FLASH", "%Flash", 0, 0, CRT_get_color_pair(COLOR_GREEN, COLOR_WHITE), 0);
    bzButtons.modify(4, "", "", 0, -1, 6, 0);
    bzButtons.modify(5, "CLEARANIMS", "%Clear%Anims", 0, 0, CRT_get_color_pair(COLOR_GREEN, COLOR_WHITE), 0);
    bzButtons.modify(6, "MENUCONTROL", "%...", 0, 0, CRT_get_color_pair(COLOR_BLUE, COLOR_WHITE), 0);
  }

  void buttons_menu_control(system_data &sdSysData)
  // Define control buttons and load them to the 
  //  button zone.
  // RasFLED settings
  {
    bzButtons.modify(0, "HAZARD","%HAZARD", int(sdSysData.booHazardRunning), 1, CRT_get_color_pair(COLOR_RED, COLOR_WHITE), 0);
    bzButtons.modify(1, "", "", 0, -1, 6, 0);
    bzButtons.modify(2, "DAYNIGHT","%Day%Night",int(sdSysData.booDay_On), 1, CRT_get_color_pair(COLOR_GREEN, COLOR_WHITE), 0);
    bzButtons.modify(3, "RUNNINGCOLOR", "Set%Running%Color", 0, 0, CRT_get_color_pair(COLOR_YELLOW, COLOR_WHITE), 0);
    bzButtons.modify(4, "", "", 0, -1, 6, 0);
    bzButtons.modify(5, "MENUSYSTEM","%SYSTEM", 0, 0, CRT_get_color_pair(COLOR_BLUE, COLOR_WHITE), 0);
    bzButtons.modify(6, "MENUHOME", "%<--", 0, 0, CRT_get_color_pair(COLOR_BLUE, COLOR_WHITE), 0);

    // When first diplaying buttons, set its value to the value it represents.
    if (sdSysData.booDay_On == true)
    {
      bzButtons.change_label("DAYNIGHT", "%Day%Mode");
    }
    else
    {
      bzButtons.change_label("DAYNIGHT", "%Night%Mode");
    }
  }

  void buttons_menu_system(system_data &sdSysData)
  // Define control buttons and load them to the 
  //  button zone.
  // RasFLED advanced settings
  {
    bzButtons.modify(0, "EXIT", "%EXIT", 0, 0, CRT_get_color_pair(COLOR_RED, COLOR_WHITE), 0);
    bzButtons.modify(1, "SHUTDOWN_NOW", "%SYSTEM%SHUTDOWN", 0, 0, CRT_get_color_pair(COLOR_RED, COLOR_WHITE), 0);
    bzButtons.modify(2, "", "", 0, -1, 6, 0);
    bzButtons.modify(3, "DEBUG", "%DEBUG", 0, 0, CRT_get_color_pair(COLOR_YELLOW, COLOR_WHITE), 0);
    bzButtons.modify(4, "", "", 0, -1, 6, 0);
    bzButtons.modify(5, "", "", 0, -1, 6, 0);
    bzButtons.modify(6, "MENUHOME", "%<--", 0, 0, CRT_get_color_pair(COLOR_BLUE, COLOR_WHITE), 0);
  }

  void buttons_menu_overhead_color(system_data &sdSysData)
  // Define control buttons and load them to the 
  //  button zone.
  // Overhead activation and color picker.
  {
    bzButtons.modify(0, "", "", 0, -1, 6, 0);
    bzButtons.modify(1, "", "", 0, -1, 6, 0);
    bzButtons.modify(2, "OVERHEAD", "Over%Head%Lights", int(sdSysData.booOverheadRunning), 1, CRT_get_color_pair(COLOR_GREEN, COLOR_WHITE), 0);
    bzButtons.modify(3, "CHOSECOLOR", "%Chose%Color", 0, 0, CRT_get_color_pair(COLOR_YELLOW, COLOR_WHITE), 0);
    bzButtons.modify(4, "", "", 0, -1, CRT_get_color_pair(COLOR_BLUE, COLOR_WHITE), 0);
    bzButtons.modify(5, "", "", 0, -1, 6, 0);
    bzButtons.modify(6, "MENUHOME", "%<--", 0, 0, CRT_get_color_pair(COLOR_BLUE, COLOR_WHITE), 0);
  }

  void init()
  // Initialize the main screen for first start.  
  {
    cbreak();   // do not buffer input until cr.
    noecho();   // do not echo back pressed characters

    keypad(stdscr, true);      // Keypad mode for reported mouse events as KEY_MOUSE.

    // Don't mask any mouse events
    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);

    printf("\033[?1003h\n");  // Makes the terminal report mouse movement events.

    if(has_colors() == true)
    // Set color pairs to defined integers.
    //  First color foreground. Second color background.
    {
      Supports_Color = true;
      start_color();

      // The only corors available
      //  
      //  COLOR_BLACK
      //  COLOR_RED
      //  COLOR_GREEN
      //  COLOR_YELLOW
      //  COLOR_BLUE
      //  COLOR_MAGENTA
      //  COLOR_CYAN
      //  COLOR_WHITE

      // Create a map of all color pair combinations for reference.
      CRT_init_all_pairs();
    }
  }

  void set(system_data &sdSysData, ScreenStatus &ScrStat)
  // Set the screen and defines its contents for first run. 
  // Call after the screen init.
  {

    // Build any Gadgets that will be called.

    // Prep Status Screen Text Box.
    tiStatus.create(1, "STATUS", " STATUS", TitleSize, CRT_get_color_pair(COLOR_BLUE, COLOR_WHITE), 0);

    // Prep Console Screen Text Box.
    tbConsole.create(1, "CONSOLE", "Console", 0, CRT_get_color_pair(COLOR_BLACK, COLOR_WHITE), 0);
    tiConsole.create(1, "CONSOLE", "CONSOLE", TitleSize, CRT_get_color_pair(COLOR_BLACK, COLOR_WHITE), 0);

    // Prep Control Buttons for program start.
    bzButtons.create_button(0, "TIMER", "%Start%Timer", int(sdSysData.cdTIMER.is_active()), 1, CRT_get_color_pair(COLOR_YELLOW, COLOR_WHITE), 0);
    bzButtons.create_button(1, "", "", 0, -1, 6, 0);
    bzButtons.create_button(2, "MENUOVERHEAD", "Over%Head%Lights", int(sdSysData.booOverheadRunning), 1, CRT_get_color_pair(COLOR_YELLOW, COLOR_WHITE), 0);
    bzButtons.create_button(3, "FLASH", "%Flash", 0, 0, CRT_get_color_pair(COLOR_GREEN, COLOR_WHITE), 0);
    bzButtons.create_button(4, "", "", 0, -1, 6, 0);
    bzButtons.create_button(5, "CLEARANIMS", "%Clear%Anims", 0, 0, CRT_get_color_pair(COLOR_GREEN, COLOR_WHITE), 0);
    bzButtons.create_button(6, "MENUCONTROL", "%...", 0, 0, CRT_get_color_pair(COLOR_BLUE, COLOR_WHITE), 0);

    // Prep Color Picker Buttons, even thought they 
    //  aren't displayed at start.
    bzCPicker.create_button(0, "RED", "%r", 0, 0, CRT_get_color_pair(COLOR_RED, COLOR_WHITE), 0);
    bzCPicker.create_button(1, "GREEN", "%g", 0, 0, CRT_get_color_pair(COLOR_GREEN, COLOR_WHITE), 0);
    bzCPicker.create_button(2, "BLUE", "%b", 0, 0, CRT_get_color_pair(COLOR_BLUE, COLOR_WHITE), 0);
    bzCPicker.create_button(3, "PURPLE", "%u", 0, 0, CRT_get_color_pair(COLOR_MAGENTA, COLOR_WHITE), 0);
    bzCPicker.create_button(4, "YELLOW", "%y", 0, 0, CRT_get_color_pair(COLOR_YELLOW, COLOR_WHITE), 0);
    bzCPicker.create_button(5, "CYAN", "%c", 0, 0, CRT_get_color_pair(COLOR_CYAN, COLOR_WHITE), 0);
    bzCPicker.create_button(6, "ORANGE", "%n", 0, 0, CRT_get_color_pair(COLOR_YELLOW, COLOR_WHITE), 0);
    bzCPicker.create_button(7, "WHITE", "%w", 0, 0, CRT_get_color_pair(COLOR_WHITE, COLOR_BLACK), 0);

    // Prep Tab buttons for program first start
    bzTabs.create_button(0, "TABCONSOLE", "Console", 1, 2, CRT_get_color_pair(COLOR_BLUE, COLOR_WHITE), 0);
    bzTabs.create_button(1, "TABPLAYER", "Player", 0, 2, CRT_get_color_pair(COLOR_BLUE, COLOR_WHITE), 0);
    bzTabs.create_button(2, "TABRADIO", "Radio", 0, 2, CRT_get_color_pair(COLOR_BLUE, COLOR_WHITE), 0);

    // Countdown Screen
    // Countdown Timer
    tiTimer.create(1, "TIMER", "TIMER", TitleSize, CRT_get_color_pair(COLOR_GREEN, COLOR_WHITE), 0);

    Countdown_Timer.label("Timer: ");
    Countdown_Timer.label_size(13);
    Countdown_Timer.size(15);
    Countdown_Timer.max_value(75);
    Countdown_Timer.color_background(COLOR_YELLOW);
    Countdown_Timer.color_foreground(COLOR_WHITE);
    Countdown_Timer.print_value(false);

    // Debug Screen 
    // Compute Times
    tiDebug.create(1, "DEBUG", "DIAG", TitleSize, CRT_get_color_pair(COLOR_RED, COLOR_WHITE), 0);

    Compute_Time.label("Compute: ");
    Compute_Time.label_size(13);
    Compute_Time.size(15);
    Compute_Time.max_value(20);
    Compute_Time.color_background(COLOR_YELLOW);
    Compute_Time.color_foreground(COLOR_WHITE);
    Compute_Time.print_value(false);
    Compute_Time.print_min(true);
    Compute_Time.print_max(true);
    Compute_Time.min_max(true);
    Compute_Time.min_max_time_span(10000);

    // Program Sleep Times
    Sleep_Time.label("Sleep: ");
    Sleep_Time.label_size(13);
    Sleep_Time.size(15);
    Sleep_Time.max_value(20);
    Sleep_Time.color_background(COLOR_YELLOW);
    Sleep_Time.color_foreground(COLOR_WHITE);
    Sleep_Time.print_value(false);
    Sleep_Time.print_min(true);
    Sleep_Time.print_max(true);
    Sleep_Time.min_max(true);
    Sleep_Time.min_max_time_span(10000);

    // Program Sleep Times
    Cycle_Time.label("Cycle: ");
    Cycle_Time.label_size(13);
    Cycle_Time.size(15);
    Cycle_Time.max_value(20);
    Cycle_Time.color_background(COLOR_YELLOW);
    Cycle_Time.color_foreground(COLOR_WHITE);
    Cycle_Time.print_value(false);
    Cycle_Time.print_min(true);
    Cycle_Time.print_max(true);
    Cycle_Time.min_max(true);
    Cycle_Time.min_max_time_span(10000);
   
    // Prep Buttons for Radio screen.
    tbRadio_Log.create(1, "RADIO", "RADIO", 0, CRT_get_color_pair(COLOR_BLACK, COLOR_WHITE), 0);
    tiRadio.create(1, "RADIO", "RADIO", TitleSize, CRT_get_color_pair(COLOR_BLACK, COLOR_WHITE), 0);

    bzRadio.create_button(0, "RADIOOFF", "%OFF", 0, 0, CRT_get_color_pair(COLOR_RED, COLOR_WHITE), 0);
    //bzRadio.create_button(0, "AIRSTOP", "%OFF", 0, 0, CRT_get_color_pair(COLOR_RED, COLOR_WHITE), 0);
    bzRadio.create_button(1, "LAFS", "AIR%LAF%SCAN", 0, 0, CRT_get_color_pair(COLOR_BLUE, COLOR_WHITE), 0);
    bzRadio.create_button(2, "LAFM", "AIR%LAF%MULTI", 0, 0, CRT_get_color_pair(COLOR_BLUE, COLOR_WHITE), 0);
    bzRadio.create_button(3, "AIRSTOP", "%STOP", 0, -1, CRT_get_color_pair(COLOR_RED, COLOR_WHITE), 0);
    bzRadio.create_button(4, "E2", "", 0, -1, CRT_get_color_pair(COLOR_BLUE, COLOR_WHITE), 0);

    // Create Radio Channel Frequency gadgets.
    Radio_Channel_0.create(0, "FREQ_0", "Frequency 0", -1, COLOR_BLUE, COLOR_BLACK);
    Radio_Channel_1.create(1, "FREQ_1", "Frequency 1", -1, COLOR_BLUE, COLOR_BLACK);
    Radio_Channel_2.create(2, "FREQ_2", "Frequency 2", -1, COLOR_BLUE, COLOR_BLACK);
    Radio_Channel_3.create(3, "FREQ_3", "Frequency 3", -1, COLOR_BLUE, COLOR_BLACK);
    Radio_Channel_4.create(4, "FREQ_4", "Frequency 4", -1, COLOR_BLUE, COLOR_BLACK);
    Radio_Channel_5.create(5, "FREQ_5", "Frequency 5", -1, COLOR_BLUE, COLOR_BLACK);

    // Draw screen the entire screen.  reset is also 
    //  called when the screen is resized.  
    reset(ScrStat);
  }


  void reset(ScreenStatus &ScrStat)
  // Creates all windows on panel and sets all positions.
  //  To be called if panel sized changes or if windows are 
  //  opened or closed. 
  {
    // Clear the Screen
    clear();

    // Get Screen Size
    getmaxyx(stdscr, YMax, XMax);

    // Panel Setup
    //  Calculate Window Sizes and Start Positions progressively
    //  as the screen is drawn.

    // Screen split variables
    int YSplit = 0;
    int XSplit = 0;

    // Start first split at X button size
    XSplit = XMax - XButtonSize;

    // ---------------------------------------------------------------------------------------
    // Status Panel
    if (ScrStat.Window_Status == true)
    // Main Status Panel
    {
      // Calculate Size and Position
      YStatusPos = YStatusPos;
      XStatusPos = XStatusPos;
      YStatusSize = YStatusSize;
      XStatusSize = XSplit;

      // Build Window
      winStatus = newwin(YStatusSize, XStatusSize, YStatusPos, XStatusPos);
      tiStatus.move_resize(YStatusPos, XStatusPos, YStatusSize, XStatusSize);
      
      // Set Y Split
      YSplit = YSplit + YStatusSize;

      // Status Window Border
      wborder(winStatus,' ',' ',' ',' ',' ',' ',' ',' ') ;
      
      // Create Status Screen
      wrefresh(winStatus);

      // Set window color
      //wbkgd(winStatus, COLOR_PAIR(CRT_get_color_pair(COLOR_BLUE, COLOR_WHITE)));
      wbkgd(winStatus, COLOR_PAIR(CRT_get_color_pair(COLOR_BLUE, COLOR_WHITE)));
    }

    // ---------------------------------------------------------------------------------------
    // Buttons
    if (ScrStat.Window_Buttons == true)
    // Control Buttons
    {
      int YButtonPos = 0;
      int XButtonPos = XMax - XButtonSize;

      bzButtons.move_resize(0, (YButtonSize *0), XButtonPos, YButtonSize, XButtonSize);
      bzButtons.move_resize(1, (YButtonSize *1), XButtonPos, YButtonSize, XButtonSize);
      bzButtons.move_resize(2, (YButtonSize *2), XButtonPos, YButtonSize, XButtonSize);
      bzButtons.move_resize(3, (YButtonSize *3), XButtonPos, YButtonSize, XButtonSize);
      bzButtons.move_resize(4, (YButtonSize *4), XButtonPos, YButtonSize, XButtonSize);
      bzButtons.move_resize(5, (YButtonSize *5), XButtonPos, YButtonSize, XButtonSize);
      bzButtons.move_resize(6, (YButtonSize *6), XButtonPos, YButtonSize, XButtonSize);
    }

    // ---------------------------------------------------------------------------------------
    // Debug Panel
    if (ScrStat.Window_Debug == true)
    {
      // Calculate Size and Position
      YDebugPos = YSplit;
      XDebugPos = XDebugPos;
      YDebugSize = YDebugSize;
      XDebugSize = XSplit;

      // Build Window
      winDebug = newwin(YDebugSize, XDebugSize, YDebugPos, XDebugPos);
      tiDebug.move_resize(YDebugPos, XDebugPos, YDebugSize, XDebugSize);
      
      // Set Y Split
      YSplit = YSplit + YDebugSize;

      // Debug Window Border
      wborder(winDebug,' ',' ',' ',' ',' ',' ',' ',' ') ;
      
      // Create Debug Screen
      wrefresh(winDebug);

      // Set window color
      wbkgd(winDebug, COLOR_PAIR(CRT_get_color_pair(COLOR_RED, COLOR_WHITE)));
    }

    // ---------------------------------------------------------------------------------------
    // Color Picker Panel
    if (ScrStat.Window_CPicker == true)
    {
      // Recreate XSplit Size
      XSplit = XSplit - XCPickerSize * 2;

      // Calculate Size and Position
      YCPickerPos = YSplit;
      XCPickerPos = XSplit;

      // Prep Side Buttons
      bzCPicker.move_resize(0, YCPickerPos + (YCPickerSize *0), XCPickerPos + (XCPickerSize * 0), YCPickerSize, XCPickerSize);
      bzCPicker.move_resize(1, YCPickerPos + (YCPickerSize *0), XCPickerPos + (XCPickerSize * 1), YCPickerSize, XCPickerSize);
      bzCPicker.move_resize(2, YCPickerPos + (YCPickerSize *1), XCPickerPos + (XCPickerSize * 0), YCPickerSize, XCPickerSize);
      bzCPicker.move_resize(3, YCPickerPos + (YCPickerSize *1), XCPickerPos + (XCPickerSize * 1), YCPickerSize, XCPickerSize);
      bzCPicker.move_resize(4, YCPickerPos + (YCPickerSize *2), XCPickerPos + (XCPickerSize * 0), YCPickerSize, XCPickerSize);
      bzCPicker.move_resize(5, YCPickerPos + (YCPickerSize *2), XCPickerPos + (XCPickerSize * 1), YCPickerSize, XCPickerSize);
      bzCPicker.move_resize(6, YCPickerPos + (YCPickerSize *3), XCPickerPos + (XCPickerSize * 0), YCPickerSize, XCPickerSize);
      bzCPicker.move_resize(7, YCPickerPos + (YCPickerSize *3), XCPickerPos + (XCPickerSize * 1), YCPickerSize, XCPickerSize);
    }

    // ---------------------------------------------------------------------------------------
    // Timer Panel
    if (ScrStat.Window_Timer == true)
    {
      // Calculate Size and Position
      YTimerPos = YSplit;
      XTimerPos = XTimerPos;
      YTimerSize = YTimerSize;
      XTimerSize = XSplit;

      // Build Window
      winTimer = newwin(YTimerSize, XTimerSize, YTimerPos, XTimerPos);
      tiTimer.move_resize(YTimerPos, XTimerPos, YTimerSize, XTimerSize);

      // Set Y Split
      YSplit = YSplit + YTimerSize;

      // Timer Window Border
      wborder(winTimer,' ',' ',' ',' ',' ',' ',' ',' ') ;
      
      // Create Timer Screen
      wrefresh(winTimer);

      // Set window color
      // wbkgd(winTimer, COLOR_PAIR(5));  //  Set color in window.
    }

    // ---------------------------------------------------------------------------------------
    // Console Panel
    if (ScrStat.Window_Console == true)
    // Main Console Screen
    {
      // Calculate Size and Position
      YConsolePos = YSplit;
      XConsolePos = XConsolePos;
      YConsoleSize = YMax - YSplit - YTabSize;
      XConsoleSize =  XSplit;

      // Build Text Box
      tbConsole.move_resize(YConsolePos, XConsolePos, YConsoleSize, XConsoleSize);
      tiConsole.move_resize(YConsolePos, XConsolePos, YConsoleSize, XConsoleSize);
      
      // Set Y Split
      YSplit = YSplit + YConsoleSize;

      // the bottom line of the console.
      strBotLine = "";
      strBotLine = strBotLine.append(XConsoleSize-1, '_');

    }

    // ---------------------------------------------------------------------------------------
    // Player Panel
    if (ScrStat.Window_Player == true)
    // Main Player Screen
    {
      // Calculate Size and Position
      YPlayerPos = YSplit;
      XPlayerPos = XPlayerPos;
      YPlayerSize = YMax - YSplit - YTabSize;
      XPlayerSize =  XSplit;

      // Build Window
      winPlayer = newwin(YPlayerSize, XPlayerSize, YPlayerPos, XPlayerPos);
      
      // Set Y Split
      YSplit = YSplit + YPlayerSize;

      // Player Window Border
      wborder(winPlayer,' ',' ',' ',' ',' ',' ',' ',' ') ;

      // Create Player Screen
      wrefresh(winPlayer);

      // Set window color
      wbkgd(winPlayer, COLOR_PAIR(0));

      // the bottom line of the Player.
      strBotLine = "";
      strBotLine = strBotLine.append(XPlayerSize-1, '_');
    }

    
    // ---------------------------------------------------------------------------------------
    // Radio Panel
    if (ScrStat.Window_Radio == true)
    // Main Radio Screen
    {
      // Radio Status Window
      // Calculate Size and Position
      YRadioStatusPos = YSplit;
      XRadioStatusPos = XRadioStatusPos;
      YRadioStatusSize = YRadioStatusSize;
      XRadioStatusSize =  XSplit;

      // Build Window
      winRadioStatus = newwin(YRadioStatusSize, XRadioStatusSize, YRadioStatusPos, XRadioStatusPos);
      tiRadio.move_resize(YRadioStatusPos, XRadioStatusPos, YRadioStatusSize, XRadioStatusSize);
      
      // Set Y Split
      YSplit = YSplit + YRadioStatusSize;

      // Create Screen
      wrefresh(winRadioStatus);

      // Set window color
      wbkgd(winRadioStatus, COLOR_PAIR(CRT_get_color_pair(COLOR_BLUE, COLOR_WHITE)));

      // Radio Window
      // Calculate Size and Position
      YRadioPos = YSplit;
      XRadioPos = XRadioPos;
      YRadioSize = YMax - YSplit - YTabSize;
      XRadioSize =  XSplit;

      YSplit = YSplit + YRadioStatusSize;

      // Build Window
      winRadio = newwin(YRadioSize, XRadioSize, YRadioPos, XRadioPos);

      // Set Y Split
      YSplit = YSplit + YRadioSize;

      // Radio Window Border
      wborder(winRadio,' ',' ',' ',' ',' ',' ',' ',' ') ;

      // Create Screen
      wrefresh(winRadio);

      // Set window color
      wbkgd(winRadio, COLOR_PAIR(0));

      // the bottom line of the Radio.
      strBotLine = "";
      strBotLine = strBotLine.append(XRadioSize-1, '_');

      // Prep Radio Buttons
      bzRadio.move_resize(0, YRadioPos + (YBRadioSize *0), XRadioPos, YBRadioSize, XBRadioSize);
      bzRadio.move_resize(1, YRadioPos + (YBRadioSize *1), XRadioPos, YBRadioSize, XBRadioSize);
      bzRadio.move_resize(2, YRadioPos + (YBRadioSize *2), XRadioPos, YBRadioSize, XBRadioSize);
      bzRadio.move_resize(3, YRadioPos + (YBRadioSize *3), XRadioPos, YBRadioSize, XBRadioSize);
      bzRadio.move_resize(4, YRadioPos + (YBRadioSize *4), XRadioPos, YBRadioSize, XBRadioSize);

      // Display Channels
      Radio_Channel_0.move_resize(YRadioPos + YGadChannelPos + (YGadChannelSize *0), XRadioPos + XGadChannelPos, YGadChannelSize, XRadioSize - XGadChannelPos);
      Radio_Channel_1.move_resize(YRadioPos + YGadChannelPos + (YGadChannelSize *1), XRadioPos + XGadChannelPos, YGadChannelSize, XRadioSize - XGadChannelPos);
      Radio_Channel_2.move_resize(YRadioPos + YGadChannelPos + (YGadChannelSize *2), XRadioPos + XGadChannelPos, YGadChannelSize, XRadioSize - XGadChannelPos);
      Radio_Channel_3.move_resize(YRadioPos + YGadChannelPos + (YGadChannelSize *3), XRadioPos + XGadChannelPos, YGadChannelSize, XRadioSize - XGadChannelPos);
      Radio_Channel_4.move_resize(YRadioPos + YGadChannelPos + (YGadChannelSize *4), XRadioPos + XGadChannelPos, YGadChannelSize, XRadioSize - XGadChannelPos);
      Radio_Channel_5.move_resize(YRadioPos + YGadChannelPos + (YGadChannelSize *5), XRadioPos + XGadChannelPos, YGadChannelSize, XRadioSize - XGadChannelPos);
      
      // Display OS Log
      tbRadio_Log.move_resize(YRadioPos + YRadioSize - YTRadio_LogSize, 0, YTRadio_LogSize, XRadioSize);

    }

    // ---------------------------------------------------------------------------------------
    // Tabs Panel
    if (ScrStat.Window_Tabs == true)
    {
      // Calculate Size and Position
      YSplit = YMax - YTabSize;

      YTabPos = YSplit;
      XTabPos = XTabPos;

      // Prep Tab Buttons
      bzTabs.move_resize(0, YTabPos + (YTabSize *0), XTabPos + (XTabSize * 0), YTabSize, XTabSize);
      bzTabs.move_resize(1, YTabPos + (YTabSize *0), XTabPos + (XTabSize * 1), YTabSize, XTabSize);
      bzTabs.move_resize(2, YTabPos + (YTabSize *0), XTabPos + (XTabSize * 2), YTabSize, XTabSize);

      // Set Y Split
      YSplit = YSplit + YTabSize;
    }

    // probably does something for the tty terminal.  probably should have 
    //  commented it when i reseached and wrote it.
    nodelay(stdscr, true);
  }
  // ---------------------------------------------------------------------------------------

  // ---------------------------------------------------------------------------------------
  void output_status(system_data &sdSysData, Keys &keywatch, ScreenStatus &ScrStat, TheMouse &mouse)
  // Displays command line input, status and door indicators
  {
    // Display Command Line
    if (keywatch.cmdPressed() == true || ScrStat.Needs_Refresh == true)
    {
      if (keywatch.cmdCleared() == true || ScrStat.Needs_Refresh == true)
      {
        // Blank out the line before redraw.
        wmove(winStatus, 0, 1);
        mvwprintw(winStatus, 0, 1, "CMD: __________");
      }
      mvwprintw(winStatus, 0, 1, "CMD: %s", keywatch.cmdRead().c_str());
    }

    //Display Door Statuses, highlighting values that are on (doors open)
    if (sdSysData.CONFIG.vSWITCH_PIN_MAP.at(0).value == true) {wattron(winStatus, A_REVERSE);}
    mvwprintw(winStatus, 1, 37, " Door1 ");
    if (sdSysData.CONFIG.vSWITCH_PIN_MAP.at(0).value == true) {wattroff(winStatus, A_REVERSE);}
    
    if (sdSysData.CONFIG.vSWITCH_PIN_MAP.at(1).value == true) {wattron(winStatus, A_REVERSE);}
    mvwprintw(winStatus, 0, 37, " Door2 ");
    if (sdSysData.CONFIG.vSWITCH_PIN_MAP.at(1).value == true) {wattroff(winStatus, A_REVERSE);}
    
    if (sdSysData.CONFIG.vSWITCH_PIN_MAP.at(2).value == true) {wattron(winStatus, A_REVERSE);}
    mvwprintw(winStatus, 1, 44, " Door3 ");
    if (sdSysData.CONFIG.vSWITCH_PIN_MAP.at(2).value == true) {wattroff(winStatus, A_REVERSE);}

    if (sdSysData.CONFIG.vSWITCH_PIN_MAP.at(3).value == true) {wattron(winStatus, A_REVERSE);}
    mvwprintw(winStatus, 0, 44, " Door4 ");
    if (sdSysData.CONFIG.vSWITCH_PIN_MAP.at(3).value == true) {wattroff(winStatus, A_REVERSE);}

    // Display Day or Night mode toggle.
    if(sdSysData.booDay_On == true)
    {
      //init_pair(1, COLOR_WHITE, COLOR_BLUE);
      //wattron(winStatus, COLOR_PAIR(1));
      wattron(winStatus, A_REVERSE);
      mvwprintw(winStatus, 0, 29, "  DAY  ");
      wattroff(winStatus, A_REVERSE);
      //wattroff(winStatus, COLOR_PAIR(1));
    }
    else
    {
      mvwprintw(winStatus, 0, 29, " NIGHT ");      
    }

    // Display Hazard Indicator
    if(sdSysData.booHazardRunning == true)
    {
      wattron(winStatus, A_REVERSE);
      mvwprintw(winStatus, 1, 18, "  HAZARD  ");
      wattroff(winStatus, A_REVERSE);
    }
    else
    {
      mvwprintw(winStatus, 1, 18, "  HAZARD  "); 
    }

    // Display Overhead Indicator
    if(sdSysData.booOverheadRunning == true)
    {
      wattron(winStatus, A_REVERSE);
      mvwprintw(winStatus, 0, 18, " OVERHEAD ");
      wattroff(winStatus, A_REVERSE);
    }
    else
    {
      mvwprintw(winStatus, 0, 18, " OVERHEAD "); 
    }

    // Display Timer Indicator
    if(sdSysData.cdTIMER.is_active() == true)
    {
      wattron(winStatus, A_REVERSE);
      mvwprintw(winStatus, 1, 29, " TIMER ");
      wattroff(winStatus, A_REVERSE);
    }
    else
    {
      mvwprintw(winStatus, 1, 29, " TIMER "); 
    }

    /*
    // Display Undervoltage
    if (sdSysData.hsHardware_Status.enabled() == true)
    {
      if (sdSysData.hsHardware_Status.get_low_voltage() != 0)
      {
        mvwprintw(winStatus, 0, XStatusSize - 13, "%3.3f", sdSysData.hsHardware_Status.get_low_voltage());
      }
    }
    */

    // Display CPU Temp
    if (sdSysData.hsHardware_Status.enabled() == true)
    {
      mvwprintw(winStatus, 1, XStatusSize - 5, "%3.0fc", sdSysData.hsHardware_Status.get_temperature());
    }
    else
    {
      mvwprintw(winStatus, 1, XStatusSize - 12, "NA");
    }

    // Commit all our changes to the status portion of the screen (winTop)
    wrefresh(winStatus);
    tiStatus.draw(ScrStat.Needs_Refresh);
  }

  // ---------------------------------------------------------------------------------------
  void output_debug2(system_data &sdSysData, Keys &keywatch, ScreenStatus &ScrStat, TheMouse &mouse)
  // Displays clock timings, event count, and mouse info.
  {
    string strRange = "";
    string strLevel = "";

    // Print Timings
    Compute_Time.label("Compute: " + to_string(sdSysData.dblCOMPUTETIME.data) + " ");
    Compute_Time.guage_bar(winDebug, 0, 7, sdSysData.dblCOMPUTETIME.data, sdSysData.tmeCURRENT_FRAME_TIME);
    
    Sleep_Time.label("Sleep:   " + to_string(sdSysData.dblPREVSLEEPTIME.data) + " ");
    Sleep_Time.guage_bar(winDebug, 1, 7, sdSysData.dblPREVSLEEPTIME.data, sdSysData.tmeCURRENT_FRAME_TIME);
    
    Cycle_Time.label("Cycle:   " + to_string(sdSysData.dblCYCLETIME.data) + " ");
    Cycle_Time.guage_bar(winDebug, 2, 7, sdSysData.dblCYCLETIME.data, sdSysData.tmeCURRENT_FRAME_TIME);
    
    //------------------------
    // Print LED Display Mode
    // Displaying LEDs selected to be displayed CYCLE selected.
    if (keywatch.get(KEYLEDTEST) == 1)
    {
      strRange = "Fi";
      strLevel = "ll";
    }
    else if (keywatch.get(KEYLEDDRCYCL) == 0)
    {
      strRange = "EA";
      strLevel = "  ";
    }
    else
    {
      strRange = "E" + to_string(keywatch.get(KEYLEDDRCYCL)-1);
      strLevel = to_string(sdSysData.t_group) + to_string(sdSysData.t_strip);
    }

    // Draw RANGE and UPPER OR LOWER VALUES selected.
    mvwprintw(winDebug, 0, 0, "RNG:%s", strRange.c_str());
    mvwprintw(winDebug, 1, 0, "LVL:%s", strLevel.c_str());
    //------------------------

    // Show Number of Events per Channel
    mvwprintw(winDebug, 1, 50, "%03d:D1", sdSysData.intCHANNEL_GROUP_EVENTS_COUNTS.at(0));
    mvwprintw(winDebug, 0, 50, "%03d:D2", sdSysData.intCHANNEL_GROUP_EVENTS_COUNTS.at(1));
    mvwprintw(winDebug, 1, 57, "D3:%03d", sdSysData.intCHANNEL_GROUP_EVENTS_COUNTS.at(2));
    mvwprintw(winDebug, 0, 57, "D4:%03d", sdSysData.intCHANNEL_GROUP_EVENTS_COUNTS.at(3));
    
    //------------------------
    //Mouse Position
    mvwprintw(winDebug, 1, XStatusSize - 14, "Mouse: %03d %03d",mouse.x(),mouse.y());

    //------------------------
    wrefresh(winDebug);
    tiDebug.draw(ScrStat.Needs_Refresh);
  }

  // ---------------------------------------------------------------------------------------
  void output_timer(system_data &sdSysData, Keys &keywatch, ScreenStatus &ScrStat, TheMouse &mouse)
  // Displays first countdown timer.
  {
    long elaped_time = 0;
    unsigned long duration_time = 0;
    long remaining_time = 0;

    // Set window color
    wbkgd(winTimer, COLOR_PAIR(CRT_get_color_pair(COLOR_GREEN, COLOR_WHITE)));

    // Calculate
    duration_time = sdSysData.cdTIMER.duration();
    elaped_time = sdSysData.cdTIMER.elapsed_time(sdSysData.tmeCURRENT_FRAME_TIME);
    remaining_time = duration_time - elaped_time;

    // Display Timer
    string mins = linemerge_right_justify(2, "00", to_string(millis_to_time_minutes(remaining_time)));
    string secs = linemerge_right_justify(2, "00", to_string(millis_to_time_seconds(remaining_time)));

    Countdown_Timer.label("Timer: " + mins + ":" + secs + " ");
    Countdown_Timer.max_value(duration_time);
    Countdown_Timer.progress_bar(winTimer, 1, 2, duration_time - elaped_time);

    //------------------------
    wrefresh(winTimer);
    tiTimer.draw(ScrStat.Needs_Refresh);
  }
  
  // ---------------------------------------------------------------------------------------
  void printout(ScreenStatus &ScrStat)
  // Displays console of commands ran, events starting and stoping, and other info.
  //  If console is on another tty through tty over ethernet or serial then a low 
  //    bandwith version will need to created.  Or, I put the console into its own 
  //    thread.  Whichever is necessary to develop or learn first.
  {
    if (tbConsole.PROP.CHANGED == true || ScrStat.Needs_Refresh == true)
    {
      tbConsole.draw(ScrStat.Needs_Refresh);
      tiConsole.draw(true);
    }

  }

  // ---------------------------------------------------------------------------------------
  void the_player(ScreenStatus &ScrStat)
  // Shows the Player Window
  {
    int yCurPos = 0;

    // Refresh the window.
    // wrefresh(winPlayer);
    
  }

  void window_player_clear()
  // clear the contents of the player window.
  {
    wclear(winPlayer);
  }

  void window_player_draw_frame(PLAYER_FRAME &qframe)
  //  Draw the window player qframe.  
  //  This routine is externally called at any time and its timing is not handled here.
  //  This routine will center the screen when its size is smaller than the display size.
  //  If the size is larger than the display size, it will not center, instead it will 
  //    only position itself in the upper left and truncate the bottom and right.
  {

    int ypos = 0;
    int xpos = 0;
    int lines_max = 0;
    int length_max = 0;

    strBuffer = "";         // Clear current buffer information before creating a new 
                            //  buffer frame.
    buffer_active = false;  // Clear the buffer active information.

    // Find upper left positions to print the screen.
    // Set the max size to be printed.
    if (qframe.HEIGHT > YPlayerSize)
    {
      ypos = 0;
      lines_max = YPlayerSize;
    }
    else
    {
      ypos = (YPlayerSize/2) - (qframe.HEIGHT/2);
      lines_max = qframe.HEIGHT;
    }

    if (qframe.WIDTH > XPlayerSize)
    {
      xpos = 0;
      length_max = XPlayerSize;
    }
    else
    {
      xpos = (XPlayerSize/2) - (qframe.WIDTH/2);
      length_max = qframe.WIDTH;
    }

    // Make sure the amount of lines are within range to avoid exception errors.
    // This routine is for program integrety safety.  There is a possibility 
    //    of a corrupt player file to not load the entire frame.
    if (lines_max > qframe.LINES.size())
    {
      lines_max = qframe.LINES.size();
    }

    for(int line=0; line < lines_max; line++)
    {
      /*
      wmove(winPlayer, line, 0);  //move cursor to next line to print or clear.
      wclrtoeol(winPlayer);            // clear line befor printing to it.
      mvwprintw(winPlayer, line, 0, "%s", qframe.LINES.front().c_str());
      qframe.LINES.pop_front();
      */

      if (qframe.TYPE == 1)
      {
        // Draw basic first iteration movie frame type with delay built in.
        //  Mananged by NCurses.

        wmove(winPlayer, line + ypos, xpos);  //move cursor to next line to print or clear.
        wclrtoeol(winPlayer);            // clear line befor printing to it.
        mvwprintw(winPlayer, line + ypos, xpos, "%s", qframe.LINES[line].c_str());

      }
      else if (qframe.TYPE == 1000)
      {
        // Draw second iteration frame type. Black and White text only.
        //  Mananged by NCurses.
        
        mvwprintw(winPlayer, line + ypos, xpos, "%s", qframe.LINES[line].c_str());

      }
      else if (qframe.TYPE == 1001)
      {
        // Draw third iteration frame type. Color by escape sequences.
        //  Not Mananged by NCurses.
        //  This routine is cheesed because for some reason NCurses cant handle 
        //  direct escape sequences to console. So...
        //    An escape sequence is made to position the cursor, then the line 
        //    read from file is tacked onto the end, followed by a \n.
        //    then the line is printed by a std printf.
        //  PROBLEMS:
        //    I have not validated the substring being printed does not contain 
        //    any unprinted escape sequences.
      
        // Find the position of the length position.

        int pos1            = 0;  //  Stores pos of last char to be displayed.

        string cursor_pos   = ""; //  Stores string containing cursor pos to print
                                  //    line.
        //string print_string = ""; //  Stores full line to be printed, including 
                                  //    moving cursor.
        
        // The line to print may be smaller than the display size. So, we need to 
        //  the position +1 of the last character to be printed. Because this is 
        //  not a simple character array, and is insted, a complex string including 
        //  escape characters, we will count escape character, and hold the pos 
        //  of the last found when the line length conditions were exceded. 
        pos1 = qframe.LINES[line].find("\e[", pos1);
        for (int x = 0; (x < length_max) && (pos1 != qframe.LINES[line].npos); x++)
        {
          pos1 = qframe.LINES[line].find("\e[", pos1 +1);
        }

        // Build cursor positioning escape sequence.
        cursor_pos = "\e[" + to_string(YPlayerPos +1 + ypos + line) + ";" 
                      + to_string(XPlayerPos +1 + xpos) + "f";

        // Bring back pos 1 if not at full length.
        if (pos1 == qframe.LINES[line].npos || length_max == XPlayerSize)
        {
          // Do nothing
        }
        else
        {
          pos1 = pos1 - 1;
        }

        // Set strBuffer var to be the cursor position escape sequence 
        //  combined with the substring, regarding length, of the line to be 
        //  printed.  Plus, whatever it was before.
        strBuffer = strBuffer + cursor_pos + qframe.LINES[line].substr(0,pos1);
      }
    }

    // If loop complete and TYPE is 1001, run these extra routines.
    if (qframe.TYPE == 1001)
    {
      // Append strBuffer with CRLF
      strBuffer = strBuffer + "\n";
      
      // The buffer was recently updated so set buffer active to true.
      buffer_active = true;
    }

    qframe.LINES.clear();

    if(Player_Frame_Counter == true)
    {
      // Print details about the player frame for debug purposes. 
      //  Only turned on at compile time.
      Player_Frame_Count++;
      mvwprintw(winPlayer, 0, 0, "%08d Count  ", Player_Frame_Count);
      mvwprintw(winPlayer, 1, 0, "%08d Width  ", qframe.WIDTH);
      mvwprintw(winPlayer, 2, 0, "%08d Height ", qframe.HEIGHT);
      mvwprintw(winPlayer, 3, 0, "%08d Delay  ", qframe.DELAY);
      mvwprintw(winPlayer, 4, 0, "%08d FPS    ", qframe.FPS);
      mvwprintw(winPlayer, 5, 0, "%08d Type   ", qframe.TYPE);
      mvwprintw(winPlayer, 6, 0, "                ");

    }

    //if (qframe.TYPE != 1001)  // Don't enable this. NCurses must be cleaing things
                                //  up.
    {
      // Update the player portion of the window. 
      wrefresh(winPlayer);

      // Since things were changed, we need to redraw the entire screen.
      refresh();
    }

  }

  string buffer()
  // Returns the value stored in the buffer.
  {
    return strBuffer;
  }

  
  // ---------------------------------------------------------------------------------------
  void radio(system_data &sdSysData, ScreenStatus &ScrStat)
  // Shows the Player Window
  {
    // Print Status
    if(ScrStat.Needs_Refresh == true || sdSysData.RADIO_COORD.DEVICE_STATUS.CHANGED == true)
    {
      if (sdSysData.RADIO_COORD.DEVICE_STATUS.ACTIVE == false)
      {
        wbkgd(winRadioStatus, COLOR_PAIR(CRT_get_color_pair(COLOR_YELLOW, COLOR_WHITE)));
      }
      else
      {
        wbkgd(winRadioStatus, COLOR_PAIR(CRT_get_color_pair(COLOR_BLUE, COLOR_WHITE)));
      }

      mvwprintw(winRadioStatus, 0, 10, "Gain: %.1f", sdSysData.RADIO_COORD.DEVICE_STATUS.GAIN);
      mvwprintw(winRadioStatus, 0, 0, "A%d", sdSysData.RADIO_COORD.DEVICE_STATUS.ACTIVE);
      mvwprintw(winRadioStatus, 0, 3, "C%d", sdSysData.RADIO_COORD.DEVICE_STATUS.CHANGED);
      mvwprintw(winRadioStatus, 0, 6, "B%d", sdSysData.RADIO_COORD.LAST_READ_BIND_COUNT);
    }

    if(ScrStat.Needs_Refresh == true || sdSysData.RADIO_COORD.DEVICE_STATUS.CHANGED == true)
    {
      // Refresh the window.
      wrefresh(winRadioStatus);

      // Refresh the window.
      wrefresh(winRadio);

      // Print Title Bar
      tiRadio.draw(ScrStat.Needs_Refresh);

      // Changes to Radio Coord cleared.
      sdSysData.RADIO_COORD.DEVICE_STATUS.CHANGED = false;
    }
    // Print Radio Information

    tbRadio_Log.draw(ScrStat.Needs_Refresh);

    bzRadio.draw(ScrStat.Needs_Refresh);
  
    // Print Channel Gadgets
    Radio_Channel_0.draw(ScrStat.Needs_Refresh, sdSysData.tmeCURRENT_FRAME_TIME);
    Radio_Channel_1.draw(ScrStat.Needs_Refresh, sdSysData.tmeCURRENT_FRAME_TIME);
    Radio_Channel_2.draw(ScrStat.Needs_Refresh, sdSysData.tmeCURRENT_FRAME_TIME);
    Radio_Channel_3.draw(ScrStat.Needs_Refresh, sdSysData.tmeCURRENT_FRAME_TIME);
    Radio_Channel_4.draw(ScrStat.Needs_Refresh, sdSysData.tmeCURRENT_FRAME_TIME);
    Radio_Channel_5.draw(ScrStat.Needs_Refresh, sdSysData.tmeCURRENT_FRAME_TIME);
    
  }

  // ---------------------------------------------------------------------------------------

  // ---------------------------------------------------------------------------------------
  // Main screen routine.
  // Draw the console, starting with status window, then whatever windows set to true.

  void output(system_data &sdSysData, Keys &keywatch, ScreenStatus &ScrStat, TheMouse &mouse)
  {
    // Run any routines that may cause the screen to need to be refreshed.

    // Button value follow ups.
    //  Sometimes things change.  Sometimes things change at strange times. 
    //  And the buttons need to reflect those status changes. But there is no way 
    //  for the buttons to know those changes occured because they have no active 
    //  communication to the variables they represent. So, they just stayed the way 
    //  they were when they were last intereacted with. I don't like these next few 
    //  lines, but they will solve the problem of buttons displaying the wrong status 
    //  until I find a way for the buttons to know that what they are representing 
    //  has changed.
    bzButtons.change_value("TIMER",int(sdSysData.cdTIMER.is_active()));
    bzButtons.change_value("MENUOVERHEAD",int(sdSysData.booOverheadRunning));

    // Check for Timer Window
    if (sdSysData.cdTIMER.is_active() == true)
    {
      ScrStat.Window_Timer_On();
    }
    else
    {
      ScrStat.Window_Timer_Off();
    }

    // ---------------------------------------------------------------------------------------
    // Check to see if the screen need to be rebuilt
    if (ScrStat.Needs_Refresh == true)
    {
      reset(ScrStat);
    }

    // ---------------------------------------------------------------------------------------
    // Draw the Screens

    // Draw Console window.
    if (ScrStat.Window_Console == true)
    {
      printout(ScrStat);
    }

    // Draw Player window.
    if (ScrStat.Window_Player == true)
    {
      the_player(ScrStat);
    }

    // Draw Radio window.
    if (ScrStat.Window_Radio == true)
    {
      radio(sdSysData, ScrStat);
    }

    // Buttons

    // Draw Tabs.
    if (ScrStat.Window_Tabs == true)
    {
      bzTabs.draw(ScrStat.Needs_Refresh);
    }

    // Draw buttons on buttons window.
    if (ScrStat.Window_Buttons == true)
    {
      bzButtons.draw(ScrStat.Needs_Refresh);
    }

    // Draw Color Picker window.
    if (ScrStat.Window_CPicker == true)
    {
      bzCPicker.draw(ScrStat.Needs_Refresh);
    }

    // Draw Statuses

    // Draw Timer window.
    if (ScrStat.Window_Timer == true)
    {
      output_timer(sdSysData, keywatch, ScrStat, mouse);
    }

    // Draw Debug window.
    if (ScrStat.Window_Debug == true)
    {
      output_debug2(sdSysData, keywatch, ScrStat, mouse);
    }

    // Draw Status window.
    if (ScrStat.Window_Status == true)
    {
      output_status(sdSysData, keywatch, ScrStat, mouse);
    }

    // ---------------------------------------------------------------------------------------
    // Draw all changes to the screen.
    // Clear Refresh varibles.
    refresh();
    ScrStat.Needs_Refresh = false;
  }
};




#endif