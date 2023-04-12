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

void AUTOMOBILE_FUEL::store_consumed(int Consumed)
{
  CONSUMED = ((float)Consumed) * 0.0015259021896696;

  CONSUMED_DISP = to_string_round_to_nth(CONSUMED, 2) + " gal";
}

void AUTOMOBILE_FUEL::store_percentage(int Percentage)
{
  PERCENTAGE = ((float)Percentage) * 0.0015259021896696;

  PERCENTAGE_DISP = to_string_round_to_nth(PERCENTAGE, 2) + " %";
}

void AUTOMOBILE_FUEL::store_level(int Level)
{
  LEVEL = ((float)Level) * 0.0015259021896696;

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

void AUTOMOBILE_INDICATORS::store_lights(int Lights)
{
  // Parse Lights
  if (Lights == 0)
  {
    LIGHTS = false;
    LIGHTS_POS = 0;
    LIGHTS_DESC = "OFF";
  }
  else if (Lights == 1)
  {
    LIGHTS = true;
    LIGHTS_POS = 1;
    LIGHTS_DESC = "PARKING";
  }
  else if (Lights == 2)
  {
    LIGHTS = true;
    LIGHTS_POS = 2;
    LIGHTS_DESC = "ON";
  }
  else if (Lights == 3)
  {
    LIGHTS = true;
    LIGHTS_POS = 3;
    LIGHTS_DESC = "AUTO";
  }
  else
  {
    LIGHTS = false;
    LIGHTS_POS = Lights;
    LIGHTS_DESC = "UNKNOWN";
  }
}

void AUTOMOBILE_INDICATORS::store_parking_brake(int Parking_Brake)
{
  // Parse Parking Brake
  if (Parking_Brake == 176)
  {
    PARKING_BRAKE = false;
    PARKING_BRAKE_DESC = "PARKING BRAKE ON";
  }
  else if (Parking_Brake == 177)
  {
    PARKING_BRAKE = true;
    PARKING_BRAKE_DESC = "PARKING BRAKE OFF";
  }
  else
  {
    PARKING_BRAKE = false;
    PARKING_BRAKE_DESC = "PARKING BRAKE UNKNOWN";
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

bool AUTOMOBILE_INDICATORS::val_lights()
{
  return LIGHTS;
}

int AUTOMOBILE_INDICATORS::val_lights_pos()
{
  return LIGHTS_POS;
}

string AUTOMOBILE_INDICATORS::lights()
{
  return LIGHTS_DESC;
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

void AUTOMOBILE_STEERING::store_steering_wheel_angle(int Angle, int Direction)
{
  // x8000 at 0 deg. x8500 at 90 deg. x9000 at 180 deg.
  //VAL_STEERING_WHEEL_ANGLE = ((float)Angle - 32768);

  VAL_STEERING_WHEEL_ANGLE = (((float)Angle - 32768) /4 ) *.18;

  // MSB for Direction

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

// Multiplier source unknown.  not calculating correctly.
// Possibly wrong spec tire size.  How the car knows is beyond me.
void AUTOMOBILE_VELOCITY::store(int kmph, float Multiplier)
{
  // Possibly meters per second devided by 3  (Multiplier = 1.2 for kmph conversion )
  //                                          (3.6 kmph = 1 mps                     )

  MULTIPLIER = Multiplier;

  KMPH = (kmph * MULTIPLIER) / 10;  // Multiplier passed is 1.2 but needs verification
                                  //  at higher speeds to rule out 1.1.

  MPH = velocity_translate_kmph_to_mph(KMPH);
  KMPH_DISP = to_string_round_to_nth(KMPH, 1);
  MPH_DISP = to_string_round_to_nth(MPH, 1);
}

float AUTOMOBILE_VELOCITY::val_kmph()
{
  return KMPH;
}

float AUTOMOBILE_VELOCITY::val_mph()
{
  return MPH;
}

string AUTOMOBILE_VELOCITY::kmph()
{
  return KMPH_DISP;
}

string AUTOMOBILE_VELOCITY::mph()
{
  return MPH_DISP;
}

void AUTOMOBILE_VELOCITY::store_LF(int mps)
{
  LF_KMPH = ((mps - 32768) * MULTIPLIER) / 100;  

  LF_MPH = velocity_translate_kmph_to_mph(LF_KMPH);
  LF_KMPH_DISP = to_string_round_to_nth(LF_KMPH, 1);
  LF_MPH_DISP = to_string_round_to_nth(LF_MPH, 1);
}

float AUTOMOBILE_VELOCITY::val_LF_kmph()
{
  return LF_KMPH;
}

float AUTOMOBILE_VELOCITY::val_LF_mph()
{
  return LF_MPH;
}

string AUTOMOBILE_VELOCITY::LF_kmph()
{
  return LF_KMPH_DISP;
}

string AUTOMOBILE_VELOCITY::LF_mph()
{
  return LF_MPH_DISP;
}

void AUTOMOBILE_VELOCITY::store_RF(int mps)
{
  RF_KMPH = ((mps - 32768) * MULTIPLIER) / 100;  

  RF_MPH = velocity_translate_kmph_to_mph(RF_KMPH);
  RF_KMPH_DISP = to_string_round_to_nth(RF_KMPH, 1);
  RF_MPH_DISP = to_string_round_to_nth(RF_MPH, 1);
}

float AUTOMOBILE_VELOCITY::val_RF_kmph()
{
  return RF_KMPH;
}

float AUTOMOBILE_VELOCITY::val_RF_mph()
{
  return RF_MPH;
}

string AUTOMOBILE_VELOCITY::RF_kmph()
{
  return RF_KMPH_DISP;
}

string AUTOMOBILE_VELOCITY::RF_mph()
{
  return RF_MPH_DISP;
}

void AUTOMOBILE_VELOCITY::store_LB(int mps)
{
  LB_KMPH = ((mps - 32768) * MULTIPLIER) / 100;  

  LB_MPH = velocity_translate_kmph_to_mph(LB_KMPH);
  LB_KMPH_DISP = to_string_round_to_nth(LB_KMPH, 1);
  LB_MPH_DISP = to_string_round_to_nth(LB_MPH, 1);
}

float AUTOMOBILE_VELOCITY::val_LB_kmph()
{
  return LB_KMPH;
}

float AUTOMOBILE_VELOCITY::val_LB_mph()
{
  return LB_MPH;
}

string AUTOMOBILE_VELOCITY::LB_kmph()
{
  return LB_KMPH_DISP;
}

string AUTOMOBILE_VELOCITY::LB_mph()
{
  return LB_MPH_DISP;
}

void AUTOMOBILE_VELOCITY::store_RB(int mps)
{
  RB_KMPH = ((mps - 32768) * MULTIPLIER) / 100;  

  RB_MPH = velocity_translate_kmph_to_mph(RB_KMPH);
  RB_KMPH_DISP = to_string_round_to_nth(RB_KMPH, 1);
  RB_MPH_DISP = to_string_round_to_nth(RB_MPH, 1);
}

float AUTOMOBILE_VELOCITY::val_RB_kmph()
{
  return RB_KMPH;
}

float AUTOMOBILE_VELOCITY::val_RB_mph()
{
  return RB_MPH;
}

string AUTOMOBILE_VELOCITY::RB_kmph()
{
  return RB_KMPH_DISP;
}

string AUTOMOBILE_VELOCITY::RB_mph()
{
  return RB_MPH_DISP;
}

void AUTOMOBILE_TRANSMISSION_GEAR::store(int gear)
{
  REPORTED = gear;    // Wrong on park and neutral and reverse.

  if (gear == 0)
  {
    SHORT_DESC = "N";
    LONG_DESC = "Neutral";
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
  else if (gear == 19)
  {
    SHORT_DESC = "P";
    LONG_DESC = "Park";
  }
  else if (gear == -1)
  {
    SHORT_DESC = "R";
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

void AUTOMOBILE::parse(string Line)
{
  string left = "";
  int pos = 0;

  AUTOMOBILE_DATA_LINE data;

  data.ORIG = Line;

  data.ID = string_hex_to_int(Line.substr(0, 2)) * 256 + string_hex_to_int(Line.substr(3, 2));
  data.DATA[0] = string_hex_to_int(Line.substr(6, 2));
  data.DATA[1] = string_hex_to_int(Line.substr(9, 2));
  data.DATA[2] = string_hex_to_int(Line.substr(12, 2));
  data.DATA[3] = string_hex_to_int(Line.substr(15, 2));
  data.DATA[4] = string_hex_to_int(Line.substr(18, 2));
  data.DATA[5] = string_hex_to_int(Line.substr(21, 2));
  data.DATA[6] = string_hex_to_int(Line.substr(24, 2));
  data.DATA[7] = string_hex_to_int(Line.substr(27, 2));

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
  else if(data.ID == 65535)
  {
    DATA.AD_FFFF = data;
  }
  else
  {
    DATA.AD_UNKNOWN = data;
  }

}

void AUTOMOBILE::process(COMPORT &Com_Port)
{
  if (Com_Port.READ_FROM_COMM.size() > 0)
  {
    for (int pos = 0; pos < Com_Port.READ_FROM_COMM.size(); pos++)
    {
      string input = trim(Com_Port.READ_FROM_COMM[pos]);
      if(input.size() == 29)
      {
        message_count++;
        
        if(input[0] != '-')
        {
          parse(input);
        }
      }
    }

    CHANGED = true;
    Com_Port.READ_FROM_COMM.clear();
  }
}

void AUTOMOBILE::translate()
{
  // Steering Wheel Angle
  STATUS.STEERING.store_steering_wheel_angle((DATA.AD_10.DATA[6] *256) + DATA.AD_10.DATA[7], 
                                              DATA.AD_10.DATA[2]);

  // Speed
  STATUS.SPEED.store((DATA.AD_F0.DATA[0] *256) + DATA.AD_F0.DATA[1], 1.12);

  STATUS.SPEED.store_LF((DATA.AD_190.DATA[0] *256) + DATA.AD_190.DATA[1]);
  STATUS.SPEED.store_RF((DATA.AD_190.DATA[2] *256) + DATA.AD_190.DATA[3]);
  STATUS.SPEED.store_LB((DATA.AD_190.DATA[4] *256) + DATA.AD_190.DATA[5]);
  STATUS.SPEED.store_RB((DATA.AD_190.DATA[6] *256) + DATA.AD_190.DATA[7]);

  // Transmission Gear Position
  STATUS.GEAR.store(DATA.AD_F0.DATA[2]);

  // RPM
  STATUS.RPM.store((DATA.AD_90.DATA[4] *256) + DATA.AD_90.DATA[5]);

  // BRAKE PRESSURE
  STATUS.POWER.store((DATA.AD_80.DATA[5] *256) + DATA.AD_80.DATA[6]);

  // INDICATORS int Lights, int Parking_Brake, int Ignition
  STATUS.INDICATORS.store_lights(DATA.AD_C8.DATA[7]);
  STATUS.INDICATORS.store_parking_brake(DATA.AD_C8.DATA[3]);
  //STATUS.INDICATORS.store_ignition(DATA.AD_C8.DATA[1]);

  // FUEL
  STATUS.FUEL.store_consumed((DATA.AD_200.DATA[6] *256) + DATA.AD_200.DATA[7]);
  STATUS.FUEL.store_percentage((DATA.AD_C0.DATA[6] *256) + DATA.AD_C0.DATA[7]);
  STATUS.FUEL.store_level((DATA.AD_380.DATA[6] *256) + DATA.AD_380.DATA[7]);
}

#endif