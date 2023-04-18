// ***************************************************************************************
// *
// *    Core       | Everything within this document is proprietary to Core Dynamics.
// *    Dynamics   | Any unauthorized duplication will be subject to prosecution.
// *
// *    Department : (R+D)^2                        Name: symbols.cpp
// *       Sub Dept: Programming
// *    Location ID: 856-45B
// *                                                      (c) 2856 - 2858 Core Dynamics
// ***************************************************************************************

#ifndef SYMBOLS_CPP
#define SYMBOLS_CPP

#include "symbols.h"

using namespace std;

// -------------------------------------------------------------------------------------

string AUTOMOTIVE_SYMBOLS::car_body()
{
  if (CAR_BODY_MADE == false)
  {
    CAR_BODY_BUILT = CAR01 + CAR02 + CAR03 + CAR04 + CAR05 + CAR06 + CAR07 + CAR08 + CAR09 + 
                      CAR10 + CAR11 + CAR12 + CAR13 + CAR14 + CAR15 + CAR16 + CAR17 + CAR18 ;
    CAR_BODY_MADE = true;
  }

  return CAR_BODY_BUILT;
}

string AUTOMOTIVE_SYMBOLS::car_door_left_front_closed()
{
  if (CAR_LEFT_FRONT_CLOSED_MADE == false)
  {
    CAR_LEFT_FRONT_CLOSED_BUILT = CAR_LD01_FRONT_CLOSED + CAR_LD02_FRONT_CLOSED + CAR_LD03_FRONT_CLOSED + CAR_LD04_FRONT_CLOSED;
    CAR_LEFT_FRONT_CLOSED_MADE = true;
  }

  return CAR_LEFT_FRONT_CLOSED_BUILT;
}

string AUTOMOTIVE_SYMBOLS::car_door_right_front_closed()
{
  if (CAR_RIGHT_FRONT_CLOSED_MADE == false)
  {
    CAR_RIGHT_FRONT_CLOSED_BUILT = CAR_RD01_FRONT_CLOSED + CAR_RD02_FRONT_CLOSED + CAR_RD03_FRONT_CLOSED + CAR_RD04_FRONT_CLOSED;
    CAR_RIGHT_FRONT_CLOSED_MADE = true;
  }

  return CAR_RIGHT_FRONT_CLOSED_BUILT;
}

string AUTOMOTIVE_SYMBOLS::car_door_left_back_closed()
{
  if (CAR_LEFT_BACK_CLOSED_MADE == false)
  {
    CAR_LEFT_BACK_CLOSED_BUILT = CAR_LD01_BACK_CLOSED + CAR_LD02_BACK_CLOSED + CAR_LD03_BACK_CLOSED + CAR_LD04_BACK_CLOSED;
    CAR_LEFT_BACK_CLOSED_MADE = true;
  }

  return CAR_LEFT_BACK_CLOSED_BUILT;
}

string AUTOMOTIVE_SYMBOLS::car_door_right_back_closed()
{
  if (CAR_RIGHT_BACK_CLOSED_MADE == false)
  {
    CAR_RIGHT_BACK_CLOSED_BUILT = CAR_RD01_BACK_CLOSED + CAR_RD02_BACK_CLOSED + CAR_RD03_BACK_CLOSED + CAR_RD04_BACK_CLOSED;
    CAR_RIGHT_BACK_CLOSED_MADE = true;
  }

  return CAR_RIGHT_BACK_CLOSED_BUILT;
}

string AUTOMOTIVE_SYMBOLS::car_door_left_open()
{
  if (CAR_LEFT_OPEN_MADE == false)
  {
    CAR_LEFT_OPEN_BUILT = CAR_LD01_OPEN + CAR_LD02_OPEN + CAR_LD03_OPEN + CAR_LD04_OPEN;
    CAR_LEFT_OPEN_MADE = true;
  }

  return CAR_LEFT_OPEN_BUILT;
}

string AUTOMOTIVE_SYMBOLS::car_door_right_open()
{
  if (CAR_RIGHT_OPEN_MADE == false)
  {
    CAR_RIGHT_OPEN_BUILT = CAR_RD01_OPEN + CAR_RD02_OPEN + CAR_RD03_OPEN + CAR_RD04_OPEN;
    CAR_RIGHT_OPEN_MADE = true;
  }

  return CAR_RIGHT_OPEN_BUILT;
}

// -------------------------------------------------------------------------------------

string SYMBOLS_5X5_NUMBERS::num_x()
{
  if (NUM_X_MADE == false)
  {
    NUM_X = X_01 + X_02 + X_03 + X_04 + X_05;
    NUM_X_MADE = true;
  }

  return NUM_X;
}

string SYMBOLS_5X5_NUMBERS::num_0()
{
  if (NUM_0_MADE == false)
  {
    NUM_0 = N_0_01 + N_0_02 + N_0_03 + N_0_04 + N_0_05;
    NUM_0_MADE = true;
  }

  return NUM_0;
}

string SYMBOLS_5X5_NUMBERS::num_1()
{
  if (NUM_1_MADE == false)
  {
    NUM_1 = N_1_01 + N_1_02 + N_1_03 + N_1_04 + N_1_05;
    NUM_1_MADE = true;
  }

  return NUM_1;
}

string SYMBOLS_5X5_NUMBERS::num_2()
{
  if (NUM_2_MADE == false)
  {
    NUM_2 = N_2_01 + N_2_02 + N_2_03 + N_2_04 + N_2_05;
    NUM_2_MADE = true;
  }

  return NUM_2;
}

string SYMBOLS_5X5_NUMBERS::num_3()
{
  if (NUM_3_MADE == false)
  {
    NUM_3 = N_3_01 + N_3_02 + N_3_03 + N_3_04 + N_3_05;
    NUM_3_MADE = true;
  }

  return NUM_3;
}

string SYMBOLS_5X5_NUMBERS::num_4()
{
  if (NUM_4_MADE == false)
  {
    NUM_4 = N_4_01 + N_4_02 + N_4_03 + N_4_04 + N_4_05;
    NUM_4_MADE = true;
  }

  return NUM_4;
}

string SYMBOLS_5X5_NUMBERS::num_5()
{
  if (NUM_5_MADE == false)
  {
    NUM_5 = N_5_01 + N_5_02 + N_5_03 + N_5_04 + N_5_05;
    NUM_5_MADE = true;
  }

  return NUM_5;
}

string SYMBOLS_5X5_NUMBERS::num_6()
{
  if (NUM_6_MADE == false)
  {
    NUM_6 = N_6_01 + N_6_02 + N_6_03 + N_6_04 + N_6_05;
    NUM_6_MADE = true;
  }

  return NUM_6;
}

string SYMBOLS_5X5_NUMBERS::num_7()
{
  if (NUM_7_MADE == false)
  {
    NUM_7 = N_7_01 + N_7_02 + N_7_03 + N_7_04 + N_7_05;
    NUM_7_MADE = true;
  }

  return NUM_7;
}

string SYMBOLS_5X5_NUMBERS::num_8()
{
  if (NUM_8_MADE == false)
  {
    NUM_8 = N_8_01 + N_8_02 + N_8_03 + N_8_04 + N_8_05;
    NUM_8_MADE = true;
  }

  return NUM_8;
}

string SYMBOLS_5X5_NUMBERS::num_9()
{
  if (NUM_9_MADE == false)
  {
    NUM_9 = N_9_01 + N_9_02 + N_9_03 + N_9_04 + N_9_05;
    NUM_9_MADE = true;
  }

  return NUM_9;
}

string SYMBOLS_5X5_NUMBERS::number(int Number)
{
  if (Number == 0)
  {
    return num_0();
  }
  else if (Number == 1)
  {
    return num_1();
  }
  else if (Number == 2)
  {
    return num_2();
  }
  else if (Number == 3)
  {
    return num_3();
  }
  else if (Number == 4)
  {
    return num_4();
  }
  else if (Number == 5)
  {
    return num_5();
  }
  else if (Number == 6)
  {
    return num_6();
  }
  else if (Number == 7)
  {
    return num_7();
  }
  else if (Number == 8)
  {
    return num_8();
  }
  else if (Number == 9)
  {
    return num_9();
  }
  else
  {
    return num_x();
  }
}

// -------------------------------------------------------------------------------------

string SYMBOLS_3X3_NUMBERS::num_x()
{
  if (NUM_X_MADE == false)
  {
    NUM_X = X_01 + X_02 + X_03;
    NUM_X_MADE = true;
  }

  return NUM_X;
}

// -------------------------------------------------------------------------------------

#endif