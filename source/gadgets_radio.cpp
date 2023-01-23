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

#ifndef GADGETS_RADIO_CPP
#define GADGETS_RADIO_CPP

#include "gadgets_radio.h"

// -------------------------------------------------------------------------------------
//  ADSB_Channel Classes

bool Mini_Compass::changed()
// Returns true if any of the properties have changed.
{
  return CHANGED;
}

void Mini_Compass::set_heading(float Heading, unsigned long tmeFrame_Time)
{
  PROP.CLEARED = false; 

  if (Heading != PROP.HEADING)
  {
    PROP.HEADING = Heading;

    CHANGED = true;
    
    if (PROP.UPDATE_INDICATION == true)
    {
      UPDATE_INDICATION_TIMER.ping_up(tmeFrame_Time, INDICATED_BLINK_TIME);
    }
  }
}

void Mini_Compass::set_heading(float Heading)
{
  set_heading(Heading, 0);
}

void Mini_Compass::clear()
{
  Text_Field_Properties cleared_properties;

  PROP.CLEARED = true;
  PROP.HEADING = 0;
  CHANGED = true;
}

void Mini_Compass::set_color(int Background_Color, int Color)
{
  if (Background_Color != PROP.BCOLOR || Color != PROP.COLOR)
  {
    PROP.BCOLOR = Background_Color;
    PROP.COLOR  = Color;
    CHANGED = true;
  }
}


bool Mini_Compass::draw(PANEL &Panel, bool Refresh, unsigned long tmeFrame_Time)
{
  bool ret_refreshed = false;

  if (PROP.UPDATE_INDICATION == true && UPDATE_INDICATION_TIMER.blip_moved(tmeFrame_Time) == true)
  {
    Refresh = true;
  }

  if (CHANGED == true || Refresh == true)
  {
    // Check for Colored Text
    wattron(Panel.winPANEL, COLOR_PAIR(CRT_get_color_pair(PROP.BCOLOR, PROP.COLOR)));


    // Check for Blink
    if (PROP.UPDATE_INDICATION == true && UPDATE_INDICATION_TIMER.ping_down(tmeFrame_Time) == true)
    {
      wattron(Panel.winPANEL, COLOR_PAIR(CRT_get_color_pair(COLOR_WHITE, COLOR_BLACK)));
    }
    
    string return_str = ""; 

    // Draw Compas Needles
    if (PROP.CLEARED == false)
    {
      // Draw Top Line
      if ((PROP.HEADING >= 337.5 && PROP.HEADING <= 360) || (PROP.HEADING >= 0 && PROP.HEADING < 22.5))
      {
        return_str = " | ";
      }
      else if (PROP.HEADING >= 22.5 && PROP.HEADING < 67.5)
      {
        return_str = "  /";
      }
      else if (PROP.HEADING >= 67.5 && PROP.HEADING < 112.5)
      {
        return_str = "  _";
      }
      else if (PROP.HEADING >= 112.5 && PROP.HEADING < 157.5)
      {
        return_str = "   ";
      }
      else if (PROP.HEADING >= 157.5 && PROP.HEADING < 202.5)
      {
        return_str = "   ";
      }
      else if (PROP.HEADING >= 202.5 && PROP.HEADING < 247.5)
      {
        return_str = "   ";
      }
      else if (PROP.HEADING >= 247.5 && PROP.HEADING < 292.5)
      {
        return_str = "_  ";
      }
      else if (PROP.HEADING >= 292.5 && PROP.HEADING < 337.5)
      {
        return_str = "\\  ";
      }
      else
        {
        return_str = "XX";
      }

      mvwprintw(Panel.winPANEL, PROP.POSY, PROP.POSX, return_str.c_str());

      // Draw Bottom Line

      if ((PROP.HEADING >= 337.5 && PROP.HEADING <= 360) || (PROP.HEADING >= 0 && PROP.HEADING < 22.5))
      {
        return_str = "   ";
      }
      else if (PROP.HEADING >= 22.5 && PROP.HEADING < 67.5)
      {
        return_str = "   ";
      }
      else if (PROP.HEADING >= 67.5 && PROP.HEADING < 112.5)
      {
        return_str = "   ";
      }
      else if (PROP.HEADING >= 112.5 && PROP.HEADING < 157.5)
      {
        return_str = "  \\";
      }
      else if (PROP.HEADING >= 157.5 && PROP.HEADING < 202.5)
      {
        return_str = " | ";
      }
      else if (PROP.HEADING >= 202.5 && PROP.HEADING < 247.5)
      {
        return_str = "/  ";
      }
      else if (PROP.HEADING >= 247.5 && PROP.HEADING < 292.5)
      {
        return_str = "   ";
      }
      else if (PROP.HEADING >= 292.5 && PROP.HEADING < 337.5)
      {
        return_str = "   ";
      }
      else
        {
        return_str = "XX";
      }

      mvwprintw(Panel.winPANEL, PROP.POSY +1, PROP.POSX, return_str.c_str());
    }
    else  // Cleared, draw blanks.
    {
      mvwprintw(Panel.winPANEL, PROP.POSY   , PROP.POSX, "   ");
      mvwprintw(Panel.winPANEL, PROP.POSY +1, PROP.POSX, "   ");
    }

    // Check for Blink
    if (PROP.UPDATE_INDICATION == true && UPDATE_INDICATION_TIMER.ping_down(tmeFrame_Time) == true)
    {
      wattroff(Panel.winPANEL, COLOR_PAIR(CRT_get_color_pair(COLOR_WHITE, COLOR_BLACK)));
    }

    // Check for Colored Text
    wattroff(Panel.winPANEL, COLOR_PAIR(CRT_get_color_pair(PROP.BCOLOR, PROP.COLOR)));
 
    //Debug -- displays dedraw count and other variables.
    if (true == DEBUG_COUNTER)
    {
      Counter++;
      mvwprintw(Panel.winPANEL, PROP.POSY, PROP.POSX, "%d ", Counter);
    }
    
    CHANGED = false;

    Panel.changed_on();
    ret_refreshed = true;
  }

  return ret_refreshed;
}
  
bool Mini_Compass::draw(PANEL &Panel, bool Refresh)
{
  return draw(Panel, Refresh, 0);
}

// -------------------------------------------------------------------------------------
//  ADS-B Classes

// -------------------------------------------------------------------------------------
//  ADSB_Channel Classes

void ADSB_Channel::create()
// Define and behavior.  
// Like set but leaves off position and size details.
// Does not create window.
{
  // Create Gadget Window
  // Create Panel
  ADSB_PANEL.PROP.POSY = PROP.POSY;
  ADSB_PANEL.PROP.POSX = PROP.POSX;
  ADSB_PANEL.PROP.SIZEY = PROP.SIZEY;
  ADSB_PANEL.PROP.SIZEX = PROP.SIZEX;

  ADSB_PANEL.create();

  // Create Text Fields

  // Flight
  FLIGHT.PROP.POSY = 0;
  FLIGHT.PROP.POSX = 0;
  FLIGHT.PROP.COLORS_ON = true;
  FLIGHT.PROP.COLOR = COLOR_BLACK;
  FLIGHT.PROP.BCOLOR = COLOR_BLACK;
  FLIGHT.PROP.SIZEX = 9;
  FLIGHT.PROP.DONT_BLANK = true;
  FLIGHT.PROP.JUSTIFICATION_LEFT = true;
  FLIGHT.PROP.UPDATE_INDICATION = true;

  // Squawk
  SQUAWK.PROP.POSY = 0;
  SQUAWK.PROP.POSX = 15;
  SQUAWK.PROP.COLORS_ON = true;
  SQUAWK.PROP.COLOR = COLOR_BLACK;
  SQUAWK.PROP.BCOLOR = COLOR_BLACK;
  SQUAWK.PROP.SIZEX = 6;
  SQUAWK.PROP.DONT_BLANK = true;
  SQUAWK.PROP.JUSTIFICATION_RIGHT = true;
  SQUAWK.PROP.UPDATE_INDICATION = true;

  // Altitude
  ALTITUDE.PROP.POSY = 1;
  ALTITUDE.PROP.POSX = 14;
  ALTITUDE.PROP.SIZEX = 6;
  ALTITUDE.PROP.DONT_BLANK = true;
  ALTITUDE.PROP.JUSTIFICATION_RIGHT = true;
  ALTITUDE.PROP.UPDATE_INDICATION = true;

  // Altitude Indicator
  ALTITUDE_IND.PROP.POSY = 1;
  ALTITUDE_IND.PROP.POSX = 20;
  ALTITUDE_IND.PROP.COLORS_ON = true;
  ALTITUDE_IND.PROP.COLOR = COLOR_BLACK;
  ALTITUDE_IND.PROP.BCOLOR = COLOR_BLACK;
  ALTITUDE_IND.PROP.SIZEX = 1;
  ALTITUDE_IND.PROP.DONT_BLANK = true;
  ALTITUDE_IND.PROP.JUSTIFICATION_LEFT = true;

  // Altitude Nav
  //NAV_ALTITUDE_MCP.PROP.LABEL = "nava";
  NAV_ALTITUDE_MCP.PROP.POSY = 2;
  NAV_ALTITUDE_MCP.PROP.POSX = 14;
  NAV_ALTITUDE_MCP.PROP.COLORS_ON = true;
  NAV_ALTITUDE_MCP.PROP.COLOR = COLOR_BLUE;
  NAV_ALTITUDE_MCP.PROP.BCOLOR = COLOR_BLACK;
  NAV_ALTITUDE_MCP.PROP.SIZEX = 6;
  NAV_ALTITUDE_MCP.PROP.DONT_BLANK = true;
  NAV_ALTITUDE_MCP.PROP.JUSTIFICATION_RIGHT = true;
  NAV_ALTITUDE_MCP.PROP.UPDATE_INDICATION = true;

  // Vertical Rate
  D_VERTICAL_RATE.PROP.POSY = 3;
  D_VERTICAL_RATE.PROP.POSX = 14;
  D_VERTICAL_RATE.PROP.SIZEX = 6;
  D_VERTICAL_RATE.PROP.DONT_BLANK = true;
  D_VERTICAL_RATE.PROP.JUSTIFICATION_RIGHT = true;
  D_VERTICAL_RATE.PROP.UPDATE_INDICATION = true;

  // Vertical Rate Indicator
  D_VERTICAL_RATE_IND.PROP.POSY = 3;
  D_VERTICAL_RATE_IND.PROP.POSX = 20;
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
  TRACK.PROP.POSX = 7;
  TRACK.PROP.SIZEX = 3;
  TRACK.PROP.DONT_BLANK = true;
  TRACK.PROP.JUSTIFICATION_RIGHT = true;
  TRACK.PROP.UPDATE_INDICATION = true;

  // Track Mini Compass
  TRACK_MINI_COMPASS.PROP.POSY = 2;
  TRACK_MINI_COMPASS.PROP.POSX = 7;
  TRACK_MINI_COMPASS.PROP.COLOR = COLOR_BLACK;
  TRACK_MINI_COMPASS.PROP.BCOLOR = COLOR_BLACK;
  
  // Track Nav
  //NAV_HEADING.PROP.LABEL = "navt";
  NAV_HEADING.PROP.POSY = 1;
  NAV_HEADING.PROP.POSX = 11;
  NAV_HEADING.PROP.COLORS_ON = true;
  NAV_HEADING.PROP.COLOR = COLOR_BLUE;
  NAV_HEADING.PROP.BCOLOR = COLOR_BLACK;
  NAV_HEADING.PROP.SIZEX = 3;
  NAV_HEADING.PROP.DONT_BLANK = true;
  NAV_HEADING.PROP.JUSTIFICATION_LEFT = true;
  NAV_HEADING.PROP.UPDATE_INDICATION = true;

  // Track Nav Mini Compass
  NAV_HEADING_MINI_COMPASS.PROP.POSY = 2;
  NAV_HEADING_MINI_COMPASS.PROP.POSX = 11;
  NAV_HEADING_MINI_COMPASS.PROP.COLOR = COLOR_BLACK;
  NAV_HEADING_MINI_COMPASS.PROP.BCOLOR = COLOR_BLACK;
  
  // Coordinate Data TTL Indicator
  COORD_TTL_IND.PROP.POSY = 0;
  COORD_TTL_IND.PROP.POSX = 9;
  COORD_TTL_IND.PROP.COLORS_ON = true;
  COORD_TTL_IND.PROP.COLOR = COLOR_BLACK;
  COORD_TTL_IND.PROP.BCOLOR = COLOR_BLACK;
  COORD_TTL_IND.PROP.SIZEX = 2;
  COORD_TTL_IND.PROP.DONT_BLANK = true;
  COORD_TTL_IND.PROP.JUSTIFICATION_LEFT = true;

  // Aircraft Data TTL Indicator
  DATA_TTL_IND.PROP.POSY = 0;
  DATA_TTL_IND.PROP.POSX = 11;
  DATA_TTL_IND.PROP.COLORS_ON = true;
  DATA_TTL_IND.PROP.COLOR = COLOR_BLACK;
  DATA_TTL_IND.PROP.BCOLOR = COLOR_BLACK;
  DATA_TTL_IND.PROP.SIZEX = 2;
  DATA_TTL_IND.PROP.DONT_BLANK = true;
  DATA_TTL_IND.PROP.JUSTIFICATION_LEFT = true;

    // Signal Strenght Indicator
  SIG_STR_IND.PROP.POSY = 0;
  SIG_STR_IND.PROP.POSX = 13;
  SIG_STR_IND.PROP.COLORS_ON = true;
  SIG_STR_IND.PROP.COLOR = COLOR_BLACK;
  SIG_STR_IND.PROP.BCOLOR = COLOR_BLACK;
  SIG_STR_IND.PROP.SIZEX = 2;
  SIG_STR_IND.PROP.DONT_BLANK = true;
  SIG_STR_IND.PROP.JUSTIFICATION_LEFT = true;

  // Message
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
  TRACK_MINI_COMPASS.clear();
  
  NAV_HEADING.clear();
  NAV_HEADING_MINI_COMPASS.clear();

  SIG_STR_IND.set_color(COLOR_BLACK, COLOR_BLACK);
  SIG_STR_IND.clear();

  COORD_TTL_IND.set_color(COLOR_BLACK, COLOR_BLACK);
  COORD_TTL_IND.clear();
  
  DATA_TTL_IND.set_color(COLOR_BLACK, COLOR_BLACK);
  DATA_TTL_IND.clear();

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

  PROP.CHANGED = true;
}

bool ADSB_Channel::draw(bool Refresh, unsigned long tmeFrame_Time)
// Draw the text_box on the screen if the value has changed or if  
//  the Refresh parameter is true.
{
  bool ret_refreshed = false;

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
    // If No Data at all
    if (PROP.AIRCRAFT_DATA.data_count() == 0 && PROP.AIRCRAFT_DATA.HEX.conversion_success() == false)
    {
      PROP.BCOLOR = COLOR_BLACK;
      PROP.COLOR = COLOR_BLACK;
      MESSAGE.set_text("");
    }
    // If No Aircraft Data
    else if (PROP.AIRCRAFT_DATA.data_count() == 0 && PROP.AIRCRAFT_DATA.HEX.conversion_success() == true)
    {
      PROP.BCOLOR = COLOR_BLUE;
      PROP.COLOR = COLOR_BLACK;
    }
    // If Position Found
    else if(PROP.AIRCRAFT_DATA.POSITION.GLOBAL_POSITION_FOUND == true)
    {
      PROP.BCOLOR = COLOR_GREEN;
      PROP.COLOR = COLOR_BLACK;
    }
    // If No Position Found but Data Exist
    else
    {
      PROP.BCOLOR = COLOR_YELLOW;
      PROP.COLOR = COLOR_BLACK;
    }

    // Write Additional Messages
    if (PROP.AIRCRAFT_DATA.data_count() == 0 && PROP.AIRCRAFT_DATA.HEX.conversion_success() == true)
    {
      MESSAGE.set_text("No Data");
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
    
    ADSB_PANEL.set_color(PROP.BCOLOR, PROP.COLOR);

    // Set Colors and Text

    // Flight and Squawk
    if (PROP.AIRCRAFT_DATA.data_count() > 0)
    {
      //TOP_BAR.set_color(COLOR_WHITE, COLOR_BLACK);
      FLIGHT.set_color(COLOR_WHITE, COLOR_BLACK);
      SQUAWK.set_color(COLOR_WHITE, COLOR_BLACK);
    }
    else
    {
      //TOP_BAR.set_color(COLOR_BLACK, COLOR_BLACK);
      FLIGHT.set_color(COLOR_BLACK, COLOR_BLACK);
      SQUAWK.set_color(COLOR_BLACK, COLOR_BLACK);
    }

    FLIGHT.set_text(PROP.AIRCRAFT_DATA.FLIGHT.get_str_value(), tmeFrame_Time);
    SQUAWK.set_text(PROP.AIRCRAFT_DATA.SQUAWK.get_str_value(), tmeFrame_Time);

    //Altitude and Altitude Inicator
    if (PROP.AIRCRAFT_DATA.ALTITUDE.conversion_success()==true)
    {
      // Aircraft Altitude data ok
      ALTITUDE_IND.set_color(color_range(PROP.AIRCRAFT_DATA.ALTITUDE.get_int_value(), 50, 500, 3000, 12000, 40000), ALTITUDE_IND.PROP.COLOR);
      ALTITUDE_IND.set_text("^");
      ALTITUDE.set_text(PROP.AIRCRAFT_DATA.ALTITUDE.get_str_value(), tmeFrame_Time);
    }
    else
    {
      if (PROP.AIRCRAFT_DATA.ALTITUDE.get_str_value() == "ground")
      // Aircraft Altitude data says on ground
      {
        ALTITUDE_IND.set_color(COLOR_RED, COLOR_BLACK);
        ALTITUDE_IND.set_text("X");
        ALTITUDE.set_text("GROUND");
      }
      else
      {
        // Aircraft Altitude data unknown
        ALTITUDE_IND.set_color(PROP.BCOLOR, PROP.BCOLOR);
        ALTITUDE_IND.set_text(" ");
        ALTITUDE.set_text(PROP.AIRCRAFT_DATA.ALTITUDE.get_str_value(), tmeFrame_Time);
      }
    }

    // Aircraft Nav Altitude
    NAV_ALTITUDE_MCP.set_color(PROP.BCOLOR, COLOR_BLUE);
    NAV_ALTITUDE_MCP.set_text(PROP.AIRCRAFT_DATA.NAV_ALTITUDE_MCP.get_str_value(), tmeFrame_Time);
    
    // Aircraft Vertical Rate and Vertical Rate Indicator
    if (PROP.AIRCRAFT_DATA.D_FLIGHT_ANGLE.conversion_success()==true)
    {
      D_VERTICAL_RATE_IND.set_color(color_scale(PROP.AIRCRAFT_DATA.D_FLIGHT_ANGLE.get_float_value(), 2, 4, 6, 8, 10), COLOR_BLACK);
      D_VERTICAL_RATE_IND.set_text("^");
    }
    else
    {
      D_VERTICAL_RATE_IND.set_color(PROP.BCOLOR, COLOR_BLACK);
      D_VERTICAL_RATE_IND.set_text(" ");
    }
    
    D_VERTICAL_RATE.set_text(PROP.AIRCRAFT_DATA.D_VERTICAL_RATE.get_str_value(), tmeFrame_Time);

    // Aircraft Speed and Speed Indicator
    if (PROP.AIRCRAFT_DATA.SPEED.conversion_success()==true)
    {
      SPEED_IND.set_color(color_range(PROP.AIRCRAFT_DATA.SPEED.get_float_value(), 60, 80, 100, 160, 600), COLOR_BLACK);
      SPEED_IND.set_text("^");
    }
    else
    {
      SPEED_IND.set_color(PROP.BCOLOR, COLOR_BLACK);
      SPEED_IND.set_text(" ");
    }

    SPEED.set_text(PROP.AIRCRAFT_DATA.SPEED.get_str_value(), tmeFrame_Time);

    // Aircraft Track and Compass Track
    if (PROP.AIRCRAFT_DATA.TRACK.conversion_success() == true)
    {
      TRACK_MINI_COMPASS.set_color(COLOR_BLUE, COLOR_WHITE);
      TRACK_MINI_COMPASS.set_heading(PROP.AIRCRAFT_DATA.TRACK.get_float_value());
      TRACK.set_text(to_string(PROP.AIRCRAFT_DATA.TRACK.get_int_value()), tmeFrame_Time);
    }
    else
    {
      TRACK_MINI_COMPASS.set_color(PROP.BCOLOR, PROP.BCOLOR);
      TRACK_MINI_COMPASS.clear();
      TRACK.set_text("");
    }

    // Aircraft NAV Track and Compass NAV Track
    NAV_HEADING.set_color(PROP.BCOLOR, COLOR_BLUE);
    if (PROP.AIRCRAFT_DATA.NAV_HEADING.conversion_success() == true)
    {
      NAV_HEADING_MINI_COMPASS.set_color(COLOR_BLUE, COLOR_WHITE);
      NAV_HEADING_MINI_COMPASS.set_heading(PROP.AIRCRAFT_DATA.NAV_HEADING.get_float_value());
      NAV_HEADING.set_text(to_string(PROP.AIRCRAFT_DATA.NAV_HEADING.get_int_value()), tmeFrame_Time);
    }
    else
    {
      NAV_HEADING_MINI_COMPASS.set_color(PROP.BCOLOR, PROP.BCOLOR);
      NAV_HEADING_MINI_COMPASS.clear();
      NAV_HEADING.set_text("");
    }

    // Aircraft COORD TTL, Data TTL, and RSSI Str.
    if (PROP.AIRCRAFT_DATA.HEX.conversion_success() == true)
    {
      // Aircraft Geo Coordinates TTL
      if (  PROP.AIRCRAFT_DATA.SEEN_POS.conversion_success()==true &&
            PROP.AIRCRAFT_DATA.POSITION.GLOBAL_POSITION_FOUND == true)
      {
        COORD_TTL_IND.set_color(color_scale(PROP.AIRCRAFT_DATA.SEEN_POS.get_float_value(), 5, 45, 65, 0, 0), COLOR_BLACK);
        COORD_TTL_IND.set_text("()");
      }
      else
      {
        COORD_TTL_IND.set_color(PROP.BCOLOR, PROP.BCOLOR);
      }

      // Aircraft Data TTL
      if (PROP.AIRCRAFT_DATA.SEEN.conversion_success()==true)
      {
        DATA_TTL_IND.set_color(color_scale(PROP.AIRCRAFT_DATA.SEEN.get_float_value(), 70, 170, 290, 0, 0), COLOR_BLACK);
        DATA_TTL_IND.set_text("()");
      }

      // Aircraft RSSI Strength
      if (PROP.AIRCRAFT_DATA.RSSI.conversion_success()==true)
      {
        SIG_STR_IND.set_color(color_scale(PROP.AIRCRAFT_DATA.RSSI.get_float_value(), 18, 30, 32, 34, 36), COLOR_BLACK);
        SIG_STR_IND.set_text("()");
      }
    }
    else
    {
      COORD_TTL_IND.set_color(PROP.BCOLOR, PROP.BCOLOR);
      COORD_TTL_IND.set_text("  ");

      DATA_TTL_IND.set_color(PROP.BCOLOR, PROP.BCOLOR);
      DATA_TTL_IND.set_text("  ");

      SIG_STR_IND.set_color(PROP.BCOLOR, PROP.BCOLOR);
      SIG_STR_IND.set_text("  ");
    }

    ret_refreshed = true;
  }

  // Write All text fields.

  FLIGHT.draw(ADSB_PANEL, Refresh, tmeFrame_Time);
  SQUAWK.draw(ADSB_PANEL, Refresh, tmeFrame_Time);

  ALTITUDE_IND.draw(ADSB_PANEL, Refresh);
  
  ALTITUDE.draw(ADSB_PANEL, Refresh, tmeFrame_Time);
  
  NAV_ALTITUDE_MCP.draw(ADSB_PANEL, Refresh, tmeFrame_Time);

  D_VERTICAL_RATE_IND.draw(ADSB_PANEL, Refresh);
  D_VERTICAL_RATE.draw(ADSB_PANEL, Refresh, tmeFrame_Time);

  SPEED_IND.draw(ADSB_PANEL, Refresh);
  SPEED.draw(ADSB_PANEL, Refresh, tmeFrame_Time);

  TRACK.draw(ADSB_PANEL, Refresh, tmeFrame_Time);
  TRACK_MINI_COMPASS.draw(ADSB_PANEL, Refresh);

  NAV_HEADING.draw(ADSB_PANEL, Refresh, tmeFrame_Time);
  NAV_HEADING_MINI_COMPASS.draw(ADSB_PANEL, Refresh);

  SIG_STR_IND.draw(ADSB_PANEL, Refresh, tmeFrame_Time);
  COORD_TTL_IND.draw(ADSB_PANEL, Refresh, tmeFrame_Time);
  DATA_TTL_IND.draw(ADSB_PANEL, Refresh, tmeFrame_Time);

  MESSAGE.draw(ADSB_PANEL, Refresh);
  
//NAV_QNH.draw(winADSB, Refresh);

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
  ADSB_PANEL.draw(Refresh);

  return ret_refreshed;
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
  
  // Create Title Bar
  TOP_BAR.PROP.POSX = 0;
  TOP_BAR.PROP.POSY = 0;
  TOP_BAR.PROP.SIZEX = PROP.SIZEX;
  TOP_BAR.PROP.COLORS_ON = true;
  TOP_BAR.set_color(COLOR_BLUE, COLOR_WHITE);
  TOP_BAR.PROP.JUSTIFICATION_LEFT = true;

  // Time
  TIME.PROP.POSX = 0;
  TIME.PROP.POSY = 0;
  TIME.PROP.SIZEX = 21;
  TIME.PROP.COLORS_ON = true;
  TIME.set_color(COLOR_BLUE, COLOR_WHITE);
  TIME.PROP.JUSTIFICATION_LEFT = true;

  // Aircraft Count
  AIRCRAFT_COUNT_TITLE.PROP.POSX = 24;
  AIRCRAFT_COUNT_TITLE.PROP.POSY = 0;
  AIRCRAFT_COUNT_TITLE.PROP.SIZEX = 9;
  AIRCRAFT_COUNT_TITLE.PROP.COLORS_ON = true;
  AIRCRAFT_COUNT_TITLE.set_color(COLOR_BLUE, COLOR_WHITE);
  AIRCRAFT_COUNT_TITLE.PROP.JUSTIFICATION_LEFT = true;
  AIRCRAFT_COUNT_TITLE.set_text("Aircraft:");

  AIRCRAFT_COUNT.PROP.POSX = 34;
  AIRCRAFT_COUNT.PROP.POSY = 0;
  AIRCRAFT_COUNT.PROP.SIZEX = 4;
  AIRCRAFT_COUNT.PROP.COLORS_ON = true;
  AIRCRAFT_COUNT.set_color(COLOR_BLUE, COLOR_WHITE);
  AIRCRAFT_COUNT.PROP.JUSTIFICATION_LEFT = true;

  // Positioned Aircraft
  POSITIONED_AIRCRAFT_TITLE.PROP.POSX = 39;
  POSITIONED_AIRCRAFT_TITLE.PROP.POSY = 0;
  POSITIONED_AIRCRAFT_TITLE.PROP.SIZEX = 4;
  POSITIONED_AIRCRAFT_TITLE.PROP.COLORS_ON = true;
  POSITIONED_AIRCRAFT_TITLE.set_color(COLOR_BLUE, COLOR_WHITE);
  POSITIONED_AIRCRAFT_TITLE.PROP.JUSTIFICATION_LEFT = true;
  POSITIONED_AIRCRAFT_TITLE.set_text("Pos:");

  POSITIONED_AIRCRAFT.PROP.POSX = 44;
  POSITIONED_AIRCRAFT.PROP.POSY = 0;
  POSITIONED_AIRCRAFT.PROP.SIZEX = 4;
  POSITIONED_AIRCRAFT.PROP.COLORS_ON = true;
  POSITIONED_AIRCRAFT.set_color(COLOR_BLUE, COLOR_WHITE);
  POSITIONED_AIRCRAFT.PROP.JUSTIFICATION_LEFT = true;

  //Delta Messages Bar
  DELTA_MESSAGES_BAR.PROP.LABEL = "Msgs: ";
  DELTA_MESSAGES_BAR.PROP.LABEL_SIZE = 6;
  DELTA_MESSAGES_BAR.PROP.COLOR = COLOR_WHITE;
  DELTA_MESSAGES_BAR.PROP.BCOLOR = COLOR_BLUE;
  DELTA_MESSAGES_BAR.PROP.COLOR_BAR_BACK = COLOR_BLUE;
  DELTA_MESSAGES_BAR.PROP.COLOR_MARKER = COLOR_WHITE;
  DELTA_MESSAGES_BAR.PROP.COLOR_MARKER_LIMIT = COLOR_RED;
  DELTA_MESSAGES_BAR.PROP.POSY = 0;
  DELTA_MESSAGES_BAR.PROP.POSX = 48;
  DELTA_MESSAGES_BAR.PROP.BAR_SIZE = 10;
  DELTA_MESSAGES_BAR.PROP.GUAGE_BAR = true;
  DELTA_MESSAGES_BAR.PROP.MIN_MAX = true;
  DELTA_MESSAGES_BAR.PROP.MAX_VALUE = 50;
  DELTA_MESSAGES_BAR.PROP.MIN_VALUE = 0;
  DELTA_MESSAGES_BAR.MIN_MAX_HISTORY.PROP.SLICES = 5;
  DELTA_MESSAGES_BAR.MIN_MAX_HISTORY.PROP.TIME_SPAN = 10000;
  DELTA_MESSAGES_BAR.PROP.PRINT_VALUE = false;
  DELTA_MESSAGES_BAR.PROP.PRINT_MIN = true;
  DELTA_MESSAGES_BAR.PROP.PRINT_MAX = true;
  DELTA_MESSAGES_BAR.PROP.COLORS_ON = true;

  // Calculate size of ADS-B Channel Grid.
  int x = PROP.SIZEX / (Default_ADS_B.PROP.SIZEX + 1);
  int y = (PROP.SIZEY - 1) /  Default_ADS_B.PROP.SIZEY;

  // Set number of Channels
  int new_count = (x * y) -1; // Skip slot one so have one less avail

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

  int yp = 1; //Skip slot 1
  int xp = 0;
  
  for (int pos = 0; pos < ADSB_Channel_Count; pos++)
  {
    ADSB_Channel_q[pos].PROP.POSX = PROP.POSX + (xp * Default_ADS_B.PROP.SIZEX) + (xp * 1);
    ADSB_Channel_q[pos].PROP.POSY = 1 + (PROP.POSY + (yp * Default_ADS_B.PROP.SIZEY));  // Offsetting Title_Bar

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

bool ADSB_Channel_Grid::draw(bool Refresh, unsigned long tmeFrame_Time, PANEL ADSB_Grid_Panel)
// Draw the text_box on the screen if the value has changed or if  
//  the Refresh parameter is true.
{
  bool ret_refreshed = false;

  for (int x = 0; x < ADSB_Channel_Count; x++)
  {
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

  }

  TIME.set_text(                                         to_string(PROP.AIRCRAFT_LIST.CONVERTED_TIME.get_year()) + 
                  "-" + linemerge_right_justify(2, "00", to_string(PROP.AIRCRAFT_LIST.CONVERTED_TIME.get_month())) + 
                  "-" + linemerge_right_justify(2, "00", to_string(PROP.AIRCRAFT_LIST.CONVERTED_TIME.get_day())) + 
                  " " + linemerge_right_justify(2, "00", to_string(PROP.AIRCRAFT_LIST.CONVERTED_TIME.get_hour())) + 
                  ":" + linemerge_right_justify(2, "00", to_string(PROP.AIRCRAFT_LIST.CONVERTED_TIME.get_minute())) + 
                  ":" + linemerge_right_justify(2, "00", to_string(PROP.AIRCRAFT_LIST.CONVERTED_TIME.get_second())) + 
                  "." + to_string(PROP.AIRCRAFT_LIST.CONVERTED_TIME.get_deciseconds())
                );


  AIRCRAFT_COUNT.set_text(to_string(PROP.AIRCRAFT_LIST.AIRCRAFTS.size()));
  POSITIONED_AIRCRAFT.set_text(to_string(PROP.AIRCRAFT_LIST.POSITIONED_AIRCRAFT));

  DELTA_MESSAGES_BAR.update(PROP.AIRCRAFT_LIST.DELTA_MESSAGES, tmeFrame_Time);
  
  // Draw
  TOP_BAR.draw(ADSB_Grid_Panel, Refresh);

  TIME.draw(ADSB_Grid_Panel, Refresh);
  AIRCRAFT_COUNT_TITLE.draw(ADSB_Grid_Panel, Refresh);
  AIRCRAFT_COUNT.draw(ADSB_Grid_Panel, Refresh);
  POSITIONED_AIRCRAFT_TITLE.draw(ADSB_Grid_Panel, Refresh);
  POSITIONED_AIRCRAFT.draw(ADSB_Grid_Panel, Refresh);

  DELTA_MESSAGES_BAR.draw(ADSB_Grid_Panel, Refresh);

  PROP.CHANGED = false;
  ADSB_Grid_Panel.draw(Refresh);

  return ret_refreshed;
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
 
  // Create Noise Level Bar
  BAR_NOISE_LEVEL.PROP.LABEL = PROP.NOISE_LABEL;
  BAR_NOISE_LEVEL.PROP.LABEL_SIZE = PROP.NOISE_LABEL.size();
  BAR_NOISE_LEVEL.PROP.POSY = 2;
  BAR_NOISE_LEVEL.PROP.POSX = 0;
  BAR_NOISE_LEVEL.PROP.COLOR = COLOR_WHITE;
  BAR_NOISE_LEVEL.PROP.BCOLOR = COLOR_GREEN;
  BAR_NOISE_LEVEL.PROP.COLOR_BAR_BACK = COLOR_YELLOW;
  BAR_NOISE_LEVEL.PROP.COLOR_MARKER = COLOR_WHITE;
  BAR_NOISE_LEVEL.PROP.COLOR_MARKER_LIMIT = COLOR_RED;
  BAR_NOISE_LEVEL.PROP.BAR_SIZE = PROP.BAR_SIZE;
  BAR_NOISE_LEVEL.PROP.PROGRESS_BAR = true;
  BAR_NOISE_LEVEL.PROP.COLORS_ON = true;
  BAR_NOISE_LEVEL.PROP.MAX_VALUE = 100;
  BAR_NOISE_LEVEL.PROP.MIN_MAX = true;
  BAR_NOISE_LEVEL.PROP.PRINT_MIN = BAR_NOISE_LEVEL.PROP.MIN_MAX;
  BAR_NOISE_LEVEL.PROP.PRINT_MAX = BAR_NOISE_LEVEL.PROP.MIN_MAX;
  BAR_NOISE_LEVEL.MIN_MAX_HISTORY.PROP.TIME_SPAN = 60000;
  BAR_NOISE_LEVEL.MIN_MAX_HISTORY.PROP.SLICES = 12;

  // Create Signal Level Bar
  BAR_SIGNAL_LEVEL.PROP.LABEL = PROP.SIGNAL_LABEL;
  BAR_SIGNAL_LEVEL.PROP.LABEL_SIZE = PROP.SIGNAL_LABEL.size();
  BAR_SIGNAL_LEVEL.PROP.POSY = 1;
  BAR_SIGNAL_LEVEL.PROP.POSX = 0;
  BAR_SIGNAL_LEVEL.PROP.COLOR = COLOR_WHITE;
  BAR_SIGNAL_LEVEL.PROP.BCOLOR = COLOR_GREEN;
  BAR_SIGNAL_LEVEL.PROP.COLOR_BAR_BACK = COLOR_YELLOW;
  BAR_SIGNAL_LEVEL.PROP.COLOR_MARKER = COLOR_WHITE;
  BAR_SIGNAL_LEVEL.PROP.COLOR_MARKER_LIMIT = COLOR_RED;
  BAR_SIGNAL_LEVEL.PROP.BAR_SIZE = PROP.BAR_SIZE;
  BAR_SIGNAL_LEVEL.PROP.GUAGE_BAR = true;
  BAR_SIGNAL_LEVEL.PROP.COLORS_ON = true;
  BAR_SIGNAL_LEVEL.PROP.MAX_VALUE = 100;
  BAR_SIGNAL_LEVEL.PROP.MIN_MAX = true;
  BAR_SIGNAL_LEVEL.PROP.PRINT_MIN = BAR_NOISE_LEVEL.PROP.MIN_MAX;
  BAR_SIGNAL_LEVEL.PROP.PRINT_MAX = BAR_NOISE_LEVEL.PROP.MIN_MAX;
  BAR_SIGNAL_LEVEL.MIN_MAX_HISTORY.PROP.TIME_SPAN = 60000;
  BAR_SIGNAL_LEVEL.MIN_MAX_HISTORY.PROP.SLICES = 12;

  bool CHANGED = true;
}

void Radio_Channel::move_resize(int posY, int posX, int sizeY, int sizeX)
// Redefine button position and size.
{
  PROP.POSX = posX;
  PROP.POSY = posY;
  PROP.SIZEX = sizeX;
  PROP.SIZEY = sizeY;

  // Panel
  FREQUENCY_PANEL.PROP.POSY = PROP.POSY;
  FREQUENCY_PANEL.PROP.POSX = PROP.POSX;
  FREQUENCY_PANEL.PROP.SIZEY = PROP.SIZEY;
  FREQUENCY_PANEL.PROP.SIZEX = PROP.SIZEX;

  FREQUENCY_PANEL.create();

  // Create Buttons
  bzGadget.clear();

  bzGadget.NEW_BUTTON_PROP.VALUE = 0;
  bzGadget.NEW_BUTTON_PROP.TYPE = 0;
  bzGadget.NEW_BUTTON_PROP.COLOR = COLOR_WHITE;
  bzGadget.NEW_BUTTON_PROP.BORDER.RIGHT = '|';

  // Gadget Button
  bzGadget.NEW_BUTTON_PROP.ID = 0;
  bzGadget.NEW_BUTTON_PROP.NAME = "GADGET";
  bzGadget.NEW_BUTTON_PROP.LABEL = "\nGadget";
  bzGadget.NEW_BUTTON_PROP.BCOLOR = COLOR_YELLOW;
  bzGadget.NEW_BUTTON_PROP.HIDDEN = true;
  bzGadget.NEW_BUTTON_PROP.ENABLED = true;
  bzGadget.NEW_BUTTON_PROP.DO_NOT_DRAW = true;
  bzGadget.NEW_BUTTON_PROP.POSY = PROP.POSY;
  bzGadget.NEW_BUTTON_PROP.POSX = PROP.POSX;
  bzGadget.NEW_BUTTON_PROP.SIZEY = PROP.SIZEY;
  bzGadget.NEW_BUTTON_PROP.SIZEX = PROP.SIZEX;
  bzGadget.create_button();
  
  // Skip Frequency Button
  bzGadget.NEW_BUTTON_PROP.ID = 0;
  bzGadget.NEW_BUTTON_PROP.NAME = "SKIP";
  if(Button_YSize > PROP.SIZEY)
  {
    bzGadget.NEW_BUTTON_PROP.LABEL = "SKIP"; 
  }
  else 
  {
    bzGadget.NEW_BUTTON_PROP.LABEL = "\nSKIP";
  }
  bzGadget.NEW_BUTTON_PROP.BCOLOR = COLOR_GREEN;
  bzGadget.NEW_BUTTON_PROP.ENABLED = true;
  bzGadget.NEW_BUTTON_PROP.SIZEY = Button_YSize;
  bzGadget.NEW_BUTTON_PROP.SIZEX = Button_XSize;
  bzGadget.NEW_BUTTON_PROP.POSY = PROP.POSY + (Button_YSize *0);
  bzGadget.NEW_BUTTON_PROP.POSX = PROP.POSX + (Button_XSize *0);
  bzGadget.create_button();
  
  // Hold Frequency Button
  bzGadget.NEW_BUTTON_PROP.ID = 0;
  bzGadget.NEW_BUTTON_PROP.NAME = "HOLD";
  if(Button_YSize > PROP.SIZEY)
  {
    bzGadget.NEW_BUTTON_PROP.LABEL = "HOLD"; 
  }
  else 
  {
    bzGadget.NEW_BUTTON_PROP.LABEL = "\nHOLD";
  }
  bzGadget.NEW_BUTTON_PROP.BCOLOR = COLOR_RED;
  bzGadget.NEW_BUTTON_PROP.ENABLED = true;
  bzGadget.NEW_BUTTON_PROP.SIZEY = Button_YSize;
  bzGadget.NEW_BUTTON_PROP.SIZEX = Button_XSize;
  bzGadget.NEW_BUTTON_PROP.POSY = PROP.POSY + (Button_YSize *0);
  bzGadget.NEW_BUTTON_PROP.POSX = PROP.POSX + (Button_XSize *1);
  bzGadget.create_button();
  
  // Clear Hold Skip Button
  bzGadget.NEW_BUTTON_PROP.ID = 0;
  bzGadget.NEW_BUTTON_PROP.NAME = "CLEAR";
  if(Button_YSize > PROP.SIZEY)
  {
    bzGadget.NEW_BUTTON_PROP.LABEL = "CLEAR"; 
  }
  else 
  {
    bzGadget.NEW_BUTTON_PROP.LABEL = "\nCLEAR";
  }
  bzGadget.NEW_BUTTON_PROP.BCOLOR = COLOR_YELLOW;
  bzGadget.NEW_BUTTON_PROP.ENABLED = true;
  bzGadget.NEW_BUTTON_PROP.SIZEY = Button_YSize;
  bzGadget.NEW_BUTTON_PROP.SIZEX = Button_XSize;
  bzGadget.NEW_BUTTON_PROP.POSY = PROP.POSY + (Button_YSize *0);
  bzGadget.NEW_BUTTON_PROP.POSX = PROP.POSX + (Button_XSize *2);
  bzGadget.create_button();
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

  VISIBLE_UPDATE_SIGNAL.ping_up(tmeFrame_Time, VISIBLE_UPATE_TIME);

  PROP.CHANGED = true;

  // Enable gadget to display.
  if(PROP.TYPE == -1)
  {
    PROP.TYPE = 0;
    bzGadget.set_enabled("GADGET", true);
  }
}

void Radio_Channel::draw(bool Refresh, unsigned long tmeFrame_Time)
// Draw the text_box on the screen if the value has changed or if  
//  the Refresh parameter is true.
{
  // Update if the Dirty Signal indicator has changed.
  if (LINGER_DIRTY_SIGNAL.blip_moved(tmeFrame_Time) == true ||
      VISIBLE_UPDATE_SIGNAL.blip_moved(tmeFrame_Time) == true)
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
      FREQUENCY_PANEL.set_color(PROP.BCOLOR, COLOR_MAGENTA);
    } 
    else if (PROP.VALUE.FREQUENCY.IS_OPEN == true)
    {
      // Reset the linger timer.
      LINGER_DIRTY_SIGNAL.ping_up(tmeFrame_Time, LINGER_TIME);

      // Change Colors
      FREQUENCY_PANEL.set_color(COLOR_WHITE, PROP.BCOLOR);
    }
    // Outside Filter
    else if (PROP.VALUE.FREQUENCY.SIGNAL_OUTSIDE_FILTER == true)
    {
      // Reset the linger timer.
      LINGER_DIRTY_SIGNAL.ping_up(tmeFrame_Time, LINGER_TIME);

      // Change the colors.
      FREQUENCY_PANEL.set_color(COLOR_YELLOW, PROP.BCOLOR);
    } 
    // If lingering dirty signal.
    else if (LINGER_DIRTY_SIGNAL.ping_down(tmeFrame_Time) == true)
    {
      // Change the colors.
      FREQUENCY_PANEL.set_color(COLOR_YELLOW, PROP.BCOLOR);
    }
    // Updated
    else if (VISIBLE_UPDATE_SIGNAL.ping_down(tmeFrame_Time) == true)
    {
      // Change the colors.
      if(PROP.HELD == false)
      {
        FREQUENCY_PANEL.set_color(PROP.BCOLOR, COLOR_GREEN);
      }
      else
      {
        FREQUENCY_PANEL.set_color(PROP.BCOLOR, COLOR_WHITE);
      }
    }
    // Listening
    else
    {
      // Change the colors.
      FREQUENCY_PANEL.set_color(PROP.BCOLOR, PROP.COLOR);
    }

    BAR_NOISE_LEVEL.set_color(PROP.BCOLOR, BAR_NOISE_LEVEL.PROP.COLOR);
    BAR_SIGNAL_LEVEL.set_color(PROP.BCOLOR, BAR_NOISE_LEVEL.PROP.COLOR);

    // Print Values
    if (PROP.SHOW_FREQUENCY == true)
    {
      mvwprintw(FREQUENCY_PANEL.winPANEL, 0, 0, "%s %3.3f", PROP.FREQUENCY_LABEL.c_str(), ((float)PROP.VALUE.FREQUENCY.FREQUENCY / 1000000));
      mvwprintw(FREQUENCY_PANEL.winPANEL, 0, 17, "%s", (PROP.VALUE.FREQUENCY.LABEL.c_str()));
    }
    else
    {
      mvwprintw(FREQUENCY_PANEL.winPANEL, 0, 0, "%s", (PROP.VALUE.FREQUENCY.LABEL.c_str()));
    }

    //Draw Bars
    if (PROP.SHOW_SIGNAL == true)
    {
      BAR_SIGNAL_LEVEL.update(100 + PROP.VALUE.FREQUENCY.SIGNAL_LEVEL, tmeFrame_Time);
      BAR_SIGNAL_LEVEL.draw(FREQUENCY_PANEL, tmeFrame_Time);
    }
    if (PROP.SHOW_NOISE == true)
    {
      BAR_NOISE_LEVEL.update(100 + PROP.VALUE.FREQUENCY.NOISE_LEVEL, tmeFrame_Time);
      BAR_NOISE_LEVEL.draw(FREQUENCY_PANEL, tmeFrame_Time);
    }

    //Debug -- displays dedraw count and other variables.
    if (true == DEBUG_COUNTER)
    {
      Counter++;
      mvwprintw(FREQUENCY_PANEL.winPANEL, 0, 0, "%d ", Counter);
      mvwprintw(FREQUENCY_PANEL.winPANEL, 1, 0, "%d ", PROP.VALUE.FREQUENCY.CHANGED);
    }

    // Reset Properties Changed.
    PROP.VALUE.FREQUENCY.IS_OPEN = false;
    PROP.VALUE.FREQUENCY.SIGNAL_OUTSIDE_FILTER = false;
    PROP.CHANGED = false;
    WAS_REDRAWN = true;

    // Draw the Gadget.
    wrefresh(FREQUENCY_PANEL.winPANEL);
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
      bzGadget.set_enabled("GADGET", false);

      bzGadget.set_enabled("HOLD", true);
      bzGadget.set_do_not_draw("HOLD", false);

      bzGadget.set_enabled("SKIP", true);
      bzGadget.set_do_not_draw("SKIP", false);

      bzGadget.set_enabled("CLEAR", true);
      bzGadget.set_do_not_draw("CLEAR", false);

      PROP.CHANGED = true;

      return_check_click = true;
    }
    else if(Name == "HOLD")
    {
      bzGadget.set_enabled("GADGET", true);

      bzGadget.set_enabled("HOLD", false);
      bzGadget.set_do_not_draw("HOLD", true);

      bzGadget.set_enabled("SKIP", false);
      bzGadget.set_do_not_draw("SKIP", true);

      bzGadget.set_enabled("CLEAR", false);
      bzGadget.set_do_not_draw("CLEAR", true);

      PROP.CHANGED = true;

      return_check_click = true;
    }
    else if(Name == "SKIP")
    {
      bzGadget.set_enabled("GADGET", true);

      bzGadget.set_enabled("HOLD", false);
      bzGadget.set_do_not_draw("HOLD", true);

      bzGadget.set_enabled("SKIP", false);
      bzGadget.set_do_not_draw("SKIP", true);

      bzGadget.set_enabled("CLEAR", false);
      bzGadget.set_do_not_draw("CLEAR", true);

      PROP.CHANGED == true;
      

      return_check_click = true;
    }
    else if(Name == "CLEAR")
    {
      bzGadget.set_enabled("GADGET", true);

      bzGadget.set_enabled("HOLD", false);
      bzGadget.set_do_not_draw("HOLD", true);

      bzGadget.set_enabled("SKIP", false);
      bzGadget.set_do_not_draw("SKIP", true);

      bzGadget.set_enabled("CLEAR", false);
      bzGadget.set_do_not_draw("CLEAR", true);

      PROP.CHANGED == true;
      
      return_check_click = true;
    }

    PROP.CHANGED = true;

    //return_check_click = true;
  }

  return return_check_click;
}





#endif