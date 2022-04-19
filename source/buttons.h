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
#define C_RED_BLACK 1
#define C_YELLOW_BLACK 2
#define C_GREEN_BLACK 3
#define C_BLUE_BLACK 4

#define C_WHITE_RED 5
#define C_WHITE_YELLOW 6
#define C_WHITE_GREEN 7
#define C_WHITE_BLUE 8
#define C_WHITE_PURPLE 9
#define C_WHITE_CYAN 10
#define C_WHITE_BLACK 11

#define C_BLACK_WHITE 12

#define C_BLACK_RED 15
#define C_BLACK_YELLOW 16
#define C_BLACK_GREEN 17
#define C_BLACK_BLUE 18
#define C_BLACK_PURPLE 19
#define C_BLACK_CYAN 20
#define C_BLACK_BLACK 21


// Standard Header Files
#include <stdio.h>
#include <ncurses.h>
#include <string.h>
#include <deque>

//#include "system.h"
//#include "consoleanddata.h"
//#include "player.h"

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

  string linefill(int size, string text)
  {
    string line = "";

    line = line.append(size,' ');

    line.replace(((size/2)-(text.length()/2)), text.length(), text);
    line.resize(size);
    return line;
  }

  string linemerge(int size, string line, string text)
  {
    int text_size = text.length();
    
    if (text_size > size)
    {
      text.resize(size);
      text_size = text.length();
    }

    line.replace(((size/2)-(text_size/2)), text_size, text);
    line.resize(size);
    return line;
  }

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
// Gadgets functions


// Drawing a progress bar
string progress_bar(int size, int max_value, int value)
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