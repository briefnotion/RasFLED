// ***************************************************************************************
// *
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

int ADS_B_List_Box::color_range(float Value, int Magenta, int Red, int Yellow, int Green, int Blue)
// Returns color in ranges of 1st to 5th of values
// eg (12, 5, 10, 15, 20, 25) returns color yellow
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

//int color_scale(float Value, int Magenta, int Red, int Yellow, int Green, int Blue)
int ADS_B_List_Box::color_scale(float Value, int Green, int Yellow, int Red, int Magenta, int Blue)
// Returns color in ranges of 1st to 5th of values
// eg (12, 5, 10, 15, 20, 25) returns color red
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
