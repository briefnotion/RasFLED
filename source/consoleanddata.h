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
#include <string>
#include <deque>

// Boost libraries
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>

// RASFled related header files
#include "definitions.h"
#include "fled_time.h"
#include "helper.h"
#include "stringthings.h"
#include "system.h"
#include "gadgets.h"
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

  unsigned long Update_Time = 0;
  
  // Mouse position and button position
  TheMouse mouse;

  public:

  Screen3 Screen;

  Keys keywatch;

  ScreenStatus ScrStat;

  PLAYER the_player;

  TIMED_IS_READY Console_Display;

  void update_ADS_B_gadgets(unsigned long &tmeCurrentMillis, system_data &sdSysData);

  void update_automobile_gadgets(unsigned long &tmeCurrentMillis, system_data &sdSysData);

  bool load_reel(fstream &fsPlayer, string filename);

  bool play_next_movie(fstream &fsPlayer);

  bool print_movie_frame(fstream &fsPlayer);

  void set_screen(system_data &sdSysData);

  void printi(string in);

  void printwait(string in);

  void readkeyboardinput2();

  void processkeyboadinput(system_data &sdSysData);

  void tab_open_console(system_data &sdSysData);

  void tab_open_player(system_data &sdSysData);

  void tab_open_automobile(system_data &sdSysData);

  void tab_open_radio(system_data &sdSysData);

  void tab_open_many_radio(system_data &sdSysData);

  void tab_open_ads_b_screen(system_data &sdSysData);

  void tab_open_log_screen(system_data &sdSysData);

  void tab_open_alerts(system_data &sdSysData);

  void tab_handler(string Button_Name, system_data &sdSysData);

  void processmouseinput(system_data &sdSysData);

  void update_displayed_time(unsigned long &time);
  
  void output(system_data &sdSysData);

  void display(fstream &fsPlayer, system_data &sdSystem, unsigned long tmeCurrentMillis);
};
// -------------------------------------------------------------------------------------



#endif