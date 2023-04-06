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

  if (left_of_char(Line, '\t', left) == true);
  {
    data.ID = left;

    Line = right_of_char(Line, '\t', left);

    while (left_of_char(Line, '\t', left) == true && pos <7)
    {
      data.DATA[pos] = string_to_int(left);

      Line = right_of_char(Line, '\t', left);
      pos++;
    }
    data.DATA[pos] = string_to_int(left);

    // Put value in pos
    if(data.ID == "0")
    {
      DATA.AD_0 = data;
    }
    else if(data.ID == "10")
    {
      DATA.AD_10 = data;
    }
    else if(data.ID == "30")
    {
      DATA.AD_10 = data;
    }
    else if(data.ID == "32")
    {
      DATA.AD_10 = data;
    }
    else if(data.ID == "50")
    {
      DATA.AD_10 = data;
    }
    else if(data.ID == "60")
    {
      DATA.AD_10 = data;
    }
    else if(data.ID == "64")
    {
      DATA.AD_10 = data;
    }
    else if(data.ID == "90")
    {
      DATA.AD_10 = data;
    }
    else if(data.ID == "A0")
    {
      DATA.AD_10 = data;
    }
    else if(data.ID == "C0")
    {
      DATA.AD_10 = data;
    }
    else if(data.ID == "C8")
    {
      DATA.AD_10 = data;
    }
    else if(data.ID == "D0")
    {
      DATA.AD_10 = data;
    }
    else if(data.ID == "E0")
    {
      DATA.AD_10 = data;
    }
    else if(data.ID == "F0")
    {
      DATA.AD_10 = data;
    }
    else if(data.ID == "F8")
    {
      DATA.AD_10 = data;
    }
    else if(data.ID == "100")
    {
      DATA.AD_10 = data;
    }
    else if(data.ID == "102")
    {
      DATA.AD_10 = data;
    }
    else if(data.ID == "1C0")
    {
      DATA.AD_10 = data;
    }
    else if(data.ID == "120")
    {
      DATA.AD_10 = data;
    }
    else if(data.ID == "128")
    {
      DATA.AD_10 = data;
    }
    else if(data.ID == "130")
    {
      DATA.AD_10 = data;
    }
    else if(data.ID == "138")
    {
      DATA.AD_10 = data;
    }
    else if(data.ID == "140")
    {
      DATA.AD_10 = data;
    }
    else if(data.ID == "150")
    {
      DATA.AD_10 = data;
    }
    else if(data.ID == "160")
    {
      DATA.AD_10 = data;
    }
    else if(data.ID == "17E")
    {
      DATA.AD_10 = data;
    }
    else if(data.ID == "180")
    {
      DATA.AD_10 = data;
    }
    else if(data.ID == "190")
    {
      DATA.AD_10 = data;
    }
    else if(data.ID == "1D0")
    {
      DATA.AD_10 = data;
    }
    else if(data.ID == "1E0")
    {
      DATA.AD_10 = data;
    }
    else if(data.ID == "200")
    {
      DATA.AD_10 = data;
    }
    else if(data.ID == "200")
    {
      DATA.AD_10 = data;
    }
    else if(data.ID == "208")
    {
      DATA.AD_10 = data;
    }
    else if(data.ID == "213")
    {
      DATA.AD_10 = data;
    }
    else if(data.ID == "218")
    {
      DATA.AD_10 = data;
    }
    else if(data.ID == "247")
    {
      DATA.AD_10 = data;
    }
    else if(data.ID == "252")
    {
      DATA.AD_10 = data;
    }
    else if(data.ID == "253")
    {
      DATA.AD_10 = data;
    }
    else if(data.ID == "260")
    {
      DATA.AD_10 = data;
    }
    else if(data.ID == "280")
    {
      DATA.AD_10 = data;
    }
    else if(data.ID == "290")
    {
      DATA.AD_10 = data;
    }
    else if(data.ID == "2B0")
    {
      DATA.AD_10 = data;
    }
    else if(data.ID == "2D0")
    {
      DATA.AD_10 = data;
    }
    else if(data.ID == "2D4")
    {
      DATA.AD_10 = data;
    }
    else if(data.ID == "2D8")
    {
      DATA.AD_10 = data;
    }
    else if(data.ID == "310")
    {
      DATA.AD_10 = data;
    }
    else if(data.ID == "318")
    {
      DATA.AD_10 = data;
    }
    else if(data.ID == "360")
    {
      DATA.AD_10 = data;
    }
    else if(data.ID == "400")
    {
      DATA.AD_10 = data;
    }
    else if(data.ID == "40A")
    {
      DATA.AD_10 = data;
    }
    else if(data.ID == "455")
    {
      DATA.AD_10 = data;
    }

  }
}

void AUTOMOBILE::process(COMPORT &Com_Port)
{
  /*
  for (int pos = 0; pos < Com_Port.READ_FROM_COMM.size(); pos++)
  {
    parse(trim(Com_Port.READ_FROM_COMM[pos]));
  }
  */

  Com_Port.READ_FROM_COMM.clear();
}



#endif