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
#include "player.h"
#include "gadgets.h"
#include "gadgets_radio.h"
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
  int TitleSize = 14;

  // Screen Size Variables
  int YMax = 0;
  int XMax = 0;

  // CYBR Screen Variables --------------------
  int YCYBRPos = 0;
  int XCYBRPos = 0;
  int YCYBRSize = -1;
  int XCYBRSize = 2;

  WINDOW * winCYBR;

  // CYBR Variables
  int CYBR_YLn = 0;

  deque<int> CYBR_Sleep_Count;
  deque<int> CYBR_Anims;

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
  Title_Bar tiConsole;

  public:
  Text_Box tbConsole;
  
  private:
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
  int XGadChannelSize = 40;
  int YGadChannelPos = 0;  // Frequency Gadges Start Position
  int XGadChannelPos = 8;

  WINDOW * winRadio;
  Title_Bar tiRadio;

  public:
  // Radio Frequency Gadgets for Radio Screen
  Button_Zone_Manager bzRadio;

  int Radio_Channel_Count = 50;   // Remove this limit in future if needed.
  int Radio_Channel_Max_Display_Count = -1;
  deque<Radio_Channel> Radio_Channels;

  private:
  // Radio Status
  int YRadioStatusPos = -1;
  int XRadioStatusPos = 0;
  int YRadioStatusSize = 1;
  int XRadioStatusSize = -1;

  WINDOW * winRadioStatus;

  // Many Radio Screen Variables --------------------
  int YManyRadioPos = -1;
  int XManyRadioPos = 0;
  int YManyRadioSize = -1;
  int XManyRadioSize = -1;

  int YManyGadChannelSize = 2;  // Frequency Gadges Size
  int XManyGadChannelSize = 27;
  int YManyGadChannelPos = 0;  // Frequency Gadges Start Position
  int XManyGadChannelPos = 8;

  WINDOW * winManyRadio;
  Title_Bar tiManyRadio;

  public:
  // Radio Frequency Gadgets for Many_Radio Screen
  int Many_Radio_Channel_Count = 50;  // Remove this limit in future if needed.
  int Many_Radio_Channel_Max_Display_Count = -1;
  deque<Radio_Channel> Many_Radio_Channels;

  private:
  // ADS_B Screen Variables --------------------

  int YADS_B_ScreenPos = -1;
  int XADS_B_ScreenPos = 0;
  int YADS_B_ScreenSize = -1;
  int XADS_B_ScreenSize = -1;

  int YBADS_BSize = 4; // ADS_B Button Standard Sizes
  int XBADS_BSize = 8;

  WINDOW * winADS_B_Screen;
  Title_Bar tiADS_B_Screen;

  public:
  // ADS_B Buttons
  Button_Zone_Manager bzADS_B;

  // ADS_B Text Box Data
  ADS_B_List_Box tbads_b_Data;

  private:
  // Log Screen Variables --------------------
  int YLog_ScreenPos = -1;
  int XLog_ScreenPos = 0;
  int YLog_ScreenSize = -1;
  int XLog_ScreenSize = -1;

  int YTRadio_LogSize = 5;

  WINDOW * winLog_Screen;
  Title_Bar tiLog_Screen;

  public:
  Text_Box  tbRadio_Log;

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

  void buttons_menu_home(system_data &sdSysData);

  void buttons_menu_control(system_data &sdSysData);

  void buttons_menu_system(system_data &sdSysData);

  void buttons_menu_overhead_color(system_data &sdSysData);

  void init();

  void set(system_data &sdSysData, ScreenStatus &ScrStat);

  void reset(ScreenStatus &ScrStat);
  // ---------------------------------------------------------------------------------------

  // ---------------------------------------------------------------------------------------
  void output_status(system_data &sdSysData, Keys &keywatch, ScreenStatus &ScrStat, TheMouse &mouse);

  // ---------------------------------------------------------------------------------------
  void output_CYBR(system_data &sdSysData, ScreenStatus &ScrStat);

  // ---------------------------------------------------------------------------------------
  void output_debug2(system_data &sdSysData, Keys &keywatch, ScreenStatus &ScrStat, TheMouse &mouse);

  // ---------------------------------------------------------------------------------------
  void output_timer(system_data &sdSysData, Keys &keywatch, ScreenStatus &ScrStat, TheMouse &mouse);
  
  // ---------------------------------------------------------------------------------------
  void printout(ScreenStatus &ScrStat);
  // ---------------------------------------------------------------------------------------
  void the_player(ScreenStatus &ScrStat);

  void window_player_clear();

  void window_player_draw_frame(PLAYER_FRAME &qframe);

  string buffer();

    // ---------------------------------------------------------------------------------------
  void radio_status(system_data &sdSysData, ScreenStatus &ScrStat);

  // ---------------------------------------------------------------------------------------
  void radio(system_data &sdSysData, ScreenStatus &ScrStat);
  
  // ---------------------------------------------------------------------------------------
  void manyradio(system_data &sdSysData, ScreenStatus &ScrStat);


  // ---------------------------------------------------------------------------------------
  void ads_b_screen(system_data &sdSysData, ScreenStatus &ScrStat);

  // ---------------------------------------------------------------------------------------
  void log_screen(system_data &sdSysData, ScreenStatus &ScrStat);

  // ---------------------------------------------------------------------------------------

  // ---------------------------------------------------------------------------------------
  // Main screen routine.
  // Draw the console, starting with status window, then whatever windows set to true.

  void output(system_data &sdSysData, Keys &keywatch, ScreenStatus &ScrStat, TheMouse &mouse);
};



#endif