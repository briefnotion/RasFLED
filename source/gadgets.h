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

#include "aircraft_coordinator.h"

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
      mvwprintw(winTitle, 0, 0, right_justify(PROP.SIZE, PROP.LABEL).c_str());
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

  void clear()
  {
    LINES.clear();
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

  // DEBUG_COUNTER
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
        wmove(winText_Box, yCurPos, 0);  //move cursor to next line to print or clear.
        wclrtoeol(winText_Box);            // clear line befor printing to it.

        // If line doesnt fit, put ">>" on the end of whats visible.
        if (line.strLine.size() > PROP.SIZEX)
        {
          string truncated_line = line.strLine.substr(0, PROP.SIZEX -2) + ">>";
          mvwprintw(winText_Box, yCurPos, 0, "%s", truncated_line.c_str());  //print line.
        }
        else
        {
          mvwprintw(winText_Box, yCurPos, 0, "%s", line.strLine.c_str());  //print line.
        }
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

  void clear_text()
  {
    PROP.LINES.clear();
  }
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
    bool UPDATED = false;
  };

  WINDOW * ADS_B_List_Box;

  // DEBUG_COUNTER
  int Counter = 0;

  deque<AIRCRAFT_INDEX_INFORMATION> AIRCRAFT_INDEX_LIST;

  
  bool IS_ACTIVE = false;

  // Types:
  // -1 - Hidden
  //  0 - Read Only

  private:

  int get_first_empty_pos()
  {
    int return_int = -1;
    for(int x=0; (x < AIRCRAFT_INDEX_LIST.size()) && (return_int == -1); x++)
    {
      if(AIRCRAFT_INDEX_LIST[x].HEX == "")
      {
        return_int = x;
      }
    }
    return return_int;
  }

  int find_HEX(string Hex)
  {
    int return_int = -1;
    for(int x=0; (x < AIRCRAFT_INDEX_LIST.size()) && (return_int == -1); x++)
    {
      if(AIRCRAFT_INDEX_LIST[x].HEX == Hex)
      {
        return_int = x;
      }
    }
    return return_int;
  }
  
  void sort_index()
  {
    // Clear the Updated Flag
    for(int x=0; x < AIRCRAFT_INDEX_LIST.size(); x++)
    {
      AIRCRAFT_INDEX_LIST[x].UPDATED = false;
    }

    // Populate the Index
    for(int x=0; x < PROP.VALUE.AIRCRAFTS.size(); x++)
    {
      // Check list to see if aircraft is in it
      int pos = find_HEX(PROP.VALUE.AIRCRAFTS[x].HEX.get_str_value());
      if (pos == -1)
      // Add to list if not in list.
      {
        // Find first empty position
        int first_empty = get_first_empty_pos();

        if(first_empty == -1)
        // No empty positions.
        //  Add to end of list.
        {
          AIRCRAFT_INDEX_INFORMATION tmp_index;
        
          tmp_index.POSITION = x;
          tmp_index.HEX = PROP.VALUE.AIRCRAFTS[x].HEX.get_str_value();
          tmp_index.DATA_COUNT = PROP.VALUE.AIRCRAFTS[x].data_count();
          tmp_index.UPDATED = true;

          AIRCRAFT_INDEX_LIST.push_back(tmp_index);
        }
        else
        // Add item to empty position.        // Add to first available position
        {
          AIRCRAFT_INDEX_LIST[first_empty].POSITION = x;
          AIRCRAFT_INDEX_LIST[first_empty].HEX = PROP.VALUE.AIRCRAFTS[x].HEX.get_str_value();
          AIRCRAFT_INDEX_LIST[first_empty].DATA_COUNT = PROP.VALUE.AIRCRAFTS[x].data_count();
          AIRCRAFT_INDEX_LIST[first_empty].UPDATED = true;
        }
      }
      else
      // Update List entry if already available
      {
        AIRCRAFT_INDEX_LIST[pos].POSITION = x;
        AIRCRAFT_INDEX_LIST[pos].DATA_COUNT = PROP.VALUE.AIRCRAFTS[x].data_count();
        AIRCRAFT_INDEX_LIST[pos].UPDATED = true;
      }
    }

    // Go through list again and mark non updated with empty.
    for(int x=0; x < AIRCRAFT_INDEX_LIST.size(); x++)
    {
      if(AIRCRAFT_INDEX_LIST[x].UPDATED == false)
      {
        AIRCRAFT_INDEX_LIST[x].HEX = "";
      }
    }
    
    /*
    // Move active entrys that are off screen up on list.
    for(int x=0; x < AIRCRAFT_INDEX_LIST.size(); x++)
    {
      if (AIRCRAFT_INDEX_LIST[x].POSITION > PROP.SIZEY)
      {
        // Search for any empty pos.
        bool pos_found = false;

        int first_empty = get_first_empty_pos();
        if(first_empty >= 0 && )

        
        for(int y=0; y < AIRCRAFT_INDEX_LIST.size() && pos_found == false; y++)
        {
          if(AIRCRAFT_INDEX_LIST[y].POSITION < PROP.SIZEY && AIRCRAFT_INDEX_LIST[y].HEX == "")
          {
            // swap positions
            int tmppos = AIRCRAFT_INDEX_LIST[y].POSITION;
            AIRCRAFT_INDEX_LIST[y].POSITION = AIRCRAFT_INDEX_LIST[x].POSITION;
            AIRCRAFT_INDEX_LIST[x].POSITION = tmppos;
            pos_found = true;
          }
        }
      }
    }
    */
  }

  int color_range(float Value, int Magenta, int Red, int Yellow, int Green, int Blue)
  // Non zero or mid level green.
  { 
    // 1 - Range Level
    // Magenta  Red  Yellow  Green  Blue  Cyan

    if (abs(Value) <= Magenta)
    {
      return COLOR_MAGENTA;
    }
    else if(abs(Value) <= Red)
    {
      return COLOR_RED;
    }
    else if(abs(Value) <= Yellow)
    {
      return COLOR_YELLOW;
    }
    else if(abs(Value) <= Green)
    {
      return COLOR_GREEN;
    }
    else if(abs(Value) <= Blue)
    {
      return COLOR_BLUE;
    }
    else
    {
      return COLOR_CYAN;
    }
  }
  
  int color_range(int Value, int Magenta, int Red, int Yellow, int Green, int Blue)
  {
    return color_range((float)Value, Magenta, Red, Yellow, Green, Blue);
  }

  //int color_scale(float Value, int Magenta, int Red, int Yellow, int Green, int Blue)
  int color_scale(float Value, int Green, int Yellow, int Red, int Magenta, int Blue)
  // zero level green.
  { 
    // 2 - Scale Level
    // Green  Yellow  Red  Magenta  Blue  Cyan
    
    if (abs(Value) <= Green)
    {
      return COLOR_GREEN;
    }
    else if(abs(Value) <= Yellow)
    {
      return COLOR_YELLOW;
    }
    else if(abs(Value) <= Red)
    {
      return COLOR_RED;
    }
    else if(abs(Value) <= Magenta)
    {
      return COLOR_MAGENTA;
    }
    else if(abs(Value) <= Blue)
    {
      return COLOR_BLUE;
    }
    else
    {
      return COLOR_CYAN;
    }
  }

  int color_scale(int Value, int Green, int Yellow, int Red, int Magenta, int Blue)
  {
    return color_scale((float)Value, Green, Yellow, Red, Magenta, Blue);
  }

  void clear_line(int &yCurPos, int &xCurPos)
  // Clear window line at y Cursor Pos and resets x Cursor Pos to 0.
  {
    wmove(ADS_B_List_Box, yCurPos, 0);  //move cursor to next line to print or clear.
    wclrtoeol(ADS_B_List_Box);            // clear line befor printing to it.
    xCurPos = 0;
  }

  void print_to_line(int &yCurPos, int &xCurPos, int Size, string Text, int Color_Pair)
  {
    
    // Turn On Color
    wattron(ADS_B_List_Box, COLOR_PAIR(Color_Pair));

    // Print Line
    mvwprintw(ADS_B_List_Box, yCurPos, xCurPos, "%s", Text.c_str());

    // Turn Off Color
    wattroff(ADS_B_List_Box, COLOR_PAIR(Color_Pair));

    xCurPos = xCurPos + Size;
  }

  void dsp_text(int &yCurPos, int &xCurPos, int Size, STRING_STRING &Text, int Text_Color, bool Inverse_Colors, int Color_Value, 
                  int Color_Scale_Type, int Level_0, int Level_1, int Level_2, int Level_3, int Level_4)
  {
    int color_pair = 0;
    int background_color = 0;

    string display_text = "";

    if(Text.conversion_success() == true)
    {
      if (Color_Scale_Type == 0)
      {
        background_color = COLOR_GREEN;
      }
      else if (Color_Scale_Type == 1)
      {
        background_color = color_range(Color_Value, Level_0, Level_1, Level_2, Level_3, Level_4);
      }
      else // Color_Scale_Type == 2
      {
        background_color = color_scale(Color_Value, Level_0, Level_1, Level_2, Level_3, Level_4);
      }
    }
    else
    {
      background_color = COLOR_GREEN;
    }

    if(Inverse_Colors == false)
    {
      color_pair = CRT_get_color_pair(background_color, Text_Color);
    }
    else
    {
      color_pair = CRT_get_color_pair(Text_Color, background_color);
    }

    // Turn On Color
    wattron(ADS_B_List_Box, COLOR_PAIR(color_pair));

    // Print Line
    if(Text.conversion_success() == false || Text.get_str_value() == "")
    {
      display_text = right_justify(Size, "");
    }
    else
    {
      display_text = right_justify(Size, Text.get_str_value());
    }

    mvwprintw(ADS_B_List_Box, yCurPos, xCurPos, "%s", display_text.c_str());

    // Turn Off Color
    wattroff(ADS_B_List_Box, COLOR_PAIR(color_pair));

    xCurPos = xCurPos + Size;
  }

  void dsp_intg(int &yCurPos, int &xCurPos, int Size, STRING_INT &Text, int Text_Color, bool Inverse_Colors, 
                  int Color_Scale_Type, int Level_0, int Level_1, int Level_2, int Level_3, int Level_4)

  // Scale Types:
  //  0 = off;
  //  1 = Range   - Non Zero Green
  //  2 = Scaler  - Zero Green
  {
    int color_pair = 0;
    int background_color = 0;

    string display_text = "";

    if(Text.conversion_success() == true)
    {
      if (Color_Scale_Type == 0)
      {
        background_color = COLOR_GREEN;
      }
      else if (Color_Scale_Type == 1)
      {
        background_color = color_range(Text.get_int_value(), Level_0, Level_1, Level_2, Level_3, Level_4);
      }
      else // Color_Scale_Type == 2
      {
        background_color = color_scale(Text.get_int_value(), Level_0, Level_1, Level_2, Level_3, Level_4);
      }
    }
    else
    {
      if(Text.get_str_value() == "")
      {
        background_color = COLOR_GREEN;
      }
      else
      {
        background_color = COLOR_RED;
      }
    }

    if(Inverse_Colors == false)
    {
      color_pair = CRT_get_color_pair(background_color, Text_Color);
    }
    else
    {
      color_pair = CRT_get_color_pair(Text_Color, background_color);
    }

    // Turn On Color
    wattron(ADS_B_List_Box, COLOR_PAIR(color_pair));

    // Print Line
    if(Text.conversion_success() == false || Text.get_str_value() == "")
    {
      display_text = right_justify(Size, Text.get_str_value());
    }
    else
    {
      display_text = right_justify(Size, Text.get_str_value());
    }

    mvwprintw(ADS_B_List_Box, yCurPos, xCurPos, "%s", display_text.c_str());
    
    // Turn Off Color
    wattroff(ADS_B_List_Box, COLOR_PAIR(color_pair));

    xCurPos = xCurPos + Size;
  }

  void dsp_floa(int &yCurPos, int &xCurPos, int Size, STRING_FLOAT &Text, int Text_Color, bool Inverse_Colors, 
                  int Color_Scale_Type, int Level_0, int Level_1, int Level_2, int Level_3, int Level_4)
  // Scale Types:
  //  0 = off;
  //  1 = Range   - Non Zero Green
  //  2 = Scaler  - Zero Green
  {
    int color_pair = 0;
    int background_color = 0;

    string display_text = "";

    if(Text.conversion_success() == true)
    {
      if (Color_Scale_Type == 0)
      {
        background_color = COLOR_GREEN;
      }
      else if (Color_Scale_Type == 1)
      {
        background_color = color_range(Text.get_float_value(), Level_0, Level_1, Level_2, Level_3, Level_4);
      }
      else // Color_Scale_Type == 2
      {
        background_color = color_scale(Text.get_float_value(), Level_0, Level_1, Level_2, Level_3, Level_4);
      }
    }
    else
    {
      if(Text.get_str_value() == "")
      {
        background_color = COLOR_GREEN;
      }
      else
      {
        background_color = COLOR_RED;
      }
    }

    if(Inverse_Colors == false)
    {
      color_pair = CRT_get_color_pair(background_color, Text_Color);
    }
    else
    {
      color_pair = CRT_get_color_pair(Text_Color, background_color);
    }

    // Turn On Color
    wattron(ADS_B_List_Box, COLOR_PAIR(color_pair));

    // Print Line
    if(Text.conversion_success() == false || Text.get_str_value() == "")
    {
      display_text = right_justify(Size, Text.get_str_value());
    }
    else
    {
      display_text = right_justify(Size, Text.get_str_value());
    }

    mvwprintw(ADS_B_List_Box, yCurPos, xCurPos, "%s", display_text.c_str());

    // Turn Off Color
    wattroff(ADS_B_List_Box, COLOR_PAIR(color_pair));

    xCurPos = xCurPos + Size;
  }

  public:

  ADS_B_List_Box_Properties PROP;  

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

    ADS_B_List_Box = newwin(PROP.SIZEY, PROP.SIZEX, PROP.POSY, PROP.POSX);

    bool CHANGED = true;
  }

  void move_resize(int posY, int posX, int sizeY, int sizeX)
  // Redefine position and size.
  {
    PROP.POSX = posX;
    PROP.POSY = posY;
    PROP.SIZEX = sizeX;
    PROP.SIZEY = sizeY;

    ADS_B_List_Box = newwin(PROP.SIZEY, PROP.SIZEX, PROP.POSY, PROP.POSX);

    refresh();

    wborder(ADS_B_List_Box,'|','|','-','-','+','+','+','+') ;

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
      int yCurPos = 0;
      int xCurPos = 0;

      int space_size = 0;

      string tmp_line = "";
      STRING_STRING blank_text;

      int color_pair = 0;
      int text_color = COLOR_WHITE;
      bool inverse_colors = false;

      if(IS_ACTIVE == true)
      {
        tmp_line = "Messages: " + PROP.VALUE.MESSAGES.get_str_value() + "   Now: " + PROP.VALUE.NOW.get_str_value() + 
                    "   Aircraft: " + to_string(PROP.VALUE.AIRCRAFTS.size()) + 
                    "   Positioned: " + to_string(PROP.VALUE.POSITIONED_AIRCRAFT)
                    ;
        
        wattron(ADS_B_List_Box, COLOR_PAIR(CRT_get_color_pair(COLOR_BLUE, COLOR_WHITE)));

        wmove(ADS_B_List_Box, yCurPos, 0);  //move cursor to next line to print or clear.
        wclrtoeol(ADS_B_List_Box);            // clear line befor printing to it.
        mvwprintw(ADS_B_List_Box, yCurPos, 0, "%s", left_justify(PROP.SIZEX, tmp_line).c_str());
        yCurPos++;
        
        //Screen.tbads_b_Data.add_line(tmeCurrentMillis, "");

        // Calculate Space Size
        space_size = PROP.SIZEX - 75;
        if(space_size < 0)
        {
          space_size = 0;
        }

        // Print Header Line
        clear_line(yCurPos, xCurPos);
        print_to_line(yCurPos, xCurPos, 6, right_justify(6, "SWK"), CRT_get_color_pair(COLOR_BLUE, COLOR_WHITE));
        print_to_line(yCurPos, xCurPos, 9, right_justify(9, "FLIGHT"), CRT_get_color_pair(COLOR_BLUE, COLOR_WHITE));

        print_to_line(yCurPos, xCurPos, 3, right_justify(3, ""), CRT_get_color_pair(COLOR_BLUE, COLOR_WHITE));

        print_to_line(yCurPos, xCurPos, 8, right_justify(8, "G SPEED"), CRT_get_color_pair(COLOR_BLUE, COLOR_WHITE));
        print_to_line(yCurPos, xCurPos, 8, right_justify(8, "ALT"), CRT_get_color_pair(COLOR_BLUE, COLOR_WHITE));
        print_to_line(yCurPos, xCurPos, 7, right_justify(7, "V RT"), CRT_get_color_pair(COLOR_BLUE, COLOR_WHITE));
        print_to_line(yCurPos, xCurPos, 7, right_justify(7, "TRACK"), CRT_get_color_pair(COLOR_BLUE, COLOR_WHITE));

        print_to_line(yCurPos, xCurPos, space_size, right_justify(space_size, ""), CRT_get_color_pair(COLOR_BLUE, COLOR_WHITE));

        print_to_line(yCurPos, xCurPos, 8, right_justify(8, "SN POS"), CRT_get_color_pair(COLOR_BLUE, COLOR_WHITE));
        print_to_line(yCurPos, xCurPos, 6, right_justify(6, "MSGS"), CRT_get_color_pair(COLOR_BLUE, COLOR_WHITE));
        print_to_line(yCurPos, xCurPos, 6, right_justify(6, "SEEN"), CRT_get_color_pair(COLOR_BLUE, COLOR_WHITE));
        print_to_line(yCurPos, xCurPos, 7, right_justify(7, "RSSI"), CRT_get_color_pair(COLOR_BLUE, COLOR_WHITE));
        
        wattroff(ADS_B_List_Box, COLOR_PAIR(CRT_get_color_pair(COLOR_BLUE, COLOR_WHITE)));

        yCurPos++;

        //----------------

        // Display Aircraft data in the order of the index.
        for (int y = 0; y < AIRCRAFT_INDEX_LIST.size() &&
                    yCurPos < PROP.SIZEY; y++)
        {
          AIRCRAFT display_aircraft;

          if(AIRCRAFT_INDEX_LIST[y].HEX != "")
          {
            display_aircraft = PROP.VALUE.AIRCRAFTS[AIRCRAFT_INDEX_LIST[y].POSITION];
          }

          // Determine Color
          if(display_aircraft.data_count() >0)
          {
            if(display_aircraft.POSITION.LATITUDE.conversion_success() == true && 
                display_aircraft.POSITION.LONGITUDE.conversion_success() == true)
              {
                text_color = COLOR_WHITE;
                inverse_colors = false;
              }
              else
              {
                text_color = COLOR_BLACK;
                inverse_colors = false;
              }
          }
          else
          {
            text_color = COLOR_BLACK;
            inverse_colors = true;
          }

          // 1 - Range Level
          // Magenta  Red  Yellow  Green  Blue  Cyan

          // 2 - Scale Level
          // Green  Yellow  Red  Magenta  Blue  Cyan
        
          // Print Aircraft Info Line
          clear_line(yCurPos, xCurPos);
          dsp_intg(yCurPos, xCurPos, 6, display_aircraft.SQUAWK, text_color, inverse_colors, 0, 0, 0, 0, 0, 0);
          dsp_text(yCurPos, xCurPos, 9, display_aircraft.FLIGHT, text_color, inverse_colors, 1, 2, 1, 2, 3, 4, 5);

          dsp_text(yCurPos, xCurPos, 3, blank_text, text_color, inverse_colors, 1, 2, 1, 2, 3, 4, 5);

          dsp_floa(yCurPos, xCurPos, 8, display_aircraft.SPEED, text_color, inverse_colors, 1, 60, 80, 100, 250, 600);
          dsp_intg(yCurPos, xCurPos, 8, display_aircraft.ALTITUDE, text_color, inverse_colors, 1, 50, 500, 3000, 12000, 40000);
          dsp_intg(yCurPos, xCurPos, 7, display_aircraft.VERT_RATE, text_color, inverse_colors, 2, 100, 1200, 3000, 4000, 5000);
          dsp_floa(yCurPos, xCurPos, 7, display_aircraft.TRACK, text_color, inverse_colors, 0, 0, 0, 0, 0, 0);

          dsp_text(yCurPos, xCurPos, space_size, blank_text, text_color, inverse_colors, 1, 2, 1, 2, 3, 4, 5);
          
          dsp_floa(yCurPos, xCurPos, 8, display_aircraft.SEEN_POS, text_color, inverse_colors, 2, 4, 10, 290, 299, 0);
          dsp_intg(yCurPos, xCurPos, 6, display_aircraft.MESSAGES, text_color, inverse_colors, 2, 100, 5000, 12000, 20000, 40000);
          dsp_floa(yCurPos, xCurPos, 6, display_aircraft.SEEN, text_color, inverse_colors, 2, 10, 290, 299, 0, 0);
          dsp_floa(yCurPos, xCurPos, 7, display_aircraft.RSSI, text_color, inverse_colors, 2, 10, 30, 32, 34, 36);

          if(display_aircraft.alert() == true)
          {
            for (int alerts_pos = 0; alerts_pos < display_aircraft.ALERT_LIST.size(); alerts_pos++)
            {
              if (yCurPos < PROP.SIZEY)
              {
                yCurPos++;
                clear_line(yCurPos, xCurPos);
                print_to_line(yCurPos, xCurPos, PROP.SIZEX, left_justify(PROP.SIZEX, display_aircraft.ALERT_LIST[alerts_pos].c_str()), CRT_get_color_pair(COLOR_RED, COLOR_WHITE));
              }
            }
          }

          yCurPos++;
        }
      }
      else  // Not Active
      {
        //tmp_line = "  ADS-B System Not Active";
        
        //wattron(ADS_B_List_Box, COLOR_PAIR(CRT_get_color_pair(COLOR_YELLOW, COLOR_WHITE)));

        clear_line(yCurPos, xCurPos);
        print_to_line(yCurPos, xCurPos, PROP.SIZEX, left_justify(PROP.SIZEX, ""), CRT_get_color_pair(COLOR_YELLOW, COLOR_WHITE));

        yCurPos++;
        clear_line(yCurPos, xCurPos);
        print_to_line(yCurPos, xCurPos, PROP.SIZEX, left_justify(PROP.SIZEX, "  ADS-B System Not Active"), CRT_get_color_pair(COLOR_YELLOW, COLOR_WHITE));
        
        yCurPos++;
        clear_line(yCurPos, xCurPos);
        print_to_line(yCurPos, xCurPos, PROP.SIZEX, left_justify(PROP.SIZEX, ""), CRT_get_color_pair(COLOR_YELLOW, COLOR_WHITE));

        //wattroff(ADS_B_List_Box, COLOR_PAIR(CRT_get_color_pair(COLOR_YELLOW, COLOR_WHITE)));
        yCurPos++;
      }

      //----------------

      // Clear remaining part of screen
      if (yCurPos < PROP.SIZEY)
      {
        for(int y = yCurPos; y < PROP.SIZEY; y++)
        {
          wmove(ADS_B_List_Box, yCurPos, 0);  //move cursor to next line to print or clear.
          wclrtoeol(ADS_B_List_Box);            // clear line befor printing to it.
          yCurPos++;
        }
      }
    

      PROP.CHANGED = false;
      
      wrefresh(ADS_B_List_Box);
    }
  }

  void update(system_data &sdSysData)
  {
    // Get new list of Aircraft.
    PROP.VALUE = sdSysData.AIRCRAFT_COORD.DATA;
    IS_ACTIVE = sdSysData.AIRCRAFT_COORD.is_active();

    // Prepare list to display.
    sort_index();

    sdSysData.AIRCRAFT_COORD.DATA.CHANGED = false;

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

  void draw(bool Refresh, unsigned long tmeFrame_Time)
  // Draw the button on the screen if the value has changed or if  
  //  the Refresh parameter is true.
  {
    /*
    if (PROP.CLEAR == true)
    {
      werase(winButton);
      wrefresh(winButton);
      PROP.CLEAR = false;
    }
    */

    if (BUTTON_PRESSED.blip_moved(tmeFrame_Time) == true)
    {
      Refresh = true;
    }

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
      if (PROP.ENABLED == true && (PROP.TYPE == 0 || PROP.TYPE == 1 || PROP.TYPE == 2))
      {

        // Start by setting button color.
        wbkgd(winButton, COLOR_PAIR(PROP.COLOR));
        
        // Top Sides and Bottom
        top = " " + top.append(PROP.SIZEX -2, ' ') + " ";
        mid = " " + mid.append(PROP.SIZEX -2, ' ') + " ";
        bot = " " + bot.append(PROP.SIZEX -2, '_') + " ";

        if (PROP.VALUE == 0 && BUTTON_PRESSED.ping_down(tmeFrame_Time) == false)
        // Dont reverse the colors if Button off or no ping
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

      //Debug -- displays dedraw count and other variables.
      if (true == DEBUG_COUNTER)
      {
        Counter++;
        mvwprintw(winButton, 0, 0, "%d ", Counter);
        //mvwprintw(winButton, 1, 0, "%d ", BUTTON_PRESSED.ping_down(tmeFrame_Time));
      }

      wattroff(winButton, A_REVERSE);

      // Draw button if type not hidden and enabled.
      if (PROP.ENABLED == true && PROP.HIDDEN == false)
      {
        wrefresh(winButton);
      }

      // If the button is simple click, reset its value
      if (PROP.TYPE == 0 && PROP.VALUE == 1)
      {
        PROP.VALUE = 0;
        BUTTON_PRESSED.ping_up(tmeFrame_Time, VISIBLE_UPATE_TIME);
      }

      PROP.CHANGED = false;
    }
  }
};


// -------------------------------------------------------------------------------------
// Button Zone Variable
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

  void draw(bool Refresh, unsigned long tmeFrame_Time)
  {
    if (BUTTONS.size() >0)
    {
      for (int pos = 0; pos < BUTTONS.size(); pos++)
      {
        BUTTONS[pos].draw(Refresh, tmeFrame_Time);
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

  void change_enabled(string Name, bool Enabled)
  // Change Property by Name.
  {
    for(int pos=0; pos<BUTTONS.size(); pos++)
    {
      if (BUTTONS[pos].PROP.NAME == Name)
      {
        if (BUTTONS[pos].PROP.ENABLED != Enabled)
        {
          BUTTONS[pos].PROP.ENABLED = Enabled;

          /*
          if(Enabled == true)
          {
            BUTTONS[pos].PROP.CLEAR = true;
          }
          */

          BUTTONS[pos].PROP.CHANGED = true;
        }
      }
    }
  }

  void change_hidden(string Name, bool Hidden)
  // Change Property by Name.
  {
    for(int pos=0; pos<BUTTONS.size(); pos++)
    {
      if (BUTTONS[pos].PROP.NAME == Name)
      {
        if (BUTTONS[pos].PROP.HIDDEN != Hidden)
        {
          BUTTONS[pos].PROP.HIDDEN = Hidden;

          /*
          if(Hidden == true)
          {
            BUTTONS[pos].PROP.CLEAR = true;
          }
          */

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

    // Check each enabled button in zone for clicked coords within
    for(int pos=0; pos<BUTTONS.size(); pos++)
    {
      if(BUTTONS[pos].PROP.ENABLED == true && (BUTTONS[pos].PROP.TYPE == 0 || BUTTONS[pos].PROP.TYPE == 1 || BUTTONS[pos].PROP.TYPE == 2))
      // Only update known button types or not disabled button type.
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

    // Create Gadget Window
    winFrequency = newwin(PROP.SIZEY, PROP.SIZEX, PROP.POSY, PROP.POSX);

    // Create Button Zone for Gadget
    bzGadget.create_button (0, "GADGET", "%Gadget", 0, 0, CRT_get_color_pair(COLOR_YELLOW, COLOR_WHITE), 0);
    
    bzGadget.create_button (1, "SKIP", "%SKIP", 0, 0, CRT_get_color_pair(COLOR_GREEN, COLOR_WHITE), 0);
    bzGadget.create_button (2, "HOLD", "%HOLD", 0, 0, CRT_get_color_pair(COLOR_BLUE, COLOR_WHITE), 0);
    bzGadget.create_button (3, "CLEAR", "%CLEAR", 0, 0, CRT_get_color_pair(COLOR_YELLOW, COLOR_WHITE), 0);

    bzGadget.change_hidden("GADGET", true);

    bzGadget.change_enabled("GADGET", false);
    bzGadget.change_enabled("HOLD", false);
    bzGadget.change_enabled("SKIP", false);
    bzGadget.change_enabled("CLEAR", false);
    
    // Create Noise Level Bar
    BAR_NOISE_LEVEL.label(PROP.NOISE_LABEL);
    BAR_NOISE_LEVEL.label_size(PROP.NOISE_LABEL.size());
    BAR_NOISE_LEVEL.size(PROP.BAR_SIZE);
    BAR_NOISE_LEVEL.max_value(100);
    BAR_NOISE_LEVEL.print_min(PROP.SHOW_MIN_MAX);
    BAR_NOISE_LEVEL.print_max(PROP.SHOW_MIN_MAX);
    BAR_NOISE_LEVEL.min_max(true);
    BAR_NOISE_LEVEL.min_max_time_span(60000);

    // Create Signal Level Bar
    BAR_SIGNAL_LEVEL.label(PROP.SIGNAL_LABEL);
    BAR_SIGNAL_LEVEL.label_size(PROP.SIGNAL_LABEL.size());
    BAR_SIGNAL_LEVEL.size(PROP.BAR_SIZE);
    BAR_SIGNAL_LEVEL.max_value(100);
    BAR_SIGNAL_LEVEL.print_min(PROP.SHOW_MIN_MAX);
    BAR_SIGNAL_LEVEL.print_max(PROP.SHOW_MIN_MAX);
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

    // Move Resize Buttons
    bzGadget.move_resize(0, PROP.POSY, PROP.POSX, PROP.SIZEY, PROP.SIZEX);
    
    if(Button_YSize > PROP.SIZEY)
    {
      Button_YSize = PROP.SIZEY;
      bzGadget.change_label("SKIP", "SKIP");
      bzGadget.change_label("HOLD", "HOLD");
      bzGadget.change_label("CLEAR", "CLEAR");
    }

    bzGadget.move_resize(1, PROP.POSY + (Button_YSize *0), PROP.POSX + (Button_XSize *0), Button_YSize, Button_XSize);
    bzGadget.move_resize(2, PROP.POSY + (Button_YSize *0), PROP.POSX + (Button_XSize *1), Button_YSize, Button_XSize);
    bzGadget.move_resize(3, PROP.POSY + (Button_YSize *0), PROP.POSX + (Button_XSize *2), Button_YSize, Button_XSize);
  }

  bool changed()
  // Returns true if any of the properties have changed.
  {
    return PROP.CHANGED;
  }

  void update_value(API_SQUELCH_DESTINATION &New_Value, unsigned long tmeFrame_Time)
  {
    PROP.VALUE.FREQUENCY.FREQUENCY = New_Value.FREQUENCY.FREQUENCY;
    PROP.VALUE.FREQUENCY.LABEL = New_Value.FREQUENCY.LABEL;
    PROP.VALUE.FREQUENCY.NOISE_LEVEL = New_Value.FREQUENCY.NOISE_LEVEL;
    PROP.VALUE.FREQUENCY.SIGNAL_LEVEL = New_Value.FREQUENCY.SIGNAL_LEVEL;
    PROP.VALUE.FREQUENCY.SIGNAL_OUTSIDE_FILTER = New_Value.FREQUENCY.SIGNAL_OUTSIDE_FILTER;
    PROP.VALUE.FREQUENCY.IS_OPEN = New_Value.FREQUENCY.IS_OPEN;

    VISIBLE_UPDATE_SIGNAL.ping_up(FRAME_TIME, VISIBLE_UPATE_TIME);

    PROP.CHANGED = true;
    //New_Value.FREQUENCY.CHANGED = false;

    // Enable gadget to display.
    if(PROP.TYPE == -1)
    {
      PROP.TYPE = 0;
      bzGadget.change_enabled("GADGET", true);
    }

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
      // Set colors.

      // Skipped
      if (PROP.SKIP == true)
      {
        // Change the colors.
        wbkgd(winFrequency, COLOR_PAIR(CRT_get_color_pair(PROP.BCOLOR, COLOR_MAGENTA)));
        BAR_NOISE_LEVEL.color_background(PROP.BCOLOR);
        BAR_SIGNAL_LEVEL.color_background(PROP.BCOLOR);
      } 
      else if (PROP.VALUE.FREQUENCY.IS_OPEN == true)
      {
        // Reset the linger timer.
        LINGER_DIRTY_SIGNAL.ping_up(FRAME_TIME, LINGER_TIME);

        // Change Colors
        wbkgd(winFrequency, COLOR_PAIR(CRT_get_color_pair(COLOR_WHITE, PROP.BCOLOR)));
        BAR_NOISE_LEVEL.color_background(COLOR_WHITE);
        BAR_SIGNAL_LEVEL.color_background(COLOR_WHITE);
      }
      // Outside Filter
      else if (PROP.VALUE.FREQUENCY.SIGNAL_OUTSIDE_FILTER == true)
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
        if(PROP.HELD == false)
        {
          wbkgd(winFrequency, COLOR_PAIR(CRT_get_color_pair(PROP.BCOLOR, COLOR_GREEN)));
        }
        else
        {
          wbkgd(winFrequency, COLOR_PAIR(CRT_get_color_pair(PROP.BCOLOR, COLOR_WHITE)));
        }
        
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
      if (PROP.SHOW_FREQUENCY == true)
      {
        mvwprintw(winFrequency, 0, 0, "%s %3.3f", PROP.FREQUENCY_LABEL.c_str(), ((float)PROP.VALUE.FREQUENCY.FREQUENCY / 1000000));
        mvwprintw(winFrequency, 0, 17, "%s", (PROP.VALUE.FREQUENCY.LABEL.c_str()));
      }
      else
      {
        mvwprintw(winFrequency, 0, 0, "%s", (PROP.VALUE.FREQUENCY.LABEL.c_str()));
      }

      //Draw Bars
      if (PROP.SHOW_SIGNAL == true)
      {
        BAR_SIGNAL_LEVEL.progress_bar(winFrequency, 1, 0, (100 + PROP.VALUE.FREQUENCY.SIGNAL_LEVEL), FRAME_TIME);
      }
      if (PROP.SHOW_NOISE == true)
      {
        BAR_NOISE_LEVEL.progress_bar(winFrequency, 2, 0, (100 + PROP.VALUE.FREQUENCY.NOISE_LEVEL), FRAME_TIME);
      }

      //Debug -- displays dedraw count and other variables.
      if (true == DEBUG_COUNTER)
      {
        Counter++;
        mvwprintw(winFrequency, 0, 0, "%d ", Counter);
        mvwprintw(winFrequency, 1, 0, "%d ", PROP.VALUE.FREQUENCY.CHANGED);
      }

      // Reset Properties Changed.
      PROP.VALUE.FREQUENCY.IS_OPEN = false;
      PROP.VALUE.FREQUENCY.SIGNAL_OUTSIDE_FILTER = false;
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

    // Draw the Buttons
    bzGadget.draw(WAS_REDRAWN, tmeFrame_Time);

  }

  bool was_redrawn()
  // Returns true if the gadget redrew itself during the previous cycle.
  {
    return WAS_REDRAWN;
  }

  bool check_click(int x_clicked, int y_clicked, string &Name)
  {
    bool return_check_click = false;

    if (bzGadget.check_click(x_clicked, y_clicked) == true)
    {
      int value = 0;
      Name = bzGadget.get_clicked_name();
      value = bzGadget.get_clicked_value(Name);

      if(Name == "GADGET")
      {
        bzGadget.change_enabled("GADGET", false);

        bzGadget.change_enabled("HOLD", true);
        bzGadget.change_enabled("SKIP", true);
        bzGadget.change_enabled("CLEAR", true);

        PROP.CHANGED = true;

        return_check_click = true;
      }
      else if(Name == "HOLD")
      {
        bzGadget.change_enabled("GADGET", true);

        bzGadget.change_enabled("HOLD", false);
        bzGadget.change_enabled("SKIP", false);
        bzGadget.change_enabled("CLEAR", false);

        PROP.CHANGED = true;

        return_check_click = true;
      }
      else if(Name == "SKIP")
      {
        bzGadget.change_enabled("GADGET", true);

        bzGadget.change_enabled("HOLD", false);
        bzGadget.change_enabled("SKIP", false);
        bzGadget.change_enabled("CLEAR", false);

        PROP.CHANGED == true;
        

        return_check_click = true;
      }
      else if(Name == "CLEAR")
      {
        bzGadget.change_enabled("GADGET", true);

        bzGadget.change_enabled("HOLD", false);
        bzGadget.change_enabled("SKIP", false);
        bzGadget.change_enabled("CLEAR", false);

        PROP.CHANGED == true;
        
        return_check_click = true;
      }

      PROP.CHANGED = true;

      //return_check_click = true;
    }

    return return_check_click;
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