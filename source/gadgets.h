// ***************************************************************************************
// *
// *    Core       | Everything within this document is proprietary to Core Dynamics.
// *    Dynamics   | Any unauthorized duplication will be subject to prosecution.
// *
// *    Department : (R+D)^2                        Name: gadgets.cpp
// *       Sub Dept: Programming
// *    Location ID: 856-45B
// *                                                      (c) 2856 - 2858 Core Dynamics
// ***************************************************************************************

#ifndef GADGETS_CPP
#define GADGETS_CPP

// Standard Header Files
#include <stdio.h>
#include <ncurses.h>
#include <string>
#include <deque>
#include <vector>

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

/*
// -------------------------------------------------------------------------------------
//  Blank Gadget

//  Panel Properties
class AUTOMOBILE_OVERVIEW_GADGET_PROPERTIES
// Properties (duh)
{
  public: 

  int POSY = 0;
  int POSX = 0;
  int SIZEY = 0;
  int SIZEX = 18;

};

class AUTOMOBILE_OVERVIEW_GADGET
{
  private:

  PANEL GADGET_PANEL;

  //-----------

  Text_Field test;

  //-----------

  bool CHANGED = false;

  public:

  AUTOMOBILE_OVERVIEW_GADGET_PROPERTIES PROP;  

  void create();
  // Panel to be drawn.  
  //  Define PROP (properties) before calling this routine.
  //    Property Size and Position is necessary before calling create.

  void update(system_data &sdSysData, unsigned long &tmeCurrentMillis);
  // Update values of panel
  //  Gadget will be redrawn if values did changed or animations scheduled. 

  bool draw(bool Refresh, unsigned long tmeFrame_Time);
  // Draw all changes to Panel.
  //  Set Refresh to true to force redraw.
  //  Animations require time reference.
  // Returns true if panel was redrawn.
};
*/

class WINDOW_BODER_PROPERTIES
// Panel border characters.
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
// Gadget containing blank window with boundaries to hold 
//  gadgets
// Set all PROP (properties) before calling create routine.
// Warning:
//  Some properties can be changed directly but will not 
//    trigger the redraw or work correctly. 
//  To change properties properly, call the provided set 
//    routines or set routines of internal gadgets.
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
  // Gadget Internal:
  //  Draw panel border.

  public:

  void create();
  // Prepare gadget to be drawn.  
  //  Define all PROP (properties before calling this routine)
  //    Property Size and Position is necessary before calling create.
  
  void clear();
  // Clear values
  
  void blank_out();
  // Set all characters on panel to space.

  void changed_on();
  // Force panel to redraw on next draw routine call

  void set_color(int Background_Color, int Color);
  // Set Value. Updates on screen at next draw

  bool draw(bool Refresh);
  // Draw all changes to Panel.
  //  Set Refresh to true to force redraw.
};


// -------------------------------------------------------------------------------------
//  CYBR Classes
class CYBR_LINE
// Simp stat vert bar clipped in delta time.  Multi 
//  input as RGB with deets inc with each ping.
{
  public:
  
  array<char, 256> COLOR_VAL;

};

class CYBR_Properties
// Properties (duh)
{
  private:

  public: 
  
  int POSY = 0;
  int POSX = 0;
  int SIZEY = 0;
  int SIZEX = 0;
};


class CYBR
{
  private:

  PANEL CYBR_PANEL;
 
  int CYBR_YLn = 0;

  deque<CYBR_LINE> CYBRValue;

  bool CHANGED = false;

  // DEBUG_COUNTER
  int Counter = 0;

  public:
  CYBR_Properties PROP;

  void create();
  // Pop into existance.

  void input(int Value, int Max_Value, int BColor, int Color);
  // Inc deet count of Value. Deet answers to its color.

  bool draw(unsigned long tmeFrame_Time);
  // Spit out the pixs.  Preme watev time stamp.
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
  bool AUTO_COLOR = false;
  
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
// Simple text field
// Complexity scales with properties.
// Set PROP (properties) before calling draw routine.
// Warning:
//  Some properties can be changed directly but will not 
//    trigger the redraw or work correctly. 
//  To change properties properly, call the provided set 
//    routines or set routines of internal gadgets.
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

  void blink(unsigned long tmeFrame_Time);
  // Causes the text field to blink as if the data has
  //  changed.
  // Note:
  //  UPDATE_INDICATION will need to be set to true.

  bool changed();
  // Return true is screen will be redrawn on next draw.
  // Return false if no changes made.

  bool has_blank();
  // Return true if label value is "".

  void redraw();
  // Set to true to force redraw.

  void set_inverse(bool Inverse);
  // Set Back Color and Color to reverse.

  void set_text(string Text, unsigned long tmeFrame_Time);
  // Set Value. Updates on screen at next draw
  //  tmeFrame_Time is needed for timed animations

  void set_text(string Text);
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
//  Text_Field Classes

class Char_Graph_Properties
// Properties (duh)
{
  private:

  public: 
  
  int POSY = 0;
  int POSX = 0;

  int MIN = 0;
  int MAX = 100;

  const int SIZEY = 1;
  const int SIZEX = 1;

  bool UPDATE_INDICATION = false;

  bool ALT_COLORS = false;
};

class Char_Graph
// Single Character Chart
// Complexity scales with properties.
// Set PROP (properties) before calling draw routine.
// Warning:
//  Some properties can be changed directly but will not 
//    trigger the redraw or work correctly. 
//  To change properties properly, call the provided set 
//    routines or set routines of internal gadgets.
{
  private:
  TIMED_PING UPDATE_INDICATION_TIMER;

  bool CHANGED = false;

  int INDICATED_BLINK_TIME = 250;

  float VALUE = 0;
  float MIN = 0;
  float MAX = 0;

  // DEBUG_COUNTER
  int Counter = 0;

  public:
  Char_Graph_Properties PROP;

  bool changed();
  // Return true is screen will be redrawn on next draw.
  // Return false if no changes made.

  void redraw();
  // Set to true to force redraw.

  void set_value(float Value, int Min, int Max, long tmeFrame_Time);
  // Set Value. Updates on screen at next draw
  //  tmeFrame_Time is needed for timed animations

  void set_value(float Value, long tmeFrame_Time);
  // Set Value. Updates on screen at next draw
  //  tmeFrame_Time is needed for timed animations

  void set_value(float Value);
  // Set Value. Updates on screen at next draw
  //  No Timed Animations
  
  void clear();
  // Clear values

  void draw(PANEL &Panel, bool Refresh, unsigned long tmeFrame_Time, int Zero_Color);
  // Draw all changes to Panel. Updates on screen at next draw
  //  Set Refresh to true to force redraw.
  //  tmeFrame_Time is needed for timed animations
  // If Zero_Color -1 then background of a zero value will be default,
  //  else, background will be color passed.

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

// -------------------------------------------------------------------------------------

class Text_Field_Multi_Line
// Multiline text field
// Complexity scales with properties.
// Set PROP (properties) before calling draw routine.
// Warning:
//  Line breaks with \n
//  Some properties can be changed directly but will not 
//    trigger the redraw or work correctly. 
//  To change properties properly, call the provided set 
//    routines or set routines of internal gadgets.
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
  
  void draw_all_lines(PANEL &Button_Panel, deque<string> &Lines, int SizeY, int PosY, int PosX);
  // Gadget Internal:
  //  Draw panel border.

  public:

  int line_count();
  // Returns size of lines.

  bool changed();
  // Return true is screen will be redrawn on next draw.
  // Return false if no changes made.

  bool has_blank();
  // Return true if label value is "".

  void redraw();
  // Set to true to force redraw.

  void set_inverse(bool Inverse);
  // Set Back Color and Color to reverse.

  void set_text(string Text, unsigned long tmeFrame_Time);
  // Set Value. Updates on screen at next draw
  //  tmeFrame_Time is needed for timed animations

  void set_text(string Text);
  // Set Value. Updates on screen at next draw
  //  Animations will be ignored without time reference

  void set_color(int Background_Color, int Color);
  // Set Value. Updates on screen at next draw

  bool draw(PANEL &Panel, bool Refresh, unsigned long tmeFrame_Time);
  // Draw all changes to Panel. Updates on screen at next draw
  //  Set Refresh to true to force redraw.
  //  tmeFrame_Time is needed for timed animations

  bool draw(PANEL &Panel, bool Refresh);
  // Draw all changes to Panel.
  //  Set Refresh to true to force redraw.
  //  Animations will be ignored without time reference
};

// -------------------------------------------------------------------------------------
/*
class Rotating_Text_Field_Properties
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


class Rotating_Text_Field
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
*/
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
};

class Title_Bar
// Title bar.
// Set PROP (properties) before calling draw routine.
// Warning:
//  Some properties can be changed directly but will not 
//    trigger the redraw or work correctly. 
{
  private:

  //WINDOW * winTitle;
  PANEL TITLE_BAR_PANEL;
  Text_Field TITLE;

  bool CHANGED = false;
  
  //Debug
  int Counter = 0;

  public:

  Title_Bar_Properties PROP;  

  void create();
// Prepare gadget to be drawn.  
//  Define all PROP (properties before calling this routine)
//    Property Size and Position is necessary before calling create.

  bool changed();
  // Return true is screen will be redrawn on next draw.
  // Return false if no changes made.

  bool draw(bool Refresh);
  // Draw all changes to Panel.
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

  Text_Line get_line_to_print(int pos);

  void clear();
};

class Text_Box_Properties
// Properties (duh)
{
  public: 

  string LABEL = "";
  
  Text_Line_List LINES;

  int COLOR = 0;
  int BCOLOR = 0;
  
  int POSY = 0;
  int POSX = 0;
  int SIZEY = 0;
  int SIZEX = 0;

};

class Text_Box
// Routines for create, draw, modify, and behavior.
{
  private:

  PANEL TEXT_BOX_PANEL;

  // DEBUG_COUNTER
  int Counter = 0;
  
  bool CHANGED = false;

  public:

  Text_Box_Properties PROP;  

  void create();

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
  bool AUTO_COLOR = true;

  bool HIDDEN = false;
  bool ENABLED = true;
  bool DO_NOT_DRAW = false;
  
  int POSY = 0;
  int POSX = 0;
  int SIZEY = 0;
  int SIZEX = 0;

  WINDOW_BODER_PROPERTIES BORDER; 

  bool CLICKED = false;
  bool CHANGED = false;
};

class Button
// Gadget display single button to panel with 
//  primary info.
// Set PROP (properties) before calling create routine.
// Warning:
//  Some properties can be changed directly but will not 
//    trigger the redraw or work correctly. 
//  To change properties properly, call the provided set 
//    routines or set routines of internal gadgets.
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

  private:
  
  public:

  void create();
  // Prepare gadget to be drawn.  
  //  Define PROP (properties before calling this routine)
  //    Property Size and Position is necessary before calling create.

  bool changed();
  // Return true is screen will be redrawn on next draw.
  // Return false if no changes made.

  void advance();
  // Increse button value by 1.
  
  void set_name(string Name);
  // Set Value. Updates on screen at next draw
  
  void set_label(string Label);
  // Set Value. Updates on screen at next draw

  void set_value(int Value);
  // Set Value. Updates on screen at next draw

  void set_type(int Type);
  // Set Value. Updates on screen at next draw

  void set_color(int Background_Color, int Color);
  // Set Value. Updates on screen at next draw

  void set_enabled(bool Enabled);
  // Set Value. Updates on screen at next draw

  void set_hidden(bool Hidden);
  // Set Value. Updates on screen at next draw

  void set_do_not_draw(bool Do_Not_Draw);
  // Set Value. Updates on screen at next draw

  bool draw(bool Refresh, unsigned long tmeFrame_Time);
  // Draw all changes to Panel. Updates on screen at next draw
  //  Set Refresh to true to force redraw.
  //  tmeFrame_Time is needed for timed animations
};


// -------------------------------------------------------------------------------------
// Button Zone Variable
class Button_Zone_Manager
// Control a group of buttons.
// Provides interface to check button values.
// To change properties properly, call the provided set 
//    routines or set routines of internal gadgets.
{
  private:

  //deque<Button_Properties> ZONES;

  deque<Button> BUTTONS;

  int get_pos(int Id);
  // Gadget Internal:
  //  Get position of button by Id.

  int get_pos(string Name);
  // Gadget Internal:
  //  Get position of button by Name.

  public:

  Button_Properties NEW_BUTTON_PROP;

  int size();

  string name(int pos);
  // Return name of button in list position.

  int value(int pos);
  // Return value of button in list position.

  void click_advance(int Position);
  // Increse button in pos value by 1.
  // NEEDS TO BE PHASED OUT AND REPLACED WITH ID
  
  void click_advance(string Name);

  void clear();
  // Clear button list

  void create_button();
  // Add new button to button list with 
  // properties of NEW_BUTTON_PROP.

  bool draw(bool Refresh, unsigned long tmeFrame_Time);
  // Draw all buttons to Panel. Updates on screen at next draw
  //  Set Refresh to true to force redraw.
  //  tmeFrame_Time is needed for timed animations

  void set_name(int Id, string Name);
  // Set Value. Updates on screen at next draw

  void set_name(string Old_Name, string Name);
  // Set Value. Updates on screen at next draw

  void set_label(int Id, string Label);
  // Set Value. Updates on screen at next draw

  void set_label(string Name, string Label);
  // Set Value. Updates on screen at next draw

  void set_value(int Id, int Value);
  // Set Value. Updates on screen at next draw

  void set_value(string Name, int Value);
  // Set Value. Updates on screen at next draw

  void set_type(int Id, int Type);
  // Set Value. Updates on screen at next draw

  void set_type(string Name, int Type);
  // Set Value. Updates on screen at next draw

  void set_color(int Id, int Background_Color, int Color);
  // Set Value. Updates on screen at next draw

  void set_color(string Name, int Background_Color, int Color);
  // Set Value. Updates on screen at next draw

  void set_enabled(int Id, bool Enabled);
  // Set Value. Updates on screen at next draw

  void set_enabled(string Name, bool Enabled);
  // Set Value. Updates on screen at next draw

  void set_hidden(int Id, bool Hidden);
  // Set Value. Updates on screen at next draw

  void set_hidden(string Name, bool Hidden);
  // Set Value. Updates on screen at next draw

  void set_do_not_draw(string Name, bool Do_Not_Draw);
  // Set Value. Updates on screen at next draw

  void set_do_not_draw(int Id, bool Do_Not_Draw);
  // Set Value. Updates on screen at next draw
  
  string get_clicked_name();
  // Returns name of clicked button.

  int get_clicked_value(string name);
  // Returns value of clicked button.

  int get_id_of_button_with_value(int Value);
  // Returns id of button with value of 1.

  string get_name_of_button_with_value(int Value);
  // Returns id of button with value of 1.

  bool check_click(int x,int y);
  // sets cliced on of any buttons in list underneith x,y coords
};

// ---------------------------------------------------------------------------------------

class BAR_PROPERTIES
// Bar properties.
// To change properties properly, call the provided set 
//    routines or set routines of internal gadgets.
{
  private:

  public: 
  
  string LABEL = "";        // Displayed left of the gadget.
  int LABEL_SIZE = 0;       // Character size of label.

  char INDICATOR_CHARACTER = '|';       // Marker Character

  int COLOR = COLOR_WHITE;              // Label Text Color
  int BCOLOR = COLOR_BLACK;             // Label Text Background Color

  int COLOR_BAR = COLOR_GREEN;          // Items on Bar Color
  int COLOR_BAR_BACK = COLOR_BLACK;     // Bar Background Color

  int COLOR_MARKER = COLOR_WHITE;       // Marker Color
  int BCOLOR_MARKER = COLOR_BLACK;      // Marker Background Color
  int COLOR_MARKER_LIMIT = COLOR_RED;   // Bar Background Excede Limit Color

  int POSY = 0;             // Y start position of gadget in window.
  int POSX = 0;             // X start position of gadget in window.
  //int SIZEY = 0;
  int BAR_SIZE = 0;             // Size of bar in gadget.

  int VALUE = 0;

  // Bar Type (Select Only One)
  bool PROGRESS_BAR = false;
  bool GUAGE_BAR = false;

  // Display Min Max Values
  bool MIN_MAX = false;    // Gadget will show min max values over time lapse.

  bool MIN_MAX_INDICATORS = true; // Draw Min Max Indictor Bars.

  int MAX_VALUE = 0;            // Gadget's Max Value to be displayed.
  int MIN_VALUE = 0;            // Gadget's Min Value to be displayed. not implemented.

  bool MIN_MAX_FILLER = true;   // Will only draw if colors are on
  int MIN_MAX_FILLER_BCOLOR = COLOR_MAGENTA;
  int MIN_MAX_FILLER_COLOR = COLOR_BLUE;

  //int  MIN_MAX_TIME_SPAN = 0;  // Span of time made by slices. In ms.

  bool PRINT_VALUE = false; // Print value on right of guage.
  bool PRINT_MIN = false;   // Print Min value on right of guage.
  bool PRINT_MAX = false;   // Print Max value on right of guage.

  bool BRACKET_END_CAPS = false;  // Print brackets on both ends of bar.

  bool COLORS_ON = false;
};


class BAR
// Display Progress Bar or Guage Bar.
// Needs to be passed an NCurses window
// Properties can be set when defined.
{
  private:

  bool CHANGED = true;

  int get_marker_pos(int value);
  // Gadget Internal:
  //  Determine position of Marker in bar

  void print_marker(WINDOW *winWindow, int Ypos, int Xpos, int value);
  // Gadget Internal:
  //  Draw marker in proper position of bar

  void print_min_max_filler(WINDOW *winWindow, int Ypos, int Xpos, int min, int max);

  public:

  MIN_MAX_TIME MIN_MAX_HISTORY;

  BAR_PROPERTIES PROP;

  void update(int Value, unsigned long tmeFrame_Time);
  // Set Value. Updates on screen at next draw

  void set_color(int Background_Color, int Color);
  // Set Value. Updates on screen at next draw

  bool draw(PANEL &Panel, bool Refresh);
  // Draw all changes to Panel. Updates on screen at next draw
};

// ---------------------------------------------------------------------------------------


class CYBR_SLICE
{
  public:

  vector<unsigned int> VAL;     // Char sized data array of chars. MAX_s 256
  unsigned long TIMESTAMP = 0;    // Time data slice created.
  unsigned int UPDATE_COUNT = 0; // How many times data was updated.
};

class CYBR_BAR_PROPERTIES
// Bar properties.
// To change properties properly, call the provided set 
//    routines or set routines of internal gadgets.
{
  public: 
  
  char INDICATOR_CHARACTER = '|';       // Marker Character

  int COLOR_BAR_BACK = COLOR_BLACK;     // Bar Background Color

  int COLOR_MARKER = COLOR_WHITE;       // Marker Color
  int BCOLOR_MARKER = COLOR_BLACK;      // Marker Background Color
  int COLOR_MARKER_LIMIT = COLOR_RED;   // Bar Background Excede Limit Color

  int POSY = 0;       // Y start position of gadget in window.
  int POSX = 0;       // X start position of gadget in window.

  int BAR_SIZE = 0;   // Size of bar in gadget.

  unsigned long TIME_SPAN = 0;  // Span of time made by slices. In ms.

  int MAX_VALUE = 0;  // Gadget's Max Value to be displayed.
  int MIN_VALUE = 0;  // Gadget's Min Value to be displayed. not implemented.

  bool PROGESS_BAR = false;

  bool JECT = false;  // Basically, just hides the marker.

  bool BRACKET_END_CAPS = false;  // Print brackets on both ends of bar.
};

class CYBR_BAR
// Display Progress Bar or Guage Bar.
// Needs to be passed an NCurses window
// Properties can be set when defined.
{
  private:

  float VALUE = 0;

  deque<CYBR_SLICE> SLICE_HISTORY;
  deque<Char_Graph> SLICE_GRAPH;

  bool JECTO_READY = false;
  TIMED_PING JECTO_TIMER;
  CYBR_SLICE JECTO_DAT;
  int MAX_SLICE_COUNT = 20;

  bool CREATED = false;
  bool CHANGED = true;

  int get_marker_pos(float value);
  // Gadget Internal:
  //  Determine position of Marker in bar

  void print_marker(WINDOW *winWindow, int Ypos, int Xpos, int value);
  // Gadget Internal:
  //  Draw marker in proper position of bar

  void check_for_ejects(unsigned long tmeFrame_Time);
  // put slice into JECTO DAT if old

  void update_cybr_slice(int Value, unsigned long tmeFrame_Time);
  // Updates most recent slice

  public:

  CYBR_BAR_PROPERTIES PROP;
  MIN_MAX_TIME MIN_MAX_HISTORY;

  void create();

  void update(float Value, unsigned long tmeFrame_Time);
  // Set Value. Updates on screen at next draw

  void update(int Value, unsigned long tmeFrame_Time);
  // Set Value. Updates on screen at next draw

  void update_via_slice(CYBR_SLICE CYBR_Slice, unsigned long tmeFrame_Time);
  // Bring in a cyber slice

  bool jecto_ready();
  // Slice ready if true

  CYBR_SLICE jecto();
  // get ready Slice

  bool draw(PANEL &Panel, bool Refresh, unsigned long tmeFrame_Time);
  // Draw all changes to Panel. Updates on screen at next draw
};

/*
// ---------------------------------------------------------------------------------------
// Planned Classes

class KEYPAD
{

};

class KEYBOARD
{

};

class VOLUME_CONTROL
{

};
*/

// ---------------------------------------------------------------------------------------
// Gadgets functions

// Drawing a progress bar
string simple_progress_bar(int size, int max_value, int value);
// draw simple bar.



#endif