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

#include "gadgets.h"

using namespace std;

// -------------------------------------------------------------------------------------
//  Panel Class

void PANEL::draw_border()
{
  wborder(winPANEL, PROP.BORDER.LEFT, PROP.BORDER.RIGHT, 
                    PROP.BORDER.TOP, PROP.BORDER.BOT, 
                    PROP.BORDER.TOP_LEFT, PROP.BORDER.TOP_RIGHT, 
                    PROP.BORDER.BOT_LEFT, PROP.BORDER.BOT_RIGHT);
}

void PANEL::create()
{
  winPANEL = newwin(PROP.SIZEY, PROP.SIZEX, PROP.POSY, PROP.POSX);

  refresh();

  draw_border();

  wbkgd(winPANEL, COLOR_PAIR(CRT_get_color_pair(PROP.BCOLOR, PROP.COLOR)));

  CHANGED = true;
}

void PANEL::clear()
{
  werase(winPANEL);
  draw_border();

  CHANGED = true;
}

void PANEL::blank_out()
{
  werase(winPANEL);

  CHANGED = true;
}


void PANEL::changed_on()
{
  CHANGED = true;
}

void PANEL::set_color(int Background_Color, int Color)
{
  if (PROP.BCOLOR != Background_Color || PROP.COLOR != Color)
  {
    PROP.BCOLOR = Background_Color;
    PROP.COLOR = Color;

    wbkgd(winPANEL, COLOR_PAIR(CRT_get_color_pair(PROP.BCOLOR, PROP.COLOR)));
    CHANGED = true;    
  }
}

void PANEL::draw(bool Refresh)
{
  if (CHANGED == true || Refresh == true)
  {
    //Debug -- displays dedraw count and other variables.
    if (true == DEBUG_COUNTER)
    {
      Counter++;
      mvwprintw(winPANEL, 0, 0, "%d ", Counter);
    }
    
    wrefresh(winPANEL);

    CHANGED = false;
  }
}


// -------------------------------------------------------------------------------------
//  Text_Field Classes

bool Text_Field::changed()
// Returns true if any of the properties have changed.
{
  return CHANGED;
}

bool Text_Field::has_blank()
// Returns true if any of the properties have changed.
{
  return HAS_BLANK;
}

void Text_Field::redraw()
{
  CHANGED = true;
}

void Text_Field::set_inverse(bool Inverse)
{
  if (Inverse != PROP.INVERSE)
  {
    PROP.INVERSE = Inverse;
    CHANGED = true;
  }
}

void Text_Field::set_text(string Text, unsigned long tmeFrame_Time)
{
  if (Text != PROP.LABEL)
  {
    if (PROP.DONT_BLANK == true && Text  == "")
    {
      HAS_BLANK = true;
    }
    else
    {
      PROP.LABEL = Text;

      if (Text  == "")
      {
        HAS_BLANK = true;
      }
      else
      {
        HAS_BLANK = false;
      }

      CHANGED = true;
      
      if (PROP.UPDATE_INDICATION == true)
      {
        UPDATE_INDICATION_TIMER.ping_up(tmeFrame_Time, INDICATED_BLINK_TIME);
      }
    }
  }
}

void Text_Field::set_text(string Text)
{
  set_text(Text, 0);
}

void Text_Field::clear()
{
  PROP.LABEL = "";
  CHANGED = true;
}

void Text_Field::set_color(int Background_Color, int Color)
{
  if (Background_Color != PROP.BCOLOR || Color != PROP.COLOR)
  {
    PROP.BCOLOR = Background_Color;
    PROP.COLOR  = Color;
    CHANGED = true;
  }
}

void Text_Field::draw(PANEL &Panel, bool Refresh, unsigned long tmeFrame_Time)
{
  if (PROP.UPDATE_INDICATION == true && UPDATE_INDICATION_TIMER.blip_moved(tmeFrame_Time) == true)
  {
    Refresh = true;
  }

  if (CHANGED == true || Refresh == true)
  {
    // Check for Reverse Text
    if (PROP.INVERSE == true)
    {
      wattron(Panel.winPANEL, A_REVERSE);
    }

    // Check for Colored Text
    if (PROP.COLORS_ON == true)
    {
      wattron(Panel.winPANEL, COLOR_PAIR(CRT_get_color_pair(PROP.BCOLOR, PROP.COLOR)));
    }

    // Check for Blink
    if (PROP.UPDATE_INDICATION == true && UPDATE_INDICATION_TIMER.ping_down(tmeFrame_Time) == true)
    {
      wattron(Panel.winPANEL, COLOR_PAIR(CRT_get_color_pair(COLOR_WHITE, COLOR_BLACK)));
    }

    // Check for Text Modification
    if ((PROP.JUSTIFICATION_LEFT == true || PROP.JUSTIFICATION_CENTER == true|| PROP.JUSTIFICATION_RIGHT == true) && PROP.SIZEX >0)
    {
      // Print Center Justified
      if (PROP.JUSTIFICATION_CENTER == true)
      {
        mvwprintw(Panel.winPANEL, PROP.POSY, PROP.POSX, linefill(PROP.SIZEX, PROP.LABEL).c_str());  //print line.  
      }
      // Print Right Justified
      else if (PROP.JUSTIFICATION_RIGHT == true)
      {
        mvwprintw(Panel.winPANEL, PROP.POSY, PROP.POSX, right_justify(PROP.SIZEX, PROP.LABEL).c_str());  //print line.  
      }
      // Print Left Justified or full field.
      else if (PROP.JUSTIFICATION_LEFT == true)
      {
        mvwprintw(Panel.winPANEL, PROP.POSY, PROP.POSX, left_justify(PROP.SIZEX, PROP.LABEL).c_str());  //print line.  
      }
    }
    else  // Print Simple Text
    {
      mvwprintw(Panel.winPANEL, PROP.POSY, PROP.POSX, PROP.LABEL.c_str());  //print line. 
    }

    // Check for Blink
    if (PROP.UPDATE_INDICATION == true && UPDATE_INDICATION_TIMER.ping_down(tmeFrame_Time) == true)
    {
      wattroff(Panel.winPANEL, COLOR_PAIR(CRT_get_color_pair(COLOR_WHITE, COLOR_BLACK)));
    }

    // Check for Colored Text
    if (PROP.COLORS_ON == true)
    {
      wattroff(Panel.winPANEL, COLOR_PAIR(CRT_get_color_pair(PROP.BCOLOR, PROP.COLOR)));
    }

    // Check for Reverse Text
    if (PROP.INVERSE == true)
    {
      wattroff(Panel.winPANEL, A_REVERSE);
    }

    //Debug -- displays dedraw count and other variables.
    if (true == DEBUG_COUNTER)
    {
      Counter++;
      mvwprintw(Panel.winPANEL, PROP.POSY, PROP.POSX, "%d ", Counter);
    }

    CHANGED = false;

    Panel.changed_on();
  }
}
  
void Text_Field::draw(PANEL &Panel, bool Refresh)
{
  draw(Panel, Refresh, 0);
}


// -------------------------------------------------------------------------------------
//  Text_Field_Multi_Line Classes

void Text_Field_Multi_Line::draw_all_lines(PANEL &Button_Panel, deque<string> &Lines, int PosY, int PosX)
{
  for (int pos = 0; pos < Lines.size(); pos++)
  {
    //mvwprintw(Button_Panel.winPANEL, PosY + pos, PosX, Lines[pos].c_str());  //print line. 
    mvwprintw(Button_Panel.winPANEL, PosY + pos, PosX, Lines[pos].c_str());  //print line. 
  }
}

int Text_Field_Multi_Line::line_count()
{
  return PROP.LABEL_MULTI_LINE.size();
}

bool Text_Field_Multi_Line::changed()
// Returns true if any of the properties have changed.
{
  return CHANGED;
}

bool Text_Field_Multi_Line::has_blank()
// Returns true if any of the properties have changed.
{
  return HAS_BLANK;
}

void Text_Field_Multi_Line::redraw()
{
  CHANGED = true;
}

void Text_Field_Multi_Line::set_inverse(bool Inverse)
{
  if (Inverse != PROP.INVERSE)
  {
    PROP.INVERSE = Inverse;
    CHANGED = true;
  }
}

void Text_Field_Multi_Line::set_text(string Text, unsigned long tmeFrame_Time)
{
  if (Text != PROP.LABEL)
  {
    if (PROP.DONT_BLANK == true && Text  == "")
    {
      HAS_BLANK = true;
    }
    else
    {
      string orig = Text;
      string line = "";
      bool done = false;
      int p = 0;

      PROP.LABEL_MULTI_LINE.clear();

      HAS_BLANK = true;

      // Parse Line
      while (done == false)
      {
        p = orig.find("\n");

        if (p >= 0)
        {
          line = orig.substr(0,p);
          orig.erase(0, p+1);
        }
        else
        {
          line = orig;
          done = true;
        }

        if (line != "")
        {
          HAS_BLANK = false;
        }

        // Add line to queue
        if ((PROP.JUSTIFICATION_LEFT == true || PROP.JUSTIFICATION_CENTER == true|| PROP.JUSTIFICATION_RIGHT == true) && PROP.SIZEX >0)
        {
          // Print Center Justified
          if (PROP.JUSTIFICATION_CENTER == true)
          {
            PROP.LABEL_MULTI_LINE.push_back(linefill(PROP.SIZEX, line));
          }
          // Print Right Justified
          else if (PROP.JUSTIFICATION_RIGHT == true)
          {
            PROP.LABEL_MULTI_LINE.push_back(right_justify(PROP.SIZEX, line));
          }
          // Print Left Justified or full field.
          else if (PROP.JUSTIFICATION_LEFT == true)
          {
            PROP.LABEL_MULTI_LINE.push_back(left_justify(PROP.SIZEX, line));
          }
        }
        else  // Print Simple Text
        {
          PROP.LABEL_MULTI_LINE.push_back(line);
        }
      }

      CHANGED = true;
      
      if (PROP.UPDATE_INDICATION == true)
      {
        UPDATE_INDICATION_TIMER.ping_up(tmeFrame_Time, INDICATED_BLINK_TIME);
      }
    }
  }
}

void Text_Field_Multi_Line::set_text(string Text)
{
  set_text(Text, 0);
}

void Text_Field_Multi_Line::set_color(int Background_Color, int Color)
{
  if (Background_Color != PROP.BCOLOR || Color != PROP.COLOR)
  {
    PROP.BCOLOR = Background_Color;
    PROP.COLOR  = Color;
    CHANGED = true;
  }
}

void Text_Field_Multi_Line::draw(PANEL &Panel, bool Refresh, unsigned long tmeFrame_Time)
{
  if (PROP.UPDATE_INDICATION == true && UPDATE_INDICATION_TIMER.blip_moved(tmeFrame_Time) == true)
  {
    Refresh = true;
  }

  if (CHANGED == true || Refresh == true)
  {
    // Clear Panel
    //  In future, clear only printable lines.
    Panel.clear();

    // Check for Reverse Text
    if (PROP.INVERSE == true)
    {
      wattron(Panel.winPANEL, A_REVERSE);
    }

    // Check for Colored Text
    if (PROP.COLORS_ON == true)
    {
      wattron(Panel.winPANEL, COLOR_PAIR(CRT_get_color_pair(PROP.BCOLOR, PROP.COLOR)));
    }

    // Check for Blink
    if (PROP.UPDATE_INDICATION == true && UPDATE_INDICATION_TIMER.ping_down(tmeFrame_Time) == true)
    {
      wattron(Panel.winPANEL, COLOR_PAIR(CRT_get_color_pair(COLOR_WHITE, COLOR_BLACK)));
    }

    // Check for Text Modification
    draw_all_lines(Panel, PROP.LABEL_MULTI_LINE, PROP.POSY, PROP.POSX);

    // Check for Blink
    if (PROP.UPDATE_INDICATION == true && UPDATE_INDICATION_TIMER.ping_down(tmeFrame_Time) == true)
    {
      wattroff(Panel.winPANEL, COLOR_PAIR(CRT_get_color_pair(COLOR_WHITE, COLOR_BLACK)));
    }

    // Check for Colored Text
    if (PROP.COLORS_ON == true)
    {
      wattroff(Panel.winPANEL, COLOR_PAIR(CRT_get_color_pair(PROP.BCOLOR, PROP.COLOR)));
    }

    // Check for Reverse Text
    if (PROP.INVERSE == true)
    {
      wattroff(Panel.winPANEL, A_REVERSE);
    }

    //Debug -- displays dedraw count and other variables.
    if (true == DEBUG_COUNTER)
    {
      Counter++;
      mvwprintw(Panel.winPANEL, PROP.POSY, PROP.POSX, "%d ", Counter);
    }

    CHANGED = false;

    Panel.changed_on();
  }
}
  
void Text_Field_Multi_Line::draw(PANEL &Panel, bool Refresh)
{
  draw(Panel, Refresh, 0);
}


// -------------------------------------------------------------------------------------
//  Title_Bar Classes

void Title_Bar::create()
// Define and behavior.  
// Like set but leaves off position and size details.
// Does not create window.
{
  TITLE_BAR_PANEL.PROP.SIZEY = 1;
  TITLE_BAR_PANEL.PROP.SIZEX = PROP.SIZE; 
  TITLE_BAR_PANEL.PROP.POSY = PROP.POSY;
  TITLE_BAR_PANEL.PROP.POSX = PROP.POSX + PROP.SIZEX - PROP.SIZE;

  TITLE_BAR_PANEL.set_color(PROP.BCOLOR, PROP.COLOR);
  
  TITLE_BAR_PANEL.create();

  TITLE.PROP.POSY = 0;
  TITLE.PROP.POSX = 0;
  TITLE.PROP.SIZEX = TITLE_BAR_PANEL.PROP.SIZEX;
  TITLE.PROP.JUSTIFICATION_RIGHT = true;
  TITLE.PROP.COLORS_ON = true;
  TITLE.PROP.INVERSE = true;
  
  TITLE.set_color(PROP.BCOLOR, PROP.COLOR);

  bool CHANGED = true;
}

bool Title_Bar::changed()
// Returns true if any of the properties have changed.
{
  return PROP.CHANGED;
}

void Title_Bar::draw(bool Refresh)
// Draw the text_box on the screen if the value has changed or if  
//  the Refresh parameter is true.
{
  if (PROP.CHANGED == true || Refresh == true)
  {
    if (PROP.LABEL != TITLE.PROP.LABEL)
    {
      TITLE.set_text(PROP.LABEL);
    }

    TITLE.draw(TITLE_BAR_PANEL, Refresh);

    TITLE_BAR_PANEL.draw(Refresh);

    PROP.CHANGED = false;
  }
}

// -------------------------------------------------------------------------------------
//  Text_Box Classes

void Text_Line_List::clear_outside_max()
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

void Text_Line_List::add(unsigned long tmeCurrentMillis, string line)
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

bool Text_Line_List::avail()
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

Text_Line Text_Line_List::get_line_to_print(int pos)
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

void Text_Line_List::clear()
{
  LINES.clear();
}


void Text_Box::modify(int id, string name, string label, int type, int color, int bcolor)
// Changes all properties
{
  PROP.ID = id;
  PROP.NAME = name;
  PROP.LABEL = label;

  PROP.TYPE = type;
  PROP.COLOR = color;

  PROP.CHANGED = true;
}

void Text_Box::create(int id, string name, string label, int type, int color, int bcolor)
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

void Text_Box::move_resize(int posY, int posX, int sizeY, int sizeX)
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

bool Text_Box::changed()
// Returns true if any of the properties have changed.
{
  return PROP.CHANGED;
}

void Text_Box::draw(bool Refresh)
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

void Text_Box::add_line(unsigned long Time_Milli, string Text)
// Add a line of text to Text_Box.
{
  PROP.LINES.add(Time_Milli, Text);
  PROP.CHANGED = true;
}

void Text_Box::clear_text()
{
  PROP.LINES.clear();
}


// -------------------------------------------------------------------------------------
// Button Classes

void Button::create()
//void create(int id, string name, string label, int value, int type, int color, int bcolor)
// Define button and behavior.  
// Like set but leaves off position and size details.
// Does not create window.
{
  BUTTON_PANEL.PROP.POSY = PROP.POSY;
  BUTTON_PANEL.PROP.POSX = PROP.POSX;
  BUTTON_PANEL.PROP.SIZEY = PROP.SIZEY;
  BUTTON_PANEL.PROP.SIZEX = PROP.SIZEX;
  BUTTON_PANEL.PROP.BORDER = PROP.BORDER;

  BUTTON_PANEL.create();

  LINES.PROP.POSY = 0;
  LINES.PROP.SIZEX = BUTTON_PANEL.PROP.SIZEX;
  LINES.PROP.SIZEY = BUTTON_PANEL.PROP.SIZEY;
  LINES.PROP.JUSTIFICATION_CENTER = true;

  bool CHANGED = true;
}

bool Button::changed()
// Returns true if any of the properties have changed.
{
  return PROP.CHANGED;
}

void Button::advance()
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

void Button::change_on()
{
  PROP.CHANGED = true;
}

void Button::set_pos_size(int PosY, int PosX, int SizeY, int SizeX)
{
  if ((PROP.POSY != PosY) && (PROP.POSX != PosX) && (PROP.SIZEY != SizeY) && (PROP.SIZEX != SizeX))
  {
    PROP.POSY = PosY;
    PROP.POSX = PosX;
    PROP.SIZEY = SizeY;
    PROP.SIZEX = SizeX;

    PROP.CHANGED = true;
  }
}

void Button::set_name(string Name)
{
  if (PROP.NAME != Name)
  {
    PROP.NAME = Name;

    PROP.CHANGED = true;
  }
}

void Button::set_label(string Label)
{
  if (PROP.LABEL != Label)
  {
    PROP.LABEL = Label;

    PROP.CHANGED = true;
  }
}

void Button::set_value(int Value)
{
  if (PROP.VALUE != Value)
  {
    PROP.VALUE = Value;

    PROP.CHANGED = true;
  }
}

void Button::set_type(int Type)
{
  if (PROP.TYPE != Type)
  {
    PROP.TYPE = Type;

    PROP.CHANGED = true;
  }
}

void Button::set_color(int Background_Color, int Color)
{
  if ((PROP.BCOLOR != Background_Color) && (PROP.COLOR != Color))
  {  
    PROP.BCOLOR = Background_Color;
    PROP.COLOR = Color;

    BUTTON_PANEL.set_color(PROP.BCOLOR, PROP.COLOR);

    PROP.CHANGED = true;
  }
}

void Button::set_enabled(bool Enabled)
{
  if (PROP.ENABLED != Enabled)
  {
    PROP.ENABLED = Enabled;
    
    PROP.CHANGED = true;
  }
}

void Button::set_hidden(bool Hidden)
{
  if (PROP.HIDDEN != Hidden)
  {
    PROP.HIDDEN = Hidden;

    PROP.CHANGED = true;
  }
}

void Button::draw(bool Refresh, unsigned long tmeFrame_Time)
// Draw the button on the screen if the value has changed or if  
//  the Refresh parameter is true.
{
  // Refresh if time active.
  if (BUTTON_PRESSED.blip_moved(tmeFrame_Time) == true)
  {
    Refresh = true;
  }

  if (PROP.CHANGED == true || Refresh == true)
  {
    LINES.set_text(PROP.LABEL);
    
    //Set Color, Set Reverse if On, Draw Sencils for Buttons
    if (PROP.ENABLED == true && PROP.HIDDEN == false && 
                        (PROP.TYPE == 0 || PROP.TYPE == 1 || PROP.TYPE == 2))
    {
      // Start by setting button color.
      BUTTON_PANEL.set_color(PROP.BCOLOR, PROP.COLOR);

      if (PROP.VALUE == 0 && BUTTON_PRESSED.ping_down(tmeFrame_Time) == false)
      // Dont reverse the colors if Button off or no ping
      {
        BUTTON_PANEL.set_color(PROP.BCOLOR, PROP.COLOR);
      }
      else
      {
        // If the color background is not black, this works 
        //  fine.
        BUTTON_PANEL.set_color(PROP.COLOR, PROP.BCOLOR);

        // Perhaps in the future, I will add a translate to 
        //  reverse the colors with white background and 
        //  text as background color.
      }
    }
    else
    // If button type is unknow or hidden then clear out and set to black.
    {
      BUTTON_PANEL.set_color(COLOR_BLACK, COLOR_BLACK);
      BUTTON_PANEL.blank_out();
    }
    
    // Dont draw lines if hidden
    if (PROP.HIDDEN == false)
    {
      LINES.draw(BUTTON_PANEL, Refresh);
    }
    BUTTON_PANEL.draw(Refresh);

    // If the button is simple click, reset its value
    if (PROP.TYPE == 0 && PROP.VALUE == 1)
    {
      PROP.VALUE = 0;
      BUTTON_PRESSED.ping_up(tmeFrame_Time, VISIBLE_UPATE_TIME);
    }

    PROP.CHANGED = false;
  }
}


// -------------------------------------------------------------------------------------
// Button Zone Variable

int Button_Zone_Manager::get_pos(int Id)
{
  int ret_pos = -1;

  for (int pos = 0; pos < BUTTONS.size(); pos++)
  {
    if (Id == BUTTONS[pos].PROP.ID)
    {
      ret_pos = pos;
    }
  }

  return ret_pos;
}

int Button_Zone_Manager::get_pos(string Name)
{
  int ret_pos = -1;

  for (int pos = 0; pos < BUTTONS.size(); pos++)
  {
    if (Name == BUTTONS[pos].PROP.NAME)
    {
      ret_pos = pos;
    }
  }

  return ret_pos;
}

int Button_Zone_Manager::size()
// return the size
{
  return BUTTONS.size();
}

string Button_Zone_Manager::name(int pos)
// return the name at the pos
{
  return BUTTONS[pos].PROP.NAME;
}

int Button_Zone_Manager::value(int pos)
// return the value at the pos
{
  return BUTTONS[pos].PROP.VALUE;
}

void Button_Zone_Manager::click_advance(int Id)
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

void Button_Zone_Manager::clear()
{
  BUTTONS.clear();
}

void Button_Zone_Manager::create_button()
{
  Button tmp_button;

  tmp_button.PROP = NEW_BUTTON_PROP;

  tmp_button.create();
  //tmp_button.modify(Id, Name, Label, Value, Type, Color, BColor);
  BUTTONS.push_back(tmp_button);
}

void Button_Zone_Manager::draw(bool Refresh, unsigned long tmeFrame_Time)
{
  if (BUTTONS.size() >0)
  {
    for (int pos = 0; pos < BUTTONS.size(); pos++)
    {
      BUTTONS[pos].draw(Refresh, tmeFrame_Time);
    }
  }
}

void Button_Zone_Manager::set_pos_size(int Id, int PosY, int PosX, int SizeY, int SizeX)
{
  int pos = get_pos(Id);

  if (pos > -1)
  {
    BUTTONS[pos].set_pos_size(PosY, PosX, SizeY, SizeX);
  }
}

void Button_Zone_Manager::set_pos_size(string Name, int PosY, int PosX, int SizeY, int SizeX)
{
  int pos = get_pos(Name);

  if (pos > -1)
  {
    BUTTONS[pos].set_pos_size(PosY, PosX, SizeY, SizeX);
  }
}

void Button_Zone_Manager::set_name(int Id, string Name)
{
  int pos = get_pos(Id);

  if (pos > -1)
  {
    BUTTONS[pos].set_name(Name);
  }
}

void Button_Zone_Manager::set_name(string Old_Name, string Name)
{
  int pos = get_pos(Old_Name);

  if (pos > -1)
  {
    BUTTONS[pos].set_name(Name);
  }
}

void Button_Zone_Manager::set_label(int Id, string Label)
{
  int pos = get_pos(Id);

  if (pos > -1)
  {
    BUTTONS[pos].set_label(Label);
  }

  BUTTONS[Id].set_label(Label);

}

void Button_Zone_Manager::set_label(string Name, string Label)
{
  int pos = get_pos(Name);

  if (pos > -1)
  {
    BUTTONS[pos].set_label(Label);
  }
}

void Button_Zone_Manager::set_value(int Id, int Value)
{
  int pos = get_pos(Id);

  if (pos > -1)
  {
    BUTTONS[pos].set_value(Value);
  }
}

void Button_Zone_Manager::set_value(string Name, int Value)
{
  int pos = get_pos(Name);

  if (pos > -1)
  {
    BUTTONS[pos].set_value(Value);
  }
}

void Button_Zone_Manager::set_type(int Id, int Type)
{
  int pos = get_pos(Id);

  if (pos > -1)
  {
    BUTTONS[pos].set_type(Type);
  }
}

void Button_Zone_Manager::set_type(string Name, int Type)
{
  int pos = get_pos(Name);

  if (pos > -1)
  {
    BUTTONS[pos].set_type(Type);
  }
}

void Button_Zone_Manager::set_color(int Id, int Background_Color, int Color)
{
  int pos = get_pos(Id);

  if (pos > -1)
  {
    BUTTONS[pos].set_color(Background_Color, Color);
  }
}

void Button_Zone_Manager::set_color(string Name, int Background_Color, int Color)
{
  int pos = get_pos(Name);

  if (pos > -1)
  {
    BUTTONS[pos].set_color(Background_Color, Color);
  }
}

void Button_Zone_Manager::set_enabled(int Id, bool Enabled)
// Change Property by Name.
{
  int pos = get_pos(Id);

  if (pos > -1)
  {
    BUTTONS[pos].set_enabled(Enabled);
  }
}

void Button_Zone_Manager::set_enabled(string Name, bool Enabled)
// Change Property by Name.
{
  int pos = get_pos(Name);

  if (pos > -1)
  {
    BUTTONS[pos].set_enabled(Enabled);
  }
}

void Button_Zone_Manager::set_hidden(int Id, bool Hidden)
// Change Property by Name.
{
  int pos = get_pos(Id);

  if (pos > -1)
  {
    BUTTONS[pos].set_hidden(Hidden);
  }
}

void Button_Zone_Manager::set_hidden(string Name, bool Hidden)
// Change Property by Name.
{
  int pos = get_pos(Name);

  if (pos > -1)
  {
    BUTTONS[pos].set_hidden(Hidden);
  }
}

string Button_Zone_Manager::get_clicked_name()
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

int Button_Zone_Manager::get_clicked_value(string Name)
// returns the value of the named clicked button in the list
{
  int pos = get_pos(Name);
  int ret_int = 0;

  if (pos > -1)
  {
    ret_int = BUTTONS[pos].PROP.VALUE;
    BUTTONS[pos].PROP.CLICKED = false;
  }

  return ret_int;
}

int Button_Zone_Manager::get_id_of_button_with_value(int Value)
{
  int ret_int = -1;
  for (int pos = 0; pos < BUTTONS.size(); pos++)
  {
    if (BUTTONS[pos].PROP.VALUE == Value)
    {
      ret_int = BUTTONS[pos].PROP.ID;
    }
  }
  return ret_int;
}

bool Button_Zone_Manager::check_click(int x,int y)
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


// ---------------------------------------------------------------------------------------
// Bar Classes

void BAR_TIME_SLICE::clear()
{
  ACTIVE = false;
  MIN_VALUE = 0;
  MAX_VALUE = 0;
  SNAPSHOT = "";
}

bool BAR_TIME_SLICE::active()
{
  return ACTIVE;
}

void BAR_TIME_SLICE::store_min_max(int Value)
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

int BAR_TIME_SLICE::min()
{
  return MIN_VALUE;
}

int BAR_TIME_SLICE::max()
{
  return MAX_VALUE;
}


// I dont like this
int BAR::get_min_value()
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
int BAR::get_max_value()
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

void BAR::wat_on_background(WINDOW *winWindow)
// Set background color to print.
{
  wattron(winWindow, COLOR_PAIR(CRT_get_color_pair(COLOR_BACKGROUND, COLOR_FOREGROUND)));
}

void BAR::wat_off_background(WINDOW *winWindow)
// Set background color off to print to red.
{
  wattroff(winWindow, COLOR_PAIR(CRT_get_color_pair(COLOR_BACKGROUND, COLOR_FOREGROUND)));
}

void BAR::wat_on_red(WINDOW *winWindow)
// Set color to print to red.
{
  wattron(winWindow, COLOR_PAIR(CRT_get_color_pair(COLOR_BACKGROUND, COLOR_RED)));
}

void BAR::wat_off_red(WINDOW *winWindow)
// Set color off to print to red.
{
  wattroff(winWindow, COLOR_PAIR(CRT_get_color_pair(COLOR_BACKGROUND, COLOR_RED)));
}

void BAR::wat_on_green_red(WINDOW *winWindow, bool value)
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

void BAR::wat_off_green_red(WINDOW *winWindow, bool value)
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

int BAR::get_marker_pos(int value)
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

void BAR::print_marker(WINDOW *winWindow, int Ypos, int Xpos, int value)
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

void BAR::draw_bar(int Bar_Type, WINDOW *winWindow)
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

void BAR::color_background(short Color)
// Set the propertie for Background Color.
// Expects NCurses color or color code. 
{
  COLOR_BACKGROUND = Color;
}

void BAR::color_foreground(short Color)
// Set the propertie for Foreground Color.
// Expects NCurses color or color code. 
{
  COLOR_FOREGROUND = Color;
}

void BAR::label(string Label)
// Set the propertie for displayed label.
{
  LABEL = Label;
}

void BAR::label_size(int Label_Size)
// Set the propertie for displayed label size.
{
  LABEL_SIZE = Label_Size;
}

void BAR::size(int Size)
// Set the propertie for progress bar saize.
{
  SIZE = Size;
}

void BAR::max_value(int Max_Value)
// Set the propertie for progress bar max value.
{
  MAX_VALUE = Max_Value;
}

void BAR::print_value(bool Print_Value)
// Set property to print value entered to right of bar.
{
  PRINT_VALUE = Print_Value;
}

void BAR::print_min(bool Print_Min)
// Set property to print value entered to right of bar.
{
  PRINT_MIN = Print_Min;
}

void BAR::print_max(bool Print_Max)
// Set property to print value entered to right of bar.
{
  PRINT_MAX = Print_Max;
}

// Guage variables
void BAR::min_max(bool min_max)
// Set property to activate Min Max observations.
{
  MIN_MAX = min_max;
}

// Guage variables
void BAR::min_max_time_span(int Time_Span_in_ms)
// Set property time amount Min Max will track.
{
  MIN_MAX_TIME_SPAN = Time_Span_in_ms;
}

// Creates a progress bar of 0 to 100 percent.
//  Returns a string of size.
//  Of size, the percentage of value to max_value will be filled
//  with characters.
void BAR::progress_bar(WINDOW *winWindow, int YPos, int XPos, int value)
// Print progress bar in window at coords with value as progress.
{
  YPOS = YPos;
  XPOS = XPos;
  VALUE = value;

  draw_bar(1, winWindow);
}

void BAR::progress_bar(WINDOW *winWindow, int YPos, int XPos, int value, unsigned long tmeFrame_Time)
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

void BAR::progress_bar(WINDOW *winWindow, int YPos, int XPos, int size, int max_value, int value)
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
void BAR::guage_bar(WINDOW *winWindow, int YPos, int XPos, int value)
// Print guage bar in window at coords with value as progress.
{
  YPOS = YPos;
  XPOS = XPos;
  VALUE = value;

  draw_bar(2, winWindow);
}

void BAR::guage_bar(WINDOW *winWindow, int YPos, int XPos, int value, unsigned long tmeFrame_Time)
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

void BAR::guage_bar(WINDOW *winWindow, int YPos, int XPos, int size, int max_value, int value)
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