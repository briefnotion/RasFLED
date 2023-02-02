// ***************************************************************************************
// *
// *    Core       | Everything within this document is proprietary to Core Dynamics.
// *    Dynamics   | Any unauthorized duplication will be subject to prosecution.
// *
// *    Department : (R+D)^2                        Name: gadgets_alerts.cpp
// *       Sub Dept: Programming
// *    Location ID: 856-45B
// *                                                      (c) 2856 - 2858 Core Dynamics
// ***************************************************************************************

#ifndef GADGETS_ALERTS_CPP
#define GADGETS_ALERTS_CPP

#include "gadgets_alerts.h"

using namespace std;

// -------------------------------------------------------------------------------------
//  Panel Class

void ALERTS_PANEL_GRID::create()
{
  CAR = CAR01 + CAR02 + CAR03 + CAR04 + CAR05 + CAR06 + CAR07 + CAR08 +
        CAR09 + CAR10 + CAR11 + CAR12 + CAR13 + CAR14 + CAR15 + CAR16 ;

  CAR_LD_OPEN = CAR_LD01_OPEN + CAR_LD02_OPEN + CAR_LD03_OPEN + CAR_LD04_OPEN;
  CAR_RD_OPEN = CAR_RD01_OPEN + CAR_RD02_OPEN + CAR_RD03_OPEN + CAR_RD04_OPEN;

  CAR_LD_FRONT_CLOSED = CAR_LD01_FRONT_CLOSED + CAR_LD02_FRONT_CLOSED + CAR_LD03_FRONT_CLOSED + CAR_LD04_FRONT_CLOSED;
  CAR_LD_BACK_CLOSED = CAR_LD01_BACK_CLOSED + CAR_LD02_BACK_CLOSED + CAR_LD03_BACK_CLOSED + CAR_LD04_BACK_CLOSED;

  CAR_RD_FRONT_CLOSED = CAR_RD01_FRONT_CLOSED + CAR_RD02_FRONT_CLOSED + CAR_RD03_FRONT_CLOSED + CAR_RD04_FRONT_CLOSED;
  CAR_RD_BACK_CLOSED = CAR_RD01_BACK_CLOSED + CAR_RD02_BACK_CLOSED + CAR_RD03_BACK_CLOSED + CAR_RD04_BACK_CLOSED;
  
  CAR_LABEL.PROP.POSX = 3;
  CAR_LABEL.PROP.POSY = 2;
  CAR_LABEL.PROP.SIZEX = 22;
  CAR_LABEL.PROP.COLORS_ON = true;
  CAR_LABEL.set_color(COLOR_RED, COLOR_WHITE);
  CAR_LABEL.PROP.JUSTIFICATION_CENTER = true;

  CAR_BODY.PROP.POSX = 3;
  CAR_BODY.PROP.POSY = 3;
  CAR_BODY.PROP.SIZEX = 22;
  CAR_BODY.PROP.SIZEY = 16;
  CAR_BODY.PROP.COLORS_ON = true;
  CAR_BODY.set_color(COLOR_RED, COLOR_WHITE);
  CAR_BODY.PROP.JUSTIFICATION_LEFT = true;

  CAR_LD_F.PROP.POSX = 3;
  CAR_LD_F.PROP.POSY = 3 + 5;
  CAR_LD_F.PROP.SIZEX = 6;
  CAR_LD_F.PROP.SIZEY = 4;
  CAR_LD_F.PROP.COLORS_ON = true;
  CAR_LD_F.set_color(COLOR_RED, COLOR_WHITE);
  CAR_LD_F.PROP.JUSTIFICATION_LEFT = true;

  CAR_LD_B.PROP.POSX = 3;
  CAR_LD_B.PROP.POSY = 3 + 9;
  CAR_LD_B.PROP.SIZEX = 6;
  CAR_LD_B.PROP.SIZEY = 4;
  CAR_LD_B.PROP.COLORS_ON = true;
  CAR_LD_B.set_color(COLOR_RED, COLOR_WHITE);
  CAR_LD_B.PROP.JUSTIFICATION_LEFT = true;

  CAR_RD_F.PROP.POSX = 3 + 17;
  CAR_RD_F.PROP.POSY = 3 + 5;
  CAR_RD_F.PROP.SIZEX = 6;
  CAR_RD_F.PROP.SIZEY = 4;
  CAR_RD_F.PROP.COLORS_ON = true;
  CAR_RD_F.set_color(COLOR_RED, COLOR_WHITE);
  CAR_RD_F.PROP.JUSTIFICATION_LEFT = true;

  CAR_RD_B.PROP.POSX = 3 + 17;
  CAR_RD_B.PROP.POSY = 3 + 9;
  CAR_RD_B.PROP.SIZEX = 6;
  CAR_RD_B.PROP.SIZEY = 4;
  CAR_RD_B.PROP.COLORS_ON = true;
  CAR_RD_B.set_color(COLOR_RED, COLOR_WHITE);
  CAR_RD_B.PROP.JUSTIFICATION_LEFT = true;

  CAR_LABEL.set_text("Car Status");

  CAR_BODY.set_text(CAR);
}

void ALERTS_PANEL_GRID::update(system_data &sdSysData, unsigned long &tmeCurrentMillis)
{

}

bool ALERTS_PANEL_GRID::draw(bool Refresh, unsigned long tmeFrame_Time, PANEL Alerts_Panel)
{
  CAR_LABEL.draw(Alerts_Panel, Refresh);
  CAR_BODY.draw(Alerts_Panel, Refresh);

  CAR_LD_F.set_text(CAR_LD_OPEN);
  CAR_LD_B.set_text(CAR_LD_OPEN);
  CAR_RD_F.set_text(CAR_RD_OPEN);
  CAR_RD_B.set_text(CAR_RD_OPEN);

  CAR_LD_F.draw(Alerts_Panel, Refresh);
  CAR_LD_B.draw(Alerts_Panel, Refresh);
  CAR_RD_F.draw(Alerts_Panel, Refresh);
  CAR_RD_B.draw(Alerts_Panel, Refresh);

  Alerts_Panel.draw(Refresh);

  return false;
}


#endif