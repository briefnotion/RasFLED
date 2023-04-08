// ***************************************************************************************
// *
// *    Core       | Everything within this document is proprietary to Core Dynamics.
// *    Dynamics   | Any unauthorized duplication will be subject to prosecution.
// *
// *    Department : (R+D)^2                        Name: auto.h
// *       Sub Dept: Programming
// *    Location ID: 856-45B
// *                                                      (c) 2856 - 2858 Core Dynamics
// ***************************************************************************************

#ifndef AUTO_H
#define AUTO_H

// Standard Header Files
#include <stdio.h>
#include <string.h>
#include <deque>

#include "fled_time.h"
#include "stringthings.h"

#include "comport.h"

using namespace std;

class AUTOMOBILE_DATA_LINE
{
  public:

  string ORIG = "";

  int ID = 0;
  int DATA[8];
};

class AUTOMOBILE_DATA
{
  public:

  AUTOMOBILE_DATA_LINE AD_0;
  AUTOMOBILE_DATA_LINE AD_10;
  AUTOMOBILE_DATA_LINE AD_30;
  AUTOMOBILE_DATA_LINE AD_32;
  AUTOMOBILE_DATA_LINE AD_50;
  AUTOMOBILE_DATA_LINE AD_60;
  AUTOMOBILE_DATA_LINE AD_64;
  AUTOMOBILE_DATA_LINE AD_90;
  AUTOMOBILE_DATA_LINE AD_A0;
  AUTOMOBILE_DATA_LINE AD_C0;
  AUTOMOBILE_DATA_LINE AD_C8;
  AUTOMOBILE_DATA_LINE AD_D0;
  AUTOMOBILE_DATA_LINE AD_E0;
  AUTOMOBILE_DATA_LINE AD_F0;
  AUTOMOBILE_DATA_LINE AD_F8;
  AUTOMOBILE_DATA_LINE AD_100;
  AUTOMOBILE_DATA_LINE AD_102;
  AUTOMOBILE_DATA_LINE AD_1C0;
  AUTOMOBILE_DATA_LINE AD_120;
  AUTOMOBILE_DATA_LINE AD_128;
  AUTOMOBILE_DATA_LINE AD_130;
  AUTOMOBILE_DATA_LINE AD_138;
  AUTOMOBILE_DATA_LINE AD_140;
  AUTOMOBILE_DATA_LINE AD_150;
  AUTOMOBILE_DATA_LINE AD_160;
  AUTOMOBILE_DATA_LINE AD_17E;
  AUTOMOBILE_DATA_LINE AD_180;
  AUTOMOBILE_DATA_LINE AD_190;
  AUTOMOBILE_DATA_LINE AD_1D0;
  AUTOMOBILE_DATA_LINE AD_1E0;
  AUTOMOBILE_DATA_LINE AD_200;
  AUTOMOBILE_DATA_LINE AD_208;
  AUTOMOBILE_DATA_LINE AD_213;
  AUTOMOBILE_DATA_LINE AD_218;
  AUTOMOBILE_DATA_LINE AD_247;
  AUTOMOBILE_DATA_LINE AD_252;
  AUTOMOBILE_DATA_LINE AD_253;
  AUTOMOBILE_DATA_LINE AD_260;
  AUTOMOBILE_DATA_LINE AD_280;
  AUTOMOBILE_DATA_LINE AD_290;
  AUTOMOBILE_DATA_LINE AD_2B0;
  AUTOMOBILE_DATA_LINE AD_2D0;
  AUTOMOBILE_DATA_LINE AD_2D4;
  AUTOMOBILE_DATA_LINE AD_2D8;
  AUTOMOBILE_DATA_LINE AD_310;
  AUTOMOBILE_DATA_LINE AD_318;
  AUTOMOBILE_DATA_LINE AD_360;
  AUTOMOBILE_DATA_LINE AD_400;
  AUTOMOBILE_DATA_LINE AD_40A;
  AUTOMOBILE_DATA_LINE AD_455;

  AUTOMOBILE_DATA_LINE AD_UNKNOWN;
};

class AUTOMOBILE_PROPERTIES
// Panel border characters.
{
  public:
  
  bool SAVE_TO_LOG = false;
  string SAVE_LOG_FILENAME = "";
};

class AUTOMOBILE
{
  private:

  void parse(string Line);

  public:

  bool CHANGED = false;

  AUTOMOBILE_DATA DATA;
  AUTOMOBILE_PROPERTIES PROPS;

  int message_count = 0;

  void process(COMPORT &Com_Port);

};





#endif