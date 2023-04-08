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

  if (PROPS.PORT == "")
  {
    ret_success = false;
  }
  if (PROPS.RECEIVE_TEST_DATA == true)
  {
    file_to_deque_string(PROPS.TEST_DATA_FILENAME, TEST_DATA);
    ret_success = true;
  }
  else
  {
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
    // Choices: B0,  B50,  B75,  B110,  B134,  B150,  B200, B300, B600, B1200, B1800, B2400, 
    //          B4800, B9600, B19200, B38400, B57600, B115200, B230400, B460800
    if (PROPS.BAUD_RATE == 300)
    {
      cfsetospeed (&tty, (speed_t)B300);
      cfsetispeed (&tty, (speed_t)B300);
    }
    else if (PROPS.BAUD_RATE == 2400)
    {
      cfsetospeed (&tty, (speed_t)B2400);
      cfsetispeed (&tty, (speed_t)B2400);
    }
    else if (PROPS.BAUD_RATE == 4800)
    {
      cfsetospeed (&tty, (speed_t)B4800);
      cfsetispeed (&tty, (speed_t)B4800);
    }
    else if (PROPS.BAUD_RATE == 9600)
    {
      cfsetospeed (&tty, (speed_t)B9600);
      cfsetispeed (&tty, (speed_t)B9600);
    }
    else if (PROPS.BAUD_RATE == 19200)
    {
      cfsetospeed (&tty, (speed_t)B19200);
      cfsetispeed (&tty, (speed_t)B19200);
    }
    else if (PROPS.BAUD_RATE == 38400)
    {
      cfsetospeed (&tty, (speed_t)B38400);
      cfsetispeed (&tty, (speed_t)B38400);
    }
    else if (PROPS.BAUD_RATE == 57600)
    {
      cfsetospeed (&tty, (speed_t)B57600);
      cfsetispeed (&tty, (speed_t)B57600);
    }
    else if (PROPS.BAUD_RATE == 115200)
    {
      cfsetospeed (&tty, (speed_t)B115200);
      cfsetispeed (&tty, (speed_t)B115200);
    }
    else if (PROPS.BAUD_RATE == 230400)
    {
      cfsetospeed (&tty, (speed_t)B230400);
      cfsetispeed (&tty, (speed_t)B230400);
    }
    else if (PROPS.BAUD_RATE == 460800)
    {
      cfsetospeed (&tty, (speed_t)B460800);
      cfsetispeed (&tty, (speed_t)B460800);
    }

    /* Setting other Port Stuff */
    if (PROPS.PARITY == false)          // Set Parity
    {
      tty.c_cflag &= ~PARENB;           // No Parity
    }
    else
    {
      tty.c_cflag |= PARENB;            // Parity
    }

    if (PROPS.STOP_BITS == 1)           // Set Stop Bits
    {
      tty.c_cflag &=  ~CSTOPB;          // 1 Stop Bit
    }
    else
    {
      tty.c_cflag |= CSTOPB;            // 2 Stop Bit    
    }

    tty.c_cflag &=  ~CSIZE;             // Clear Bits per Byte
    if (PROPS.BIT_COUNT == 5)           // 5 Bits per Byte
    {
      tty.c_cflag |=  CS5;
    }
    else if (PROPS.BIT_COUNT == 6)      // 6 Bits per Byte
    {
      tty.c_cflag |=  CS6;
    }
    else if (PROPS.BIT_COUNT == 7)      // 7 Bits per Byte
    {
      tty.c_cflag |=  CS7;
    }
    else //(PROPS.BIT_COUNT == 8)       // 8 Bits per Byte
    {
      tty.c_cflag |=  CS8;
    }

    if (PROPS.HARDWARE_FLOW_CONTROL == false) // Hardware Flow Control
    {
      tty.c_cflag &=  ~CRTSCTS;         // no flow control
    }
    else
    {
      tty.c_cflag |= CRTSCTS;           // flow control
    }

    tty.c_cc[VMIN]  = PROPS.READ_BYTE_MIN;  // default 1
    tty.c_cc[VTIME] = PROPS.READ_MIN_TIME;  // default 0.5 seconds


    tty.c_cflag |=  CREAD | CLOCAL; // turn on READ & ignore ctrl lines

    if (PROPS.DISABLE_CANONICAL_MODE == true)
    {
      tty.c_cflag &= ~ICANON;
    }

    if (PROPS.XONXOFF == true)
    {
      tty.c_iflag |= IXON | IXOFF;            // enable XON/XOFF flow control
    }

    /* Make raw */
    cfmakeraw(&tty);

    /* Flush Port, then applies attributes */
    tcflush( USB, TCIFLUSH );

    if ( tcsetattr ( USB, TCSANOW, &tty ) != 0) 
    {
      //   std::cout << "Error " << errno << " from tcsetattr" << std::endl;
      ret_success = false;
    }
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
      if (PROPS.SAVE_TO_LOG == true && WRITE_TO_COMM.size() >0)
      {
        WRITE_TO_COMM.push_front("- Send");
        deque_string_to_file(PROPS.SAVE_LOG_FILENAME, WRITE_TO_COMM, true);
        WRITE_TO_COMM.pop_front();
      }

      write_to_comm(WRITE_TO_COMM.front());
      WRITE_TO_COMM.pop_front();

    }

    if(PROPS.RECEIVE_TEST_DATA == false)
    {
      while (data_received == true)
      {
        data_received = read_from_comm();
      }

      if (PROPS.SAVE_TO_LOG == true && READ_FROM_COMM.size() >0)
      {
        deque_string_to_file(PROPS.SAVE_LOG_FILENAME, READ_FROM_COMM, true);
      }
    }
    else
    {
      // send test data
      for (int count = 0; count < 3; count++)
      {
        if (TEST_DATA.size() > 0)
        {
          READ_FROM_COMM.push_back(TEST_DATA.front());
          TEST_DATA.pop_front();
        }
      }
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