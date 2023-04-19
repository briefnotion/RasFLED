// ***************************************************************************************
// *
// *    Core       | Everything within this document is proprietary to Core Dynamics.
// *    Dynamics   | Any unauthorized duplication will be subject to prosecution.
// *
// *    Department : (R+D)^2                        Name: symbols.h
// *       Sub Dept: Programming
// *    Location ID: 856-45B
// *                                                      (c) 2856 - 2858 Core Dynamics
// ***************************************************************************************

#ifndef SYMBOLS_H
#define SYMBOLS_H

// Standard Header Files
#include <stdio.h>
#include <string>

using namespace std;

// -------------------------------------------------------------------------------------

class AUTOMOTIVE_SYMBOLS
{
  private:

  // Images

  // Car Doors Closed
  //  1 :          ___
  //  2 :       -==   ==-
	//  3 :      /         \
  //  4 :     |   .   .   |
	//  5 :     | -=======- |
	//  6 :     |\=========/|
	//  7 :    /|\=========/|\
	//  8 :     ||-       -||
	//  9 :     ||         ||
	// 10 :     ||         ||
  // 11 :     |=         =|
	// 12 :     ||         ||
	// 13 :     ||    :    ||
	// 14 :     ||         ||
	// 15 :     |/  _____  \|
	// 16 :     || /#####\ ||
	// 17 :      \/#######\/
	// 18 :        =======

  string CAR01 = "      ___\n"        ;  //  1
  string CAR02 = "   -==   ==-\n"     ;  //  2
  string CAR03 = "  /         \\\n"   ;  //  3
  string CAR04 = " |   .   .   |\n"   ;  //  3 
  string CAR05 = " | -=======- |\n"   ;  //  4
  string CAR06 = " |\\=========/|\n"  ;  //  5
  string CAR07 = "/|\\=========/|\\\n";  //  6
  string CAR08 = " ||-       -||\n"   ;  //  7
  string CAR09 = " ||         ||\n"   ;  //  8
  string CAR10 = " ||         ||\n"   ;  //  9
  string CAR11 = " |=         =|\n"   ;  // 10
  string CAR12 = " ||         ||\n"   ;  // 10
  string CAR13 = " ||    _    ||\n"   ;  // 11
  string CAR14 = " ||    v    ||\n"   ;  // 12
  string CAR15 = " |/  _____  \\|\n"  ;  // 13
  string CAR16 = " || /#####\\ ||\n"   ;  // 14
  string CAR17 = "  \\/#######\\/\n" ;  // 15
  string CAR18 = "    ======="      ;  // 16
                

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

  // Car Body
  string CAR_BODY_BUILT = "";
  bool CAR_BODY_MADE = false;

  // Car Left Front Closed
  string CAR_LEFT_FRONT_CLOSED_BUILT = "";
  bool CAR_LEFT_FRONT_CLOSED_MADE = false;

  // Car Right Front Closed
  string CAR_RIGHT_FRONT_CLOSED_BUILT = "";
  bool CAR_RIGHT_FRONT_CLOSED_MADE = false;

  // Car Left Back Closed
  string CAR_LEFT_BACK_CLOSED_BUILT = "";
  bool CAR_LEFT_BACK_CLOSED_MADE = false;

  // Car Right Back Closed
  string CAR_RIGHT_BACK_CLOSED_BUILT = "";
  bool CAR_RIGHT_BACK_CLOSED_MADE = false;

  // Car Left Open
  string CAR_LEFT_OPEN_BUILT = "";
  bool CAR_LEFT_OPEN_MADE = false;

  // Car Right Open
  string CAR_RIGHT_OPEN_BUILT = "";
  bool CAR_RIGHT_OPEN_MADE = false;

  public:

  string car_body();
  string car_door_left_front_closed();
  string car_door_right_front_closed();
  string car_door_left_back_closed();
  string car_door_right_back_closed();
  string car_door_left_open();
  string car_door_right_open();

};

// -------------------------------------------------------------------------------------

/*
class SYMBOLS_5X5_BLANK
{
  private:

  string X_01 = "\n";
  string X_02 = "\n";
  string X_03 = "\n";
  string X_04 = "\n";
  string X_05 = "\n";

  string N_0_01 = "\n";
  string N_0_02 = "\n";
  string N_0_03 = "\n";
  string N_0_04 = "\n";
  string N_0_05 = "\n";

  string N_1_01 = "\n";
  string N_1_02 = "\n";
  string N_1_03 = "\n";
  string N_1_04 = "\n";
  string N_1_05 = "\n";

  string N_2_01 = "\n";
  string N_2_02 = "\n";
  string N_2_03 = "\n";
  string N_2_04 = "\n";
  string N_2_05 = "\n";

  string N_3_01 = "\n";
  string N_3_02 = "\n";
  string N_3_03 = "\n";
  string N_3_04 = "\n";
  string N_3_05 = "\n";
  
  string N_4_01 = "\n";
  string N_4_02 = "\n";
  string N_4_03 = "\n";
  string N_4_04 = "\n";
  string N_4_05 = "\n";

  string N_5_01 = "\n";
  string N_5_02 = "\n";
  string N_5_03 = "\n";
  string N_5_04 = "\n";
  string N_5_05 = "\n";

  string N_6_01 = "\n";
  string N_6_02 = "\n";
  string N_6_03 = "\n";
  string N_6_04 = "\n";
  string N_6_05 = "\n";

  string N_7_01 = "\n";
  string N_7_02 = "\n";
  string N_7_03 = "\n";
  string N_7_04 = "\n";
  string N_7_05 = "\n";

  string N_8_01 = "\n";
  string N_8_02 = "\n";
  string N_8_03 = "\n";
  string N_8_04 = "\n";
  string N_8_05 = "\n";

  string N_9_01 = "\n";
  string N_9_02 = "\n";
  string N_9_03 = "\n";
  string N_9_04 = "\n";
  string N_9_05 = "\n";

  string NUM_X = "";
  string NUM_0 = "";
  string NUM_1 = "";
  string NUM_2 = "";
  string NUM_3 = "";
  string NUM_4 = "";
  string NUM_5 = "";
  string NUM_6 = "";
  string NUM_7 = "";
  string NUM_8 = "";
  string NUM_9 = "";

  bool NUM_X_MADE = false;
  bool NUM_0_MADE = false;
  bool NUM_1_MADE = false;
  bool NUM_2_MADE = false;
  bool NUM_3_MADE = false;
  bool NUM_4_MADE = false;
  bool NUM_5_MADE = false;
  bool NUM_6_MADE = false;
  bool NUM_7_MADE = false;
  bool NUM_8_MADE = false;
  bool NUM_9_MADE = false;

  public:

  string num_x();
  string num_0();
  string num_1();
  string num_2();
  string num_3();
  string num_4();
  string num_5();
  string num_6();
  string num_7();
  string num_8();
  string num_9();

  string number(int Number);
};
*/

// -------------------------------------------------------------------------------------

class SYMBOLS_5X5_NUMBERS
{
  private:

  string X_01 = "#   #\n";
  string X_02 = " # #\n";
  string X_03 = "  #\n";
  string X_04 = " # #\n";
  string X_05 = "#   #\n";

  string N_0_01 = "  ## \n";
  string N_0_02 = " #  #\n";
  string N_0_03 = " #  #\n";
  string N_0_04 = " #  #\n";
  string N_0_05 = "  ## \n";

  string N_1_01 = "   # \n";
  string N_1_02 = "  ## \n";
  string N_1_03 = "   # \n";
  string N_1_04 = "   # \n";
  string N_1_05 = "   # \n";

  string N_2_01 = " ### \n";
  string N_2_02 = "    #\n";
  string N_2_03 = "  ## \n";
  string N_2_04 = " #   \n";
  string N_2_05 = "  ###\n";

  string N_3_01 = " ### \n";
  string N_3_02 = "    #\n";
  string N_3_03 = " ### \n";
  string N_3_04 = "    #\n";
  string N_3_05 = " ### \n";
  
  string N_4_01 = " #  #\n";
  string N_4_02 = " #  #\n";
  string N_4_03 = " ####\n";
  string N_4_04 = "    #\n";
  string N_4_05 = "    #\n";

  string N_5_01 = " ####\n";
  string N_5_02 = " #   \n";
  string N_5_03 = " ### \n";
  string N_5_04 = "    #\n";
  string N_5_05 = " ### \n";

  string N_6_01 = "  ## \n";
  string N_6_02 = " #   \n";
  string N_6_03 = " ### \n";
  string N_6_04 = " #  #\n";
  string N_6_05 = "  ## \n";

  string N_7_01 = " ####\n";
  string N_7_02 = "    #\n";
  string N_7_03 = "   # \n";
  string N_7_04 = "   # \n";
  string N_7_05 = "   # \n";

  string N_8_01 = "  ## \n";
  string N_8_02 = " #  #\n";
  string N_8_03 = "  ## \n";
  string N_8_04 = " #  #\n";
  string N_8_05 = "  ## \n";

  string N_9_01 = "  ## \n";
  string N_9_02 = " #  #\n";
  string N_9_03 = "  ###\n";
  string N_9_04 = "    #\n";
  string N_9_05 = "  ## \n";

  string NUM_X = "";
  string NUM_0 = "";
  string NUM_1 = "";
  string NUM_2 = "";
  string NUM_3 = "";
  string NUM_4 = "";
  string NUM_5 = "";
  string NUM_6 = "";
  string NUM_7 = "";
  string NUM_8 = "";
  string NUM_9 = "";

  bool NUM_X_MADE = false;
  bool NUM_0_MADE = false;
  bool NUM_1_MADE = false;
  bool NUM_2_MADE = false;
  bool NUM_3_MADE = false;
  bool NUM_4_MADE = false;
  bool NUM_5_MADE = false;
  bool NUM_6_MADE = false;
  bool NUM_7_MADE = false;
  bool NUM_8_MADE = false;
  bool NUM_9_MADE = false;

  public:

  string num_x();
  string num_0();
  string num_1();
  string num_2();
  string num_3();
  string num_4();
  string num_5();
  string num_6();
  string num_7();
  string num_8();
  string num_9();

  string number(int Number);
};

// -------------------------------------------------------------------------------------

// Text to ASCII Art Generator. (Much better than what I can do on my own.)
//  http://www.patorjk.com/software/taag/#p=display&h=0&v=0&c=c&f=Small&t=12345678910

// Small
/***
 *      _   ___   ____  _ _    ___    __   ____   ___   ___   _    __  
 *     / | |_  ) |__ / | | |  | __|  / /  |__  | ( _ ) / _ \ / |  /  \ 
 *     | |  / /   |_ \ |_  _| |__ \ / _ \   / /  / _ \ \_, / | | | () |
 *     |_| /___| |___/   |_|  |___/ \___/  /_/   \___/  /_/  |_|  \__/ 
 *                                                                     
 */
// Notable: Mini, Straight, Goofy, Bigfig

class SYMBOLS_6X5_SMALL
{
  private:

  string X_01 = "__  __\n";
  string X_02 = "\\ \\/ /\n";
  string X_03 = " >  < \n";
  string X_04 = "/_/\\_\\\n";
  string X_05 = "      \n";

  string N_0_01 = "  __  \n";
  string N_0_02 = " /  \\ \n";
  string N_0_03 = "| () |\n";
  string N_0_04 = " \\__/ \n";
  string N_0_05 = "      \n";

  string N_1_01 = "  _   \n";
  string N_1_02 = " / |  \n";
  string N_1_03 = " | |  \n";
  string N_1_04 = " |_|  \n";
  string N_1_05 = "      \n";

  string N_2_01 = " ___  \n";
  string N_2_02 = "|_  ) \n";
  string N_2_03 = " / /  \n";
  string N_2_04 = "/___| \n";
  string N_2_05 = "      \n";

  string N_3_01 = " ____ \n";
  string N_3_02 = "|__ / \n";
  string N_3_03 = " |_ \\ \n";
  string N_3_04 = "|___/ \n";
  string N_3_05 = "      \n";
  
  string N_4_01 = " _ _  \n";
  string N_4_02 = "| | | \n";
  string N_4_03 = "|_  | \n";
  string N_4_04 = "  |_| \n";
  string N_4_05 = "      \n";

  string N_5_01 = " ___  \n";
  string N_5_02 = "| __| \n";
  string N_5_03 = "|__ \\ \n";
  string N_5_04 = "|___/ \n";
  string N_5_05 = "      \n";

  string N_6_01 = "  __  \n";
  string N_6_02 = " / /  \n";
  string N_6_03 = "/ _ \\ \n";
  string N_6_04 = "\\___/ \n";
  string N_6_05 = "      \n";

  string N_7_01 = " ____ \n";
  string N_7_02 = "|__  |\n";
  string N_7_03 = "  / / \n";
  string N_7_04 = " /_/  \n";
  string N_7_05 = "      \n";

  string N_8_01 = " ___  \n";
  string N_8_02 = "( _ ) \n";
  string N_8_03 = "/ _ \\ \n";
  string N_8_04 = "\\___/ \n";
  string N_8_05 = "      \n";

  string N_9_01 = " ___  \n";
  string N_9_02 = "/ _ \\ \n";
  string N_9_03 = "\\_, / \n";
  string N_9_04 = " /_/  \n";
  string N_9_05 = "      \n";

  string NUM_X = "";
  string NUM_0 = "";
  string NUM_1 = "";
  string NUM_2 = "";
  string NUM_3 = "";
  string NUM_4 = "";
  string NUM_5 = "";
  string NUM_6 = "";
  string NUM_7 = "";
  string NUM_8 = "";
  string NUM_9 = "";

  bool NUM_X_MADE = false;
  bool NUM_0_MADE = false;
  bool NUM_1_MADE = false;
  bool NUM_2_MADE = false;
  bool NUM_3_MADE = false;
  bool NUM_4_MADE = false;
  bool NUM_5_MADE = false;
  bool NUM_6_MADE = false;
  bool NUM_7_MADE = false;
  bool NUM_8_MADE = false;
  bool NUM_9_MADE = false;

  public:

  string num_x();
  string num_0();
  string num_1();
  string num_2();
  string num_3();
  string num_4();
  string num_5();
  string num_6();
  string num_7();
  string num_8();
  string num_9();

  string number(int Number);
};

// -------------------------------------------------------------------------------------

class SYMBOLS_3X3_NUMBERS
{
  private:

  string X_01 = "# #\n";
  string X_02 = " # \n";
  string X_03 = "# #\n";

  string NUM_X = "";

  bool NUM_X_MADE = false;

  public:

  string num_x();
};

// -------------------------------------------------------------------------------------

#endif