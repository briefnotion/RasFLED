// ***************************************************************************************
// *
// *    Core       | Everything within this document is proprietary to Core Dynamics.
// *    Dynamics   | Any unauthorized duplication will be subject to prosecution.
// *
// *    Department : (R+D)^2                        Name: hardware_status.cpp
// *       Sub Dept: Programming
// *    Location ID: 856-45B
// *                                                      (c) 2856 - 2858 Core Dynamics
// ***************************************************************************************

#ifndef HARDWARE_STATUS_CPP
#define HARDWARE_STATUS_CPP

#include "hardware_status.h"

void HARDWARE_STATUS::read_temperature()
// Read the value of the CPU Temp by reading the sys thermal zone temp.
//  Then, put the value into its holding variable.
// I have no idea how this works. Simply cut and paste from the World Wide Internet.
{
  const int buf_size = 100;
  char data[buf_size];

  FILE *fshardware;
  size_t bytesread;

  if(ENABLED==true)
  {
    fshardware = fopen(strTEMPERTURE_FILENAME.c_str(), "r");

    if (fshardware != NULL)
    {

      memset(data, 0, buf_size);

      fread(data, buf_size, 1, fshardware);

      TEMPERTURE = string_to_int(data);
      TEMPERTURE /= 1000;

      fclose(fshardware);
    }      
    else
    {
      ENABLED = false;
    }
  }
}

void HARDWARE_STATUS::read_low_voltage()
// Read the value of the low voltage indicator by checking RasPi led 0 or 1.
//  Then, put the value into its holding variable.
// This routine doesnt work as is.
{
  const int buf_size = 100;
  char data[buf_size];

  FILE *fshardware;
  size_t bytesread;

  if(ENABLED==true)
  {
    fshardware = fopen(strLOW_VOLTAGE_FILENAME.c_str(), "r");

    if (fshardware != NULL)
    {

      memset(data, 0, buf_size);

      fread(data, buf_size, 1, fshardware);

      LOW_VOLTAGE = string_to_int(data);

      fclose(fshardware);
    }      
    else
    {
      ENABLED = false;
    }
  }
}

bool HARDWARE_STATUS::enabled()
// Returns the value of the Hardware Status Monitor being active or not.
//  If or any reason any of the system monitors fail to function proplerly, 
//  it will shut itself off.
{
  return ENABLED;
}

double HARDWARE_STATUS::get_temperature()
// Returns the value of the CPU in Celcius.
{
  if(ENABLED==true)
  {
    return TEMPERTURE;
  }
  else
  {
    return -273;
  }
}

double HARDWARE_STATUS::get_low_voltage()
// Returns the value of and undervoltage indicator.
{
  return LOW_VOLTAGE;
}

void HARDWARE_STATUS::read_hardware_status(unsigned long tmeCURRENT_FRAME_TIME, int Milis_Frequency)
// Read the values of certain mainboard components and put them into memory
//  for reference from other routines.  
//  Milis_Frequency is how often these values will be read, so as to not bog 
//  the system down with unnecessary hardware calls.
{
  if (tmeCURRENT_FRAME_TIME >= tmeLAST_READ_TIME + Milis_Frequency)
  {
    tmeLAST_READ_TIME = tmeCURRENT_FRAME_TIME;
    read_temperature();
    //read_low_voltage();
  }
}




#endif