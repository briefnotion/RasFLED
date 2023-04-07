// ***************************************************************************************
// *
// *    Core       | Everything within this document is proprietary to Core Dynamics.
// *    Dynamics   | Any unauthorized duplication will be subject to prosecution.
// *
// *    Department : (R+D)^2                        Name: rasapi.h
// *       Sub Dept: Programming
// *    Location ID: 856-45B
// *                                                      (c) 2856 - 2858 Core Dynamics
// ***************************************************************************************
// *
// *  PROJECTID: gi6$b*E>*q%;    Revision: 00000000.01A
// *  TEST CODE:                 QACODE: A565              CENSORCODE: EQK6}Lc`:Eg>
// *
// ***************************************************************************************
// Note: I dont like the way boost filesystem and standard file system is mixed.  Needs 
//        a few rewrites.

#ifndef RASAPI_H
#define RASAPI_H

// Standard Header Files
#include <fstream>
#include <iostream>
#include <sys/stat.h>
#include <string>
#include <time.h>
#include <deque>

// Boost libraries
#include <boost/filesystem.hpp>

using namespace std;

// -------------------------------------------------------------------------------------
class FILE_WATCH_Properties
// Properties (duh)
{
  public:
  bool READ_FROM_BEGINNING = false; // Set behavior to return next line from previous 
                                    //  read last line read on file change or start 
                                    //  next line from beginning on file change.

  bool FILE_EXIST = false;  // Indicates existance of file on last file check.
  bool ACTIVE = true;       // Indicates if routine is in good status and working.
  bool ENABLED = true;      // turn on and off routine.  (Not Yet Implemented)

  bool WATCH_SIZE_CHANGE = true;  // New line indicated if File Size changed.
  bool WATCH_TIME_CHANGE = false; // New line indicated if File Write Time changed.
};

class FILE_WATCH
// Watches a log file and returns lines added through the get_next_line function.
{
  private:
  ifstream LOG_FILE;

  string FILENAME = "";

  long  FILE_SIZE   = 0;
  bool  LINE_AVAIL  = false;

  // Next cursor position of Read_Line
  streampos POSITION;

  // File Properties
  time_t LAST_WRITE_TIME;

  bool CHANGED = false;

  public:
  FILE_WATCH_Properties PROP;

  private:

  bool open();

  bool close();

  void close_then_reopen();

  bool check_file_status();

  void reset();

  long get_file_size();

  bool file_time_changed();

  bool file_changed();

  public:

  void start(string Filename);
  
  void stop();

  bool line_avail();

  bool changed();

  string get_next_line();
};

bool check_create_working_dir(string Directory);
// Not Coded

string file_to_string(string Dir_Filename, bool &Success);
// Opens and loads a file to return as a string.
// Reurns Success true false value.

string file_to_string(string Dir_Filename);
// Opens and loads a file to return as a string.

bool deque_string_to_file(string Dir_Filename, deque<string> &qFile, bool Append);
// Opens and saves a dequed string into a file with append option
// Reurns false if failed.

bool file_to_deque_string(string Dir_Filename, deque<string> &qFile);
// Opens and saves a dequed string into a file with append option
// Reurns false if failed.

#endif