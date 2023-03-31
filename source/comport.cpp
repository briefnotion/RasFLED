// ***************************************************************************************
// *
// *    Core       | Everything within this document is proprietary to Core Dynamics.
// *    Dynamics   | Any unauthorized duplication will be subject to prosecution.
// *
// *    Department : (R+D)^2                        Name: comport.cpp
// *       Sub Dept: Programming
// *    Location ID: 856-45B
// *                                                      (c) 2856 - 2858 Core Dynamics
// ***************************************************************************************

#ifndef COMPORT_CPP
#define COMPORT_CPP

#include "comport.h"

using namespace std;

// -------------------------------------------------------------------------------------
// 

/***************************************************************************
* signal handler. sets wait_flag to FALSE, to indicate above loop that     *
* characters have been received.                                           *
***************************************************************************/

void COMPORT::write_to_comm(string Command)
{
  Command = Command + "\r";
  
  // WARNING:
  // Method #2: Allocate memory on stack and copy the contents of the
  // original string. Keep in mind that once a current function returns,
  // the memory is invalidated.
  char *cmd;
  cmd = (char *)alloca(Command.size() + 1);
  memcpy(cmd, Command.c_str(), Command.size() + 1);

  int n_written = 0,
      spot = 0;

  do {
      n_written = write( USB, &cmd[spot], 1 );
      spot += n_written;
  } while (cmd[spot-1] != '\r' && n_written > 0);
}

bool COMPORT::read_from_comm()
{
  bool ret_data_read = false;

  int n = 0,
  spot = 0;
  char buf = '\0';

  int size_of_buffer = 0;

  /* Whole response*/
  char response[1024];
  memset(response, '\0', sizeof response);

  do 
  {
    n = read( USB, &buf, 1 );
    sprintf( &response[spot], "%c", buf );
    spot += n;
  } while( buf != '\r' && n > 0 && spot < sizeof response);
  
  //READ_FROM_COMM.push_back("size: " + to_string(spot));

  if (n < 0)
  {
    //READ_FROM_COMM.push_back("Error reading: " ); // + strerror(errno) << std::endl;)
    //READ_FROM_COMM.push_back("error!");
  }
  else if (n == 0)
  {
    //READ_FROM_COMM.push_back("Read nothing!");
  }
  else 
  {
    string res = "";
    res = trim(string(response, spot));
    
    if (res.size() > 0)
    {
      READ_FROM_COMM.push_back(res);
      ret_data_read = true;
    }
  }

  return ret_data_read;
}

void COMPORT::printout()
{
  for (int pos = 0; pos < READ_FROM_COMM.size(); pos++)
  {
    printf("pos: %d |%s|\n", pos, READ_FROM_COMM[pos].c_str());
  }
}

bool COMPORT::create()
{
  bool ret_success = true;

  memset (&tty, 0, sizeof tty);

  // WARNING:
  // Method #2: Allocate memory on stack and copy the contents of the
  // original string. Keep in mind that once a current function returns,
  // the memory is invalidated.
  char *port;
  port = (char *)alloca(PROPS.PORT.size() + 1);
  memcpy(port, PROPS.PORT.c_str(), PROPS.PORT.size() + 1);

  USB = open(port, O_RDWR| O_NOCTTY| O_NONBLOCK );

  /* Error Handling */
  if ( tcgetattr ( USB, &tty ) != 0 ) 
  {
    //   std::cout << "Error " << errno << " from tcgetattr: " << strerror(errno) << std::endl;
    ret_success = false;
  }

  /* Save old tty parameters */
  tty_old = tty;

  /* Set Baud Rate */
  if (PROPS.BAUD_RATE == 38400)
  {
    cfsetospeed (&tty, (speed_t)B38400);
    cfsetispeed (&tty, (speed_t)B38400);
  }

  /* Setting other Port Stuff */
  tty.c_cflag     &=  ~PARENB;            // Make 8n1
  tty.c_cflag     &=  ~CSTOPB;
  tty.c_cflag     &=  ~CSIZE;
  tty.c_cflag     |=  CS8;

  tty.c_cflag     &=  ~CRTSCTS;           // no flow control
  tty.c_cc[VMIN]   =  1;                  // read doesn't block
  tty.c_cc[VTIME]  =  5;                  // 0.5 seconds read timeout
  tty.c_cflag     |=  CREAD | CLOCAL;     // turn on READ & ignore ctrl lines

  /* Make raw */
  cfmakeraw(&tty);

  /* Flush Port, then applies attributes */
  tcflush( USB, TCIFLUSH );

  if ( tcsetattr ( USB, TCSANOW, &tty ) != 0) 
  {
    //   std::cout << "Error " << errno << " from tcsetattr" << std::endl;
    ret_success = false;
  }

  ACTIVE = ret_success;
  return ret_success;
}

void COMPORT::send(string Text)
{
  WRITE_TO_COMM.push_back(Text);
}

void COMPORT::cycle()
{
  bool data_received = true;

  // Do not access comm port if it is shut down.
  if (ACTIVE == true)
  {
    if (WRITE_TO_COMM.size() > 0)
    {
      write_to_comm(WRITE_TO_COMM.front());
      WRITE_TO_COMM.pop_front();
    }

    while (data_received == true)
    {
      data_received = read_from_comm();
    }
  }
}

void COMPORT::close_port()
{
  // i dont know how to close this thing.
  tty = tty_old;
  ACTIVE = false;
}



#endif