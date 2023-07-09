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
#include <string>
#include <deque>

#include "fled_time.h"
#include "stringthings.h"
#include "helper.h"

#include "comport.h"

using namespace std;

// -------------------------------------------------------------------------------------
//  Functions

int method_temp_1(char Byte_1);

int method_2_byte(char Byte_1, char Byte_2);

float method_2_byte_float(char Byte_1, char Byte_2);

float method_2_byte_div_1000(char Byte_1, char Byte_2);

// -------------------------------------------------------------------------------------
//  Classs

bool check_availability(bool Coded_Availability, bool Source_Availabilty);

class AUTOMOBILE_DATA_LINE
{
  public:

  string ORIG = "";

  int ID = -1;

  int ID_DATA[2];
  int DATA[8];

  unsigned long TIMESTAMP_MESSAGE_SENT = 0;
    // Measured in miliseconds
    // Time sent on sending unit
    // Not synced with RasFLED clock.
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
  AUTOMOBILE_DATA_LINE AD_130;  //* 304 - Speed, Data 6 kph, Data 7 Decimal
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

  AUTOMOBILE_DATA_LINE AD_73F;  //  07 3f 03 7f 01 22 00 00 00 00

  // Message Recieved Lines
  AUTOMOBILE_DATA_LINE AD_7E8;  //* 2025 - 
  AUTOMOBILE_DATA_LINE AD_7E9;  //* 2025 - 07 E9 03 41 0D 00 00 00 00 00
  AUTOMOBILE_DATA_LINE AD_7EA;  //* 2025 - 
  AUTOMOBILE_DATA_LINE AD_7EB;  //* 2025 - 

  AUTOMOBILE_DATA_LINE AD_UNKNOWN;
};

class VELOCITY
{
  private:

  float KMPH = -1;
  float MPH = -1;
  float METERS_PER_SECOND = -1;

  string KMPH_DISP = "X";
  string MPH_DISP = "X";

  unsigned long TIME_STAMP = -1;            // Miliseconds.  Fairly loose timings.
  unsigned long TIME_STAMP_TIME_SENT = -1;  // Miliseconds.  Should be a more 
                                            //  accurate timing because set on sending 
                                            //  device. Latency of serial port send and 
                                            //  receive and processing is not factored.
                                            // May also be likely the latency is the same.
                                            //  May only matter when Serial Comm is congested.

  public:

  void store(float kmph, unsigned long tmeFrame_Time, unsigned long tmeFrame_Time_Sent);
  void store_meters_per_second(float mps, unsigned long tmeFrame_Time, unsigned long tmeFrame_Time_Sent);
  void store_miles_per_hour(float Miph, unsigned long tmeFrame_Time, unsigned long tmeFrame_Time_Sent);
  float val_kmph();
  float val_meters_per_second();
  float val_mph();
  string kmph();
  string mph();

  unsigned long time_stamp();
  unsigned long time_stamp_time_sent();
};

class TEMPERATURE
{
  private:

  float C = -1;

  unsigned long TIME_STAMP = -1; // Miliseconds.  Fairly loose timings.

  public:

  void store_c(int Celsius);
  void store_c(float Celsius);
  float val_c();
  //float val_f();
  string c();
  //string f();

  unsigned long time_stamp();
};

class TIME
{
  private:

  int SECONDS = -1;

  public:

  void store_seconds(int Seconds);
  int val_seconds();
  string seconds();
};

class PRESSURE
{
  private:

  float PA = -1;

  unsigned long TIME_STAMP = -1; // Miliseconds.  Fairly loose timings.

  public:

  void store_kPa(int kPa);
  void store_kPa(float kPa);
  void store_Pa(int Pa);
  void store_Pa(float Pa);

  float val_kPa();
  string kPa();
  float val_Pa();
  string Pa();
  float val_inHg();
  string inHg();


  unsigned long time_stamp();
};

class VOLTAGE
{
  private:

  float V = -1;

  unsigned long TIME_STAMP = -1; // Miliseconds.  Fairly loose timings.

  public:

  void store_v(float Voltage);
  float val_v();
  string v();

  unsigned long time_stamp();
};

class AUTOMOBILE_DOORS
{
  private:

  bool CODED_AVAILABILITY = true;
  bool SOURCE_AVAILABILITY = false;

  bool LF_DOOR_OPEN = false;
  bool RF_DOOR_OPEN = false;
  bool LB_DOOR_OPEN = false;
  bool RB_DOOR_OPEN = false;

  bool HATCHBACK_DOOR_OPEN = false;

  //bool MOONROOF_DOOR_OPEN = false;  // Not Implemented

  bool HOOD_DOOR_OPEN = false;

  public:

  void set_source_availability(bool Available);
  bool available();

  void store(int Data);
  bool store_from_alt_source(int Door, bool Value);

  bool lf_door_open();
  bool rf_door_open();
  bool lb_door_open();
  bool rb_door_open();
  bool hatchback_door_open();
  //bool moonroof_door_open();
  bool hood_door_open();
};

class AUTOMOBILE_GUAGES
{
  private:

  bool CODED_AVAILABILITY = false;
  bool SOURCE_AVAILABILITY = false;

  int COOLANT = -1;
  string COLLANT_DISP = "X";

  public:

  void set_source_availability(bool Available);
  bool available();

  void store_coolant(int Value);
  int val_coolant();
  string coolant();

};

class AUTOMOBILE_FUEL
{
  private:

  bool CODED_AVAILABILITY = true;
  bool SOURCE_AVAILABILITY = false;

  float CONSUMED = -1;
  string CONSUMED_DISP = "X";

  float PERCENTAGE = -1;
  string PERCENTAGE_DISP = "X";

  float LEVEL = -1;
  string LEVEL_DISP = "X";

  public:

  PRESSURE FUEL_RAIL_PRESSURE;
  PRESSURE EVAP_SYSTEM_VAP_PRESSURE;

  void set_source_availability(bool Available);
  bool available();

  void store_consumed(int Consumed);
  void store_percentage(int Percentage);
  void store_level(int Level);
  void store_fuel_rail_pressure_23(int A, int B);
  void store_evap_system_vap_pressure_32(int A, int B);

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

  bool CODED_AVAILABILITY = true;
  bool SOURCE_AVAILABILITY = false;

  bool LIGHTS_ON = false;
  bool LIGHTS_HEADLIGHTS_ON = false;
  bool LIGHTS_PARKING_ON = false;
  bool LIGHTS_HIGH_BEAM_ON;
  int LIGHTS_POS = -1;
  bool LIGHT_SWITCH = false;
  string LIGHTS_DESC = "X";

  bool PARKING_BRAKE = false;
  string PARKING_BRAKE_DESC = "X";

  bool IGNITION = false;
  string IGNITION_DESC = "X";

  bool CRUISE_CONTROL = false;
  float CRUISE_CONTROL_SPEED = -1;

  public:

  void process();
  //  To be called at caculate to set headlight and paring status.

  void set_source_availability(bool Available);
  bool available();

  void store_lights(int Lights);
  void store_lights_high_beam(int Data_1);
  void store_on(int Parking_Brake);
  void store_ignition(int Ignition);
  void store_cruise_control(int Data_1, int Data_2, float Multiplier);

  bool val_light_switch();
  int val_lights_pos();
  string lights_switch();
  bool val_lights_high_beam_on();
  bool val_lights_headlights_on();
  bool val_lights_parking_on();

  bool val_parking_brake();
  string parking_brake();

  bool ignition();
  string val_ignition();

  bool cruise_control();
  float cruise_control_speed();
};

class AUTOMOBILE_POWER
{
  private:

  bool CODED_AVAILABILITY = true;
  bool SOURCE_AVAILABILITY = false;

  int VAL_LOAD;

  string LOAD;

  public:

  void set_source_availability(bool Available);
  bool available();

  void store(int Load);
  int val_load();
  string load();
};

class AUTOMOBILE_RPM
{
  private:

  bool CODED_AVAILABILITY = true;
  bool SOURCE_AVAILABILITY = false;

  int VAL_RPM = -1;
  string RPM = "X";

  int VAL_RPM_2 = -1;  //  unknown
  string RPM_2 = "X";   //  unknown

  public:

  void set_source_availability(bool Available);
  bool available();

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

  bool CODED_AVAILABILITY = true;
  bool SOURCE_AVAILABILITY = false;

  float PREVIOUS_STEERING_WHEEL_ANGLE = -1;

  int REPORTED_STEERING_WHEEL_ANGLE = -1;
  int CLOCKWISE = -1;
  bool LEFT_OF_CENTER = false;

  float VAL_STEERING_WHEEL_ANGLE = -1;
  string STEERING_WHEEL_ANGLE = "X";
  string DIRECTION = "X";
  string LEFT_OF_CENTER_DISP = "X";

  public:

  void set_source_availability(bool Available);
  bool available();

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

  bool CODED_AVAILABILITY = true;
  bool SOURCE_AVAILABILITY = false;

  float MULTIPLIER = 1;

  public:

  VELOCITY SPEED_TRANS;
  
  VELOCITY SPEED_DASH;
  
  VELOCITY SPEED_LF_TIRE;
  VELOCITY SPEED_RF_TIRE;
  VELOCITY SPEED_LB_TIRE;
  VELOCITY SPEED_RB_TIRE;

  void set_source_availability(bool Available);
  bool available();

  void store_trans(int kmph, float Multiplier, unsigned long tmeFrame_Time, unsigned long tmeFrame_Time_Sent, 
                    float Verify_kmph);
  void store_dash(int Upper, int Lower, unsigned long tmeFrame_Time, unsigned long tmeFrame_Time_Sent);
  void store_LF(int mps, unsigned long tmeFrame_Time, unsigned long tmeFrame_Time_Sent);
  void store_RF(int mps, unsigned long tmeFrame_Time, unsigned long tmeFrame_Time_Sent);
  void store_LB(int mps, unsigned long tmeFrame_Time, unsigned long tmeFrame_Time_Sent);
  void store_RB(int mps, unsigned long tmeFrame_Time, unsigned long tmeFrame_Time_Sent);

  float multiplier();
};

class AUTOMOBILE_TEMPATURE
{
  private:

  bool CODED_AVAILABILITY = true;
  bool SOURCE_AVAILABILITY = false;

  public:

  TEMPERATURE COOLANT_05;
  TEMPERATURE COOLANT_67_b;
  TEMPERATURE COOLANT_67_c;
  
  TEMPERATURE AIR_INTAKE_0f;
  TEMPERATURE AIR_INTAKE_68_a;
  TEMPERATURE AIR_INTAKE_68_b;

  TEMPERATURE AMBIANT_AIR_46;

  TEMPERATURE OIL_5c;
  TEMPERATURE EXHAUST_GAS_6b;
  TEMPERATURE MANIFOLD_SURFACE_84;
  
  TEMPERATURE CATALYST_3C;

  PRESSURE BARO_33;

  void set_source_availability(bool Available);
  bool available();

  void store_coolant_05(int Sensor_Temp);
  void store_coolant_67(int Sensor_Temp_B, int Sensor_Temp_C);

  void store_air_intake_0f(int Sensor_Temp);
  void store_air_intake_68(int Sensor_Temp_B, int Sensor_Temp_C);

  void store_ambiant_air_46(int Sensor_Temp);
  void store_oil_5c(int Sensor_Temp);
  void store_exhaust_gas_6b(int Sensor_Temp);
  void store_manifold_surface_84(int Sensor_Temp);

  void store_abs_baro_33(int Baro);
  
  void store_catalyst_3c(int A, int B);
};

class AUTOMOBILE_ELECTRICAL
{
  private:

  bool CODED_AVAILABILITY = true;
  bool SOURCE_AVAILABILITY = false;

  public:

  VOLTAGE CONTROL_UNIT_42;
  TIME RUN_TIME_SINCE_START;

  void set_source_availability(bool Available);
  bool available();

  void store_control_voltage_42(int Sensor_B, int Sensor_C);  
  void store_run_time_since_start_1f(int Sensor_B, int Sensor_C);
};

class AUTOMOBILE_TRANSMISSION_GEAR
{
  private:

  bool CODED_AVAILABILITY = true;
  bool SOURCE_AVAILABILITY = false;
  
  // Transmission Info
  int REPORTED = -1;
  string SHORT_DESC = "X";
  string LONG_DESC = "X";

  // Transmission Gear Selection
  int GEAR_SELECTION_REPORTED = -1;
  string GEAR_SELECTION_SHORT_DESC = "X";
  string GEAR_SELECTION_LONG_DESC = "X";
  bool GEAR_SELECTION_PARK = false;
  bool GEAR_SELECTION_REVERSE = false;
  bool GEAR_SELECTION_NEUTRAL = false;
  bool GEAR_SELECTION_DRIVE = false;
  bool GEAR_SELECTION_LOW = false;
  
  public:

  void set_source_availability(bool Available);
  bool available();

  void store(int gear);
  int reported();
  string short_desc();
  string long_desc();

  void store_gear_selection(int Gear, int Gear_Alt, int Transmission_Gear_Reported);
  int gear_selection_reported();
  string gear_selection_short_desc();
  string gear_selection_long_desc();
  bool gear_selection_park();
  bool gear_selection_reverse();
  bool gear_selection_neutral();
  bool gear_selection_drive();
  bool gear_selection_low();
};

class AUTOMOBILE_TRANSLATED_DATA
{
  public:

  AUTOMOBILE_STEERING STEERING;
  AUTOMOBILE_TRANSMISSION_GEAR GEAR;
  AUTOMOBILE_VELOCITY SPEED;
  AUTOMOBILE_TEMPATURE TEMPS;
  AUTOMOBILE_RPM RPM;
  AUTOMOBILE_POWER POWER;
  AUTOMOBILE_INDICATORS INDICATORS;
  AUTOMOBILE_FUEL FUEL;
  AUTOMOBILE_DOORS DOORS;
  AUTOMOBILE_GUAGES GUAGES;
  AUTOMOBILE_ELECTRICAL ELECTRICAL;
};

class TIRE_TTL
{  
  // Hardcoding Tire Life Span
  // +0.03 m/s to -0.15 mi/hr, difference of .18 mi/hr, 0 is transmission registered normal tire size.
  // +0.01341 m/s to -0.06705 mi/hr, difference of .18 mi/hr, 0 is transmission registered normal tire size.

  private:

  MIN_MAX_TIME WHEEL_SPEED_PECENTAGE_DIFF_MEAN;
  VELOCITY WHEEL_SPEED_OFFSET;

  float DIFFERANCE_PERCENTAGE = 0;
  float LIFE_PERCENTAGE = 0;

  float TOP_PERCENTAGE = 100.15;
  float LOW_PERCENTAGE = 99.7;

  public:

  void first_run(float Low_Percentage, float Top_Percentage);

  void calculate(VELOCITY Tire_Speed, VELOCITY Transmission_Speed, 
                  unsigned long tmeFrame_Time);

  int slice_size();

  int slice_size_max();

  float val_instant_differance_percentage();

  string instant_differance_percentage();

  float val_life_percentage_mean();

  string life_percentage_mean();

  VELOCITY wheel_speed_offset();
};

class AUTOMOBILE_CALCULATED
{
  private:

  bool FIRST_RUN = true;

  TIMED_PING ACCELERATION_TIMER;

  float PREVIOUS_VELOCITY_FOR_ACC;
  unsigned long PREVIOUS_TIME_FOR_ACC;
  
  float S_TEMP = -1;

  public:

  TIRE_TTL UNFILTHERED_LF_TTL;
  TIRE_TTL UNFILTHERED_RF_TTL;
  TIRE_TTL UNFILTHERED_LB_TTL;
  TIRE_TTL UNFILTHERED_RB_TTL;

  TIRE_TTL LF_TTL;
  TIRE_TTL RF_TTL;
  TIRE_TTL LB_TTL;
  TIRE_TTL RB_TTL;

  VELOCITY PREVIOUS_VELOCITY;
  
  MIN_MAX_TIME ACCELERATION_MIN_MAX_HISTORY;
  MIN_MAX_TIME ACCELERATION_QUICK_MEAN_HISTORY;

  void compute_low(AUTOMOBILE_TRANSLATED_DATA &Status, unsigned long tmeFrame_Time);
  // Low level Compute not requiring calculation on all data.
  //  Fast but not fully acurate.
  //  Currently call just before the data is displayed.

  float acceleration();
  // Acceleration computed from averageing 4 tire speeds and comparing the times
  //  the value was sent.
  //  Respons calculated over 1 second with 4 time slices

  float s_temp();
  // Non standand temperature score computed by 
  //  ambiant temp + intake temp + coolant temp + catalyst temp divided by twenty
  //  then all divided by 4 then subtracted by 30 then multiplied by 4. 
  // The results give a better single value about the amount of heat the system 
  //  is handling
};

class AUTOMOBILE_AVAILABILITY
{
  private:

  TIMED_PING ACTIVITY_TIMER;
  bool ACTIVE = false;

  public:

  bool check_for_live_data(unsigned long tmeFrame_Time);
  // returns true if data live.

  bool set_active(AUTOMOBILE_TRANSLATED_DATA &Status, bool Available, unsigned long tmeFrame_Time);
  // returns true if active status changed

  bool is_active();

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

  AUTOMOBILE_AVAILABILITY AVAILABILITY;

  string REQUESTED_PID = "";

  // Satus Log File
  deque<string> STATUS_LOG_MESSAGE;
  TIMED_PING STATUS_LOG_TIMER;

  // PID Send List
  deque<string> REQUESTED_PID_SEND_LIST;
  int REQUESTED_PID_SEND_LIST_POSITION = -1;

  TIMED_PING REQUESTED_PID_TIMER_WAIT;
  int REQUESTED_PID_TIMER_WAIT_DELAY = 100;
  //int REQUESTED_PID_TIMER_TIMEOUT_DELAY = 250;

  bool parse(string Line, int &PID_Recieved);
  // Returns true if line is considered a message recieved.
  //  Message id will be in PID_Recieved

  public:

  bool CHANGED = false;

  AUTOMOBILE_DATA DATA;
  AUTOMOBILE_TRANSLATED_DATA STATUS;
  AUTOMOBILE_CALCULATED CALCULATED;
  AUTOMOBILE_PROPERTIES PROPS;

  int message_count = 0;

  void add_to_pid_send_list(string Requested_PID);

  void set_default_request_pid_list();

  string requested_pid();

  bool active();

  void process(COMPORT &Com_Port, unsigned long tmeFrame_Time);

  void translate(unsigned long tmeFrame_Time);
};





#endif