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
#include "helper.h"
#include "symbols.h"

using namespace std;

// Ledgend Scale Types:
#define LEDGEND_OFF     0
#define LEDGEND_RANGE   1
#define LEDGEND_SCALER  2

// -------------------------------------------------------------------------------------
//  Panel Class

//  Panel Properties
class AUTOMOBILE_OVERVIEW_GADGET_PROPERTIES
// Properties (duh)
{
  public: 

  int POSY = 0;
  int POSX = 0;
  int SIZEY = 0;
  int SIZEX = 18;

};

class AUTOMOBILE_OVERVIEW_GADGET
{
  private:

  PANEL GADGET_PANEL;
  AUTOMOTIVE_SYMBOLS CAR_SYMBOLS;

  //-----------
  Text_Field_Multi_Line SYMBOL_CAR_BODY;
  Text_Field_Multi_Line SYMBOL_CAR_DOOR_LEFT_FRONT;
  Text_Field_Multi_Line SYMBOL_CAR_DOOR_RIGHT_FRONT;
  Text_Field_Multi_Line SYMBOL_CAR_DOOR_LEFT_BACK;
  Text_Field_Multi_Line SYMBOL_CAR_DOOR_RIGHT_BACK;

  // Door Values
  bool LEFT_FRONT_DOOR_VAL = true;
  bool RIGHT_FRONT_DOOR_VAL = true;
  bool LEFT_BACK_DOOR_VAL = true;
  bool RIGHT_BACK_DOOR_VAL = true;

  //-----------
  // Tire Test
  Text_Field LF_SPEED;
  Text_Field RF_SPEED;
  Text_Field LB_SPEED;
  Text_Field RB_SPEED;

  Text_Field LF_SPEED_OFFSET;
  Text_Field RF_SPEED_OFFSET;
  Text_Field LB_SPEED_OFFSET;
  Text_Field RB_SPEED_OFFSET;

  //-----------
  Text_Field LIGHTS_STATUS;
  Text_Field FUEL_LEVEL;

  //-----------

  bool CHANGED = false;

  public:

  AUTOMOBILE_OVERVIEW_GADGET_PROPERTIES PROP;  

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

  Text_Field AD_UNKNOWN;

  //-----------

  SYMBOLS_5X5_NUMBERS NUMBERS_5X5;

  //-----------
  // Large Velocity
  Text_Field_Multi_Line LARGE_SPEED_DESC;
  Text_Field_Multi_Line LARGE_SPEED_1;
  Text_Field_Multi_Line LARGE_SPEED_10;

  //-----------
  // Large Gear
  Text_Field_Multi_Line LARGE_GEAR_DESC;
  Text_Field_Multi_Line LARGE_GEAR_1;

  //-----------

  Text_Field SPEEDOMETER_DESC;
  BAR SPEEDOMETER;
  Text_Field SPEED;
  Text_Field GEAR;
  Text_Field SPEEDOMETER_MIN;
  Text_Field SPEEDOMETER_MAX;

  //-----------

  Text_Field RPM_DESC;
  BAR RPM_GUAGE;
  Text_Field RPM;
  Text_Field RPM_MIN;
  Text_Field RPM_MAX;

  //-----------

  Text_Field POWER_LOAD_DESC;
  BAR POWER_LOAD_GUAGE;
  Text_Field POWER_LOAD;
  Text_Field POWER_LOAD_MIN;
  Text_Field POWER_LOAD_MAX;

  //-----------

  Text_Field STEERING_WHEEL_DESC;
  BAR STEERING_WHEEL;
  Text_Field STEERING_WHEEL_ANGLE;

  //-----------

  //-----------

  Text_Field AD_D0;   // - Gear Lever Status, Transmission Gear Position
  Text_Field AD_130;  // - Speed
  Text_Field AD_200;  // - Fuel Consumed From Start
  Text_Field AD_218;  // - Odometer
  Text_Field AD_C0;   // - Fuel % hex 3A

  //-----------

  //-----------

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