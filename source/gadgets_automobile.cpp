// ***************************************************************************************
// *
// *    Core       | Everything within this document is proprietary to Core Dynamics.
// *    Dynamics   | Any unauthorized duplication will be subject to prosecution.
// *
// *    Department : (R+D)^2                        Name: gadgets_automobile.cpp
// *       Sub Dept: Programming
// *    Location ID: 856-45B
// *                                                      (c) 2856 - 2858 Core Dynamics
// ***************************************************************************************

#ifndef GADGETS_AUTOMOBILE_CPP
#define GADGETS_AUTOMOBILE_CPP

#include "gadgets_automobile.h"

using namespace std;

// -------------------------------------------------------------------------------------
//  Panel Class

void AUTOMOBILE_GADGET::create()
{
  // Build Display Window
  AUTOMOBILE_PANEL.PROP.SIZEY = PROP.SIZEY;
  AUTOMOBILE_PANEL.PROP.SIZEX = PROP.SIZEX;
  AUTOMOBILE_PANEL.PROP.POSY = PROP.POSY;
  AUTOMOBILE_PANEL.PROP.POSX = PROP.POSX;
  AUTOMOBILE_PANEL.PROP.COLOR = COLOR_WHITE;
  AUTOMOBILE_PANEL.PROP.BCOLOR = COLOR_BLACK;

  AUTOMOBILE_PANEL.create();

  Text_Field_Properties temp_prop;
  Text_Field_Properties temp_prop_2;

  //TEST.set_color(COLOR_RED, COLOR_WHITE);

  temp_prop.POSX = 3;
  temp_prop.POSY = 1;
  temp_prop.SIZEX = 50;
  temp_prop.COLORS_ON = true;
  temp_prop.BCOLOR = COLOR_BLACK;
  temp_prop.COLOR = COLOR_WHITE;
  temp_prop.JUSTIFICATION_LEFT = true;

  MESSAGES.PROP = temp_prop;

  AD_0.PROP = temp_prop;
  AD_10.PROP = temp_prop;
  AD_30.PROP = temp_prop;
  AD_32.PROP = temp_prop;
  AD_50.PROP = temp_prop;
  AD_60.PROP = temp_prop;
  AD_64.PROP = temp_prop;
  AD_90.PROP = temp_prop;
  AD_A0.PROP = temp_prop;
  AD_C0.PROP = temp_prop;
  AD_C8.PROP = temp_prop;
  AD_D0.PROP = temp_prop;
  AD_E0.PROP = temp_prop;
  AD_F0.PROP = temp_prop;
  AD_F8.PROP = temp_prop;
  AD_100.PROP = temp_prop;
  AD_102.PROP = temp_prop;
  AD_1C0.PROP = temp_prop;
  AD_120.PROP = temp_prop;
  AD_128.PROP = temp_prop;
  AD_130.PROP = temp_prop;
  AD_138.PROP = temp_prop;



  AD_UNKNOWN.PROP = temp_prop;

  MESSAGES.PROP.POSY = 0;

  AD_0.PROP.POSY = 1;
  AD_10.PROP.POSY = 2;
  AD_30.PROP.POSY = 3;
  AD_32.PROP.POSY = 4;
  AD_50.PROP.POSY = 5;
  AD_60.PROP.POSY = 6;
  AD_64.PROP.POSY = 7;
  AD_90.PROP.POSY = 8;
  AD_A0.PROP.POSY = 9;
  AD_C0.PROP.POSY = 10;
  AD_C8.PROP.POSY = 11;
  AD_D0.PROP.POSY = 12;
  AD_E0.PROP.POSY = 13;
  AD_F0.PROP.POSY = 14;
  AD_F8.PROP.POSY = 15;
  AD_100.PROP.POSY = 16;
  AD_102.PROP.POSY = 17;
  AD_1C0.PROP.POSY = 18;
  AD_120.PROP.POSY = 19;
  AD_128.PROP.POSY = 20;
  AD_130.PROP.POSY = 21;
  AD_138.PROP.POSY = 22;


  AD_UNKNOWN.PROP.POSY = 24;




}

void AUTOMOBILE_GADGET::update(system_data &sdSysData, unsigned long &tmeCurrentMillis)
{
  MESSAGES.set_text(to_string(sdSysData.CAR_INFO.message_count));

  AD_0.set_text(sdSysData.CAR_INFO.DATA.AD_0.ORIG);
  AD_10.set_text(sdSysData.CAR_INFO.DATA.AD_10.ORIG);
  AD_30.set_text(sdSysData.CAR_INFO.DATA.AD_30.ORIG);
  AD_32.set_text(sdSysData.CAR_INFO.DATA.AD_32.ORIG);
  AD_50.set_text(sdSysData.CAR_INFO.DATA.AD_50.ORIG);
  AD_60.set_text(sdSysData.CAR_INFO.DATA.AD_60.ORIG);
  AD_64.set_text(sdSysData.CAR_INFO.DATA.AD_64.ORIG);
  AD_90.set_text(sdSysData.CAR_INFO.DATA.AD_90.ORIG);
  AD_A0.set_text(sdSysData.CAR_INFO.DATA.AD_A0.ORIG);
  AD_C0.set_text(sdSysData.CAR_INFO.DATA.AD_C0.ORIG);
  AD_C8.set_text(sdSysData.CAR_INFO.DATA.AD_C8.ORIG);
  AD_D0.set_text(sdSysData.CAR_INFO.DATA.AD_D0.ORIG);
  AD_E0.set_text(sdSysData.CAR_INFO.DATA.AD_E0.ORIG);
  AD_F0.set_text(sdSysData.CAR_INFO.DATA.AD_F0.ORIG);
  AD_F8.set_text(sdSysData.CAR_INFO.DATA.AD_F8.ORIG);
  AD_100.set_text(sdSysData.CAR_INFO.DATA.AD_100.ORIG);
  AD_102.set_text(sdSysData.CAR_INFO.DATA.AD_102.ORIG);
  AD_120.set_text(sdSysData.CAR_INFO.DATA.AD_120.ORIG);
  AD_128.set_text(sdSysData.CAR_INFO.DATA.AD_128.ORIG);
  AD_130.set_text(sdSysData.CAR_INFO.DATA.AD_130.ORIG);
  AD_138.set_text(sdSysData.CAR_INFO.DATA.AD_138.ORIG);

  AD_UNKNOWN.set_text(sdSysData.CAR_INFO.DATA.AD_UNKNOWN.ORIG);

  sdSysData.CAR_INFO.CHANGED = false;
  CHANGED = true;
}

bool AUTOMOBILE_GADGET::draw(bool Refresh, unsigned long tmeFrame_Time)
{
  if (CHANGED == false)
  {

  }

  MESSAGES.draw(AUTOMOBILE_PANEL, Refresh);

  AD_0.draw(AUTOMOBILE_PANEL, Refresh);
  AD_10.draw(AUTOMOBILE_PANEL, Refresh);
  AD_30.draw(AUTOMOBILE_PANEL, Refresh);
  AD_32.draw(AUTOMOBILE_PANEL, Refresh);
  AD_50.draw(AUTOMOBILE_PANEL, Refresh);
  AD_60.draw(AUTOMOBILE_PANEL, Refresh);
  AD_64.draw(AUTOMOBILE_PANEL, Refresh);
  AD_90.draw(AUTOMOBILE_PANEL, Refresh);
  AD_A0.draw(AUTOMOBILE_PANEL, Refresh);
  AD_C0.draw(AUTOMOBILE_PANEL, Refresh);
  AD_C8.draw(AUTOMOBILE_PANEL, Refresh);
  AD_D0.draw(AUTOMOBILE_PANEL, Refresh);
  AD_E0.draw(AUTOMOBILE_PANEL, Refresh);
  AD_F0.draw(AUTOMOBILE_PANEL, Refresh);
  AD_F8.draw(AUTOMOBILE_PANEL, Refresh);
  AD_100.draw(AUTOMOBILE_PANEL, Refresh);
  AD_102.draw(AUTOMOBILE_PANEL, Refresh);
  AD_1C0.draw(AUTOMOBILE_PANEL, Refresh);
  AD_120.draw(AUTOMOBILE_PANEL, Refresh);
  AD_128.draw(AUTOMOBILE_PANEL, Refresh);
  AD_130.draw(AUTOMOBILE_PANEL, Refresh);
  AD_138.draw(AUTOMOBILE_PANEL, Refresh);

  AD_UNKNOWN.draw(AUTOMOBILE_PANEL, Refresh);

  AUTOMOBILE_PANEL.draw(Refresh);

  CHANGED = false;
  return false;
}


#endif