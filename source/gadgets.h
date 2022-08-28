// ***************************************************************************************
// *
// *    Core       | Everything within this document is proprietary to Core Dynamics.
// *    Dynamics   | Any unauthorized duplication will be subject to prosecution.
// *
// *    Department : (R+D)^2                        Name: gadgets.h
// *       Sub Dept: Programming
// *    Location ID: 856-45B
// *                                                      (c) 2856 - 2858 Core Dynamics
// ***************************************************************************************

#ifndef GADGETS_H
#define GADGETS_H

// Standard Header Files
#include <stdio.h>
#include <ncurses.h>
#include <string.h>
#include <deque>

#include "fled_time.h"
#include "stringthings.h"
#include "system.h"
#include "helper_ncurses.h"
#include "api_rtlairband.h"

#include "aircraft_coordinator.h"

using namespace std;

// Ledgend Scale Types:
#define LEDGEND_OFF     0
#define LEDGEND_RANGE   1
#define LEDGEND_SCALER  2

// -------------------------------------------------------------------------------------
//  Title_Bar Classes
class Title_Bar_Properties
// Properties (duh)
{
  public: 

  int ID;
  string NAME = "";
  string LABEL = "";

  int SIZE = 0;
  int COLOR = 0;
  int BCOLOR = 0;
  
  int POSY = 0;
  int POSX = 0;
  int SIZEY = 0;
  int SIZEX = 0;

  bool CHANGED = false;
};

class Title_Bar
// Routines for create, draw, modify, and behavior.
{
  private:

  WINDOW * winTitle;

  //Debug
  int Counter = 0;

  public:

  Title_Bar_Properties PROP;  

  void modify(int id, string name, string label, int size, int color, int bcolor);

  void create(int id, string name, string label, int size, int color, int bcolor);

  void move_resize(int posY, int posX, int sizeY, int sizeX);

  bool changed();

  void draw(bool Refresh);
};

// -------------------------------------------------------------------------------------
//  Text_Box Classes

class Text_Line
// Stores a standard text line with timestamp.
{
  public:
  unsigned long tmeTime_stamp = 0;      // Timestamp of line time, if provided.
  string strLine              = "";     // Text value of console line
  bool printed                = false;  // If ever line was displayed, set to true.
};

class Text_Line_List
// Routines for managing a list of Text_Line.
{
  private:

  int max_lines = 200;        // MaxSize of stored lines

  deque<Text_Line> LINES;  // stored console line 

  public: 
  
  bool Refresh_Text_Line_List = false;

  private:
  
  void clear_outside_max();

  public:

  void add(unsigned long tmeCurrentMillis, string line);

  bool avail();

  Text_Line get_line_to_print(int pos);

  void clear();
};

class Text_Box_Properties
// Properties (duh)
{
  public: 

  int ID;
  string NAME = "";
  string LABEL = "";
  
  Text_Line_List LINES;

  int TYPE = 0;
  int COLOR = 0;
  int BCOLOR = 0;
  
  int POSY = 0;
  int POSX = 0;
  int SIZEY = 0;
  int SIZEX = 0;

  bool CHANGED = false;
};

class Text_Box
// Routines for create, draw, modify, and behavior.
{
  private:

  WINDOW * winText_Box;

  // DEBUG_COUNTER
  int Counter = 0;

  // Types:
  // -1 - Hidden
  //  0 - Read Only

  public:

  Text_Box_Properties PROP;  

  void modify(int id, string name, string label, int type, int color, int bcolor);

  void create(int id, string name, string label, int type, int color, int bcolor);

  void move_resize(int posY, int posX, int sizeY, int sizeX);

  bool changed();

  void draw(bool Refresh);

  void add_line(unsigned long Time_Milli, string Text);

  void clear_text();
};

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

  // Types:
  // -1 - Hidden
  //  0 - Read Only

  private:

  int get_first_empty_pos();

  int get_first_pos_with_no_data();

  int find_HEX(string Hex);

  void organize_index();

  void sort_index();

  int color_range(float Value, int Magenta, int Red, int Yellow, int Green, int Blue);

  //int color_scale(float Value, int Magenta, int Red, int Yellow, int Green, int Blue)
  int color_scale(float Value, int Green, int Yellow, int Red, int Magenta, int Blue);

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
// Button Classes

class Button_Properties
// Properties (duh)
{
  public: 

  int ID;
  string NAME = "";
  string LABEL = "";
  
  int VALUE = 0;

  int TYPE = 0;
  int COLOR = 0;
  int BCOLOR = 0;

  bool HIDDEN = false;
  bool ENABLED = true;

  //bool CLEAR = false;
  
  int POSY = 0;
  int POSX = 0;
  int SIZEY = 0;
  int SIZEX = 0;

  bool CLICKED = false;
  bool CHANGED = false;
};

class Button
// Routines for create, draw, modify, and behavior.
{
  private:

  WINDOW * winButton;

  TIMED_PING BUTTON_PRESSED;
  int VISIBLE_UPATE_TIME = 500;

  //Debug DEBUG_COUNTER
  int Counter = 0;

  // Types:
  // -2 - Disabled
  // -1 - Hidden
  //  0 - Single Click
  //  1 - Toggle Button
  //  2 - Radio Button (Zone)
  // FIX ME: Correctly seperate type into prop values of hidden, disabled.

  public:

  Button_Properties PROP;  

  void modify(int id, string name, string label, int value, int type, int color, int bcolor);

  void create();

  void move_resize(int posY, int posX, int sizeY, int sizeX);

  bool changed();

  void advance();

  void draw(bool Refresh, unsigned long tmeFrame_Time);
};


// -------------------------------------------------------------------------------------
// Button Zone Variable
class Button_Zone_Manager
{
  private:

  //deque<Button_Properties> ZONES;

  deque<Button> BUTTONS;

  public:

  int size();

  string name(int pos);

  int value(int pos);

  void click_advance(int Id);

  void create_button(int Id, string Name, string Label, int Value, int Type, int Color, int BColor);

  void modify(int Id, string Name, string Label, int Value, int Type, int Color, int BColor);

  void move_resize(int Id, int posY, int posX, int sizeY, int sizeX);

  void draw(bool Refresh, unsigned long tmeFrame_Time);

  void change_label(string name, string label);

  void change_value(string name, int value);

  void change_enabled(string Name, bool Enabled);

  void change_hidden(string Name, bool Hidden);

  string get_clicked_name();

  int get_clicked_value(string name);

  bool check_click(int x,int y);
};

// ---------------------------------------------------------------------------------------
// Bar Classes

class BAR_TIME_SLICE
{
  private:

  bool ACTIVE = false;
  int MIN_VALUE = 0;
  int MAX_VALUE = 0;
  string SNAPSHOT = "";

  public:

  void clear();

  bool active();

  void store_min_max(int Value);

  int min();

  int max();
};

class BAR
// Display Progress Bar or Guage Bar.
// Needs to be passed an NCurses window
// Properties can be set when defined.
{
  private:

  // Min Max time slice varables.
  TIMED_IS_READY        TIME_SLICE_TIMER;       // Internal
  int                   TIME_SLICE_COUNT = 5;   // Internal, could be exterenal.
  deque<BAR_TIME_SLICE> TIME_SLICES;            // Internal
  bool                  TIME_PROVIDED = false;  // Internal
  
  unsigned long         FRAME_TIME;             // Internal
  int                   MIN_MAX_TIME_SPAN = 0;  // Span of time made by slices. In ms.

  int COLOR_BACKGROUND = 0; // Guage background color
  int COLOR_FOREGROUND = 0; // Guage text color, when not std.

  string LABEL = "";        // Displayed left of the gadget.
  int LABEL_SIZE = 0;       // Character size of label.

  int YPOS = 0;             // Y start position of gadget in window.
  int XPOS = 0;             // X start position of gadget in window.

  int SIZE = 0;             // Size of bar in gadget.

  int MAX_VALUE = 0;        // Gadget's Max Value to be displayed.
  int MIN_VALUE = 0;        // Gadget's Min Value to be displayed. not implemented.
  int VALUE = 0;

  // Guage Variables
  bool MIN_MAX  = false;    // Gadget will show min max values over time lapse.
  //bool MIN_MAX_SET = false; // Min Max values stored in min and max when true - internal
  //int MIN = 0;              // Min value - internal.
  //int MAX = 0;              // Max value - internal.

  bool PRINT_VALUE = false; // Print value on right of guage.
  bool PRINT_MIN = false;   // Print Min value on right of guage.
  bool PRINT_MAX = false;   // Print Max value on right of guage.

  // I dont like this
  int get_min_value();

  // I dont like this
  int get_max_value();

  void wat_on_background(WINDOW *winWindow);

  void wat_off_background(WINDOW *winWindow);

  void wat_on_red(WINDOW *winWindow);

  void wat_off_red(WINDOW *winWindow);

  void wat_on_green_red(WINDOW *winWindow, bool value);

  void wat_off_green_red(WINDOW *winWindow, bool value);

  int get_marker_pos(int value);

  void print_marker(WINDOW *winWindow, int Ypos, int Xpos, int value);

  void draw_bar(int Bar_Type, WINDOW *winWindow);

  public:

  void color_background(short Color);

  void color_foreground(short Color);

  void label(string Label);

  void label_size(int Label_Size);

  void size(int Size);

  void max_value(int Max_Value);

  void print_value(bool Print_Value);

  void print_min(bool Print_Min);

  void print_max(bool Print_Max);

  // Guage variables
  void min_max(bool min_max);

  // Guage variables
  void min_max_time_span(int Time_Span_in_ms);

  // Creates a progress bar of 0 to 100 percent.
  //  Returns a string of size.
  //  Of size, the percentage of value to max_value will be filled
  //  with characters.
  void progress_bar(WINDOW *winWindow, int YPos, int XPos, int value);

  void progress_bar(WINDOW *winWindow, int YPos, int XPos, int value, unsigned long tmeFrame_Time);

  void progress_bar(WINDOW *winWindow, int YPos, int XPos, int size, int max_value, int value);

  // Creates a progress bar of 0 to 100 percent.
  //  Returns a string of size.
  //  Of size, the percentage of value to max_value will be filled
  //  with characters.
  void guage_bar(WINDOW *winWindow, int YPos, int XPos, int value);

  void guage_bar(WINDOW *winWindow, int YPos, int XPos, int value, unsigned long tmeFrame_Time);

  void guage_bar(WINDOW *winWindow, int YPos, int XPos, int size, int max_value, int value);
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

// ---------------------------------------------------------------------------------------
// Gadgets functions

// Drawing a progress bar
string simple_progress_bar(int size, int max_value, int value);



#endif