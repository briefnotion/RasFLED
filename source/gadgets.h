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
class WINDOW_BODER_PROPERTIES
{
  public:
  char TOP_LEFT = ' ';
  char TOP = ' ';
  char TOP_RIGHT = ' ';
  char LEFT = ' ';
  char RIGHT = ' ';
  char BOT_LEFT = ' ';
  char BOT = ' ';
  char BOT_RIGHT = ' ';
};


class PANEL_PROPERTIES
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

  WINDOW_BODER_PROPERTIES BORDER;
};


class PANEL
{
  private:

  bool CHANGED = false;

  // DEBUG_COUNTER
  int Counter = 0;

  public:
  WINDOW * winPANEL;

  PANEL_PROPERTIES PROP;

  private:

  void draw_border();

  public:

  void create();
  
  void clear();

  void blank_out();

  void changed_on();

  void set_color(int Background_Color, int Color);

  void draw(bool Refresh);
};


// -------------------------------------------------------------------------------------
//  Text_Field Classes

class Text_Field_Properties
// Properties (duh)
{
  private:

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

  void draw(PANEL &Panel, bool Refresh, unsigned long tmeFrame_Time);

  void draw(PANEL &Panel, bool Refresh);
};


// -------------------------------------------------------------------------------------
//  Text_Field_Multi_Line Classes

class Text_Field_Multi_Line_Properties
// Properties (duh)
{
  private:

  public:

  string LABEL = "";
  deque<string> LABEL_MULTI_LINE;
  
  int TYPE = 0;
  int COLOR = 0;
  int BCOLOR = 0;
  
  int POSY = 0;
  int POSX = 0;
  int SIZEY = 0;
  int SIZEX = 0;

  bool JUSTIFICATION_LEFT = false;
  bool JUSTIFICATION_CENTER = false;
  bool JUSTIFICATION_RIGHT = false;

  bool UPDATE_INDICATION = false;

  bool DONT_BLANK = false;

  bool COLORS_ON = false;
  bool INVERSE = false;
};


class Text_Field_Multi_Line
{
  private:
  TIMED_PING UPDATE_INDICATION_TIMER;

  bool CHANGED = false;
  bool HAS_BLANK = false;

  int INDICATED_BLINK_TIME = 250;

  // DEBUG_COUNTER
  int Counter = 0;

  public:
  Text_Field_Multi_Line_Properties PROP;

  private:
  
  void draw_all_lines(PANEL &Button_Panel, deque<string> &Lines, int PosY, int PosX);

  public:

  int line_count();

  bool changed();

  bool has_blank();

  void redraw();

  void set_inverse(bool Inverse);

  void set_text(string Text, unsigned long tmeFrame_Time);

  void set_text(string Text);

  void set_color(int Background_Color, int Color);

  void draw(PANEL &Panel, bool Refresh, unsigned long tmeFrame_Time);

  void draw(PANEL &Panel, bool Refresh);
};


// -------------------------------------------------------------------------------------
//  Title_Bar Classes
class Title_Bar_Properties
// Properties (duh)
{
  public: 

  int ID;
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

  //WINDOW * winTitle;
  PANEL TITLE_BAR_PANEL;
  Text_Field TITLE;

  //Debug
  int Counter = 0;

  public:

  Title_Bar_Properties PROP;  

  void create();

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

  WINDOW_BODER_PROPERTIES BORDER; 

  bool CLICKED = false;
  bool CHANGED = false;
};

class Button
// Routines for create, draw, modify, and behavior.
{
  private:

  //WINDOW * winButton;
  PANEL BUTTON_PANEL;

  TIMED_PING BUTTON_PRESSED;
  int VISIBLE_UPATE_TIME = 500;

  //Debug DEBUG_COUNTER
  int Counter = 0;

  Text_Field_Multi_Line LINES;
  
  // Types:
  // -2 - Disabled
  // -1 - Hidden
  //  0 - Single Click
  //  1 - Toggle Button
  //  2 - Radio Button (Zone)
  // FIX ME: Correctly seperate type into prop values of hidden, disabled.

  public:

  Button_Properties PROP;

  void create();

  bool changed();

  void advance();

  void set_pos_size(int PosY, int PosX, int SizeY, int SizeX);
  
  void set_name(string Name);
  
  void set_label(string Label);

  void set_value(int Value);

  void set_type(int Type);

  void set_color(int Background_Color, int Color);

  void set_enabled(bool Enabled);

  void set_hidden(bool Hidden);

  void change_on();

  void draw(bool Refresh, unsigned long tmeFrame_Time);
};


// -------------------------------------------------------------------------------------
// Button Zone Variable
class Button_Zone_Manager
{
  private:

  //deque<Button_Properties> ZONES;

  deque<Button> BUTTONS;

  int get_pos(int Id);

  int get_pos(string Name);

  public:

  Button_Properties NEW_BUTTON_PROP;

  int size();

  string name(int pos);

  int value(int pos);

  void click_advance(int Id);

  void clear();

  void create_button();

  void draw(bool Refresh, unsigned long tmeFrame_Time);

  void set_pos_size(int Id, int PosY, int PosX, int SizeY, int SizeX);

  void set_pos_size(string Name, int PosY, int PosX, int SizeY, int SizeX);

  void set_name(int Id, string Name);

  void set_name(string Old_Name, string Name);

  void set_label(int Id, string Label);

  void set_label(string Name, string Label);

  void set_value(int Id, int Value);

  void set_value(string Name, int Value);

  void set_type(int Id, int Type);

  void set_type(string Name, int Type);

  void set_color(int Id, int Background_Color, int Color);

  void set_color(string Name, int Background_Color, int Color);

  void set_enabled(int Id, bool Enabled);

  void set_enabled(string Name, bool Enabled);

  void set_hidden(int Id, bool Hidden);

  void set_hidden(string Name, bool Hidden);

  string get_clicked_name();

  int get_clicked_value(string name);

  int get_id_of_button_with_value(int Value);

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