// ***************************************************************************************
// *
// *    Core       | Everything within this document is proprietary to Core Dynamics.
// *    Dynamics   | Any unauthorized duplication will be subject to prosecution.
// *
// *    Department : (R+D)^2                        Name: hardware_status.h
// *       Sub Dept: Programming
// *    Location ID: 856-45B
// *                                                      (c) 2856 - 2858 Core Dynamics
// ***************************************************************************************

#ifndef HARDWARE_STATUS_H
#define HARDWARE_STATUS_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>


#include "stringthings.h"
#include "helper.h"
#include <wiringPi.h>


class HARDWARE_STATUS
{
  private:
  string strTEMPERTURE_FILENAME = "/sys/class/thermal/thermal_zone0/temp";
  string strLOW_VOLTAGE_FILENAME = "/sys/class/leds/led1";

  bool ENABLED = true;

  double TEMPERTURE = 0;
  double LOW_VOLTAGE = 0;

  unsigned long tmeLAST_READ_TIME = 0;

  void read_temperature();

  void read_low_voltage();

  public:

  bool enabled();

  double get_temperature();

  double get_low_voltage();

  void read_hardware_status(unsigned long tmeCURRENT_FRAME_TIME, int Milis_Frequency);
};



#endif