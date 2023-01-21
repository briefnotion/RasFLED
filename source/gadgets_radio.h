// ***************************************************************************************
// *
// *    Core       | Everything within this document is proprietary to Core Dynamics.
// *    Dynamics   | Any unauthorized duplication will be subject to prosecution.
// *
// *    Department : (R+D)^2                        Name: gadgets_radio.h
// *       Sub Dept: Programming
// *    Location ID: 856-45B
// *                                                      (c) 2856 - 2858 Core Dynamics
// ***************************************************************************************

#ifndef GADGETS_RADIO_H
#define GADGETS_RADIO_H

// Standard Header Files
#include <stdio.h>
#include <ncurses.h>
#include <string.h>
#include <deque>

#include "fled_time.h"
#include "stringthings.h"
#include "system.h"

#include "gadgets.h"
#include "helper_ncurses.h"
#include "api_rtlairband.h"

#include "aircraft_coordinator.h"

using namespace std;


class Mini_Compass_Properties
// Properties (duh)
{
  public: 
  float HEADING = 0;

  int COLOR = 0;
  int BCOLOR = 0;
  
  int POSY = 0;
  int POSX = 0;

  bool CLEARED = true;

  bool UPDATE_INDICATION = false;
};

class Mini_Compass
{
  private:
  TIMED_PING UPDATE_INDICATION_TIMER;

  bool CHANGED = false;
  bool HAS_BLANK = false;

  int INDICATED_BLINK_TIME = 250;

  // DEBUG_COUNTER
  int Counter = 0;

  public:
  Mini_Compass_Properties PROP;

  bool changed();

  void set_heading(float Heading, unsigned long tmeFrame_Time);

  void set_heading(float Heading);
  
  void clear();

  void set_color(int Background_Color, int Color);

  bool draw(PANEL &Panel, bool Refresh, unsigned long tmeFrame_Time);

  bool draw(PANEL &Panel, bool Refresh);
};

// -------------------------------------------------------------------------------------
//  ADS-B Classes

// -------------------------------------------------------------------------------------
//  ADSB_Channel Classes
class ADSB_Channel_Properties
// Properties (duh)
{
  public: 

  int ID;
  string NAME = "";
  string LABEL = "";

  int COLOR = COLOR_WHITE;
  int BCOLOR = COLOR_BLACK;
  
  int POSY = 0;
  int POSX = 0;
  int SIZEY = 5;
  int SIZEX = 21;

  bool CHANGED = true;

  AIRCRAFT AIRCRAFT_DATA;
};

class ADSB_Channel
// Routines for create, draw, modify, and behavior.
// Note: Function needs frame time to function.
{
  private:

  // Gadget window
  PANEL ADSB_PANEL;

  // Was gadget redrawn during the previous draw cycle.
  bool WAS_REDRAWN = false;

  int EXPIRATION_TIME = 15000;
  TIMED_PING EXPIREED;

  string compass_mini_top(float Heading);

  string compass_mini_bottom(float Heading);

  //Debug
  int Counter = 0;

  public:

  // Text Fields  
  Text_Field FLIGHT;
  Text_Field SQUAWK;

  Text_Field ALTITUDE;
  Text_Field ALTITUDE_IND;
  Text_Field NAV_ALTITUDE_MCP; 

  Text_Field D_VERTICAL_RATE;
  Text_Field D_VERTICAL_RATE_IND;

  Text_Field SPEED;
  Text_Field SPEED_IND;

  Text_Field TRACK;
  Mini_Compass TRACK_MINI_COMPASS;
  
  Text_Field NAV_HEADING;
  Mini_Compass NAV_HEADING_MINI_COMPASS;

  Text_Field SIG_STR_IND;
  Text_Field COORD_TTL_IND;
  Text_Field DATA_TTL_IND;

  Text_Field MESSAGE;

  ADSB_Channel_Properties PROP;  

  void create();

  void clear();

  bool changed();

  void update_value(string Flight, string Squawk, string Speed, string Track, 
                                string D_Vertical_Rate, string Altitude, 
                                unsigned long tmeFrame_Time);

  void update_aircraft(AIRCRAFT Aircraft, unsigned long &tmeCurrentMillis);

  bool draw(bool Refresh, unsigned long tmeFrame_Time);
};


//  ADSB_Channel Classes
class ADSB_Channel_Grid_Properties
// Properties (duh)
{
  public: 

  int POSY = 0;
  int POSX = 0;
  int SIZEY = 0;
  int SIZEX = 0;

  bool CHANGED = true;
  bool NEEDS_REFRESH_DATA = true;

  AIRCRAFT_DATA AIRCRAFT_LIST;
};


class ADSB_Channel_Grid
// Routines for create, draw, modify, and behavior.
// Note: Function needs frame time to function.
{
  private:
  deque<ADSB_Channel> ADSB_Channel_q;

  ADSB_Channel test;

  int ADSB_Channel_Count = 0;
  
  int find_HEX(string Hex);

  int find_expired();

  Text_Field TOP_BAR;
  Text_Field TIME;
  Text_Field AIRCRAFT_COUNT_TITLE;
  Text_Field AIRCRAFT_COUNT;
  Text_Field POSITIONED_AIRCRAFT_TITLE;
  Text_Field POSITIONED_AIRCRAFT;
  BAR DELTA_MESSAGES_BAR;

  public:

  ADSB_Channel_Grid_Properties PROP;  

  bool IS_ACTIVE = false;

  void create();

  void update(system_data &sdSysData, unsigned long &tmeCurrentMillis);

  bool draw(bool Refresh, unsigned long tmeFrame_Time, PANEL ADSB_Grid_Panel);
};

// -------------------------------------------------------------------------------------
//  Radio_Channel Classes
class Radio_Channel_Properties
// Properties (duh)
{
  public: 

  int ID;
  string NAME = "";
  string LABEL = "";
  
  API_SQUELCH_DESTINATION VALUE;

  int TYPE = -1; // Type -1 = Hidden. Automatic Enabling.
  int COLOR = 0;
  int BCOLOR = 0;
  
  int POSY = 0;
  int POSX = 0;
  int SIZEY = 0;
  int SIZEX = 0;

  bool SKIP = false;
  bool HELD = false;

  bool CLICKED = false;
  bool CHANGED = false;

  bool SHOW_FREQUENCY = true;
  string FREQUENCY_LABEL = "  FREQ:";
  
  int BAR_SIZE = 15;
  bool SHOW_MIN_MAX = true;

  bool SHOW_SIGNAL = true;
  string SIGNAL_LABEL = "SIGNAL: ";

  bool SHOW_NOISE = true;
  string NOISE_LABEL = " NOISE: ";
};

class Radio_Channel
// Routines for create, draw, modify, and behavior.
// Note: Function needs frame time to function.
{
  private:

  // Gadget window
  PANEL FREQUENCY_PANEL;

  Button_Zone_Manager bzGadget;
  int Button_YSize = 3;
  int Button_XSize = 9;

  // Show frequency levels in progress bars
  BAR BAR_NOISE_LEVEL;
  BAR BAR_SIGNAL_LEVEL;

  // Timing
  TIMED_PING LINGER_DIRTY_SIGNAL;
  TIMED_PING VISIBLE_UPDATE_SIGNAL;
  int LINGER_TIME = 7000;
  int VISIBLE_UPATE_TIME = 500;

  // Was gadget redrawn during the previous draw cycle.
  bool WAS_REDRAWN = false;

  //Debug
  int Counter = 0;

  public:

  Radio_Channel_Properties PROP;  

  void modify(int id, string name, string label, int value, int type, int color, int bcolor);

  void create(int id, string name, string label, int type, int color, int bcolor);

  void move_resize(int posY, int posX, int sizeY, int sizeX);

  bool changed();

  void update_value(API_SQUELCH_DESTINATION &New_Value, unsigned long tmeFrame_Time);

  void draw(bool Refresh, unsigned long tmeFrame_Time);

  bool was_redrawn();

  bool check_click(int x_clicked, int y_clicked, string &Name);
};




#endif