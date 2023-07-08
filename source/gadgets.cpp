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

#include "gadgets.h"

using namespace std;

/*
// -------------------------------------------------------------------------------------
//  Blank Gadget

// ---------- Creating

// Calculate Size and Position
YAUTOMOBILE_ScreenPos = YSplit;
XAUTOMOBILE_ScreenPos = XAUTOMOBILE_OVERVIEW_ScreenPos + XAUTOMOBILE_OVERVIEW_ScreenSize;
YAUTOMOBILE_ScreenSize = YMax - YSplit - YTabSize;
XAUTOMOBILE_ScreenSize =  XSplit - XAUTOMOBILE_OVERVIEW_ScreenSize;

// Build Window
AUTOMOBILE_PANEL.PROP.SIZEY = YAUTOMOBILE_ScreenSize;
AUTOMOBILE_PANEL.PROP.SIZEX = XAUTOMOBILE_ScreenSize;
AUTOMOBILE_PANEL.PROP.POSY = YAUTOMOBILE_ScreenPos;
AUTOMOBILE_PANEL.PROP.POSX = XAUTOMOBILE_ScreenPos;

AUTOMOBILE_PANEL.create();

// ---------- Update Data
Screen.AUTOMOBILE_OVERVIEW_PANEL.update(sdSysData, tmeCurrentMillis);

// ---------- Screen Draw
AUTOMOBILE_OVERVIEW_PANEL.draw(ScrStat.Needs_Refresh, sdSysData.tmeCURRENT_FRAME_TIME);

// -------------------------------------------------------------------------------------
//  Panel Class

void AUTOMOBILE_OVERVIEW_GADGET::create()
{
  // Build Display Window
  GADGET_PANEL.PROP.SIZEY = PROP.SIZEY;
  GADGET_PANEL.PROP.SIZEX = PROP.SIZEX;
  GADGET_PANEL.PROP.POSY = PROP.POSY;
  GADGET_PANEL.PROP.POSX = PROP.POSX;
  GADGET_PANEL.PROP.COLOR = COLOR_WHITE;
  GADGET_PANEL.PROP.BCOLOR = COLOR_RED;

  GADGET_PANEL.create();

  test.PROP.POSY = 5;
  test.PROP.POSX = 1;
  test.PROP.SIZEX = 10;
  test.PROP.COLORS_ON = true;
  test.PROP.BCOLOR = COLOR_BLACK;
  test.PROP.COLOR = COLOR_WHITE;
  test.PROP.JUSTIFICATION_LEFT = true;
  test.set_text("test");
}

void AUTOMOBILE_OVERVIEW_GADGET::update(system_data &sdSysData, unsigned long &tmeCurrentMillis)
{

}

bool AUTOMOBILE_OVERVIEW_GADGET::draw(bool Refresh, unsigned long tmeFrame_Time)
{
  //-----------
  if (CHANGED == false)
  {

  }

  test.draw(GADGET_PANEL, Refresh);

  GADGET_PANEL.draw(Refresh);

  CHANGED = false;
  return false;
}
*/

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

bool PANEL::draw(bool Refresh)
{
  bool ret_redrawn = false;

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
    ret_redrawn = true;
  }

  return ret_redrawn;
}


// -------------------------------------------------------------------------------------
//  CYBR Classes

  void CYBR::create()
  {
    CYBR_PANEL.PROP.SIZEY = PROP.SIZEY;
    CYBR_PANEL.PROP.SIZEX = PROP.SIZEX; 
    CYBR_PANEL.PROP.POSY = PROP.POSY;
    CYBR_PANEL.PROP.POSX = PROP.POSX;

    CYBR_PANEL.set_color(COLOR_BLACK, COLOR_RED);
    
    CYBR_PANEL.create();

    CYBRValue.resize(CYBR_PANEL.PROP.SIZEY);

    CYBR_YLn = 0;
  }

  void CYBR::input(int Value, int Max_Value, int BColor, int Color)
  {
    if (Value > 0)
    {
      int pos = position_of_scale(PROP.SIZEY -1 , Max_Value, Value);
      int col = CRT_get_color_pair(BColor, Color);

      if (pos > PROP.SIZEY)
      {
        pos = PROP.SIZEY;
      }

      CYBRValue[pos].COLOR_VAL[col]++;

      wattron(CYBR_PANEL.winPANEL, COLOR_PAIR(col));
      mvwprintw(CYBR_PANEL.winPANEL, pos, 0, "%x", CYBRValue[pos].COLOR_VAL[col]);
      wattroff(CYBR_PANEL.winPANEL, COLOR_PAIR(col));
    }
  }

  bool CYBR::draw(unsigned long tmeFrame_Time)
  {
    wattron(CYBR_PANEL.winPANEL, COLOR_PAIR(CRT_get_color_pair(COLOR_RED, COLOR_WHITE)));
    mvwprintw(CYBR_PANEL.winPANEL, 0, 0, "%d", tmeFrame_Time/100);
    wattroff(CYBR_PANEL.winPANEL, COLOR_PAIR(CRT_get_color_pair(COLOR_RED, COLOR_WHITE)));

    mvwprintw(CYBR_PANEL.winPANEL, CYBR_YLn, 0, "  ");

    CYBRValue[CYBR_YLn].COLOR_VAL.fill(0);

    CYBR_YLn = CYBR_YLn -1;
    if (CYBR_YLn <0)
    {
      CYBR_YLn = PROP.SIZEY -1;
    }
    wattron(CYBR_PANEL.winPANEL, COLOR_PAIR(CRT_get_color_pair(COLOR_RED, COLOR_WHITE)));
    mvwprintw(CYBR_PANEL.winPANEL, CYBR_YLn, 0, "/\\");
    wattroff(CYBR_PANEL.winPANEL, COLOR_PAIR(CRT_get_color_pair(COLOR_RED, COLOR_WHITE)));

    // Commit all our changes to the status portion of the screen (winTop)
    return CYBR_PANEL.draw(true);
  }


// -------------------------------------------------------------------------------------
//  Text_Field Classes

void Text_Field::blink(unsigned long tmeFrame_Time)
{
  if (PROP.UPDATE_INDICATION == true)
  {
    UPDATE_INDICATION_TIMER.ping_up(tmeFrame_Time, INDICATED_BLINK_TIME);
    CHANGED = true;
  }
}

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
      if (PROP.AUTO_COLOR == false)
      {
        wattron(Panel.winPANEL, COLOR_PAIR(CRT_get_color_pair(PROP.BCOLOR, PROP.COLOR)));
      }
      else
      {
        wattron(Panel.winPANEL, COLOR_PAIR(CRT_get_color_pair(PROP.BCOLOR, text_color_correction(PROP.BCOLOR))));
      }
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
        mvwprintw(Panel.winPANEL, PROP.POSY, PROP.POSX, "%s", center_justify(PROP.SIZEX, PROP.LABEL).c_str());  //print line.  
      }
      // Print Right Justified
      else if (PROP.JUSTIFICATION_RIGHT == true)
      {
        mvwprintw(Panel.winPANEL, PROP.POSY, PROP.POSX, "%s", right_justify(PROP.SIZEX, PROP.LABEL).c_str());  //print line.  
      }
      // Print Left Justified or full field.
      else if (PROP.JUSTIFICATION_LEFT == true)
      {
        mvwprintw(Panel.winPANEL, PROP.POSY, PROP.POSX, "%s", left_justify(PROP.SIZEX, PROP.LABEL).c_str());  //print line.  
      }
    }
    else  // Print Simple Text
    {
      mvwprintw(Panel.winPANEL, PROP.POSY, PROP.POSX, "%s", PROP.LABEL.c_str());  //print line. 
    }

    // Check for Blink
    if (PROP.UPDATE_INDICATION == true && UPDATE_INDICATION_TIMER.ping_down(tmeFrame_Time) == true)
    {
      wattroff(Panel.winPANEL, COLOR_PAIR(CRT_get_color_pair(COLOR_WHITE, COLOR_BLACK)));
    }

    // Check for Colored Text
    if (PROP.COLORS_ON == true)
    {
      if (PROP.AUTO_COLOR == false)
      {
        wattroff(Panel.winPANEL, COLOR_PAIR(CRT_get_color_pair(PROP.BCOLOR, PROP.COLOR)));
      }
      else
      {
        wattroff(Panel.winPANEL, COLOR_PAIR(CRT_get_color_pair(PROP.BCOLOR, text_color_correction(PROP.BCOLOR))));
      }
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
//  Char_Graph Classes

bool Char_Graph::changed()
// Returns true if any of the properties have changed.
{
  return CHANGED;
}

void Char_Graph::redraw()
{
  CHANGED = true;
}

void Char_Graph::set_value(float Value, int Min, int Max, long tmeFrame_Time)
{
  if (VALUE != Value || PROP.MIN != Min || PROP.MAX != Max)
  {
    VALUE = Value;
    PROP.MIN = Min;
    PROP.MAX = Max;
    
    CHANGED = true;
      
    if (PROP.UPDATE_INDICATION == true)
    {
      UPDATE_INDICATION_TIMER.ping_up(tmeFrame_Time, INDICATED_BLINK_TIME);
    }
  }
}

void Char_Graph::set_value(float Value, long tmeFrame_Time)
{
  set_value(Value, PROP.MIN, PROP.MAX, 0);
}

void Char_Graph::set_value(float Value)
{
  set_value(Value, PROP.MIN, PROP.MAX, 0);
}

void Char_Graph::clear()
{
  VALUE = 0;
  CHANGED = true;
}

void Char_Graph::draw(PANEL &Panel, bool Refresh, unsigned long tmeFrame_Time, int Zero_Color)
{
  if (PROP.UPDATE_INDICATION == true && UPDATE_INDICATION_TIMER.blip_moved(tmeFrame_Time) == true)
  {
    Refresh = true;
  }

  if (CHANGED == true || Refresh == true)
  {
    // Calculate
    int BColor = COLOR_BLACK;
    int Color = COLOR_WHITE;

    char scale = 'X';

    int pos = (int)(100 * ((VALUE - PROP.MIN) / (PROP.MAX - PROP.MIN)));

    int lower = pos % 33;

    // Character
    //    .,:;|o   

    if (lower == 0)
    {
      scale = ' ';
    }
    else if (lower >= 0 && lower < 7)
    {
      scale = '.';
    }
    else if (lower >= 7 && lower < 13)
    {
      scale = ',';
    }
    else if (lower >= 13 && lower < 20)
    {
      scale = ':';
    }
    else if (lower >= 20 && lower < 26)
    {
      scale = ';';
    }
    else if (lower >= 26)
    {
      scale = '|';
    }

    // Color

    if (PROP.ALT_COLORS == false)
    {
      if (VALUE == 0)
      {
        if (Zero_Color == -1)
        {
          BColor = COLOR_RED;
        }
        else
        {
          BColor = Zero_Color;
        }
        Color = COLOR_WHITE;
      }
      else if (pos >= 0 && pos < 33)
      {
        BColor = COLOR_RED;
        Color = COLOR_WHITE;
      }
      else if (pos >= 33 && pos < 66)
      {
        BColor = COLOR_YELLOW;
        Color = COLOR_BLACK;
      }
      else if (pos >= 66 && pos < 100)
      {
        BColor = COLOR_GREEN;
        Color = COLOR_WHITE;
      }
      else if (pos >= 100)
      {
        BColor = COLOR_GREEN;
        Color = COLOR_WHITE;
        scale = 'o';
      }
    }
    else
    {
      if (VALUE == 0)
      {
        if (Zero_Color == -1)
        {
          BColor = COLOR_BLUE;
        }
        else
        {
          BColor = Zero_Color;
        }

        Color = COLOR_WHITE;
      }
      else if (pos >= 0 && pos < 33)
      {
        BColor = COLOR_GREEN;
        Color = COLOR_WHITE;
      }
      else if (pos >= 33 && pos < 66)
      {
        BColor = COLOR_YELLOW;
        Color = COLOR_BLACK;
      }
      else if (pos >= 66 && pos < 100)
      {
        BColor = COLOR_RED;
        Color = COLOR_WHITE;
      }
      else if (pos >= 100)
      {
        BColor = COLOR_RED;
        Color = COLOR_WHITE;
        scale = 'o';
      }
    }
 
    // Draw

    wattron(Panel.winPANEL, COLOR_PAIR(CRT_get_color_pair(BColor, Color)));

    // Check for Blink
    if (PROP.UPDATE_INDICATION == true && UPDATE_INDICATION_TIMER.ping_down(tmeFrame_Time) == true)
    {
      wattron(Panel.winPANEL, COLOR_PAIR(CRT_get_color_pair(COLOR_WHITE, COLOR_BLACK)));
    }

    // Check for Text Modification
    mvwprintw(Panel.winPANEL, PROP.POSY, PROP.POSX, "%c", scale);  //print line. 

    // Check for Blink
    if (PROP.UPDATE_INDICATION == true && UPDATE_INDICATION_TIMER.ping_down(tmeFrame_Time) == true)
    {
      wattroff(Panel.winPANEL, COLOR_PAIR(CRT_get_color_pair(COLOR_WHITE, COLOR_BLACK)));
    }

    wattroff(Panel.winPANEL, COLOR_PAIR(CRT_get_color_pair(BColor, Color)));

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
  
void Char_Graph::draw(PANEL &Panel, bool Refresh, unsigned long tmeFrame_Time)
{
  draw(Panel, Refresh, tmeFrame_Time, -1);
}
  
void Char_Graph::draw(PANEL &Panel, bool Refresh)
{
  draw(Panel, Refresh, 0, -1);
}

// -------------------------------------------------------------------------------------
//  Text_Field_Multi_Line Classes

void Text_Field_Multi_Line::draw_all_lines(PANEL &Button_Panel, deque<string> &Lines, int SizeY, int PosY, int PosX)
{
  for (int pos = 0; pos < SizeY; pos++)
  {
    mvwprintw(Button_Panel.winPANEL, PosY + pos, PosX, line_create(PROP.SIZEX, ' ').c_str());   //clear line. 
    
    if (pos < Lines.size())
    {
      mvwprintw(Button_Panel.winPANEL, PosY + pos, PosX, Lines[pos].c_str());                    //print line. 
    }
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

      PROP.LABEL = Text;

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
            PROP.LABEL_MULTI_LINE.push_back(center_justify(PROP.SIZEX, line));
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

bool Text_Field_Multi_Line::draw(PANEL &Panel, bool Refresh, unsigned long tmeFrame_Time)
{
  bool ret_was_redrawn = false;

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
      wattron(Panel.winPANEL, COLOR_PAIR(CRT_get_color_pair(PROP.COLOR, PROP.BCOLOR)));
    }

    // Check for Text Modification
    draw_all_lines(Panel, PROP.LABEL_MULTI_LINE, PROP.SIZEY, PROP.POSY, PROP.POSX);

    // Check for Blink
    if (PROP.UPDATE_INDICATION == true && UPDATE_INDICATION_TIMER.ping_down(tmeFrame_Time) == true)
    {
      wattroff(Panel.winPANEL, COLOR_PAIR(CRT_get_color_pair(PROP.COLOR, PROP.BCOLOR)));
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

    ret_was_redrawn = true;

    Panel.changed_on();
  }

  return ret_was_redrawn;
}

bool Text_Field_Multi_Line::draw(PANEL &Panel, bool Refresh)
{
  bool ret_was_redrawn = draw(Panel, Refresh, 0);
  return ret_was_redrawn;
}

// -------------------------------------------------------------------------------------
/*
//  Rotating_Text_Field Classes  
bool Rotating_Text_Field::changed()
{
  return false;
}

bool Rotating_Text_Field::has_blank()
{
  return false;
}

void Rotating_Text_Field::redraw()
{
  
}

void Rotating_Text_Field::set_inverse(bool Inverse)
{
  
}

void Rotating_Text_Field::set_text(string Text, unsigned long tmeFrame_Time)
{
  
}

void Rotating_Text_Field::set_text(string Text)
{
  
}

void Rotating_Text_Field::clear()
{
  
}

void Rotating_Text_Field::set_color(int Background_Color, int Color)
{
  
}

void Rotating_Text_Field::draw(PANEL &Panel, bool Refresh, unsigned long tmeFrame_Time)
{
  
}

void Rotating_Text_Field::draw(PANEL &Panel, bool Refresh)
{
  
}
*/

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
  return CHANGED;
}

bool Title_Bar::draw(bool Refresh)
// Draw the text_box on the screen if the value has changed or if  
//  the Refresh parameter is true.
{
  if (CHANGED == true || Refresh == true)
  {
    if (PROP.LABEL != TITLE.PROP.LABEL)
    {
      TITLE.set_text(PROP.LABEL);
    }

    TITLE.draw(TITLE_BAR_PANEL, Refresh);

    CHANGED = false;
  }
  
  return TITLE_BAR_PANEL.draw(Refresh);
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

void Text_Box::create()
// Define and behavior.  
// Like set but leaves off position and size details.
// Does not create window.

{
  TEXT_BOX_PANEL.PROP.SIZEY = PROP.SIZEY;
  TEXT_BOX_PANEL.PROP.SIZEX = PROP.SIZEX; 
  TEXT_BOX_PANEL.PROP.POSY = PROP.POSY;
  TEXT_BOX_PANEL.PROP.POSX = PROP.POSX;

  TEXT_BOX_PANEL.set_color(PROP.BCOLOR, PROP.COLOR);
  
  TEXT_BOX_PANEL.create();

  bool CHANGED = true;
}

bool Text_Box::changed()
// Returns true if any of the properties have changed.
{
  return CHANGED;
}

void Text_Box::draw(bool Refresh)
// Draw the text_box on the screen if the value has changed or if  
//  the Refresh parameter is true.
{
  if (CHANGED == true || Refresh == true)
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
      wmove(TEXT_BOX_PANEL.winPANEL, yCurPos, 0);  //move cursor to next line to print or clear.
      wclrtoeol(TEXT_BOX_PANEL.winPANEL);            // clear line befor printing to it.

      // If line doesnt fit, put ">>" on the end of whats visible.
      if (line.strLine.size() > PROP.SIZEX)
      {
        string truncated_line = line.strLine.substr(0, PROP.SIZEX -2) + ">>";
        mvwprintw(TEXT_BOX_PANEL.winPANEL, yCurPos, 0, "%s", truncated_line.c_str());  //print line.
      }
      else
      {
        mvwprintw(TEXT_BOX_PANEL.winPANEL, yCurPos, 0, "%s", line.strLine.c_str());  //print line.
      }
    }

    CHANGED = false;
    
    wrefresh(TEXT_BOX_PANEL.winPANEL);
  }
}

void Text_Box::add_line(unsigned long Time_Milli, string Text)
// Add a line of text to Text_Box.
{
  PROP.LINES.add(Time_Milli, Text);
  CHANGED = true;
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
  if (PROP.BCOLOR != Background_Color || PROP.COLOR != Color)
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

void Button::set_do_not_draw(bool Do_Not_Draw)
{
  if (PROP.DO_NOT_DRAW != Do_Not_Draw)
  {
    PROP.DO_NOT_DRAW = Do_Not_Draw;

    PROP.CHANGED = true;
  }
}

bool Button::draw(bool Refresh, unsigned long tmeFrame_Time)
// Draw the button on the screen if the value has changed or if  
//  the Refresh parameter is true.
{
  bool ret_redrawn = false;

  // Refresh if time active.
  if (BUTTON_PRESSED.blip_moved(tmeFrame_Time) == true)
  {
    Refresh = true;
  }

  if (PROP.CHANGED == true || Refresh == true)
  {
    LINES.set_text(PROP.LABEL);
    LINES.redraw();
    
    //Set Color, Set Reverse if On, Draw Sencils for Buttons
    if (PROP.ENABLED == true && PROP.HIDDEN == false && 
                        (PROP.TYPE == 0 || PROP.TYPE == 1 || PROP.TYPE == 2))
    {
      if (PROP.VALUE == 0 && BUTTON_PRESSED.ping_down(tmeFrame_Time) == false)
      // Dont reverse the colors if Button off or no ping
      {
        // Start by setting button color.
        if (PROP.AUTO_COLOR == false)
        {
          BUTTON_PANEL.set_color(PROP.BCOLOR, PROP.COLOR);
        }
        else
        {
          BUTTON_PANEL.set_color(PROP.BCOLOR, text_color_correction(PROP.BCOLOR));
        }
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

    // Dont draw refresh pannel if do not draw
    if (PROP.DO_NOT_DRAW == false)
    {
      BUTTON_PANEL.draw(Refresh);
    }
    
    // If the button is simple click, reset its value
    if (PROP.TYPE == 0 && PROP.VALUE == 1)
    {
      PROP.VALUE = 0;
      BUTTON_PRESSED.ping_up(tmeFrame_Time, VISIBLE_UPATE_TIME);
    }

    PROP.CHANGED = false;
    ret_redrawn = true;
  }

  return ret_redrawn;
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

void Button_Zone_Manager::click_advance(int Position)
{
  if (BUTTONS[Position].PROP.TYPE == 0 || BUTTONS[Position].PROP.TYPE == 1)
  {
    BUTTONS[Position].advance();
  }
  else if (BUTTONS[Position].PROP.TYPE == 2)
  {
    for (int pos = 0; pos < BUTTONS.size(); pos++)
    {
      BUTTONS[pos].PROP.VALUE = 0;
      BUTTONS[pos].PROP.CHANGED = true;
    }
    BUTTONS[Position].PROP.VALUE = 1;
  }
}

void Button_Zone_Manager::click_advance(string Name)
{
  click_advance(get_pos(Name));
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
  BUTTONS.push_back(tmp_button);
}

bool Button_Zone_Manager::draw(bool Refresh, unsigned long tmeFrame_Time)
{
  TRUTH_CATCH ret_redrawn;

  if (BUTTONS.size() >0)
  {
    for (int pos = 0; pos < BUTTONS.size(); pos++)
    {
      ret_redrawn.catch_truth(BUTTONS[pos].draw(Refresh, tmeFrame_Time));
    }
  }
  
  return ret_redrawn.has_truth();
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

void Button_Zone_Manager::set_do_not_draw(int Id, bool Do_Not_Draw)
// Change Property by Name.
{
  int pos = get_pos(Id);

  if (pos > -1)
  {
    BUTTONS[pos].set_do_not_draw(Do_Not_Draw);
  }
}

void Button_Zone_Manager::set_do_not_draw(string Name, bool Do_Not_Draw)
// Change Property by Name.
{
  int pos = get_pos(Name);

  if (pos > -1)
  {
    BUTTONS[pos].set_do_not_draw(Do_Not_Draw);
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
      BUTTONS[pos].PROP.CLICKED = false;
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

string Button_Zone_Manager::get_name_of_button_with_value(int Value)
{
  string ret_string = "";
  for (int pos = 0; pos < BUTTONS.size(); pos++)
  {
    if (BUTTONS[pos].PROP.VALUE == Value)
    {
      ret_string = BUTTONS[pos].PROP.NAME;
    }
  }
  return ret_string;
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

int BAR::get_marker_pos(int Value)
// calculate the size of the fill bar with respects to full bar size.
{
  int pos = abs((PROP.BAR_SIZE) * Value / PROP.MAX_VALUE);

  // Check bounds
  if (pos > PROP.BAR_SIZE - 1)
  {
    pos = PROP.BAR_SIZE - 1;
  }

  return pos;
}

void BAR::print_marker(WINDOW *winWindow, int Ypos, int Xpos, int value)
// Draw marker at value on guage.
//  Draws > if exceeding max of guage size.
//  Draws < if exceeding min of guage size.
{
  char marker = PROP.INDICATOR_CHARACTER;
  
  if (value > PROP.MAX_VALUE)
  {
    marker = '>';
  }
  else if (value < PROP.MIN_VALUE)
  {
    marker = '<';
  }

  mvwprintw(winWindow, Ypos, Xpos + get_marker_pos(value), "%c", marker);
}

void BAR::print_min_max_filler(WINDOW *winWindow, int Ypos, int Xpos, int min, int max)
// Draw marker at value on guage.
//  Draws > if exceeding max of guage size.
//  Draws < if exceeding min of guage size.
{
  string fill_bar = "";
  int start = 0;
  int end = 0;
  int lenght = 0;

  // Keep within range
  if (min < PROP.MIN_VALUE)
  {
    start = 0;
  }
  else
  {
    start = get_marker_pos(min);
  }

  if (max > PROP.MAX_VALUE)
  {
    end = PROP.BAR_SIZE - 1;
  }
  else
  {
    end = get_marker_pos(max);
  }

  // Calculate Size.
  lenght = end - start + 1;
  
  // Draw Bar
  if (lenght > 0)
  {
    fill_bar.resize(lenght, ':');
    mvwprintw(winWindow, Ypos, Xpos + start, "%s", fill_bar.c_str());    
  }
}

void BAR::update(int Value, unsigned long tmeFrame_Time)
{
  if (PROP.VALUE != Value || PROP.MIN_MAX == true)
  {
    PROP.VALUE = Value;

    if (PROP.MIN_MAX == true)
    {
      MIN_MAX_HISTORY.put_value(Value, tmeFrame_Time);
    }

    CHANGED = true;
  }
}

void BAR::set_color(int Background_Color, int Color)
{
  if (PROP.BCOLOR != Background_Color || PROP.COLOR != Color)
  {
    PROP.BCOLOR = Background_Color;
    PROP.COLOR = Color;

    CHANGED = true;    
  }
}

bool BAR::draw(PANEL &Panel, bool Refresh)
{
  bool ret_redrawn = false;

  string label = "";

  string bar = "";
  string fill = "";
  int marker_pos = 0;
  int bar_min = 0;
  int bar_max = 0;

  // Color Management Variables
  int bar_color = 0;
  int indicaor_background_color = 0;

  if (CHANGED == true || Refresh == true)
  {
    if (PROP.COLORS_ON == true)
    {
      wattron(Panel.winPANEL, COLOR_PAIR(CRT_get_color_pair(PROP.BCOLOR, PROP.COLOR)));
    }

    // Prepare Colors
    if (PROP.COLORS_ON == true)
    {
      // Alert background color if value is negative
      if (PROP.VALUE >= PROP.MIN_VALUE && PROP.VALUE <= PROP.MAX_VALUE)
      {
        bar_color = PROP.COLOR_BAR_BACK;
      }
      else
      {
        bar_color = PROP.COLOR_MARKER_LIMIT;
      }

      // Prepare background colors for indicators
      if (PROP.MIN_MAX_FILLER == true)
      {
        indicaor_background_color = PROP.MIN_MAX_FILLER_BCOLOR;
      }
      else
      {
        indicaor_background_color = PROP.COLOR_BAR_BACK;
      }
    }

    // Print Label and Bar.
    if (PROP.LABEL.size() < PROP.LABEL_SIZE)
    {
      label = label.append(PROP.LABEL_SIZE - PROP.LABEL.size(), ' ') + PROP.LABEL;
    }
    else
    {
      label = PROP.LABEL;
    }

    mvwprintw(Panel.winPANEL, PROP.POSY, PROP.POSX, "%s", label.c_str());

    if (PROP.BRACKET_END_CAPS == true)
    {  
      // Print Bar Start "[""
      mvwprintw(Panel.winPANEL, PROP.POSY, PROP.POSX + PROP.LABEL_SIZE, "[");
      
      // Print Bar End "]""
      mvwprintw(Panel.winPANEL, PROP.POSY, PROP.POSX + PROP.LABEL_SIZE + PROP.BAR_SIZE +1 , "]");
    }

    // Create empty bar
    bar = bar.append(PROP.BAR_SIZE, ' ');
  
    // Bar Marker Position
    marker_pos = get_marker_pos(PROP.VALUE);

    if (PROP.COLORS_ON == true)
    {
      // Set Panel Color
      wattroff(Panel.winPANEL, COLOR_PAIR(CRT_get_color_pair(PROP.BCOLOR, PROP.COLOR)));
    }

    // Clear Bar Background
    if (PROP.COLORS_ON == true)
    {
      wattron(Panel.winPANEL, COLOR_PAIR(CRT_get_color_pair(bar_color, PROP.COLOR_BAR)));
    }

    mvwprintw(Panel.winPANEL, PROP.POSY, PROP.POSX + PROP.LABEL_SIZE +1, "%s", bar.c_str());

    if (PROP.COLORS_ON == true)
    {
      wattroff(Panel.winPANEL, COLOR_PAIR(CRT_get_color_pair(bar_color, PROP.COLOR_BAR)));
    }

    // Min Max filler bar.
    if (PROP.MIN_MAX_FILLER == true)
    {
      if (PROP.PROGRESS_BAR == true)
      {
        bar_min = 0;
        bar_max = PROP.VALUE;
      }
      else if (PROP.GUAGE_BAR == true)
      {
        bar_min = MIN_MAX_HISTORY.min();
        bar_max = MIN_MAX_HISTORY.max();
      }

      // Change background color to cooperate with marker limit background if color is on
      if (PROP.COLORS_ON == true)
      {
        if (PROP.VALUE > PROP.MAX_VALUE || PROP.VALUE < PROP.MIN_VALUE)
        {
          wattron(Panel.winPANEL, COLOR_PAIR(CRT_get_color_pair(PROP.COLOR_MARKER_LIMIT, PROP.MIN_MAX_FILLER_COLOR)));
        }
        else
        {
          wattron(Panel.winPANEL, COLOR_PAIR(CRT_get_color_pair(indicaor_background_color, PROP.MIN_MAX_FILLER_COLOR)));
        }
      }

      print_min_max_filler(Panel.winPANEL, PROP.POSY, PROP.POSX + PROP.LABEL_SIZE + 1, bar_min, bar_max);

      if (PROP.COLORS_ON == true)
      {
        if (PROP.VALUE > PROP.MAX_VALUE || PROP.VALUE < PROP.MIN_VALUE)
        {
          wattroff(Panel.winPANEL, COLOR_PAIR(CRT_get_color_pair(PROP.COLOR_MARKER_LIMIT, PROP.MIN_MAX_FILLER_COLOR)));
        }
        else
        {
          wattroff(Panel.winPANEL, COLOR_PAIR(CRT_get_color_pair(indicaor_background_color, PROP.MIN_MAX_FILLER_COLOR)));
        }
      }
    }

    // Print Min Max Indicators
    if (PROP.MIN_MAX_INDICATORS == true)
    {
      if (PROP.COLORS_ON == true)
      {
        wattron(Panel.winPANEL, COLOR_PAIR(CRT_get_color_pair(indicaor_background_color, PROP.COLOR_MARKER_LIMIT)));
      }

      print_marker(Panel.winPANEL, PROP.POSY, PROP.POSX + PROP.LABEL_SIZE + 1, MIN_MAX_HISTORY.min());
      print_marker(Panel.winPANEL, PROP.POSY, PROP.POSX + PROP.LABEL_SIZE + 1, MIN_MAX_HISTORY.max());

      if (PROP.COLORS_ON == true)
      {
        wattroff(Panel.winPANEL, COLOR_PAIR(CRT_get_color_pair(indicaor_background_color, PROP.COLOR_MARKER_LIMIT)));
      }
    }

    // Print Value Marker
    if (PROP.COLORS_ON == true)
    {
      wattron(Panel.winPANEL, COLOR_PAIR(CRT_get_color_pair(PROP.BCOLOR_MARKER, PROP.COLOR_MARKER)));
    }

    print_marker(Panel.winPANEL, PROP.POSY, PROP.POSX + PROP.LABEL_SIZE + 1, PROP.VALUE);

    if (PROP.COLORS_ON == true)
    {
      wattroff(Panel.winPANEL, COLOR_PAIR(CRT_get_color_pair(PROP.BCOLOR_MARKER, PROP.COLOR_MARKER)));
    }

    // If Print Min Max Values are on
    if (PROP.PRINT_MIN == true || PROP.PRINT_VALUE == true || PROP.PRINT_MAX == true)
    {
      int step = 0;

      if (PROP.COLORS_ON == true)
      {
        wattron(Panel.winPANEL, COLOR_PAIR(CRT_get_color_pair(PROP.BCOLOR, PROP.COLOR)));
      }

      if (PROP.PRINT_MIN == true)
      {
        mvwprintw(Panel.winPANEL, PROP.POSY, PROP.POSX + PROP.LABEL_SIZE + PROP.BAR_SIZE +3 + (step *4), " %3d ", MIN_MAX_HISTORY.min());
        step ++;
      }
      if (PROP.PRINT_VALUE == true)
      {
        mvwprintw(Panel.winPANEL, PROP.POSY, PROP.POSX + PROP.LABEL_SIZE + PROP.BAR_SIZE +3 + (step *4), " %3d ", PROP.VALUE);
        step ++;
      }
      if (PROP.PRINT_MAX == true)
      {
        mvwprintw(Panel.winPANEL, PROP.POSY, PROP.POSX + PROP.LABEL_SIZE + PROP.BAR_SIZE +3 + (step *4), " %3d ", MIN_MAX_HISTORY.max());
        step ++;
      }

      if (PROP.COLORS_ON == true)
      {
        wattroff(Panel.winPANEL, COLOR_PAIR(CRT_get_color_pair(PROP.BCOLOR, PROP.COLOR)));
      }
    }

    CHANGED = false;
    Panel.changed_on();
    ret_redrawn = true;
  }
  
  return ret_redrawn;
}

// ---------------------------------------------------------------------------------------
// Bar Classes

int CYBR_BAR::get_marker_pos(float Value)
// calculate the size of the fill bar with respects to full bar size.
{
  int pos = (int)abs(((float)PROP.BAR_SIZE) * Value / (float)PROP.MAX_VALUE);

  // Check bounds
  if (pos > PROP.BAR_SIZE - 1)
  {
    pos = PROP.BAR_SIZE - 1;
  }

  return pos;
}

void CYBR_BAR::print_marker(WINDOW *winWindow, int Ypos, int Xpos, int value)
// Draw marker at value on guage.
//  Draws > if exceeding max of guage size.
//  Draws < if exceeding min of guage size.
{
  char marker = PROP.INDICATOR_CHARACTER;
  
  if (value > PROP.MAX_VALUE)
  {
    marker = '>';
  }
  else if (value < PROP.MIN_VALUE)
  {
    marker = '<';
  }

  mvwprintw(winWindow, Ypos, Xpos + get_marker_pos(value), "%c", marker);
}

void CYBR_BAR::check_for_ejects(unsigned long tmeFrame_Time)
{
  if (SLICE_HISTORY.size() > 0)
  {
    if (tmeFrame_Time > SLICE_HISTORY.back().TIMESTAMP + PROP.TIME_SPAN)
    {
      JECTO_DAT = SLICE_HISTORY.back();
      JECTO_DAT.TIMESTAMP = tmeFrame_Time;

      if (JECTO_DAT.UPDATE_COUNT > 0)
      {
        JECTO_READY = true;
      }

      SLICE_HISTORY.pop_back();
    }
  }
}

void CYBR_BAR::update_cybr_slice(int Value, unsigned long tmeFrame_Time)
{
  if (SLICE_HISTORY.size() == 0)
  {
    CYBR_SLICE new_slice;
    SLICE_HISTORY.push_front(new_slice);
    SLICE_HISTORY.front().VAL.resize(PROP.BAR_SIZE);
    SLICE_HISTORY.front().TIMESTAMP = tmeFrame_Time;
  }
  else
  {
    check_for_ejects(tmeFrame_Time);

    if (tmeFrame_Time > SLICE_HISTORY.front().TIMESTAMP + (PROP.TIME_SPAN / MAX_SLICE_COUNT))
    {
      CYBR_SLICE new_slice;
      SLICE_HISTORY.push_front(new_slice);
      SLICE_HISTORY.front().VAL.resize(PROP.BAR_SIZE);
      SLICE_HISTORY.front().TIMESTAMP = tmeFrame_Time;
    }
  }

  // Not complete, not fully supporting minimum values
  if (Value >= PROP.MIN_VALUE && Value <= PROP.MAX_VALUE)
  {
    SLICE_HISTORY.front().VAL[Value]++;
  }
  SLICE_HISTORY.front().UPDATE_COUNT++;
}

void CYBR_BAR::create()
{
  SLICE_GRAPH.resize(PROP.BAR_SIZE);

  MIN_MAX_HISTORY.PROP.SLICES = 20;
  MIN_MAX_HISTORY.PROP.TIME_SPAN = PROP.TIME_SPAN;

  for (int pos = 0; pos < SLICE_GRAPH.size(); pos++)
  {
    SLICE_GRAPH[pos].PROP.POSY = PROP.POSY;
    SLICE_GRAPH[pos].PROP.POSX = PROP.POSX +1 + pos;
    SLICE_GRAPH[pos].PROP.ALT_COLORS = true;
  }

  CREATED = true;
}

void CYBR_BAR::update(float Value, unsigned long tmeFrame_Time)
{
  if (CREATED == true)
  {
    VALUE = Value;
    update_cybr_slice(get_marker_pos(VALUE), tmeFrame_Time);

    MIN_MAX_HISTORY.put_value(Value, tmeFrame_Time);

    CHANGED = true;
  }
}

void CYBR_BAR::update(int Value, unsigned long tmeFrame_Time)
{
  update((float)Value, tmeFrame_Time);
}

void CYBR_BAR::update_via_slice(CYBR_SLICE CYBR_Slice, unsigned long tmeFrame_Time)
{
  CYBR_SLICE new_slice = CYBR_Slice;

  // create new slice or merge with existing.
  if (SLICE_HISTORY.size() == 0)
  {
    SLICE_HISTORY.push_front(new_slice);
  }
  else
  {
    // merge to front slice or push new slice forward 
    if (tmeFrame_Time > SLICE_HISTORY.front().TIMESTAMP + (PROP.TIME_SPAN / MAX_SLICE_COUNT))
    {
      SLICE_HISTORY.push_front(new_slice);
    }
    else
    {
      for (int pos = 0; pos < SLICE_HISTORY.front().VAL.size(); pos ++)
      {
        SLICE_HISTORY.front().VAL[pos] = SLICE_HISTORY.front().VAL[pos] + new_slice.VAL[pos];
      }
      SLICE_HISTORY.front().UPDATE_COUNT = SLICE_HISTORY.front().UPDATE_COUNT + new_slice.UPDATE_COUNT;
    }
  }

  check_for_ejects(tmeFrame_Time);

  CHANGED = true;
}

bool CYBR_BAR::jecto_ready()
{
  return JECTO_READY;
}

CYBR_SLICE CYBR_BAR::jecto()
{
  JECTO_READY = false;
  return JECTO_DAT;
}

bool CYBR_BAR::draw(PANEL &Panel, bool Refresh, unsigned long tmeFrame_Time)
{
  bool ret_redrawn = false;

  if (CHANGED == true || Refresh == true)
  {
    if (PROP.BRACKET_END_CAPS == true)
    {  
      // Print Bar Start "[""
      mvwprintw(Panel.winPANEL, PROP.POSY, PROP.POSX, "[");
      
      // Print Bar End "]""
      mvwprintw(Panel.winPANEL, PROP.POSY, PROP.POSX + PROP.BAR_SIZE +1 , "]");
    }

    // get update_count of slices
    int update_count = 0;
    int slice_graph_max_value = 0;

    for (int slice = 0; slice < SLICE_HISTORY.size(); slice++)
    {
      update_count = update_count + SLICE_HISTORY[slice].UPDATE_COUNT;
    }

    if (update_count > 0)
    {
      // values of slices
      for(int pos = 0; pos < PROP.BAR_SIZE; pos ++)
      {
        float value = 0;
        int value_total = 0;

        for (int slice = 0; slice < SLICE_HISTORY.size(); slice++)
        {
          value_total = value_total + SLICE_HISTORY[slice].VAL[pos];
        }

        value = (float)(value_total * 100) / (float)update_count;

        // Adjust the graph max value to make sure small values arent de-exposed.
        if (value > slice_graph_max_value)
        {
          slice_graph_max_value = value;
        }

        SLICE_GRAPH[pos].set_value(value, tmeFrame_Time);
      }
    }

    for(int pos = 0; pos < PROP.BAR_SIZE; pos ++)
    {
      SLICE_GRAPH[pos].PROP.MAX = slice_graph_max_value;

      if ((VALUE < PROP.MIN_VALUE || VALUE > PROP.MAX_VALUE) || 
          (PROP.PROGESS_BAR == true && pos < get_marker_pos(VALUE)))
      {
        SLICE_GRAPH[pos].draw(Panel, true, tmeFrame_Time, PROP.COLOR_MARKER_LIMIT);
      }
      else
      {
        SLICE_GRAPH[pos].draw(Panel, true, tmeFrame_Time, PROP.COLOR_BAR_BACK);
      }
    }

    // Print Value Marker
    if (PROP.JECT == false)
    {
      wattron(Panel.winPANEL, COLOR_PAIR(CRT_get_color_pair(PROP.BCOLOR_MARKER, PROP.COLOR_MARKER)));
      print_marker(Panel.winPANEL, PROP.POSY, PROP.POSX + 1, VALUE);
      wattroff(Panel.winPANEL, COLOR_PAIR(CRT_get_color_pair(PROP.BCOLOR_MARKER, PROP.COLOR_MARKER)));
    }

    Panel.changed_on();
    ret_redrawn = true;
    
  }

  CHANGED = false;
  return ret_redrawn;
}


// ---------------------------------------------------------------------------------------
// Keyboard Classes



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