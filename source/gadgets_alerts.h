// ***************************************************************************************
// *
// *    Core       | Everything within this document is proprietary to Core Dynamics.
// *    Dynamics   | Any unauthorized duplication will be subject to prosecution.
// *
// *    Department : (R+D)^2                        Name: gadgets_alerts.h
// *       Sub Dept: Programming
// *    Location ID: 856-45B
// *                                                      (c) 2856 - 2858 Core Dynamics
// ***************************************************************************************

#ifndef GADGETS_ALERTS_H
#define GADGETS_ALERTS_H

// Standard Header Files
#include <stdio.h>
#include <ncurses.h>
#include <string.h>
#include <deque>

#include "fled_time.h"
#include "stringthings.h"
#include "system.h"

#include "alert_system.h"
#include "gadgets.h"
#include "helper_ncurses.h"

using namespace std;

// Ledgend Scale Types:
#define LEDGEND_OFF     0
#define LEDGEND_RANGE   1
#define LEDGEND_SCALER  2

// -------------------------------------------------------------------------------------
//  Panel Class

//  Alerts Panel Properties
class ALERTS_PANEL_GRID_PROPERTIES
// Properties (duh)
{
  public: 

  int POSY = 0;
  int POSX = 0;
  int SIZEY = 0;
  int SIZEX = 0;

  //bool NEEDS_REFRESH_DATA = true;


};

class ALERTS_PANEL_GRID
// Creates Alerts screen.
// Panel mananages positions and gadgets. Will not need to be
//  externally accessed.
// Warning:
//  If Pos or Size changes, create will need to be called 
//    again.
//  Some properties can be changed directly but will not 
//    trigger the redraw or work correctly. 
//  To change properties properly, call the provided set 
//    routines or set routines of internal gadgets.
{
  private:
  //deque<ADSB_Channel> ADSB_Channel_q;

  //ADSB_Channel test;

  //int ADSB_Channel_Count = 0;

  Text_Field CAR_LABEL;
  Text_Field_Multi_Line CAR_BODY;
  Text_Field_Multi_Line CAR_LD_F;
  Text_Field_Multi_Line CAR_LD_B;
  Text_Field_Multi_Line CAR_RD_F;
  Text_Field_Multi_Line CAR_RD_B;
  //Text_Field TIME;
  //Text_Field AIRCRAFT_COUNT_TITLE;
  //Text_Field AIRCRAFT_COUNT;
  //Text_Field POSITIONED_AIRCRAFT_TITLE;
  //Text_Field POSITIONED_AIRCRAFT;
  //BAR DELTA_MESSAGES_BAR;

  

  // Images

  // Car Doors Closed
  //  1 :          ___
  //  2 :       -==   ==-
	//  3 :      /  .   .  \
	//  4 :     | -=======- |
	//  5 :     |\=========/|
	//  6 :    /|\=========/|\
	//  7 :     ||-       -||
	//  8 :     ||         ||
	//  9 :     ||         ||
	// 10 :     ||         ||
	// 11 :     ||         ||
	// 12 :     ||         ||
	// 13 :     |/    :    \|
	// 14 :     || _______ ||
	// 15 :      \\\#####///
	// 16 :        =======

  string CAR = "";

  string CAR01 = "          ___\n"        ;  //  1
  string CAR02 = "       -==   ==-\n"     ;  //  2
  string CAR03 = "      /  .   .  \\\n"   ;  //  3
  string CAR04 = "     | -=======- |\n"   ;  //  4
  string CAR05 = "     |\\=========/|\n"  ;  //  5
  string CAR06 = "    /|\\=========/|\\\n";  //  6
  string CAR07 = "     ||-       -||\n"   ;  //  7
  string CAR08 = "     ||         ||\n"   ;  //  8
  string CAR09 = "     ||         ||\n"   ;  //  9
  string CAR10 = "     ||         ||\n"   ;  // 10
  string CAR11 = "     ||         ||\n"   ;  // 11
  string CAR12 = "     ||         ||\n"   ;  // 12
  string CAR13 = "     |/    :    \\|\n"  ;  // 13
  string CAR14 = "     || _______ ||\n"   ;  // 14
  string CAR15 = "      \\\\\\#####///\n" ;  // 15
  string CAR16 = "        ======="      ;  // 16
                

  // Car Doors Open
  //   :          ___
  //   :       -==   ==-
  //   :      /  .   .  \
  //   :	   | -=======- |
  //   :	   |\=========/|  
  //   :   _-#\=========/#-_
  //   : _=/ #|-       -|# \=_
  //   :=/   #|         |#   \=
  //   :	   #|         |#    
  //   :   _-#|         |#-_
  //   : _=/ #|         |# \=_
  //   :=/   #|         |#   \=
  //   :     #/    :    \#
  //   :     || _______ ||
  //   :      \\\#####///
  //   :        =======

  // Car Door Left
  //  1 :   _-#
  //  2 : _=/ #
  //  3 :=/   #
  //  4 :	    #

  string CAR_LD_OPEN = "";
  string CAR_LD_FRONT_CLOSED = "";
  string CAR_LD_BACK_CLOSED = "";

  string CAR_LD01_OPEN = "   _-#\n";  //  1
  string CAR_LD02_OPEN = " _=/ #\n";  //  2
  string CAR_LD03_OPEN = "=/   #\n";  //  3
  string CAR_LD04_OPEN = "     #"  ;  //  4

  string CAR_LD01_FRONT_CLOSED = "    /|\n";  //  1
  string CAR_LD02_FRONT_CLOSED = "     |\n";  //  2
  string CAR_LD03_FRONT_CLOSED = "     |\n";  //  3
  string CAR_LD04_FRONT_CLOSED = "     |"  ;  //  4

  string CAR_LD01_BACK_CLOSED = "     |\n";  //  1
  string CAR_LD02_BACK_CLOSED = "     |\n";  //  2
  string CAR_LD03_BACK_CLOSED = "     |\n";  //  3
  string CAR_LD04_BACK_CLOSED = "     |"  ;  //  4

    // Car Door Left
  //  1 :|#-
  //  2 :# \=
  //  3 :#   \=
  //  4 :#

  string CAR_RD_OPEN = "";
  string CAR_RD_FRONT_CLOSED = "";
  string CAR_RD_BACK_CLOSED = "";

  string CAR_RD01_OPEN = "#-_\n"     ; //  1
  string CAR_RD02_OPEN = "# \\=_\n"  ; //  2
  string CAR_RD03_OPEN = "#   \\=\n"; //  3
  string CAR_RD04_OPEN = "#"        ; //  4

  string CAR_RD01_FRONT_CLOSED = "|\\\n";  //  1
  string CAR_RD02_FRONT_CLOSED = "|\n";  //  2
  string CAR_RD03_FRONT_CLOSED = "|\n";  //  3
  string CAR_RD04_FRONT_CLOSED = "|"  ;  //  4

  string CAR_RD01_BACK_CLOSED = "|\n";  //  1
  string CAR_RD02_BACK_CLOSED = "|\n";  //  2
  string CAR_RD03_BACK_CLOSED = "|\n";  //  3
  string CAR_RD04_BACK_CLOSED = "|"  ;  //  4

  public:

  ALERTS_PANEL_GRID_PROPERTIES PROP;  

  void create();
  // Panel to be drawn.  
  //  Define PROP (properties) before calling this routine.
  //    Property Size and Position is necessary before calling create.

  void update(system_data &sdSysData, unsigned long &tmeCurrentMillis);
  // Update values of panel
  //  Gadget will be redrawn if values did changed or animations scheduled. 

  bool draw(bool Refresh, unsigned long tmeFrame_Time, ALERT_SYSTEM Alerts, PANEL Alerts_Panel);
  // Draw all changes to Panel.
  //  Set Refresh to true to force redraw.
  //  Animations require time reference.
  // Returns true if panel was redrawn.
};



#endif