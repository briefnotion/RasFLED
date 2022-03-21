// ***************************************************************************************
// *
// *    Core       | Everything within this document is proprietary to Core Dynamics.
// *    Dynamics   | Any unauthorized duplication will be subject to prosecution.
// *
// *    Department : (R+D)^2                        Name: screen3.h
// *       Sub Dept: Programming
// *    Location ID: 856-45B
// *                                                      (c) 2856 - 2858 Core Dynamics
// ***************************************************************************************

#ifndef SCREEN3_H
#define SCREEN3_H

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

#include "system.h"
#include "consoleanddata.h"
#include "player.h"

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
  bool CHANGED = false;

  void modify(int id, string name, string label, int value, int type, int color, int bcolor)
  // Changes all button properties
  {
    PROP.ID = id;
    PROP.NAME = name;
    PROP.LABEL = label;

    PROP.VALUE = value;

    PROP.TYPE = type;
    PROP.COLOR = color;

    CHANGED = true;
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
    wrefresh(winButton);

    bool CHANGED = true;
  }

  bool changed()
  {
    return CHANGED;
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

    CHANGED = true;
  }

  void draw(bool Refresh)
  // draw
  {
    if (CHANGED == true || Refresh == true)
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
        mvwprintw(winButton, 1, 0, to_string(PROP.COLOR).c_str());
        mvwprintw(winButton, 2, 0, to_string(PROP.VALUE).c_str());
      }

      wattroff(winButton, A_REVERSE);
      wrefresh(winButton);

      // If the button is simple click, reset its value to 0 and
      //  leave the changed property on so that it can be redrawn off
      //  at next pass.
      if (PROP.TYPE == 0 && PROP.VALUE == 1)
      {
        PROP.VALUE = 0;
        CHANGED == true;
      }
      else
      {
        CHANGED = false;
      }
    }
  }
};


// -------------------------------------------------------------------------------------
// Button Variable
class Button_Zone_Manager
{
  private:

  deque<Button_Properties> ZONES;

  public:

  int size()
  // return the size
  {
    return ZONES.size();
  }

  string name(int pos)
  // return the name at the pos
  {
    return ZONES[pos].NAME;
  }

  int value(int pos)
  // return the value at the pos
  {
    return ZONES[pos].VALUE;
  }

  void clear()
  // erase the button list.
  {
    ZONES.clear();
  }

  void change_label(string name, string label)
  {
    for(int pos=0; pos<ZONES.size(); pos++)
    {
      if (ZONES[pos].NAME.compare(name) == 0)
      {
        ZONES[pos].LABEL = label;
        ZONES[pos].CHANGED = true;
      }
    }
  }

  void change_value(string name, int value)
  {
    for(int pos=0; pos<ZONES.size(); pos++)
    {
      if (ZONES[pos].NAME.compare(name) == 0)
      {
        ZONES[pos].VALUE = value;
        ZONES[pos].CHANGED = true;
      }
    }
  }

  void scan(Button &button)
  // Add a buttons info to the button list.
  {
    int found = false;

    // try to find the premade zone then update.
    for(int pos=0; pos<ZONES.size(); pos++)
    {
      if (ZONES[pos].NAME.compare(button.PROP.NAME) == 0)
      {
        ZONES[pos].ID = button.PROP.ID;

        ZONES[pos].VALUE = button.PROP.VALUE;

        ZONES[pos].TYPE = button.PROP.TYPE;
        ZONES[pos].COLOR = button.PROP.COLOR;
        ZONES[pos].BCOLOR = button.PROP.BCOLOR;

        ZONES[pos].POSY = button.PROP.POSY;
        ZONES[pos].POSX = button.PROP.POSX;
        ZONES[pos].SIZEY = button.PROP.SIZEY;
        ZONES[pos].SIZEX = button.PROP.SIZEX;
        
        found = true;
      }
    }

    // if zone not found, create then add.
    if (found == false)
    {
      Button_Properties zone;

      zone.ID = button.PROP.ID;
      zone.NAME = button.PROP.NAME;

      zone.VALUE = button.PROP.VALUE;

      zone.TYPE = button.PROP.TYPE;
      zone.COLOR = button.PROP.COLOR;
      zone.BCOLOR = button.PROP.BCOLOR;

      zone.POSY = button.PROP.POSY;
      zone.POSX = button.PROP.POSX;
      zone.SIZEY = button.PROP.SIZEY;
      zone.SIZEX = button.PROP.SIZEX;

      ZONES.push_back(zone);
    }
  }

  void update_change_process(Button &button)
  // UPDATE THE BUTTONS FROM LIST
  // search button list for passed button, then 
  //  update properties of button if list items changed.
  //  process or advance if clicked.
  {
    // Regurlar buttons behave differantly than radio buttons.
    // For now, just checking the first button in the list.

    for(int pos=0; pos<ZONES.size(); pos++)
    {
      if (ZONES[pos].NAME.compare(button.PROP.NAME) == 0)
      {
        if (ZONES[pos].CHANGED == true)
        {
          button.PROP.LABEL = ZONES[pos].LABEL;

          button.PROP.VALUE = ZONES[pos].VALUE;

          button.PROP.TYPE = ZONES[pos].TYPE;
          button.PROP.COLOR = ZONES[pos].COLOR;
          button.PROP.BCOLOR = ZONES[pos].BCOLOR;

          button.PROP.POSY = ZONES[pos].POSY;
          button.PROP.POSX = ZONES[pos].POSX;
          button.PROP.SIZEY = ZONES[pos].SIZEY;
          button.PROP.SIZEX = ZONES[pos].SIZEX;

          ZONES[pos].CHANGED = false;
          button.CHANGED = true;
        }


        if (ZONES[pos].CLICKED == true)
        {
          if (button.PROP.TYPE == 0 || button.PROP.TYPE == 1)
          {
            button.advance();
            ZONES[pos].VALUE = button.PROP.VALUE;
          }

          if (button.PROP.TYPE == 2)
          // For radio buttons, follow up with setting the values.
          //  But only when the button that was clicked was found.
          {
            for(int pos_radio = 0; pos_radio < ZONES.size(); pos_radio++)
            {
              ZONES[pos_radio].VALUE = 0;
              ZONES[pos_radio].CHANGED = false;
            }

            ZONES[pos].VALUE = 1;
            button.PROP.VALUE = 1;
            button.CHANGED = true;
          }

        }

        if (ZONES[pos].CLICKED == false)
        {
          if (button.PROP.TYPE == 2)
          {
            button.PROP.VALUE = 0;
            button.CHANGED = true;
          }
        }
      }
    }
  }

  void advance_radio_buttons()
  // Radio Buttons
  //  Update all radio buttons if one was pressed.
  {
    if (ZONES[0].TYPE == 2)
    // check to see if the first button is a radio before continuing.
    {
      int pos_clicked = 0;

      // Find the first button in the list that has been 
      //  marked clicked.
      for(int pos = 0; pos < ZONES.size(); pos++)
      {
        if (ZONES[pos].CLICKED == true)
        {
          pos_clicked = pos;
        }
      }

      // Set value of all buttons to off, except the clicked 
      //  button.
      for(int pos = 0; pos < ZONES.size(); pos++)
      {
        ZONES[pos].VALUE = 0;
        ZONES[pos].CHANGED = false;
      }
      ZONES[pos_clicked].VALUE = 1;
    }
  }

  string get_clicked_name()
  // returns the name of the first clicked button in the list
  {
    string name = "";
    
    for (int pos = 0; pos < ZONES.size(); pos ++)
    {
      if (ZONES[pos].CLICKED == true)
      {
        name = ZONES[pos].NAME;
        return name;
      }
    }
    return name;
  }

  int get_clicked_value(string name)
  // returns the value of the named clicked button in the list
  {
    int value = 0;
    for (int pos = 0; pos < ZONES.size(); pos ++)
    {
      if (ZONES[pos].NAME.compare(name) == 0)
      {
        value = ZONES[pos].VALUE;
        ZONES[pos].CLICKED = false;
        return value;
      }
    }
    return value;
  }

  bool check_click(int x,int y)
  // Check to see if any button in the list was clicked.
  {
    bool clicked = false;
    
    for(int pos=0; pos<ZONES.size(); pos++)
    {
      if(x >= ZONES[pos].POSX && x <= (ZONES[pos].POSX + ZONES[pos].SIZEX -1) &&
         y >= ZONES[pos].POSY && y <= (ZONES[pos].POSY + ZONES[pos].SIZEY -1))
      {
        clicked = true;
        ZONES[pos].CLICKED = true;

        return clicked;
      }
    }
    return clicked;
  }

};
// ---------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------
class Screen3
// Color tty interface with main touch control buttons on right side. Large so they can be 
//  accessed in moving vehicle without difficulty.  Limited access to main program and 
//  communicates through the command line to avoid confusion if a more advanced interface 
//  is created in the futer.
//  Button Control is managed by consoleanddata mouse input.
//  Current screen status is manage through system
{
  private:
  // Keyboard input variable
  int key = -1;

  bool Supports_Color = false;


  // Window Configuration
  //   Y
  //   S   v-----------XMax-------------------v
  //   t  > __________________________________    <
  //   a  ||                            |     |   |
  //   t  ||       winStatus            |  w  |   |
  //   u  ||                            |  i  |   |Y
  //   s  >|____________________________|  n  |   |M
  //      ||                            |  B  |   |a
  //      ||                            |  u  |   |x
  //   Y  ||                            |  t  |   |
  //   C  ||                            |  t  |   |
  //   o  ||      winConsole            |  o  |   |
  //   n  ||                            |  n  |   |
  //   s  ||                            |  s  |   |
  //   o  ||                            |     |   |
  //   l  ||                            |     |   |
  //   e  >|____________________________|_____|   <
  //                                    ^-----^ XButtons
  //       ^-------XStatus--------------^
  //

  // Screen Size Variables
  int YMax = 0;
  int XMax = 0;

  // Status
  int YStatusPos = 0;
  int XStatusPos = 0;
  int YStatusSize = 2;
  int XStatusSize = -1;

  // Buttons
  int YButtonPos = 0;
  int XButtonPos = 0;
  int YButtonSize = 4;
  int XButtonSize = 8;

  // Debug
  int YDebugPos = -1;
  int XDebugPos = 0;
  int YDebugSize = 3;
  int XDebugSize = -1;

  // Timer
  int YTimerPos = -1;
  int XTimerPos = 0;
  int YTimerSize = 3;
  int XTimerSize = -1;

  // Color Picker
  int YCPickerPos = -1;
  int XCPickerPos = -1;
  int YCPickerSize = 3;
  int XCPickerSize = 6;

  // Tabs
  int YTabPos = -1;
  int XTabPos = 0;
  int YTabSize = 2;
  int XTabSize = 12;

  // Console
  int YConsolePos = -1;
  int XConsolePos = 0;
  int YConsoleSize = -1;
  int XConsoleSize = -1;

  // Player
  int YPlayerPos = -1;
  int XPlayerPos = 0;
  int YPlayerSize = -1;
  int XPlayerSize = -1;
  
  bool Player_Frame_Counter = false;
  int Player_Frame_Count = 0;

  // NCurses Window Variables
  string strBotLine;
  
  WINDOW * winStatus;
  WINDOW * winDebug;
  WINDOW * winTimer;
  WINDOW * winCPicker;
  WINDOW * winConsole;
  WINDOW * winPlayer;

  // Buttons
  Button btnButton1;
  Button btnButton2;
  Button btnButton3;
  Button btnButton4;
  Button btnButton5;
  Button btnButton6;
  Button btnButton7;

  Button btnCPicker_Red;
  Button btnCPicker_Green;
  Button btnCPicker_Blue;
  Button btnCPicker_Purple;
  Button btnCPicker_Yellow;
  Button btnCPicker_Cyan;
  Button btnCPicker_Orange;
  Button btnCPicker_Blank1;

  Button btnTab1;
  Button btnTab2;
  Button btnTab3;

  public:

  Button_Zone_Manager bzButtons;
  Button_Zone_Manager bzCPicker;
  Button_Zone_Manager bzTabs;

  void update_buttons()
  // Scan a button for changes and update its duplicate in the 
  //  button zone manager.
  {
    bzButtons.update_change_process(btnButton1);
    bzButtons.update_change_process(btnButton2);
    bzButtons.update_change_process(btnButton3);
    bzButtons.update_change_process(btnButton4);
    bzButtons.update_change_process(btnButton5);
    bzButtons.update_change_process(btnButton6);
    bzButtons.update_change_process(btnButton7);
  }

  void update_tabs()
  // Scan a button for changes and update its duplicate in the 
  //  button zone manager.
  {
    bzTabs.update_change_process(btnTab1);
    bzTabs.update_change_process(btnTab2);
    bzTabs.update_change_process(btnTab3);
  }

  void buttons_CPicker(system_data &sdSysData)
  // Define Color Picker buttons and load them to the 
  //  color picker button zone.
  {
    btnCPicker_Red.modify(1, "RED", "%r", 0, 1, C_WHITE_RED, 0);
    btnCPicker_Green.modify(2, "GREEN", "%g", 0, 1, C_WHITE_GREEN, 0);
    btnCPicker_Blue.modify(3, "BLUE", "%b", 0, 1, C_WHITE_BLUE, 0);
    btnCPicker_Purple.modify(4, "PURPLE", "%u", 0, 1, C_WHITE_PURPLE, 0);
    btnCPicker_Yellow.modify(5, "YELLOW", "%y", 0, 1, C_WHITE_YELLOW, 0);
    btnCPicker_Cyan.modify(6, "CYAN", "%c", 0, 1, C_WHITE_CYAN, 0);
    btnCPicker_Orange.modify(7, "ORANGE", "%n", 0, 1, C_WHITE_YELLOW, 0);
    btnCPicker_Blank1.modify(8, "WHITE", "%w", 0, 1, C_BLACK_WHITE, 0);
    
    bzCPicker.clear();
    bzCPicker.scan(btnCPicker_Red);
    bzCPicker.scan(btnCPicker_Green);
    bzCPicker.scan(btnCPicker_Blue);
    bzCPicker.scan(btnCPicker_Purple);
    bzCPicker.scan(btnCPicker_Yellow);
    bzCPicker.scan(btnCPicker_Cyan);
    bzCPicker.scan(btnCPicker_Orange);
    bzCPicker.scan(btnCPicker_Blank1);
  }

  void buttons_Tabs(system_data &sdSysData)
  // Define Tab buttons and load them to the 
  //  button zone.
  // Console Tab Buttons 
  {
    btnTab1.modify(1, "TABCONSOLE", "Console", 1, 2, C_WHITE_BLUE, 0);
    btnTab2.modify(2, "TABBLANKSCREEN", "Blank%Screen", 0, 2, C_WHITE_BLUE, 0);
    btnTab3.modify(3, "TABPLAYER", "Player", 0, 2, C_WHITE_BLUE, 0);
    
    bzTabs.clear();
    bzTabs.scan(btnTab1);
    bzTabs.scan(btnTab2);
    bzTabs.scan(btnTab3);
  }

  void buttons_menu_home(system_data &sdSysData)
  // Define control buttons and load them to the 
  //  button zone.
  // Main Buttons (Top)
  {
    btnButton1.modify(1, "TIMER", "%Start%Timer", 0, 0, C_WHITE_YELLOW, 0);
    btnButton2.modify(2, "", "", 0, -1, 6, 0);
    btnButton3.modify(3, "MENUOVERHEAD", "Over%Head%Lights", 0, 0, C_WHITE_YELLOW, 0);
    btnButton4.modify(4, "FLASH", "%Flash", 0, 0, C_WHITE_GREEN, 0);
    btnButton5.modify(5, "", "", 0, -1, 6, 0);
    btnButton6.modify(3, "CLEARANIMS", "%Clear%Anims", 0, 0, C_WHITE_GREEN, 0);
    btnButton7.modify(3, "MENUCONTROL", "%...", 0, 0, C_WHITE_BLUE, 0);

    bzButtons.clear();
    bzButtons.scan(btnButton1);
    bzButtons.scan(btnButton2);
    bzButtons.scan(btnButton3);
    bzButtons.scan(btnButton4);
    bzButtons.scan(btnButton5);
    bzButtons.scan(btnButton6);
    bzButtons.scan(btnButton7);
  }

  void buttons_menu_control(system_data &sdSysData)
  // Define control buttons and load them to the 
  //  button zone.
  // RasFLED settings
  {
    btnButton1.modify(1, "HAZARD","%HAZARD", 0, 0, C_WHITE_RED, 0);
    btnButton2.modify(2, "", "", 0, -1, 6, 0);
    btnButton3.modify(3, "DAYNIGHT","%Day%Night",int(sdSysData.booDay_On), 1, C_WHITE_YELLOW, 0);
    btnButton4.modify(4, "RUNNINGCOLOR", "Set%Running%Color", 0,- 0, C_WHITE_YELLOW, 0);
    btnButton5.modify(5, "", "", 0, -1, 6, 0);
    btnButton6.modify(3, "MENUSYSTEM","%SYSTEM", 0, 0, C_WHITE_BLUE, 0);
    btnButton7.modify(3, "MENUHOME", "%<--", 0, 0, C_WHITE_BLUE, 0);

    if (sdSysData.booDay_On == true)
    {
      btnButton3.PROP.LABEL = "%Day%Mode";
      btnButton3.PROP.VALUE = 1;
      btnButton3.CHANGED=true;
    }
    else
    {
      btnButton3.PROP.LABEL = "%Night%Mode";
      btnButton3.PROP.VALUE = 0;
      btnButton3.CHANGED=true;
    }

    bzButtons.clear();
    bzButtons.scan(btnButton1);
    bzButtons.scan(btnButton2);
    bzButtons.scan(btnButton3);
    bzButtons.scan(btnButton4);
    bzButtons.scan(btnButton5);
    bzButtons.scan(btnButton6);
    bzButtons.scan(btnButton7);
  }

  void buttons_menu_system(system_data &sdSysData)
  // Define control buttons and load them to the 
  //  button zone.
  // RasFLED advanced settings
  {
    btnButton1.modify(1, "EXIT", "%EXIT", 0, 0, C_WHITE_RED, 0);
    btnButton2.modify(2, "SHUTDOWN_NOW", "%SYSTEM%SHUTDOWN", 0, 0, C_WHITE_RED, 0);
    btnButton3.modify(3, "", "", 0, -1, 6, 0);
    btnButton4.modify(4, "DEBUG", "%DEBUG", 0, 0, C_WHITE_YELLOW, 0);
    btnButton5.modify(5, "", "", 0, -1, 6, 0);
    btnButton6.modify(3, "", "", 0, -1, 6, 0);
    btnButton7.modify(3, "MENUHOME", "%<--", 0, 0, C_WHITE_BLUE, 0);

    bzButtons.clear();
    bzButtons.scan(btnButton1);
    bzButtons.scan(btnButton2);
    bzButtons.scan(btnButton3);
    bzButtons.scan(btnButton4);
    bzButtons.scan(btnButton5);
    bzButtons.scan(btnButton6);
    bzButtons.scan(btnButton7);
  }

  void buttons_menu_overhead_color(system_data &sdSysData)
  // Define control buttons and load them to the 
  //  button zone.
  // Overhead activation and color picker.
  {
    btnButton1.modify(1, "", "", 0, -1, C_WHITE_RED, 0);
    btnButton2.modify(2, "OVERHEAD", "Over%Head%Lights", 0, 0, C_WHITE_GREEN, 0);
    btnButton3.modify(3, "CHOSECOLOR", "%Chose%Color", 0, 0, C_WHITE_YELLOW, 0);
    btnButton4.modify(4, "", "", 0, -1, C_WHITE_BLUE, 0);
    btnButton5.modify(5, "", "", 0, -1, 6, 0);
    btnButton6.modify(3, "", "", 0, -1, 6, 0);
    btnButton7.modify(3, "MENUHOME", "%<--", 0, 0, C_WHITE_BLUE, 0);

    bzButtons.clear();
    bzButtons.scan(btnButton1);
    bzButtons.scan(btnButton2);
    bzButtons.scan(btnButton3);
    bzButtons.scan(btnButton4);
    bzButtons.scan(btnButton5);
    bzButtons.scan(btnButton6);
    bzButtons.scan(btnButton7);
  }

  void init()
  // Initialize the main screen for first start.  
  {
    cbreak();   // do not buffer input until cr.
    noecho();   // do not echo back pressed characters

    keypad(stdscr, true);      // Keypad mode for reported mouse events as KEY_MOUSE.

    // Don't mask any mouse events
    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);

    printf("\033[?1003h\n");  // Makes the terminal report mouse movement events.

    if(has_colors() == true)
    // Set color pairs to defined integers.
    //  First color foreground. Second color background.
    {
      Supports_Color = true;
      start_color();

      init_pair(C_RED_BLACK, COLOR_RED, COLOR_BLACK);
      init_pair(C_YELLOW_BLACK, COLOR_YELLOW, COLOR_BLACK);
      init_pair(C_GREEN_BLACK, COLOR_GREEN, COLOR_BLACK);
      init_pair(C_BLUE_BLACK, COLOR_BLUE, COLOR_BLACK);
      init_pair(C_WHITE_RED, COLOR_WHITE, COLOR_RED);
      init_pair(C_WHITE_YELLOW, COLOR_WHITE, COLOR_YELLOW);
      init_pair(C_WHITE_GREEN, COLOR_WHITE, COLOR_GREEN);
      init_pair(C_WHITE_BLUE, COLOR_WHITE, COLOR_BLUE);
      init_pair(C_WHITE_PURPLE, COLOR_WHITE, COLOR_MAGENTA);
      init_pair(C_WHITE_CYAN, COLOR_WHITE, COLOR_CYAN);
      init_pair(C_WHITE_BLACK, COLOR_WHITE, COLOR_BLACK);
      init_pair(C_BLACK_WHITE, COLOR_BLACK, COLOR_WHITE);

      init_pair(C_BLACK_RED, COLOR_BLACK, COLOR_RED);
      init_pair(C_BLACK_YELLOW, COLOR_BLACK, COLOR_YELLOW);
      init_pair(C_BLACK_GREEN, COLOR_BLACK, COLOR_GREEN);
      init_pair(C_BLACK_BLUE, COLOR_BLACK, COLOR_BLUE);
      init_pair(C_BLACK_PURPLE, COLOR_BLACK, COLOR_MAGENTA);
      init_pair(C_BLACK_CYAN, COLOR_BLACK, COLOR_CYAN);
      init_pair(C_BLACK_BLACK, COLOR_BLACK, COLOR_BLACK);
    }
  }

  void set(system_data &sdSysData, ScreenStatus &ScrStat)
  // Set the screen and defines its contents for first run. 
  // Call after the screen init.
  {
    // Prep Control Buttons for program start.
    btnButton1.create(0, "", "", 0, 0, 0, 0);
    btnButton2.create(0, "", "", 0, 0, 0, 0);
    btnButton3.create(0, "", "", 0, 0, 0, 0);
    btnButton4.create(0, "", "", 0, 0, 0, 0);
    btnButton5.create(0, "", "", 0, 0, 0, 0);
    btnButton6.create(0, "", "", 0, 0, 0, 0);
    btnButton7.create(0, "", "", 0, 0, 0, 0);
    buttons_menu_home(sdSysData);

    // Prep Color Picker Buttons, even thought they 
    //  aren't displayed at start.
    btnCPicker_Red.create(0, "", "", 0, 0, 0, 0);
    btnCPicker_Green.create(0, "", "", 0, 0, 0, 0);
    btnCPicker_Blue.create(0, "", "", 0, 0, 0, 0);
    btnCPicker_Purple.create(0, "", "", 0, 0, 0, 0);
    btnCPicker_Yellow.create(0, "", "", 0, 0, 0, 0);
    btnCPicker_Cyan.create(0, "", "", 0, 0, 0, 0);
    btnCPicker_Orange.create(0, "", "", 0, 0, 0, 0);
    buttons_CPicker(sdSysData);

    // Prep Tab buttons for program first start
    btnTab1.create(0, "", "", 0, 0, 0, 0);
    btnTab2.create(0, "", "", 0, 0, 0, 0);
    btnTab3.create(0, "", "", 0, 0, 0, 0);
    buttons_Tabs(sdSysData);

    // Draw screen the entire screen.  reset is also 
    //  called when the screen is resized.  
    reset(ScrStat);
  }


  void reset(ScreenStatus &ScrStat)
  // Creates all windows on panel and sets all positions.
  //  To be called if panel sized changes or if windows are 
  //  opened or closed. 
  {
    // Clear the Screen
    clear();

    // Get Screen Size
    getmaxyx(stdscr, YMax, XMax);

    // Panel Setup
    //  Calculate Window Sizes and Start Positions progressively
    //  as the screen is drawn.

    // Screen split variables
    int YSplit = 0;
    int XSplit = 0;

    // Start first split at X button size
    XSplit = XMax - XButtonSize;

    // ---------------------------------------------------------------------------------------
    // Status Panel
    if (ScrStat.Window_Status == true)
    // Main Status Panel
    {
      // Calculate Size and Position
      YStatusPos = YStatusPos;
      XStatusPos = XStatusPos;
      YStatusSize = YStatusSize;
      XStatusSize = XSplit;

      // Build Window
      winStatus = newwin(YStatusSize, XStatusSize, YStatusPos, XStatusPos);
      
      // Set Y Split
      YSplit = YSplit + YStatusSize;

      // Status Window Border
      wborder(winStatus,' ',' ',' ',' ',' ',' ',' ',' ') ;
      
      // Create Status Screen
      wrefresh(winStatus);

      // Set window color
      wbkgd(winStatus, COLOR_PAIR(C_WHITE_BLUE));
    }

    // ---------------------------------------------------------------------------------------
    // Buttons
    if (ScrStat.Window_Buttons == true)
    // Control Buttons
    {
      int YButtonPos = 0;
      int XButtonPos = XMax - XButtonSize;

      // Prep Side Buttons
      btnButton1.move_resize((YButtonSize *0), XButtonPos, YButtonSize, XButtonSize);
      btnButton2.move_resize((YButtonSize *1), XButtonPos, YButtonSize, XButtonSize);
      btnButton3.move_resize((YButtonSize *2), XButtonPos, YButtonSize, XButtonSize);
      btnButton4.move_resize((YButtonSize *3), XButtonPos, YButtonSize, XButtonSize);
      btnButton5.move_resize((YButtonSize *4), XButtonPos, YButtonSize, XButtonSize);
      btnButton6.move_resize((YButtonSize *5), XButtonPos, YButtonSize, XButtonSize);
      btnButton7.move_resize((YButtonSize *6), XButtonPos, YButtonSize, XButtonSize);
      
      bzButtons.clear();
      bzButtons.scan(btnButton1);
      bzButtons.scan(btnButton2);
      bzButtons.scan(btnButton3);
      bzButtons.scan(btnButton4);
      bzButtons.scan(btnButton5);
      bzButtons.scan(btnButton6);
      bzButtons.scan(btnButton7);
    }

    // ---------------------------------------------------------------------------------------
    // Debug Panel
    if (ScrStat.Window_Debug == true)
    {
      // Calculate Size and Position
      YDebugPos = YSplit;
      XDebugPos = XDebugPos;
      YDebugSize = YDebugSize;
      XDebugSize = XSplit;

      // Build Window
      winDebug = newwin(YDebugSize, XDebugSize, YDebugPos, XDebugPos);
      
      // Set Y Split
      YSplit = YSplit + YDebugSize;

      // Debug Window Border
      wborder(winDebug,' ',' ',' ',' ',' ',' ',' ',' ') ;
      
      // Create Debug Screen
      wrefresh(winDebug);

      // Set window color
      wbkgd(winDebug, COLOR_PAIR(C_WHITE_RED));
    }

    // ---------------------------------------------------------------------------------------
    // Color Picker Panel
    if (ScrStat.Window_CPicker == true)
    {
      // Recreate XSplit Size
      XSplit = XSplit - XCPickerSize * 2;

      // Calculate Size and Position
      YCPickerPos = YSplit;
      XCPickerPos = XSplit;

      // Prep Side Buttons
      btnCPicker_Red.move_resize(YCPickerPos + (YCPickerSize *0), XCPickerPos + (XCPickerSize * 0), YCPickerSize, XCPickerSize);
      btnCPicker_Green.move_resize(YCPickerPos + (YCPickerSize *0), XCPickerPos + (XCPickerSize * 1), YCPickerSize, XCPickerSize);
      btnCPicker_Blue.move_resize(YCPickerPos + (YCPickerSize *1), XCPickerPos + (XCPickerSize * 0), YCPickerSize, XCPickerSize);
      btnCPicker_Purple.move_resize(YCPickerPos + (YCPickerSize *1), XCPickerPos + (XCPickerSize * 1), YCPickerSize, XCPickerSize);
      btnCPicker_Yellow.move_resize(YCPickerPos + (YCPickerSize *2), XCPickerPos + (XCPickerSize * 0), YCPickerSize, XCPickerSize);
      btnCPicker_Cyan.move_resize(YCPickerPos + (YCPickerSize *2), XCPickerPos + (XCPickerSize * 1), YCPickerSize, XCPickerSize);
      btnCPicker_Orange.move_resize(YCPickerPos + (YCPickerSize *3), XCPickerPos + (XCPickerSize * 0), YCPickerSize, XCPickerSize);
      btnCPicker_Blank1.move_resize(YCPickerPos + (YCPickerSize *3), XCPickerPos + (XCPickerSize * 1), YCPickerSize, XCPickerSize);
      
      bzCPicker.clear();
      bzCPicker.scan(btnCPicker_Red);
      bzCPicker.scan(btnCPicker_Green);
      bzCPicker.scan(btnCPicker_Blue);
      bzCPicker.scan(btnCPicker_Purple);
      bzCPicker.scan(btnCPicker_Yellow);
      bzCPicker.scan(btnCPicker_Cyan);
      bzCPicker.scan(btnCPicker_Orange);
      bzCPicker.scan(btnCPicker_Blank1);
    }

    // ---------------------------------------------------------------------------------------
    // Timer Panel
    if (ScrStat.Window_Timer == true)
    {
      // Calculate Size and Position
      YTimerPos = YSplit;
      XTimerPos = XTimerPos;
      YTimerSize = YTimerSize;
      XTimerSize = XSplit;

      // Build Window
      winTimer = newwin(YTimerSize, XTimerSize, YTimerPos, XTimerPos);
      
      // Set Y Split
      YSplit = YSplit + YTimerSize;

      // Timer Window Border
      wborder(winTimer,' ',' ',' ',' ',' ',' ',' ',' ') ;
      
      // Create Timer Screen
      wrefresh(winTimer);

      // Set window color
      // wbkgd(winTimer, COLOR_PAIR(5));  //  Set color in window.
    }

    // ---------------------------------------------------------------------------------------
    // Console Panel
    if (ScrStat.Window_Console == true)
    // Main Console Screen
    {
      // Calculate Size and Position
      YConsolePos = YSplit;
      XConsolePos = XConsolePos;
      YConsoleSize = YMax - YSplit - YTabSize;
      XConsoleSize =  XSplit;

      // Build Window
      winConsole = newwin(YConsoleSize, XConsoleSize, YConsolePos, XConsolePos);
      
      // Set Y Split
      YSplit = YSplit + YConsoleSize;

      // Console Window Border
      wborder(winConsole,' ',' ',' ','_',' ',' ',' ',' ') ;

      // Create Console Screen
      wrefresh(winConsole);

      // Set window color
      wbkgd(winConsole, COLOR_PAIR(0));

      // the bottom line of the console.
      strBotLine = "";
      strBotLine = strBotLine.append(XConsoleSize-1, '_');

    }

    // ---------------------------------------------------------------------------------------
    // Player Panel
    if (ScrStat.Window_Player == true)
    // Main Player Screen
    {
      // Calculate Size and Position
      YPlayerPos = YSplit;
      XPlayerPos = XPlayerPos;
      YPlayerSize = YMax - YSplit - YTabSize;
      XPlayerSize =  XSplit;

      // Build Window
      winPlayer = newwin(YPlayerSize, XPlayerSize, YPlayerPos, XPlayerPos);
      
      // Set Y Split
      YSplit = YSplit + YPlayerSize;

      // Player Window Border
      wborder(winPlayer,' ',' ',' ',' ',' ',' ',' ',' ') ;

      // Create Player Screen
      wrefresh(winPlayer);

      // Set window color
      wbkgd(winPlayer, COLOR_PAIR(0));

      // the bottom line of the Player.
      strBotLine = "";
      strBotLine = strBotLine.append(XPlayerSize-1, '_');
    }
    
    // ---------------------------------------------------------------------------------------
    // Tabs Panel
    if (ScrStat.Window_Tabs == true)
    {
      // Calculate Size and Position
      YSplit = YMax - YTabSize;

      YTabPos = YSplit;
      XTabPos = XTabPos;

      // Prep Tab Buttons
      btnTab1.move_resize(YTabPos + (YTabSize *0), XTabPos + (XTabSize * 0), YTabSize, XTabSize);
      btnTab2.move_resize(YTabPos + (YTabSize *0), XTabPos + (XTabSize * 1), YTabSize, XTabSize);
      btnTab3.move_resize(YTabPos + (YTabSize *0), XTabPos + (XTabSize * 2), YTabSize, XTabSize);

      bzTabs.clear();
      bzTabs.scan(btnTab1);
      bzTabs.scan(btnTab2);
      bzTabs.scan(btnTab3);

      // Set Y Split
      YSplit = YSplit + YTabSize;
    }

    // probably does something for the tty terminal.  probably should have 
    //  commented it when i reseached and wrote it.
    nodelay(stdscr, true);
  }
  // ---------------------------------------------------------------------------------------

  // ---------------------------------------------------------------------------------------
  void output_status(system_data &sdSysData, Keys &keywatch, ConsoleLineList &clou, ScreenStatus &ScrStat, TheMouse &mouse)
  // Displays command line input, status and door indicators
  {
    // Display Command Line
    if (keywatch.cmdPressed() == true || ScrStat.Needs_Refresh == true)
    {
      if (keywatch.cmdCleared() == true || ScrStat.Needs_Refresh == true)
      {
        // Blank out the line before redraw.
        wmove(winStatus, 0, 1);
        mvwprintw(winStatus, 0, 1, "CMD: __________");
      }
      mvwprintw(winStatus, 0, 1, "CMD: %s", keywatch.cmdRead().c_str());
    }

    //Display Door Statuses, highlighting values that are on (doors open)
    if (sdSysData.CONFIG.vSWITCH_PIN_MAP.at(0).value == true) {wattron(winStatus, A_REVERSE);}
    mvwprintw(winStatus, 1, 45, " D1 ");
    if (sdSysData.CONFIG.vSWITCH_PIN_MAP.at(0).value == true) {wattroff(winStatus, A_REVERSE);}
    
    if (sdSysData.CONFIG.vSWITCH_PIN_MAP.at(1).value == true) {wattron(winStatus, A_REVERSE);}
    mvwprintw(winStatus, 0, 45, " D2 ");
    if (sdSysData.CONFIG.vSWITCH_PIN_MAP.at(1).value == true) {wattroff(winStatus, A_REVERSE);}
    
    if (sdSysData.CONFIG.vSWITCH_PIN_MAP.at(2).value == true) {wattron(winStatus, A_REVERSE);}
    mvwprintw(winStatus, 1, 50, " D3 ");
    if (sdSysData.CONFIG.vSWITCH_PIN_MAP.at(2).value == true) {wattroff(winStatus, A_REVERSE);}

    if (sdSysData.CONFIG.vSWITCH_PIN_MAP.at(3).value == true) {wattron(winStatus, A_REVERSE);}
    mvwprintw(winStatus, 0, 50, " D4 ");
    if (sdSysData.CONFIG.vSWITCH_PIN_MAP.at(3).value == true) {wattroff(winStatus, A_REVERSE);}

    // Display Repeat Animations Enabled.  (Not Yet Implemented)
    mvwprintw(winStatus, 0, 18, "REPEAT");

    // Display Door Aware Toggle Enabled. (Not Yet Implemented)
    wattron(winStatus, A_REVERSE);
    mvwprintw(winStatus, 0, 26, "DOORAWARE");
    wattroff(winStatus, A_REVERSE);

    // Display Day or Night mode toggle.
    if(sdSysData.booDay_On == true)
    {
      //init_pair(1, COLOR_WHITE, COLOR_BLUE);
      //wattron(winStatus, COLOR_PAIR(1));
      wattron(winStatus, A_REVERSE);
      mvwprintw(winStatus, 0, 37, " DAY ");
      wattroff(winStatus, A_REVERSE);
      //wattroff(winStatus, COLOR_PAIR(1));
    }
    else
    {
      mvwprintw(winStatus, 0, 37, "NIGHT");      
    }

    // Screen Title
    wattron(winStatus, A_REVERSE);
    mvwprintw(winStatus, 0, XStatusSize - 7, " STATUS");
    wattroff(winStatus, A_REVERSE);

    // Commit all our changes to the status portion of the screen (winTop)
    wrefresh(winStatus);
  }

  // ---------------------------------------------------------------------------------------
  void output_debug2(system_data &sdSysData, Keys &keywatch, ConsoleLineList &clou, ScreenStatus &ScrStat, TheMouse &mouse)
  // Displays clock timings, event count, and mouse info.
  {
    string strRange = "";
    string strLevel = "";

    // Print Timings
    mvwprintw(winDebug, 0, 7, "Compute: %fms", sdSysData.fltCOMPUTETIME.data);
    mvwprintw(winDebug, 1, 7, "  Sleep: %fms", sdSysData.fltPREVSLEEPTIME.data);
    mvwprintw(winDebug, 2, 7, "  Cycle: %fms", sdSysData.fltCYCLETIME.data);
    // Not Very Usefule: mvwprintw(winDebug, 4, 47, "(m:%fms)", sdSysData.fltCYCLETIME.max);

    /*  -- Needs Removal
    if (sdSysData.booprintbuffer == true)
    {
      mvwprintw(winStatus, 4, 1, ":%s", sdSysData.strprintbuffer.c_str());
    }
    */

    //------------------------
    // Print LED Display Mode
    // Displaying LEDs selected to be displayed CYCLE selected.
    if (keywatch.get(KEYLEDTEST) == 1)
    {
      strRange = "Fi";
      strLevel = "ll";
    }
    else if (keywatch.get(KEYLEDDRCYCL) == 0)
    {
      strRange = "EA";
      strLevel = "  ";
    }
    else
    {
      strRange = "E" + to_string(keywatch.get(KEYLEDDRCYCL)-1);
      strLevel = to_string(sdSysData.t_group) + to_string(sdSysData.t_strip);
    }

    // Draw RANGE and UPPER OR LOWER VALUES selected.
    mvwprintw(winDebug, 0, 0, "RNG:%s", strRange.c_str());
    mvwprintw(winDebug, 1, 0, "LVL:%s", strLevel.c_str());
    //------------------------

    // Show Number of Events per Channel
    mvwprintw(winDebug, 1, 42, "%03d:D1", sdSysData.intCHANNEL_GROUP_EVENTS_COUNTS.at(0));
    mvwprintw(winDebug, 0, 42, "%03d:D2", sdSysData.intCHANNEL_GROUP_EVENTS_COUNTS.at(1));
    mvwprintw(winDebug, 1, 51, "D3:%03d", sdSysData.intCHANNEL_GROUP_EVENTS_COUNTS.at(2));
    mvwprintw(winDebug, 0, 51, "D4:%03d", sdSysData.intCHANNEL_GROUP_EVENTS_COUNTS.at(3));
    
    //------------------------
    //Mouse Position
    mvwprintw(winDebug, 1, XStatusSize - 14, "Mouse: %03d %03d",mouse.x(),mouse.y());

    //------------------------
    // Screen Title
    wattron(winDebug, A_REVERSE);
    mvwprintw(winDebug, 0, XDebugSize - 7, "   DIAG");
    wattroff(winDebug, A_REVERSE);

    wrefresh(winDebug);
  }

  // ---------------------------------------------------------------------------------------
  void output_timer(system_data &sdSysData, Keys &keywatch, ConsoleLineList &clou, ScreenStatus &ScrStat, TheMouse &mouse)
  // Displays first countdown timer.
  {
    long elaped_time = 0;
    unsigned long duration_time = 0;
    long remaining_time = 0;

    // Set window color
    wbkgd(winTimer, COLOR_PAIR(C_WHITE_GREEN));

    // Calculate
    duration_time = sdSysData.cdTIMER.duration();
    elaped_time = sdSysData.cdTIMER.elapsed_time(sdSysData.tmeCURRENT_FRAME_TIME);
    remaining_time = duration_time - elaped_time;

    // Display
    mvwprintw(winTimer, 1, 2, "Timer: %02d:%02d", millis_to_time_minutes(remaining_time), millis_to_time_seconds(remaining_time));
    mvwprintw(winTimer, 1, 15, "[%s]", progress_bar(15, duration_time, duration_time-elaped_time).c_str());

    //------------------------
    // Screen Title
    wattron(winTimer, A_REVERSE);
    mvwprintw(winTimer, 0, XTimerSize - 7, "  TIMER");
    wattroff(winTimer, A_REVERSE);

    wrefresh(winTimer);
  }
  
  // ---------------------------------------------------------------------------------------
  void printout(ConsoleLineList &clou, ScreenStatus &ScrStat)
  // Displays console of commands ran, events starting and stoping, and other info.
  //  If console is on another tty through tty over ethernet or serial then a low 
  //    bandwith version will need to created.  Or, I put the console into its own 
  //    thread.  Whichever is necessary to develop or learn first.
  {
    // Figurout the size of the console.
    ConsoleLine line;

    int yCurPos = 0;

    if(clou.avail() == true || ScrStat.Needs_Refresh == true)
    {
      for( int y=0; y < YConsoleSize; y++ )
      {
        // line position on screen or window
        yCurPos = YConsoleSize -y -1;

        // get next line to print from the line history
        line = clou.get_line_to_print(y);

        // print the line to the screen
        wmove(winConsole, yCurPos, 0);  //move cursor to next line to print or clear.
        wclrtoeol(winConsole);            // clear line befor printing to it.
        mvwprintw(winConsole, yCurPos, 0, "%s", line.strLine.c_str());  //print line.       
      }

      // Screen Title
      wattron(winConsole, A_REVERSE);
      mvwprintw(winConsole, 0, XConsoleSize - 7, "CONSOLE");
      wattroff(winConsole, A_REVERSE);

      // Refresh the window.
      wrefresh(winConsole);
    }
  }
  // ---------------------------------------------------------------------------------------
  void the_player(ConsoleLineList &clou, ScreenStatus &ScrStat)
  // Shows the Player Window
  {
    int yCurPos = 0;

    // Screen Title
    /*
    wattron(winPlayer, A_REVERSE);
    mvwprintw(winPlayer, 0, XPlayerSize - 7, " PLAYER");
    wattroff(winPlayer, A_REVERSE);
    */

    // Refresh the window.
    // wrefresh(winPlayer);
    
  }

  void window_player_draw_frame(PLAYER_FRAME &qframe)
  {

    for(int line=0; line < qframe.LINES.size(); line++)
    {
      /*
      wmove(winPlayer, line, 0);  //move cursor to next line to print or clear.
      wclrtoeol(winPlayer);            // clear line befor printing to it.
      mvwprintw(winPlayer, line, 0, "%s", qframe.LINES.front().c_str());
      qframe.LINES.pop_front();
      */

      wmove(winPlayer, (line + (YPlayerSize/2) - (qframe.HEIGHT/2)), ((XPlayerSize/2) - (qframe.WIDTH/2)));  //move cursor to next line to print or clear.
      wclrtoeol(winPlayer);            // clear line befor printing to it.
      mvwprintw(winPlayer, line + (YPlayerSize/2) - (qframe.HEIGHT/2), ((XPlayerSize/2) - (qframe.WIDTH/2)), "%s", qframe.LINES[line].c_str());
    }
    qframe.LINES.clear();

    if(Player_Frame_Counter == true)
    {
      Player_Frame_Count++;
      mvwprintw(winPlayer, 0, 0, "%08d", Player_Frame_Count);
    }
    wrefresh(winPlayer);
    refresh();

  }
  // ---------------------------------------------------------------------------------------

  // ---------------------------------------------------------------------------------------
  void buttons(system_data &sdSysData, ScreenStatus &ScrStat, Button_Zone_Manager &button_manager)
  // Draw and manage button window.
  {
    btnButton1.draw(ScrStat.Needs_Refresh);
    btnButton2.draw(ScrStat.Needs_Refresh);
    btnButton3.draw(ScrStat.Needs_Refresh);
    btnButton4.draw(ScrStat.Needs_Refresh);
    btnButton5.draw(ScrStat.Needs_Refresh);
    btnButton6.draw(ScrStat.Needs_Refresh);
    btnButton7.draw(ScrStat.Needs_Refresh);
  }

  void cpicker(system_data &sdSysData, ScreenStatus &ScrStat, Button_Zone_Manager &button_manager)
  // Draw and manage Color Picker window.
  {
    btnCPicker_Red.draw(ScrStat.Needs_Refresh);
    btnCPicker_Green.draw(ScrStat.Needs_Refresh);
    btnCPicker_Blue.draw(ScrStat.Needs_Refresh);
    btnCPicker_Purple.draw(ScrStat.Needs_Refresh);
    btnCPicker_Yellow.draw(ScrStat.Needs_Refresh);
    btnCPicker_Cyan.draw(ScrStat.Needs_Refresh);
    btnCPicker_Orange.draw(ScrStat.Needs_Refresh);
    btnCPicker_Blank1.draw(ScrStat.Needs_Refresh);
  }

    
  void tabs(system_data &sdSysData, ScreenStatus &ScrStat, Button_Zone_Manager &button_manager)
  // Draw Tab buttons.
  {
    btnTab1.draw(ScrStat.Needs_Refresh);
    btnTab2.draw(ScrStat.Needs_Refresh);
    btnTab3.draw(ScrStat.Needs_Refresh);
  }
  // ---------------------------------------------------------------------------------------
  
  // ---------------------------------------------------------------------------------------
  // Main screen routine.
  // Draw the console, starting with status window, then whatever windows set to true.

  void output(system_data &sdSysData, Keys &keywatch, ConsoleLineList &clou, ScreenStatus &ScrStat, TheMouse &mouse)
  {
    // Run any routines that may cause the screen to need to be refreshed.

    if (sdSysData.cdTIMER.is_active() == true)
    // Check for Timer Window
    {
      ScrStat.Window_Timer_On();
    }
    else
    {
      ScrStat.Window_Timer_Off();
    }

    // ---------------------------------------------------------------------------------------
    // Check to see if the screen need to be rebuilt
    if (ScrStat.Needs_Refresh == true)
    {
      reset(ScrStat);
    }

    // ---------------------------------------------------------------------------------------
    // Draw the windows on the screen

    // Draw Status window.
    if (ScrStat.Window_Status == true)
    {
      output_status(sdSysData, keywatch, clou, ScrStat, mouse);
    }

    // Draw buttons on buttons window.
    if (ScrStat.Window_Buttons == true)
    {
      buttons(sdSysData, ScrStat, bzButtons);
    }

    // Draw Color Picker window.
    if (ScrStat.Window_CPicker == true)
    {
      cpicker(sdSysData, ScrStat, bzButtons);
    }

    // Draw Debug window.
    if (ScrStat.Window_Debug == true)
    {
      output_debug2(sdSysData, keywatch, clou, ScrStat, mouse);
    }

    // Draw Timer window.
    if (ScrStat.Window_Timer == true)
    {
      output_timer(sdSysData, keywatch, clou, ScrStat, mouse);
    }

    // Draw Tabs.
    if (ScrStat.Window_Tabs == true)
    {
      tabs(sdSysData, ScrStat, bzButtons);
    }

    // Draw Console window.
    if (ScrStat.Window_Console == true)
    {
      printout(clou, ScrStat);
    }

    // Draw Player window.
    if (ScrStat.Window_Player == true)
    {
      the_player(clou, ScrStat);
    }

    // ---------------------------------------------------------------------------------------
    // Draw all changes to the screen.
    // Clear Refresh varibles.
    refresh();
    ScrStat.Needs_Refresh = false;
  }
};



#endif