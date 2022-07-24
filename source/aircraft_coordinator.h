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
  string LATITUDE = "";
  string LONGITUDE = "";
};

class AIRCRAFT
{
  public:
  /*
  string HEX = "";
  long SQUAWK = 0;
  string FLIGHT = "";
  GLOBAL_POSITION POSITION;
  string NUCP = "";
  long SEEN_POS = 0;
  long ALTITUDE = 0;
  long VERT_RATE = 0;
  long TRACK = 0;
  long SPEED = 0;
  long MESSAGES = 0;
  long SEEN = 0;
  long RSSI = 0;
  */

  string HEX = "";
  string SQUAWK = "";
  string FLIGHT = "";
  GLOBAL_POSITION POSITION;
  string NUCP = "";
  string SEEN_POS = "";
  string ALTITUDE = "";
  string VERT_RATE = "";
  string TRACK = "";
  string SPEED = "";
  string MESSAGES = "";
  string SEEN = "";
  string RSSI = "";
};

class AIRCRAFT_DATA
{
  public:
  float NOW = 0;
  long MESSAGES = 0;
  deque<AIRCRAFT> AIRCRAFTS;
};

class AIRCRAFT_COORDINATOR
{
  private:
  ptree PROPERTY_TREE;

  public:
  AIRCRAFT_DATA DATA;

  string data = "";

  private:
  bool read_json_file()
  {
    bool boo_return = false;
    
    //PROPERTY_TREE.clear();

    try
    {
      read_json(FILES_AIRCRAFT_JSON, PROPERTY_TREE);
      boo_return = true;
    }
    catch (std::exception const& e)
    {
      //boo_return = false;
    }
    return boo_return;
  }

  string tree_value(string First, ptree::value_type &Branch)
  {
    try
    {
      return Branch.second.get<string>(First);
    }
    catch (std::exception const& e)
    {
      return "";
    }
  }

/*
{ "now" : 1658364366.8,
  "messages" : 65,
  "aircraft" : [
    {
      "hex":"ae0113",
      "alt_baro":23000,
      "version":2,
      "nic_baro":1,
      "nac_p":10,
      "sil":3,
      "sil_type":"perhour",
      "gva":2,
      "sda":2,
      "mlat":[],
      "tisb":[],
      "messages":9,
      "seen":4.9,
      "rssi":-28.8
    },  
    {
      "hex":"a84dce",
      "version":0,
      "mlat":[],
      "tisb":[],
      "messages":11,
      "seen":111.7,
      "rssi":-29.8
    }
  ]
}
*/

  public:
  bool process()
  {
    if (read_json_file() == true)
    {
      

      DATA.AIRCRAFTS.clear();

      DATA.NOW = PROPERTY_TREE.get<float>("now");
      DATA.MESSAGES = PROPERTY_TREE.get<long>("messages");
      
      for (ptree::value_type &aircraft : PROPERTY_TREE.get_child("aircraft"))
      {
        
        AIRCRAFT tmpAircraft;

        string first = "";
        string second = "";

        string tmp = "";
        string version = "";

        tmpAircraft.HEX = tree_value("hex", aircraft);
        tmpAircraft.MESSAGES = tree_value("messages", aircraft);
        tmpAircraft.SEEN = tree_value("seen", aircraft);
        tmpAircraft.RSSI = tree_value("rssi", aircraft);

        tmpAircraft.SQUAWK = tree_value("squawk", aircraft);
        tmpAircraft.FLIGHT = tree_value("flight", aircraft);
        tmpAircraft.NUCP = tree_value("nucp", aircraft);

        //tmpAircraft.POSITION = tree_value("mlat[]", aircraft);
        tmpAircraft.SEEN_POS = tree_value("seen_pos", aircraft);
        tmpAircraft.ALTITUDE = tree_value("alt_baro", aircraft);
        //tmpAircraft.ALTITUDE = tree_value("alt_geom", aircraft);
        //tmpAircraft.VERT_RATE = tree_value("vert_rate", aircraft);
        tmpAircraft.VERT_RATE = tree_value("baro_rate", aircraft);
        tmpAircraft.TRACK = tree_value("track", aircraft);
        tmpAircraft.SPEED = tree_value("speed", aircraft);
        tmpAircraft.SPEED = tree_value("gs", aircraft);
        
        //tmpAircraft.SPEED = tree_value("gs", aircraft);
        //tmpAircraft.SPEED = tree_value("baro_rate", aircraft);
        //tmpAircraft.SPEED = tree_value("version", aircraft);
        //tmpAircraft.SPEED = tree_value("nac_p", aircraft);
        //tmpAircraft.SPEED = tree_value("sil", aircraft);
        //tmpAircraft.SPEED = tree_value("sil_type", aircraft);

        //tmpAircraft.SPEED = tree_value("gs", aircraft);
        //tmpAircraft.SPEED = tree_value("tisb[]", aircraft);
        //tmpAircraft.SPEED = tree_value("flight", aircraft);
        //tmpAircraft.SPEED = tree_value("category", aircraft);
        //tmpAircraft.SPEED = tree_value("nav_qnh", aircraft);
        //tmpAircraft.SPEED = tree_value("nav_heading", aircraft);
        //tmpAircraft.SPEED = tree_value("nic_baro", aircraft);
        //tmpAircraft.SPEED = tree_value("nac_p", aircraft);
        //tmpAircraft.SPEED = tree_value("nac_v", aircraft);

        //tmpAircraft.SPEED = tree_value("gva", aircraft);
        //tmpAircraft.SPEED = tree_value("sda", aircraft);
        //tmpAircraft.SPEED = tree_value("flight", aircraft);
        //tmpAircraft.SPEED = tree_value("category", aircraft);
        //tmpAircraft.SPEED = tree_value("nav_qnh", aircraft);
        //tmpAircraft.SPEED = tree_value("nav_heading", aircraft);
        //tmpAircraft.SPEED = tree_value("nic_baro", aircraft);
        //tmpAircraft.SPEED = tree_value("nac_p", aircraft);
        //tmpAircraft.SPEED = tree_value("nac_v", aircraft);



        DATA.AIRCRAFTS.push_back(tmpAircraft);
      }
      


      return true;
    }
    else
    {
      return false;
    }
  }

};


#endif