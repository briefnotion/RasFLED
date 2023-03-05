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
#include <string>
#include <math.h>

// RASFled related header files
#include "stringthings.h"
#include "fled_time.h"
#include "json_interface.h"

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

class ALERT_ENTRY
{
  public:
  int ALERT_LEVEL;
  string ALERT;
};

class GLOBAL_POSITION
{
  public:
  STRING_FLOAT LATITUDE;
  STRING_FLOAT LONGITUDE;

  bool GLOBAL_POSITION_FOUND = false;
};

class AIRCRAFT
{
  private:
  // Data Status
  int DATA_COUNT = 0;
  bool ALERT = false;

  public:
  
  // Alert List
  deque<ALERT_ENTRY> ALERT_LIST;

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

  // Display Data
  STRING_INT D_VERTICAL_RATE;
  STRING_FLOAT D_FLIGHT_ANGLE;

  // Radio Information
  STRING_INT MESSAGES;    // Message Count Received.                    "messages":261
  STRING_FLOAT SEEN;      // Seconds since last                         "seen":209.0
                          //  received message (300 second expiration)
  STRING_FLOAT RSSI;      // Signal Strength                            "rssi":-28.4

  string simple_float_to_string(int Decimal_Positions, float Number);

  int data_count();

  void check_alerts();

  void count_data();

  void post_process();

  bool alert();
};

class AIRCRAFT_DATA
{
  public:
  STRING_FLOAT NOW;
  STRING_INT MESSAGES;
  deque<AIRCRAFT> AIRCRAFTS;
  int POSITIONED_AIRCRAFT = 0;

  FLED_TIME_VAR CONVERTED_TIME;

  int DELTA_MESSAGES = 0;
  
  bool CHANGED = false;
};

class AIRCRAFT_COORDINATOR
{
  private:

  bool IS_ACTIVE = false;

  JSON_INTERFACE AIRCRAFT_JSON;

  public:
  AIRCRAFT_DATA DATA;

  private:

  void post_post_process();

  public:

  bool is_active();

  bool process(string JSON_Text);
};


#endif