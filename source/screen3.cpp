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
  bzButtons.set_value(2, int(sdSysData.booDay_On));
  bzButtons.set_type(2, 1);
  bzButtons.set_color(2, COLOR_GREEN, COLOR_WHITE);
  bzButtons.set_hidden(2, false);
  bzButtons.set_enabled(2, true);

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

  if (sdSysData.booDay_On == true)
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
  
  bzButtons.set_hidden(2, true);
  bzButtons.set_enabled(2, false);

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

  // Prep Console Screen Text Box.
  tbConsole.create(1, "CONSOLE", "Console", 0, CRT_get_color_pair(COLOR_BLACK, COLOR_WHITE), 0);

  // Countdown Screen
  // Countdown Timer
  Countdown_Timer.label("Timer: ");
  Countdown_Timer.label_size(13);
  Countdown_Timer.size(15);
  Countdown_Timer.max_value(75);
  Countdown_Timer.color_background(COLOR_YELLOW);
  Countdown_Timer.color_foreground(COLOR_WHITE);
  Countdown_Timer.print_value(false);

  // Debug Screen 
  // Compute Times  
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
  
  // Prep Gadgets for Radio screen. 

  // Radio Channel Frequency gadgets Properties for Multi Screen.
  Radio_Channel tmp_radio_channel;  // Leaving defaults
  //Radio_Channel_Properties tmp_radio_channel_props;  // Leaving defaults

  // Create Radio Channel Frequency gadgets.
  for (int x = 0; x < Radio_Channel_Count; x++)
  {
    Radio_Channels.push_back(tmp_radio_channel);
    Radio_Channels[x].create(x, "FREQ", "Frequency", -1, COLOR_BLUE, COLOR_BLACK);
  }

  // Radio Channel Frequency gadgets Properties for Multi Screen.
  Radio_Channel tmp_many_radio_channel;
  Radio_Channel_Properties tmp_many_radio_channel_props;

  tmp_many_radio_channel_props.SHOW_FREQUENCY = false;
  tmp_many_radio_channel_props.BAR_SIZE = 15;
  tmp_many_radio_channel_props.SHOW_MIN_MAX = false;
  tmp_many_radio_channel_props.SHOW_SIGNAL = true;
  tmp_many_radio_channel_props.SIGNAL_LABEL = "  sig: ";
  tmp_many_radio_channel_props.SHOW_NOISE = false;

  tmp_many_radio_channel.PROP = tmp_many_radio_channel_props;

  // Create Radio Channel Frequency gadgets.
  for (int x = 0; x < Many_Radio_Channel_Count; x++)
  {
    Many_Radio_Channels.push_back(tmp_many_radio_channel);
    Many_Radio_Channels[x].create(x, "FREQ", "Frequency", -1, COLOR_BLUE, COLOR_BLACK);
  }

  //tbads_b_Data.create(1, "ADS_B", "ADS_B", TitleSize, CRT_get_color_pair(COLOR_BLACK, COLOR_WHITE), 0);

  tbRadio_Log.create(1, "RADIO", "RADIO", TitleSize, CRT_get_color_pair(COLOR_BLACK, COLOR_WHITE), 0);
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
    YCYBRPos = YCYBRPos;
    XCYBRPos = XSplit;
    YCYBRSize = YMax;
    XCYBRSize = XCYBRSize;

    CYBR_Sleep_Count.resize(YCYBRSize);
    CYBR_Anims.resize(YCYBRSize);

    // Build Window
    winCYBR = newwin(YCYBRSize, XCYBRSize, YCYBRPos, XCYBRPos);
    
    // Set Y Split
    // YSplit = YSplit + YCYBRSize;

    // CYBR Window Border
    wborder(winCYBR,' ',' ',' ',' ',' ',' ',' ',' ') ;
    
    // Create CYBR Screen
    wrefresh(winCYBR);

    // Set window color
    wbkgd(winCYBR, COLOR_PAIR(CRT_get_color_pair(COLOR_BLACK, COLOR_RED)));
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

    ADSB.PROP.POSY = 1;
    ADSB.PROP.POSX = 53;

    VERSION.PROP.POSY = 0;
    VERSION.PROP.POSX = XStatusSize - 6 - TitleSize;
    VERSION.PROP.SIZEX = 5;
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
    winDebug = newwin(YDebugSize, XDebugSize, YDebugPos, XDebugPos);

    // Set Y Split
    YSplit = YSplit + YDebugSize;

    // Debug Window Border
    wborder(winDebug,' ',' ',' ',' ',' ',' ',' ',' ') ;
    
    // Create Debug Screen
    wrefresh(winDebug);

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

    // Set window color
    wbkgd(winDebug, COLOR_PAIR(CRT_get_color_pair(COLOR_RED, COLOR_WHITE)));
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
    winTimer = newwin(YTimerSize, XTimerSize, YTimerPos, XTimerPos);

    // Set Y Split
    YSplit = YSplit + YTimerSize;

    // Timer Window Border
    wborder(winTimer,' ',' ',' ',' ',' ',' ',' ',' ') ;
    
    // Create Timer Screen
    wrefresh(winTimer);
    
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

    // Set window color
    // wbkgd(winTimer, COLOR_PAIR(5));  //  Set color in window.
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
    tbConsole.move_resize(YConsolePos, XConsolePos, YConsoleSize, XConsoleSize);

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
  // Color Radio Buttons Panel
  if (ScrStat.Window_Radio_Buttons.value() == true)
  {
    // Recreate XSplit Size
    //XSplit = XSplit - XCPickerSize * 2;

    // Calculate Size and Position
    YRadioPos = YSplit + YRadioStatusSize;
    XRadioPos = 0;

    // Prep Radio Buttons

    bzRadio.clear();

    bzRadio.NEW_BUTTON_PROP.VALUE = 0;
    bzRadio.NEW_BUTTON_PROP.TYPE = 0;
    bzRadio.NEW_BUTTON_PROP.COLOR = COLOR_WHITE;
    bzRadio.NEW_BUTTON_PROP.SIZEY = YBRadioSize;
    bzRadio.NEW_BUTTON_PROP.SIZEX = XBRadioSize;
    bzRadio.NEW_BUTTON_PROP.BORDER.RIGHT = '|';

    //bzRadio.move_resize(0, YRadioPos + (YBRadioSize *0), XRadioPos, YBRadioSize, XBRadioSize);
    //bzRadio.create_button(0, "RADIOOFF", "%OFF", 0, 0, CRT_get_color_pair(COLOR_RED, COLOR_WHITE), 0);
    bzRadio.NEW_BUTTON_PROP.ID = 0;
    bzRadio.NEW_BUTTON_PROP.NAME = "RADIOOFF";
    bzRadio.NEW_BUTTON_PROP.LABEL = "\nOFF";
    bzRadio.NEW_BUTTON_PROP.BCOLOR = COLOR_RED;
    bzRadio.NEW_BUTTON_PROP.POSY = YRadioPos + (YBRadioSize *0);
    bzRadio.NEW_BUTTON_PROP.POSX = XRadioPos;
    bzRadio.create_button();
    
    
    //bzRadio.move_resize(1, YRadioPos + (YBRadioSize *1), XRadioPos, YBRadioSize, XBRadioSize);
    //bzRadio.create_button(1, "LAFS", "AIR%LAF%SCAN", 0, 0, CRT_get_color_pair(COLOR_BLUE, COLOR_WHITE), 0);
    bzRadio.NEW_BUTTON_PROP.ID = 1;
    bzRadio.NEW_BUTTON_PROP.NAME = "LAFS";
    bzRadio.NEW_BUTTON_PROP.LABEL = "AIR\nLAF\nSCAN";
    bzRadio.NEW_BUTTON_PROP.BCOLOR = COLOR_BLUE;
    bzRadio.NEW_BUTTON_PROP.POSY = YRadioPos + (YBRadioSize *1);
    bzRadio.NEW_BUTTON_PROP.POSX = XRadioPos;
    bzRadio.create_button();

    //bzRadio.move_resize(2, YRadioPos + (YBRadioSize *2), XRadioPos, YBRadioSize, XBRadioSize);
    //bzRadio.create_button(2, "CBS", "%CB%SCAN", 0, 0, CRT_get_color_pair(COLOR_BLUE, COLOR_WHITE), 0);
    bzRadio.NEW_BUTTON_PROP.ID = 2;
    bzRadio.NEW_BUTTON_PROP.NAME = "CBS";
    bzRadio.NEW_BUTTON_PROP.LABEL = "\nCB\nSCAN";
    bzRadio.NEW_BUTTON_PROP.BCOLOR = COLOR_BLUE;
    bzRadio.NEW_BUTTON_PROP.POSY = YRadioPos + (YBRadioSize *2);
    bzRadio.NEW_BUTTON_PROP.POSX = XRadioPos;
    bzRadio.create_button();

    //bzRadio.move_resize(3, YRadioPos + (YBRadioSize *3), XRadioPos, YBRadioSize, XBRadioSize);
    //bzRadio.create_button(3, "NOAA", "%NOAA", 0, 0, CRT_get_color_pair(COLOR_GREEN, COLOR_WHITE), 0);
    bzRadio.NEW_BUTTON_PROP.ID = 3;
    bzRadio.NEW_BUTTON_PROP.NAME = "NOAA";
    bzRadio.NEW_BUTTON_PROP.LABEL = "\nNOAA";
    bzRadio.NEW_BUTTON_PROP.BCOLOR = COLOR_GREEN;
    bzRadio.NEW_BUTTON_PROP.POSY = YRadioPos + (YBRadioSize *3);
    bzRadio.NEW_BUTTON_PROP.POSX = XRadioPos;
    bzRadio.create_button();

    //bzRadio.move_resize(4, YRadioPos + (YBRadioSize *4), XRadioPos, YBRadioSize, XBRadioSize);
    //bzRadio.create_button(4, "EMERGENCY", "%EMER%GENCY", 0, 0, CRT_get_color_pair(COLOR_YELLOW, COLOR_WHITE), 0);
    bzRadio.NEW_BUTTON_PROP.ID = 4;
    bzRadio.NEW_BUTTON_PROP.NAME = "EMERGENCY";
    bzRadio.NEW_BUTTON_PROP.LABEL = "\nEMER\nGENCY";
    bzRadio.NEW_BUTTON_PROP.BCOLOR = COLOR_YELLOW;
    bzRadio.NEW_BUTTON_PROP.POSY = YRadioPos + (YBRadioSize *4);
    bzRadio.NEW_BUTTON_PROP.POSX = XRadioPos;
    bzRadio.create_button();
  }

  // ---------------------------------------------------------------------------------------
  // Radio Panel
  if (ScrStat.Window_Radio.value() == true || ScrStat.Window_Many_Radio.value() == true)
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

    // Set Y Split
    YSplit = YSplit + YRadioStatusSize;

    // Create Screen
    wrefresh(winRadioStatus);

    // Radio Title Bar
    tiRadio.PROP.POSY = YRadioStatusPos;
    tiRadio.PROP.POSX = XRadioStatusPos;
    tiRadio.PROP.SIZEY = YRadioStatusSize;
    tiRadio.PROP.SIZEX = XRadioStatusSize;
    tiRadio.PROP.SIZE = TitleSize;

    tiRadio.PROP.LABEL = "RADIO";
    tiRadio.PROP.BCOLOR = COLOR_BLACK;
    tiRadio.PROP.COLOR = COLOR_WHITE;
    tiRadio.create();

    // Set window color
    wbkgd(winRadioStatus, COLOR_PAIR(CRT_get_color_pair(COLOR_BLUE, COLOR_WHITE)));
  }

  if (ScrStat.Window_Radio.value() == true)
  {
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
    strBotLine = strBotLine.append(XRadioSize-1, '_');  // meh!

    // Display Channels
    // Try to not fill, and not exceed, the screen with Radio Gadgets.
    int in_max_col = (XRadioSize - XGadChannelPos) / XGadChannelSize;
    int in_max_row = YRadioSize / YGadChannelSize ;
    int pos = 0;
    Radio_Channel_Max_Display_Count = 0;

    for(int x=0; x<in_max_col && pos < Radio_Channel_Count; x++)  // Colum
    {
      for(int y=0; y<in_max_row && pos < Radio_Channel_Count; y++) // Row
      {
        Radio_Channels[pos].move_resize(YRadioPos + YGadChannelPos + (YGadChannelSize *y), 
                                              1 + XRadioPos + XGadChannelPos + (XGadChannelSize *x), 
                                              YGadChannelSize, XGadChannelSize);
        pos++;
        Radio_Channel_Max_Display_Count++;
      }
    }

    // Turn off remaining Gadgets
    for(int rem_pos = Radio_Channel_Max_Display_Count; rem_pos < Radio_Channel_Count; rem_pos++)
    {
      Radio_Channels[rem_pos].PROP.TYPE = -1;
    }
  }

  // ---------------------------------------------------------------------------------------
  // Many Radio Panel
  if (ScrStat.Window_Many_Radio.value() == true)
  // Main Radio Screen
  {
    // Radio Window
    // Calculate Size and Position
    YManyRadioPos = YSplit;
    XManyRadioPos = XManyRadioPos;
    YManyRadioSize = YMax - YSplit - YTabSize;
    XManyRadioSize =  XSplit;

    YSplit = YSplit + YRadioStatusSize;

    // Build Window
    winManyRadio = newwin(YManyRadioSize, XManyRadioSize, YManyRadioPos, XManyRadioPos);

    // Set Y Split
    YSplit = YSplit + YManyRadioSize;

    // Radio Window Border
    wborder(winManyRadio,' ',' ',' ',' ',' ',' ',' ',' ') ;

    // Create Screen
    wrefresh(winManyRadio);

    // Radio Title Bar
    tiRadio.PROP.POSY = YRadioStatusPos;
    tiRadio.PROP.POSX = XRadioStatusPos;
    tiRadio.PROP.SIZEY = YRadioStatusSize;
    tiRadio.PROP.SIZEX = XRadioStatusSize;
    tiRadio.PROP.SIZE = TitleSize;

    tiRadio.PROP.LABEL = "(multi) RADIO";
    tiRadio.PROP.BCOLOR = COLOR_BLACK;
    tiRadio.PROP.COLOR = COLOR_WHITE;
    tiRadio.create();

    // Set window color
    wbkgd(winManyRadio, COLOR_PAIR(0));

    // the bottom line of the Many Radio.
    strBotLine = "";
    strBotLine = strBotLine.append(XManyRadioSize-1, '_');

    // Display Channels
    // Try to not fill, and not exceed, the screen with Radio Gadgets.
    int in_max_col = (XManyRadioSize - XManyGadChannelPos) / XManyGadChannelSize;
    int in_max_row = YManyRadioSize / YManyGadChannelSize ;
    int pos = 0;
    Many_Radio_Channel_Max_Display_Count = 0;

    for(int x=0; x<in_max_col && pos < Many_Radio_Channel_Count; x++)  // Colum
    {
      for(int y=0; y<in_max_row && pos < Many_Radio_Channel_Count; y++) // Row
      {
        Many_Radio_Channels[pos].move_resize(YManyRadioPos + YManyGadChannelPos + (YManyGadChannelSize *y), 
                                              1 + XManyRadioPos + XManyGadChannelPos + (XManyGadChannelSize *x), 
                                              YManyGadChannelSize, XManyGadChannelSize);
        pos++;
        Many_Radio_Channel_Max_Display_Count++;
      }
    }
    
    // Turn off remaining Gadgets
    for(int rem_pos = Many_Radio_Channel_Max_Display_Count; rem_pos < Many_Radio_Channel_Count; rem_pos++)
    {
      Many_Radio_Channels[rem_pos].PROP.TYPE = -1;
    }
  }

  if (ScrStat.Window_Log_Screen.value() == true)
  {
    // Radio Window
    // Calculate Size and Position
    YLog_ScreenPos = YSplit;
    XLog_ScreenPos = XRadioPos;
    YLog_ScreenSize = YMax - YSplit - YTabSize;
    XLog_ScreenSize =  XSplit;

    // Build Window
    winLog_Screen = newwin(YLog_ScreenSize, XLog_ScreenSize, YLog_ScreenPos, XLog_ScreenPos);

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

    // Radio Window Border
    wborder(winLog_Screen,' ',' ',' ',' ',' ',' ',' ',' ') ;

    // Create Screen
    wrefresh(winLog_Screen);

    // Set window color
    wbkgd(winLog_Screen, COLOR_PAIR(0));

    // the bottom line of the Radio.
    strBotLine = "";
    strBotLine = strBotLine.append(XLog_ScreenSize-1, '_');
  
    // Display OS Log
    tbRadio_Log.move_resize(YLog_ScreenPos, XLog_ScreenPos, YLog_ScreenSize, XLog_ScreenSize);
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
    
    tiADS_B_Screen.PROP.LABEL = "ADS_B";
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
    bzTabs.NEW_BUTTON_PROP.BORDER.TOP_RIGHT = '|';
    bzTabs.NEW_BUTTON_PROP.BORDER.RIGHT = '|';
    bzTabs.NEW_BUTTON_PROP.BORDER.BOT_RIGHT = '|';

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
    bzTabs.NEW_BUTTON_PROP.POSX = XTabPos + (XTabSize * 1);
    bzTabs.create_button();

    bzTabs.NEW_BUTTON_PROP.ID = 3;
    bzTabs.NEW_BUTTON_PROP.NAME = "TABRADIO";
    bzTabs.NEW_BUTTON_PROP.LABEL = "Radio";
    bzTabs.NEW_BUTTON_PROP.POSY = YTabPos + (YTabSize *0);
    bzTabs.NEW_BUTTON_PROP.POSX = XTabPos + (XTabSize * 2 +2);
    bzTabs.create_button();

    bzTabs.NEW_BUTTON_PROP.ID = 4;
    bzTabs.NEW_BUTTON_PROP.NAME = "TABMANYRADIO";
    bzTabs.NEW_BUTTON_PROP.LABEL = "Radio\n(Multi)";
    bzTabs.NEW_BUTTON_PROP.POSY = YTabPos + (YTabSize *0);
    bzTabs.NEW_BUTTON_PROP.POSX = XTabPos + (XTabSize * 3 +2);
    bzTabs.create_button();

    bzTabs.NEW_BUTTON_PROP.ID = 6;
    bzTabs.NEW_BUTTON_PROP.NAME = "TAB_ADS_B_SCREEN";
    bzTabs.NEW_BUTTON_PROP.LABEL = "ADS";
    bzTabs.NEW_BUTTON_PROP.POSY = YTabPos + (YTabSize *0);
    bzTabs.NEW_BUTTON_PROP.POSX = XTabPos + (XTabSize * 4 +4);
    bzTabs.create_button();

    bzTabs.NEW_BUTTON_PROP.ID = 8;
    bzTabs.NEW_BUTTON_PROP.NAME = "TAB_LOG_SCREEN";
    bzTabs.NEW_BUTTON_PROP.LABEL = "Log";
    bzTabs.NEW_BUTTON_PROP.POSY = YTabPos + (YTabSize *0);
    bzTabs.NEW_BUTTON_PROP.POSX = XTabPos + (XTabSize * 5 +6);
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
  if(sdSysData.Lights_On == false)
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
  if(sdSysData.booDay_On == true)
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
  
  // Display Radio Indicator
  /*
  if(true)
  {
    wattron(winStatus, A_REVERSE);
    mvwprintw(winStatus, 0, 53, " RADIO ");
    wattroff(winStatus, A_REVERSE);
  }
  else
  {
    mvwprintw(winStatus, 0, 53, "       "); 
  }
  */

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
  int working_pos = 0;
  int color_pair = 0;

  int anims = 0;

  mvwprintw(winCYBR, 0, 0, "%d",sdSysData.tmeCURRENT_FRAME_TIME/100);

  mvwprintw(winCYBR, CYBR_YLn, 0, "  ");
  CYBR_Sleep_Count[CYBR_YLn] = 0;
  CYBR_Anims[CYBR_YLn] = 0;

  CYBR_YLn = CYBR_YLn -1;
  if (CYBR_YLn <0)
  {
    CYBR_YLn = YCYBRSize -1;
  }
  wattron(winCYBR, A_REVERSE);
  mvwprintw(winCYBR, CYBR_YLn, 0, "/\\");
  wattroff(winCYBR, A_REVERSE);

  // Sleep 
  working_pos = position_of_scale(YCYBRSize, 20, sdSysData.dblPREVSLEEPTIME.get_data());
  CYBR_Sleep_Count[working_pos]++;
  mvwprintw(winCYBR, working_pos, 0, "%x", CYBR_Sleep_Count[working_pos]);

  // Anims
  for(int gr = 0; gr <=3; gr++)
  {
    if(sdSysData.intCHANNEL_GROUP_EVENTS_COUNTS.at(gr)>0)
    {
      anims = anims + sdSysData.intCHANNEL_GROUP_EVENTS_COUNTS.at(gr);
    }
  }
  if (anims > 0)
  {
    working_pos = position_of_scale(YCYBRSize, 256, anims);
    CYBR_Anims[working_pos]++;
    color_pair = CRT_get_color_pair(COLOR_BLACK, COLOR_WHITE);
    wattron(winCYBR, A_REVERSE);
    wattron(winCYBR, COLOR_PAIR(color_pair));
    mvwprintw(winCYBR, working_pos, 0, "%x", CYBR_Anims[working_pos]);
    wattroff(winCYBR, COLOR_PAIR(color_pair));
    wattroff(winCYBR, A_REVERSE);
  }

  // Commit all our changes to the status portion of the screen (winTop)
  wrefresh(winCYBR);
}

// ---------------------------------------------------------------------------------------
void Screen3::output_debug2(system_data &sdSysData, Keys &keywatch, ScreenStatus &ScrStat, TheMouse &mouse)
// Displays clock timings, event count, and mouse info.
{
  string strRange = "";
  string strLevel = "";

  // Print Timings
  Compute_Time.label("Compute: " + to_string(sdSysData.dblCOMPUTETIME.get_data()) + " ");
  Compute_Time.guage_bar(winDebug, 0, 7, sdSysData.dblCOMPUTETIME.get_data(), sdSysData.tmeCURRENT_FRAME_TIME);
  
  Sleep_Time.label("Sleep:   " + to_string(sdSysData.dblPREVSLEEPTIME.get_data()) + " ");
  Sleep_Time.guage_bar(winDebug, 1, 7, sdSysData.dblPREVSLEEPTIME.get_data(), sdSysData.tmeCURRENT_FRAME_TIME);
  
  Cycle_Time.label("Cycle:   " + to_string(sdSysData.dblCYCLETIME.get_data()) + " ");
  Cycle_Time.guage_bar(winDebug, 2, 7, sdSysData.dblCYCLETIME.get_data(), sdSysData.tmeCURRENT_FRAME_TIME);
  
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
void Screen3::output_timer(system_data &sdSysData, Keys &keywatch, ScreenStatus &ScrStat, TheMouse &mouse)
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
void Screen3::printout(ScreenStatus &ScrStat)
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
void Screen3::radio_status(system_data &sdSysData, ScreenStatus &ScrStat)
// Shows the Radio Status Window
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

    wrefresh(winRadioStatus);
    
    // Print Title Bar
    tiRadio.draw(true);

    // Changes to Radio Coord cleared.
    sdSysData.RADIO_COORD.DEVICE_STATUS.CHANGED = false;
  }
}

// ---------------------------------------------------------------------------------------
void Screen3::radio(system_data &sdSysData, ScreenStatus &ScrStat)
// Shows the Player Window
{
  // Print Status
  radio_status(sdSysData, ScrStat);

  // Print Radio Information
  bzRadio.draw(ScrStat.Needs_Refresh, sdSysData.tmeCURRENT_FRAME_TIME);

  // Print Channel Gadgets
  for(int pos = 0; pos < Radio_Channel_Max_Display_Count; pos++)
  {
    Radio_Channels[pos].draw(ScrStat.Needs_Refresh, sdSysData.tmeCURRENT_FRAME_TIME);
  }   
}

// ---------------------------------------------------------------------------------------
void Screen3::manyradio(system_data &sdSysData, ScreenStatus &ScrStat)
// Shows the Player Window
{
  // Print Status
  radio_status(sdSysData, ScrStat);

  // Print Radio Information

  bzRadio.draw(ScrStat.Needs_Refresh, sdSysData.tmeCURRENT_FRAME_TIME);

  // Print Channel Gadgets
  for(int pos = 0; pos < Many_Radio_Channel_Max_Display_Count; pos++)
  {
    Many_Radio_Channels[pos].draw(ScrStat.Needs_Refresh, sdSysData.tmeCURRENT_FRAME_TIME);
  }
}


// ---------------------------------------------------------------------------------------
void Screen3::ads_b_screen(system_data &sdSysData, ScreenStatus &ScrStat)
// Shows the Player Window
{
  // Print ADS_B Buttons
  bzADS_B.draw(ScrStat.Needs_Refresh, sdSysData.tmeCURRENT_FRAME_TIME);

  ADSB_Grid.draw(ScrStat.Needs_Refresh, sdSysData.tmeCURRENT_FRAME_TIME, ADSB_GRID_PANEL);

  if(ScrStat.Needs_Refresh == true)
  {
    /*
    Default_ADS_B.update_value("Data", sdSysData.tmeCURRENT_FRAME_TIME);

    Default_ADS_B.draw(ScrStat.Needs_Refresh, sdSysData.tmeCURRENT_FRAME_TIME);
    */
    // Refresh Screen
    //wrefresh(winADS_B_Screen);

    // Print Title
    tiADS_B_Screen.draw(true);
  }
}

// ---------------------------------------------------------------------------------------
void Screen3::log_screen(system_data &sdSysData, ScreenStatus &ScrStat)
// Shows the Player Window
{
  // Print Log File
  tbRadio_Log.draw(ScrStat.Needs_Refresh);

  // Print Title
  tiLog_Screen.draw(ScrStat.Needs_Refresh);
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
  bzButtons.set_value("LIGHTSOFF", int(sdSysData.Lights_On));
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
  if (ScrStat.Window_Radio.value() == true)
  {
    radio(sdSysData, ScrStat);
  }

  // Draw Radio window.
  if (ScrStat.Window_Many_Radio.value() == true)
  {
    manyradio(sdSysData, ScrStat);
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