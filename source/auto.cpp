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

void AUTOMOBILE_BRAKE_PRESSURE::store(int Pressure)
{
  VAL_PRESSURE = -(Pressure - 32768);   // Value type unknown

  PRESSURE = to_string(VAL_PRESSURE);
}

int AUTOMOBILE_BRAKE_PRESSURE::val_pressure()
{
  return VAL_PRESSURE;
}

string AUTOMOBILE_BRAKE_PRESSURE::pressure()
{
  return PRESSURE;
}


void AUTOMOBILE_RPM::store(int Rpm)
{
  VAL_RPM = (Rpm - 25088) * 5;    // Wrong

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

  VAL_STEERING_WHEEL_ANGLE = ((float)Angle - 32768) *.18;

  // MSB for Direction
  if (Direction >= 128)
  {
    CLOCKWISE = true;
    DIRECTION = "->";
  }
  else
  {
    CLOCKWISE = FALSE;
    DIRECTION = "<-";
  }

  STEERING_WHEEL_ANGLE = to_string_round_to_nth(VAL_STEERING_WHEEL_ANGLE, 1) + " deg";
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

void AUTOMOBILE_VELOCITY::store(int kmph, float Multiplier)
{
  KMPH_X_10 = kmph * Multiplier;  // Multiplier guessed.

  MPH_X_10 = velocity_translate_kmph_to_mph(KMPH_X_10);
  KMPH = to_string_round_to_nth(KMPH_X_10 / 10, 1);
  MPH = to_string_round_to_nth(velocity_translate_kmph_to_mph(KMPH_X_10 / 10), 1);
}

float AUTOMOBILE_VELOCITY::kmph_x_10()
{
  return KMPH_X_10;
}

float AUTOMOBILE_VELOCITY::mph_x_10()
{
  return MPH_X_10;
}

string AUTOMOBILE_VELOCITY::kmph()
{
  return KMPH;
}

string AUTOMOBILE_VELOCITY::mph()
{
  return MPH;
}

void AUTOMOBILE_TRANSMISSION_GEAR::store(int gear)
{
  REPORTED = gear;    // Wrong on park and neutral and reverse.

  if (gear == 19)
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
  else if (gear == 0)
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
  STATUS.SPEED.store((DATA.AD_F0.DATA[0] *256) + DATA.AD_F0.DATA[1], 1.11);

  // Transmission Gear Position
  STATUS.GEAR.store(DATA.AD_F0.DATA[2]);

  // RPM
  STATUS.RPM.store((DATA.AD_90.DATA[4] *256) + DATA.AD_90.DATA[5]);

  // BRAKE PRESSURE
  STATUS.BRAKE_PRESSURE.store((DATA.AD_80.DATA[5] *256) + DATA.AD_80.DATA[6]);
}

#endif