// ***************************************************************************************
// *
// *    Core       | Everything within this document is proprietary to Core Dynamics.
// *    Dynamics   | Any unauthorized duplication will be subject to prosecution.
// *
// *    Department : (R+D)^2                        Name: auto.h
// *       Sub Dept: Programming
// *    Location ID: 856-45B
// *                                                      (c) 2856 - 2858 Core Dynamics
// ***************************************************************************************

#ifndef AUTO_H
#define AUTO_H

// Standard Header Files
#include <stdio.h>
#include <string.h>
#include <deque>

#include "fled_time.h"
#include "stringthings.h"
#include "helper.h"

#include "comport.h"

using namespace std;

class AUTOMOBILE_DATA_LINE
{
  public:

  string ORIG = "";

  int ID = 0;
  int DATA[8];
};

class AUTOMOBILE_DATA
{
  public:

  // AD_C0  - Fuel % hex 3A
  // 00 C0 20 2D AC 27 50 00 3A 04

  // Hex 41 Engine Temp (C)
  // 01 00 80 00 41 A9 82 04 03 46

  AUTOMOBILE_DATA_LINE AD_0;
  AUTOMOBILE_DATA_LINE AD_10; //  16  - Steering Wheeal Rate and Torue
  AUTOMOBILE_DATA_LINE AD_30;
  AUTOMOBILE_DATA_LINE AD_32;
  AUTOMOBILE_DATA_LINE AD_4A;
  AUTOMOBILE_DATA_LINE AD_4B;
  AUTOMOBILE_DATA_LINE AD_50;
  AUTOMOBILE_DATA_LINE AD_60;
  AUTOMOBILE_DATA_LINE AD_64;
  AUTOMOBILE_DATA_LINE AD_6A;
  AUTOMOBILE_DATA_LINE AD_70; //  112? - Tourqe at Trans
  AUTOMOBILE_DATA_LINE AD_80; //  128? - TPS or Break thing
  AUTOMOBILE_DATA_LINE AD_90; //  144?  - RPM
  AUTOMOBILE_DATA_LINE AD_A0;
  AUTOMOBILE_DATA_LINE AD_B0;
  AUTOMOBILE_DATA_LINE AD_C0; // 192?  - Guages? Fuel % hex 3A
  AUTOMOBILE_DATA_LINE AD_C8; // 200? - Headlamp status, Ignition Status, Parking Brake Status
  AUTOMOBILE_DATA_LINE AD_D0; // 208? - Gear Lever Status, Transmission Gear Position
  AUTOMOBILE_DATA_LINE AD_E0;
  AUTOMOBILE_DATA_LINE AD_F0; //  240 - Velocity (1,2) and Transmission Gear (3)
  AUTOMOBILE_DATA_LINE AD_F8;
  AUTOMOBILE_DATA_LINE AD_100;  //  256?  - Guages Hex 41 Engine Temp (C)
  AUTOMOBILE_DATA_LINE AD_102;
  AUTOMOBILE_DATA_LINE AD_120;
  AUTOMOBILE_DATA_LINE AD_128;
  AUTOMOBILE_DATA_LINE AD_130;  //  304?  - Speed
  AUTOMOBILE_DATA_LINE AD_138;
  AUTOMOBILE_DATA_LINE AD_140;  // - Actual Stearing Effort?
  AUTOMOBILE_DATA_LINE AD_150;
  AUTOMOBILE_DATA_LINE AD_160;
  AUTOMOBILE_DATA_LINE AD_17E;
  AUTOMOBILE_DATA_LINE AD_180;
  AUTOMOBILE_DATA_LINE AD_190;
  AUTOMOBILE_DATA_LINE AD_1A0;
  AUTOMOBILE_DATA_LINE AD_1C0;
  AUTOMOBILE_DATA_LINE AD_1D0;
  AUTOMOBILE_DATA_LINE AD_1E0;
  AUTOMOBILE_DATA_LINE AD_200;  // 512? - Fuel Consumed From Start
  AUTOMOBILE_DATA_LINE AD_208;
  AUTOMOBILE_DATA_LINE AD_210;
  AUTOMOBILE_DATA_LINE AD_213;  // 531? - Break Pressure?
  AUTOMOBILE_DATA_LINE AD_218;  //  536? - Odometer
  AUTOMOBILE_DATA_LINE AD_247;
  AUTOMOBILE_DATA_LINE AD_252;
  AUTOMOBILE_DATA_LINE AD_253;
  AUTOMOBILE_DATA_LINE AD_260;  // 608?  - Auto Start Stop Button?
  AUTOMOBILE_DATA_LINE AD_270;
  AUTOMOBILE_DATA_LINE AD_280;
  AUTOMOBILE_DATA_LINE AD_290;
  AUTOMOBILE_DATA_LINE AD_2B0;
  AUTOMOBILE_DATA_LINE AD_2C0;  // 704?   - RPM delta or Request timing??
  AUTOMOBILE_DATA_LINE AD_2D0;
  AUTOMOBILE_DATA_LINE AD_2D4;
  AUTOMOBILE_DATA_LINE AD_2D8;
  AUTOMOBILE_DATA_LINE AD_2F0;
  AUTOMOBILE_DATA_LINE AD_310;
  AUTOMOBILE_DATA_LINE AD_318;
  AUTOMOBILE_DATA_LINE AD_340;
  AUTOMOBILE_DATA_LINE AD_360;  // 864? -High Beam Status ?
  AUTOMOBILE_DATA_LINE AD_380;  // 896? - Fuel Level
  AUTOMOBILE_DATA_LINE AD_388;
  AUTOMOBILE_DATA_LINE AD_390;
  AUTOMOBILE_DATA_LINE AD_398;
  AUTOMOBILE_DATA_LINE AD_3B4;
  AUTOMOBILE_DATA_LINE AD_400;
  AUTOMOBILE_DATA_LINE AD_405;
  AUTOMOBILE_DATA_LINE AD_40A;
  AUTOMOBILE_DATA_LINE AD_435;
  AUTOMOBILE_DATA_LINE AD_455;
  AUTOMOBILE_DATA_LINE AD_581;
  AUTOMOBILE_DATA_LINE AD_5E2;
  AUTOMOBILE_DATA_LINE AD_FFFF;

  AUTOMOBILE_DATA_LINE AD_UNKNOWN;
};

class AUTOMOBILE_BRAKE_PRESSURE
{
  private:
  int VAL_PRESSURE;

  string PRESSURE;

  public:

  void store(int Pressure);
  int val_pressure();
  string pressure();
};

class AUTOMOBILE_RPM
{
  private:
  int VAL_RPM;

  string RPM;

  public:

  void store(int Rpm);
  int val_rpm();
  string rpm();
};

class AUTOMOBILE_STEERING
{
  private:
  int REPORTED_STEERING_WHEEL_ANGLE = 0;
  bool CLOCKWISE = false;

  float VAL_STEERING_WHEEL_ANGLE;
  string STEERING_WHEEL_ANGLE;
  string DIRECTION = "XX";

  public:

  void store_steering_wheel_angle(int Angle, int Direction);
  float val_steering_wheel_angle();
  string steering_wheel_angle();
  string turning_direction();
  bool clockwise();
};

class AUTOMOBILE_VELOCITY
{
  private:
  float KMPH_X_10 = 0;
  float MPH_X_10 = 0;
  string KMPH;
  string MPH;

  public:

  void store(int kmph, float Multiplier);
  float kmph_x_10();
  float mph_x_10();
  string kmph();
  string mph();
};

class AUTOMOBILE_TEMPATURE
{
  public:

  float CELSIUS = 0;
  float FAHRENHEIT = 0;
};

class AUTOMOBILE_TRANSMISSION_GEAR
{
  private:
  
  int REPORTED = 0;
  string SHORT_DESC = " ";
  string LONG_DESC = " ";
  
  public:

  void store(int gear);
  int reported();
  string short_desc();
  string long_desc();
};

class AUTOMOBILE_TRANSLATED_DATA
{
  public:

  AUTOMOBILE_STEERING STEERING;
  AUTOMOBILE_TRANSMISSION_GEAR GEAR;
  AUTOMOBILE_VELOCITY SPEED;
  AUTOMOBILE_TEMPATURE COOLANT_TEMP;
  AUTOMOBILE_RPM RPM;
  AUTOMOBILE_BRAKE_PRESSURE BRAKE_PRESSURE;
};

class AUTOMOBILE_PROPERTIES
// Panel border characters.
{
  public:
  
  bool SAVE_TO_LOG = false;
  string SAVE_LOG_FILENAME = "";
};

class AUTOMOBILE
{
  private:

  void parse(string Line);

  public:

  bool CHANGED = false;

  AUTOMOBILE_DATA DATA;
  AUTOMOBILE_TRANSLATED_DATA STATUS;
  AUTOMOBILE_PROPERTIES PROPS;

  int message_count = 0;

  void process(COMPORT &Com_Port);

  void translate();
};





#endif