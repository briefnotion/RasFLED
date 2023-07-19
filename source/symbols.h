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


  // Car Lights Off
  //  1 :           
  //  2 :           ___

  string CAR_LIGHTS_OFF_01 = "\n"        ;  //  1
  string CAR_LIGHTS_OFF_02 = "     ___\n";  //  2

  // Car Lights On
	//  1 :			\     X     /	
	//  2 :      \   /_\   /

  string CAR_LIGHTS_ON_01 = "\\     X     /\n";  //  1
  string CAR_LIGHTS_ON_02 = " \\   /_\\   /"   ;  //  2


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

  // Car Lights Off
  string CAR_LIGHTS_OFF_BUILT = "";
  bool CAR_LIGHTS_OFF_MADE = false;

  // Car Lights On
  string CAR_LIGHTS_ON_BUILT = "";
  bool CAR_LIGHTS_ON_MADE = false;

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
  string car_lights_off();
  string car_lights_on();
  string car_door_left_front_closed();
  string car_door_right_front_closed();
  string car_door_left_back_closed();
  string car_door_right_back_closed();
  string car_door_left_open();
  string car_door_right_open();

};

// -------------------------------------------------------------------------------------

// Text to ASCII Art Generator. (Much better than what I can do on my own.)
//  https://www.patorjk.com/software/taag/#p=display&h=0&v=0&c=c&f=Small&t=ABCDEFG%0AHIJKLMN%0AOPQRSTU%0AVWXYZ

// Small
/***
 *        _     ___    ___   ___    ___   ___    ___    
 *       /_\   | _ )  / __| |   \  | __| | __|  / __|   
 *      / _ \  | _ \ | (__  | |) | | _|  | _|  | (_ |   
 *     /_/ \_\ |___/  \___| |___/  |___| |_|    \___|   
 *                                                      
 *      _  _   ___      _   _  __  _      __  __   _  _ 
 *     | || | |_ _|  _ | | | |/ / | |    |  \/  | | \| |
 *     | __ |  | |  | || | | ' <  | |__  | |\/| | | .` |
 *     |_||_| |___|  \__/  |_|\_\ |____| |_|  |_| |_|\_|
 *                                                      
 *       ___    ___    ___    ___   ___   _____   _   _ 
 *      / _ \  | _ \  / _ \  | _ \ / __| |_   _| | | | |
 *     | (_) | |  _/ | (_) | |   / \__ \   | |   | |_| |
 *      \___/  |_|    \__\_\ |_|_\ |___/   |_|    \___/ 
 *                                                      
 *     __   __ __      __ __  __ __   __  ____          
 *     \ \ / / \ \    / / \ \/ / \ \ / / |_  /          
 *      \ V /   \ \/\/ /   >  <   \ V /   / /           
 *       \_/     \_/\_/   /_/\_\   |_|   /___|          
 *                                                      
 */


/***
 *             _              _          __           
 *      __ _  | |__   __   __| |  ___   / _|  __ _    
 *     / _` | | '_ \ / _| / _` | / -_) |  _| / _` |   
 *     \__,_| |_.__/ \__| \__,_| \___| |_|   \__, |   
 *                                           |___/    
 *      _      _     _   _     _                      
 *     | |_   (_)   (_) | |__ | |  _ __    _ _    ___ 
 *     | ' \  | |   | | | / / | | | '  \  | ' \  / _ \
 *     |_||_| |_|  _/ | |_\_\ |_| |_|_|_| |_||_| \___/
 *                |__/                                
 *                               _                    
 *      _ __   __ _   _ _   ___ | |_   _  _  __ __    
 *     | '_ \ / _` | | '_| (_-< |  _| | || | \ V /    
 *     | .__/ \__, | |_|   /__/  \__|  \_,_|  \_/     
 *     |_|       |_|                                  
 *                                                    
 *     __ __ __ __ __  _  _   ___                     
 *     \ V  V / \ \ / | || | |_ /                     
 *      \_/\_/  /_\_\  \_, | /__|                     
 *                     |__/                           
 */

//  https://www.patorjk.com/software/taag/#p=display&h=0&v=0&c=c&f=Small&t=!%40%23%24%25%5E%26*()%0A-%3D_%2B%5B%5D%7B%7D%0A%3B'%3A%22%2C.%2F%3C%3E%3F%0A%5C%7C%60~
/***
 *      _    ____      _ _          _  __   /\   __             __ __  
 *     | |  / __ \   _| | |_   ||_ (_)/ /  |/\| / _|___  _/\_  / / \ \ 
 *     |_| / / _` | |_  .  _| (_-<   / /_       > _|_ _| >  < | |   | |
 *     (_) \ \__,_| |_     _| / _/  /_/(_)      \_____|   \/  | |   | |
 *          \____/    |_|_|    ||                              \_\ /_/ 
 *                          _     __   __     __ __                    
 *      ___   ___         _| |_  | _| |_ |   / / \ \                   
 *     |___| |___|       |_   _| | |   | | _| |   | |_                 
 *           |___|  ___    |_|   | |   | |  | |   | |                  
 *                 |___|         |__| |__|   \_\ /_/                   
 *      _   _   _   _ _             __   __ __    ___                  
 *     (_) ( ) (_) ( | )           / /  / / \ \  |__ \                 
 *      _  |/   _   V V   _   _   / /  < <   > >   /_/                 
 *     ( )     (_)       ( ) (_) /_/    \_\ /_/   (_)                  
 *     |/                |/                                            
 *     __     _   _   /\/|                                             
 *     \ \   | | ( ) |/\/                                              
 *      \ \  | |  \|                                                   
 *       \_\ | |                                                       
 *           |_|                                                       
 */

// https://www.patorjk.com/software/taag/#p=display&h=0&v=0&c=c&f=Small&t=1234%0A5678%0A90.0
/***
 *      _   ___   ____  _ _    
 *     / | |_  ) |__ / | | |   
 *     | |  / /   |_ \ |_  _|  
 *     |_| /___| |___/   |_|   
 *                             
 *      ___    __   ____   ___ 
 *     | __|  / /  |__  | ( _ )
 *     |__ \ / _ \   / /  / _ \
 *     |___/ \___/  /_/   \___/
 *                             
 *      ___    __         __   
 *     / _ \  /  \       /  \  
 *     \_, / | () |  _  | () | 
 *      /_/   \__/  (_)  \__/  
 *                             
 */


// Notable: Mini, Straight, Goofy, Bigfig

class SYMBOLS_6X5_CHARACTER_SMALL
{
  private:

  string SPACE_01 = "      \n";
  string SPACE_02 = "      \n";
  string SPACE_03 = "      \n";
  string SPACE_04 = "      \n";
  string SPACE_05 = "      ";

  string A_01 = "__  __\n";
  string A_02 = "\\ \\/ /\n";
  string A_03 = " >  < \n";
  string A_04 = "/_/\\_\\\n";
  string A_05 = "      ";

  string B_01 = "__  __\n";
  string B_02 = "\\ \\/ /\n";
  string B_03 = " >  < \n";
  string B_04 = "/_/\\_\\\n";
  string B_05 = "      ";

  string C_01 = "__  __\n";
  string C_02 = "\\ \\/ /\n";
  string C_03 = " >  < \n";
  string C_04 = "/_/\\_\\\n";
  string C_05 = "      ";

  string D_01 = " ___  \n";
  string D_02 = "|   \\ \n";
  string D_03 = "| |) |\n";
  string D_04 = "|___/ \n";
  string D_05 = "      ";

  string E_01 = "__  __\n";
  string E_02 = "\\ \\/ /\n";
  string E_03 = " >  < \n";
  string E_04 = "/_/\\_\\\n";
  string E_05 = "      ";

  string F_01 = "__  __\n";
  string F_02 = "\\ \\/ /\n";
  string F_03 = " >  < \n";
  string F_04 = "/_/\\_\\\n";
  string F_05 = "      ";

  string G_01 = "__  __\n";
  string G_02 = "\\ \\/ /\n";
  string G_03 = " >  < \n";
  string G_04 = "/_/\\_\\\n";
  string G_05 = "      ";

  string H_01 = "__  __\n";
  string H_02 = "\\ \\/ /\n";
  string H_03 = " >  < \n";
  string H_04 = "/_/\\_\\\n";
  string H_05 = "      ";

  string I_01 = "__  __\n";
  string I_02 = "\\ \\/ /\n";
  string I_03 = " >  < \n";
  string I_04 = "/_/\\_\\\n";
  string I_05 = "      ";

  string J_01 = "__  __\n";
  string J_02 = "\\ \\/ /\n";
  string J_03 = " >  < \n";
  string J_04 = "/_/\\_\\\n";
  string J_05 = "      ";

  string K_01 = "__  __\n";
  string K_02 = "\\ \\/ /\n";
  string K_03 = " >  < \n";
  string K_04 = "/_/\\_\\\n";
  string K_05 = "      ";

  string L_01 = " _    \n";
  string L_02 = "| |   \n";
  string L_03 = "| |__ \n";
  string L_04 = "|____|\n";
  string L_05 = "      ";

  string M_01 = " __  __ \n";
  string M_02 = "|  \\/  |\n";
  string M_03 = "| |\\/| |\n";
  string M_04 = "|_|  |_|\n";
  string M_05 = "        ";

  string N_01 = "__  __\n";
  string N_02 = "| \\| |\n";
  string N_03 = "| .` |\n";
  string N_04 = "|_|\\_|\n";
  string N_05 = "      ";

  string O_01 = "__  __\n";
  string O_02 = "\\ \\/ /\n";
  string O_03 = " >  < \n";
  string O_04 = "/_/\\_\\\n";
  string O_05 = "      ";

  string P_01 = " ___  \n";
  string P_02 = "| _ \\ \n";
  string P_03 = "|  _/ \n";
  string P_04 = "|_|   \n";
  string P_05 = "      ";

  string Q_01 = "__  __\n";
  string Q_02 = "\\ \\/ /\n";
  string Q_03 = " >  < \n";
  string Q_04 = "/_/\\_\\\n";
  string Q_05 = "      ";

  string R_01 = " ___  \n";
  string R_02 = "| _ \\ \n";
  string R_03 = "|   / \n";
  string R_04 = "|_|_\\ \n";
  string R_05 = "      ";

  string S_01 = "__  __\n";
  string S_02 = "\\ \\/ /\n";
  string S_03 = " >  < \n";
  string S_04 = "/_/\\_\\\n";
  string S_05 = "      ";

  string T_01 = "__  __\n";
  string T_02 = "\\ \\/ /\n";
  string T_03 = " >  < \n";
  string T_04 = "/_/\\_\\\n";
  string T_05 = "      ";

  string U_01 = "__  __\n";
  string U_02 = "\\ \\/ /\n";
  string U_03 = " >  < \n";
  string U_04 = "/_/\\_\\\n";
  string U_05 = "      ";

  string V_01 = "__  __\n";
  string V_02 = "\\ \\/ /\n";
  string V_03 = " >  < \n";
  string V_04 = "/_/\\_\\\n";
  string V_05 = "      ";

  string W_01 = "__  __\n";
  string W_02 = "\\ \\/ /\n";
  string W_03 = " >  < \n";
  string W_04 = "/_/\\_\\\n";
  string W_05 = "      ";

  string X_01 = "__  __\n";
  string X_02 = "\\ \\/ /\n";
  string X_03 = " >  < \n";
  string X_04 = "/_/\\_\\\n";
  string X_05 = "      ";

  string Y_01 = "__  __\n";
  string Y_02 = "\\ \\/ /\n";
  string Y_03 = " >  < \n";
  string Y_04 = "/_/\\_\\\n";
  string Y_05 = "      ";

  string Z_01 = "__  __\n";
  string Z_02 = "\\ \\/ /\n";
  string Z_03 = " >  < \n";
  string Z_04 = "/_/\\_\\\n";
  string Z_05 = "      ";

  string N_0_01 = "  __  \n";
  string N_0_02 = " /  \\ \n";
  string N_0_03 = "| () |\n";
  string N_0_04 = " \\__/ \n";
  string N_0_05 = "      ";

  string N_1_01 = "  _   \n";
  string N_1_02 = " / |  \n";
  string N_1_03 = " | |  \n";
  string N_1_04 = " |_|  \n";
  string N_1_05 = "      ";

  string N_2_01 = " ___  \n";
  string N_2_02 = "|_  ) \n";
  string N_2_03 = " / /  \n";
  string N_2_04 = "/___| \n";
  string N_2_05 = "      ";

  string N_3_01 = " ____ \n";
  string N_3_02 = "|__ / \n";
  string N_3_03 = " |_ \\ \n";
  string N_3_04 = "|___/ \n";
  string N_3_05 = "      \n";
  
  string N_4_01 = " _ _  \n";
  string N_4_02 = "| | | \n";
  string N_4_03 = "|_  | \n";
  string N_4_04 = "  |_| \n";
  string N_4_05 = "      ";

  string N_5_01 = " ___  \n";
  string N_5_02 = "| __| \n";
  string N_5_03 = "|__ \\ \n";
  string N_5_04 = "|___/ \n";
  string N_5_05 = "      ";

  string N_6_01 = "  __  \n";
  string N_6_02 = " / /  \n";
  string N_6_03 = "/ _ \\ \n";
  string N_6_04 = "\\___/ \n";
  string N_6_05 = "      ";

  string N_7_01 = " ____ \n";
  string N_7_02 = "|__  |\n";
  string N_7_03 = "  / / \n";
  string N_7_04 = " /_/  \n";
  string N_7_05 = "      ";

  string N_8_01 = " ___  \n";
  string N_8_02 = "( _ ) \n";
  string N_8_03 = "/ _ \\ \n";
  string N_8_04 = "\\___/ \n";
  string N_8_05 = "      ";

  string N_9_01 = " ___  \n";
  string N_9_02 = "/ _ \\ \n";
  string N_9_03 = "\\_, / \n";
  string N_9_04 = " /_/  \n";
  string N_9_05 = "      ";

  string N_0_01_d = "  __  \n";
  string N_0_02_d = " /  \\ \n";
  string N_0_03_d = "| () |\n";
  string N_0_04_d = " \\__/o\n";
  string N_0_05_d = "      ";

  string N_1_01_d = "  _   \n";
  string N_1_02_d = " / |  \n";
  string N_1_03_d = " | |  \n";
  string N_1_04_d = " |_| o\n";
  string N_1_05_d = "      ";

  string N_2_01_d = " ___  \n";
  string N_2_02_d = "|_  ) \n";
  string N_2_03_d = " / /  \n";
  string N_2_04_d = "/___|o\n";
  string N_2_05_d = "      ";

  string N_3_01_d = " ____ \n";
  string N_3_02_d = "|__ / \n";
  string N_3_03_d = " |_ \\ \n";
  string N_3_04_d = "|___/o\n";
  string N_3_05_d = "      ";
  
  string N_4_01_d = " _ _  \n";
  string N_4_02_d = "| | | \n";
  string N_4_03_d = "|_  | \n";
  string N_4_04_d = "  |_|o\n";
  string N_4_05_d = "      ";

  string N_5_01_d = " ___  \n";
  string N_5_02_d = "| __| \n";
  string N_5_03_d = "|__ \\ \n";
  string N_5_04_d = "|___/o\n";
  string N_5_05_d = "      ";

  string N_6_01_d = "  __  \n";
  string N_6_02_d = " / /  \n";
  string N_6_03_d = "/ _ \\ \n";
  string N_6_04_d = "\\___/o\n";
  string N_6_05_d = "      ";

  string N_7_01_d = " ____ \n";
  string N_7_02_d = "|__  |\n";
  string N_7_03_d = "  / / \n";
  string N_7_04_d = " /_/ o\n";
  string N_7_05_d = "      ";

  string N_8_01_d = " ___  \n";
  string N_8_02_d = "( _ ) \n";
  string N_8_03_d = "/ _ \\ \n";
  string N_8_04_d = "\\___/o\n";
  string N_8_05_d = "      ";

  string N_9_01_d = " ___  \n";
  string N_9_02_d = "/ _ \\ \n";
  string N_9_03_d = "\\_, / \n";
  string N_9_04_d = " /_/ o\n";
  string N_9_05_d = "      ";

  string SPACE = "";
  string CHAR_A = "";
  string CHAR_B = "";
  string CHAR_C = "";
  string CHAR_D = "";
  string CHAR_E = "";
  string CHAR_F = "";
  string CHAR_G = "";
  string CHAR_H = "";
  string CHAR_I = "";
  string CHAR_J = "";
  string CHAR_K = "";
  string CHAR_L = "";
  string CHAR_M = "";
  string CHAR_N = "";
  string CHAR_O = "";
  string CHAR_P = "";
  string CHAR_Q = "";
  string CHAR_R = "";
  string CHAR_S = "";
  string CHAR_T = "";
  string CHAR_U = "";
  string CHAR_V = "";
  string CHAR_W = "";
  string CHAR_X = "";
  string CHAR_Y = "";
  string CHAR_Z = "";
  string CHAR_0 = "";
  string CHAR_1 = "";
  string CHAR_2 = "";
  string CHAR_3 = "";
  string CHAR_4 = "";
  string CHAR_5 = "";
  string CHAR_6 = "";
  string CHAR_7 = "";
  string CHAR_8 = "";
  string CHAR_9 = "";
  string CHAR_0_d = "";
  string CHAR_1_d = "";
  string CHAR_2_d = "";
  string CHAR_3_d = "";
  string CHAR_4_d = "";
  string CHAR_5_d = "";
  string CHAR_6_d = "";
  string CHAR_7_d = "";
  string CHAR_8_d = "";
  string CHAR_9_d = "";

  bool SPACE_MADE = false;
  bool CHAR_A_MADE = false;
  bool CHAR_B_MADE = false;
  bool CHAR_C_MADE = false;
  bool CHAR_D_MADE = false;
  bool CHAR_E_MADE = false;
  bool CHAR_F_MADE = false;
  bool CHAR_G_MADE = false;
  bool CHAR_H_MADE = false;
  bool CHAR_I_MADE = false;
  bool CHAR_J_MADE = false;
  bool CHAR_K_MADE = false;
  bool CHAR_L_MADE = false;
  bool CHAR_M_MADE = false;
  bool CHAR_N_MADE = false;
  bool CHAR_O_MADE = false;
  bool CHAR_P_MADE = false;
  bool CHAR_Q_MADE = false;
  bool CHAR_R_MADE = false;
  bool CHAR_S_MADE = false;
  bool CHAR_T_MADE = false;
  bool CHAR_U_MADE = false;
  bool CHAR_V_MADE = false;
  bool CHAR_W_MADE = false;
  bool CHAR_X_MADE = false;
  bool CHAR_Y_MADE = false;
  bool CHAR_Z_MADE = false;
  bool CHAR_0_MADE = false;
  bool CHAR_1_MADE = false;
  bool CHAR_2_MADE = false;
  bool CHAR_3_MADE = false;
  bool CHAR_4_MADE = false;
  bool CHAR_5_MADE = false;
  bool CHAR_6_MADE = false;
  bool CHAR_7_MADE = false;
  bool CHAR_8_MADE = false;
  bool CHAR_9_MADE = false;
  bool CHAR_0_d_MADE = false;
  bool CHAR_1_d_MADE = false;
  bool CHAR_2_d_MADE = false;
  bool CHAR_3_d_MADE = false;
  bool CHAR_4_d_MADE = false;
  bool CHAR_5_d_MADE = false;
  bool CHAR_6_d_MADE = false;
  bool CHAR_7_d_MADE = false;
  bool CHAR_8_d_MADE = false;
  bool CHAR_9_d_MADE = false;

  public:
  string space();
  string char_A();
  string char_B();
  string char_C();
  string char_D();
  string char_E();
  string char_F();
  string char_G();
  string char_H();
  string char_I();
  string char_J();
  string char_K();
  string char_L();
  string char_M();
  string char_N();
  string char_O();
  string char_P();
  string char_Q();
  string char_R();
  string char_S();
  string char_T();
  string char_U();
  string char_V();
  string char_W();
  string char_X();
  string char_Y();
  string char_Z();
  string char_0();
  string char_1();
  string char_2();
  string char_3();
  string char_4();
  string char_5();
  string char_6();
  string char_7();
  string char_8();
  string char_9();
  string char_0_d();
  string char_1_d();
  string char_2_d();
  string char_3_d();
  string char_4_d();
  string char_5_d();
  string char_6_d();
  string char_7_d();
  string char_8_d();
  string char_9_d();

  string character(char Character);
  string number(int Number);
  string number(int Number, bool Decimal);
};

// -------------------------------------------------------------------------------------

#endif