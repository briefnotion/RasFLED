// ***************************************************************************************
// *
// *    Core       | Everything within this document is proprietary to Core Dynamics.
// *    Dynamics   | Any unauthorized duplication will be subject to prosecution.
// *
// *    Department : (R+D)^2                        Name: aircraft_coordinator.cpp
// *       Sub Dept: Programming
// *    Location ID: 856-45B
// *                                                      (c) 2856 - 2858 Core Dynamics
// ***************************************************************************************

#ifndef AIRCRAFT_COORDINATOR_CPP
#define AIRCRAFT_COORDINATOR_CPP

#include "aircraft_coordinator.h"

/*
aircraft.json
This file contains dump1090's list of recently seen aircraft. The keys are:

now:        the time this file was generated, in seconds since Jan 1 1970 00:00:00 GMT (the Unix epoch).
messages:   the total number of Mode S messages processed since dump1090 started.
aircraft:   an array of JSON objects, one per known aircraft. Each aircraft has the following keys. Keys will be omitted if data is not available.
hex:        the 24-bit ICAO identifier of the aircraft, as 6 hex digits. The identifier may start with '~', this means that the address is a non-ICAO address (e.g. from TIS-B).
squawk:     the 4-digit squawk (octal representation)
flight:     the flight name / callsign
lat, lon:   the aircraft position in decimal degrees
nucp:       the NUCp (navigational uncertainty category) reported for the position
seen_pos:   how long ago (in seconds before "now") the position was last updated
altitude:   the aircraft altitude in feet, or "ground" if it is reporting it is on the ground
vert_rate:  vertical rate in feet/minute
track:      true track over ground in degrees (0-359)
speed:      reported speed in kt. This is usually speed over ground, but might be IAS - you can't tell the difference here, sorry!
messages:   total number of Mode S messages received from this aircraft
seen:       how long ago (in seconds before "now") a message was last received from this aircraft
rssi:       recent average RSSI (signal power), in dbFS; this will always be negative.
*/


//using namespace std;
using namespace boost::property_tree;

string AIRCRAFT::simple_float_to_string(int Decimal_Positions, float Number)
{
  int c1 = 0;

  string return_string = to_string(Number);

  c1 = return_string.find(".") + 1;

  if(c1!=std::string::npos)
  {
    return_string.erase(c1 + Decimal_Positions, return_string.size() - c1 - Decimal_Positions);
  }

  return return_string;
}

int AIRCRAFT::data_count()
{
  return DATA_COUNT;
}

void AIRCRAFT::check_alerts()
{
  ALERT_ENTRY tmp_alert_entry;
  // Check Squak Codes
  if(SQUAWK.conversion_success() == true)
  {
    if (SQUAWK.get_int_value() == 1200)
    {
      tmp_alert_entry.ALERT_LEVEL = 1;
      tmp_alert_entry.ALERT = "  \\_________ SQUAWK: Visual Flight Rules (VFR)";
      ALERT_LIST.push_back(tmp_alert_entry);
      ALERT= true;
    }

    if (SQUAWK.get_int_value() == 7500)
    {
      tmp_alert_entry.ALERT_LEVEL = 3;
      tmp_alert_entry.ALERT = "  \\___ SQUAWK ALERT: Special Purpose Code - Hi-Jacking";
      ALERT_LIST.push_back(tmp_alert_entry);
      ALERT= true;
    }

    if (SQUAWK.get_int_value() == 7600)
    {        
      tmp_alert_entry.ALERT_LEVEL = 2;
      tmp_alert_entry.ALERT = "  \\___ SQUAWK ALERT: Special Purpose Code - Radio Failure";
      ALERT_LIST.push_back(tmp_alert_entry);
      ALERT= true;
    }

    if (SQUAWK.get_int_value() == 7700)
    {
      tmp_alert_entry.ALERT_LEVEL = 3;
      tmp_alert_entry.ALERT = "  \\___ SQUAWK ALERT: Special Purpose Code - Emergency";
      ALERT_LIST.push_back(tmp_alert_entry);
      ALERT= true;
    }
  }

  // Check Emergency Stat
  if (EMERGENCY.get_str_value() != "" && EMERGENCY.get_str_value() != "none")
  {
      tmp_alert_entry.ALERT_LEVEL = 3;
      tmp_alert_entry.ALERT = "  \\ EMERGENCY ALERT: " + EMERGENCY.get_str_value();
      ALERT_LIST.push_back(tmp_alert_entry);
      ALERT= true;
  }

  // Check Values
  if (D_FLIGHT_ANGLE.get_float_value() > 6)
  {
      tmp_alert_entry.ALERT_LEVEL = 2;
      tmp_alert_entry.ALERT = "  \\___ FLIGHT ANGLE: " + simple_float_to_string(1, D_FLIGHT_ANGLE.get_float_value()) + " deg";
      ALERT_LIST.push_back(tmp_alert_entry);
      ALERT= true;
  }
}

void AIRCRAFT::count_data()
{
  DATA_COUNT =  SQUAWK.conversion_success() +
                FLIGHT.conversion_success() +
                //VERSION.conversion_success() +
                SPEED.conversion_success() +
                SEEN_POS.conversion_success() +
                ALTITUDE.conversion_success() +
                ALTITUDE_GEOM.conversion_success() +
                VERT_RATE.conversion_success() +
                GEOM_RATE.conversion_success() +
                TRACK.conversion_success() +
                POSITION.LATITUDE.conversion_success() +
                POSITION.LONGITUDE.conversion_success() +
                SIL.conversion_success() +
                //(SIL_TYPE.length() > 0) +
                EMERGENCY.conversion_success() +
                //(CATAGORY.length() > 0) +
                //NAV_QNH.conversion_success() +
                NAV_HEADING.conversion_success() +
                NAV_ALTITUDE_MCP.conversion_success() +
                //NAV_MODES.conversion_success() +
                NIC.conversion_success() +
                RC.conversion_success() +
                NIC_BARO.conversion_success() +
                NAC_P.conversion_success() +
                NAC_V.conversion_success() +
                GVA.conversion_success() +
                SDA.conversion_success() 
                //MLAT.conversion_success() +
                //TISB.conversion_success()
                ;
}

void AIRCRAFT::post_process()
{
  // Convert Data to Display Standard.
  // Vertical Rate
  if (VERT_RATE.conversion_success() == true)
  {
    D_VERTICAL_RATE = VERT_RATE;
  }
  else
  {
    D_VERTICAL_RATE = GEOM_RATE;
  }

  // Calculate Flight Angle
  if (D_VERTICAL_RATE.conversion_success() == true && SPEED.conversion_success() == true )
  {
    float scent_rate  = (float)D_VERTICAL_RATE.get_int_value();
    float speed       = ((float)SPEED.get_float_value()) * (5280/ 60);

    D_FLIGHT_ANGLE.store (to_string(abs((atan( scent_rate / speed) * (180 / 3.14159)))));
  }

  // Fill Data Size Field
  count_data();

  // Fill Alert Fields.
  check_alerts();
}

bool AIRCRAFT::alert()
{
  return ALERT;
}

bool AIRCRAFT_COORDINATOR::read_json_file(string &JSON_Filename)
// Read JSON file into Property Tree
{
  bool boo_return = false;

  // No easy way to avoid all types of errors.
  try
  {
    read_json(JSON_Filename, PROPERTY_TREE);
    boo_return = true;
  }
  catch (std::exception const& e)
  {
    //boo_return = false;
  }
  return boo_return;
}

string AIRCRAFT_COORDINATOR::tree_value(string First, ptree::value_type &Branch)
// Search for First and return value from property tree.
{
  // No easy way to avoid all types of errors.
  //  Exception thrown if First cant be found.
  try
  {
    return Branch.second.get<string>(First);
  }
  catch (std::exception const& e)
  {
    return "";
  }
}

void AIRCRAFT_COORDINATOR::post_post_process()
// Calculate full aircraft data.
{
  // Convert time
  if (DATA.NOW.conversion_success() == true)
  {
    int dec_pos = DATA.NOW.get_str_value().find('.');
    if (dec_pos != string::npos)
    {
      DATA.CONVERTED_TIME.put_seconds(string_to_ulong(DATA.NOW.get_str_value().erase(dec_pos)));
      DATA.CONVERTED_TIME.put_deciseconds(string_to_int(DATA.NOW.get_str_value().erase(0, dec_pos +1)));
    }
  }
}

bool AIRCRAFT_COORDINATOR::is_active()
{
  return IS_ACTIVE;
}

bool AIRCRAFT_COORDINATOR::process(string JSON_Filename)
// Read JSON Aircraft file, parse data, and store data to the Aircraft Data list.
//  Returns true if sucessfule
//  Returns false if fails.
//    Possible reason for fail is if file not found.
{
  if (read_json_file(JSON_Filename) == true)
  {
    IS_ACTIVE = true;

    // Clear the current list for new list replacement.
    DATA.AIRCRAFTS.clear();
    DATA.POSITIONED_AIRCRAFT = 0;

    // Read data from property tree.
    try
    {
      // Safegaurd the finicky read.  
      DATA.NOW.store(PROPERTY_TREE.get<string>("now"));

      int prev_message_count = DATA.MESSAGES.get_int_value();
      DATA.MESSAGES.store(PROPERTY_TREE.get<string>("messages"));
      DATA.DELTA_MESSAGES = DATA.MESSAGES.get_int_value() - prev_message_count;

      for (ptree::value_type &aircraft : PROPERTY_TREE.get_child("aircraft"))
      {
        AIRCRAFT tmpAircraft;

        string first = "";
        string second = "";

        string tmp = "";
        string version = "";

        // Idents
        tmpAircraft.HEX.store(tree_value("hex", aircraft));
        tmpAircraft.SQUAWK.store(tree_value("squawk", aircraft));
        tmpAircraft.FLIGHT.store(tree_value("flight", aircraft));
        tmpAircraft.VERSION.store(tree_value("version", aircraft));

        // Speed Rate Positions
        tmpAircraft.SPEED.store(tree_value("gs", aircraft));
        tmpAircraft.SEEN_POS.store(tree_value("seen_pos", aircraft));
        tmpAircraft.ALTITUDE.store(tree_value("alt_baro", aircraft));
        tmpAircraft.ALTITUDE_GEOM.store(tree_value("alt_geom", aircraft));
        tmpAircraft.NAV_ALTITUDE_MCP.store(tree_value("nav_altitude_mcp", aircraft));
        tmpAircraft.VERT_RATE.store(tree_value("baro_rate", aircraft));
        tmpAircraft.GEOM_RATE.store(tree_value("geom_rate", aircraft));
        tmpAircraft.TRACK.store(tree_value("track", aircraft));
        tmpAircraft.NAV_HEADING.store(tree_value("nav_heading", aircraft));
        tmpAircraft.POSITION.LATITUDE.store(tree_value("lat", aircraft));
        tmpAircraft.POSITION.LONGITUDE.store(tree_value("lon", aircraft));
        tmpAircraft.NAV_MODES.store(tree_value("nav_modes", aircraft));
        
        // Aircraft Configuration
        tmpAircraft.EMERGENCY.store(tree_value("emergency", aircraft));
        /*  Not yet grabbing all data.
              .
              .
              .
        */

        // Radio Information
        tmpAircraft.MESSAGES.store(tree_value("messages", aircraft));
        tmpAircraft.SEEN.store(tree_value("seen", aircraft));
        tmpAircraft.RSSI.store(tree_value("rssi", aircraft));

        if(tmpAircraft.POSITION.LATITUDE.conversion_success() == true &&  tmpAircraft.POSITION.LONGITUDE.conversion_success() == true)
        {
          DATA.POSITIONED_AIRCRAFT ++;
        }

        
        tmpAircraft.post_process();

        // Store Aircraft ADS-B Data into list.
        DATA.AIRCRAFTS.push_back(tmpAircraft);
      }



      post_post_process();

      DATA.CHANGED = true;
    }
    catch (std::exception const& e)
    {
      // Do nothing
    }

    return true;
  }
  else
  {
    if(IS_ACTIVE == true)
    {
      DATA.CHANGED = true;
    }

    IS_ACTIVE = false;
    return false;
  }
}




#endif