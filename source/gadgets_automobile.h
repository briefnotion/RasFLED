// ***************************************************************************************
// *
// *    Core       | Everything within this document is proprietary to Core Dynamics.
// *    Dynamics   | Any unauthorized duplication will be subject to prosecution.
// *
// *    Department : (R+D)^2                        Name: gadgets_automobile.h
// *       Sub Dept: Programming
// *    Location ID: 856-45B
// *                                                      (c) 2856 - 2858 Core Dynamics
// ***************************************************************************************

#ifndef GADGETS_AUTOMOBILE_H
#define GADGETS_AUTOMOBILE_H

// Standard Header Files
#include <stdio.h>
#include <ncurses.h>
#include <string>
#include <deque>

#include "fled_time.h"
#include "stringthings.h"
#include "system.h"

#include "gadgets.h"
#include "helper_ncurses.h"
#include "auto.h"

using namespace std;

// Ledgend Scale Types:
#define LEDGEND_OFF     0
#define LEDGEND_RANGE   1
#define LEDGEND_SCALER  2

// -------------------------------------------------------------------------------------
//  Panel Class

//  Panel Properties
class AUTOMOBILE_GADGET_PROPERTIES
// Properties (duh)
{
  public: 

  int POSY = 0;
  int POSX = 0;
  int SIZEY = 0;
  int SIZEX = 0;

};

class AUTOMOBILE_GADGET
{
  private:

  PANEL AUTOMOBILE_PANEL;

  Text_Field MESSAGES;

  Text_Field AD_260;
  Text_Field AD_2C0;
  Text_Field AD_360;

  Text_Field AD_UNKNOWN;

  //-----------

  Text_Field AD_F0;
  BAR SPEEDOMETER;
  Text_Field SPEED;
  Text_Field GEAR;

  //-----------

  Text_Field AD_10;
  BAR STEERING_WHEEL;
  Text_Field STEERING_WHEEL_ANGLE;

  //-----------

  Text_Field AD_90;
  BAR RPM_GUAGE;
  Text_Field RPM;

  //-----------

  Text_Field AD_80;
  BAR BRAKE_PRESSURE_GUAGE;
  Text_Field BRAKE_PRESSURE;

  //-----------

  Text_Field AD_x0;
  BAR ACCELERATOR_POSITION_GUAGE;
  Text_Field ACCELERATOR_POSITION;

  //-----------

  Text_Field AD_x1;
  BAR TEMP_COOLANT_GUAGE;
  Text_Field TEMP_COOLANT;

  //-----------

  Text_Field AD_x2;
  BAR FUEL_LEVEL_GUAGE;
  Text_Field FUEL_LEVEL;

  //-----------

  Text_Field AD_C8;   // - Headlamp status, Ignition Status, Parking Brake Status
  Text_Field AD_D0;   // - Gear Lever Status, Transmission Gear Position
  Text_Field AD_130;  // - Speed
  Text_Field AD_200;  // - Fuel Consumed From Start
  Text_Field AD_380;  // - Fuel Level
  Text_Field AD_218;  // - Odometer
  Text_Field AD_C0;   // - Fuel % hex 3A

  bool CHANGED = false;

  public:

  AUTOMOBILE_GADGET_PROPERTIES PROP;  

  void create();
  // Panel to be drawn.  
  //  Define PROP (properties) before calling this routine.
  //    Property Size and Position is necessary before calling create.

  void update(system_data &sdSysData, unsigned long &tmeCurrentMillis);
  // Update values of panel
  //  Gadget will be redrawn if values did changed or animations scheduled. 

  bool draw(bool Refresh, unsigned long tmeFrame_Time);
  // Draw all changes to Panel.
  //  Set Refresh to true to force redraw.
  //  Animations require time reference.
  // Returns true if panel was redrawn.
};



#endif