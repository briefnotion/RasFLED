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

  Text_Field_Multi_Line SYMBOL_CAR_LIGHTS;

  Text_Field PARKING_LIGHT_LF;
  Text_Field PARKING_LIGHT_RF;
  Text_Field PARKING_LIGHT_LB;
  Text_Field PARKING_LIGHT_RB;

  Text_Field_Multi_Line PARKING_BREAK_LEFT;
  Text_Field_Multi_Line PARKING_BREAK_RIGHT;

  Text_Field_Multi_Line SYMBOL_CAR_DOOR_LEFT_FRONT;
  Text_Field_Multi_Line SYMBOL_CAR_DOOR_RIGHT_FRONT;
  Text_Field_Multi_Line SYMBOL_CAR_DOOR_LEFT_BACK;
  Text_Field_Multi_Line SYMBOL_CAR_DOOR_RIGHT_BACK;

  //-----------
  // Values
  bool LIGHTS_HEADLIGHT_VAL = true;
  bool LIGHTS_PARKING_LIGHTS_VAL = true;

  bool PARKING_BREAK_VAL = true;

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
  // Tire TTL

  //Text_Field LF_UNFILTERED_TTL;
  //Text_Field RF_UNFILTERED_TTL;
  //Text_Field LB_UNFILTERED_TTL;
  //Text_Field RB_UNFILTERED_TTL;

  //Char_Graph LF_UNFILTERED_TTL_DATA_FILL;
  //Char_Graph RF_UNFILTERED_TTL_DATA_FILL;
  //Char_Graph LB_UNFILTERED_TTL_DATA_FILL;
  //Char_Graph RB_UNFILTERED_TTL_DATA_FILL;

  Text_Field LF_TTL;
  Text_Field RF_TTL;
  Text_Field LB_TTL;
  Text_Field RB_TTL;

  Char_Graph LF_TTL_DATA_FILL;
  Char_Graph RF_TTL_DATA_FILL;
  Char_Graph LB_TTL_DATA_FILL;
  Char_Graph RB_TTL_DATA_FILL;

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

  string SCALE_BAR = ".:.|.:.|.o.|.:.|.:.";
  
  int BAR_SIZE = 12;

  int BAR_A_MAX_VALUE = 100;
  int BAR_B_MAX_VALUE = 100;

  string DESCRIPTION = "";

};

class DUEL_BAR_GUAGE_GADGET
{
  private:

  //BAR DATA_BAR_A;
  CYBR_BAR DATA_BAR_A;
  BAR DATA_BAR_B;
  
  Text_Field SCALE;

  Text_Field VALUE;
  Text_Field MIN;
  Text_Field MAX;

  Text_Field DESCRIPTION;

  public:

  DUEL_BAR_GUAGE_GADGET_PROPERTIES PROP;

  void create();

  bool jecto_ready();

  CYBR_SLICE jecto();

  void update(float Value, unsigned long tmeFrame_Time);

  void draw(PANEL Host_Panel, bool Refresh, unsigned long tmeFrame_Time);
};

class WATERFALL_HISTO_GADGET_PROPERTIES
// Properties (duh)
{
  public: 

  int POSY = 0;
  int POSX = 0;
  int SIZEY = 5;
  int SIZEX = 21;

  int BAR_SIZE = 12;
  
  int MAX_VALUE = 100;
};

class WATERFALL_HISTO_GADGET
{
  private:
  CYBR_BAR WATERF_A;
  CYBR_BAR WATERF_B;
  CYBR_BAR WATERF_C;
  CYBR_BAR WATERF_D;
  CYBR_BAR WATERF_E;

  void check_slices(unsigned long tmeFrame_Time);

  public:

  WATERFALL_HISTO_GADGET_PROPERTIES PROP;

  void create();

  bool jecto_ready();

  CYBR_SLICE jecto();

  void update_via_slice(CYBR_SLICE CYBR_Slice, unsigned long tmeFrame_Time);

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

  SYMBOLS_6X5_CHARACTER_SMALL CHARACTERS_6X5;

  //-----------
  // Large Velocity
  Text_Field_Multi_Line LARGE_SPEED_DESC;
  Text_Field_Multi_Line LARGE_SPEED_1;
  Text_Field_Multi_Line LARGE_SPEED_10;

  // Large Acceleration
  Text_Field_Multi_Line LARGE_ACCELERATION_DESC;
  Text_Field_Multi_Line LARGE_ACCELERATION_1;
  Text_Field_Multi_Line LARGE_ACCELERATION_10;

  Text_Field LARGE_ACCELERATION_MIN;
  Text_Field LARGE_ACCELERATION_MAX;

  //-----------
  // Large Gear
  Text_Field_Multi_Line LARGE_GEAR_DESC;
  Text_Field_Multi_Line LARGE_GEAR_S;
  Text_Field_Multi_Line LARGE_GEAR_1;

  // Large Acceleration
  Text_Field_Multi_Line LARGE_TACH_DESC;
  Text_Field_Multi_Line LARGE_TACH_1;
  Text_Field_Multi_Line LARGE_TACH_10;

  MIN_MAX_TIME TACHOMETER_MIN_MAX;
  Text_Field TACHOMETER_VALUE;
  Text_Field TACHOMETER_MAX;

  //-----------

  Text_Field STEERING_WHEEL_DESC;
  BAR STEERING_WHEEL;
  Text_Field STEERING_WHEEL_ANGLE;

  //-----------

  Text_Field TACHOMETER_DESC;
  CYBR_BAR TACHOMETER;
  CYBR_BAR TACHOMETER2;

  //-----------

  Text_Field TORQUE_DESC;
  Text_Field TORQUE_VAL;
  Text_Field TORQUE_MIN;
  Text_Field TORQUE_MAX;
  
  CYBR_BAR TORQUE;

  //-----------

  DUEL_BAR_GUAGE_GADGET SPEEDO;
  WATERFALL_HISTO_GADGET SPEEDO_WATERFALL;

  DUEL_BAR_GUAGE_GADGET SUPER_TEMP;
  WATERFALL_HISTO_GADGET SUPER_TEMP_WATERFALL;

  Text_Field WAT_0_0;
  Text_Field WAT_0_1;
  Text_Field WAT_0_2;
  Text_Field WAT_0_3;
  Text_Field WAT_0_4;
  Text_Field WAT_0_5;

  //-----------

  Text_Field ACCELERATION;

  //-----------

  Text_Field ST_0_0;
  Text_Field ST_0_1;
  Text_Field ST_0_2;
  Text_Field ST_0_3;
  //Text_Field ST_0_4;
  //Text_Field ST_0_5;
  //Text_Field ST_0_6;
  //Text_Field ST_0_7;
  //Text_Field ST_0_8;
  //Text_Field ST_0_9;

  Text_Field ST_1_0;
  Text_Field ST_1_1;
  Text_Field ST_1_2;
  Text_Field ST_1_3;
  //Text_Field ST_1_4;
  //Text_Field ST_1_5;
  //Text_Field ST_1_6;
  //Text_Field ST_1_7;
  //Text_Field ST_1_8;
  //Text_Field ST_1_9;

  Text_Field ST_3_0;
  Text_Field ST_3_1;
  //Text_Field ST_3_2;
  Text_Field ST_3_3;
  //Text_Field ST_3_4;
  Text_Field ST_3_5;
  //Text_Field ST_3_6;
  //Text_Field ST_3_7;
  //Text_Field ST_3_8;
  //Text_Field ST_3_9;

  Text_Field ST_4_0;
  Text_Field ST_4_1;
  //Text_Field ST_4_2;
  Text_Field ST_4_3;
  //Text_Field ST_4_4;
  Text_Field ST_4_5;
  //Text_Field ST_4_6;
  //Text_Field ST_4_7;
  //Text_Field ST_4_8;
  //Text_Field ST_4_9;


  //-----------

  //DATA_SET_GADGET DATA_SET_01;
  //DATA_SET_GADGET DATA_SET_02;
  DATA_SET_GADGET DATA_SET_03;
  DATA_SET_GADGET DATA_SET_04;
  //DATA_SET_GADGET DATA_SET_05;
  //DATA_SET_GADGET DATA_SET_06;
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