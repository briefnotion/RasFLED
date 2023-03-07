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

  if (POSITION.LATITUDE.conversion_success() == true && 
      POSITION.LONGITUDE.conversion_success() == true)
  {
    POSITION.GLOBAL_POSITION_FOUND = true;
  }
  else
  {
    POSITION.GLOBAL_POSITION_FOUND = false;
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

bool AIRCRAFT_COORDINATOR::process(string JSON_Text)
{
  bool ret_success = false;

  if (AIRCRAFT_JSON.load_json_from_string(JSON_Text))
  {
    IS_ACTIVE = true;

    // Clear the current list for new list replacement.
    DATA.AIRCRAFTS.clear();
    DATA.POSITIONED_AIRCRAFT = 0;

    for(int root = 0; root < AIRCRAFT_JSON.ROOT.DATA.size(); root++)
    {
      // Load Top Level Messages
      if (AIRCRAFT_JSON.ROOT.DATA[root].label() == "now")
      {
        DATA.NOW.store(AIRCRAFT_JSON.ROOT.DATA[root].value());
      }
      if (AIRCRAFT_JSON.ROOT.DATA[root].label() == "messages")
      {
        int prev_message_count = DATA.MESSAGES.get_int_value();
        DATA.MESSAGES.store(AIRCRAFT_JSON.ROOT.DATA[root].value());
        DATA.DELTA_MESSAGES = DATA.MESSAGES.get_int_value() - prev_message_count;
      }

      // Process Aircraft List
      if (AIRCRAFT_JSON.ROOT.DATA[root].label() == "aircraft")
      {
        for (int aircraft_list = 0; 
              aircraft_list < AIRCRAFT_JSON.ROOT.DATA[root].DATA.size(); aircraft_list++)
        {
          // For Each Aircraft

          AIRCRAFT tmpAircraft;

          string first = "";
          string second = "";

          string tmp = "";
          string version = "";

          // Process Messages in Aircraft
          for (int data_element = 0; 
                data_element < AIRCRAFT_JSON.ROOT.DATA[root].DATA[aircraft_list].DATA.size(); data_element++)
          {
            // For Each Data Element

            // Idents
            AIRCRAFT_JSON.ROOT.DATA[root].DATA[aircraft_list].DATA[data_element].get_if_is("hex", tmpAircraft.HEX);
            AIRCRAFT_JSON.ROOT.DATA[root].DATA[aircraft_list].DATA[data_element].get_if_is("squawk", tmpAircraft.SQUAWK);
            AIRCRAFT_JSON.ROOT.DATA[root].DATA[aircraft_list].DATA[data_element].get_if_is("flight", tmpAircraft.FLIGHT);
            AIRCRAFT_JSON.ROOT.DATA[root].DATA[aircraft_list].DATA[data_element].get_if_is("version", tmpAircraft.VERSION);
            
            // Speed Rate Positions
            AIRCRAFT_JSON.ROOT.DATA[root].DATA[aircraft_list].DATA[data_element].get_if_is("gs", tmpAircraft.SPEED);
            AIRCRAFT_JSON.ROOT.DATA[root].DATA[aircraft_list].DATA[data_element].get_if_is("seen_pos", tmpAircraft.SEEN_POS);
            AIRCRAFT_JSON.ROOT.DATA[root].DATA[aircraft_list].DATA[data_element].get_if_is("alt_baro", tmpAircraft.ALTITUDE);
            AIRCRAFT_JSON.ROOT.DATA[root].DATA[aircraft_list].DATA[data_element].get_if_is("alt_geom", tmpAircraft.ALTITUDE_GEOM);
            AIRCRAFT_JSON.ROOT.DATA[root].DATA[aircraft_list].DATA[data_element].get_if_is("nav_altitude_mcp", tmpAircraft.NAV_ALTITUDE_MCP);
            AIRCRAFT_JSON.ROOT.DATA[root].DATA[aircraft_list].DATA[data_element].get_if_is("baro_rate", tmpAircraft.VERT_RATE);
            AIRCRAFT_JSON.ROOT.DATA[root].DATA[aircraft_list].DATA[data_element].get_if_is("geom_rate", tmpAircraft.GEOM_RATE);
            AIRCRAFT_JSON.ROOT.DATA[root].DATA[aircraft_list].DATA[data_element].get_if_is("track", tmpAircraft.TRACK);
            AIRCRAFT_JSON.ROOT.DATA[root].DATA[aircraft_list].DATA[data_element].get_if_is("nav_heading", tmpAircraft.NAV_HEADING);
            AIRCRAFT_JSON.ROOT.DATA[root].DATA[aircraft_list].DATA[data_element].get_if_is("lat", tmpAircraft.POSITION.LATITUDE);
            AIRCRAFT_JSON.ROOT.DATA[root].DATA[aircraft_list].DATA[data_element].get_if_is("lon", tmpAircraft.POSITION.LONGITUDE);
            AIRCRAFT_JSON.ROOT.DATA[root].DATA[aircraft_list].DATA[data_element].get_if_is("nav_modes", tmpAircraft.NAV_MODES);

            // Aircraft Configuration
            AIRCRAFT_JSON.ROOT.DATA[root].DATA[aircraft_list].DATA[data_element].get_if_is("emergency", tmpAircraft.EMERGENCY);
            
            //  Not yet grabbing all data.
            //      .
            //      .
            //      .

            // Radio Information
            AIRCRAFT_JSON.ROOT.DATA[root].DATA[aircraft_list].DATA[data_element].get_if_is("messages", tmpAircraft.MESSAGES);
            AIRCRAFT_JSON.ROOT.DATA[root].DATA[aircraft_list].DATA[data_element].get_if_is("seen", tmpAircraft.SEEN);
            AIRCRAFT_JSON.ROOT.DATA[root].DATA[aircraft_list].DATA[data_element].get_if_is("rssi", tmpAircraft.RSSI);
          }

          if(tmpAircraft.POSITION.LATITUDE.conversion_success() == true &&  tmpAircraft.POSITION.LONGITUDE.conversion_success() == true)
          {
            DATA.POSITIONED_AIRCRAFT ++;
          }

          // Process Data Recieved on Aircraft
          tmpAircraft.post_process();

          // Store Aircraft ADS-B Data into list.
          DATA.AIRCRAFTS.push_back(tmpAircraft);
        }
      }
    }

    // Process Data Recieved on All Aircraft
    post_post_process();
    DATA.CHANGED = true;
    ret_success = true;
  }  
  else
  {
    if(IS_ACTIVE == true)
    {
      DATA.CHANGED = true;
    }

    IS_ACTIVE = false;
    ret_success = false;
  }

  return ret_success;
}



#endif