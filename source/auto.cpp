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

  data.DATA[7] = 99;


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
  else if(data.ID == 144)
  {
    DATA.AD_90 = data;
  }
  else if(data.ID == 160)
  {
    DATA.AD_A0 = data;
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
  else if(data.ID == 784)
  {
    DATA.AD_310 = data;
  }
  else if(data.ID == 792)
  {
    DATA.AD_318 = data;
  }
  else if(data.ID == 864)
  {
    DATA.AD_360 = data;
  }
  else if(data.ID == 1024)
  {
    DATA.AD_400 = data;
  }
  else if(data.ID == 1034)
  {
    DATA.AD_40A = data;
  }
  else if(data.ID == 1109)
  {
    DATA.AD_455 = data;
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



#endif