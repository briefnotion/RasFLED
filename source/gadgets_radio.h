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


// -------------------------------------------------------------------------------------
//  ADS-B Classes

class ADS_B_List_Box_Properties
// Properties (duh)
{
  public: 

  int ID;
  string NAME = "";
  string LABEL = "";

  AIRCRAFT_DATA VALUE;

  int TYPE = 0;
  int COLOR = 0;
  int BCOLOR = 0;
  
  int POSY = 0;
  int POSX = 0;
  int SIZEY = 0;
  int SIZEX = 0;

  bool CHANGED = false;
};

class ADS_B_List_Box
// Routines for create, draw, modify, and behavior.
{
  private:
  class AIRCRAFT_INDEX_INFORMATION
  {
    public:
    string HEX = "";
    int POSITION = -1;
    int DATA_COUNT = 0;
    int SIZE = 0;
    bool UPDATED = false;
  };

  WINDOW * ADS_B_List_Box;

  // DEBUG_COUNTER
  int Counter = 0;

  deque<AIRCRAFT_INDEX_INFORMATION> AIRCRAFT_INDEX_LIST;
  int AIRCRAFT_INDEX_LIST_ALERT_COUNT_GUIDE = 0;
  
  bool IS_ACTIVE = false;

  private:

  int get_first_empty_pos();

  int get_first_pos_with_no_data();

  int find_HEX(string Hex);

  void organize_index();

  void sort_index();

  void clear_line(int &yCurPos, int &xCurPos);

  void print_to_line(int &yCurPos, int &xCurPos, int Size, string Text, int Color_Pair);

  void dsp_text(int &yCurPos, int &xCurPos, int Size, STRING_STRING &Text, int Text_Color, bool Inverse_Colors, int Color_Value, 
                  int Color_Scale_Type, int Level_0, int Level_1, int Level_2, int Level_3, int Level_4);

  // Scale Types:
  //  0 = LEDGEND_OFF;
  //  1 = LEDGEND_RANGE   - Non Zero Green
  //  2 = LEDGEND_SCALER  - Zero Green

  void dsp_intg(int &yCurPos, int &xCurPos, int Size, STRING_INT &Text, float Alt_Value, bool Alt_Success, int Text_Color, bool Inverse_Colors, 
                  int Color_Scale_Type, int Level_0, int Level_1, int Level_2, int Level_3, int Level_4);

  void dsp_intg(int &yCurPos, int &xCurPos, int Size, STRING_INT &Text, int Text_Color, bool Inverse_Colors, 
                  int Color_Scale_Type, int Level_0, int Level_1, int Level_2, int Level_3, int Level_4);

  void dsp_floa(int &yCurPos, int &xCurPos, int Size, STRING_FLOAT &Text, float Alt_Value, bool Alt_Success, int Text_Color, bool Inverse_Colors, 
                  int Color_Scale_Type, int Level_0, int Level_1, int Level_2, int Level_3, int Level_4);

  void dsp_floa(int &yCurPos, int &xCurPos, int Size, STRING_FLOAT &Text, int Text_Color, bool Inverse_Colors, 
                int Color_Scale_Type, int Level_0, int Level_1, int Level_2, int Level_3, int Level_4);

  public:

  ADS_B_List_Box_Properties PROP;  

  void modify(int id, string name, string label, int type, int color, int bcolor);

  void create(int id, string name, string label, int type, int color, int bcolor);

  void move_resize(int posY, int posX, int sizeY, int sizeX);

  bool changed();

  void draw(bool Refresh);

  void update(system_data &sdSysData);
};



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
  WINDOW * winADSB;

  // Time Provided
  unsigned long FRAME_TIME;             // Internal

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
  Text_Field TOP_BAR;
  
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
  Text_Field TRACK_MINI_COMPASS_TOP;
  Text_Field TRACK_MINI_COMPASS_BOTTOM;
  
  Text_Field NAV_HEADING;
  Text_Field NAV_HEADING_MINI_COMPASS_TOP;
  Text_Field NAV_HEADING_MINI_COMPASS_BOTTOM;

  Text_Field MESSAGE;
  
  //Text_Field NAV_QNH;

  ADSB_Channel_Properties PROP;  

  void create();

  void clear();

  bool changed();

  void update_value(string Flight, string Squawk, string Speed, string Track, 
                                string D_Vertical_Rate, string Altitude, 
                                unsigned long tmeFrame_Time);

  void update_aircraft(AIRCRAFT Aircraft, unsigned long &tmeCurrentMillis);

  void draw(bool Refresh, unsigned long tmeFrame_Time);
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

  public:

  ADSB_Channel_Grid_Properties PROP;  

  bool IS_ACTIVE = false;

  void create();

  void update(system_data &sdSysData, unsigned long &tmeCurrentMillis);

  void draw(bool Refresh, unsigned long tmeFrame_Time);
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
  WINDOW * winFrequency;

  Button_Zone_Manager bzGadget;
  int Button_YSize = 3;
  int Button_XSize = 9;

  // Show frequency levels in progress bars
  BAR BAR_NOISE_LEVEL;
  BAR BAR_SIGNAL_LEVEL;

  // Time Provided
  unsigned long FRAME_TIME;             // Internal

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