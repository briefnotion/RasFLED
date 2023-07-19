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

string AUTOMOTIVE_SYMBOLS::car_lights_off()
{
  if (CAR_LIGHTS_OFF_MADE == false)
  {
    CAR_LIGHTS_OFF_BUILT = CAR_LIGHTS_OFF_01 + CAR_LIGHTS_OFF_02;
    CAR_LIGHTS_OFF_MADE = true;
  }

  return CAR_LIGHTS_OFF_BUILT;
}

string AUTOMOTIVE_SYMBOLS::car_lights_on()
{
  if (CAR_LIGHTS_ON_MADE == false)
  {
    CAR_LIGHTS_ON_BUILT = CAR_LIGHTS_ON_01 + CAR_LIGHTS_ON_02;
    CAR_LIGHTS_ON_MADE = true;
  }

  return CAR_LIGHTS_ON_BUILT;
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

string SYMBOLS_6X5_CHARACTER_SMALL::space()
{
  if (SPACE_MADE == false)
  {
    SPACE = SPACE_01 + SPACE_02 + SPACE_03 + SPACE_04 + SPACE_05;
    SPACE_MADE = true;
  }

  return SPACE;
}

string SYMBOLS_6X5_CHARACTER_SMALL::char_A()
{
  if (CHAR_A_MADE == false)
  {
    CHAR_A = A_01 + A_02 + A_03 + A_04 + A_05;
    CHAR_A_MADE = true;
  }

  return CHAR_A;
}

string SYMBOLS_6X5_CHARACTER_SMALL::char_B()
{
  if (CHAR_B_MADE == false)
  {
    CHAR_B = B_01 + B_02 + B_03 + B_04 + B_05;
    CHAR_B_MADE = true;
  }

  return CHAR_B;
}

string SYMBOLS_6X5_CHARACTER_SMALL::char_C()
{
  if (CHAR_C_MADE == false)
  {
    CHAR_C = C_01 + C_02 + C_03 + C_04 + C_05;
    CHAR_C_MADE = true;
  }

  return CHAR_C;
}

string SYMBOLS_6X5_CHARACTER_SMALL::char_D()
{
  if (CHAR_D_MADE == false)
  {
    CHAR_D = D_01 + D_02 + D_03 + D_04 + D_05;
    CHAR_D_MADE = true;
  }

  return CHAR_D;
}

string SYMBOLS_6X5_CHARACTER_SMALL::char_E()
{
  if (CHAR_E_MADE == false)
  {
    CHAR_E = E_01 + E_02 + E_03 + E_04 + E_05;
    CHAR_E_MADE = true;
  }

  return CHAR_E;
}

string SYMBOLS_6X5_CHARACTER_SMALL::char_F()
{
  if (CHAR_F_MADE == false)
  {
    CHAR_F = F_01 + F_02 + F_03 + F_04 + F_05;
    CHAR_F_MADE = true;
  }

  return CHAR_F;
}

string SYMBOLS_6X5_CHARACTER_SMALL::char_G()
{
  if (CHAR_G_MADE == false)
  {
    CHAR_G = G_01 + G_02 + G_03 + G_04 + G_05;
    CHAR_G_MADE = true;
  }

  return CHAR_G;
}

string SYMBOLS_6X5_CHARACTER_SMALL::char_H()
{
  if (CHAR_H_MADE == false)
  {
    CHAR_H = H_01 + H_02 + H_03 + H_04 + H_05;
    CHAR_H_MADE = true;
  }

  return CHAR_H;
}

string SYMBOLS_6X5_CHARACTER_SMALL::char_I()
{
  if (CHAR_I_MADE == false)
  {
    CHAR_I = I_01 + I_02 + I_03 + I_04 + I_05;
    CHAR_I_MADE = true;
  }

  return CHAR_I;
}

string SYMBOLS_6X5_CHARACTER_SMALL::char_J()
{
  if (CHAR_J_MADE == false)
  {
    CHAR_J = J_01 + J_02 + J_03 + J_04 + J_05;
    CHAR_J_MADE = true;
  }

  return CHAR_J;
}

string SYMBOLS_6X5_CHARACTER_SMALL::char_K()
{
  if (CHAR_K_MADE == false)
  {
    CHAR_K = K_01 + K_02 + K_03 + K_04 + K_05;
    CHAR_K_MADE = true;
  }

  return CHAR_K;
}

string SYMBOLS_6X5_CHARACTER_SMALL::char_L()
{
  if (CHAR_L_MADE == false)
  {
    CHAR_L = L_01 + L_02 + L_03 + L_04 + L_05;
    CHAR_L_MADE = true;
  }

  return CHAR_L;
}

string SYMBOLS_6X5_CHARACTER_SMALL::char_M()
{
  if (CHAR_M_MADE == false)
  {
    CHAR_M = M_01 + M_02 + M_03 + M_04 + M_05;
    CHAR_M_MADE = true;
  }

  return CHAR_M;
}

string SYMBOLS_6X5_CHARACTER_SMALL::char_N()
{
  if (CHAR_N_MADE == false)
  {
    CHAR_N = N_01 + N_02 + N_03 + N_04 + N_05;
    CHAR_N_MADE = true;
  }

  return CHAR_N;
}

string SYMBOLS_6X5_CHARACTER_SMALL::char_O()
{
  if (CHAR_O_MADE == false)
  {
    CHAR_O = O_01 + O_02 + O_03 + O_04 + O_05;
    CHAR_O_MADE = true;
  }

  return CHAR_O;
}

string SYMBOLS_6X5_CHARACTER_SMALL::char_P()
{
  if (CHAR_P_MADE == false)
  {
    CHAR_P = P_01 + P_02 + P_03 + P_04 + P_05;
    CHAR_P_MADE = true;
  }

  return CHAR_P;
}

string SYMBOLS_6X5_CHARACTER_SMALL::char_Q()
{
  if (CHAR_Q_MADE == false)
  {
    CHAR_Q = Q_01 + Q_02 + Q_03 + Q_04 + Q_05;
    CHAR_Q_MADE = true;
  }

  return CHAR_Q;
}

string SYMBOLS_6X5_CHARACTER_SMALL::char_R()
{
  if (CHAR_R_MADE == false)
  {
    CHAR_R = R_01 + R_02 + R_03 + R_04 + R_05;
    CHAR_R_MADE = true;
  }

  return CHAR_R;
}

string SYMBOLS_6X5_CHARACTER_SMALL::char_S()
{
  if (CHAR_S_MADE == false)
  {
    CHAR_S = S_01 + S_02 + S_03 + S_04 + S_05;
    CHAR_S_MADE = true;
  }

  return CHAR_S;
}

string SYMBOLS_6X5_CHARACTER_SMALL::char_T()
{
  if (CHAR_T_MADE == false)
  {
    CHAR_T = T_01 + T_02 + T_03 + T_04 + T_05;
    CHAR_T_MADE = true;
  }

  return CHAR_T;
}

string SYMBOLS_6X5_CHARACTER_SMALL::char_U()
{
  if (CHAR_U_MADE == false)
  {
    CHAR_U = U_01 + U_02 + U_03 + U_04 + U_05;
    CHAR_U_MADE = true;
  }

  return CHAR_U;
}

string SYMBOLS_6X5_CHARACTER_SMALL::char_V()
{
  if (CHAR_V_MADE == false)
  {
    CHAR_V = V_01 + V_02 + V_03 + V_04 + V_05;
    CHAR_V_MADE = true;
  }

  return CHAR_V;
}

string SYMBOLS_6X5_CHARACTER_SMALL::char_W()
{
  if (CHAR_W_MADE == false)
  {
    CHAR_W = W_01 + W_02 + W_03 + W_04 + W_05;
    CHAR_W_MADE = true;
  }

  return CHAR_W;
}

string SYMBOLS_6X5_CHARACTER_SMALL::char_X()
{
  if (CHAR_X_MADE == false)
  {
    CHAR_X = A_01 + A_02 + A_03 + A_04 + A_05;
    CHAR_X_MADE = true;
  }

  return CHAR_X;
}

string SYMBOLS_6X5_CHARACTER_SMALL::char_Y()
{
  if (CHAR_Y_MADE == false)
  {
    CHAR_Y = Y_01 + Y_02 + Y_03 + Y_04 + Y_05;
    CHAR_Y_MADE = true;
  }

  return CHAR_Y;
}

string SYMBOLS_6X5_CHARACTER_SMALL::char_Z()
{
  if (CHAR_Z_MADE == false)
  {
    CHAR_Z = Z_01 + Z_02 + Z_03 + Z_04 + Z_05;
    CHAR_Z_MADE = true;
  }

  return CHAR_Z;
}


string SYMBOLS_6X5_CHARACTER_SMALL::char_0()
{
  if (CHAR_0_MADE == false)
  {
    CHAR_0 = N_0_01 + N_0_02 + N_0_03 + N_0_04 + N_0_05;
    CHAR_0_MADE = true;
  }

  return CHAR_0;
}

string SYMBOLS_6X5_CHARACTER_SMALL::char_1()
{
  if (CHAR_1_MADE == false)
  {
    CHAR_1 = N_1_01 + N_1_02 + N_1_03 + N_1_04 + N_1_05;
    CHAR_1_MADE = true;
  }

  return CHAR_1;
}

string SYMBOLS_6X5_CHARACTER_SMALL::char_2()
{
  if (CHAR_2_MADE == false)
  {
    CHAR_2 = N_2_01 + N_2_02 + N_2_03 + N_2_04 + N_2_05;
    CHAR_2_MADE = true;
  }

  return CHAR_2;
}

string SYMBOLS_6X5_CHARACTER_SMALL::char_3()
{
  if (CHAR_3_MADE == false)
  {
    CHAR_3 = N_3_01 + N_3_02 + N_3_03 + N_3_04 + N_3_05;
    CHAR_3_MADE = true;
  }

  return CHAR_3;
}

string SYMBOLS_6X5_CHARACTER_SMALL::char_4()
{
  if (CHAR_4_MADE == false)
  {
    CHAR_4 = N_4_01 + N_4_02 + N_4_03 + N_4_04 + N_4_05;
    CHAR_4_MADE = true;
  }

  return CHAR_4;
}

string SYMBOLS_6X5_CHARACTER_SMALL::char_5()
{
  if (CHAR_5_MADE == false)
  {
    CHAR_5 = N_5_01 + N_5_02 + N_5_03 + N_5_04 + N_5_05;
    CHAR_5_MADE = true;
  }

  return CHAR_5;
}

string SYMBOLS_6X5_CHARACTER_SMALL::char_6()
{
  if (CHAR_6_MADE == false)
  {
    CHAR_6 = N_6_01 + N_6_02 + N_6_03 + N_6_04 + N_6_05;
    CHAR_6_MADE = true;
  }

  return CHAR_6;
}

string SYMBOLS_6X5_CHARACTER_SMALL::char_7()
{
  if (CHAR_7_MADE == false)
  {
    CHAR_7 = N_7_01 + N_7_02 + N_7_03 + N_7_04 + N_7_05;
    CHAR_7_MADE = true;
  }

  return CHAR_7;
}

string SYMBOLS_6X5_CHARACTER_SMALL::char_8()
{
  if (CHAR_8_MADE == false)
  {
    CHAR_8 = N_8_01 + N_8_02 + N_8_03 + N_8_04 + N_8_05;
    CHAR_8_MADE = true;
  }

  return CHAR_8;
}

string SYMBOLS_6X5_CHARACTER_SMALL::char_9()
{
  if (CHAR_9_MADE == false)
  {
    CHAR_9 = N_9_01 + N_9_02 + N_9_03 + N_9_04 + N_9_05;
    CHAR_9_MADE = true;
  }

  return CHAR_9;
}

string SYMBOLS_6X5_CHARACTER_SMALL::char_0_d()
{
  if (CHAR_0_d_MADE == false)
  {
    CHAR_0_d = N_0_01_d + N_0_02_d + N_0_03_d + N_0_04_d + N_0_05_d;
    CHAR_0_d_MADE = true;
  }

  return CHAR_0_d;
}

string SYMBOLS_6X5_CHARACTER_SMALL::char_1_d()
{
  if (CHAR_1_d_MADE == false)
  {
    CHAR_1_d = N_1_01_d + N_1_02_d + N_1_03_d + N_1_04_d + N_1_05_d;
    CHAR_1_d_MADE = true;
  }

  return CHAR_1_d;
}

string SYMBOLS_6X5_CHARACTER_SMALL::char_2_d()
{
  if (CHAR_2_d_MADE == false)
  {
    CHAR_2_d = N_2_01_d + N_2_02_d + N_2_03_d + N_2_04_d + N_2_05_d;
    CHAR_2_d_MADE = true;
  }

  return CHAR_2_d;
}

string SYMBOLS_6X5_CHARACTER_SMALL::char_3_d()
{
  if (CHAR_3_d_MADE == false)
  {
    CHAR_3_d = N_3_01_d + N_3_02_d + N_3_03_d + N_3_04_d + N_3_05_d;
    CHAR_3_d_MADE = true;
  }

  return CHAR_3_d;
}

string SYMBOLS_6X5_CHARACTER_SMALL::char_4_d()
{
  if (CHAR_4_d_MADE == false)
  {
    CHAR_4_d = N_4_01_d + N_4_02_d + N_4_03_d + N_4_04_d + N_4_05_d;
    CHAR_4_d_MADE = true;
  }

  return CHAR_4_d;
}

string SYMBOLS_6X5_CHARACTER_SMALL::char_5_d()
{
  if (CHAR_5_d_MADE == false)
  {
    CHAR_5_d = N_5_01_d + N_5_02_d + N_5_03_d + N_5_04_d + N_5_05_d;
    CHAR_5_d_MADE = true;
  }

  return CHAR_5_d;
}

string SYMBOLS_6X5_CHARACTER_SMALL::char_6_d()
{
  if (CHAR_6_d_MADE == false)
  {
    CHAR_6_d = N_6_01_d + N_6_02_d + N_6_03_d + N_6_04_d + N_6_05_d;
    CHAR_6_d_MADE = true;
  }

  return CHAR_6_d;
}

string SYMBOLS_6X5_CHARACTER_SMALL::char_7_d()
{
  if (CHAR_7_d_MADE == false)
  {
    CHAR_7_d = N_7_01_d + N_7_02_d + N_7_03_d + N_7_04_d + N_7_05_d;
    CHAR_7_d_MADE = true;
  }

  return CHAR_7_d;
}

string SYMBOLS_6X5_CHARACTER_SMALL::char_8_d()
{
  if (CHAR_8_d_MADE == false)
  {
    CHAR_8_d = N_8_01_d + N_8_02_d + N_8_03_d + N_8_04_d + N_8_05_d;
    CHAR_8_d_MADE = true;
  }

  return CHAR_8_d;
}

string SYMBOLS_6X5_CHARACTER_SMALL::char_9_d()
{
  if (CHAR_9_d_MADE == false)
  {
    CHAR_9_d = N_9_01_d + N_9_02_d + N_9_03_d + N_9_04_d + N_9_05_d;
    CHAR_9_d_MADE = true;
  }

  return CHAR_9_d;
}

string SYMBOLS_6X5_CHARACTER_SMALL::character(char Character)
{
  if (Character == ' ')
  {
    return space();
  }
  else if (Character == 'A')
  {
    return char_A();
  }
  else if (Character == 'B')
  {
    return char_B();
  }
  else if (Character == 'C')
  {
    return char_C();
  }
  else if (Character == 'D')
  {
    return char_D();
  }
  else if (Character == 'E')
  {
    return char_E();
  }
  else if (Character == 'F')
  {
    return char_F();
  }
  else if (Character == 'G')
  {
    return char_G();
  }
  else if (Character == 'H')
  {
    return char_H();
  }
  else if (Character == 'I')
  {
    return char_I();
  }
  else if (Character == 'J')
  {
    return char_J();
  }
  else if (Character == 'K')
  {
    return char_K();
  }
  else if (Character == 'L')
  {
    return char_L();
  }
  else if (Character == 'M')
  {
    return char_M();
  }
  else if (Character == 'N')
  {
    return char_N();
  }
  else if (Character == 'O')
  {
    return char_O();
  }
  else if (Character == 'P')
  {
    return char_P();
  }
  else if (Character == 'Q')
  {
    return char_Q();
  }
  else if (Character == 'R')
  {
    return char_R();
  }
  else if (Character == 'S')
  {
    return char_S();
  }
  else if (Character == 'T')
  {
    return char_T();
  }
  else if (Character == 'U')
  {
    return char_U();
  }
  else if (Character == 'V')
  {
    return char_V();
  }
  else if (Character == 'W')
  {
    return char_W();
  }
  else if (Character == 'X')
  {
    return char_X();
  }
  else if (Character == 'Y')
  {
    return char_Y();
  }
  else if (Character == 'Z')
  {
    return char_Z();
  }
  else if (Character == '0')
  {
    return char_0();
  }
  else if (Character == '1')
  {
    return char_1();
  }
  else if (Character == '2')
  {
    return char_2();
  }
  else if (Character == '3')
  {
    return char_3();
  }
  else if (Character == '4')
  {
    return char_4();
  }
  else if (Character == '5')
  {
    return char_5();
  }
  else if (Character == '6')
  {
    return char_6();
  }
  else if (Character == '7')
  {
    return char_7();
  }
  else if (Character == '8')
  {
    return char_8();
  }
  else if (Character == '9')
  {
    return char_9();
  }
  else
  {
    return char_X();
  }
}

string SYMBOLS_6X5_CHARACTER_SMALL::number(int Number)
{
  if (Number == 0)
  {
    return char_0();
  }
  else if (Number == 1)
  {
    return char_1();
  }
  else if (Number == 2)
  {
    return char_2();
  }
  else if (Number == 3)
  {
    return char_3();
  }
  else if (Number == 4)
  {
    return char_4();
  }
  else if (Number == 5)
  {
    return char_5();
  }
  else if (Number == 6)
  {
    return char_6();
  }
  else if (Number == 7)
  {
    return char_7();
  }
  else if (Number == 8)
  {
    return char_8();
  }
  else if (Number == 9)
  {
    return char_9();
  }
  else
  {
    return char_X();
  }
}

string SYMBOLS_6X5_CHARACTER_SMALL::number(int Number, bool Decimal)
{
  if (Decimal == false)
  {
    return number(Number);
  }
  else
  {
    if (Number == 0)
    {
      return char_0_d();
    }
    else if (Number == 1)
    {
      return char_1_d();
    }
    else if (Number == 2)
    {
      return char_2_d();
    }
    else if (Number == 3)
    {
      return char_3_d();
    }
    else if (Number == 4)
    {
      return char_4_d();
    }
    else if (Number == 5)
    {
      return char_5_d();
    }
    else if (Number == 6)
    {
      return char_6_d();
    }
    else if (Number == 7)
    {
      return char_7_d();
    }
    else if (Number == 8)
    {
      return char_8_d();
    }
    else if (Number == 9)
    {
      return char_9_d();
    }
    else
    {
      return char_X();
    }
  }
}

// -------------------------------------------------------------------------------------

#endif