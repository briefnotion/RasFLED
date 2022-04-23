// ***************************************************************************************
// *
// *    Core       | Everything within this document is proprietary to Core Dynamics.
// *    Dynamics   | Any unauthorized duplication will be subject to prosecution.
// *
// *    Department : (R+D)^2                        Name: buttons.h
// *       Sub Dept: Programming
// *    Location ID: 856-45B
// *                                                      (c) 2856 - 2858 Core Dynamics
// ***************************************************************************************

#ifndef BUTTONS_H
#define BUTTONS_H

// Color pairing definitions for screen colors.
//  Bacward Compatability
// To Be Phased Out
#define C_RED_BLACK 1
#define C_YELLOW_BLACK 2
#define C_GREEN_BLACK 3
#define C_BLUE_BLACK 4

#define C_WHITE_RED 17
#define C_WHITE_YELLOW 27
#define C_WHITE_GREEN 37
#define C_WHITE_BLUE 47
#define C_WHITE_PURPLE 57
#define C_WHITE_CYAN 67
#define C_WHITE_BLACK 07

#define C_BLACK_WHITE 70

#define C_BLACK_RED 10
#define C_BLACK_YELLOW 20
#define C_BLACK_GREEN 30
#define C_BLACK_BLUE 40
#define C_BLACK_PURPLE 50
#define C_BLACK_CYAN 60
#define C_BLACK_BLACK 70


// Standard Header Files
#include <stdio.h>
#include <ncurses.h>
#include <string.h>
#include <deque>

#include "stringthings.h"
#include "helper_ncurses.h"

using namespace std;

// -------------------------------------------------------------------------------------
// Button properties
class Button_Properties
{
  public: 

  int ID;
  string NAME = "";
  string LABEL = "";
  
  int VALUE = 0;

  int TYPE = 0;
  int COLOR = 0;
  int BCOLOR = 0;
  
  int POSY = 0;
  int POSX = 0;
  int SIZEY = 0;
  int SIZEX = 0;

  bool CLICKED = false;
  bool CHANGED = false;
};


// -------------------------------------------------------------------------------------
// Button Variable
class Button
{
  private:

  WINDOW * winButton;

  //Debug
  bool CounterOn = false;
  int Counter = 0;

  // Types:
  // -1 - dont show
  //  0 - click
  //  1 - toggle
  //  2 - radio (for the zone) (Not Implemented)

  public:

  Button_Properties PROP;  

  void modify(int id, string name, string label, int value, int type, int color, int bcolor)
  // Changes all button properties
  {
    PROP.ID = id;
    PROP.NAME = name;
    PROP.LABEL = label;

    PROP.VALUE = value;

    PROP.TYPE = type;
    PROP.COLOR = color;

    PROP.CHANGED = true;
  }

  void create(int id, string name, string label, int value, int type, int color, int bcolor)
  // Define button and behavior.  
  // Like set but leaves off position and size details.
  // Does not create window.

  //      COLOR_BLACK   0
  //      COLOR_RED     1
  //      COLOR_GREEN   2
  //      COLOR_YELLOW  3
  //      COLOR_BLUE    4
  //      COLOR_MAGENTA 5
  //      COLOR_CYAN    6
  //      COLOR_WHITE   7

  {
    PROP.ID = id;
    PROP.NAME = name;
    PROP.LABEL = label;

    PROP.VALUE = value;
    PROP.TYPE = type;
    PROP.COLOR = color;
    PROP.BCOLOR = bcolor;

    winButton = newwin(PROP.SIZEY, PROP.SIZEX, PROP.POSY, PROP.POSX);

    bool CHANGED = true;
  }

  void set(int id, string name, string label, int posY, int posX, int sizeY, int sizeX, int value, int type, int color, int bcolor)
  // Define button and behavior.
  {
    PROP.ID = id;
    PROP.NAME = name;
    PROP.LABEL = label;
    PROP.POSX = posX;
    PROP.POSY = posY;
    PROP.SIZEX = sizeX;
    PROP.SIZEY = sizeY;

    PROP.VALUE = value;
    PROP.TYPE = type;
    PROP.COLOR = color;
    PROP.BCOLOR = bcolor;

    winButton = newwin(PROP.SIZEY, PROP.SIZEX, PROP.POSY, PROP.POSX);

    refresh();

    wborder(winButton,'|','|','-','-','+','+','+','+') ;
    wrefresh(winButton);

    bool CHANGED = true;
  }

  void move_resize(int posY, int posX, int sizeY, int sizeX)
  // Define button and behavior.
  // Like set but only allows pos and size to change.
  // Recreates the window.
  {
    PROP.POSX = posX;
    PROP.POSY = posY;
    PROP.SIZEX = sizeX;
    PROP.SIZEY = sizeY;

    winButton = newwin(PROP.SIZEY, PROP.SIZEX, PROP.POSY, PROP.POSX);

    refresh();

    wborder(winButton,'|','|','-','-','+','+','+','+') ;
    //wrefresh(winButton);

    bool CHANGED = true;
  }

  bool changed()
  {
    return PROP.CHANGED;
  }

  void advance()
  {
    //LABEL = "clicked";
    if (PROP.TYPE == 0)  // Click Button
    {
      PROP.VALUE = 1;
    }
    if (PROP.TYPE == 1)  // Toggle Type
    {
      if (PROP.VALUE == 0)
      {
        PROP.VALUE = 1;
      }
      else
      {
        PROP.VALUE = 0;
      }
    }
    if (PROP.TYPE == 2)  // Radio Type
    {
      // Let the zone manager handle its value.
    }

    PROP.CHANGED = true;
  }

  void draw(bool Refresh)
  // draw
  {
    if (PROP.CHANGED == true || Refresh == true)
    {
      string top = "";
      string mid = "";
      string bot = "";

      string strorig = PROP.LABEL;
      string strtmp = "";

      int p = 0;
      int y = 0;

      /*    This code was developed before color was given to the
            buttons.  Though functional, they dont look that great.
            So... If ever a no color is created, they may still be 
            fuctional.  Or, maybe a button type param could be made 
            if needed. 
      
      if (PROP.TYPE == 0 || PROP.TYPE == 1)
      {
        if (PROP.VALUE == 0)
        {
          wattroff(winButton, A_REVERSE);
          top = " " + top.append(PROP.SIZEX -2, '-') + " ";
          mid = "|" + mid.append(PROP.SIZEX -2, ' ') + "|";
          bot = " " + bot.append(PROP.SIZEX -2, '-') + " ";
        }
        else
        {
          wattron(winButton, A_REVERSE);
          top = " " + top.append(PROP.SIZEX -2, ' ') + " ";
          mid = " " + mid.append(PROP.SIZEX -2, ' ') + " ";
          bot = " " + bot.append(PROP.SIZEX -2, '_') + " ";
        }
      }
      else
      {
        wattroff(winButton, A_REVERSE);
        top = " " + top.append(PROP.SIZEX -2, ' ') + " ";
        mid = " " + mid.append(PROP.SIZEX -2, ' ') + " ";
        bot = " " + bot.append(PROP.SIZEX -2, ' ') + " ";
      }
      */

      //Set Color, Set Reverse if On, Draw Sencils for Buttons
      if (PROP.TYPE == 0 || PROP.TYPE == 1 || PROP.TYPE == 2)
      {

        // Start by setting button color.
        wbkgd(winButton, COLOR_PAIR(PROP.COLOR));
        
        // Top Sides and Bottom
        top = " " + top.append(PROP.SIZEX -2, ' ') + " ";
        mid = " " + mid.append(PROP.SIZEX -2, ' ') + " ";
        bot = " " + bot.append(PROP.SIZEX -2, '_') + " ";

        if (PROP.VALUE == 0)
        // Just reverse the colors if Button is on
        {
          wattroff(winButton, A_REVERSE);
        }
        else
        {
          // If the color background is not black, this works 
          //  fine.
          wattron(winButton, A_REVERSE);  // Nope, NVM. Keeping this.

          // However
          //wbkgd(winButton, COLOR_PAIR(C_BLACK_WHITE));

          // Perhaps in the future, I will add a translate to 
          //  reverse the colors with white background and 
          //  text as background color.
        }
      }
      else
      // If button type is unknow then dont draw anything.
      {
        wbkgd(winButton, COLOR_PAIR(0));
        wattroff(winButton, A_REVERSE);
        top = " " + top.append(PROP.SIZEX -2, ' ') + " ";
        mid = " " + mid.append(PROP.SIZEX -2, ' ') + " ";
        bot = " " + bot.append(PROP.SIZEX -2, ' ') + " ";
      }

      //Draw button at position with centered text.
      int x=0;
      while (x < PROP.SIZEX)
      {
        p = strorig.find('%');
        if (p >= 0)
        {
          strtmp = strorig.substr(0,p);
          strorig.erase(0,p+1);
        }
        else 
        {
          strtmp = strorig;
          strorig = "";
        }

        if (x==0) // Top
        {
          mvwprintw(winButton, x, 0, linemerge(PROP.SIZEX, top ,strtmp).c_str());
        }
        else if (x==PROP.SIZEY-1) // Bot
        {
          mvwprintw(winButton, x, 0, linemerge(PROP.SIZEX, bot ,strtmp).c_str());
        }
        else // Mid
        {
          mvwprintw(winButton, x, 0, linemerge(PROP.SIZEX, mid ,strtmp).c_str());
        }

        x++;
      }

      //Debug -- displays dedraw count and other variables
      if (CounterOn == true)
      {

        Counter++;
        mvwprintw(winButton, 0, 0, to_string(Counter).c_str());
        mvwprintw(winButton, 1, 0, to_string(PROP.SIZEY).c_str());
        mvwprintw(winButton, 2, 0, to_string(PROP.SIZEX).c_str());
      }

      wattroff(winButton, A_REVERSE);
      wrefresh(winButton);

      // If the button is simple click, reset its value to 0 and
      //  leave the changed property on so that it can be redrawn off
      //  at next pass.
      if (PROP.TYPE == 0 && PROP.VALUE == 1)
      {
        PROP.VALUE = 0;
        PROP.CHANGED == true;
      }
      else
      {
        PROP.CHANGED = false;
      }
    }
  }
};


// -------------------------------------------------------------------------------------
// Button Variable
class Button_Zone_Manager
{
  private:

  //deque<Button_Properties> ZONES;

  deque<Button> BUTTONS;

  public:

  int size()
  // return the size
  {
    return BUTTONS.size();
  }

  string name(int pos)
  // return the name at the pos
  {
    return BUTTONS[pos].PROP.NAME;
  }

  int value(int pos)
  // return the value at the pos
  {
    return BUTTONS[pos].PROP.VALUE;
  }

  void click_advance(int Id)
  {
    if (BUTTONS[Id].PROP.TYPE == 0 || BUTTONS[Id].PROP.TYPE == 1)
    {
      BUTTONS[Id].advance();
    }
    else if (BUTTONS[Id].PROP.TYPE == 2)
    {
      for (int pos = 0; pos < BUTTONS.size(); pos++)
      {
        BUTTONS[pos].PROP.VALUE = 0;
        BUTTONS[pos].PROP.CHANGED = true;
      }
      BUTTONS[Id].PROP.VALUE = 1;
    }
  }

  void create_button()
  {
    Button tmp_button;

    tmp_button.create(0, "", "", 0, 0, 0, 0);
    BUTTONS.push_back(tmp_button);
  }

  void modify(int Id, string Name, string Label, int Value, int Type, int Color, int BColor)
  {
    BUTTONS[Id].PROP.ID = Id;
    BUTTONS[Id].PROP.NAME = Name;
    BUTTONS[Id].PROP.LABEL = Label;
    BUTTONS[Id].PROP.VALUE = Value;
    BUTTONS[Id].PROP.TYPE = Type;
    BUTTONS[Id].PROP.COLOR = Color;
    BUTTONS[Id].PROP.BCOLOR = BColor;
    BUTTONS[Id].PROP.CHANGED = true;
  }

  void move_resize(int Id, int posY, int posX, int sizeY, int sizeX)
  {
    BUTTONS[Id].move_resize(posY, posX, sizeY, sizeX);
  }

  void draw(bool Refresh)
  {
    if (BUTTONS.size() >0)
    {
      for (int pos = 0; pos < BUTTONS.size(); pos++)
      {
        BUTTONS[pos].draw(Refresh);
      }
    }
  }

  void change_label(string name, string label)
  {
    for(int pos=0; pos<BUTTONS.size(); pos++)
    {
      if (BUTTONS[pos].PROP.NAME == name)
      {
        if (BUTTONS[pos].PROP.LABEL != label)
        {
          BUTTONS[pos].PROP.LABEL = label;
          BUTTONS[pos].PROP.CHANGED = true;
        }
      }
    }
  }

  void change_value(string name, int value)
  {
    for(int pos=0; pos<BUTTONS.size(); pos++)
    {
      if (BUTTONS[pos].PROP.NAME == name)
      {
        if (BUTTONS[pos].PROP.VALUE != value)
        {
          BUTTONS[pos].PROP.VALUE = value;
          BUTTONS[pos].PROP.CHANGED = true;
        }
      }
    }
  }

  string get_clicked_name()
  // returns the name of the first clicked button in the list
  {
    string name = "";
    
    for (int pos = 0; pos < BUTTONS.size(); pos ++)
    {
      if (BUTTONS[pos].PROP.CLICKED == true)
      {
        name = BUTTONS[pos].PROP.NAME;
        return name;
      }
    }
    return name;
  }

  int get_clicked_value(string name)
  // returns the value of the named clicked button in the list
  {
    int value = 0;
    for (int pos = 0; pos < BUTTONS.size(); pos ++)
    {
      if (BUTTONS[pos].PROP.NAME == name)
      {
        value = BUTTONS[pos].PROP.VALUE;
        BUTTONS[pos].PROP.CLICKED = false;
        return value;
      }
    }
    return value;
  }

  bool check_click(int x,int y)
  // Check to see if any button in the list was clicked.
  {
    bool clicked = false;
    
    for(int pos=0; pos<BUTTONS.size(); pos++)
    {
      if(x >= BUTTONS[pos].PROP.POSX && x <= (BUTTONS[pos].PROP.POSX + BUTTONS[pos].PROP.SIZEX -1) &&
         y >= BUTTONS[pos].PROP.POSY && y <= (BUTTONS[pos].PROP.POSY + BUTTONS[pos].PROP.SIZEY -1))
      {
        clicked = true;
        BUTTONS[pos].PROP.CLICKED = true;
        click_advance(pos);

        return clicked;
      }
    }
    return clicked;
  }
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

  void clear()
  {
    ACTIVE = false;
    MIN_VALUE = 0;
    MAX_VALUE = 0;
    SNAPSHOT = "";
  }

  bool active()
  {
    return ACTIVE;
  }

  void store_min_max(int Value)
  {
    if (ACTIVE == false)
    {
      MIN_VALUE = Value;
      MAX_VALUE = Value;
      ACTIVE = true;
    }
    else
    {
      if (Value < MIN_VALUE)
      {
        MIN_VALUE = Value;
      }
      if (Value > MAX_VALUE)
      {
        MAX_VALUE = Value;
      }
    }
  }

  int min()
  {
    return MIN_VALUE;
  }

  int max()
  {
    return MAX_VALUE;
  }
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

  int YPOS = 0;             // Y start position of gaudget in window.
  int XPOS = 0;             // X start position of gaudget in window.

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
  int get_min_value()
  {
    bool found = false;
    int min = 0;

    for (int x = 0; x < TIME_SLICES.size(); x++)
    {
      if (TIME_SLICES[x].active() == true)
      {
        if (found == false)
        {
          min = TIME_SLICES[x].min();
          found = true;
        }
        else
        {
          if (TIME_SLICES[x].min() < min)
          {
            min = TIME_SLICES[x].min();
          }
        }
      }
    }
    return min;
  }

  // I dont like this
  int get_max_value()
  {
    bool found = false;
    int max = 0;

    for (int x = 0; x < TIME_SLICES.size(); x++)
    {
      if (TIME_SLICES[x].active() == true)
      {
        if (found == false)
        {
          max = TIME_SLICES[x].max();
          found = true;
        }
        else
        {
          if (TIME_SLICES[x].max() > max)
          {
            max = TIME_SLICES[x].max();
          }
        }
      }
    }
    return max;
  }

  void wat_on_background(WINDOW *winWindow)
  // Set background color to print.
  {
    wattron(winWindow, COLOR_PAIR(CRT_get_color_pair(COLOR_BACKGROUND, COLOR_FOREGROUND)));
  }

  void wat_off_background(WINDOW *winWindow)
  // Set background color off to print to red.
  {
    wattroff(winWindow, COLOR_PAIR(CRT_get_color_pair(COLOR_BACKGROUND, COLOR_FOREGROUND)));
  }

  void wat_on_red(WINDOW *winWindow)
  // Set color to print to red.
  {
    wattron(winWindow, COLOR_PAIR(CRT_get_color_pair(COLOR_BACKGROUND, COLOR_RED)));
  }

  void wat_off_red(WINDOW *winWindow)
  // Set color off to print to red.
  {
    wattroff(winWindow, COLOR_PAIR(CRT_get_color_pair(COLOR_BACKGROUND, COLOR_RED)));
  }

  void wat_on_green_red(WINDOW *winWindow, bool value)
  // Set color to print to green if true. Set color to print to red if false.
  {
    if(value == true)
    {
      wattron(winWindow, COLOR_PAIR(CRT_get_color_pair(COLOR_BACKGROUND, COLOR_GREEN)));
    }
    else
    {
      wattron(winWindow, COLOR_PAIR(CRT_get_color_pair(COLOR_BACKGROUND, COLOR_RED)));
    }
  }

  void wat_off_green_red(WINDOW *winWindow, bool value)
  // Set color off to print to green if true. Set color off to print to red if false.
  {
    if(value == true)
    {
      wattroff(winWindow, COLOR_PAIR(CRT_get_color_pair(COLOR_BACKGROUND, COLOR_GREEN)));
    }
    else
    {
      wattroff(winWindow, COLOR_PAIR(CRT_get_color_pair(COLOR_BACKGROUND, COLOR_RED)));
    }
  }

  int get_marker_pos(int value)
  // calculate the size of the fill bar with respects to full bar size.
  {
    int pos = abs(SIZE*value/MAX_VALUE);

    // Check bounds
    if (pos > SIZE)
    {
      pos = SIZE;
    }

    return pos;
  }

  void print_marker(WINDOW *winWindow, int Ypos, int Xpos, int value)
  // Draw marker at value on guage.
  //  Draws > if exceeding max of guage size.
  //  Draws < if exceeding min of guage size.
  {
    char marker = '|';
    
    if (value > MAX_VALUE)
    {
      marker = '>';
    }
    else if (value < MIN_VALUE)
    {
      marker = '<';
    }

    mvwprintw(winWindow, Ypos, Xpos + get_marker_pos(value), "%c", marker);
  }

  void draw_bar(int Bar_Type, WINDOW *winWindow)
  // Drawing a progress bar
  // This function is only acessable within this class.

  //  Bar Type
  //  1 - Progress Bar
  //  2 - Variable Guage Bar
  //  3 - Mechanical Guage Bar

  {
    string label = "";

    string bar = "";
    string fill = "";
    int bar_size = 0;

    // Initial setup of min max timer variable for first run.
    if (TIME_PROVIDED == true && TIME_SLICE_TIMER.is_set() == false)
    {
      TIME_SLICE_TIMER.set(FRAME_TIME, MIN_MAX_TIME_SPAN / 5);
    }

    // create empty label
    if (LABEL.size() < LABEL_SIZE)
    {
      label = label.append(LABEL_SIZE - LABEL.size(), ' ') + LABEL;
    }
    else
    {
      label = LABEL;
    }

    bar_size = get_marker_pos(VALUE);

    // create empty bar
    bar = bar.append(SIZE +1,' ');
    
    // Create Progress Bar
    if (Bar_Type == 1)
    {
      // create fill bar
      // put bar in empty bar
      bar.replace(0, bar_size, fill.append(bar_size , '|'  ));
    }

    // Store Min Max
    if (MIN_MAX == true)         // If Guage
    {
      // Advance the stored values if time is up.

      if (TIME_SLICE_TIMER.is_ready(FRAME_TIME) == true)
      {
        if (TIME_SLICES.size() >= TIME_SLICE_COUNT)
        {
          TIME_SLICES.pop_back();
          BAR_TIME_SLICE new_time_slice;
          TIME_SLICES.push_front(new_time_slice);
        }
        else if (TIME_SLICES.size() < TIME_SLICE_COUNT)
        {
          BAR_TIME_SLICE new_time_slice;
          TIME_SLICES.push_front(new_time_slice);
        }
      }
      TIME_SLICES.front().store_min_max(VALUE);
    }

    // Print bar

    // Print Label
    mvwprintw(winWindow, YPOS, XPOS, "%s", label.c_str());

    // Print Bar Start "[""
    mvwprintw(winWindow, YPOS, XPOS + LABEL_SIZE, "[");

    if (Bar_Type == 1)
    {
      // Print progress bar filler in color
      wat_on_green_red(winWindow, VALUE > 0);
      mvwprintw(winWindow, YPOS, XPOS + LABEL_SIZE +1, "%s", bar.c_str());
      wat_off_green_red(winWindow, VALUE > 0);
    }
    else if (Bar_Type == 2) // Guage bar blank background
    {
      wat_on_red(winWindow);
      mvwprintw(winWindow, YPOS, XPOS + LABEL_SIZE +1, "%s", bar.c_str());
      wat_off_red(winWindow);
    }

    // Print Bar End "]""
    mvwprintw(winWindow, YPOS, XPOS + LABEL_SIZE + SIZE +2 , "]");

    // Print Markers
    
    // Print Min Max
    if (MIN_MAX == true)
    {
      wat_on_red(winWindow);
      print_marker(winWindow, YPOS, XPOS + LABEL_SIZE + 1, get_min_value());
      print_marker(winWindow, YPOS, XPOS + LABEL_SIZE + 1, get_max_value());
      wat_off_red(winWindow);
    }
    // Print Indicator Marker
    wat_on_background(winWindow);
    print_marker(winWindow, YPOS, XPOS + LABEL_SIZE + 1, VALUE);
    wat_off_background(winWindow);

    // If Print Values are on
    if (PRINT_MIN == true || PRINT_VALUE == true || PRINT_MAX == true)
    {
      int step = 0;
      if (PRINT_MIN == true)
      {
        mvwprintw(winWindow, YPOS, XPOS + LABEL_SIZE + SIZE +3 + (step *4), " %03d ", get_min_value());
        step ++;
      }
      if (PRINT_VALUE == true)
      {
        mvwprintw(winWindow, YPOS, XPOS + LABEL_SIZE + SIZE +3 + (step *4), " %03d ", VALUE);
        step ++;
      }
      if (PRINT_MAX == true)
      {
        mvwprintw(winWindow, YPOS, XPOS + LABEL_SIZE + SIZE +3 + (step *4), " %03d ", get_max_value());
        step ++;
      }
    }

    // Debug
    //  mvwprintw(winWindow, YPOS, XPOS + LABEL_SIZE + SIZE +7, " %03d %03d %03d", 
    //                                                    TIME_SLICES.size(), TIME_SLICE_TIMER.get_ready_time(), FRAME_TIME);
  }

  public:

  void color_background(short Color)
  // Set the propertie for Background Color.
  // Expects NCurses color or color code. 
  {
    COLOR_BACKGROUND = Color;
  }

  void color_foreground(short Color)
  // Set the propertie for Foreground Color.
  // Expects NCurses color or color code. 
  {
    COLOR_FOREGROUND = Color;
  }

  void label(string Label)
  // Set the propertie for displayed label.
  {
    LABEL = Label;
  }

  void label_size(int Label_Size)
  // Set the propertie for displayed label size.
  {
    LABEL_SIZE = Label_Size;
  }

  void size(int Size)
  // Set the propertie for progress bar saize.
  {
    SIZE = Size;
  }

  void max_value(int Max_Value)
  // Set the propertie for progress bar max value.
  {
    MAX_VALUE = Max_Value;
  }

  void print_value(bool Print_Value)
  // Set property to print value entered to right of bar.
  {
    PRINT_VALUE = Print_Value;
  }

  void print_min(bool Print_Min)
  // Set property to print value entered to right of bar.
  {
    PRINT_MIN = Print_Min;
  }

  void print_max(bool Print_Max)
  // Set property to print value entered to right of bar.
  {
    PRINT_MAX = Print_Max;
  }

  // Guage variables
  void min_max(bool min_max)
  // Set property to activate Min Max observations.
  {
    MIN_MAX = min_max;
  }

  // Guage variables
  void min_max_time_span(int Time_Span_in_ms)
  // Set property time amount Min Max will track.
  {
    MIN_MAX_TIME_SPAN = Time_Span_in_ms;
  }

  // Creates a progress bar of 0 to 100 percent.
  //  Returns a string of size.
  //  Of size, the percentage of value to max_value will be filled
  //  with characters.
  void progress_bar(WINDOW *winWindow, int YPos, int XPos, int value)
  // Print progress bar in window at coords with value as progress.
  {
    YPOS = YPos;
    XPOS = XPos;
    VALUE = value;

    draw_bar(1, winWindow);
  }

  void progress_bar(WINDOW *winWindow, int YPos, int XPos, int size, int max_value, int value)
  // Print progress bar in window at coords with value as progress.
  // Also, allows for other properties to be change.
  {
    YPOS = YPos;
    XPOS = XPos;
    SIZE = size;
    MAX_VALUE = max_value;
    VALUE = value;

    draw_bar(1, winWindow);
  }

  // Creates a progress bar of 0 to 100 percent.
  //  Returns a string of size.
  //  Of size, the percentage of value to max_value will be filled
  //  with characters.
  void guage_bar(WINDOW *winWindow, int YPos, int XPos, int value)
  // Print progress bar in window at coords with value as progress.
  {
    YPOS = YPos;
    XPOS = XPos;
    VALUE = value;

    draw_bar(2, winWindow);
  }

    void guage_bar(WINDOW *winWindow, int YPos, int XPos, int value, unsigned long tmeFrame_Time)
  // Print progress bar in window at coords with value as progress.
  {
    YPOS = YPos;
    XPOS = XPos;
    VALUE = value;

    TIME_PROVIDED = true;
    FRAME_TIME = tmeFrame_Time;

    draw_bar(2, winWindow);
  }

  void guage_bar(WINDOW *winWindow, int YPos, int XPos, int size, int max_value, int value)
  // Print progress bar in window at coords with value as progress.
  // Also, allows for other properties to be change.
  {
    YPOS = YPos;
    XPOS = XPos;
    SIZE = size;
    MAX_VALUE = max_value;
    VALUE = value;

    draw_bar(2, winWindow);
  }
};


// ---------------------------------------------------------------------------------------
// Gadgets functions

// Drawing a progress bar
string simple_progress_bar(int size, int max_value, int value)
// Creates a simple progress bar of 0 to 100 percent.
//  Returns a string of size.
//  Of size, the percentage of value to max_value will be filled
//  with characters.
{
  string bar = "";
  string fill = "";
  int bar_size = 0;

  // create empty bar
  bar = bar.append(size,' ');

  // stay positive
  value = abs(value);

  // stay within size
  if (value > max_value)
  {
    value = max_value;
  }

  // calculate the size of the fill bar with respects to full bar size.
  bar_size = size*value/max_value;

  // create fill bar
  fill = fill.append(bar_size , '|'   );

  // put bar in empty bar
  bar.replace(0, bar_size, fill);

  return bar;
}




#endif