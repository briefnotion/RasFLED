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
#include <string>
#include <deque>

#include "fled_time.h"
#include "stringthings.h"
#include "system.h"

#include "gadgets.h"
#include "helper_ncurses.h"

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
// Simple 2x2 Compass indicating direction at 0 to 360 degrees
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

  void set_heading(float Heading, unsigned long tmeFrame_Time);
  // Set Value. Updates on screen at next draw
  //  tmeFrame_Time is needed for timed animations

  void set_heading(float Heading);
  // Set Value. Updates on screen at next draw
  //  Animations will be ignored without time reference
  
  void clear();
  // Clear values

  void set_color(int Background_Color, int Color);
  // Set Value. Updates on screen at next draw

  void draw(PANEL &Panel, bool Refresh, unsigned long tmeFrame_Time);
  // Draw all changes to Panel. Updates on screen at next draw
  //  Set Refresh to true to force redraw.
  //  tmeFrame_Time is needed for timed animations

  void draw(PANEL &Panel, bool Refresh);
  // Draw all changes to Panel.
  //  Set Refresh to true to force redraw.
  //  Animations will be ignored without time reference
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
// Gadget display single aircraft information to panel with 
//  primary info.  Includes alt, ground speed, heading, 
//  some nav info, signal strength, and time to expire. 
// Set PROP (properties) before calling create routine.
// Warning:
//  Some properties can be changed directly but will not 
//    trigger the redraw or work correctly. 
//  To change properties properly, call the provided set 
//    routines or set routines of internal gadgets.
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

  // Directional varables
  MIN_MAX_TIME ALTITUDE_DIRECION;
  MIN_MAX_TIME SPEED_DIRECION;
  MIN_MAX_TIME SIG_STR_DIRECION;

  // Last known good cood data
  float LATITUDE = 0;
  float LONGITUDE = 0;

  //Debug
  int Counter = 0;

  public:

  // Text Fields  
  Text_Field FLIGHT;
  Text_Field SQUAWK;

  Text_Field ALTITUDE;
  Text_Field_Multi_Line ALTITUDE_IND;
  Text_Field NAV_ALTITUDE_MCP; 

  Text_Field D_VERTICAL_RATE;
  Text_Field_Multi_Line D_VERTICAL_RATE_IND;

  Text_Field SPEED;
  Text_Field_Multi_Line SPEED_IND;

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
  // Prepare gadget to be drawn.  
  //  Define PROP (properties before calling this routine)
  //    Property Size and Position is necessary before calling create.

  void clear();
  // Clear values

  bool changed();
  //  Return true is screen will be redrawn on next draw.
  //  Return false if no changes made.

  void update_aircraft(AIRCRAFT Aircraft, unsigned long &tmeCurrentMillis);
  // Update values of gadget
  //  Gadget will be redrawn if values did changed or animations scheduled. 

  bool draw(bool Refresh, unsigned long tmeFrame_Time);
  // Draw all changes to Panel.
  //  Set Refresh to true to force redraw.
  //  Animations will be ignored without time reference.
  // Returns true if panel was redrawn.
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
// Creates grid of blank ADS_B gadgets.
// Gadget pos 0,0 will be blank to hold control buttons.
// Gadgets are updated automatically by passing list of 
//  ADS_B data.
// Grid mananages positions and gadgets will not need to be
//  accessed.
// Warning:
//  If Pos or Size changes, create will need to be called 
//    again
//  Some properties can be changed directly but will not 
//    trigger the redraw or work correctly. 
//  To change properties properly, call the provided set 
//    routines or set routines of internal gadgets.
{
  private:
  deque<ADSB_Channel> ADSB_Channel_q;

  ADSB_Channel test;

  int ADSB_Channel_Count = 0;
  
  int find_HEX(string Hex);
  // Gadget Internal:
  //  returns gadget position of aircraft with Hex ID

  int find_expired();
  // Gadget Internal:
  //  returns gadget position of aircraft with time expired.

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
  // Prepare gadget grid to be drawn.  
  //  Define PROP (properties) before calling this routine.
  //    Property Size and Position is necessary before calling create.

  void update(system_data &sdSysData, unsigned long &tmeCurrentMillis);
  // Update values of gadget
  //  Gadget will be redrawn if values did changed or animations scheduled. 

  bool draw(bool Refresh, unsigned long tmeFrame_Time, PANEL ADSB_Grid_Panel);
  // Draw all changes to Panel.
  //  Set Refresh to true to force redraw.
  //  Animations require time reference.
  //  ADSB_Grid_Panel defines boundaries.
  // Returns true if panel was redrawn.
};



#endif