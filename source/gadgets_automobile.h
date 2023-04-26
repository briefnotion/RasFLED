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

// -------------------------------------------------------------------------------------
//  AUTOMOBILE_OVERVIEW

//  Panel Properties
class AUTOMOBILE_OVERVIEW_GADGET_PROPERTIES
// Properties (duh)
{
  public: 

  int POSY = 0;
  int POSX = 0;
  int SIZEY = 6;
  int SIZEX = 22;

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

  //-----------
  // Door Values
  bool LEFT_FRONT_DOOR_VAL = true;
  bool RIGHT_FRONT_DOOR_VAL = true;
  bool LEFT_BACK_DOOR_VAL = true;
  bool RIGHT_BACK_DOOR_VAL = true;

  //-----------
  // Gear Selection Values
  Text_Field GEAR_SELECTION_PARK;
  Text_Field GEAR_SELECTION_REVERSE;
  Text_Field GEAR_SELECTION_NEUTRAL;
  Text_Field GEAR_SELECTION_DRIVE;
  Text_Field GEAR_SELECTION_LOW;

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
  Text_Field CRUIS_CONTROL;

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

// -------------------------------------------------------------------------------------
//  DATA_SET_GADGET

class DATA_SET_GADGET_PROPERTIES
// Properties (duh)
{
  public: 

  int POSY = 0;
  int POSX = 0;
  int SIZEY = 5;
  int SIZEX = 13;

  string DESCRIPTION = "";
};

class DATA_SET_GADGET
{
  private:

  Text_Field DESCRIPTION;

  Text_Field ID_0;
  Text_Field ID_1;

  BAR DATA_BAR_A;
  BAR DATA_BAR_B;

  Text_Field DATA_FIELD_0;
  Text_Field DATA_FIELD_1;
  Text_Field DATA_FIELD_2;
  Text_Field DATA_FIELD_3;
  Text_Field DATA_FIELD_4;
  Text_Field DATA_FIELD_5;
  Text_Field DATA_FIELD_6;
  Text_Field DATA_FIELD_7;

  Text_Field CALCULATION;

  public:

  DATA_SET_GADGET_PROPERTIES PROP;

  void create();

  void update(AUTOMOBILE_DATA_LINE Data, int Bar_Value_1, int Bar_Value_2, 
              string Calculation, unsigned long tmeFrame_Time);

  void update(AUTOMOBILE_DATA_LINE Data, 
              string Calculation, unsigned long tmeFrame_Time);

  void draw(PANEL Host_Panel, bool Refresh, unsigned long tmeFrame_Time);
};

// -------------------------------------------------------------------------------------
//  DATA_SET_GADGET

class DUEL_BAR_GUAGE_GADGET_PROPERTIES
// Properties (duh)
{
  public: 

  int POSY = 0;
  int POSX = 0;
  int SIZEY = 5;
  int SIZEX = 21;

  int SCALE = 1;

  string DESCRIPTION = "";

};

class DUEL_BAR_GUAGE_GADGET
{
  private:

  BAR DATA_BAR_A;
  BAR DATA_BAR_B;
  
  Text_Field SCALE;

  Text_Field VALUE;
  Text_Field MIN;
  Text_Field MAX;

  Text_Field DESCRIPTION;

  public:

  DUEL_BAR_GUAGE_GADGET_PROPERTIES PROP;

  void create();

  void update(float Value, unsigned long tmeFrame_Time);

  void draw(PANEL Host_Panel, bool Refresh, unsigned long tmeFrame_Time);
};

// -------------------------------------------------------------------------------------
//  AUTOMOBILE_GADGET


//  Panel Properties
class AUTOMOBILE_GADGET_PROPERTIES
// Properties (duh)
{
  public: 

  int POSY = 0;
  int POSX = 0;
  int SIZEY = 4;
  int SIZEX = 12;

};
class AUTOMOBILE_GADGET
{
  private:

  PANEL AUTOMOBILE_PANEL;

  Text_Field MESSAGES;

  Text_Field AD_UNKNOWN;

  //-----------

  SYMBOLS_6X5_SMALL NUMBERS_6X5;

  //-----------
  // Large Velocity
  Text_Field_Multi_Line LARGE_SPEED_DESC;
  Text_Field_Multi_Line LARGE_SPEED_1;
  Text_Field_Multi_Line LARGE_SPEED_10;

  //-----------
  // Large Gear
  Text_Field_Multi_Line LARGE_GEAR_DESC;
  Text_Field_Multi_Line LARGE_GEAR_1;

  // Large Acceleration
  Text_Field_Multi_Line LARGE_ACCELERATION_DESC;
  Text_Field_Multi_Line LARGE_ACCELERATION_1;
  Text_Field_Multi_Line LARGE_ACCELERATION_10;

  Text_Field LARGE_ACCELERATION_MIN;
  Text_Field LARGE_ACCELERATION_MAX;

  //-----------

  DUEL_BAR_GUAGE_GADGET SPEEDO;
  DUEL_BAR_GUAGE_GADGET TACHO;

  //-----------

  Text_Field ACCELERATION;

  //-----------

  Text_Field STEERING_WHEEL_DESC;
  BAR STEERING_WHEEL;
  Text_Field STEERING_WHEEL_ANGLE;

  //-----------

  DATA_SET_GADGET DATA_SET_01;
  DATA_SET_GADGET DATA_SET_02;
  DATA_SET_GADGET DATA_SET_03;
  DATA_SET_GADGET DATA_SET_04;
  DATA_SET_GADGET DATA_SET_05;
  DATA_SET_GADGET DATA_SET_06;
  DATA_SET_GADGET DATA_SET_07;
  DATA_SET_GADGET DATA_SET_08;

  //-----------



  //-----------

  bool CHANGED = false;

  public:

  AUTOMOBILE_GADGET_PROPERTIES PROP;  

  void create();
  // Panel to be drawn.  
  //  Define PROP (properties) before calling this routine.
  //    Property Size and Position is necessary before calling create.

  void update(system_data &sdSysData, unsigned long tmeFrame_Time);
  // Update values of panel
  //  Gadget will be redrawn if values did changed or animations scheduled. 

  bool draw(bool Refresh, unsigned long tmeFrame_Time);
  // Draw all changes to Panel.
  //  Set Refresh to true to force redraw.
  //  Animations require time reference.
  // Returns true if panel was redrawn.
};



#endif