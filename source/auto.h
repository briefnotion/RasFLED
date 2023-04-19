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

  // (((256*A)+B)/3+22/3)*0.145=32. 

  AUTOMOBILE_DATA_LINE AD_0;
  AUTOMOBILE_DATA_LINE AD_10;   //* 16  - Steering Wheeal Rate and Torue
                                //  00 10 0F 37 00 31 00 10 80 C8
  AUTOMOBILE_DATA_LINE AD_30;
  AUTOMOBILE_DATA_LINE AD_32;
  AUTOMOBILE_DATA_LINE AD_4A;
  AUTOMOBILE_DATA_LINE AD_4B;
  AUTOMOBILE_DATA_LINE AD_50;
  AUTOMOBILE_DATA_LINE AD_60;
  AUTOMOBILE_DATA_LINE AD_64;
  AUTOMOBILE_DATA_LINE AD_6A;
  AUTOMOBILE_DATA_LINE AD_70;   //  112? - Tourqe at Trans
                                //  Torque at Trans bit 25. 1 byte
                                //  00 70 0A 8F 0A 24 6A 24 FA 24
  AUTOMOBILE_DATA_LINE AD_80;   //* 128 - Power or Torque
                                //  00 80 90 00 7D 00 00 80 21 F7

  AUTOMOBILE_DATA_LINE AD_90;   //* 144  - RPM
  AUTOMOBILE_DATA_LINE AD_A0;
  AUTOMOBILE_DATA_LINE AD_B0;
  AUTOMOBILE_DATA_LINE AD_C0;   //? 192 - Guages? Fuel % hex 3A
  AUTOMOBILE_DATA_LINE AD_C8;   //* 200 - Headlamp status, Ignition Status, Parking Brake Status
  AUTOMOBILE_DATA_LINE AD_D0;   // 208? - Gear Lever Status, Transmission Gear Position
  AUTOMOBILE_DATA_LINE AD_E0;
  AUTOMOBILE_DATA_LINE AD_F0;   //* 240 - Velocity (1,2) and Transmission Gear (3)
  AUTOMOBILE_DATA_LINE AD_F8;
  AUTOMOBILE_DATA_LINE AD_100;  //  256?  - Guages Hex 41 Engine Temp (C)
  AUTOMOBILE_DATA_LINE AD_102;
  AUTOMOBILE_DATA_LINE AD_120;
  AUTOMOBILE_DATA_LINE AD_128;
  AUTOMOBILE_DATA_LINE AD_130;  //? 304 - Speed
  AUTOMOBILE_DATA_LINE AD_138;
  AUTOMOBILE_DATA_LINE AD_140;  // - Actual Stearing Effort?
  AUTOMOBILE_DATA_LINE AD_150;
  AUTOMOBILE_DATA_LINE AD_160;
  AUTOMOBILE_DATA_LINE AD_17E;
  AUTOMOBILE_DATA_LINE AD_180;
  AUTOMOBILE_DATA_LINE AD_190;  //* - Tire Speed
  AUTOMOBILE_DATA_LINE AD_1A0;
  AUTOMOBILE_DATA_LINE AD_1C0;
  AUTOMOBILE_DATA_LINE AD_1D0;
  AUTOMOBILE_DATA_LINE AD_1E0;
  AUTOMOBILE_DATA_LINE AD_200;  //* 512 - Fuel Consumed From Start
  AUTOMOBILE_DATA_LINE AD_208;  //  02 08 7E F4 29 E6 40 84 FF 18
  AUTOMOBILE_DATA_LINE AD_210;  //  02 10 00 00 00 00 F2 9B 00 00
  AUTOMOBILE_DATA_LINE AD_213;  //? 531 - Break Pressure?
  AUTOMOBILE_DATA_LINE AD_218;  //? 536 - Odometer
  AUTOMOBILE_DATA_LINE AD_247;
  AUTOMOBILE_DATA_LINE AD_252;  //  02 52 00 00 00 0F FF 20 00 60 *
  AUTOMOBILE_DATA_LINE AD_253;  //  02 10 00 00 00 00 FA 8B 00 00
  AUTOMOBILE_DATA_LINE AD_260;  //? 608 - Auto Start Stop Button?
                                //  02 60 88 82 00 0E 25 61 90 00
  AUTOMOBILE_DATA_LINE AD_270;  //  02 70 5E 4A 04 21 00 00 00 00
  AUTOMOBILE_DATA_LINE AD_280;  //  02 80 46 30 9E 72 05 12 C0 00
  AUTOMOBILE_DATA_LINE AD_290;  //  02 90 06 00 00 00 00 02 D2 0A *
                                //  02 90 06 00 00 00 00 02 D4 0A  
                                //  02 90 06 00 00 00 00 02 C1 0A
  AUTOMOBILE_DATA_LINE AD_2B0;  //  02 B0 2D FE 7B 46 80 00 22 1F
  AUTOMOBILE_DATA_LINE AD_2C0;  //? 704 - RPM delta or Request timing??
  AUTOMOBILE_DATA_LINE AD_2D0;  //  02 D0 00 00 01 FB 73 D0 5A 85
  AUTOMOBILE_DATA_LINE AD_2D4;  //  02 D4 00 00 00 00 BD FE FF FE
  AUTOMOBILE_DATA_LINE AD_2D8;  //  02 D8 04 00 00 80 00 00 00 00
  AUTOMOBILE_DATA_LINE AD_2F0;  //  02 F0 34 30 00 56 79 8D 92 60
  AUTOMOBILE_DATA_LINE AD_310;  //  03 10 D1 40 30 60 1D 42 00 6B
  AUTOMOBILE_DATA_LINE AD_318;  //  
  AUTOMOBILE_DATA_LINE AD_340;  //  03 40 00 00 00 00 03 0A 66 4A
  AUTOMOBILE_DATA_LINE AD_360;  //* 864 -High Beam Status and doors?
  AUTOMOBILE_DATA_LINE AD_380;  //* 896 - Fuel Level
  AUTOMOBILE_DATA_LINE AD_388;
  AUTOMOBILE_DATA_LINE AD_390;  //  03 90 00 00 00 00 0D 52 00 00
  AUTOMOBILE_DATA_LINE AD_398;  //  03 98 11 40 50 32 41 53 54 36
  AUTOMOBILE_DATA_LINE AD_3B4;  //  03 88 00 00 47 45 46 87 28 50
  AUTOMOBILE_DATA_LINE AD_400;  //  temp according to chat
                                //  04 00 24 00 00 00 00 00 00 00
  AUTOMOBILE_DATA_LINE AD_405;  //  04 05 01 67 67 13 ED 45 08 9C
  AUTOMOBILE_DATA_LINE AD_40A;  //  04 0A FF 16 21 00 21 01 10 00
  AUTOMOBILE_DATA_LINE AD_435;  //  04 35 B2 28 91 DC FF D7 C3 E4
  AUTOMOBILE_DATA_LINE AD_455;  //  04 55 00 00 00 00 00 00 00 00
  AUTOMOBILE_DATA_LINE AD_581;  //  05 81 81 00 FF FF FF FF FF FF
  AUTOMOBILE_DATA_LINE AD_5E2;  //  05 E2 62 00 FF FF FF FF FF FF
  AUTOMOBILE_DATA_LINE AD_FFFF;

  AUTOMOBILE_DATA_LINE AD_UNKNOWN;
};

class VELOCITY
{
  private:

  float KMPH = 0;
  float MPH = 0;
  string KMPH_DISP;
  string MPH_DISP;

  public:

  void store(float kmps);
  float val_kmph();
  float val_mph();
  string kmph();
  string mph();

};

class AUTOMOBILE_DOORS
{
  private:

  bool LF_DOOR_OPEN = false;
  bool RF_DOOR_OPEN = false;
  bool LB_DOOR_OPEN = false;
  bool RB_DOOR_OPEN = false;

  bool HATCHBACK_DOOR_OPEN = false;

  //bool MOONROOF_DOOR_OPEN = false;  // Not Implemented

  bool HOOD_DOOR_OPEN = false;

  bool AVAILABLE = true;

  public:

  void store(int Data);
  bool lf_door_open();
  bool rf_door_open();
  bool lb_door_open();
  bool rb_door_open();
  bool hatchback_door_open();
  //bool moonroof_door_open();
  bool hood_door_open();

  bool door_switch_available();
};

class AUTOMOBILE_GUAGES
{
  private:
  int COOLANT = 0;
  string COLLANT_DISP = "";

  public:

  void store_coolant(int Value);
  int val_coolant();
  string coolant();

};

class AUTOMOBILE_FUEL
{
  private:
  float CONSUMED = 0;
  string CONSUMED_DISP = "";

  float PERCENTAGE = 0;
  string PERCENTAGE_DISP = "";

  float LEVEL = 0;
  string LEVEL_DISP = "";

  public:

  void store_consumed(int Consumed);
  void store_percentage(int Percentage);
  void store_level(int Level);

  float val_consumed();
  string consumed();

  float val_percentage();
  string percentage();

  float val_level();
  string level();
};

class AUTOMOBILE_INDICATORS
{
  private:
  bool LIGHTS = false;
  int LIGHTS_POS = 0;
  string LIGHTS_DESC = "";

  bool PARKING_BRAKE = false;
  string PARKING_BRAKE_DESC = "";

  bool IGNITION = false;
  string IGNITION_DESC = "";

  bool AVAILABLE = true;

  public:

  void store_lights(int Lights);
  void store_parking_brake(int Parking_Brake);
  void store_ignition(int Ignition);

  bool val_lights();
  int val_lights_pos();
  string lights();

  bool val_parking_brake();
  string parking_brake();

  bool ignition();
  string val_ignition();

  bool light_switch_available();
};

class AUTOMOBILE_POWER
{
  private:
  int VAL_LOAD;

  string LOAD;

  public:

  void store(int Load);
  int val_load();
  string load();
};

class AUTOMOBILE_RPM
{
  private:
  int VAL_RPM;
  string RPM;

  int VAL_RPM_2;  //  unknown
  string RPM_2;   //  unknown

  public:

  void store(int Rpm);
  int val_rpm();
  string rpm();

  void store_2(int Rpm);
  int val_rpm_2();
  string rpm_2();
};

class AUTOMOBILE_STEERING
{
  private:

  float PREVIOUS_STEERING_WHEEL_ANGLE = 0;

  int REPORTED_STEERING_WHEEL_ANGLE = 0;
  int CLOCKWISE = -1;
  bool LEFT_OF_CENTER = false;

  float VAL_STEERING_WHEEL_ANGLE;
  string STEERING_WHEEL_ANGLE;
  string DIRECTION = "XX";
  string LEFT_OF_CENTER_DISP = "XX";

  public:

  void store_steering_wheel_angle(int Angle, int Direction);
  float val_steering_wheel_angle();
  string steering_wheel_angle();
  string turning_direction();
  bool clockwise();
  bool val_left_of_center();
  string left_of_center();
};

class AUTOMOBILE_VELOCITY
{
  private:

  float MULTIPLIER = 1;

  float KMPH = 0;
  float MPH = 0;
  string KMPH_DISP;
  string MPH_DISP;

  float LF_KMPH = 0;
  float LF_MPH = 0;
  string LF_KMPH_DISP;
  string LF_MPH_DISP;

  float RF_KMPH = 0;
  float RF_MPH = 0;
  string RF_KMPH_DISP;
  string RF_MPH_DISP;

  float LB_KMPH = 0;
  float LB_MPH = 0;
  string LB_KMPH_DISP;
  string LB_MPH_DISP;

  float RB_KMPH = 0;
  float RB_MPH = 0;
  string RB_KMPH_DISP;
  string RB_MPH_DISP;

  public:

  void store(int kmph, float Multiplier);
  float val_kmph();
  float val_mph();
  string kmph();
  string mph();

  void store_LF(int mps);
  float val_LF_kmph();
  float val_LF_mph();
  string LF_kmph();
  string LF_mph();

  void store_RF(int mps);
  float val_RF_kmph();
  float val_RF_mph();
  string RF_kmph();
  string RF_mph();

  void store_LB(int mps);
  float val_LB_kmph();
  float val_LB_mph();
  string LB_kmph();
  string LB_mph();

  void store_RB(int mps);
  float val_RB_kmph();
  float val_RB_mph();
  string RB_kmph();
  string RB_mph();
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
  AUTOMOBILE_POWER POWER;
  AUTOMOBILE_INDICATORS INDICATORS;
  AUTOMOBILE_FUEL FUEL;
  AUTOMOBILE_DOORS DOORS;
  AUTOMOBILE_GUAGES GUAGES;
};

class AUTOMOBILE_CALCULATED
{
  private:

  float SPEED_TOTAL;
  float LF_WHEEL_SPEED_TOTAL;
  float RF_WHEEL_SPEED_TOTAL;
  float LB_WHEEL_SPEED_TOTAL;
  float RB_WHEEL_SPEED_TOTAL;

  TIMED_PING DATA_CLEAR_TIMER;
  int counter = 0;

  public:

  VELOCITY LF_WHEEL_SPEED_OFFSET;
  VELOCITY RF_WHEEL_SPEED_OFFSET;
  VELOCITY LB_WHEEL_SPEED_OFFSET;
  VELOCITY RB_WHEEL_SPEED_OFFSET;

  void compute_low(AUTOMOBILE_TRANSLATED_DATA Status, unsigned long tmeFrame_Time);
  // Low level Compute not requiring calculation on all data.
  //  Fast but not fully acurate.
  //  Currently call just before the data is displayed.
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

  bool ACTIVE = false;
  TIMED_PING ACTIVITY_TIMER;

  void parse(string Line);

  public:

  bool CHANGED = false;

  AUTOMOBILE_DATA DATA;
  AUTOMOBILE_TRANSLATED_DATA STATUS;
  AUTOMOBILE_CALCULATED CALCULATED;
  AUTOMOBILE_PROPERTIES PROPS;

  int message_count = 0;

  bool active();

  void process(COMPORT &Com_Port, unsigned long tmeFrame_Time);

  void translate(unsigned long tmeFrame_Time);
};





#endif