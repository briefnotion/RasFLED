// ***************************************************************************************
// *
// *    Core       | Everything within this document is proprietary to Core Dynamics.
// *    Dynamics   | Any unauthorized duplication will be subject to prosecution.
// *
// *    Department : (R+D)^2                        Name: helper_ncurses.cpp
// *       Sub Dept: Programming
// *    Location ID: 856-45B
// *                                                      (c) 2856 - 2858 Core Dynamics
// ***************************************************************************************

#ifndef HELPER_NCURSES_CPP
#define HELPER_NCURSES_CPP

#include "helper_ncurses.h"

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

short CRT_get_color(short Color)
// Retrieve the Color ID associated in the color pair index.
//  Not the standard color codes, but simple enough to calculate 
//  even without this function. 
{
  if (Color == COLOR_YELLOW)
  {
    return 2;
  }
  else if (Color == COLOR_GREEN)
  {
    return 3;
  }
  else
  {
    return Color;
  }
}

int CRT_get_color_pair(short Background_Color, short Foreground_Color)
// Called to retrieve the the color pair ID. 
{
  short back = CRT_get_color(Background_Color);
  short fore = CRT_get_color(Foreground_Color);

  if (back == fore)
  {
    return 0;
  }
  else
  {
    return back*10 + fore;
  }
  //return 47;
}

void CRT_init_all_pairs()
// Pair all color combinations.
// Should only be needed to call once, at startup of any screen 
//  activities.
{
  for(short b = 0; b < 8; b++)
  {
    for(short f = 0; f < 8; f++)
    {
      if (b != f)
      {
        init_pair( (b*10)+f , CRT_get_color(f), CRT_get_color(b));
      }
    }
  }
}

int text_color_correction(int Background_Color)
{
  if (Background_Color == COLOR_BLUE || Background_Color == COLOR_RED || Background_Color == COLOR_MAGENTA)
  {
    return COLOR_WHITE;
  }
  else
  {
    return COLOR_BLACK;
  }
}

void tmp_text_color_correction(int Background_Color, 
                  int &New_Temp_Background_Color, int &New_Temp_Text_Color)
{
  New_Temp_Background_Color = Background_Color;
  New_Temp_Text_Color = text_color_correction(New_Temp_Background_Color);
}



#endif