// ***************************************************************************************
// *
// *    Core       | Everything within this document is proprietary to Core Dynamics.
// *    Dynamics   | Any unauthorized duplication will be subject to prosecution.
// *
// *    Department : (R+D)^2                        Name: screen3.cpp
// *       Sub Dept: Programming
// *    Location ID: 856-45B
// *                                                      (c) 2856 - 2858 Core Dynamics
// ***************************************************************************************

#ifndef SCREEN3_CPP
#define SCREEN3_CPP

#include "screen3.h"

using namespace std;

void Screen3::buttons_menu_home(system_data &sdSysData)
// Define control buttons and load them to the 
//  button zone.
// Main Buttons (Top)
{
  bzButtons.set_name(0, "TIMER");
  bzButtons.set_label(0, "\nStart\nTimer");
  bzButtons.set_value(0, int(sdSysData.cdTIMER.is_active()));
  bzButtons.set_type(0, 1);
  bzButtons.set_color(0, COLOR_YELLOW, COLOR_WHITE);
  bzButtons.set_hidden(0, false);
  bzButtons.set_enabled(0, true);

  bzButtons.set_hidden(1, true);
  bzButtons.set_enabled(1, false);

  bzButtons.set_name(2, "MENUOVERHEAD");
  bzButtons.set_label(2, "Over\nHead\nLights");
  bzButtons.set_value(2, int(sdSysData.booOverheadRunning));
  bzButtons.set_type(2, 1);
  bzButtons.set_color(2, COLOR_YELLOW, COLOR_WHITE);
  bzButtons.set_hidden(2, false);
  bzButtons.set_enabled(2, true);

  bzButtons.set_name(3, "FLASH");
  bzButtons.set_label(3, "\nFlash");
  bzButtons.set_value(3, 0);
  bzButtons.set_type(3, 0);
  bzButtons.set_color(3, COLOR_GREEN, COLOR_WHITE);
  bzButtons.set_hidden(3, false);
  bzButtons.set_enabled(3, true);

  bzButtons.set_hidden(4, true);
  bzButtons.set_enabled(4, false);

  bzButtons.set_name(5, "LIGHTSOFF");
  bzButtons.set_label(5, "\nLIGHTS\nON");
  bzButtons.set_value(5, 0);
  bzButtons.set_type(5, 1);
  bzButtons.set_color(5, COLOR_RED, COLOR_WHITE);
  bzButtons.set_hidden(5, false);
  bzButtons.set_enabled(5, true);
  
  bzButtons.set_name(6, "MENUCONTROL");
  bzButtons.set_label(6, "\n...");
  bzButtons.set_value(6, 0);
  bzButtons.set_type(6, 0);
  bzButtons.set_color(6, COLOR_BLUE, COLOR_WHITE);
  bzButtons.set_hidden(6, false);
  bzButtons.set_enabled(6, true);
}

void Screen3::buttons_menu_control(system_data &sdSysData)
// Define control buttons and load them to the 
//  button zone.
// RasFLED settings
{
  bzButtons.set_name(0, "HAZARD");
  bzButtons.set_label(0, "\nHAZARD");
  bzButtons.set_value(0, int(sdSysData.booHazardRunning));
  bzButtons.set_type(0, 1);
  bzButtons.set_color(0, COLOR_RED, COLOR_WHITE);
  bzButtons.set_hidden(0, false);
  bzButtons.set_enabled(0, true);

  bzButtons.set_hidden(1, true);
  bzButtons.set_enabled(1, false);

  bzButtons.set_name(2, "DAYNIGHT");
  bzButtons.set_label(2, "\nDay\nNight");
  //bzButtons.set_value(2, int(sdSysData.booDay_On));
  bzButtons.set_value(2, int(sdSysData.Day_On_With_Override.value()));
  bzButtons.set_type(2, 1);
  bzButtons.set_color(2, COLOR_GREEN, COLOR_WHITE);
  if (sdSysData.Day_On_With_Override.overridden() == false)
  {
    bzButtons.set_hidden(2, false);
    bzButtons.set_enabled(2, true);
  }
  else
  {
    bzButtons.set_hidden(2, true);
    bzButtons.set_enabled(2, false);
  }
  

  bzButtons.set_name(3, "RUNNINGCOLOR");
  bzButtons.set_label(3, "Set\nRunning\nColor");
  bzButtons.set_value(3, 0);
  bzButtons.set_type(3, 0);
  bzButtons.set_color(3, COLOR_YELLOW, COLOR_WHITE);
  bzButtons.set_hidden(3, false);
  bzButtons.set_enabled(3, true);

  bzButtons.set_name(4, "CLEARANIMS");
  bzButtons.set_label(4, "\nClear\nAnims");
  bzButtons.set_value(4, 0);
  bzButtons.set_type(4, 0);
  bzButtons.set_color(4, COLOR_GREEN, COLOR_WHITE);
  bzButtons.set_hidden(4, false);
  bzButtons.set_enabled(4, true);

  bzButtons.set_name(5, "MENUSYSTEM");
  bzButtons.set_label(5, "\nSYSTEM");
  bzButtons.set_value(5, 0);
  bzButtons.set_type(5, 0);
  bzButtons.set_color(5, COLOR_BLUE, COLOR_WHITE);
  bzButtons.set_hidden(5, false);
  bzButtons.set_enabled(5, true);
  
  bzButtons.set_name(6, "MENUHOME");
  bzButtons.set_label(6, "\n<--");
  bzButtons.set_value(6, 0);
  bzButtons.set_type(6, 0);
  bzButtons.set_color(6, COLOR_BLUE, COLOR_WHITE);
  bzButtons.set_hidden(6, false);
  bzButtons.set_enabled(6, true);

  if (sdSysData.Day_On_With_Override.value() == true)
  {
    bzButtons.set_label("DAYNIGHT", "\nDay\nMode");
  }
  else
  {
    bzButtons.set_label("DAYNIGHT", "\nNight\nMode");
  }
}

void Screen3::buttons_menu_system(system_data &sdSysData)
// Define control buttons and load them to the 
//  button zone.
// RasFLED advanced settings
{
  bzButtons.set_name(0, "EXIT");
  bzButtons.set_label(0, "\nEXIT");
  bzButtons.set_value(0, 0);
  bzButtons.set_type(0, 0);
  bzButtons.set_color(0, COLOR_RED, COLOR_WHITE);
  bzButtons.set_hidden(0, false);
  bzButtons.set_enabled(0, true);

  bzButtons.set_name(1, "SHUTDOWN_NOW");
  bzButtons.set_label(1, "\nSYSTEM\nSHUTDOWN");
  bzButtons.set_value(1, 0);
  bzButtons.set_type(1, 0);
  bzButtons.set_color(1, COLOR_RED, COLOR_WHITE);
  bzButtons.set_hidden(1, false);
  bzButtons.set_enabled(1, true);
  
  bzButtons.set_name(2, "REBOOT");
  bzButtons.set_label(2, "\nSYSTEM\nREBOOT");
  bzButtons.set_value(2, 0);
  bzButtons.set_type(2, 0);
  bzButtons.set_color(2, COLOR_RED, COLOR_WHITE);
  bzButtons.set_hidden(2, false);
  bzButtons.set_enabled(2, true);

  bzButtons.set_name(3, "DEBUG");
  bzButtons.set_label(3, "\nDEBUG");
  bzButtons.set_value(3, 0);
  bzButtons.set_type(3, 0);
  bzButtons.set_color(3, COLOR_YELLOW, COLOR_WHITE);
  bzButtons.set_hidden(3, false);
  bzButtons.set_enabled(3, true);
  
  bzButtons.set_hidden(4, true);
  bzButtons.set_enabled(4, false);
  
  bzButtons.set_hidden(5, true);
  bzButtons.set_enabled(5, false);
  
  bzButtons.set_name(6, "MENUHOME");
  bzButtons.set_label(6, "\n<--");
  bzButtons.set_value(6, 0);
  bzButtons.set_type(6, 0);
  bzButtons.set_color(6, COLOR_BLUE, COLOR_WHITE);
  bzButtons.set_hidden(6, false);
  bzButtons.set_enabled(6, true);
}

void Screen3::buttons_menu_overhead_color(system_data &sdSysData)
// Define control buttons and load them to the 
//  button zone.
// Overhead activation and color picker.
{
  bzButtons.set_hidden(0, true);
  bzButtons.set_enabled(0, false);
  
  bzButtons.set_hidden(1, true);
  bzButtons.set_enabled(1, false);
  
  bzButtons.set_name(2, "OVERHEAD");
  bzButtons.set_label(2, "Over\nHead\nLights");
  bzButtons.set_value(2, int(sdSysData.booOverheadRunning));
  bzButtons.set_type(2, 1);
  bzButtons.set_color(2, COLOR_GREEN, COLOR_WHITE);
  bzButtons.set_hidden(2, false);
  bzButtons.set_enabled(2, true);
  
  bzButtons.set_name(3, "CHOSECOLOR");
  bzButtons.set_label(3, "\nChose\nColor");
  bzButtons.set_value(3, 0);
  bzButtons.set_type(3, 0);
  bzButtons.set_color(3, COLOR_YELLOW, COLOR_WHITE);
  bzButtons.set_hidden(3, false);
  bzButtons.set_enabled(3, true);
  
  bzButtons.set_hidden(4, true);
  bzButtons.set_enabled(4, false);
  
  bzButtons.set_hidden(5, true);
  bzButtons.set_enabled(5, false);
  
  bzButtons.set_name(6, "MENUHOME");
  bzButtons.set_label(6, "\n<--");
  bzButtons.set_value(6, 0);
  bzButtons.set_type(6, 0);
  bzButtons.set_color(6, COLOR_BLUE, COLOR_WHITE);
  bzButtons.set_hidden(6, false);
  bzButtons.set_enabled(6, true);
}

void Screen3::init()
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

void Screen3::set(system_data &sdSysData, ScreenStatus &ScrStat)
// Set the screen and defines its contents for first run. 
// Call after the screen init.
{

  // Build any Gadgets that will be called.

  // Prep Status Screen Text Box.
  // Countdown Screen
  
  // Countdown Timer
  Countdown_Timer.PROP.LABEL = "Timer: ";
  Countdown_Timer.PROP.LABEL_SIZE = 13;
  Countdown_Timer.PROP.COLOR = COLOR_WHITE;
  Countdown_Timer.PROP.BCOLOR = COLOR_GREEN;
  Countdown_Timer.PROP.COLOR_BAR_BACK = COLOR_GREEN;
  Countdown_Timer.PROP.COLOR_MARKER = COLOR_WHITE;
  Countdown_Timer.PROP.COLOR_MARKER_LIMIT = COLOR_RED;
  Countdown_Timer.PROP.BAR_SIZE = 15;
  Countdown_Timer.PROP.PROGRESS_BAR = true;
  Countdown_Timer.PROP.COLORS_ON = true;
  Countdown_Timer.PROP.MIN_MAX = false;
  Countdown_Timer.PROP.MIN_MAX_FILLER = true;
  Countdown_Timer.PROP.MIN_MAX_FILLER_BCOLOR = COLOR_YELLOW;
  Countdown_Timer.PROP.MIN_MAX_FILLER_COLOR = COLOR_WHITE;
  Countdown_Timer.PROP.MIN_MAX_INDICATORS = false;
  Countdown_Timer.PROP.BRACKET_END_CAPS = true;

  // Debug Screen 
  
  // Compute Times
  Compute_Time.PROP.LABEL = "Compute: ";
  Compute_Time.PROP.LABEL_SIZE = 13;
  Compute_Time.PROP.COLOR = COLOR_WHITE;
  Compute_Time.PROP.BCOLOR = COLOR_RED;
  Compute_Time.PROP.COLOR_BAR_BACK = COLOR_YELLOW;
  Compute_Time.PROP.BCOLOR_MARKER = COLOR_GREEN;
  Compute_Time.PROP.COLOR_MARKER = COLOR_WHITE;
  Compute_Time.PROP.COLOR_MARKER_LIMIT = COLOR_RED;
  Compute_Time.PROP.POSY = 0;
  Compute_Time.PROP.POSX = 7;
  Compute_Time.PROP.BAR_SIZE = 15;
  Compute_Time.PROP.GUAGE_BAR = true;
  Compute_Time.PROP.MIN_MAX = true;
  Compute_Time.PROP.MAX_VALUE = 20;
  Compute_Time.PROP.MIN_VALUE = 0;
  Compute_Time.PROP.MIN_MAX_INDICATORS = true;
  Compute_Time.PROP.MIN_MAX_FILLER = true;
  Compute_Time.PROP.MIN_MAX_FILLER_BCOLOR = COLOR_GREEN;
  Compute_Time.PROP.MIN_MAX_FILLER_COLOR = COLOR_WHITE;
  Compute_Time.MIN_MAX_HISTORY.PROP.SLICES = 5;
  Compute_Time.MIN_MAX_HISTORY.PROP.TIME_SPAN = 10000;
  Compute_Time.PROP.PRINT_VALUE = false;
  Compute_Time.PROP.PRINT_MIN = true;
  Compute_Time.PROP.PRINT_MAX = true;
  Compute_Time.PROP.COLORS_ON = true;

  // Program Sleep Times
  Sleep_Time.PROP.LABEL = "Sleep: ";
  Sleep_Time.PROP.LABEL_SIZE = 13;
  Sleep_Time.PROP.COLOR = COLOR_WHITE;
  Sleep_Time.PROP.BCOLOR = COLOR_RED;
  Sleep_Time.PROP.COLOR_BAR_BACK = COLOR_YELLOW;
  Sleep_Time.PROP.BCOLOR_MARKER = COLOR_GREEN;
  Sleep_Time.PROP.COLOR_MARKER = COLOR_WHITE;
  Sleep_Time.PROP.COLOR_MARKER_LIMIT = COLOR_RED;
  Sleep_Time.PROP.POSY = 1;
  Sleep_Time.PROP.POSX = 7;
  Sleep_Time.PROP.BAR_SIZE = 15;
  Sleep_Time.PROP.GUAGE_BAR = true;
  Sleep_Time.PROP.MIN_MAX = true;
  Sleep_Time.PROP.MAX_VALUE = 20;
  Sleep_Time.PROP.MIN_VALUE = 0;
  Sleep_Time.PROP.MIN_MAX_INDICATORS = true;
  Sleep_Time.PROP.MIN_MAX_FILLER = true;
  Sleep_Time.PROP.MIN_MAX_FILLER_BCOLOR = COLOR_GREEN;
  Sleep_Time.PROP.MIN_MAX_FILLER_COLOR = COLOR_WHITE;
  Sleep_Time.MIN_MAX_HISTORY.PROP.SLICES = 5;
  Sleep_Time.MIN_MAX_HISTORY.PROP.TIME_SPAN = 10000;
  Sleep_Time.PROP.PRINT_VALUE = false;
  Sleep_Time.PROP.PRINT_MIN = true;
  Sleep_Time.PROP.PRINT_MAX = true;
  Sleep_Time.PROP.COLORS_ON = true;

  // Program Sleep Times
  Cycle_Time.PROP.LABEL = "Cycle: ";
  Cycle_Time.PROP.LABEL_SIZE = 13;
  Cycle_Time.PROP.COLOR = COLOR_WHITE;
  Cycle_Time.PROP.BCOLOR = COLOR_RED;
  Cycle_Time.PROP.COLOR_BAR_BACK = COLOR_YELLOW;
  Cycle_Time.PROP.BCOLOR_MARKER = COLOR_GREEN;
  Cycle_Time.PROP.COLOR_MARKER = COLOR_WHITE;
  Cycle_Time.PROP.COLOR_MARKER_LIMIT = COLOR_RED;
  Cycle_Time.PROP.POSY = 2;
  Cycle_Time.PROP.POSX = 7;
  Cycle_Time.PROP.BAR_SIZE = 15;
  Cycle_Time.PROP.GUAGE_BAR = true;
  Cycle_Time.PROP.MIN_MAX = true;
  Cycle_Time.PROP.MAX_VALUE = 20;
  Cycle_Time.PROP.MIN_VALUE = 0;
  Cycle_Time.PROP.MIN_MAX_INDICATORS = true;
  Cycle_Time.PROP.MIN_MAX_FILLER = true;
  Cycle_Time.PROP.MIN_MAX_FILLER_BCOLOR = COLOR_GREEN;
  Cycle_Time.PROP.MIN_MAX_FILLER_COLOR = COLOR_WHITE;
  Cycle_Time.MIN_MAX_HISTORY.PROP.SLICES = 5;
  Cycle_Time.MIN_MAX_HISTORY.PROP.TIME_SPAN = 10000;
  Cycle_Time.PROP.PRINT_VALUE = false;
  Cycle_Time.PROP.PRINT_MIN = true;
  Cycle_Time.PROP.PRINT_MAX = true;
  Cycle_Time.PROP.COLORS_ON = true;
  
  // Draw screen the entire screen.  reset is also 
  //  called when the screen is resized.  
  reset(sdSysData, ScrStat);
}


void Screen3::reset(system_data &sdSysData, ScreenStatus &ScrStat)
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

  // Start first split
  XSplit = XMax - XCYBRSize;

  // ---------------------------------------------------------------------------------------
  // CYBR Panel
  if (ScrStat.Window_CYBR.value() == true)
  // Main CYBR Panel
  {
    // Calculate Size and Position
    YCYBRPos = 0;
    XCYBRPos = XSplit;
    YCYBRSize = YMax;
    XCYBRSize = XCYBRSize;

    CYBR_Status.PROP.POSY = YCYBRPos;
    CYBR_Status.PROP.POSX = XCYBRPos;
    CYBR_Status.PROP.SIZEY = YCYBRSize;
    CYBR_Status.PROP.SIZEX = XCYBRSize;

    CYBR_Status.create();
  }

  // ---------------------------------------------------------------------------------------
  // Status Panel
  if (ScrStat.Window_Status.value() == true)
  // Main Status Panel
  {
    // Recreate XSplit Size
    XSplit = XSplit - XButtonSize;

    // Calculate Size and Position
    YStatusPos = YStatusPos;
    XStatusPos = XStatusPos;
    YStatusSize = YStatusSize;
    XStatusSize = XSplit;

    // Build Window
    STATUS_PANEL.PROP.SIZEY = YStatusSize;
    STATUS_PANEL.PROP.SIZEX = XStatusSize;
    STATUS_PANEL.PROP.POSY = YStatusPos;
    STATUS_PANEL.PROP.POSX = XStatusPos;

    STATUS_PANEL.create();

    // Status Title Bar
    tiStatus.PROP.POSY = YStatusPos;
    tiStatus.PROP.POSX = XStatusPos;
    tiStatus.PROP.SIZEY = YStatusSize;
    tiStatus.PROP.SIZEX = XStatusSize;
    tiStatus.PROP.SIZE = TitleSize;

    tiStatus.PROP.LABEL = "STATUS";
    tiStatus.PROP.BCOLOR = COLOR_BLUE;
    tiStatus.PROP.COLOR = COLOR_WHITE;
    tiStatus.create();

    // Set Y Split
    YSplit = YSplit + YStatusSize;

    STATUS_PANEL.set_color(COLOR_BLUE, COLOR_WHITE);
    
    // Create Status Screen
    STATUS_PANEL.draw(true);

    // Text Fields
    COMMAND_TITLE.PROP.POSY = 0;
    COMMAND_TITLE.PROP.POSX = 1;

    COMMAND_UNDERLINE.PROP.POSY = 0;
    COMMAND_UNDERLINE.PROP.POSX = 6;

    COMMAND.PROP.POSY = 0;
    COMMAND.PROP.POSX = 6;

    DOOR1.PROP.POSY = 1;
    DOOR1.PROP.POSX = 37;

    DOOR2.PROP.POSY = 0;
    DOOR2.PROP.POSX = 37;

    DOOR3.PROP.POSY = 1;
    DOOR3.PROP.POSX = 44;

    DOOR4.PROP.POSY = 0;
    DOOR4.PROP.POSX = 44;

    LIGHTSOFF.PROP.POSY = 1;
    LIGHTSOFF.PROP.POSX = 4;

    NIGHT.PROP.POSY = 0;
    NIGHT.PROP.POSX = 29;

    HAZARD.PROP.POSY = 1;
    HAZARD.PROP.POSX = 18;

    OVERHEAD.PROP.POSY = 0;
    OVERHEAD.PROP.POSX = 18;

    TIMER.PROP.POSY = 1;
    TIMER.PROP.POSX = 29;

    AUTO.PROP.POSY = 0;
    AUTO.PROP.POSX = 53;

    ADSB.PROP.POSY = 1;
    ADSB.PROP.POSX = 53;

    VERSION.PROP.POSY = 0;
    VERSION.PROP.POSX = XStatusSize - 15 - TitleSize;
    VERSION.PROP.SIZEX = 15;
    VERSION.PROP.JUSTIFICATION_LEFT = true;

    TEMPERATURE.PROP.POSY = 1;
    TEMPERATURE.PROP.POSX = XStatusSize - 4;
    TEMPERATURE.PROP.SIZEX = 5;
    TEMPERATURE.PROP.JUSTIFICATION_LEFT = true;
  }

  // ---------------------------------------------------------------------------------------
  // Buttons
  if (ScrStat.Window_Buttons.value() == true)
  // Control Buttons
  {
    YButtonPos = 0;
    XButtonPos = XSplit;

    //buttons_menu_home(system_data &sdSysData, 0, XButtonPos, YButtonSize, XButtonSize);

    bzButtons.clear();

    bzButtons.NEW_BUTTON_PROP.BORDER.BOT = '_';
    bzButtons.NEW_BUTTON_PROP.POSX = XButtonPos;
    bzButtons.NEW_BUTTON_PROP.SIZEY = YButtonSize;
    bzButtons.NEW_BUTTON_PROP.SIZEX = XButtonSize;

    bzButtons.NEW_BUTTON_PROP.ID = 0;
    bzButtons.NEW_BUTTON_PROP.POSY = 0 * YButtonSize;
    bzButtons.create_button();

    bzButtons.NEW_BUTTON_PROP.ID = 1;
    bzButtons.NEW_BUTTON_PROP.POSY = 1 * YButtonSize;
    bzButtons.create_button();

    bzButtons.NEW_BUTTON_PROP.ID = 2;
    bzButtons.NEW_BUTTON_PROP.POSY = 2 * YButtonSize;
    bzButtons.create_button();

    bzButtons.NEW_BUTTON_PROP.ID = 3;
    bzButtons.NEW_BUTTON_PROP.POSY = 3 * YButtonSize;
    bzButtons.create_button();

    bzButtons.NEW_BUTTON_PROP.ID = 4;
    bzButtons.NEW_BUTTON_PROP.POSY = 4 * YButtonSize;
    bzButtons.create_button();

    bzButtons.NEW_BUTTON_PROP.ID = 5;
    bzButtons.NEW_BUTTON_PROP.POSY = 5 * YButtonSize;
    bzButtons.create_button();

    bzButtons.NEW_BUTTON_PROP.ID = 6;
    bzButtons.NEW_BUTTON_PROP.POSY = 6 * YButtonSize;
    bzButtons.create_button(); 

    buttons_menu_home(sdSysData);
  }

  // ---------------------------------------------------------------------------------------
  // Debug Panel
  if (ScrStat.Window_Debug.value() == true)
  {
    // Calculate Size and Position
    YDebugPos = YSplit;
    XDebugPos = XDebugPos;
    YDebugSize = YDebugSize;
    XDebugSize = XSplit;

    // Build Window
    DEBUG_PANEL.PROP.SIZEY = YDebugSize;
    DEBUG_PANEL.PROP.SIZEX = XDebugSize;
    DEBUG_PANEL.PROP.POSY = YDebugPos;
    DEBUG_PANEL.PROP.POSX = XDebugPos;
    DEBUG_PANEL.PROP.COLOR = COLOR_WHITE;
    DEBUG_PANEL.PROP.BCOLOR = COLOR_RED;

    DEBUG_PANEL.create();

    // Debug Title Bar
    tiDebug.PROP.POSY = YDebugPos;
    tiDebug.PROP.POSX = XDebugPos;
    tiDebug.PROP.SIZEY = YDebugSize;
    tiDebug.PROP.SIZEX = XDebugSize;
    tiDebug.PROP.SIZE = TitleSize;
    
    tiDebug.PROP.LABEL = "DIAG";
    tiDebug.PROP.BCOLOR = COLOR_RED;
    tiDebug.PROP.COLOR = COLOR_WHITE;
    tiDebug.create();

    // Set Y Split
    YSplit = YSplit + YDebugSize;
  }

  // ---------------------------------------------------------------------------------------
  // Color Picker Panel
  if (ScrStat.Window_CPicker.value() == true)
  {
    // Recreate XSplit Size
    XSplit = XSplit - XCPickerSize * 2;

    // Calculate Size and Position
    YCPickerPos = YSplit;
    XCPickerPos = XSplit;

    // Prep Side Buttons
    bzCPicker.clear();

    bzCPicker.NEW_BUTTON_PROP.VALUE = 0;
    bzCPicker.NEW_BUTTON_PROP.TYPE = 0;
    bzCPicker.NEW_BUTTON_PROP.COLOR = COLOR_WHITE;
    bzCPicker.NEW_BUTTON_PROP.SIZEY = YCPickerSize;
    bzCPicker.NEW_BUTTON_PROP.SIZEX = XCPickerSize;
    
    bzCPicker.NEW_BUTTON_PROP.ID = 0;
    bzCPicker.NEW_BUTTON_PROP.NAME = "RED";
    bzCPicker.NEW_BUTTON_PROP.LABEL = "\nr";
    bzCPicker.NEW_BUTTON_PROP.BCOLOR = COLOR_RED;
    bzCPicker.NEW_BUTTON_PROP.POSY = YCPickerPos + (YCPickerSize *0);
    bzCPicker.NEW_BUTTON_PROP.POSX = XCPickerPos + (XCPickerSize * 0);
    bzCPicker.create_button();

    bzCPicker.NEW_BUTTON_PROP.ID = 1;
    bzCPicker.NEW_BUTTON_PROP.NAME = "GREEN";
    bzCPicker.NEW_BUTTON_PROP.LABEL = "\ng";
    bzCPicker.NEW_BUTTON_PROP.BCOLOR = COLOR_GREEN;
    bzCPicker.NEW_BUTTON_PROP.POSY = YCPickerPos + (YCPickerSize *0);
    bzCPicker.NEW_BUTTON_PROP.POSX = XCPickerPos + (XCPickerSize * 1);
    bzCPicker.create_button();

    bzCPicker.NEW_BUTTON_PROP.ID = 2;
    bzCPicker.NEW_BUTTON_PROP.NAME = "BLUE";
    bzCPicker.NEW_BUTTON_PROP.LABEL = "\nb";
    bzCPicker.NEW_BUTTON_PROP.BCOLOR = COLOR_BLUE;
    bzCPicker.NEW_BUTTON_PROP.POSY = YCPickerPos + (YCPickerSize *1);
    bzCPicker.NEW_BUTTON_PROP.POSX = XCPickerPos + (XCPickerSize * 0);
    bzCPicker.create_button();

    bzCPicker.NEW_BUTTON_PROP.ID = 3;
    bzCPicker.NEW_BUTTON_PROP.NAME = "PURPLE";
    bzCPicker.NEW_BUTTON_PROP.LABEL = "\nu";
    bzCPicker.NEW_BUTTON_PROP.BCOLOR = COLOR_MAGENTA;
    bzCPicker.NEW_BUTTON_PROP.POSY = YCPickerPos + (YCPickerSize *1);
    bzCPicker.NEW_BUTTON_PROP.POSX = XCPickerPos + (XCPickerSize * 1);
    bzCPicker.create_button();

    bzCPicker.NEW_BUTTON_PROP.ID = 4;
    bzCPicker.NEW_BUTTON_PROP.NAME = "YELLOW";
    bzCPicker.NEW_BUTTON_PROP.LABEL = "\ny";
    bzCPicker.NEW_BUTTON_PROP.BCOLOR = COLOR_YELLOW;
    bzCPicker.NEW_BUTTON_PROP.POSY = YCPickerPos + (YCPickerSize *2);
    bzCPicker.NEW_BUTTON_PROP.POSX = XCPickerPos + (XCPickerSize * 0);
    bzCPicker.create_button();

    bzCPicker.NEW_BUTTON_PROP.ID = 5;
    bzCPicker.NEW_BUTTON_PROP.NAME = "CYAN";
    bzCPicker.NEW_BUTTON_PROP.LABEL = "\nc";
    bzCPicker.NEW_BUTTON_PROP.BCOLOR = COLOR_CYAN;
    bzCPicker.NEW_BUTTON_PROP.POSY = YCPickerPos + (YCPickerSize *2);
    bzCPicker.NEW_BUTTON_PROP.POSX = XCPickerPos + (XCPickerSize * 1);
    bzCPicker.create_button();

    bzCPicker.NEW_BUTTON_PROP.ID = 6;
    bzCPicker.NEW_BUTTON_PROP.NAME = "ORANGE";
    bzCPicker.NEW_BUTTON_PROP.LABEL = "\nn";
    bzCPicker.NEW_BUTTON_PROP.BCOLOR = COLOR_YELLOW;
    bzCPicker.NEW_BUTTON_PROP.POSY = YCPickerPos + (YCPickerSize *3);
    bzCPicker.NEW_BUTTON_PROP.POSX = XCPickerPos + (XCPickerSize * 0);
    bzCPicker.create_button();

    bzCPicker.NEW_BUTTON_PROP.ID = 7;
    bzCPicker.NEW_BUTTON_PROP.NAME = "WHITE";
    bzCPicker.NEW_BUTTON_PROP.LABEL = "\nw";
    bzCPicker.NEW_BUTTON_PROP.BCOLOR = COLOR_WHITE;
    bzCPicker.NEW_BUTTON_PROP.COLOR = COLOR_BLACK;
    bzCPicker.NEW_BUTTON_PROP.POSY = YCPickerPos + (YCPickerSize *3);
    bzCPicker.NEW_BUTTON_PROP.POSX = XCPickerPos + (XCPickerSize * 1);
    bzCPicker.create_button();
  }

  // ---------------------------------------------------------------------------------------
  // Timer Panel
  if (ScrStat.Window_Timer.value() == true)
  {
    // Calculate Size and Position
    YTimerPos = YSplit;
    XTimerPos = XTimerPos;
    YTimerSize = YTimerSize;
    XTimerSize = XSplit;

    // Build Window
    TIMER_PANEL.PROP.SIZEY = YTimerSize;
    TIMER_PANEL.PROP.SIZEX = XTimerSize;
    TIMER_PANEL.PROP.POSY = YTimerPos;
    TIMER_PANEL.PROP.POSX = XTimerPos;
    TIMER_PANEL.PROP.COLOR = COLOR_WHITE;
    TIMER_PANEL.PROP.BCOLOR = COLOR_GREEN;

    TIMER_PANEL.create();

    // Set Y Split
    YSplit = YSplit + YTimerSize;
    
    // Timer Title Bar
    tiTimer.PROP.POSY = YTimerPos;
    tiTimer.PROP.POSX = XTimerPos;
    tiTimer.PROP.SIZEY = YTimerSize;
    tiTimer.PROP.SIZEX = XTimerSize;
    tiTimer.PROP.SIZE = TitleSize;

    tiTimer.PROP.LABEL = "TIMER";
    tiTimer.PROP.BCOLOR = COLOR_GREEN;
    tiTimer.PROP.COLOR = COLOR_WHITE;
    tiTimer.create();
  }

  // ---------------------------------------------------------------------------------------
  // Console Panel
  if (ScrStat.Window_Console.value() == true)
  // Main Console Screen
  {
    // Calculate Size and Position
    YConsolePos = YSplit;
    XConsolePos = XConsolePos;
    YConsoleSize = YMax - YSplit - YTabSize;
    XConsoleSize =  XSplit;

    // Build Text Box
    tbConsole.PROP.LABEL = "Console";
    tbConsole.PROP.COLOR = COLOR_WHITE;
    tbConsole.PROP.BCOLOR = COLOR_BLACK;
    
    tbConsole.PROP.POSY = YConsolePos;
    tbConsole.PROP.POSX = XConsolePos;
    tbConsole.PROP.SIZEY = YConsoleSize;
    tbConsole.PROP.SIZEX = XConsoleSize;

    tbConsole.create();

    // Console Title Bar
    tiConsole.PROP.POSY = YConsolePos;
    tiConsole.PROP.POSX = XConsolePos;
    tiConsole.PROP.SIZEY = YConsoleSize;
    tiConsole.PROP.SIZEX = XConsoleSize;
    tiConsole.PROP.SIZE = TitleSize;

    tiConsole.PROP.LABEL = "CONSOLE";
    tiConsole.PROP.BCOLOR = COLOR_BLACK;
    tiConsole.PROP.COLOR = COLOR_WHITE;
    tiConsole.create();

    // Set Y Split
    YSplit = YSplit + YConsoleSize;

    // the bottom line of the console.
    strBotLine = "";
    strBotLine = strBotLine.append(XConsoleSize-1, '_');

  }

  // ---------------------------------------------------------------------------------------
  // Player Panel
  if (ScrStat.Window_Player.value() == true)
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
  if (ScrStat.Window_Log_Screen.value() == true)
  {
    // Radio Window
    // Calculate Size and Position
    YLog_ScreenPos = YSplit;
    XLog_ScreenPos = XLog_ScreenPos;
    YLog_ScreenSize = YMax - YSplit - YTabSize;
    XLog_ScreenSize =  XSplit;

    // Build Window
    Log_Screen_TEXT_BOX.PROP.LABEL = "Logs";
    Log_Screen_TEXT_BOX.PROP.POSY = YLog_ScreenPos;
    Log_Screen_TEXT_BOX.PROP.POSX = XLog_ScreenPos;
    Log_Screen_TEXT_BOX.PROP.SIZEY = YLog_ScreenSize;
    Log_Screen_TEXT_BOX.PROP.SIZEX = XLog_ScreenSize;
    Log_Screen_TEXT_BOX.PROP.BCOLOR = COLOR_BLACK;
    Log_Screen_TEXT_BOX.PROP.COLOR = COLOR_WHITE;

    Log_Screen_TEXT_BOX.create();

    // Log Screen Title Bar
    tiLog_Screen.PROP.POSY = YLog_ScreenPos;
    tiLog_Screen.PROP.POSX = XLog_ScreenPos;
    tiLog_Screen.PROP.SIZEY = YLog_ScreenSize;
    tiLog_Screen.PROP.SIZEX = XLog_ScreenSize;
    tiLog_Screen.PROP.SIZE = TitleSize;

    tiLog_Screen.PROP.LABEL = "LOGS";
    tiLog_Screen.PROP.BCOLOR = COLOR_BLACK;
    tiLog_Screen.PROP.COLOR = COLOR_WHITE;
    
    tiLog_Screen.create();

    // Set Y Split      
    YSplit = YSplit + YLog_ScreenSize;
  }


  // ---------------------------------------------------------------------------------------
  // Color AUTOMOBILE Buttons Panel
  if (ScrStat.Window_Automobile_Screen.value() == true || 
        ScrStat.Window_Alerts_Screen.value() == true)
  {    
    // AUTOMOBILE_OVERVIEW Window
    // Calculate Size and Position
    YAUTOMOBILE_OVERVIEW_ScreenPos = YSplit;
    XAUTOMOBILE_OVERVIEW_ScreenPos = XAUTOMOBILE_OVERVIEW_ScreenPos;
    YAUTOMOBILE_OVERVIEW_ScreenSize = YMax - YSplit - YTabSize;
    XAUTOMOBILE_OVERVIEW_ScreenSize = XAUTOMOBILE_OVERVIEW_ScreenSize;

    // Build Window
    AUTOMOBILE_OVERVIEW_PANEL.PROP.SIZEY = YAUTOMOBILE_OVERVIEW_ScreenSize;
    AUTOMOBILE_OVERVIEW_PANEL.PROP.SIZEX = XAUTOMOBILE_OVERVIEW_ScreenSize;
    AUTOMOBILE_OVERVIEW_PANEL.PROP.POSY = YAUTOMOBILE_OVERVIEW_ScreenPos;
    AUTOMOBILE_OVERVIEW_PANEL.PROP.POSX = XAUTOMOBILE_OVERVIEW_ScreenPos;

    AUTOMOBILE_OVERVIEW_PANEL.create();
  }
    
  // ---------------------------------------------------------------------------------------
  // Color AUTOMOBILE Buttons Panel

  if (ScrStat.Window_Automobile_Screen.value() == true)
  { 
    // AUTOMOBILE Window
    // Calculate Size and Position
    YAUTOMOBILE_ScreenPos = YSplit;
    XAUTOMOBILE_ScreenPos = XAUTOMOBILE_OVERVIEW_ScreenPos + XAUTOMOBILE_OVERVIEW_ScreenSize;
    YAUTOMOBILE_ScreenSize = YMax - YSplit - YTabSize;
    XAUTOMOBILE_ScreenSize =  XSplit - XAUTOMOBILE_OVERVIEW_ScreenSize;

    // Build Window
    AUTOMOBILE_PANEL.PROP.SIZEY = YAUTOMOBILE_ScreenSize;
    AUTOMOBILE_PANEL.PROP.SIZEX = XAUTOMOBILE_ScreenSize;
    AUTOMOBILE_PANEL.PROP.POSY = YAUTOMOBILE_ScreenPos;
    AUTOMOBILE_PANEL.PROP.POSX = XAUTOMOBILE_ScreenPos;

    AUTOMOBILE_PANEL.create();

    // AUTOMOBILE Title Bar
    tiAUTOMOBILE_Screen.PROP.POSY = YAUTOMOBILE_ScreenPos;
    tiAUTOMOBILE_Screen.PROP.POSX = XAUTOMOBILE_ScreenPos;
    tiAUTOMOBILE_Screen.PROP.SIZEY = YAUTOMOBILE_ScreenSize;
    tiAUTOMOBILE_Screen.PROP.SIZEX = XAUTOMOBILE_ScreenSize;
    tiAUTOMOBILE_Screen.PROP.SIZE = TitleSize;
    
    tiAUTOMOBILE_Screen.PROP.LABEL = "AUTOMOBILE";
    tiAUTOMOBILE_Screen.PROP.BCOLOR = COLOR_BLACK;
    tiAUTOMOBILE_Screen.PROP.COLOR = COLOR_WHITE;
    tiAUTOMOBILE_Screen.create();

    // Set Y Split      
    YSplit = YSplit + YLog_ScreenSize;
  }


  // ---------------------------------------------------------------------------------------
  // Color ADS_B Buttons Panel
  if (ScrStat.Window_ADS_B_Buttons.value() == true)
  {
    // Recreate XSplit Size
    //XSplit = XSplit - XCPickerSize * 2;

    // Calculate Size and Position
    YADS_B_ScreenPos = YSplit;
    XADS_B_ScreenPos = 0;

    // Prep ADS_B Buttons
    
    bzADS_B.clear();

    bzADS_B.NEW_BUTTON_PROP.BORDER.BOT = '_';

    bzADS_B.NEW_BUTTON_PROP.ID = 0;
    bzADS_B.NEW_BUTTON_PROP.NAME = "ADS_BON";
    bzADS_B.NEW_BUTTON_PROP.LABEL = "\nADS-B";
    bzADS_B.NEW_BUTTON_PROP.VALUE = 0;
    bzADS_B.NEW_BUTTON_PROP.TYPE = 1;
    bzADS_B.NEW_BUTTON_PROP.COLOR = COLOR_WHITE;
    bzADS_B.NEW_BUTTON_PROP.BCOLOR = COLOR_YELLOW;
    bzADS_B.NEW_BUTTON_PROP.POSY = YADS_B_ScreenPos + 1 + (YBADS_BSize *0);
    bzADS_B.NEW_BUTTON_PROP.POSX = XADS_B_ScreenPos + (XBADS_BSize *0);
    bzADS_B.NEW_BUTTON_PROP.SIZEY = YBADS_BSize;
    bzADS_B.NEW_BUTTON_PROP.SIZEX = XBADS_BSize;
    bzADS_B.create_button();
    
    bzADS_B.NEW_BUTTON_PROP.ID = 1;
    bzADS_B.NEW_BUTTON_PROP.NAME = "ADS_B_SNAPSHOT";
    bzADS_B.NEW_BUTTON_PROP.LABEL = "\nSnap\nShot";
    bzADS_B.NEW_BUTTON_PROP.VALUE = 0;
    bzADS_B.NEW_BUTTON_PROP.TYPE = 0;
    bzADS_B.NEW_BUTTON_PROP.COLOR = COLOR_WHITE;
    bzADS_B.NEW_BUTTON_PROP.BCOLOR = COLOR_RED;
    bzADS_B.NEW_BUTTON_PROP.POSY = YADS_B_ScreenPos + 1 + (YBADS_BSize *0);
    bzADS_B.NEW_BUTTON_PROP.POSX = XADS_B_ScreenPos + (XBADS_BSize *1);
    bzADS_B.NEW_BUTTON_PROP.SIZEY = YBADS_BSize;
    bzADS_B.NEW_BUTTON_PROP.SIZEX = XBADS_BSize;
    bzADS_B.create_button();
  }

  if (ScrStat.Window_ADS_B_Screen.value() == true)
  {
    // ADS_B Window
    // Calculate Size and Position
    YADS_B_ScreenPos = YSplit;
    XADS_B_ScreenPos = XADS_B_ScreenPos;  // + XBADS_BSize;
    YADS_B_ScreenSize = YMax - YSplit - YTabSize;
    XADS_B_ScreenSize =  XSplit;          // - XBADS_BSize;

    // Build Window
    ADSB_GRID_PANEL.PROP.SIZEY = YADS_B_ScreenSize;
    ADSB_GRID_PANEL.PROP.SIZEX = XADS_B_ScreenSize;
    ADSB_GRID_PANEL.PROP.POSY = YADS_B_ScreenPos;
    ADSB_GRID_PANEL.PROP.POSX = XADS_B_ScreenPos;

    ADSB_GRID_PANEL.create();

    // ADS-B Title Bar
    tiADS_B_Screen.PROP.POSY = YADS_B_ScreenPos;
    tiADS_B_Screen.PROP.POSX = XADS_B_ScreenPos;
    tiADS_B_Screen.PROP.SIZEY = YADS_B_ScreenSize;
    tiADS_B_Screen.PROP.SIZEX = XADS_B_ScreenSize;
    tiADS_B_Screen.PROP.SIZE = TitleSize;
    
    tiADS_B_Screen.PROP.LABEL = "ADS-B";
    tiADS_B_Screen.PROP.BCOLOR = COLOR_BLACK;
    tiADS_B_Screen.PROP.COLOR = COLOR_WHITE;
    tiADS_B_Screen.create();

    // Set Y Split      
    YSplit = YSplit + YLog_ScreenSize;

    // Create Screen
    ADSB_GRID_PANEL.set_color(COLOR_BLACK, COLOR_BLACK);
    ADSB_GRID_PANEL.draw(true);

    // the bottom line of the ADS_B.
    strBotLine = "";
    strBotLine = strBotLine.append(XADS_B_ScreenSize-1, '_');

    // Display ADSB Tital Bar
    //tbads_b_Data.move_resize(YADS_B_ScreenPos, XADS_B_ScreenPos + XBADS_BSize, YADS_B_ScreenSize, XADS_B_ScreenSize - XBADS_BSize);
    
    ADSB_Grid.PROP.POSY = YADS_B_ScreenPos;
    ADSB_Grid.PROP.POSX = XADS_B_ScreenPos;
    ADSB_Grid.PROP.SIZEY = YADS_B_ScreenSize;
    ADSB_Grid.PROP.SIZEX = XADS_B_ScreenSize;

    ADSB_Grid.create();
  }

  // ---------------------------------------------------------------------------------------
  if (ScrStat.Window_Alerts_Screen.value() == true)
  {
    // Alerts Window
    // Calculate Size and Position
    YALERTS_ScreenPos = YSplit;
    XALERTS_ScreenPos =  XAUTOMOBILE_OVERVIEW_ScreenPos + XAUTOMOBILE_OVERVIEW_ScreenSize;
    YALERTS_ScreenSize = YMax - YSplit - YTabSize;
    XALERTS_ScreenSize =  XSplit - XAUTOMOBILE_OVERVIEW_ScreenSize;

    // Build Window
    ALERTS_GRID.PROP.SIZEY = YALERTS_ScreenSize;
    ALERTS_GRID.PROP.SIZEX = XALERTS_ScreenSize;
    ALERTS_GRID.PROP.POSY = YALERTS_ScreenPos;
    ALERTS_GRID.PROP.POSX = XALERTS_ScreenPos;

    ALERTS_GRID.create();

    // Alerts Title Bar
    tiALERTS_Screen.PROP.POSY = YALERTS_ScreenPos;
    tiALERTS_Screen.PROP.POSX = XALERTS_ScreenPos;
    tiALERTS_Screen.PROP.SIZEY = YALERTS_ScreenSize;
    tiALERTS_Screen.PROP.SIZEX = XALERTS_ScreenSize;
    tiALERTS_Screen.PROP.SIZE = TitleSize;
    
    tiALERTS_Screen.PROP.LABEL = "ALERTS";
    tiALERTS_Screen.PROP.BCOLOR = COLOR_RED;
    tiALERTS_Screen.PROP.COLOR = COLOR_WHITE;
    tiALERTS_Screen.create();

    // Set Y Split      
    YSplit = YSplit + YLog_ScreenSize;
  }

  // ---------------------------------------------------------------------------------------
  // Tabs Panel
  if (ScrStat.Window_Tabs.value() == true)
  {
    // Calculate Size and Position
    YSplit = YMax - YTabSize;

    YTabPos = YSplit;
    XTabPos = XTabPos;

    int id_of_val_1 = bzTabs.get_id_of_button_with_value(1);

    // Prep Tab Buttons
    bzTabs.clear();

    // Shared Properties
    bzTabs.NEW_BUTTON_PROP.TYPE = 2;
    bzTabs.NEW_BUTTON_PROP.BCOLOR = COLOR_BLUE;
    bzTabs.NEW_BUTTON_PROP.COLOR = COLOR_WHITE;
    bzTabs.NEW_BUTTON_PROP.SIZEY = YTabSize;
    bzTabs.NEW_BUTTON_PROP.SIZEX = XTabSize;

    bzTabs.NEW_BUTTON_PROP.ID = 0;
    bzTabs.NEW_BUTTON_PROP.NAME = "TABCONSOLE";
    bzTabs.NEW_BUTTON_PROP.LABEL = "Console";
    bzTabs.NEW_BUTTON_PROP.POSY = YTabPos + (YTabSize *0);
    bzTabs.NEW_BUTTON_PROP.POSX = XTabPos + (XTabSize * 0);
    bzTabs.create_button();
    
    bzTabs.NEW_BUTTON_PROP.ID = 1;
    bzTabs.NEW_BUTTON_PROP.NAME = "TABPLAYER";
    bzTabs.NEW_BUTTON_PROP.LABEL = "Player";
    bzTabs.NEW_BUTTON_PROP.POSY = YTabPos + (YTabSize *0);
    bzTabs.NEW_BUTTON_PROP.POSX = XTabPos + (XTabSize * 1 +1);
    bzTabs.create_button();

    bzTabs.NEW_BUTTON_PROP.ID = 2;
    bzTabs.NEW_BUTTON_PROP.NAME = "TAB_AUTOMOBILE";
    bzTabs.NEW_BUTTON_PROP.LABEL = "Automobile";
    bzTabs.NEW_BUTTON_PROP.POSY = YTabPos + (YTabSize *0);
    bzTabs.NEW_BUTTON_PROP.POSX = XTabPos + (XTabSize * 2 +2);
    bzTabs.create_button();

    bzTabs.NEW_BUTTON_PROP.ID = 6;
    bzTabs.NEW_BUTTON_PROP.NAME = "TAB_ADS_B_SCREEN";
    bzTabs.NEW_BUTTON_PROP.LABEL = "ADS-B";
    bzTabs.NEW_BUTTON_PROP.POSY = YTabPos + (YTabSize *0);
    bzTabs.NEW_BUTTON_PROP.POSX = XTabPos + (XTabSize * 3 +3);
    bzTabs.create_button();

    bzTabs.NEW_BUTTON_PROP.ID = 8;
    bzTabs.NEW_BUTTON_PROP.NAME = "TAB_LOG_SCREEN";
    bzTabs.NEW_BUTTON_PROP.LABEL = "Log";
    bzTabs.NEW_BUTTON_PROP.POSY = YTabPos + (YTabSize *0);
    bzTabs.NEW_BUTTON_PROP.POSX = XTabPos + (XTabSize * 5 +6);
    bzTabs.create_button();

    bzTabs.NEW_BUTTON_PROP.ID = 10;
    bzTabs.NEW_BUTTON_PROP.NAME = "TAB_ALERTS_SCREEN";
    bzTabs.NEW_BUTTON_PROP.LABEL = "ALERTS";
    bzTabs.NEW_BUTTON_PROP.POSY = YTabPos + (YTabSize *0);
    bzTabs.NEW_BUTTON_PROP.POSX = XTabPos + (XTabSize * 6 +8);

    bzTabs.NEW_BUTTON_PROP.BCOLOR = COLOR_RED;
    bzTabs.NEW_BUTTON_PROP.COLOR = COLOR_WHITE;
    
    bzTabs.create_button();

    if (id_of_val_1 > -1)
    {
      bzTabs.set_value(id_of_val_1, 1);
    }
    else
    {
      bzTabs.set_value(0, 1);
    }

    // Set Y Split
    YSplit = YSplit + YTabSize;
  }

  // probably does something for the tty terminal.  probably should have 
  //  commented it when i reseached and wrote it.
  nodelay(stdscr, true);
}
// ---------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------
void Screen3::output_status(system_data &sdSysData, Keys &keywatch, ScreenStatus &ScrStat, TheMouse &mouse)
// Displays command line input, status and door indicators
{
  // Display Command Line
  COMMAND_TITLE.set_text("CMD:");
  if (keywatch.cmdPressed() == true || keywatch.cmdCleared() == true || ScrStat.Needs_Refresh == true)
  {
    COMMAND_UNDERLINE.set_text("__________");
    COMMAND_UNDERLINE.redraw();

    COMMAND.set_text(keywatch.cmdRead().c_str());
  }

  //Display Door Statuses, highlighting values that are on (doors open)
  DOOR1.set_text(" Door1 ");
  DOOR1.set_inverse(sdSysData.CONFIG.vSWITCH_PIN_MAP.at(0).value);
  
  DOOR2.set_text(" Door2 ");
  DOOR2.set_inverse(sdSysData.CONFIG.vSWITCH_PIN_MAP.at(1).value);

  DOOR3.set_text(" Door3 ");
  DOOR3.set_inverse(sdSysData.CONFIG.vSWITCH_PIN_MAP.at(2).value);
  
  DOOR4.set_text(" Door4 ");
  DOOR4.set_inverse(sdSysData.CONFIG.vSWITCH_PIN_MAP.at(3).value);
  

  // Display Lights Off mode toggle.
  if(sdSysData.Lights_On.value() == false)
  {
    LIGHTSOFF.set_inverse(true);
    LIGHTSOFF.set_text("  LIGHTS OFF  ");
  }
  else
  {
    LIGHTSOFF.set_inverse(false);
    LIGHTSOFF.set_text("              ");    
  }

  // Display Day or Night mode toggle.
  if(sdSysData.Day_On_With_Override.value() == true)
  {
    NIGHT.set_inverse(true);
    NIGHT.set_text("  DAY  ");
  }
  else
  {
    NIGHT.set_inverse(false);
    NIGHT.set_text(" NIGHT ");   
  }
  
  // Display Hazard Indicator
  HAZARD.set_inverse(sdSysData.booHazardRunning);
  HAZARD.set_text("  HAZARD  ");
  
  // Display Overhead Indicator
  OVERHEAD.set_inverse(sdSysData.booOverheadRunning);
  OVERHEAD.set_text(" OVERHEAD ");
  
  // Display Timer Indicator
  TIMER.set_inverse(sdSysData.cdTIMER.is_active());
  TIMER.set_text(" TIMER ");

  // Display ADS-B Indicaor
  AUTO.set_inverse(sdSysData.CAR_INFO.active());
  AUTO.set_text(" AUTO  ");

  // Display ADS-B Indicaor
  ADSB.set_inverse(sdSysData.AIRCRAFT_COORD.is_active());
  ADSB.set_text(" ADS-B ");
  
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

  // Display Version
  VERSION.set_text(Revision);
  
  // Display CPU Temp
  if (sdSysData.hsHardware_Status.enabled() == true)
  {
    TEMPERATURE.set_text(to_string((int)sdSysData.hsHardware_Status.get_temperature()) + "c");
  }
  else
  {
    TEMPERATURE.set_text("NA");
  }

  // Draw Fields
  COMMAND_TITLE.draw(STATUS_PANEL, ScrStat.Needs_Refresh);
  COMMAND_UNDERLINE.draw(STATUS_PANEL, ScrStat.Needs_Refresh);
  COMMAND.draw(STATUS_PANEL, ScrStat.Needs_Refresh);
  DOOR1.draw(STATUS_PANEL, ScrStat.Needs_Refresh);
  DOOR2.draw(STATUS_PANEL, ScrStat.Needs_Refresh);
  DOOR3.draw(STATUS_PANEL, ScrStat.Needs_Refresh);
  DOOR4.draw(STATUS_PANEL, ScrStat.Needs_Refresh);
  LIGHTSOFF.draw(STATUS_PANEL, ScrStat.Needs_Refresh);
  NIGHT.draw(STATUS_PANEL, ScrStat.Needs_Refresh);
  HAZARD.draw(STATUS_PANEL, ScrStat.Needs_Refresh);
  OVERHEAD.draw(STATUS_PANEL, ScrStat.Needs_Refresh);
  TIMER.draw(STATUS_PANEL, ScrStat.Needs_Refresh);
  AUTO.draw(STATUS_PANEL, ScrStat.Needs_Refresh);
  ADSB.draw(STATUS_PANEL, ScrStat.Needs_Refresh);
  TEMPERATURE.draw(STATUS_PANEL, ScrStat.Needs_Refresh);
  VERSION.draw(STATUS_PANEL, ScrStat.Needs_Refresh);

  // Commit all our changes to the status portion of the screen
  STATUS_PANEL.draw(ScrStat.Needs_Refresh);

  tiStatus.draw(ScrStat.Needs_Refresh);
}

// ---------------------------------------------------------------------------------------
void Screen3::output_CYBR(system_data &sdSysData, ScreenStatus &ScrStat)
// Displays CYBR
{
  int anims = 0;

  // Sleep
  CYBR_Status.input(20 - sdSysData.dblPREVSLEEPTIME.get_data(), 20, COLOR_BLACK, COLOR_YELLOW);

  // RSSI
  if(sdSysData.AIRCRAFT_COORD.is_active() == true)
  {
    for (int adsb = 0; adsb < sdSysData.AIRCRAFT_COORD.DATA.AIRCRAFTS.size(); adsb++)
    {
      if (sdSysData.AIRCRAFT_COORD.DATA.AIRCRAFTS[adsb].POSITION.GLOBAL_POSITION_FOUND == true)
      {
        CYBR_Status.input( 35 + sdSysData.AIRCRAFT_COORD.DATA.AIRCRAFTS[adsb].RSSI.get_int_value() , 35, COLOR_GREEN, COLOR_BLACK);
      }
      else
      {
        CYBR_Status.input( 35 + sdSysData.AIRCRAFT_COORD.DATA.AIRCRAFTS[adsb].RSSI.get_int_value() , 35, COLOR_BLACK, COLOR_GREEN);
      }

      
    }

    CYBR_Status.input(sdSysData.AIRCRAFT_COORD.DATA.DELTA_MESSAGES , 50, COLOR_CYAN, COLOR_BLACK);

  }

  // Animations
  for(int gr = 0; gr <=3; gr++)
  {
    if(sdSysData.intCHANNEL_GROUP_EVENTS_COUNTS.at(gr)>0)
    {
      anims = anims + sdSysData.intCHANNEL_GROUP_EVENTS_COUNTS.at(gr);
    }
  }
  if (anims > 0)
  {
    CYBR_Status.input(anims, 255, COLOR_WHITE, COLOR_BLACK);
  }

  CYBR_Status.draw(sdSysData.tmeCURRENT_FRAME_TIME);
}

// ---------------------------------------------------------------------------------------
void Screen3::output_debug2(system_data &sdSysData, Keys &keywatch, ScreenStatus &ScrStat, TheMouse &mouse)
// Displays clock timings, event count, and mouse info.
{
  string strRange = "";
  string strLevel = "";

  // Print Timings
  Compute_Time.PROP.LABEL = "Compute: " + to_string(sdSysData.dblCOMPUTETIME.get_data()) + " ";
  Compute_Time.update(sdSysData.dblCOMPUTETIME.get_data(), sdSysData.tmeCURRENT_FRAME_TIME);
  Compute_Time.draw(DEBUG_PANEL, true);
  
  Sleep_Time.PROP.LABEL = "Sleep:   " + to_string(sdSysData.dblPREVSLEEPTIME.get_data()) + " ";
  Sleep_Time.update(sdSysData.dblPREVSLEEPTIME.get_data(), sdSysData.tmeCURRENT_FRAME_TIME);
  Sleep_Time.draw(DEBUG_PANEL, true);
  
  Cycle_Time.PROP.LABEL = "Cycle:   " + to_string(sdSysData.dblCYCLETIME.get_data()) + " ";
  Cycle_Time.update(sdSysData.dblCYCLETIME.get_data(), sdSysData.tmeCURRENT_FRAME_TIME);
  Cycle_Time.draw(DEBUG_PANEL, true);
  
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
  mvwprintw(DEBUG_PANEL.winPANEL, 0, 0, "RNG:%s", strRange.c_str());
  mvwprintw(DEBUG_PANEL.winPANEL, 1, 0, "LVL:%s", strLevel.c_str());
  //------------------------

  // Show Number of Events per Channel
  mvwprintw(DEBUG_PANEL.winPANEL, 1, 50, "%03d:D1", sdSysData.intCHANNEL_GROUP_EVENTS_COUNTS.at(0));
  mvwprintw(DEBUG_PANEL.winPANEL, 0, 50, "%03d:D2", sdSysData.intCHANNEL_GROUP_EVENTS_COUNTS.at(1));
  mvwprintw(DEBUG_PANEL.winPANEL, 1, 57, "D3:%03d", sdSysData.intCHANNEL_GROUP_EVENTS_COUNTS.at(2));
  mvwprintw(DEBUG_PANEL.winPANEL, 0, 57, "D4:%03d", sdSysData.intCHANNEL_GROUP_EVENTS_COUNTS.at(3));
  
  //------------------------
  //Mouse Position
  mvwprintw(DEBUG_PANEL.winPANEL, 1, XStatusSize - 14, "Mouse: %03d %03d",mouse.x(),mouse.y());

  //------------------------
  DEBUG_PANEL.draw(true);

  tiDebug.draw(ScrStat.Needs_Refresh);
}

// ---------------------------------------------------------------------------------------
void Screen3::output_timer(system_data &sdSysData, Keys &keywatch, ScreenStatus &ScrStat, TheMouse &mouse)
// Displays first countdown timer.
{
  long elaped_time = 0;
  unsigned long duration_time = 0;
  long remaining_time = 0;

  // Calculate
  duration_time = sdSysData.cdTIMER.duration();
  elaped_time = sdSysData.cdTIMER.elapsed_time(sdSysData.tmeCURRENT_FRAME_TIME);
  remaining_time = duration_time - elaped_time;

  // Display Timer
  string mins = linemerge_right_justify(2, "00", to_string(millis_to_time_minutes(remaining_time)));
  string secs = linemerge_right_justify(2, "00", to_string(millis_to_time_seconds(remaining_time)));

  Countdown_Timer.PROP.LABEL = "Timer: " + mins + ":" + secs + " ";
  Countdown_Timer.PROP.MAX_VALUE = duration_time;
  Countdown_Timer.PROP.POSY = 1;
  Countdown_Timer.PROP.POSX = 2;
  Countdown_Timer.update(duration_time - elaped_time, sdSysData.tmeCURRENT_FRAME_TIME);

  Countdown_Timer.draw(TIMER_PANEL, ScrStat.Needs_Refresh);
  TIMER_PANEL.draw(ScrStat.Needs_Refresh);
  tiTimer.draw(ScrStat.Needs_Refresh);
}

// ---------------------------------------------------------------------------------------
void Screen3::printout(ScreenStatus &ScrStat)
// Displays console of commands ran, events starting and stoping, and other info.
//  If console is on another tty through tty over ethernet or serial then a low 
//    bandwith version will need to created.  Or, I put the console into its own 
//    thread.  Whichever is necessary to develop or learn first.
{
  tbConsole.draw(ScrStat.Needs_Refresh);
  tiConsole.draw(ScrStat.Needs_Refresh);
}

// ---------------------------------------------------------------------------------------
void Screen3::the_player(ScreenStatus &ScrStat)
// Shows the Player Window
{
  int yCurPos = 0;

  // Refresh the window.
  // wrefresh(winPlayer);
  
}

void Screen3::window_player_clear()
// clear the contents of the player window.
{
  wclear(winPlayer);
}

void Screen3::window_player_draw_frame(PLAYER_FRAME &qframe)
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

string Screen3::buffer()
// Returns the value stored in the buffer.
{
  return strBuffer;
}

// ---------------------------------------------------------------------------------------
void Screen3::automobile_screen(system_data &sdSysData, ScreenStatus &ScrStat)
// Shows the Player Window
{
  AUTOMOBILE_OVERVIEW_PANEL.draw(ScrStat.Needs_Refresh, sdSysData.tmeCURRENT_FRAME_TIME);
  AUTOMOBILE_PANEL.draw(ScrStat.Needs_Refresh, sdSysData.tmeCURRENT_FRAME_TIME);
  tiAUTOMOBILE_Screen.draw(ScrStat.Needs_Refresh == true);
}

// ---------------------------------------------------------------------------------------
void Screen3::ads_b_screen(system_data &sdSysData, ScreenStatus &ScrStat)
// Shows the Player Window
{
  // Print ADS_B Buttons
  bzADS_B.draw(ScrStat.Needs_Refresh, sdSysData.tmeCURRENT_FRAME_TIME);

  ADSB_Grid.draw(ScrStat.Needs_Refresh, sdSysData.tmeCURRENT_FRAME_TIME, ADSB_GRID_PANEL);
  tiADS_B_Screen.draw(ScrStat.Needs_Refresh);
}

// ---------------------------------------------------------------------------------------
void Screen3::log_screen(system_data &sdSysData, ScreenStatus &ScrStat)
// Shows the Player Window
{
  // Print Log File
  Log_Screen_TEXT_BOX.draw(ScrStat.Needs_Refresh);

  // Print Title
  tiLog_Screen.draw(ScrStat.Needs_Refresh);
}

// ---------------------------------------------------------------------------------------
void Screen3::alerts_screen(system_data &sdSysData, ScreenStatus &ScrStat)
// Shows the Player Window
{
  AUTOMOBILE_OVERVIEW_PANEL.draw(ScrStat.Needs_Refresh, sdSysData.tmeCURRENT_FRAME_TIME);
  ALERTS_GRID.draw(ScrStat.Needs_Refresh, sdSysData.tmeCURRENT_FRAME_TIME, sdSysData.ALERTS);
  tiALERTS_Screen.draw(ScrStat.Needs_Refresh == true);
}

// ---------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------
// Main screen routine.
// Draw the console, starting with status window, then whatever windows set to true.

void Screen3::output(system_data &sdSysData, Keys &keywatch, ScreenStatus &ScrStat, TheMouse &mouse)
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
  bzButtons.set_value("TIMER", int(sdSysData.cdTIMER.is_active()));
  bzButtons.set_value("MENUOVERHEAD", int(sdSysData.booOverheadRunning));
  bzButtons.set_value("HAZARD", int(sdSysData.booHazardRunning));
  bzButtons.set_value("LIGHTSOFF", int(sdSysData.Lights_On.value()));
  bzADS_B.set_value("ADS_BON", int(sdSysData.AIRCRAFT_COORD.is_active()));

  // Check for Timer Window
  if (sdSysData.cdTIMER.is_active() == true)
  {
    ScrStat.Window_Timer.on(ScrStat.Needs_Refresh);
  }
  else
  {
    ScrStat.Window_Timer.off(ScrStat.Needs_Refresh);
  }

  // ---------------------------------------------------------------------------------------
  // Check to see if the screen need to be rebuilt
  if (ScrStat.Needs_Refresh == true)
  {
    reset(sdSysData, ScrStat);
  }

  // ---------------------------------------------------------------------------------------
  // Draw the Screens

  // Draw Console window.
  if (ScrStat.Window_Console.value() == true)
  {
    printout(ScrStat);
  }

  // Draw Player window.
  if (ScrStat.Window_Player.value() == true)
  {
    the_player(ScrStat);
  }

  // Draw Radio window.
  if (ScrStat.Window_Automobile_Screen.value() == true)
  {
    automobile_screen(sdSysData, ScrStat);
  }
  
  // Draw Log Screen window.
  if (ScrStat.Window_ADS_B_Screen.value() == true)
  {
    ads_b_screen(sdSysData, ScrStat);
  }

  // Draw Log Screen window.
  if (ScrStat.Window_Log_Screen.value() == true)
  {
    log_screen(sdSysData, ScrStat);
  }

  // Draw Alerts Screen window.
  if (ScrStat.Window_Alerts_Screen.value() == true)
  {
    alerts_screen(sdSysData, ScrStat);
  }

  // Buttons

  // Draw Tabs.
  if (ScrStat.Window_Tabs.value() == true)
  {
    bzTabs.draw(ScrStat.Needs_Refresh, sdSysData.tmeCURRENT_FRAME_TIME);
  }

  // Draw buttons on buttons window.
  if (ScrStat.Window_Buttons.value() == true)
  {
    bzButtons.draw(ScrStat.Needs_Refresh, sdSysData.tmeCURRENT_FRAME_TIME);
  }

  // Draw Color Picker window.
  if (ScrStat.Window_CPicker.value() == true)
  {
    bzCPicker.draw(ScrStat.Needs_Refresh, sdSysData.tmeCURRENT_FRAME_TIME);
  }

  // Draw Statuses

  // Draw Timer window.
  if (ScrStat.Window_Timer.value() == true)
  {
    output_timer(sdSysData, keywatch, ScrStat, mouse);
  }

  // Draw Debug window.
  if (ScrStat.Window_Debug.value() == true)
  {
    output_debug2(sdSysData, keywatch, ScrStat, mouse);
  }

  // Draw Status window.
  if (ScrStat.Window_Status.value() == true)
  {
    output_status(sdSysData, keywatch, ScrStat, mouse);
  }

  // Draw CYBR window.
  if (ScrStat.Window_CYBR.value() == true)
  {
    output_CYBR(sdSysData, ScrStat);
  }

  // ---------------------------------------------------------------------------------------
  // Draw all changes to the screen.
  // Clear Refresh varibles.
  refresh();
  ScrStat.Needs_Refresh = false;
}




#endif