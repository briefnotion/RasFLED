// ***************************************************************************************
// *
// *    Core       | Everything within this document is proprietary to Core Dynamics.
// *    Dynamics   | Any unauthorized duplication will be subject to prosecution.
// *
// *    Department : (R+D)^2                        Name: radio_channel_coordinator.h
// *       Sub Dept: Programming
// *    Location ID: 856-45B
// *                                                      (c) 2856 - 2858 Core Dynamics
// ***************************************************************************************

#ifndef RADIO_CHANNEL_COORDINATOR_H
#define RADIO_CHANNEL_COORDINATOR_H

#include <deque>

#include "helper.h"
#include "api_rtlairband.h"

using namespace std;

class RADIO_CHANNEL_COORDINATOR
{
  private:

  bool PLAY = false; // Radio Coordinator active when set to true. Pause when 
                    //  set to false

  public:
  
  API_COMMAND COMMAND_TO_RADIO;

  // Last know device status.
  API_DEVICE DEVICE_STATUS;
  int LAST_READ_BIND_COUNT = 0;

  // Stores all the frequencies observed and parsed into frequencies.
  deque<API_SQUELCH_DESTINATION> CHANNELS;
  
  int size();

  void process_command_received(API_COMMAND &Command_Received);

  void process(API_SQUELCH_DESTINATION &Received_Squelch);

  void pause();

  void play();

  bool is_paused();

  void command_send(int Command, int Parameter);

};



#endif