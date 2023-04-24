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
  // Build Display Window
  ALERTS_PANEL.PROP.SIZEY = PROP.SIZEY;
  ALERTS_PANEL.PROP.SIZEX = 0;
  ALERTS_PANEL.PROP.POSY = PROP.POSY;
  ALERTS_PANEL.PROP.POSX = PROP.POSX;
  ALERTS_PANEL.PROP.COLOR = COLOR_WHITE;
  ALERTS_PANEL.PROP.BCOLOR = COLOR_RED;

  ALERTS_PANEL.create();

  // Alerts side panel
  ALERTS_TEXT_BOX.PROP.SIZEY = PROP.SIZEY;
  ALERTS_TEXT_BOX.PROP.SIZEX = PROP.SIZEX;
  ALERTS_TEXT_BOX.PROP.POSY = PROP.POSY;
  ALERTS_TEXT_BOX.PROP.POSX = PROP.POSX;
  ALERTS_TEXT_BOX.PROP.COLOR = COLOR_WHITE;
  ALERTS_TEXT_BOX.PROP.BCOLOR = COLOR_BLACK;

  ALERTS_TEXT_BOX.create();
}

void ALERTS_PANEL_GRID::update(ALERT_SYSTEM &Alerts)
{
  // Process any changes to alerts, into the gadget, independant to draw system.
  if (Alerts.GENERIC_ALERTS.size() > 0)
  {
    for (int pos = 0; pos < Alerts.GENERIC_ALERTS.size(); pos++)
    {
      ALERTS_TEXT_BOX.add_line(0, "");
      ALERTS_TEXT_BOX.add_line(0, Alerts.GENERIC_ALERTS[pos].TEXT);
    }
    Alerts.GENERIC_ALERTS.clear();
    CHANGED = true;
  }
}

bool ALERTS_PANEL_GRID::draw(bool Refresh, unsigned long tmeFrame_Time, ALERT_SYSTEM &Alerts)
{
  if (Alerts.changed() == true)
  {
    update(Alerts);
  }

  if (CHANGED == false)
  {

  }

  ALERTS_TEXT_BOX.draw(Refresh);

  ALERTS_PANEL.draw(Refresh);

  CHANGED = false;
  return false;
}


#endif