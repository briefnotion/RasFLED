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

#ifndef RASAPI_H
#define RASAPI_H

// Standard Header Files
#include <fstream>
#include <iostream>
#include <sys/stat.h>
#include <string.h>

using namespace std;

// -------------------------------------------------------------------------------------
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

  void close_then_reopen()
  // Simple close the stream then reopen, effectivly clearing stram errors.
  {
    close();
    open(FILENAME);
  }

  void reset()
  // Simple close the stream then reopen, effectivly clearing stram errors.
  // Also, clears the positon variable so the next attempt to get line or
  //  check line avail will cause the routine to start reading from the 
  //  beginning.
  {
    close();
    LINE_AVAIL = false;
    POSITION = 0;
    open(FILENAME);
  }

  long get_file_size()
  // Get the size of file with name and path defined by the class var named 
  //  FILENAME.
  {
    struct stat stat_buf;
    int rc = stat(FILENAME.c_str(), &stat_buf);
    return rc == 0 ? stat_buf.st_size : -1;
  }

  bool file_changed()
  // Returns true if file size has changed.
  // Sets the new FILE_SIZE if changed.
  // Complete reset of the entire FILE_WATCH if 
  //  the read position is past the end of file because 
  //  the file has had content removed.
  {
    // Get file size;
    long new_file_size = get_file_size();

    // Reset if position is outside file or file read has failed.
    if (POSITION > new_file_size || (LOG_FILE.fail() == true))
    {
      reset();
      return false; 
    }
    
    // Compair file size to history.
    if (FILE_SIZE == new_file_size)
    {
      return false;
    }
    else
    {
      FILE_SIZE = new_file_size;
      return true;
    }
  }

  public:

  bool open(string Filename)
  // Open the file for watching.
  {
    FILENAME = Filename;
    LOG_FILE.open(FILENAME, ios::in);
    return true;
  }

  bool close()
  // Close the file.
  {
    LOG_FILE.close();
    return true;
  }

  bool line_avail()
  // Returns true if a line is available to be read.
  {
    if (LINE_AVAIL == true || file_changed() == true)
    {
      LINE_AVAIL = true;
    }
    
    return LINE_AVAIL;
  }

  string get_next_line()
  // Returns the newly added line of the watch file.
  {
    //string containing new line.
    string str_read_line = "";

    if (LINE_AVAIL == true)
    // if line available read line to return.
    {
      // New Position var for comparison.
      streampos new_position;

      // Insure cursor position is at correct spot.
      LOG_FILE.seekg(POSITION);

      // Load next line.
      getline(LOG_FILE, str_read_line);

      // Read new cursor position.
      new_position = LOG_FILE.tellg();

      if (LOG_FILE.eof())
      // No more lines available at EOF.
      {
        // Set class var showing no more lines are available.
        LINE_AVAIL = false;

        // The file will be errored out because of the EOF, 
        //  so properly close it and open again.  There will 
        //  be no more read attempts until the size changes. 
        close_then_reopen();

        // Set the new cursor position to one position back 
        // from the file size, or, one position prior to the 
        // END_OF_FILE marker, so the cursor will be at the 
        // correct posion when the file is read again.
        POSITION = FILE_SIZE -1;
      }
      else
      {
        // More lines are available, but store the new positon 
        //  for safe keeping, which is necessary becaues of the 
        //  next get line call.
        POSITION = new_position;

        // Check and stop grabbing next lines if the program 
        //  is at the END OF FILE.
        if (POSITION >= FILE_SIZE -1)
        {
          LINE_AVAIL = false;
        }
      }
    }
    
    // Return the read line.
    return str_read_line;
  }
};



#endif