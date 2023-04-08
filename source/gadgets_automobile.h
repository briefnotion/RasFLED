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

  Text_Field AD_0;
  Text_Field AD_10;
  Text_Field AD_30;
  Text_Field AD_32;
  Text_Field AD_50;
  Text_Field AD_60;
  Text_Field AD_64;
  Text_Field AD_90;
  Text_Field AD_A0;
  Text_Field AD_C0;
  Text_Field AD_C8;
  Text_Field AD_D0;
  Text_Field AD_E0;
  Text_Field AD_F0;
  Text_Field AD_F8;
  Text_Field AD_100;
  Text_Field AD_102;
  Text_Field AD_1C0;
  Text_Field AD_120;
  Text_Field AD_128;
  Text_Field AD_130;
  Text_Field AD_138;

  Text_Field AD_UNKNOWN;

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