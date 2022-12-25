// ***************************************************************************************
// *size
// *    Core       | Everything within this document is proprietary to Core Dynamics.
// *    Dynamics   | Any unauthorized duplication will be subject to prosecution.
// *
// *    Department : (R+D)^2                        Name: gadgets_radio.cpp
// *       Sub Dept: Programming
// *    Location ID: 856-45B
// *                                                      (c) 2856 - 2858 Core Dynamics
// ***************************************************************************************

#include "gadgets_radio.h"

// -------------------------------------------------------------------------------------
//  ADS-B Classes

int ADS_B_List_Box::get_first_empty_pos()
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

int ADS_B_List_Box::get_first_pos_with_no_data()
{
  int return_int = -1;
  for(int x=0; (x < AIRCRAFT_INDEX_LIST.size()) && (return_int == -1); x++)
  {
    if(AIRCRAFT_INDEX_LIST[x].DATA_COUNT == 0)
    {
      return_int = x;
    }
  }
  return return_int;
}

int ADS_B_List_Box::find_HEX(string Hex)
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

void ADS_B_List_Box::organize_index()
// Move items with data and off screen to first empty pos
{
  if(AIRCRAFT_INDEX_LIST.size() > PROP.SIZEY -2 - AIRCRAFT_INDEX_LIST_ALERT_COUNT_GUIDE)
  {
    // First Loop to fill empty positions
    for(int pos = PROP.SIZEY -2; pos < AIRCRAFT_INDEX_LIST.size(); pos++)
    {
      if(AIRCRAFT_INDEX_LIST[pos].DATA_COUNT > 0)
      {
        int first_empty = get_first_empty_pos();
        if(first_empty >= 0 && first_empty < PROP.SIZEY)
        {
          // move position and blank old postion
          AIRCRAFT_INDEX_LIST[first_empty] = AIRCRAFT_INDEX_LIST[pos];

          AIRCRAFT_INDEX_INFORMATION blank_index;
          AIRCRAFT_INDEX_LIST[pos] = blank_index;
        }
      }
    }

    // Second loop to swap positions of no data.
    for(int pos = PROP.SIZEY -2; pos < AIRCRAFT_INDEX_LIST.size(); pos++)
    {
      if(AIRCRAFT_INDEX_LIST[pos].DATA_COUNT > 0)
      {
        int first_empty = get_first_pos_with_no_data();
        if(first_empty >= 0 && first_empty < PROP.SIZEY)
        {
          // swap positions
          AIRCRAFT_INDEX_INFORMATION no_data_index = AIRCRAFT_INDEX_LIST[first_empty];
          AIRCRAFT_INDEX_LIST[first_empty] = AIRCRAFT_INDEX_LIST[pos];
          AIRCRAFT_INDEX_LIST[pos] = no_data_index;
        }
      }
    }
  }
}

void ADS_B_List_Box::sort_index()
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
  AIRCRAFT_INDEX_LIST_ALERT_COUNT_GUIDE = 0;
  
  for(int x=0; x < AIRCRAFT_INDEX_LIST.size(); x++)
  {
    // Count the Alerts for display guide.
    if (PROP.VALUE.AIRCRAFTS[AIRCRAFT_INDEX_LIST[x].POSITION].alert() == true)
    {
      if(PROP.VALUE.AIRCRAFTS[AIRCRAFT_INDEX_LIST[x].POSITION].ALERT_LIST.size() > AIRCRAFT_INDEX_LIST[x].SIZE)
      {
        AIRCRAFT_INDEX_LIST[x].SIZE = PROP.VALUE.AIRCRAFTS[AIRCRAFT_INDEX_LIST[x].POSITION].ALERT_LIST.size();
      }

      AIRCRAFT_INDEX_LIST_ALERT_COUNT_GUIDE = 
        AIRCRAFT_INDEX_LIST_ALERT_COUNT_GUIDE + AIRCRAFT_INDEX_LIST[x].SIZE;
    }

    // Erase data on non updated.~
    if(AIRCRAFT_INDEX_LIST[x].UPDATED == false)
    {
      AIRCRAFT_INDEX_LIST[x].HEX = "";
      AIRCRAFT_INDEX_LIST[x].SIZE = 0;
    }
  }
}

void ADS_B_List_Box::clear_line(int &yCurPos, int &xCurPos)
// Clear window line at y Cursor Pos and resets x Cursor Pos to 0.
{
  wmove(ADS_B_List_Box, yCurPos, 0);  //move cursor to next line to print or clear.
  wclrtoeol(ADS_B_List_Box);            // clear line befor printing to it.
  xCurPos = 0;
}

void ADS_B_List_Box::print_to_line(int &yCurPos, int &xCurPos, int Size, string Text, int Color_Pair)
{
  
  // Turn On Color
  wattron(ADS_B_List_Box, COLOR_PAIR(Color_Pair));

  // Print Line
  mvwprintw(ADS_B_List_Box, yCurPos, xCurPos, "%s", Text.c_str());

  // Turn Off Color
  wattroff(ADS_B_List_Box, COLOR_PAIR(Color_Pair));

  xCurPos = xCurPos + Size;
}

void ADS_B_List_Box::dsp_text(int &yCurPos, int &xCurPos, int Size, STRING_STRING &Text, int Text_Color, bool Inverse_Colors, int Color_Value, 
                int Color_Scale_Type, int Level_0, int Level_1, int Level_2, int Level_3, int Level_4)
{
  int color_pair = 0;
  int background_color = 0;

  string display_text = "";

  if(Text.conversion_success() == true)
  {
    if (Color_Scale_Type == LEDGEND_OFF)
    {
      background_color = Level_0;
    }
    else if (Color_Scale_Type == LEDGEND_RANGE)
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

  if(Inverse_Colors == true)
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

// Scale Types:
//  0 = LEDGEND_OFF;
//  1 = LEDGEND_RANGE   - Non Zero Green
//  2 = LEDGEND_SCALER  - Zero Green

void ADS_B_List_Box::dsp_intg(int &yCurPos, int &xCurPos, int Size, STRING_INT &Text, float Alt_Value, bool Alt_Success, int Text_Color, bool Inverse_Colors, 
                int Color_Scale_Type, int Level_0, int Level_1, int Level_2, int Level_3, int Level_4)
{
  int color_pair = 0;
  int background_color = 0;

  string display_text = "";

  if(Alt_Success == true)
  {
    if (Color_Scale_Type == LEDGEND_OFF)
    {
      background_color = Level_0;
    }
    else if (Color_Scale_Type == LEDGEND_RANGE)
    {
      background_color = color_range(Alt_Value, Level_0, Level_1, Level_2, Level_3, Level_4);
    }
    else // Color_Scale_Type == 2
    {
      background_color = color_scale(Alt_Value, Level_0, Level_1, Level_2, Level_3, Level_4);
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

  if(Inverse_Colors == true)
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

void ADS_B_List_Box::dsp_intg(int &yCurPos, int &xCurPos, int Size, STRING_INT &Text, int Text_Color, bool Inverse_Colors, 
                int Color_Scale_Type, int Level_0, int Level_1, int Level_2, int Level_3, int Level_4)
{
  if (Text.conversion_success() == true)
  {
    dsp_intg(yCurPos, xCurPos, Size, Text, ((float)Text.get_int_value()), Text.conversion_success(), Text_Color, Inverse_Colors, Color_Scale_Type, Level_0, Level_1, Level_2, Level_3, Level_4);
  }
  else
  {
    dsp_intg(yCurPos, xCurPos, Size, Text, 0, false, Text_Color, Inverse_Colors, Color_Scale_Type, Level_0, Level_1, Level_2, Level_3, Level_4);
  }
}

void ADS_B_List_Box::dsp_floa(int &yCurPos, int &xCurPos, int Size, STRING_FLOAT &Text, float Alt_Value, bool Alt_Success, int Text_Color, bool Inverse_Colors, 
                int Color_Scale_Type, int Level_0, int Level_1, int Level_2, int Level_3, int Level_4)
{
  int color_pair = 0;
  int background_color = 0;

  string display_text = "";

  if(Alt_Success == true)
  {
    if (Color_Scale_Type == LEDGEND_OFF)
    {
      background_color = Level_0;
    }
    else if (Color_Scale_Type == LEDGEND_RANGE)
    {
      background_color = color_range(Alt_Value, Level_0, Level_1, Level_2, Level_3, Level_4);
    }
    else // Color_Scale_Type == 2
    {
      background_color = color_scale(Alt_Value, Level_0, Level_1, Level_2, Level_3, Level_4);
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

  if(Inverse_Colors == true)
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

void ADS_B_List_Box::dsp_floa(int &yCurPos, int &xCurPos, int Size, STRING_FLOAT &Text, int Text_Color, bool Inverse_Colors, 
              int Color_Scale_Type, int Level_0, int Level_1, int Level_2, int Level_3, int Level_4)
{
  if (Text.conversion_success() == true)
  {
    dsp_floa(yCurPos, xCurPos, Size, Text, Text.get_float_value(), Text.conversion_success(), Text_Color, Inverse_Colors, Color_Scale_Type, Level_0, Level_1, Level_2, Level_3, Level_4);
  }
  else
  {
    dsp_floa(yCurPos, xCurPos, Size, Text, 0, false, Text_Color, Inverse_Colors, Color_Scale_Type, Level_0, Level_1, Level_2, Level_3, Level_4);
  }
}

void ADS_B_List_Box::modify(int id, string name, string label, int type, int color, int bcolor)
// Changes all properties
{
  PROP.ID = id;
  PROP.NAME = name;
  PROP.LABEL = label;

  PROP.TYPE = type;
  PROP.COLOR = color;

  PROP.CHANGED = true;
}

void ADS_B_List_Box::create(int id, string name, string label, int type, int color, int bcolor)
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

void ADS_B_List_Box::move_resize(int posY, int posX, int sizeY, int sizeX)
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

bool ADS_B_List_Box::changed()
// Returns true if any of the properties have changed.
{
  return PROP.CHANGED;
}

void ADS_B_List_Box::draw(bool Refresh)
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
    int position_color = COLOR_WHITE;
    bool inverse_colors = false;

    if(IS_ACTIVE == true)
    {
      tmp_line = "Messages: " + linemerge_right_justify(6, "      ", PROP.VALUE.MESSAGES.get_str_value()) + 
                  "   " + to_string(PROP.VALUE.CONVERTED_TIME.get_year()) + 
                  "-" + linemerge_right_justify(2, "00", to_string(PROP.VALUE.CONVERTED_TIME.get_month())) + 
                  "-" + linemerge_right_justify(2, "00", to_string(PROP.VALUE.CONVERTED_TIME.get_day())) + 
                  " " + linemerge_right_justify(2, "00", to_string(PROP.VALUE.CONVERTED_TIME.get_hour())) + 
                  ":" + linemerge_right_justify(2, "00", to_string(PROP.VALUE.CONVERTED_TIME.get_minute())) + 
                  ":" + linemerge_right_justify(2, "00", to_string(PROP.VALUE.CONVERTED_TIME.get_second())) + 
                  "." + to_string(PROP.VALUE.CONVERTED_TIME.get_deciseconds()) + 
                  "   Aircraft: " + to_string(PROP.VALUE.AIRCRAFTS.size()) + 
                  "   Pos: " + to_string(PROP.VALUE.POSITIONED_AIRCRAFT)
                  ;
      
      wattron(ADS_B_List_Box, COLOR_PAIR(CRT_get_color_pair(COLOR_BLUE, COLOR_WHITE)));

      wmove(ADS_B_List_Box, yCurPos, 0);  //move cursor to next line to print or clear.
      wclrtoeol(ADS_B_List_Box);            // clear line befor printing to it.
      mvwprintw(ADS_B_List_Box, yCurPos, 0, "%s", left_justify(PROP.SIZEX, tmp_line).c_str());
      yCurPos++;

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

      print_to_line(yCurPos, xCurPos, 8, right_justify(8, "GS"), CRT_get_color_pair(COLOR_BLUE, COLOR_WHITE));
      print_to_line(yCurPos, xCurPos, 7, right_justify(7, "TRACK"), CRT_get_color_pair(COLOR_BLUE, COLOR_WHITE));
      print_to_line(yCurPos, xCurPos, 7, right_justify(7, "V RT"), CRT_get_color_pair(COLOR_BLUE, COLOR_WHITE));
      print_to_line(yCurPos, xCurPos, 8, right_justify(8, "ALT"), CRT_get_color_pair(COLOR_BLUE, COLOR_WHITE));

      print_to_line(yCurPos, xCurPos, space_size, right_justify(space_size, ""), CRT_get_color_pair(COLOR_BLUE, COLOR_WHITE));

      print_to_line(yCurPos, xCurPos, 6, right_justify(6, "SEEN"), CRT_get_color_pair(COLOR_BLUE, COLOR_WHITE));
      print_to_line(yCurPos, xCurPos, 8, right_justify(8, "SN POS"), CRT_get_color_pair(COLOR_BLUE, COLOR_WHITE));
      print_to_line(yCurPos, xCurPos, 6, right_justify(6, "MSGS"), CRT_get_color_pair(COLOR_BLUE, COLOR_WHITE));
      print_to_line(yCurPos, xCurPos, 7, right_justify(7, "RSSI"), CRT_get_color_pair(COLOR_BLUE, COLOR_WHITE));
      
      wattroff(ADS_B_List_Box, COLOR_PAIR(CRT_get_color_pair(COLOR_BLUE, COLOR_WHITE)));

      yCurPos++;

      //----------------

      // Attempt to make sure anything with data will not be displayed off screen.
      organize_index();

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
              position_color = COLOR_WHITE;
              inverse_colors = true;
            }
            else
            {
              position_color = COLOR_GREEN;
              inverse_colors = true;
            }
        }
        else
        {
          position_color = COLOR_BLACK;
          inverse_colors = false;
        }

        // Scale Types:
        //  0 = LEDGEND_OFF;
        //  1 = LEDGEND_RANGE   - Non Zero Green
        //  2 = LEDGEND_SCALER  - Zero Green

        // LEDGEND_RANGE - Range Level
        // Magenta  Red  Yellow  Green  Blue  Cyan

        // LEDGEND_SCALER - Scale Level
        // Green  Yellow  Red  Magenta  Blue  Cyan
      
        // Print Aircraft Info Line
        clear_line(yCurPos, xCurPos);
        dsp_intg(yCurPos, xCurPos, 6, display_aircraft.SQUAWK, COLOR_BLACK, inverse_colors, LEDGEND_OFF, position_color, 0, 0, 0, 0);
        dsp_text(yCurPos, xCurPos, 9, display_aircraft.FLIGHT, COLOR_BLACK, inverse_colors, 0, LEDGEND_OFF, position_color, 2, 3, 4, 5);

        dsp_text(yCurPos, xCurPos, 3, blank_text, COLOR_BLACK, inverse_colors, 0, LEDGEND_OFF, COLOR_GREEN, 2, 3, 4, 5);

        dsp_floa(yCurPos, xCurPos, 8, display_aircraft.SPEED, COLOR_BLACK, inverse_colors, LEDGEND_RANGE, 60, 80, 100, 160, 600);
        dsp_floa(yCurPos, xCurPos, 7, display_aircraft.TRACK, COLOR_BLACK, inverse_colors, LEDGEND_OFF, COLOR_GREEN, 0, 0, 0, 0);
        dsp_intg(yCurPos, xCurPos, 7, display_aircraft.D_VERTICAL_RATE, display_aircraft.D_FLIGHT_ANGLE.get_float_value(), 
                  display_aircraft.D_FLIGHT_ANGLE.conversion_success(), COLOR_BLACK, inverse_colors, LEDGEND_SCALER, 2, 4, 6, 8, 10);
        dsp_intg(yCurPos, xCurPos, 8, display_aircraft.ALTITUDE, COLOR_BLACK, inverse_colors, LEDGEND_RANGE, 50, 500, 3000, 12000, 40000);

        dsp_text(yCurPos, xCurPos, space_size, blank_text, COLOR_BLACK, inverse_colors,  0, LEDGEND_OFF, COLOR_GREEN, 2, 3, 4, 5);

        dsp_floa(yCurPos, xCurPos, 6, display_aircraft.SEEN, COLOR_BLACK, inverse_colors, LEDGEND_SCALER, 10, 290, 298, 0, 0);
        dsp_floa(yCurPos, xCurPos, 8, display_aircraft.SEEN_POS, COLOR_BLACK, inverse_colors, LEDGEND_SCALER, 5, 60, 68, 299, 0);
        dsp_intg(yCurPos, xCurPos, 6, display_aircraft.MESSAGES, COLOR_BLACK, inverse_colors, LEDGEND_SCALER, 100, 5000, 12000, 20000, 40000);
        dsp_floa(yCurPos, xCurPos, 7, display_aircraft.RSSI, COLOR_BLACK, inverse_colors, LEDGEND_SCALER, 18, 30, 32, 34, 36);

        // Display alerts
        if(display_aircraft.alert() == true)
        {
          for (int alerts_pos = 0; alerts_pos < display_aircraft.ALERT_LIST.size(); alerts_pos++)
          {
            if (yCurPos < PROP.SIZEY)
            {
              yCurPos++;
              clear_line(yCurPos, xCurPos);
              
              int alert_color = 0;

              if (display_aircraft.ALERT_LIST[alerts_pos].ALERT_LEVEL == 1)
              {
                alert_color = COLOR_GREEN;
              }
              else if (display_aircraft.ALERT_LIST[alerts_pos].ALERT_LEVEL == 2)
              {
                alert_color = COLOR_YELLOW;
              }
              else
              {
                alert_color = COLOR_RED;
              }

              print_to_line(yCurPos, xCurPos, PROP.SIZEX, left_justify(PROP.SIZEX, display_aircraft.ALERT_LIST[alerts_pos].ALERT.c_str()), CRT_get_color_pair(alert_color, COLOR_BLACK));
            }
          }
        }

        // Display expired alert blank lines.
        if(AIRCRAFT_INDEX_LIST[y].SIZE > display_aircraft.ALERT_LIST.size())
        {
          for(int line = display_aircraft.ALERT_LIST.size(); line < AIRCRAFT_INDEX_LIST[y].SIZE; line++)
          {
            yCurPos++;
            clear_line(yCurPos, xCurPos);

            if(display_aircraft.data_count() >0)
            {
              print_to_line(yCurPos, xCurPos, PROP.SIZEX, left_justify(PROP.SIZEX, "  \\_____..."), CRT_get_color_pair(COLOR_GREEN, COLOR_BLACK));
            }
            else
            {
              print_to_line(yCurPos, xCurPos, PROP.SIZEX, left_justify(PROP.SIZEX, "  \\_____..."), CRT_get_color_pair(COLOR_BLACK, COLOR_GREEN));
            }
          }
        }

        yCurPos++;
      }
    }
    else  // Not Active
    {
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

void ADS_B_List_Box::update(system_data &sdSysData)
{
  // Get new list of Aircraft.
  PROP.VALUE = sdSysData.AIRCRAFT_COORD.DATA;
  IS_ACTIVE = sdSysData.AIRCRAFT_COORD.is_active();

  // Prepare list to display.
  sort_index();

  sdSysData.AIRCRAFT_COORD.DATA.CHANGED = false;

  PROP.CHANGED = true;
}


// -------------------------------------------------------------------------------------
//  ADSB_Channel Classes

string ADSB_Channel::compass_mini_top(float Heading)
{
  string return_str = ""; 

  if ((Heading >= 337.5 && Heading <= 360) || (Heading >= 0 && Heading < 22.5))
  {
    return_str = " | ";
  }
  else if (Heading >= 22.5 && Heading < 67.5)
  {
    return_str = "  /";
  }
  else if (Heading >= 67.5 && Heading < 112.5)
  {
    return_str = "  _";
  }
  else if (Heading >= 112.5 && Heading < 157.5)
  {
    return_str = "   ";
  }
  else if (Heading >= 157.5 && Heading < 202.5)
  {
    return_str = "   ";
  }
  else if (Heading >= 202.5 && Heading < 247.5)
  {
    return_str = "   ";
  }
  else if (Heading >= 247.5 && Heading < 292.5)
  {
    return_str = "_  ";
  }
  else if (Heading >= 292.5 && Heading < 337.5)
  {
    return_str = "\\  ";
  }
  else
    {
    return_str = "XX";
  }

  return return_str;
}

string ADSB_Channel::compass_mini_bottom(float Heading)
{
  string return_str = ""; 

  if ((Heading >= 337.5 && Heading <= 360) || (Heading >= 0 && Heading < 22.5))
  {
    return_str = "   ";
  }
  else if (Heading >= 22.5 && Heading < 67.5)
  {
    return_str = "   ";
  }
  else if (Heading >= 67.5 && Heading < 112.5)
  {
    return_str = "   ";
  }
  else if (Heading >= 112.5 && Heading < 157.5)
  {
    return_str = "  \\";
  }
  else if (Heading >= 157.5 && Heading < 202.5)
  {
    return_str = " | ";
  }
  else if (Heading >= 202.5 && Heading < 247.5)
  {
    return_str = "/  ";
  }
  else if (Heading >= 247.5 && Heading < 292.5)
  {
    return_str = "   ";
  }
  else if (Heading >= 292.5 && Heading < 337.5)
  {
    return_str = "   ";
  }
  else
    {
    return_str = "XX";
  }

  return return_str;
}

void ADSB_Channel::create()
// Define and behavior.  
// Like set but leaves off position and size details.
// Does not create window.
{
  // Create Gadget Window
  winADSB = newwin(PROP.SIZEY, PROP.SIZEX, PROP.POSY, PROP.POSX);

  //wborder(winFrequency,'|','|','-','-','+','+','+','+') ;
  wborder(winADSB,' ',' ',' ',' ',' ',' ',' ',' ') ;

  // Create Text Fields

  // Top Bar
  TOP_BAR.PROP.POSY = 0;
  TOP_BAR.PROP.POSX = 0;
  TOP_BAR.PROP.COLORS_ON = true;
  TOP_BAR.PROP.COLOR = COLOR_BLACK;
  TOP_BAR.PROP.BCOLOR = COLOR_BLACK;
  TOP_BAR.PROP.SIZEX = PROP.SIZEX;
  TOP_BAR.PROP.JUSTIFICATION_LEFT = true;

  // Flight
  FLIGHT.PROP.POSY = 0;
  FLIGHT.PROP.POSX = 1;
  FLIGHT.PROP.COLORS_ON = true;
  FLIGHT.PROP.COLOR = COLOR_BLACK;
  FLIGHT.PROP.BCOLOR = COLOR_BLACK;
  FLIGHT.PROP.SIZEX = 8;
  FLIGHT.PROP.DONT_BLANK = true;
  FLIGHT.PROP.JUSTIFICATION_LEFT = true;
  FLIGHT.PROP.UPDATE_INDICATION = true;

  // Squawk
  SQUAWK.PROP.POSY = 0;
  SQUAWK.PROP.POSX = 16;
  SQUAWK.PROP.COLORS_ON = true;
  SQUAWK.PROP.COLOR = COLOR_BLACK;
  SQUAWK.PROP.BCOLOR = COLOR_BLACK;
  SQUAWK.PROP.SIZEX = 4;
  SQUAWK.PROP.DONT_BLANK = true;
  SQUAWK.PROP.JUSTIFICATION_RIGHT = true;
  SQUAWK.PROP.UPDATE_INDICATION = true;

  // Altitude
  ALTITUDE.PROP.POSY = 1;
  ALTITUDE.PROP.POSX = 6;
  ALTITUDE.PROP.SIZEX = 6;
  ALTITUDE.PROP.DONT_BLANK = true;
  ALTITUDE.PROP.JUSTIFICATION_RIGHT = true;
  ALTITUDE.PROP.UPDATE_INDICATION = true;

  // Altitude Indicator
  ALTITUDE_IND.PROP.POSY = 1;
  ALTITUDE_IND.PROP.POSX = 12;
  ALTITUDE_IND.PROP.COLORS_ON = true;
  ALTITUDE_IND.PROP.COLOR = COLOR_BLACK;
  ALTITUDE_IND.PROP.BCOLOR = COLOR_BLACK;
  ALTITUDE_IND.PROP.SIZEX = 1;
  ALTITUDE_IND.PROP.DONT_BLANK = true;
  ALTITUDE_IND.PROP.JUSTIFICATION_LEFT = true;

  // Altitude Nav
  //NAV_ALTITUDE_MCP.PROP.LABEL = "nava";
  NAV_ALTITUDE_MCP.PROP.POSY = 2;
  NAV_ALTITUDE_MCP.PROP.POSX = 6;
  NAV_ALTITUDE_MCP.PROP.COLORS_ON = true;
  NAV_ALTITUDE_MCP.PROP.COLOR = COLOR_BLUE;
  NAV_ALTITUDE_MCP.PROP.BCOLOR = COLOR_BLACK;
  NAV_ALTITUDE_MCP.PROP.SIZEX = 6;
  NAV_ALTITUDE_MCP.PROP.DONT_BLANK = true;
  NAV_ALTITUDE_MCP.PROP.JUSTIFICATION_RIGHT = true;
  NAV_ALTITUDE_MCP.PROP.UPDATE_INDICATION = true;

  // Vertical Rate
  D_VERTICAL_RATE.PROP.POSY = 3;
  D_VERTICAL_RATE.PROP.POSX = 6;
  D_VERTICAL_RATE.PROP.SIZEX = 6;
  D_VERTICAL_RATE.PROP.DONT_BLANK = true;
  D_VERTICAL_RATE.PROP.JUSTIFICATION_RIGHT = true;
  D_VERTICAL_RATE.PROP.UPDATE_INDICATION = true;

  // Vertical Rate Indicator
  D_VERTICAL_RATE_IND.PROP.POSY = 3;
  D_VERTICAL_RATE_IND.PROP.POSX = 12;
  D_VERTICAL_RATE_IND.PROP.COLORS_ON = true;
  D_VERTICAL_RATE_IND.PROP.COLOR = COLOR_BLACK;
  D_VERTICAL_RATE_IND.PROP.BCOLOR = COLOR_BLACK;
  D_VERTICAL_RATE_IND.PROP.SIZEX = 1;
  D_VERTICAL_RATE_IND.PROP.DONT_BLANK = true;
  D_VERTICAL_RATE_IND.PROP.JUSTIFICATION_LEFT = true;

  // Speed
  SPEED.PROP.POSY = 1;
  SPEED.PROP.POSX = 1;
  SPEED.PROP.SIZEX = 5;
  SPEED.PROP.DONT_BLANK = true;
  SPEED.PROP.JUSTIFICATION_LEFT = true;
  SPEED.PROP.UPDATE_INDICATION = true;

  // Speed Indicator
  SPEED_IND.PROP.POSY = 1;
  SPEED_IND.PROP.POSX = 0;
  SPEED_IND.PROP.COLORS_ON = true;
  SPEED_IND.PROP.COLOR = COLOR_BLACK;
  SPEED_IND.PROP.BCOLOR = COLOR_BLACK;
  SPEED_IND.PROP.SIZEX = 1;
  SPEED_IND.PROP.DONT_BLANK = true;
  SPEED_IND.PROP.JUSTIFICATION_LEFT = true;

  // Track
  TRACK.PROP.POSY = 1;
  TRACK.PROP.POSX = 14;
  TRACK.PROP.SIZEX = 3;
  TRACK.PROP.DONT_BLANK = true;
  TRACK.PROP.JUSTIFICATION_RIGHT = true;
  TRACK.PROP.UPDATE_INDICATION = true;

  // Track Mini Compass
  TRACK_MINI_COMPASS_TOP.PROP.POSY = 2;
  TRACK_MINI_COMPASS_TOP.PROP.POSX = 14;
  TRACK_MINI_COMPASS_TOP.PROP.SIZEX = 3;
  TRACK_MINI_COMPASS_TOP.PROP.COLOR = COLOR_BLACK;
  TRACK_MINI_COMPASS_TOP.PROP.BCOLOR = COLOR_BLACK;
  TRACK_MINI_COMPASS_TOP.PROP.COLORS_ON = true;
  TRACK_MINI_COMPASS_TOP.PROP.JUSTIFICATION_LEFT = true;

  TRACK_MINI_COMPASS_BOTTOM.PROP.POSY = 3;
  TRACK_MINI_COMPASS_BOTTOM.PROP.POSX = 14;
  TRACK_MINI_COMPASS_BOTTOM.PROP.SIZEX = 3;
  TRACK_MINI_COMPASS_BOTTOM.PROP.COLOR = COLOR_BLACK;
  TRACK_MINI_COMPASS_BOTTOM.PROP.BCOLOR = COLOR_BLACK;
  TRACK_MINI_COMPASS_BOTTOM.PROP.COLORS_ON = true;
  TRACK_MINI_COMPASS_BOTTOM.PROP.JUSTIFICATION_LEFT = true;
  
  // Track Nav
  //NAV_HEADING.PROP.LABEL = "navt";
  NAV_HEADING.PROP.POSY = 1;
  NAV_HEADING.PROP.POSX = 18;
  NAV_HEADING.PROP.COLORS_ON = true;
  NAV_HEADING.PROP.COLOR = COLOR_BLUE;
  NAV_HEADING.PROP.BCOLOR = COLOR_BLACK;
  NAV_HEADING.PROP.SIZEX = 3;
  NAV_HEADING.PROP.DONT_BLANK = true;
  NAV_HEADING.PROP.JUSTIFICATION_LEFT = true;
  NAV_HEADING.PROP.UPDATE_INDICATION = true;

  // Track Nav Mini Compass
  NAV_HEADING_MINI_COMPASS_TOP.PROP.POSY = 2;
  NAV_HEADING_MINI_COMPASS_TOP.PROP.POSX = 18;
  NAV_HEADING_MINI_COMPASS_TOP.PROP.SIZEX = 3;
  NAV_HEADING_MINI_COMPASS_TOP.PROP.COLOR = COLOR_BLACK;
  NAV_HEADING_MINI_COMPASS_TOP.PROP.BCOLOR = COLOR_BLACK;
  NAV_HEADING_MINI_COMPASS_TOP.PROP.COLORS_ON = true;
  NAV_HEADING_MINI_COMPASS_TOP.PROP.JUSTIFICATION_LEFT = true;

  NAV_HEADING_MINI_COMPASS_BOTTOM.PROP.POSY = 3;
  NAV_HEADING_MINI_COMPASS_BOTTOM.PROP.POSX = 18;
  NAV_HEADING_MINI_COMPASS_BOTTOM.PROP.SIZEX = 3;
  NAV_HEADING_MINI_COMPASS_BOTTOM.PROP.COLOR = COLOR_BLACK;
  NAV_HEADING_MINI_COMPASS_BOTTOM.PROP.BCOLOR = COLOR_BLACK;
  NAV_HEADING_MINI_COMPASS_BOTTOM.PROP.COLORS_ON = true;
  NAV_HEADING_MINI_COMPASS_BOTTOM.PROP.JUSTIFICATION_LEFT = true;

  /*
  // Autopilot QNH Nav
  //NAV_QNH.PROP.LABEL = "qnh";
  NAV_QNH.PROP.POSY = 6;
  NAV_QNH.PROP.POSX = 1;
  NAV_QNH.PROP.SIZEX = 12;
  NAV_QNH.PROP.JUSTIFICATION_LEFT = true;
  */

  /*
  // Signal Strenght Indicator
  SIG_STR_IND.PROP.POSY = 1;
  SIG_STR_IND.PROP.POSX = 12;
  SIG_STR_IND.PROP.COLORS_ON = true;
  SIG_STR_IND.PROP.COLOR = COLOR_BLACK;
  SIG_STR_IND.PROP.BCOLOR = COLOR_BLACK;
  SIG_STR_IND.PROP.SIZEX = 1;
  SIG_STR_IND.PROP.DONT_BLANK = true;
  SIG_STR_IND.PROP.JUSTIFICATION_LEFT = true;

  // Coordinate Data TTL Indicator
  COORD_TTL_IND.PROP.POSY = 1;
  COORD_TTL_IND.PROP.POSX = 12;
  COORD_TTL_IND.PROP.COLORS_ON = true;
  COORD_TTL_IND.PROP.COLOR = COLOR_BLACK;
  COORD_TTL_IND.PROP.BCOLOR = COLOR_BLACK;
  COORD_TTL_IND.PROP.SIZEX = 1;
  COORD_TTL_IND.PROP.DONT_BLANK = true;
  COORD_TTL_IND.PROP.JUSTIFICATION_LEFT = true;

  // Aircraft Data TTL Indicator
  DATA_TTL_IND.PROP.POSY = 1;
  DATA_TTL_IND.PROP.POSX = 12;
  DATA_TTL_IND.PROP.COLORS_ON = true;
  DATA_TTL_IND.PROP.COLOR = COLOR_BLACK;
  DATA_TTL_IND.PROP.BCOLOR = COLOR_BLACK;
  DATA_TTL_IND.PROP.SIZEX = 1;
  DATA_TTL_IND.PROP.DONT_BLANK = true;
  DATA_TTL_IND.PROP.JUSTIFICATION_LEFT = true;
  */

  // Track
  MESSAGE.PROP.POSY = PROP.SIZEY - 1;
  MESSAGE.PROP.POSX = 1;
  MESSAGE.PROP.SIZEX = PROP.SIZEX - 2;
  MESSAGE.PROP.JUSTIFICATION_LEFT = true;

  refresh();

  PROP.CHANGED = true;
}

void ADSB_Channel::clear()
{
  // Clear Variables
  ADSB_Channel_Properties cleared_properties;
  PROP = cleared_properties;

  // Reset Text Fields
  FLIGHT.clear();
  SQUAWK.clear();
  ALTITUDE.clear();
  NAV_ALTITUDE_MCP.clear();
  D_VERTICAL_RATE.clear();
  SPEED.clear();

  TRACK.clear();
  TRACK_MINI_COMPASS_TOP.clear();
  TRACK_MINI_COMPASS_BOTTOM.clear();
  
  NAV_HEADING.clear();
  NAV_HEADING_MINI_COMPASS_TOP.clear();
  NAV_HEADING_MINI_COMPASS_BOTTOM.clear();

  //NAV_QNH.set_text(PROP.AIRCRAFT_DATA.NAV_QNH.get_str_value());
}

bool ADSB_Channel::changed()
// Returns true if any of the properties have changed.
{
  return PROP.CHANGED;
}

void ADSB_Channel::update_aircraft(AIRCRAFT Aircraft, unsigned long &tmeCurrentMillis)
{
  // Start or Continue expiration timer
  EXPIREED.ping_up(tmeCurrentMillis, EXPIRATION_TIME);

  PROP.AIRCRAFT_DATA = Aircraft;

  FLIGHT.set_text(PROP.AIRCRAFT_DATA.FLIGHT.get_str_value(), tmeCurrentMillis);
  SQUAWK.set_text(PROP.AIRCRAFT_DATA.SQUAWK.get_str_value(), tmeCurrentMillis);

  //ALTITUDE.set_text(PROP.AIRCRAFT_DATA.ALTITUDE.get_str_value());
  ALTITUDE.set_text(PROP.AIRCRAFT_DATA.ALTITUDE.get_str_value(), tmeCurrentMillis);

  NAV_ALTITUDE_MCP.set_text(PROP.AIRCRAFT_DATA.NAV_ALTITUDE_MCP.get_str_value(), tmeCurrentMillis);
  D_VERTICAL_RATE.set_text(PROP.AIRCRAFT_DATA.D_VERTICAL_RATE.get_str_value(), tmeCurrentMillis);
  SPEED.set_text(PROP.AIRCRAFT_DATA.SPEED.get_str_value(), tmeCurrentMillis);

  if (PROP.AIRCRAFT_DATA.TRACK.conversion_success() == true)
  {
    TRACK.set_text(to_string(PROP.AIRCRAFT_DATA.TRACK.get_int_value()), tmeCurrentMillis);
    TRACK_MINI_COMPASS_TOP.set_text(compass_mini_top(PROP.AIRCRAFT_DATA.TRACK.get_float_value()));
    TRACK_MINI_COMPASS_BOTTOM.set_text(compass_mini_bottom(PROP.AIRCRAFT_DATA.TRACK.get_float_value()));
  }
  else
  {
    TRACK.set_text("");
    TRACK_MINI_COMPASS_TOP.clear();
    TRACK_MINI_COMPASS_BOTTOM.clear();
  }

  if (PROP.AIRCRAFT_DATA.NAV_HEADING.conversion_success() == true)
  {
    NAV_HEADING.set_text(to_string(PROP.AIRCRAFT_DATA.NAV_HEADING.get_int_value()), tmeCurrentMillis);
    NAV_HEADING_MINI_COMPASS_TOP.set_text(compass_mini_top(PROP.AIRCRAFT_DATA.NAV_HEADING.get_float_value()));
    NAV_HEADING_MINI_COMPASS_BOTTOM.set_text(compass_mini_bottom(PROP.AIRCRAFT_DATA.NAV_HEADING.get_float_value()));
  }
  else
  {
    NAV_HEADING_MINI_COMPASS_BOTTOM.set_text("");
    NAV_HEADING_MINI_COMPASS_BOTTOM.clear();
    NAV_HEADING_MINI_COMPASS_BOTTOM.clear();
  }
  
  //NAV_QNH.set_text(PROP.AIRCRAFT_DATA.NAV_QNH.get_str_value());

  PROP.CHANGED = true;
}

void ADSB_Channel::draw(bool Refresh, unsigned long tmeFrame_Time)
// Draw the text_box on the screen if the value has changed or if  
//  the Refresh parameter is true.
{
  TRUTH_CATCH redraw_screen;

  FRAME_TIME = tmeFrame_Time;

  // Check Expiration
  if (EXPIREED.blip_moved(tmeFrame_Time) == true && EXPIREED.ping_down(tmeFrame_Time) == false)
  {
    // Clear all data and reset to start empty state.
    clear();
    Refresh = true;
  }

  if ((PROP.CHANGED == true || Refresh == true))
  {
    // Draw Background
    // If No Data
    if (PROP.AIRCRAFT_DATA.data_count() == 0 && PROP.AIRCRAFT_DATA.HEX.conversion_success() == false)
    {
      PROP.BCOLOR = COLOR_BLACK;
      PROP.COLOR = COLOR_BLACK;
      MESSAGE.set_text("");
    }
    else if (PROP.AIRCRAFT_DATA.data_count() == 0 && PROP.AIRCRAFT_DATA.HEX.conversion_success() == true)
    {
      PROP.BCOLOR = COLOR_BLUE;
      PROP.COLOR = COLOR_BLACK;
    }
    // If Position Found
    else if(PROP.AIRCRAFT_DATA.POSITION.LATITUDE.conversion_success() == true && 
              PROP.AIRCRAFT_DATA.POSITION.LONGITUDE.conversion_success() == true)
    {
      PROP.BCOLOR = COLOR_GREEN;
      PROP.COLOR = COLOR_BLACK;
    }
    // If No Position Found
    else
    {
      PROP.BCOLOR = COLOR_YELLOW;
      PROP.COLOR = COLOR_BLACK;
    }

    // Write Additional Messages
    if (PROP.AIRCRAFT_DATA.data_count() == 0 && PROP.AIRCRAFT_DATA.HEX.conversion_success() == true)
    {
      MESSAGE.set_text("All Data Expired");
    }
    else
    {
      MESSAGE.set_text("");
    }

    // If Emergency set message
    if (PROP.AIRCRAFT_DATA.EMERGENCY.conversion_success() == true)
    {
      if (PROP.AIRCRAFT_DATA.EMERGENCY.get_str_value() != "none")
      {
        PROP.BCOLOR = COLOR_RED;
        PROP.COLOR = COLOR_WHITE;
        MESSAGE.set_text(PROP.AIRCRAFT_DATA.EMERGENCY.get_str_value());
      }  
    }
    
    wbkgd(winADSB, COLOR_PAIR(CRT_get_color_pair(PROP.BCOLOR, PROP.COLOR)));

    // Set Colors
    if (PROP.AIRCRAFT_DATA.data_count() > 0)
    {
      TOP_BAR.set_color(COLOR_WHITE, COLOR_BLACK);
      FLIGHT.set_color(COLOR_WHITE, COLOR_BLACK);
      SQUAWK.set_color(COLOR_WHITE, COLOR_BLACK);
    }
    else
    {
      TOP_BAR.set_color(COLOR_BLACK, COLOR_BLACK);
      FLIGHT.set_color(COLOR_BLACK, COLOR_BLACK);
      SQUAWK.set_color(COLOR_BLACK, COLOR_BLACK);
    }

    if (PROP.AIRCRAFT_DATA.ALTITUDE.conversion_success()==true)
    {
      ALTITUDE_IND.set_color(color_range(PROP.AIRCRAFT_DATA.ALTITUDE.get_int_value(), 50, 500, 3000, 12000, 40000), ALTITUDE_IND.PROP.COLOR);
    }
    else
    {
      if (PROP.AIRCRAFT_DATA.ALTITUDE.get_str_value() == "")
      {
          ALTITUDE_IND.set_color(PROP.BCOLOR, PROP.BCOLOR);
      }
      else if (PROP.AIRCRAFT_DATA.ALTITUDE.get_str_value() == "ground")
      {
        ALTITUDE_IND.set_color(COLOR_RED, PROP.BCOLOR);
        ALTITUDE.set_text("GROUND");
      }
      else
      {
        ALTITUDE_IND.set_color(COLOR_RED, PROP.BCOLOR);
      }
    }

    if (PROP.AIRCRAFT_DATA.D_FLIGHT_ANGLE.conversion_success()==true)
    {
      D_VERTICAL_RATE_IND.set_color(color_scale(PROP.AIRCRAFT_DATA.D_FLIGHT_ANGLE.get_float_value(), 2, 4, 6, 8, 10), D_VERTICAL_RATE_IND.PROP.COLOR);
    }
    else
    {
      D_VERTICAL_RATE_IND.set_color(PROP.BCOLOR, PROP.BCOLOR);
    }

    if (PROP.AIRCRAFT_DATA.ALTITUDE.conversion_success()==true)
    {
      SPEED_IND.set_color(color_range(PROP.AIRCRAFT_DATA.SPEED.get_float_value(), 60, 80, 100, 160, 600), SPEED_IND.PROP.COLOR);
    }
    else
    {
      SPEED_IND.set_color(PROP.BCOLOR, PROP.BCOLOR);
    }

    // Color Track Compass
    if (PROP.AIRCRAFT_DATA.TRACK.conversion_success() == true)
    {
      TRACK_MINI_COMPASS_TOP.set_color(COLOR_BLUE, COLOR_WHITE);
      TRACK_MINI_COMPASS_BOTTOM.set_color(COLOR_BLUE, COLOR_WHITE);
    }
    else
    {
      TRACK_MINI_COMPASS_TOP.set_color(PROP.BCOLOR, PROP.BCOLOR);
      TRACK_MINI_COMPASS_BOTTOM.set_color(PROP.BCOLOR, PROP.BCOLOR);
    }

    // Color Nav Compass
    if (PROP.AIRCRAFT_DATA.NAV_HEADING.conversion_success() == true)
    {
      NAV_HEADING_MINI_COMPASS_TOP.set_color(COLOR_BLUE, COLOR_WHITE);
      NAV_HEADING_MINI_COMPASS_BOTTOM.set_color(COLOR_BLUE, COLOR_WHITE);
    }
    else
    {
      NAV_HEADING_MINI_COMPASS_TOP.set_color(PROP.BCOLOR, PROP.BCOLOR);
      NAV_HEADING_MINI_COMPASS_BOTTOM.set_color(PROP.BCOLOR, PROP.BCOLOR);
    }

    // Screen needs to be redrawn.
    redraw_screen.catch_truth(true);
  }


  // Write All text fields.
  redraw_screen.catch_truth(TOP_BAR.draw(winADSB, Refresh));

  redraw_screen.catch_truth(FLIGHT.draw(winADSB, Refresh, tmeFrame_Time));
  redraw_screen.catch_truth(SQUAWK.draw(winADSB, Refresh, tmeFrame_Time));

  redraw_screen.catch_truth(ALTITUDE_IND.draw(winADSB, Refresh));
  
  redraw_screen.catch_truth(ALTITUDE.draw(winADSB, Refresh, tmeFrame_Time));
  
  NAV_ALTITUDE_MCP.set_color(PROP.BCOLOR, COLOR_BLUE);
  redraw_screen.catch_truth(NAV_ALTITUDE_MCP.draw(winADSB, Refresh, tmeFrame_Time));

  redraw_screen.catch_truth(D_VERTICAL_RATE_IND.draw(winADSB, Refresh));
  redraw_screen.catch_truth(D_VERTICAL_RATE.draw(winADSB, Refresh, tmeFrame_Time));

  redraw_screen.catch_truth(SPEED_IND.draw(winADSB, Refresh));
  redraw_screen.catch_truth(SPEED.draw(winADSB, Refresh, tmeFrame_Time));

  redraw_screen.catch_truth(TRACK.draw(winADSB, Refresh, tmeFrame_Time));
  redraw_screen.catch_truth(TRACK_MINI_COMPASS_TOP.draw(winADSB, Refresh));
  redraw_screen.catch_truth(TRACK_MINI_COMPASS_BOTTOM.draw(winADSB, Refresh));

  NAV_HEADING.set_color(PROP.BCOLOR, COLOR_BLUE);
  redraw_screen.catch_truth(NAV_HEADING.draw(winADSB, Refresh, tmeFrame_Time));
  redraw_screen.catch_truth(NAV_HEADING_MINI_COMPASS_TOP.draw(winADSB, Refresh));
  redraw_screen.catch_truth(NAV_HEADING_MINI_COMPASS_BOTTOM.draw(winADSB, Refresh));

  MESSAGE.draw(winADSB, Refresh);
  
  //NAV_QNH.draw(winADSB, Refresh);


  if (redraw_screen.has_truth() == true)
  {
    /*
    //Debug -- displays dedraw count and other variables.
    if (true == DEBUG_COUNTER)
    {
      Counter++;
      mvwprintw(winFrequency, 0, 0, "%d ", Counter);
      mvwprintw(winFrequency, 1, 0, "%d ", PROP.VALUE.FREQUENCY.CHANGED);
    }
    */

    // Reset Properties Changed.
    PROP.CHANGED = false;

    // Draw the Gadget.
    wrefresh(winADSB);
  }
}

// -------------------------------------------------------------------------------------

int ADSB_Channel_Grid::find_HEX(string Hex)
{
  int return_int = -1;
  for(int x=0; (x < ADSB_Channel_q.size()) && (return_int == -1); x++)
  {
    if(ADSB_Channel_q[x].PROP.AIRCRAFT_DATA.HEX.get_str_value() == Hex)
    {
      return_int = x;
    }
  }
  return return_int;
}

int ADSB_Channel_Grid::find_expired()
{
  int return_int = -1;
  for(int x=0; (x < ADSB_Channel_q.size()) && (return_int == -1); x++)
  {
    if(ADSB_Channel_q[x].PROP.AIRCRAFT_DATA.data_count() == 0)
    {
      return_int = x;
    }
  }
  return return_int;
}

void ADSB_Channel_Grid::create()
{
  ADSB_Channel Default_ADS_B; // Default ADSB Gadget.
  
  // Calculate size of ADS-B Channel Grid.
  int x = (PROP.SIZEX + 1) / Default_ADS_B.PROP.SIZEX;
  int y =  PROP.SIZEY      / Default_ADS_B.PROP.SIZEY;

  // Set number of Channels
  int new_count = x * y;

  // Create
  if (new_count > ADSB_Channel_Count)
  {
    for (int size = ADSB_Channel_Count; size < new_count; size++)
    {
      // Put channel in queue
      ADSB_Channel_q.push_back(Default_ADS_B);
    }
  }
  else if (new_count < ADSB_Channel_Count)
  {
    for (int size = new_count; size < ADSB_Channel_Count; size++)
    {
      // Put channel in queue
      ADSB_Channel_q.erase(ADSB_Channel_q.begin() + new_count, ADSB_Channel_q.end());
    }
  }

  ADSB_Channel_Count = new_count;


  int yp = 0;
  int xp = 0;
  
  for (int pos = 0; pos < ADSB_Channel_Count; pos++)
  {
    ADSB_Channel_q[pos].PROP.POSX = PROP.POSX + (xp * Default_ADS_B.PROP.SIZEX) + (xp * 1);
    ADSB_Channel_q[pos].PROP.POSY = PROP.POSY + (yp * Default_ADS_B.PROP.SIZEY);

    ADSB_Channel_q[pos].create();

    yp++;
    if (yp >= y)
    {
      yp = 0;
      xp++;
    }
  }

  PROP.CHANGED = true;
  PROP.NEEDS_REFRESH_DATA = true;

}

void ADSB_Channel_Grid::update(system_data &sdSysData, unsigned long &tmeCurrentMillis)
{
  int pos_found = 0;
  int pos_avail = 0;
  int pos_expired_avail = 0;

  // Get new list of Aircraft.
  PROP.AIRCRAFT_LIST = sdSysData.AIRCRAFT_COORD.DATA;
  IS_ACTIVE = sdSysData.AIRCRAFT_COORD.is_active();

  // Prepare list to display.
  //sort_index();

  for (int pos_search = 0; pos_search < PROP.AIRCRAFT_LIST.AIRCRAFTS.size(); pos_search++)
  {
    //Search gadget list for existing item to update.
    pos_found = find_HEX(PROP.AIRCRAFT_LIST.AIRCRAFTS[pos_search].HEX.get_str_value());

    // if not found, put aircraft info in first avail slot.
    if (pos_found == -1)
    {
      pos_avail = find_HEX("");
      
      //if slot found
      if (pos_avail == -1)
      {
        // search to put in empty position
        pos_expired_avail = find_expired();

        if (pos_expired_avail == -1)
        {
          // do nothing. nothing avail.
        }
        else
        {
          ADSB_Channel_q[pos_expired_avail].clear();
          ADSB_Channel_q[pos_expired_avail].update_aircraft(PROP.AIRCRAFT_LIST.AIRCRAFTS[pos_search], tmeCurrentMillis);
        }
      }
      else // slot found and pos avail.
      {
        ADSB_Channel_q[pos_avail].update_aircraft(PROP.AIRCRAFT_LIST.AIRCRAFTS[pos_search], tmeCurrentMillis);
      }
    }
    else // put in found pos.
    {
      ADSB_Channel_q[pos_found].update_aircraft(PROP.AIRCRAFT_LIST.AIRCRAFTS[pos_search], tmeCurrentMillis);
    }
  }


  sdSysData.AIRCRAFT_COORD.DATA.CHANGED = false;
  PROP.NEEDS_REFRESH_DATA = false;
}

void ADSB_Channel_Grid::draw(bool Refresh, unsigned long tmeFrame_Time)
// Draw the text_box on the screen if the value has changed or if  
//  the Refresh parameter is true.
{
  for (int x = 0; x < ADSB_Channel_Count; x++)
  {
    //int speed = string_to_int(ADSB_Channel_q[x].SPEED.PROP.LABEL);
    //speed++;
    //ADSB_Channel_q[x].update_value(to_string(x), to_string(ADSB_Channel_Count), "", "", "", "", tmeFrame_Time);
    //ADSB_Channel_q[x].update_value("FLIGHTxx", "1234", "099.9", "180.1", "1234", "35000", tmeFrame_Time);
    ADSB_Channel_q[x].draw(Refresh, tmeFrame_Time);
  }

  if ((PROP.CHANGED == true || Refresh == true))
  {

    /*
    //Debug -- displays dedraw count and other variables.
    if (true == DEBUG_COUNTER)
    {
      Counter++;
      mvwprintw(winFrequency, 0, 0, "%d ", Counter);
      mvwprintw(winFrequency, 1, 0, "%d ", PROP.VALUE.FREQUENCY.CHANGED);
    }
    */

    // Reset Properties Changed.
    PROP.CHANGED = false;

  }
}


// -------------------------------------------------------------------------------------
//  Radio_Channel Classes

void Radio_Channel::modify(int id, string name, string label, int value, int type, int color, int bcolor)
// Changes all button properties
{
  PROP.ID = id;
  PROP.NAME = name;
  PROP.LABEL = label;

  PROP.TYPE = type;
  PROP.COLOR = color;

  PROP.CHANGED = true;
}

void Radio_Channel::create(int id, string name, string label, int type, int color, int bcolor)
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

void Radio_Channel::move_resize(int posY, int posX, int sizeY, int sizeX)
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

bool Radio_Channel::changed()
// Returns true if any of the properties have changed.
{
  return PROP.CHANGED;
}

void Radio_Channel::update_value(API_SQUELCH_DESTINATION &New_Value, unsigned long tmeFrame_Time)
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

void Radio_Channel::draw(bool Refresh, unsigned long tmeFrame_Time)
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

bool Radio_Channel::was_redrawn()
// Returns true if the gadget redrew itself during the previous cycle.
{
  return WAS_REDRAWN;
}

bool Radio_Channel::check_click(int x_clicked, int y_clicked, string &Name)
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





using namespace std;
