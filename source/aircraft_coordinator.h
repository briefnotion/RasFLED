// ***************************************************************************************
// *
// *    Core       | Everything within this document is proprietary to Core Dynamics.
// *    Dynamics   | Any unauthorized duplication will be subject to prosecution.
// *
// *    Department : (R+D)^2                        Name: aircraft_coordinator.h
// *       Sub Dept: Programming
// *    Location ID: 856-45B
// *                                                      (c) 2856 - 2858 Core Dynamics
// ***************************************************************************************

#ifndef AIRCRAFT_COORDINATOR_H
#define AIRCRAFT_COORDINATOR_H

#include <deque>

#include <string.h>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>


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

class GLOBAL_POSITION
{
  public:
  STRING_FLOAT LATITUDE;
  STRING_FLOAT LONGITUDE;
};

class AIRCRAFT
{
  private:
  // Data Status
  int DATA_COUNT = 0;
  bool ALERT = false;

  public:

  // VARIABLES            // DESCRIPTION                                EXAMPLE
  // Idents
  STRING_STRING HEX;      // Hex Identifier                             "hex":"a8e85f"
  STRING_INT SQUAWK;      // Squawk Code Identifier                     "squawk":"4327"
  STRING_STRING FLIGHT;   // Flight Code                                "flight":"RLC673  "
  STRING_INT VERSION;     // ADS-B Version                              "version":2

  // Speed Rate Positions
  STRING_FLOAT SPEED;     // Ground Speed                               "gs":135.1
  STRING_FLOAT SEEN_POS;  // Seen Pos                                   "seen_pos":6.6
  STRING_INT ALTITUDE;    // Aircaft Altitude from Sea Level            "alt_baro":300
  STRING_INT ALTITUDE_GEOM;  // UNKNOWN                                 "alt_geom":425
  STRING_INT VERT_RATE;   // Vertical Assend or Desend Rate             "baro_rate":0
  STRING_INT GEOM_RATE;   // UNKNOWN                                    "geom_rate":-384
  STRING_FLOAT TRACK;     // Track (magnetic or polar?)                 "track":315.9

  GLOBAL_POSITION POSITION; // Lat Lon Position                         "lat":30.121399
                            //                                          "lon":-92.435033

  // Aircraft Configuration
  STRING_INT SIL;         // UNKNOWN                                    "sil":3
  STRING_STRING SIL_TYPE; // UNKNOWN                                    "sil_type":"perhour"
  STRING_STRING EMERGENCY;// UNKNOWN                                    "emergency":"none"
  STRING_STRING CATAGORY; // UNKNOWN                                    "category":"A7"
  STRING_FLOAT NAV_QNH;     // Selected Sea Level Pressure (MSLP)       "nav_qnh":1012.8
  STRING_FLOAT NAV_HEADING; // Selected Nav Heading                      "nav_heading":347.3
  STRING_INT NAV_ALTITUDE_MCP; // UNKNOWN                               "nav_altitude_mcp":36992
  STRING_STRING NAV_MODES;  // UNKNOWN                                  "nav_modes":["autopilot","althold","tcas"]
  STRING_INT NIC ;        // UNKNOWN                                    "nic":8
  STRING_INT RC;          // UNKNOWN                                    "rc":186
  STRING_FLOAT NIC_BARO;  // UNKNOWN                                    "nic_baro":0
  STRING_INT NAC_P;       // Aircraft Operational                       "nac_p":10
  STRING_INT NAC_V;       // Airborne Velocity                          "nac_v":2
  STRING_INT GVA;         // Airborne Operational                       "gva":2
  STRING_INT SDA;         // UNKNOWN                                    "sda":2
  STRING_STRING MLAT;     // UNKNOWN                                    "mlat":[]
  STRING_STRING TISB;     // UNKNOWN                                    "tisb":[]

  // Radio Information
  STRING_INT MESSAGES;    // Message Count Received.                    "messages":261
  STRING_FLOAT SEEN;        // Seconds since last                         "seen":209.0
                          //  received message (300 second expiration)
  STRING_FLOAT RSSI;      // Signal Strength                            "rssi":-28.4

  int data_count()
  {
    return DATA_COUNT;
  }

  void count_data()
  {
    DATA_COUNT =  SQUAWK.conversion_success() +
                  //FLIGHT.conversion_success() +
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
                  //EMERGENCY.conversion_success() +
                  //(CATAGORY.length() > 0) +
                  NAV_QNH.conversion_success() +
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
};

class AIRCRAFT_DATA
{
  public:
  float NOW = 0;
  long MESSAGES = 0;
  deque<AIRCRAFT> AIRCRAFTS;
  
  bool CHANGED = false;
};

class AIRCRAFT_COORDINATOR
{
  private:
  ptree PROPERTY_TREE;

  //bool PREPARED = false;

  public:
  AIRCRAFT_DATA DATA;

  string data = "";

  private:

  bool read_json_file(string &JSON_Filename)
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

  string tree_value(string First, ptree::value_type &Branch)
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

  public:
  bool process(string JSON_Filename)
  // Read JSON Aircraft file, parse data, and store data to the Aircraft Data list.
  //  Returns true if sucessfule
  //  Returns false if fails.
  //    Possible reason for fail is if file not found.
  {
    if (read_json_file(JSON_Filename) == true)
    {
      // Clear the current list for new list replacement.
      DATA.AIRCRAFTS.clear();

      // Read data from property tree.
      DATA.NOW = PROPERTY_TREE.get<float>("now");
      DATA.MESSAGES = PROPERTY_TREE.get<long>("messages");
      
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
        tmpAircraft.VERT_RATE.store(tree_value("baro_rate", aircraft));
        tmpAircraft.GEOM_RATE.store(tree_value("geom_rate", aircraft));
        tmpAircraft.TRACK.store(tree_value("track", aircraft));
        tmpAircraft.POSITION.LATITUDE.store(tree_value("lat", aircraft));
        tmpAircraft.POSITION.LONGITUDE.store(tree_value("lon", aircraft));
        
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

        tmpAircraft.count_data();

        // Store Aircraft ADS-B Data into list.
        DATA.AIRCRAFTS.push_back(tmpAircraft);
      }

      DATA.CHANGED = true;
      
      return true;
    }
    else
    {
      return false;
    }
  }

};


#endif