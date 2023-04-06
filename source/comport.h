// ***************************************************************************************
// *
// *    Core       | Everything within this document is proprietary to Core Dynamics.
// *    Dynamics   | Any unauthorized duplication will be subject to prosecution.
// *
// *    Department : (R+D)^2                        Name: comport.h
// *       Sub Dept: Programming
// *    Location ID: 856-45B
// *                                                      (c) 2856 - 2858 Core Dynamics
// ***************************************************************************************
// *  Derived from miniterm.c.
// ***************************************************************************************

#ifndef COMPORT_H
#define COMPORT_H

// Standard Header Files
#include <stdio.h>
#include <string>
#include <deque>

#include <stdio.h>      // standard input / output functions
#include <stdlib.h>
#include <string.h>     // string function definitions
#include <unistd.h>     // UNIX standard function definitions
#include <fcntl.h>      // File control definitions
#include <errno.h>      // Error number definitions
#include <termios.h>    // POSIX terminal control definitions

// RASFled related header files

#include "stringthings.h"
#include "rasapi.h"

using namespace std;

// -------------------------------------------------------------------------------------
// 

class COMPORT_PROPERTIES
// Panel border characters.
{
  public:

  string PORT = "";
  int BAUD_RATE = 38400;

  int BIT_COUNT = 8;
  bool PARITY = false;
  int STOP_BITS = 1;

  // Not access because implementation is non blocking.
  int READ_BYTE_MIN = 1;   // Minimum bytes to process.
  int READ_MIN_TIME = 5;  // Minimum time to wait till process.

  bool HARDWARE_FLOW_CONTROL = false;

  // Experiemental (Not Implemented)
  bool DISABLE_CANONICAL_MODE = false;
  
  bool XONXOFF = false;

  bool SAVE_TO_LOG = false;
  string SAVE_LOG_FILENAME = "";

};

class COMPORT
{
  private:

  struct termios tty;
  struct termios tty_old;

  int USB = 0;

  deque<string> WRITE_TO_COMM;
  // List of text to be sent to com port on next cycle.

  public:

  COMPORT_PROPERTIES PROPS;

  deque<string> READ_FROM_COMM;
  // list of received data from com port

  private:

  void write_to_comm(string Command);
  // Sends text Command to comm

  bool read_from_comm();
  // Read a line from comm port.
  // Returns true if data added to queue.
  // Returns false if error or no data available.

  public:

  bool ACTIVE = false;
  // Error detection not implemented. Comm can be disabled
  //  by setting ACTIVE TO FALSE.
  //  Queue stacks will remain available.

  //bool CHANGED = false;

  void printout();

  bool create();
  // Prepares communications.

  void send(string Text);
  // Stack send commands to be processed at cycle.

  void cycle();
  // Writes and Reads data to comm port to send and
  //  recieve queues.

  void close_port();

};



#endif