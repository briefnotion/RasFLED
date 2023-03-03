// ***************************************************************************************
// *
// *    Core       | Everything within this document is proprietary to Core Dynamics.
// *    Dynamics   | Any unauthorized duplication will be subject to prosecution.
// *
// *    Department : (R+D)^2                        Name: helper_ncurses.h
// *       Sub Dept: Programming
// *    Location ID: 856-45B
// *                                                      (c) 2856 - 2858 Core Dynamics
// ***************************************************************************************

#ifndef HELPER_NCURSES_H
#define HELPER_NCURSES_H

// Standard Header Files
#include <ncurses.h>

using namespace std;

/*  
All possible color pairs are indexed in a simple 
  background color * 10 + forground color.
  
The color index values of a few of the colors are 
  rearanged to roll from red to green to white to allow 
  values to be indicated by color by scale. 

Order:
Mine    Color        Standard
    0  COLOR_BLACK   0
    1  COLOR_RED     1
    2  COLOR_YELLOW  3
    3  COLOR_GREEN   2
    4  COLOR_BLUE    4
    5  COLOR_MAGENTA 5
    6  COLOR_CYAN    6
    7  COLOR_WHITE   7
*/

short CRT_get_color(short Color);

int CRT_get_color_pair(short Background_Color, short Foreground_Color);

void CRT_init_all_pairs();

int text_color_correction(int Background_Color);
// Color correction to increase contrast between text background and foreground colors. 

void tmp_text_color_correction(int Background_Color, 
                  int &New_Temp_Background_Color, int &New_Temp_Text_Color);
// Color correction to increase contrast between text background and foreground colors. 

#endif