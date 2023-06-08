// ***************************************************************************************
// *size
// *    Core       | Everything within this document is proprietary to Core Dynamics.
// *    Dynamics   | Any unauthorized duplication will be subject to prosecution.
// *
// *    Department : (R+D)^2                        Name: auto.cpp
// *       Sub Dept: Programming
// *    Location ID: 856-45B
// *                                                      (c) 2856 - 2858 Core Dynamics
// ***************************************************************************************

#ifndef AUTO_CPP
#define AUTO_CPP

#include "auto.h"

// -------------------------------------------------------------------------------------
//  Functions

int method_temp_1(int Byte_1)
{
  return Byte_1 - 40;
}

int method_2_byte_div_1000(int Byte_1, int Byte_2)
{
  return ((Byte_1 * 256) + Byte_2) / 1000;
}

// -------------------------------------------------------------------------------------
//  Classs

bool check_availability(bool Coded_Availability, bool Source_Availabilty)
{
  if (Coded_Availability == true && Source_Availabilty == true)
  {
    return true;
  }
  else
  {
    return false;
  }
}

//-----------

void VELOCITY::store(float kmph, unsigned long tmeFrame_Time)
{
  KMPH = kmph;  

  MPH = velocity_translate_kmph_to_mph(KMPH);
  METERS_PER_SECOND = velocity_translate_kmph_to_meters_per_second(KMPH);

  KMPH_DISP = to_string_round_to_nth(KMPH, 2);
  MPH_DISP = to_string_round_to_nth(MPH, 2);

  TIME_STAMP = tmeFrame_Time;
}

void VELOCITY::store_meters_per_second(float mps, unsigned long tmeFrame_Time)
{
  METERS_PER_SECOND = mps;

  KMPH = velocity_translate_meters_per_second_to_kmph(mps);  
  MPH = velocity_translate_kmph_to_mph(KMPH);

  KMPH_DISP = to_string_round_to_nth(KMPH, 2);
  MPH_DISP = to_string_round_to_nth(MPH, 2);

  TIME_STAMP = tmeFrame_Time;
}

float VELOCITY::val_kmph()
{
  return KMPH;
}

float VELOCITY::val_meters_per_second()
{
  return METERS_PER_SECOND;
}

float VELOCITY::val_mph()
{
  return MPH;
}

string VELOCITY::kmph()
{
  return KMPH_DISP;
}

string VELOCITY::mph()
{
  return MPH_DISP;
}

unsigned long VELOCITY::time_stamp()
{
  return TIME_STAMP;
}

//-----------

void TEMPERATURE::store_c(int Celsius)
{
  C  = Celsius;
}

int TEMPERATURE::val_c()
{
  return C;
}

/*
float TEMPERATURE::val_f()
{
  return -1;
}
*/

string TEMPERATURE::c()
{
  return to_string(C) + "c";
}

/*
string TEMPERATURE::f()
{
  return "(O)";
}
*/

//-----------

void VOLTAGE::store_v(int Voltage)
{
  V  = Voltage;
}

float VOLTAGE::val_v()
{
  return V;
}

string VOLTAGE::v()
{
  return to_string_round_to_nth(V, 1) + "v";
}

//-----------

void AUTOMOBILE_DOORS::set_source_availability(bool Available)
{
  SOURCE_AVAILABILITY = Available;
}

bool AUTOMOBILE_DOORS::available()
{
  return check_availability(CODED_AVAILABILITY, SOURCE_AVAILABILITY);
}

void AUTOMOBILE_DOORS::store(int Data)
{
  // AD_360 also contains info on the engine running status  

  // RB - Door
  LF_DOOR_OPEN = !get_bit_value(Data, 1);
  RF_DOOR_OPEN = !get_bit_value(Data, 2);
  LB_DOOR_OPEN = !get_bit_value(Data, 4);
  RB_DOOR_OPEN = !get_bit_value(Data, 8);

  HATCHBACK_DOOR_OPEN = !get_bit_value(Data, 16);
  HOOD_DOOR_OPEN = !get_bit_value(Data, 32);

  //1[2]
  //MOONROOF_DOOR_OPEN = get_bit_value(Data, 8);
}

bool AUTOMOBILE_DOORS::store_from_alt_source(int Door, bool Value)
{
  TRUTH_CATCH ret_changed;
  if (Door == 0)
  {
    ret_changed.catch_truth(set_bool_with_change_notify(Value, LB_DOOR_OPEN));
  }
  else if (Door == 1)
  {
    ret_changed.catch_truth(set_bool_with_change_notify(Value, LF_DOOR_OPEN));
  }
  else if (Door == 2)
  {
    ret_changed.catch_truth(set_bool_with_change_notify(Value, RB_DOOR_OPEN));
  }
  else if (Door == 3)
  {
    ret_changed.catch_truth(set_bool_with_change_notify(Value, RF_DOOR_OPEN));
  }
  return ret_changed.has_truth();
}

bool AUTOMOBILE_DOORS::lf_door_open()
{
  return LF_DOOR_OPEN;
}

bool AUTOMOBILE_DOORS::rf_door_open()
{
  return RF_DOOR_OPEN;
}

bool AUTOMOBILE_DOORS::lb_door_open()
{
  return LB_DOOR_OPEN;
}

bool AUTOMOBILE_DOORS::rb_door_open()
{
  return RB_DOOR_OPEN;
}

bool AUTOMOBILE_DOORS::hatchback_door_open()
{
  return HATCHBACK_DOOR_OPEN;
}

/*
bool AUTOMOBILE_DOORS::moonroof_door_open()
{
  return MOONROOF_DOOR_OPEN;
}
*/

bool AUTOMOBILE_DOORS::hood_door_open()
{
  return HOOD_DOOR_OPEN;
}

//-----------

void AUTOMOBILE_GUAGES::set_source_availability(bool Available)
{
  if (SOURCE_AVAILABILITY == true && Available == false)
  {
    COOLANT = -1;
    COLLANT_DISP = "X";
  }
  
  SOURCE_AVAILABILITY = Available;
}

bool AUTOMOBILE_GUAGES::available()
{
  return check_availability(CODED_AVAILABILITY, SOURCE_AVAILABILITY);
}

void AUTOMOBILE_GUAGES::store_coolant(int Value)
{
  COOLANT = Value;
  COLLANT_DISP = to_string(COOLANT) + "c";
}

int AUTOMOBILE_GUAGES::val_coolant()
{
  return COOLANT;
}

string AUTOMOBILE_GUAGES::coolant()
{
  return COLLANT_DISP;
}

//-----------

void AUTOMOBILE_FUEL::set_source_availability(bool Available)
{
  if (SOURCE_AVAILABILITY == true && Available == false)
  {
    CONSUMED = -1;
    CONSUMED_DISP = "X";

    PERCENTAGE = -1;
    PERCENTAGE_DISP = "X";

    LEVEL = -1;
    LEVEL_DISP = "X";
  }
  
  SOURCE_AVAILABILITY = Available;
}

bool AUTOMOBILE_FUEL::available()
{
  return check_availability(CODED_AVAILABILITY, SOURCE_AVAILABILITY);
}

void AUTOMOBILE_FUEL::store_consumed(int Consumed)
{
  CONSUMED = ((float)Consumed) / 20;

  CONSUMED_DISP = to_string_round_to_nth(CONSUMED, 2) + " gal";
}

void AUTOMOBILE_FUEL::store_percentage(int Percentage)
{
  PERCENTAGE = ((float)Percentage * 100) / 256 ;

  PERCENTAGE_DISP = to_string_round_to_nth(PERCENTAGE, 1) + " %";
}

void AUTOMOBILE_FUEL::store_level(int Level)
{
  LEVEL = ((float)Level) / 20;

  LEVEL_DISP = to_string_round_to_nth(LEVEL, 1) + " gal";
}

float AUTOMOBILE_FUEL::val_consumed()
{
  return CONSUMED;
}

string AUTOMOBILE_FUEL::consumed()
{
  return CONSUMED_DISP;
}

float AUTOMOBILE_FUEL::val_percentage()
{
  return PERCENTAGE;
}

string AUTOMOBILE_FUEL::percentage()
{
  return PERCENTAGE_DISP;
}

float AUTOMOBILE_FUEL::val_level()
{
  return LEVEL;
}

string AUTOMOBILE_FUEL::level()
{
  return LEVEL_DISP;
}

//-----------

void AUTOMOBILE_INDICATORS::process()
{
  // Condition Headlights On
  if (LIGHTS_HIGH_BEAM_ON == true || LIGHTS_POS == 2 || (LIGHTS_POS == 3 && LIGHTS_ON == true))
  {
    LIGHTS_HEADLIGHTS_ON = true;
  }
  else
  {
    LIGHTS_HEADLIGHTS_ON = false;
  }

  // Condition Parking Lights On
  if (LIGHTS_POS == 1 || LIGHTS_POS == 2 || (LIGHTS_POS == 3 && LIGHTS_ON == true))
  {
    LIGHTS_PARKING_ON = true;
  }
  else
  {
    LIGHTS_PARKING_ON = false;
  }
}

void AUTOMOBILE_INDICATORS::set_source_availability(bool Available)
{
  if (SOURCE_AVAILABILITY == true && Available == false)
  {
    LIGHTS_POS = -1;
    LIGHTS_DESC = "X";

    PARKING_BRAKE_DESC = "X";

    IGNITION_DESC = "X";

    CRUISE_CONTROL_SPEED = -1;
  }
  
  SOURCE_AVAILABILITY = Available;
}

bool AUTOMOBILE_INDICATORS::available()
{
  return check_availability(CODED_AVAILABILITY, SOURCE_AVAILABILITY);
}

void AUTOMOBILE_INDICATORS::store_lights(int Lights)
{
  // Parse Lights
  if (Lights == 0)
  {
    LIGHT_SWITCH = false;
    LIGHTS_POS = 0;
    LIGHTS_DESC = "OFF";
  }
  else if (Lights == 1)
  {
    LIGHT_SWITCH = true;
    LIGHTS_POS = 1;
    LIGHTS_DESC = "PARKING";
  }
  else if (Lights == 2)
  {
    LIGHT_SWITCH = true;
    LIGHTS_POS = 2;
    LIGHTS_DESC = "ON";
  }
  else if (Lights == 3)
  {
    LIGHT_SWITCH = true;
    LIGHTS_POS = 3;
    LIGHTS_DESC = "AUTO";
  }
  else
  {
    LIGHT_SWITCH = false;
    LIGHTS_POS = Lights;
    LIGHTS_DESC = "UNKNOWN";
  }
}

void AUTOMOBILE_INDICATORS::store_lights_high_beam(int Data_1)
{
  LIGHTS_HIGH_BEAM_ON = get_bit_value(Data_1, 32);
}

void AUTOMOBILE_INDICATORS::store_on(int Light_Bits)
{
  // Lights Actually On      1st bit
  //  c8 [3] 	b1 lights on	10110001
	//          b0 lights off 10110000
  LIGHTS_ON = get_bit_value(Light_Bits, 1);

  // Parse Parking Brake      7th bit
  // B0 or B1 - OFF 10110000
  // F0 or F1 - On  11110000
  // bit
  if (get_bit_value(Light_Bits, 64) == false)
  {
    PARKING_BRAKE = false;
    PARKING_BRAKE_DESC = "PARKING BRAKE OFF";
  }
  else
  {
    PARKING_BRAKE = true;
    PARKING_BRAKE_DESC = "PARKING BRAKE ON";
  }
}

void AUTOMOBILE_INDICATORS::store_ignition(int Ignition)
{
  // Parse Ignition
  if (Ignition == 0)
  {
    // UNKNOWN
  }
}

void AUTOMOBILE_INDICATORS::store_cruise_control(int Data_1, int Data_2, float Multiplier)
{
  if (Data_1 == 194 || Data_1 == 210)  // c2 (194) or d2 (210) on
  {
    CRUISE_CONTROL = true;
    CRUISE_CONTROL_SPEED = Data_2 * Multiplier;
  }
  else                //  c0 (192) or d0 (208) off
  {
    CRUISE_CONTROL = false;
    CRUISE_CONTROL_SPEED = Data_2 * Multiplier;
  }
}

bool AUTOMOBILE_INDICATORS::val_light_switch()
{
  return LIGHT_SWITCH;
}

int AUTOMOBILE_INDICATORS::val_lights_pos()
{
  return LIGHTS_POS;
}

string AUTOMOBILE_INDICATORS::lights_switch()
{
  return LIGHTS_DESC;
}

bool AUTOMOBILE_INDICATORS::val_lights_high_beam_on()
{
  return LIGHTS_HIGH_BEAM_ON;
}

bool AUTOMOBILE_INDICATORS::val_lights_headlights_on()
{
  return LIGHTS_HEADLIGHTS_ON;
}

bool AUTOMOBILE_INDICATORS::val_lights_parking_on()
{
  return LIGHTS_PARKING_ON;
}

bool AUTOMOBILE_INDICATORS::val_parking_brake()
{
  return PARKING_BRAKE;
}

string AUTOMOBILE_INDICATORS::parking_brake()
{
  return PARKING_BRAKE_DESC;
}

bool AUTOMOBILE_INDICATORS::ignition()
{
  return IGNITION;
}

string AUTOMOBILE_INDICATORS::val_ignition()
{
  return IGNITION_DESC;
}

bool AUTOMOBILE_INDICATORS::cruise_control()
{
  return CRUISE_CONTROL;
}

float AUTOMOBILE_INDICATORS::cruise_control_speed()
{
  return CRUISE_CONTROL_SPEED;
}

//-----------

void AUTOMOBILE_POWER::set_source_availability(bool Available)
{
  if (SOURCE_AVAILABILITY == true && Available == false)
  {
    VAL_LOAD = -1;
    LOAD = "X";
  }
  
  SOURCE_AVAILABILITY = Available;
}

bool AUTOMOBILE_POWER::available()
{
  return check_availability(CODED_AVAILABILITY, SOURCE_AVAILABILITY);
}

void AUTOMOBILE_POWER::store(int Load)
{
  // val - 8000 -- Negative value is reverse power request.
  VAL_LOAD = (Load - 32768);   // Value type unknown

  LOAD = to_string(VAL_LOAD);
}

int AUTOMOBILE_POWER::val_load()
{
  return VAL_LOAD;
}

string AUTOMOBILE_POWER::load()
{
  return LOAD;
}

//-----------

void AUTOMOBILE_RPM::set_source_availability(bool Available)
{
  if (SOURCE_AVAILABILITY == true && Available == false)
  {
    VAL_RPM = -1;
    RPM = "X";

    VAL_RPM_2 = -1;
    RPM_2 = "X";
  }
  
  SOURCE_AVAILABILITY = Available;
}

bool AUTOMOBILE_RPM::available()
{
  return check_availability(CODED_AVAILABILITY, SOURCE_AVAILABILITY);
}

void AUTOMOBILE_RPM::store(int Rpm)
{
  // val - x6000
  VAL_RPM = (Rpm - 24576) * 2;    // Wrong

  RPM = to_string(VAL_RPM);
}

int AUTOMOBILE_RPM::val_rpm()
{
  return VAL_RPM;
}

string AUTOMOBILE_RPM::rpm()
{
  return RPM;
}

void AUTOMOBILE_RPM::store_2(int Rpm)
{
  // val - xC000
  VAL_RPM_2 = (Rpm - 49152) * 2;    // Wrong

  RPM_2 = to_string(VAL_RPM_2);
}

int AUTOMOBILE_RPM::val_rpm_2()
{
  return VAL_RPM_2;
}

string AUTOMOBILE_RPM::rpm_2()
{
  return RPM_2;
}

//-----------

void AUTOMOBILE_STEERING::set_source_availability(bool Available)
{
  if (SOURCE_AVAILABILITY == true && Available == false)
  {
    PREVIOUS_STEERING_WHEEL_ANGLE = -1;
    REPORTED_STEERING_WHEEL_ANGLE = -1;
    VAL_STEERING_WHEEL_ANGLE = -1;
    STEERING_WHEEL_ANGLE = "X";
    DIRECTION = "X";
    LEFT_OF_CENTER_DISP = "X";
  }
  
  SOURCE_AVAILABILITY = Available;
}

bool AUTOMOBILE_STEERING::available()
{
  return check_availability(CODED_AVAILABILITY, SOURCE_AVAILABILITY);
}

void AUTOMOBILE_STEERING::store_steering_wheel_angle(int Angle, int Direction)
{
  // x8000 at 0 deg. x8500 at 90 deg. x9000 at 180 deg.
  //VAL_STEERING_WHEEL_ANGLE = ((float)Angle - 32768);

  VAL_STEERING_WHEEL_ANGLE = (((float)Angle - 32768) /4 ) *.18;

  // MSB for Direction

  // Determine direction of wheel turn.
  if (VAL_STEERING_WHEEL_ANGLE == PREVIOUS_STEERING_WHEEL_ANGLE)
  {
    CLOCKWISE = 0;
    DIRECTION = "--";
  }
  else
  {
    if (Direction >= 128)
    {
      CLOCKWISE = 1;
      DIRECTION = "->";
    }
    else
    {
      CLOCKWISE = -1;
      DIRECTION = "<-";
    }

    // Determine if wheel is left or right of center.
    if (CLOCKWISE == 1)
    {
      if (VAL_STEERING_WHEEL_ANGLE > PREVIOUS_STEERING_WHEEL_ANGLE)
      {
        LEFT_OF_CENTER = false;
      }
    }
    else if (CLOCKWISE = -1)
    {
      if (VAL_STEERING_WHEEL_ANGLE > PREVIOUS_STEERING_WHEEL_ANGLE)
      {
        LEFT_OF_CENTER = true;
      }
    }

    if (LEFT_OF_CENTER == true)
    {
      LEFT_OF_CENTER_DISP = "<-";
    }
    else
    {
      LEFT_OF_CENTER_DISP = "->";
    }

    // Set Display Variables
    PREVIOUS_STEERING_WHEEL_ANGLE = VAL_STEERING_WHEEL_ANGLE;
    STEERING_WHEEL_ANGLE = to_string_round_to_nth(VAL_STEERING_WHEEL_ANGLE, 1) + " deg";
  }
}

float AUTOMOBILE_STEERING::val_steering_wheel_angle()
{
  return VAL_STEERING_WHEEL_ANGLE;
}

string AUTOMOBILE_STEERING::steering_wheel_angle()
{
  return STEERING_WHEEL_ANGLE;
}

string AUTOMOBILE_STEERING::turning_direction()
{
  return DIRECTION;
}

bool AUTOMOBILE_STEERING::clockwise()
{
  return CLOCKWISE;
}

bool AUTOMOBILE_STEERING::val_left_of_center()
{
  return LEFT_OF_CENTER;
}

string AUTOMOBILE_STEERING::left_of_center()
{
  return LEFT_OF_CENTER_DISP;
}

//-----------

void AUTOMOBILE_VELOCITY::set_source_availability(bool Available)
{
  if (SOURCE_AVAILABILITY == true && Available == false)
  {
    SPEED_TRANS.store(-1, 0);
    SPEED_DASH.store(-1, 0);
    SPEED_LF_TIRE.store(-1, 0);
    SPEED_RF_TIRE.store(-1, 0);
    SPEED_LB_TIRE.store(-1, 0);
    SPEED_RB_TIRE.store(-1, 0);
  }
  
  SOURCE_AVAILABILITY = Available;
}

bool AUTOMOBILE_VELOCITY::available()
{
  return check_availability(CODED_AVAILABILITY, SOURCE_AVAILABILITY);
}

// Multiplier source unknown.  not calculating correctly.
// Possibly wrong spec tire size.  How the car knows is beyond me.
void AUTOMOBILE_VELOCITY::store_trans(int kmph, float Multiplier, unsigned long tmeFrame_Time)
{
  // Possibly meters per second devided by 3  (Multiplier = 1.2 for kmph conversion )
  //                                          (3.6 kmph = 1 mps                     )

  MULTIPLIER = Multiplier;
  SPEED_TRANS.store((kmph * MULTIPLIER) / 10, tmeFrame_Time);
}

void AUTOMOBILE_VELOCITY::store_dash(int kmph, int kmph_decimal, unsigned long tmeFrame_Time)
{
  SPEED_DASH.store(kmph + (kmph_decimal / 255), tmeFrame_Time);
}

void AUTOMOBILE_VELOCITY::store_LF(int mps, unsigned long tmeFrame_Time)
{
  SPEED_LF_TIRE.store(((mps - 32768) * MULTIPLIER) / 100, tmeFrame_Time);
}

void AUTOMOBILE_VELOCITY::store_RF(int mps, unsigned long tmeFrame_Time)
{
  SPEED_RF_TIRE.store(((mps - 32768) * MULTIPLIER) / 100, tmeFrame_Time);
}

void AUTOMOBILE_VELOCITY::store_LB(int mps, unsigned long tmeFrame_Time)
{
  SPEED_LB_TIRE.store(((mps - 32768) * MULTIPLIER) / 100, tmeFrame_Time);
}

void AUTOMOBILE_VELOCITY::store_RB(int mps, unsigned long tmeFrame_Time)
{
  SPEED_RB_TIRE.store(((mps - 32768) * MULTIPLIER) / 100, tmeFrame_Time);
}

float AUTOMOBILE_VELOCITY::multiplier()
{
  return MULTIPLIER;
}

//-----------

void AUTOMOBILE_TEMPATURE::set_source_availability(bool Available)
{
  if (SOURCE_AVAILABILITY == true && Available == false)
  {
    // clear fields?
  }
  
  SOURCE_AVAILABILITY = Available;
}

bool AUTOMOBILE_TEMPATURE::available()
{
  return check_availability(CODED_AVAILABILITY, SOURCE_AVAILABILITY);
}

void AUTOMOBILE_TEMPATURE::store_coolant_05(int Sensor_Temp)
{
  COOLANT_05.store_c(method_temp_1(Sensor_Temp));
}

void AUTOMOBILE_TEMPATURE::store_coolant_67(int Sensor_Temp_B, int Sensor_Temp_C)
{
  COOLANT_67_b.store_c(method_temp_1(Sensor_Temp_B));
  COOLANT_67_c.store_c(method_temp_1(Sensor_Temp_C));
}

void AUTOMOBILE_TEMPATURE::store_air_intake_0f(int Sensor_Temp)
{
  AIR_INTAKE_0f.store_c(method_temp_1(Sensor_Temp));
}

void AUTOMOBILE_TEMPATURE::store_air_intake_68(int Sensor_Temp_B, int Sensor_Temp_C)
{
  AIR_INTAKE_68_b.store_c(method_temp_1(Sensor_Temp_B));
  AIR_INTAKE_68_b.store_c(method_temp_1(Sensor_Temp_C));
}

void AUTOMOBILE_TEMPATURE::store_ambiant_air_46(int Sensor_Temp)
{
  AMBIANT_AIR_46.store_c(method_temp_1(Sensor_Temp));
}

void AUTOMOBILE_TEMPATURE::store_oil_5c(int Sensor_Temp)
{
  OIL_5c.store_c(method_temp_1(Sensor_Temp));
}

void AUTOMOBILE_TEMPATURE::store_exhaust_gas_6b(int Sensor_Temp)
{
  EXHAUST_GAS_6b.store_c(method_temp_1(Sensor_Temp));
}

void AUTOMOBILE_TEMPATURE::store_manifold_surface_84(int Sensor_Temp)
{
  MANIFOLD_SURFACE_84.store_c(method_temp_1(Sensor_Temp));
}

//-----------

void AUTOMOBILE_ELECTRICAL::set_source_availability(bool Available)
{
  if (SOURCE_AVAILABILITY == true && Available == false)
  {
    // clear fields?
  }
  
  SOURCE_AVAILABILITY = Available;
}

bool AUTOMOBILE_ELECTRICAL::available()
{
  return check_availability(CODED_AVAILABILITY, SOURCE_AVAILABILITY);
}

void AUTOMOBILE_ELECTRICAL::store_control_voltage_42(int Sensor_B, int Sensor_C)
{
  CONTROL_UNIT_42.store_v(method_2_byte_div_1000(Sensor_B, Sensor_C));
}

//-----------

void AUTOMOBILE_TRANSMISSION_GEAR::set_source_availability(bool Available)
{
  if (SOURCE_AVAILABILITY == true && Available == false)
  {
    REPORTED = -1;
    SHORT_DESC = "X";
    LONG_DESC = "X";

    GEAR_SELECTION_REPORTED = -1;
    GEAR_SELECTION_LONG_DESC = "X";
    GEAR_SELECTION_PARK = false;
    GEAR_SELECTION_REVERSE = false;
    GEAR_SELECTION_NEUTRAL = false;
    GEAR_SELECTION_DRIVE = false;
    GEAR_SELECTION_LOW = false;
  }
  
  SOURCE_AVAILABILITY = Available;
}

bool AUTOMOBILE_TRANSMISSION_GEAR::available()
{
  return check_availability(CODED_AVAILABILITY, SOURCE_AVAILABILITY);
}

void AUTOMOBILE_TRANSMISSION_GEAR::store(int gear)
{
  REPORTED = gear;    // Wrong on park and neutral and reverse.

  if (gear == 19)
  {
    SHORT_DESC = "PN (19)";
    LONG_DESC = "NeuPrk";
  }
  else if (gear == 1)
  {
    SHORT_DESC = "1";
    LONG_DESC = "1st";
  }
  else if (gear == 2)
  {
    SHORT_DESC = "2";
    LONG_DESC = "2nd";
  }
  else if (gear == 3)
  {
    SHORT_DESC = "3";
    LONG_DESC = "3rd";
  }
  else if (gear == 4)
  {
    SHORT_DESC = "4";
    LONG_DESC = "4th";
  }
  else if (gear == 5)
  {
    SHORT_DESC = "5";
    LONG_DESC = "5th";
  }
  else if (gear == 6)
  {
    SHORT_DESC = "6";
    LONG_DESC = "6th";
  }
  //else if (gear == 19)
  //{
  //  SHORT_DESC = "P";
  //  LONG_DESC = "Park";
  //}
  else if (gear == 0)
  {
    SHORT_DESC = "R (0)";
    LONG_DESC = "Reverse";
  }
  else
  {
    SHORT_DESC = "X";
    LONG_DESC = "Unknown";
  }
}

int AUTOMOBILE_TRANSMISSION_GEAR::reported()
{
  return REPORTED;
}

string AUTOMOBILE_TRANSMISSION_GEAR::short_desc()
{
  return SHORT_DESC;
}

string AUTOMOBILE_TRANSMISSION_GEAR::long_desc()
{
  return LONG_DESC;
}

void AUTOMOBILE_TRANSMISSION_GEAR::store_gear_selection(int Gear, int Gear_Alt)
{
  GEAR_SELECTION_REPORTED = Gear;

  /*
  E0 Reverse
  00 Neutral
  10 Drive
  data 2 51 low
  01 Park
  */

  if (Gear == 0 && Gear_Alt == 0)
  {
    // Park
    SHORT_DESC = "Park";
    GEAR_SELECTION_PARK = true;
    GEAR_SELECTION_REVERSE = false;
    GEAR_SELECTION_NEUTRAL = false;
    GEAR_SELECTION_DRIVE = false;
    GEAR_SELECTION_LOW = false;
  }
  else if (Gear == 224)
  {
    // Reverse
    SHORT_DESC = "Reverse";
    GEAR_SELECTION_PARK = false;
    GEAR_SELECTION_REVERSE = true;
    GEAR_SELECTION_NEUTRAL = false;
    GEAR_SELECTION_DRIVE = false;
    GEAR_SELECTION_LOW = false;
  }
  else if (Gear == 0 && Gear_Alt == 32)
  {
    // Reverse
    SHORT_DESC = "Neutral";
    GEAR_SELECTION_PARK = false;
    GEAR_SELECTION_REVERSE = false;
    GEAR_SELECTION_NEUTRAL = true;
    GEAR_SELECTION_DRIVE = false;
    GEAR_SELECTION_LOW = false;
  }
  else if (Gear >= 10 && Gear <= 96 && !get_bit_value(Gear_Alt, 64))
  {
    // Drive
    SHORT_DESC = "Drive";
    GEAR_SELECTION_PARK = false;
    GEAR_SELECTION_REVERSE = false;
    GEAR_SELECTION_NEUTRAL = false;
    GEAR_SELECTION_DRIVE = true;
    GEAR_SELECTION_LOW = false;
  }
  else if (Gear >= 10 && Gear <= 96 && get_bit_value(Gear_Alt, 64))
  {
    // Low
    SHORT_DESC = "Low";
    GEAR_SELECTION_PARK = false;
    GEAR_SELECTION_REVERSE = false;
    GEAR_SELECTION_NEUTRAL = false;
    GEAR_SELECTION_DRIVE = false;
    GEAR_SELECTION_LOW = true;
  }
  else
  {
    // Unknown
    SHORT_DESC = "Unknown";
    GEAR_SELECTION_PARK = false;
    GEAR_SELECTION_REVERSE = false;
    GEAR_SELECTION_NEUTRAL = false;
    GEAR_SELECTION_DRIVE = false;
    GEAR_SELECTION_LOW = false;
  }
}

int AUTOMOBILE_TRANSMISSION_GEAR::gear_selection_reported()
{
  return GEAR_SELECTION_REPORTED;
}

string AUTOMOBILE_TRANSMISSION_GEAR::gear_selection_long_desc()
{
  return GEAR_SELECTION_LONG_DESC;
}

bool AUTOMOBILE_TRANSMISSION_GEAR::gear_selection_park()
{
  return GEAR_SELECTION_PARK;
}

bool AUTOMOBILE_TRANSMISSION_GEAR::gear_selection_reverse()
{
  return GEAR_SELECTION_REVERSE;
}

bool AUTOMOBILE_TRANSMISSION_GEAR::gear_selection_neutral()
{
  return GEAR_SELECTION_NEUTRAL;
}

bool AUTOMOBILE_TRANSMISSION_GEAR::gear_selection_drive()
{
  return GEAR_SELECTION_DRIVE;
}

bool AUTOMOBILE_TRANSMISSION_GEAR::gear_selection_low()
{
  return GEAR_SELECTION_LOW;
}

//-----------

void TIRE_TTL::first_run()
{
  WHEEL_SPEED_OFFSET_MEAN.PROP.SLICES = 20;
  WHEEL_SPEED_OFFSET_MEAN.PROP.SAMPLE_LIMIT = 100;
  WHEEL_SPEED_OFFSET_MEAN.PROP.SAMPLE_LIMITED_SPANS = true;
}

void TIRE_TTL::calculate(VELOCITY Tire_Speed, VELOCITY Transmission_Speed, unsigned long tmeFrame_Time)
{
  WHEEL_SPEED_OFFSET_MEAN.put_value(Transmission_Speed.val_kmph() - Tire_Speed.val_kmph(), tmeFrame_Time);
  WHEEL_SPEED_OFFSET.store(WHEEL_SPEED_OFFSET_MEAN.mean_float(), tmeFrame_Time);

  LIFE_PERCENTAGE = ((V_HIGH - V_MIDDLE_OFFSET - WHEEL_SPEED_OFFSET.val_meters_per_second()) / V_HIGH);
}

int TIRE_TTL::slice_size()
{
  return WHEEL_SPEED_OFFSET_MEAN.slice_size();
}

int TIRE_TTL::slice_size_max()
{
  return WHEEL_SPEED_OFFSET_MEAN.slice_size_max();
}

int TIRE_TTL::val_life_percentage()
{
  return (int)(LIFE_PERCENTAGE * 100);
}

string TIRE_TTL::life_percentage()
{
  return to_string((int)(LIFE_PERCENTAGE * 100)) + "% ";
}

VELOCITY TIRE_TTL::wheel_speed_offset()
{
  return WHEEL_SPEED_OFFSET;
}

//-----------

void AUTOMOBILE_CALCULATED::compute_low(AUTOMOBILE_TRANSLATED_DATA &Status, unsigned long tmeFrame_Time)
{
  // Set Lights
  Status.INDICATORS.process();

  // No init process. Set first run variables
  if (FIRST_RUN == true)
  { 
    UNFILTHERED_LF_TTL.first_run();
    UNFILTHERED_RF_TTL.first_run();
    UNFILTHERED_LB_TTL.first_run();
    UNFILTHERED_RB_TTL.first_run();

    LF_TTL.first_run();
    RF_TTL.first_run();
    LB_TTL.first_run();
    RB_TTL.first_run();

    ACCELERATION_MIN_MAX_HISTORY.PROP.SLICES = 6;
    ACCELERATION_MIN_MAX_HISTORY.PROP.TIME_SPAN = 30000;

    ACCELERATION_QUICK_MEAN_HISTORY.PROP.SLICES = 4;
    ACCELERATION_QUICK_MEAN_HISTORY.PROP.TIME_SPAN = 1000;
    
    FIRST_RUN = false;
  }
 
  // Calculate Acceleration and Wheel Speed offsets.
  if (Status.SPEED.SPEED_LB_TIRE.time_stamp() != PREVIOUS_VELOCITY_FOR_ACC.time_stamp())
  {
    // Reading Acceleration from tire speed may be more accurate.
    float ACCELERATION = 1000 * (Status.SPEED.SPEED_LB_TIRE.val_meters_per_second() - PREVIOUS_VELOCITY_FOR_ACC.val_meters_per_second()) / 
                        (Status.SPEED.SPEED_LB_TIRE.time_stamp() - PREVIOUS_VELOCITY_FOR_ACC.time_stamp());

    ACCELERATION_QUICK_MEAN_HISTORY.put_value(ACCELERATION, tmeFrame_Time);

    ACCELERATION_MIN_MAX_HISTORY.put_value(ACCELERATION_QUICK_MEAN_HISTORY.mean_float(), tmeFrame_Time);

    PREVIOUS_VELOCITY_FOR_ACC = Status.SPEED.SPEED_LB_TIRE;
    ACCELERATION_TIMER.ping_up(tmeFrame_Time, 250);

    // Calculate Wheelspeed Offset or Differance.

    // Unfilthered
    if (Status.SPEED.SPEED_TRANS.time_stamp() != PREVIOUS_VELOCITY.time_stamp())
    {
      UNFILTHERED_LF_TTL.calculate(Status.SPEED.SPEED_LF_TIRE, Status.SPEED.SPEED_TRANS, tmeFrame_Time);
      UNFILTHERED_RF_TTL.calculate(Status.SPEED.SPEED_RF_TIRE, Status.SPEED.SPEED_TRANS, tmeFrame_Time);
      UNFILTHERED_LB_TTL.calculate(Status.SPEED.SPEED_LB_TIRE, Status.SPEED.SPEED_TRANS, tmeFrame_Time);
      UNFILTHERED_RB_TTL.calculate(Status.SPEED.SPEED_RB_TIRE, Status.SPEED.SPEED_TRANS, tmeFrame_Time);

      if (Status.SPEED.SPEED_TRANS.val_mph() > 43 && Status.SPEED.SPEED_TRANS.val_mph() < 48 && 
          Status.STEERING.val_steering_wheel_angle() < 2 && 
          ACCELERATION_QUICK_MEAN_HISTORY.mean_float() > -.2 && 
          ACCELERATION_QUICK_MEAN_HISTORY.mean_float() < .2 ) 
          // Only get values at certain speeds and while drivng straight.
          // Centering speed at 45 because I can drive for hours and not get over 50mph 
          //  and Acceleration < +- .2.
      {
        LF_TTL.calculate(Status.SPEED.SPEED_LF_TIRE, Status.SPEED.SPEED_TRANS, tmeFrame_Time);
        RF_TTL.calculate(Status.SPEED.SPEED_RF_TIRE, Status.SPEED.SPEED_TRANS, tmeFrame_Time);
        LB_TTL.calculate(Status.SPEED.SPEED_LB_TIRE, Status.SPEED.SPEED_TRANS, tmeFrame_Time);
        RB_TTL.calculate(Status.SPEED.SPEED_RB_TIRE, Status.SPEED.SPEED_TRANS, tmeFrame_Time);
      }
    }
  }
}

float AUTOMOBILE_CALCULATED::acceleration()
{
  return ACCELERATION_QUICK_MEAN_HISTORY.mean_float();
}

//-----------

bool AUTOMOBILE::parse(string Line, int &PID_Recieved)
{
  bool ret_message_recieved = false;
  
  string left = "";
  int pos = 0;

  int upper = 0;
  int lower = 0;

  int time_byte_0 = 0;
  int time_byte_1 = 0;
  int time_byte_2 = 0;
  int time_byte_3 = 0;

  FALSE_CATCH valid;

  AUTOMOBILE_DATA_LINE data;

  data.ORIG = Line;

  valid.catch_false(string_hex_to_int(Line.substr(0, 2), upper));
  valid.catch_false(string_hex_to_int(Line.substr(3, 2), lower));

  valid.catch_false(string_hex_to_int(Line.substr(6, 2), data.ID_DATA[0]));
  valid.catch_false(string_hex_to_int(Line.substr(3, 2), data.ID_DATA[1]));

  valid.catch_false(string_hex_to_int(Line.substr(6, 2), data.DATA[0]));
  valid.catch_false(string_hex_to_int(Line.substr(9, 2), data.DATA[1]));
  valid.catch_false(string_hex_to_int(Line.substr(12, 2), data.DATA[2]));
  valid.catch_false(string_hex_to_int(Line.substr(15, 2), data.DATA[3]));
  valid.catch_false(string_hex_to_int(Line.substr(18, 2), data.DATA[4]));
  valid.catch_false(string_hex_to_int(Line.substr(21, 2), data.DATA[5]));
  valid.catch_false(string_hex_to_int(Line.substr(24, 2), data.DATA[6]));
  valid.catch_false(string_hex_to_int(Line.substr(27, 2), data.DATA[7]));

  if (Line.size() == 38)
  {
    valid.catch_false(string_hex_to_int(Line.substr(30, 2), time_byte_0));
    valid.catch_false(string_hex_to_int(Line.substr(32, 2), time_byte_1));
    valid.catch_false(string_hex_to_int(Line.substr(34, 2), time_byte_2));
    valid.catch_false(string_hex_to_int(Line.substr(36, 2), time_byte_3));

    data.TIMESTAMP = (time_byte_3 * (256 ^3)) + (time_byte_2 * (256 ^2)) + 
                      (time_byte_1 * 256) + time_byte_0;
  }

  if (valid.has_false() == false)
  {
    data.ID = upper *256 + lower;

    // Put value in pos
    if(data.ID == 0)
    {
      DATA.AD_0 = data;
    }
    else if(data.ID == 16)
    {
      DATA.AD_10 = data;
    }
    else if(data.ID == 48)
    {
      DATA.AD_30 = data;
    }
    else if(data.ID == 50)
    {
      DATA.AD_32 = data;
    }
    else if(data.ID == 74)
    {
      DATA.AD_4A = data;
    }
    else if(data.ID == 75)
    {
      DATA.AD_4B = data;
    }
    else if(data.ID == 80)
    {
      DATA.AD_50 = data;
    }
    else if(data.ID == 96)
    {
      DATA.AD_60 = data;
    }
    else if(data.ID == 100)
    {
      DATA.AD_64 = data;
    }
    else if(data.ID == 106)
    {
      DATA.AD_6A = data;
    }
    else if(data.ID == 112)
    {
      DATA.AD_70 = data;
    }
    else if(data.ID == 128)
    {
      DATA.AD_80 = data;
    }
    else if(data.ID == 144)
    {
      DATA.AD_90 = data;
    }
    else if(data.ID == 160)
    {
      DATA.AD_A0 = data;
    }
    else if(data.ID == 176)
    {
      DATA.AD_B0 = data;
    }
    else if(data.ID == 192)
    {
      DATA.AD_C0 = data;
    }
    else if(data.ID == 200)
    {
      DATA.AD_C8 = data;
    }
    else if(data.ID == 208)
    {
      DATA.AD_D0 = data;
    }
    else if(data.ID == 224)
    {
      DATA.AD_E0 = data;
    }
    else if(data.ID == 240)
    {
      DATA.AD_F0 = data;
    }
    else if(data.ID == 248)
    {
      DATA.AD_F8 = data;
    }
    else if(data.ID == 256)
    {
      DATA.AD_100 = data;
    }
    else if(data.ID == 258)
    {
      DATA.AD_102 = data;
    }
    else if(data.ID == 416)
    {
      DATA.AD_1A0 = data;
    }
    else if(data.ID == 448)
    {
      DATA.AD_1C0 = data;
    }
    else if(data.ID == 288)
    {
      DATA.AD_120 = data;
    }
    else if(data.ID == 296)
    {
      DATA.AD_128 = data;
    }
    else if(data.ID == 304)
    {
      DATA.AD_130 = data;
    }
    else if(data.ID == 312)
    {
      DATA.AD_138 = data;
    }
    else if(data.ID == 320)
    {
      DATA.AD_140 = data;
    }
    else if(data.ID == 336)
    {
      DATA.AD_150 = data;
    }
    else if(data.ID == 352)
    {
      DATA.AD_160 = data;
    }
    else if(data.ID == 382)
    {
      DATA.AD_17E = data;
    }
    else if(data.ID == 384)
    {
      DATA.AD_180 = data;
    }
    else if(data.ID == 400)
    {
      DATA.AD_190 = data;
    }
    else if(data.ID == 464)
    {
      DATA.AD_1D0 = data;
    }
    else if(data.ID == 480)
    {
      DATA.AD_1E0 = data;
    }
    else if(data.ID == 512)
    {
      DATA.AD_200 = data;
    }
    else if(data.ID == 520)
    {
      DATA.AD_208 = data;
    }
    else if(data.ID == 528)
    {
      DATA.AD_210 = data;
    }
    else if(data.ID == 531)
    {
      DATA.AD_213 = data;
    }
    else if(data.ID == 536)
    {
      DATA.AD_218 = data;
    }
    else if(data.ID == 583)
    {
      DATA.AD_247 = data;
    }
    else if(data.ID == 594)
    {
      DATA.AD_252 = data;
    }
    else if(data.ID == 595)
    {
      DATA.AD_253 = data;
    }
    else if(data.ID == 608)
    {
      DATA.AD_260 = data;
    }
    else if(data.ID == 624)
    {
      DATA.AD_270 = data;
    }
    else if(data.ID == 640)
    {
      DATA.AD_280 = data;
    }
    else if(data.ID == 656)
    {
      DATA.AD_290 = data;
    }
    else if(data.ID == 688)
    {
      DATA.AD_2B0 = data;
    }
    else if(data.ID == 704)
    {
      DATA.AD_2C0 = data;
    }
    else if(data.ID == 720)
    {
      DATA.AD_2D0 = data;
    }
    else if(data.ID == 724)
    {
      DATA.AD_2D4 = data;
    }
    else if(data.ID == 728)
    {
      DATA.AD_2D8 = data;
    }
    else if(data.ID == 752)
    {
      DATA.AD_2F0 = data;
    }
    else if(data.ID == 784)
    {
      DATA.AD_310 = data;
    }
    else if(data.ID == 792)
    {
      DATA.AD_318 = data;
    }
    else if(data.ID == 832)
    {
      DATA.AD_340 = data;
    }
    else if(data.ID == 864)
    {
      DATA.AD_360 = data;
    }
    else if(data.ID == 896)
    {
      DATA.AD_380 = data;
    }
    else if(data.ID == 904)
    {
      DATA.AD_388 = data;
    }
    else if(data.ID == 912)
    {
      DATA.AD_390 = data;
    }
    else if(data.ID == 920)
    {
      DATA.AD_398 = data;
    }
    else if(data.ID == 948)
    {
      DATA.AD_3B4 = data;
    }
    else if(data.ID == 1024)
    {
      DATA.AD_400 = data;
    }
    else if(data.ID == 1029)
    {
      DATA.AD_405 = data;
    }
    else if(data.ID == 1034)
    {
      DATA.AD_40A = data;
    }
    else if(data.ID == 1077)
    {
      DATA.AD_435 = data;
    }
    else if(data.ID == 1109)
    {
      DATA.AD_455 = data;
    }
    else if(data.ID == 1409)
    {
      DATA.AD_581 = data;
    }
    else if(data.ID == 1506)
    {
      DATA.AD_5E2 = data;
    }

    // Message Recieved Lines
    else if(data.ID == 2024)
    {
      DATA.AD_7E8 = data;
      PID_Recieved = data.ID;
      ret_message_recieved = true;
    }
    else if(data.ID == 2025)
    {
      DATA.AD_7E9 = data;
      PID_Recieved = data.ID;
      ret_message_recieved = true;
    }
    else if(data.ID == 2026)
    {
      DATA.AD_7EA = data;
      PID_Recieved = data.ID;
      ret_message_recieved = true;
    }
    else if(data.ID == 2027)
    {
      DATA.AD_7EB = data;
      PID_Recieved = data.ID;
      ret_message_recieved = true;
    }
    
    // Unknown
    else
    {
      DATA.AD_UNKNOWN = data;
    }
  }

  return ret_message_recieved;
}

bool AUTOMOBILE_AVAILABILITY::check_for_live_data(unsigned long tmeFrame_Time)
{
  if (ACTIVITY_TIMER.ping_down(tmeFrame_Time) == false)
  {
    return false;
  }
  else
  {
    return true;
  }
}

bool AUTOMOBILE_AVAILABILITY::set_active(AUTOMOBILE_TRANSLATED_DATA &Status, bool Available, unsigned long tmeFrame_Time)
{
  bool ret_changed = false;

  if (Available == false)
  {
    // Data not available, but was before.
    if (ACTIVE == true)
    {
      // turn everything off
      Status.STEERING.set_source_availability(false);
      Status.GEAR.set_source_availability(false);
      Status.SPEED.set_source_availability(false);
      Status.TEMPS.set_source_availability(false);
      Status.RPM.set_source_availability(false);
      Status.POWER.set_source_availability(false);
      Status.INDICATORS.set_source_availability(false);
      Status.FUEL.set_source_availability(false);
      Status.DOORS.set_source_availability(false);
      Status.GUAGES.set_source_availability(false);

      ACTIVE = false;
      ret_changed = true;
    }
  }
  else
  {
    // Data available.
    
    // Restart the timeout timer

    ACTIVITY_TIMER.ping_up(tmeFrame_Time, 5000);

    // Data available, but wasnt before.
    if (ACTIVE == false)
    {
      // turn everything on
      Status.STEERING.set_source_availability(true);
      Status.GEAR.set_source_availability(true);
      Status.SPEED.set_source_availability(true);
      Status.TEMPS.set_source_availability(true);
      Status.RPM.set_source_availability(true);
      Status.POWER.set_source_availability(true);
      Status.INDICATORS.set_source_availability(true);
      Status.FUEL.set_source_availability(true);
      Status.DOORS.set_source_availability(true);
      Status.GUAGES.set_source_availability(true);

      ACTIVE = true;
      ret_changed = true;
    }    
  }
  
  return ret_changed;
}

bool AUTOMOBILE_AVAILABILITY::is_active()
{
  return ACTIVE;
}

void AUTOMOBILE::add_to_pid_send_list(string Requested_PID)
{
  REQUESTED_PID_SEND_LIST.push_back(Requested_PID);
}

string AUTOMOBILE::requested_pid()
{
  return REQUESTED_PID;
}

bool AUTOMOBILE::active()
{
  return AVAILABILITY.is_active();
}

void AUTOMOBILE::process(COMPORT &Com_Port, unsigned long tmeFrame_Time)
{
  int pid_recieved = 0;

  if (AVAILABILITY.check_for_live_data(tmeFrame_Time) == false)
  {
   if (AVAILABILITY.set_active(STATUS, false, tmeFrame_Time) == true)
   {
    CHANGED = true;
   }
  }

  if (Com_Port.recieve_size() > 0)
  {
    while (Com_Port.recieve_size() > 0)
    {
      string input = trim(Com_Port.recieve());
      if(input.size() == 29 || input.size() == 38)
      {
        message_count++;

        if (parse(input, pid_recieved) == true)
        {
          AUTOMOBILE_DATA_LINE message;

          // Check to see what was requested and put data in correct 
          //  spot.

          if (pid_recieved == 0x7E8)
          {
            message = DATA.AD_7E8;
          }
          else if (pid_recieved == 0x7E9)
          {
            message = DATA.AD_7E9;
          }
          else if (pid_recieved == 0x7EA)
          {
            message = DATA.AD_7EA;
          }
          else if (pid_recieved == 0x7EB)
          {
            message = DATA.AD_7EB;
          }

          // Check message to make sure its in correct format
          if (message.DATA[0] == 0x03 && message.DATA[1] == 0x41)
          {
            // Dont send another request until wait delay is up
            REQUESTED_PID_TIMER_WAIT.ping_up(tmeFrame_Time, REQUESTED_PID_TIMER_WAIT_DELAY);

            // Speed

            // Temp
            if (REQUESTED_PID == "05")  // Engine coolant temperature
            {
              STATUS.TEMPS.store_coolant_05(message.DATA[3]);
            }

            if (REQUESTED_PID == "67")  // Engine coolant temperature
            {
              STATUS.TEMPS.store_coolant_67(message.DATA[3], message.DATA[4]);
            }

            if (REQUESTED_PID == "0F")  // Intake air temperature
            {
              STATUS.TEMPS.store_air_intake_0f(message.DATA[3]);
            }

            if (REQUESTED_PID == "68")  // Intake air temperature
            {
              STATUS.TEMPS.store_air_intake_68(message.DATA[3], message.DATA[4]);
            }
            
            if (REQUESTED_PID == "46")  // Ambient air temperature
            {
              STATUS.TEMPS.store_ambiant_air_46(message.DATA[3]);
            }
            
            if (REQUESTED_PID == "5C")  // Engine oil temperature
            {
              STATUS.TEMPS.store_oil_5c(message.DATA[3]);
            }
            
            if (REQUESTED_PID == "6B")  // Exhaust gas recirculation temperature
            {
              STATUS.TEMPS.store_exhaust_gas_6b(message.DATA[3]);
            }
            
            if (REQUESTED_PID == "6B")  // Manifold surface temperature
            {
              STATUS.TEMPS.store_manifold_surface_84(message.DATA[3]);
            }



            // Voltage

            if (REQUESTED_PID == "42")  // Engine coolant temperature
            {
              STATUS.ELECTRICAL.store_control_voltage_42(message.DATA[3], message.DATA[4]);
            }

            // Other

            //if (REQUESTED_PID == "4F")  // Engine coolant temperature
            //{
            //  STATUS.ELECTRICAL.store_control_voltage_42(message.DATA[3], message.DATA[4]);
            //}





          }
        }

        // High level Compute requiring calculation on all data.
        //  Compute on all data but can be processor intensive.
        //compute_high();

        AVAILABILITY.set_active(STATUS, true, tmeFrame_Time);
        CHANGED = true;
      }
    }
  }

  // Send pid to get values
  if (REQUESTED_PID_TIMER_WAIT.ping_down(tmeFrame_Time) == false && active() == true)
  {
    // Dont send another request until wait timeout is up.
    REQUESTED_PID_TIMER_WAIT.ping_up(tmeFrame_Time, REQUESTED_PID_TIMER_TIMEOUT_DELAY);

    REQUESTED_PID_SEND_LIST_POSITION ++;

    if (REQUESTED_PID_SEND_LIST_POSITION < 0 || REQUESTED_PID_SEND_LIST_POSITION > REQUESTED_PID_SEND_LIST.size() -1)
    {
      REQUESTED_PID_SEND_LIST_POSITION = 0;
    }
    
    REQUESTED_PID = REQUESTED_PID_SEND_LIST[REQUESTED_PID_SEND_LIST_POSITION];

    Com_Port.send(REQUESTED_PID);    
  }
}

void AUTOMOBILE::translate(unsigned long tmeFrame_Time)
{
  if (AVAILABILITY.is_active() == true)
  {  
    // Steering Wheel Angle
    STATUS.STEERING.store_steering_wheel_angle((DATA.AD_10.DATA[6] *256) + DATA.AD_10.DATA[7], 
                                                DATA.AD_10.DATA[2]);

    // Speed
    STATUS.SPEED.store_trans((DATA.AD_F0.DATA[0] *256) + DATA.AD_F0.DATA[1], 1.13, tmeFrame_Time);

    STATUS.SPEED.store_LF((DATA.AD_190.DATA[0] *256) + DATA.AD_190.DATA[1], tmeFrame_Time);
    STATUS.SPEED.store_RF((DATA.AD_190.DATA[2] *256) + DATA.AD_190.DATA[3], tmeFrame_Time);
    STATUS.SPEED.store_LB((DATA.AD_190.DATA[4] *256) + DATA.AD_190.DATA[5], tmeFrame_Time);
    STATUS.SPEED.store_RB((DATA.AD_190.DATA[6] *256) + DATA.AD_190.DATA[7], tmeFrame_Time);

    STATUS.SPEED.store_dash(DATA.AD_130.DATA[6], DATA.AD_130.DATA[7], tmeFrame_Time);

    // Transmission Gear Position
    STATUS.GEAR.store(DATA.AD_F0.DATA[2]);
    STATUS.GEAR.store_gear_selection(DATA.AD_D0.DATA[1], DATA.AD_D0.DATA[2]);

    // RPM
    STATUS.RPM.store((DATA.AD_90.DATA[4] *256) + DATA.AD_90.DATA[5]);
    STATUS.RPM.store_2((DATA.AD_90.DATA[2] *256) + DATA.AD_90.DATA[3]);

    // BRAKE PRESSURE
    STATUS.POWER.store((DATA.AD_80.DATA[5] *256) + DATA.AD_80.DATA[6]);

    // INDICATORS int Lights, int Parking_Brake, int Ignition
    STATUS.INDICATORS.store_lights(DATA.AD_C8.DATA[7]);
    STATUS.INDICATORS.store_lights_high_beam(DATA.AD_360.DATA[0]);
    STATUS.INDICATORS.store_on(DATA.AD_C8.DATA[3]);
    //STATUS.INDICATORS.store_ignition(DATA.AD_C8.DATA[1]);
    STATUS.INDICATORS.store_cruise_control(DATA.AD_200.DATA[6], DATA.AD_200.DATA[7], .312);

    // FUEL
    STATUS.FUEL.store_consumed(DATA.AD_200.DATA[7]);
    STATUS.FUEL.store_percentage(DATA.AD_C0.DATA[7]);
    STATUS.FUEL.store_level(DATA.AD_380.DATA[7]);

    // DOORS 3B 3F
    STATUS.DOORS.store(DATA.AD_360.DATA[2]);

    // Guages
    STATUS.GUAGES.store_coolant(DATA.AD_100.DATA[3]);
    
    // Low level Compute not requiring calculation on all data.
    //  Fast but not fully acurate.
    //  Currently call just before the data is displayed.
    CALCULATED.compute_low(STATUS, tmeFrame_Time);
  }
}

#endif