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
#include "helper_ncurses.h"
#include "api_rtlairband.h"

using namespace std;

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
  bool CounterOn = false;
  int Counter = 0;

  public:

  Title_Bar_Properties PROP;  

  void modify(int id, string name, string label, int size, int color, int bcolor)
  // Changes all properties
  {
    PROP.ID = id;
    PROP.NAME = name;
    PROP.LABEL = label;

    PROP.SIZE = size;
    PROP.COLOR = color;

    PROP.CHANGED = true;
  }

  void create(int id, string name, string label, int size, int color, int bcolor)
  // Define and behavior.  
  // Like set but leaves off position and size details.
  // Does not create window.

  {
    PROP.ID = id;
    PROP.NAME = name;
    PROP.LABEL = label;

    PROP.SIZE = size;
    PROP.COLOR = color;
    PROP.BCOLOR = bcolor;

    winTitle = newwin(PROP.SIZEY, PROP.SIZEX, PROP.POSY, PROP.POSX);

    bool CHANGED = true;
  }

  void move_resize(int posY, int posX, int sizeY, int sizeX)
  // Redefine position and size.
  {
    PROP.POSX = posX;
    PROP.POSY = posY;
    PROP.SIZEX = sizeX;
    PROP.SIZEY = sizeY;

    winTitle = newwin(1, PROP.SIZE, PROP.POSY, sizeX - PROP.SIZE);

    refresh();

    wborder(winTitle,'|','|','-','-','+','+','+','+') ;

    bool CHANGED = true;
  }

  bool changed()
  // Returns true if any of the properties have changed.
  {
    return PROP.CHANGED;
  }

  void draw(bool Refresh)
  // Draw the text_box on the screen if the value has changed or if  
  //  the Refresh parameter is true.
  {
    if (PROP.CHANGED == true || Refresh == true)
    {
      wbkgd(winTitle, COLOR_PAIR(PROP.COLOR));
      wattron(winTitle, A_REVERSE);
      mvwprintw(winTitle, 0, 0, PROP.LABEL.c_str());
      wattroff(winTitle, A_REVERSE);

      PROP.CHANGED = false;

      wrefresh(winTitle);
    }
  }
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
  
  void clear_outside_max()
  // Remove old line, printed or unprint, that are outside the 
  //  max_lines range/
  {
    // keeping a buffer of 50, just to keep this routine from running
    //  with every new line added. 
    if (LINES.size()> (max_lines + 50))
    {
      // Erase lines from max to end.
      LINES.erase(LINES.begin()+max_lines, LINES.end());
    }
  }

  public:

  void add(unsigned long tmeCurrentMillis, string line)
  // Add a line to the line list. List is in reverse
  //  order. most recent is top of list.
  {
    Text_Line tmp_line;

    //  create a new console line from provided info. 
    tmp_line.tmeTime_stamp = tmeCurrentMillis;
    tmp_line.strLine = line;
    tmp_line.printed = false;

    LINES.push_front(tmp_line);  // Bring new console line to the front 
                                //  of the list.

    clear_outside_max();        // remove any old lines.
  }

  bool avail()
  // Returns true if there is something to be printed.  
  //  More specificly, will return the value of the printed status
  //  of the most recent line added to the line list. 
  {
    if (Refresh_Text_Line_List == true)
    {
      Refresh_Text_Line_List = false;
      return true;
    }
    else if (LINES.empty() == false)
    {
      if (LINES[0].printed == false)
      {
        return true;
      }
      else
      {
        return false;
      }
    }
    else
    {
      return false;
    }
  }

  Text_Line get_line_to_print(int pos)
  // Will return the line requested from the pos. 
  //  pos 0 is the most recent line added to the console line list.
  {
    if (pos < LINES.size() && pos >= 0)
    {
      LINES[pos].printed = true;
      return LINES[pos];
    }
    else
    {
      Text_Line tmp;
      return tmp;
    }
  }
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

  //Debug
  bool CounterOn = false;
  int Counter = 0;

  // Types:
  // -1 - Hidden
  //  0 - Read Only

  public:

  Text_Box_Properties PROP;  

  void modify(int id, string name, string label, int type, int color, int bcolor)
  // Changes all properties
  {
    PROP.ID = id;
    PROP.NAME = name;
    PROP.LABEL = label;

    PROP.TYPE = type;
    PROP.COLOR = color;

    PROP.CHANGED = true;
  }

  void create(int id, string name, string label, int type, int color, int bcolor)
  // Define and behavior.  
  // Like set but leaves off position and size details.
  // Does not create window.

  {
    PROP.ID = id;
    PROP.NAME = name;
    PROP.LABEL = label;

    PROP.TYPE = type;
    PROP.COLOR = color;
    PROP.BCOLOR = bcolor;

    winText_Box = newwin(PROP.SIZEY, PROP.SIZEX, PROP.POSY, PROP.POSX);

    bool CHANGED = true;
  }

  void move_resize(int posY, int posX, int sizeY, int sizeX)
  // Redefine position and size.
  {
    PROP.POSX = posX;
    PROP.POSY = posY;
    PROP.SIZEX = sizeX;
    PROP.SIZEY = sizeY;

    winText_Box = newwin(PROP.SIZEY, PROP.SIZEX, PROP.POSY, PROP.POSX);

    refresh();

    wborder(winText_Box,'|','|','-','-','+','+','+','+') ;

    bool CHANGED = true;
  }

  bool changed()
  // Returns true if any of the properties have changed.
  {
    return PROP.CHANGED;
  }

  void draw(bool Refresh)
  // Draw the text_box on the screen if the value has changed or if  
  //  the Refresh parameter is true.
  {
    if (PROP.CHANGED == true || Refresh == true)
    {
      Text_Line line;
      int yCurPos = 0;

      for( int y=0; y < PROP.SIZEY; y++ )
      {
        // line position on screen or window
        yCurPos = PROP.SIZEY -y -1;

        // get next line to print from the line history
        line = PROP.LINES.get_line_to_print(y);

        // print the line to the screen
        wmove(winText_Box, yCurPos, PROP.POSX);  //move cursor to next line to print or clear.
        wclrtoeol(winText_Box);            // clear line befor printing to it.
        mvwprintw(winText_Box, yCurPos, PROP.POSX, "%s", line.strLine.c_str());  //print line.       
      }

      PROP.CHANGED = false;
      
      wrefresh(winText_Box);
    }
  }

  void add_line(unsigned long Time_Milli, string Text)
  // Add a line of text to Text_Box.
  {
    PROP.LINES.add(Time_Milli, Text);
    PROP.CHANGED = true;
  }
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

  //Debug
  bool CounterOn = false;
  int Counter = 0;

  // Types:
  // -1 - Hidden
  //  0 - Single Click
  //  1 - Toggle Button
  //  2 - Radio Button (Zone)

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

  void create()
  //void create(int id, string name, string label, int value, int type, int color, int bcolor)
  // Define button and behavior.  
  // Like set but leaves off position and size details.
  // Does not create window.
  {
    winButton = newwin(PROP.SIZEY, PROP.SIZEX, PROP.POSY, PROP.POSX);

    bool CHANGED = true;
  }

  void move_resize(int posY, int posX, int sizeY, int sizeX)
  // Redefine button position and size.
  {
    PROP.POSX = posX;
    PROP.POSY = posY;
    PROP.SIZEX = sizeX;
    PROP.SIZEY = sizeY;

    winButton = newwin(PROP.SIZEY, PROP.SIZEX, PROP.POSY, PROP.POSX);

    refresh();

    wborder(winButton,'|','|','-','-','+','+','+','+') ;

    bool CHANGED = true;
  }

  bool changed()
  // Returns true if any of the properties have changed.
  {
    return PROP.CHANGED;
  }

  void advance()
  // Brings the value of the button up to its next value state
  //  e.g. A simple button Off (value = 0) would advance to On (value = 1).
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
  // Draw the button on the screen if the value has changed or if  
  //  the Refresh parameter is true.
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

  void create_button(int Id, string Name, string Label, int Value, int Type, int Color, int BColor)
  {
    Button tmp_button;

    tmp_button.create();
    tmp_button.modify(Id, Name, Label, Value, Type, Color, BColor);
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
        mvwprintw(winWindow, YPOS, XPOS + LABEL_SIZE + SIZE +3 + (step *4), " %3d ", get_min_value());
        step ++;
      }
      if (PRINT_VALUE == true)
      {
        mvwprintw(winWindow, YPOS, XPOS + LABEL_SIZE + SIZE +3 + (step *4), " %3d ", VALUE);
        step ++;
      }
      if (PRINT_MAX == true)
      {
        mvwprintw(winWindow, YPOS, XPOS + LABEL_SIZE + SIZE +3 + (step *4), " %3d ", get_max_value());
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

  void progress_bar(WINDOW *winWindow, int YPos, int XPos, int value, unsigned long tmeFrame_Time)
  // Print progress bar in window at coords with value as progress.
  // Also receives time value for max min fade away.
  {
    YPOS = YPos;
    XPOS = XPos;
    VALUE = value;

    TIME_PROVIDED = true;
    FRAME_TIME = tmeFrame_Time;

    draw_bar(1, winWindow);
    TIME_PROVIDED = false;
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
  // Print guage bar in window at coords with value as progress.
  {
    YPOS = YPos;
    XPOS = XPos;
    VALUE = value;

    draw_bar(2, winWindow);
  }

  void guage_bar(WINDOW *winWindow, int YPos, int XPos, int value, unsigned long tmeFrame_Time)
  // Print guage bar in window at coords with value as progress.
  // Also receives time value for max min fade away.
  {
    YPOS = YPos;
    XPOS = XPos;
    VALUE = value;

    TIME_PROVIDED = true;
    FRAME_TIME = tmeFrame_Time;

    draw_bar(2, winWindow);
    TIME_PROVIDED = false;
  }

  void guage_bar(WINDOW *winWindow, int YPos, int XPos, int size, int max_value, int value)
  // Print guage bar in window at coords with value as progress.
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

  bool CLICKED = false;
  bool CHANGED = false;
};

class Radio_Channel
// Routines for create, draw, modify, and behavior.
// Note: Function needs frame time to function.
{
  private:

  // Gadget window
  WINDOW * winFrequency;

  // Show frequency levels in progress bars
  BAR BAR_NOISE_LEVEL;
  BAR BAR_SIGNAL_LEVEL;

  // Time Provided
  unsigned long FRAME_TIME;             // Internal

  // Timing
  TIMED_PING LINGER_DIRTY_SIGNAL;
  TIMED_PING VISIBLE_UPDATE_SIGNAL;
  int LINGER_TIME = 15000;
  int VISIBLE_UPATE_TIME = 200;

  // Was gadget redrawn during the previous draw cycle.
  bool WAS_REDRAWN = false;

  //Debug
  bool CounterOn = false;
  int Counter = 0;

  public:

  Radio_Channel_Properties PROP;  

  void modify(int id, string name, string label, int value, int type, int color, int bcolor)
  // Changes all button properties
  {
    PROP.ID = id;
    PROP.NAME = name;
    PROP.LABEL = label;

    PROP.TYPE = type;
    PROP.COLOR = color;

    PROP.CHANGED = true;
  }

  void create(int id, string name, string label, int type, int color, int bcolor)
  // Define and behavior.  
  // Like set but leaves off position and size details.
  // Does not create window.
  {
    PROP.ID = id;
    PROP.NAME = name;
    PROP.LABEL = label;

    PROP.TYPE = type;
    PROP.COLOR = color;
    PROP.BCOLOR = bcolor;

    winFrequency = newwin(PROP.SIZEY, PROP.SIZEX, PROP.POSY, PROP.POSX);

    BAR_NOISE_LEVEL.label("NOISE: ");
    BAR_NOISE_LEVEL.label_size(11);
    BAR_NOISE_LEVEL.size(15);
    BAR_NOISE_LEVEL.max_value(100);
    BAR_NOISE_LEVEL.print_min(true);
    BAR_NOISE_LEVEL.print_max(true);
    BAR_NOISE_LEVEL.min_max(true);
    BAR_NOISE_LEVEL.min_max_time_span(60000);

    BAR_SIGNAL_LEVEL.label("SIGNAL: ");
    BAR_SIGNAL_LEVEL.label_size(11);
    BAR_SIGNAL_LEVEL.size(15);
    BAR_SIGNAL_LEVEL.max_value(100);
    BAR_SIGNAL_LEVEL.print_min(true);
    BAR_SIGNAL_LEVEL.print_max(true);
    BAR_SIGNAL_LEVEL.min_max(true);
    BAR_SIGNAL_LEVEL.min_max_time_span(60000);

    bool CHANGED = true;
  }

  void move_resize(int posY, int posX, int sizeY, int sizeX)
  // Redefine button position and size.
  {
    PROP.POSX = posX;
    PROP.POSY = posY;
    PROP.SIZEX = sizeX;
    PROP.SIZEY = sizeY;

    winFrequency = newwin(PROP.SIZEY, PROP.SIZEX, PROP.POSY, PROP.POSX);

    refresh();

    //wborder(winFrequency,'|','|','-','-','+','+','+','+') ;
    wborder(winFrequency,' ',' ',' ',' ',' ',' ',' ',' ') ;
  }

  bool changed()
  // Returns true if any of the properties have changed.
  {
    return PROP.CHANGED;
  }

  void update_value(API_SQUELCH_DESTINATION &New_Value)
  {
    PROP.VALUE.FREQUENCY = New_Value.FREQUENCY;
    PROP.VALUE.LABEL = New_Value.LABEL;
    PROP.VALUE.NOISE_LEVEL = New_Value.NOISE_LEVEL;
    PROP.VALUE.SIGNAL_LEVEL = New_Value.SIGNAL_LEVEL;
    PROP.VALUE.SIGNAL_OUTSIDE_FILTER = New_Value.SIGNAL_OUTSIDE_FILTER;
    PROP.VALUE.IS_OPEN = New_Value.IS_OPEN;

    PROP.CHANGED = true;
    New_Value.CHANGED = false;

    // Enable gadget to display.
    PROP.TYPE = 0;

  }

  void draw(bool Refresh, unsigned long tmeFrame_Time)
  // Draw the text_box on the screen if the value has changed or if  
  //  the Refresh parameter is true.
  {
    FRAME_TIME = tmeFrame_Time;

    // Update if the Dirty Signal indicator has changed.
    if (LINGER_DIRTY_SIGNAL.blip_moved(FRAME_TIME) == true ||
        VISIBLE_UPDATE_SIGNAL.blip_moved(FRAME_TIME) == true)
    {
      Refresh = true;
    }

    if ((PROP.CHANGED == true || Refresh == true) && (PROP.TYPE >=0))
    {

      //
      if (PROP.CHANGED == true)
      {
        VISIBLE_UPDATE_SIGNAL.ping_up(FRAME_TIME, VISIBLE_UPATE_TIME);
      }

      // Set colors.

      // Channel Open
      if (PROP.VALUE.IS_OPEN == true)
      {
        // Reset the linger timer.
        LINGER_DIRTY_SIGNAL.ping_up(FRAME_TIME, LINGER_TIME);

        // Change Colors
        wbkgd(winFrequency, COLOR_PAIR(CRT_get_color_pair(COLOR_WHITE, PROP.BCOLOR)));
        BAR_NOISE_LEVEL.color_background(COLOR_WHITE);
        BAR_SIGNAL_LEVEL.color_background(COLOR_WHITE);
      }
      // Outside Filter
      else if (PROP.VALUE.SIGNAL_OUTSIDE_FILTER == true)
      {
        // Reset the linger timer.
        LINGER_DIRTY_SIGNAL.ping_up(FRAME_TIME, LINGER_TIME);

        // Change the colors.
        wbkgd(winFrequency, COLOR_PAIR(CRT_get_color_pair(COLOR_YELLOW, PROP.BCOLOR)));
        BAR_NOISE_LEVEL.color_background(COLOR_YELLOW);
        BAR_SIGNAL_LEVEL.color_background(COLOR_YELLOW);
      } 
      // If lingering dirty signal.
      else if (LINGER_DIRTY_SIGNAL.ping_down(FRAME_TIME) == true)
      {
        // Change the colors.
        wbkgd(winFrequency, COLOR_PAIR(CRT_get_color_pair(COLOR_YELLOW, PROP.BCOLOR)));
        BAR_NOISE_LEVEL.color_background(COLOR_YELLOW);
        BAR_SIGNAL_LEVEL.color_background(COLOR_YELLOW);  
      }
      // Updated
      else if (VISIBLE_UPDATE_SIGNAL.ping_down(FRAME_TIME) == true)
      {
        // Change the colors.
        wbkgd(winFrequency, COLOR_PAIR(CRT_get_color_pair(PROP.BCOLOR, COLOR_GREEN)));
        BAR_NOISE_LEVEL.color_background(PROP.BCOLOR);
        BAR_SIGNAL_LEVEL.color_background(PROP.BCOLOR);
      }
      // Listening
      else
      {
        // Change the colors.
        wbkgd(winFrequency, COLOR_PAIR(CRT_get_color_pair(PROP.BCOLOR, PROP.COLOR)));
        BAR_NOISE_LEVEL.color_background(PROP.BCOLOR);
        BAR_SIGNAL_LEVEL.color_background(PROP.BCOLOR);
      }

      // Print Values
      mvwprintw(winFrequency, 0, 0, "     FREQ:  %3.3f", ((float)PROP.VALUE.FREQUENCY / 1000000));
      mvwprintw(winFrequency, 0, 21, "%s", (PROP.VALUE.LABEL.c_str()));
      //Draw Bars

      BAR_SIGNAL_LEVEL.progress_bar(winFrequency, 1, 0, (100 + PROP.VALUE.SIGNAL_LEVEL), FRAME_TIME);
      BAR_NOISE_LEVEL.progress_bar(winFrequency, 2, 0, (100 + PROP.VALUE.NOISE_LEVEL), FRAME_TIME);

      // Reset Properties Changed.
      PROP.CHANGED = false;
      WAS_REDRAWN = true;

      // Draw the Gadget.
      wrefresh(winFrequency);
    }
    else
    {
      // Set redrawn indicator
      WAS_REDRAWN = false;
    }
  }

  bool was_redrawn()
  // Returns true if the gadget redrew itself during the previous cycle.
  {
    return WAS_REDRAWN;
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