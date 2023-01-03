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

using namespace std;

// Ledgend Scale Types:
#define LEDGEND_OFF     0
#define LEDGEND_RANGE   1
#define LEDGEND_SCALER  2

// -------------------------------------------------------------------------------------
//  Panel Class

class Panel_Properties
// Properties (duh)
{
  public: 
  string LABEL = "";

  int TYPE = 0;
  int COLOR = 0;
  int BCOLOR = 0;
  
  int POSY = 0;
  int POSX = 0;
  int SIZEY = 0;
  int SIZEX = 0;
};


class Panel
{
  private:

  WINDOW * winPanel;

  bool CHANGED = false;

  // DEBUG_COUNTER
  int Counter = 0;

  public:
  Panel_Properties PROP;

  //bool changed();

  void create();

  void set_color(int Background_Color, int Color);

  void draw(bool Refresh);
};

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
//  Text_Field Classes

class Text_Field_Properties
// Properties (duh)
{
  public: 
  string LABEL = "";

  int TYPE = 0;
  int COLOR = 0;
  int BCOLOR = 0;
  
  int POSY = 0;
  int POSX = 0;
  //int SIZEY = 0;
  int SIZEX = 0;

  bool JUSTIFICATION_LEFT = false;
  bool JUSTIFICATION_CENTER = false;
  bool JUSTIFICATION_RIGHT = false;

  bool UPDATE_INDICATION = false;

  bool DONT_BLANK = false;

  bool COLORS_ON = false;
  bool INVERSE = false;
};


class Text_Field
{
  private:
  TIMED_PING UPDATE_INDICATION_TIMER;

  bool CHANGED = false;
  bool HAS_BLANK = false;

  int INDICATED_BLINK_TIME = 250;

  // DEBUG_COUNTER
  int Counter = 0;

  public:
  Text_Field_Properties PROP;

  bool changed();

  bool has_blank();

  void redraw();

  void set_inverse(bool Inverse);

  void set_text(string Text, unsigned long tmeFrame_Time);

  void set_text(string Text);
  
  void clear();

  void set_color(int Background_Color, int Color);

  bool draw(WINDOW *window, bool Refresh, unsigned long tmeFrame_Time);

  bool draw(WINDOW *window, bool Refresh);
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

// ---------------------------------------------------------------------------------------
// Gadgets functions

// Drawing a progress bar
string simple_progress_bar(int size, int max_value, int value);



#endif