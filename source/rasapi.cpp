// ***************************************************************************************
// *
// *    Core       | Everything within this document is proprietary to Core Dynamics.
// *    Dynamics   | Any unauthorized duplication will be subject to prosecution.
// *
// *    Department : (R+D)^2                        Name: rasapi.cpp
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

#ifndef RASAPI_CPP
#define RASAPI_CPP

#include "rasapi.h"

using namespace std;

// -------------------------------------------------------------------------------------

bool FILE_WATCH::open()
// Open the file for watching.
{
  LOG_FILE.open(FILENAME, ios::in);

  if(LOG_FILE.is_open() == true)
  {
    PROP.ACTIVE = true;
  }
  else
  {
    PROP.ACTIVE = false;
    PROP.ENABLED = false;
  }
  return PROP.ACTIVE;
}

bool FILE_WATCH::close()
// Close the file.
{
  if(LOG_FILE.is_open())
  {
    LOG_FILE.close();
  }

  PROP.ACTIVE = false;

  return true;
}

void FILE_WATCH::close_then_reopen()
// Simple close the stream then reopen, effectivly clearing stram errors.
{
  close();
  open();
}

bool FILE_WATCH::check_file_status()
{
  if (boost::filesystem::exists(FILENAME) == false)
  {
    if (PROP.FILE_EXIST == true)
    {
      CHANGED = true;
    }

    PROP.FILE_EXIST = false;
    close();
  }
  else if(LOG_FILE.is_open() != true)
  {
    if (PROP.FILE_EXIST == false)
    {
      CHANGED = true;
    }

    PROP.FILE_EXIST = true;
    open();
  }

  return PROP.ACTIVE;
  
}

void FILE_WATCH::reset()
// Simple close the stream then reopen, effectivly clearing stram errors.
// Also, clears the positon variable so the next attempt to get line or
//  check line avail will cause the routine to start reading from the 
//  beginning.
{
  close();
  LINE_AVAIL = false;
  POSITION = 0;
  open();
}

long FILE_WATCH::get_file_size()
// Get the size of file with name and path defined by the class var named 
//  FILENAME.
{
  if (check_file_status() == true)
  {
    struct stat stat_buf;
    int rc = stat(FILENAME.c_str(), &stat_buf);
    return rc == 0 ? stat_buf.st_size : -1;
  }
  else
  {
    return 0;
  }
}

bool FILE_WATCH::file_time_changed()
// Returns true if file write time has changed from 
//  previous check.
{
  bool boo_return = false;
  time_t write_time;

  //double seconds;

  if (check_file_status() == true)
  {
    boost::filesystem::path path_and_filename{FILENAME};

    write_time = last_write_time(path_and_filename);

    if(LAST_WRITE_TIME == write_time)
    {
      boo_return = false;
    }
    else
    {
      LAST_WRITE_TIME = write_time;
      boo_return = true;
    }
  }

  return boo_return;
}

bool FILE_WATCH::file_changed()
// Returns true if file size has changed.
// Seperate behavior for Watch Size and or Watch Time Write.

// If Watch Time:
//  Stores time.

// If Watch Size:
// Sets the new FILE_SIZE if changed.
// Complete reset of the entire FILE_WATCH if 
//  the read position is past the end of file because 
//  the file has had content removed.
{
  bool boo_return = false;

  // Watch for File Write Change.
  if(PROP.WATCH_TIME_CHANGE == true)
  {
    if(file_time_changed() == true)
    {
      CHANGED = true;
    }
  }

  // Watch for File Size Change.
  if(PROP.WATCH_SIZE_CHANGE == true && CHANGED == false)
  {
    // Get file size;
    long new_file_size = get_file_size();

    // Reset if position is outside file or file read has failed.
    if (POSITION > new_file_size || (LOG_FILE.fail() == true))
    {
      reset();
      //return false; 
    }
    
    // Compair file size to history.
    if (FILE_SIZE == new_file_size)
    {
      //return false;
    }
    else
    {
      FILE_SIZE = new_file_size;
      CHANGED =  true;
    }
  }

  boo_return = CHANGED;

  CHANGED = false;

  return boo_return;
}

void FILE_WATCH::start(string Filename)
{
  FILENAME = Filename;
}

void FILE_WATCH::stop()
{
  close();
}

bool FILE_WATCH::line_avail()
// Returns true if a line is available to be read.
{
  if (LINE_AVAIL == true || file_changed() == true)
  {
    LINE_AVAIL = true;
  }
  
  return LINE_AVAIL;
}

bool FILE_WATCH::changed()
// Returns true if file changed.
{
  if (file_changed() == true)
  {
    return true;
  }
  else
  {
    return false;
  }
}

string FILE_WATCH::get_next_line()
// Returns the newly added line of the watch file.
{
  //string containing new line.
  string str_read_line = "";

  if(check_file_status() == true)
  {
    if(LINE_AVAIL == true && PROP.WATCH_TIME_CHANGE == true)
    {
      if(LOG_FILE.is_open() == false)
      {
        LOG_FILE.open(FILENAME);
      }

      getline(LOG_FILE, str_read_line);

      if (LOG_FILE.eof())
      {
        LINE_AVAIL = false;
        LOG_FILE.close();
      }
    }
    else if (LINE_AVAIL == true && PROP.WATCH_SIZE_CHANGE == true)
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
  }
  
  // Return the read line.
  return str_read_line;
}

bool check_create_working_dir(string Directory)
{
  // Not Coded
  return false;
}

string file_to_string(string Dir_Filename, bool &Success)
{
  fstream fsFile;

  string File_String = "";

  bool booSuccess = false;
  bool booActive = false;

  fsFile.open(Dir_Filename, ios::in);

  if (!fsFile)
  {
    booActive = false;
  }
  else 
  {
    booActive = true;
  }

  if (booActive == true)
  {
    string strRead = "";

    while(booActive == true)
    {
      getline(fsFile,strRead);

      File_String = File_String + strRead;

      if(fsFile.eof())
      {
        booActive = false;
        booSuccess = true;
      }
    }
  }

  Success = booSuccess;
  return File_String;
}

string file_to_string(string Dir_Filename)
{
  bool success = false;
  return file_to_string(Dir_Filename, success);
}

bool deque_string_to_file(string Dir_Filename, deque<string> &qFile, bool Append)
{
  fstream fsFile;
  bool booSuccess = false;

  bool booActive = false;

  if (Append == true)
  {
    fsFile.open(Dir_Filename, ios::app);
  }
  else
  {
    fsFile.open(Dir_Filename, ios::out);
  }

  if (!fsFile)
  {
    booActive = false;
    booSuccess = false;
  }
  else 
  {
    booActive = true;
  }

  if (booActive == true)
  {
    if (Append == true)
    {
      for (int pos = 0; pos < qFile.size(); pos++)
      {
        fsFile << qFile[pos];
        fsFile << endl;
      }
      fsFile << endl;
      fsFile.close();
      booSuccess = true;
    }
    else
    {
      while(qFile.empty() == false)
      {
        fsFile << qFile.front();
        fsFile << endl;
        qFile.pop_front();
      }
      fsFile << endl;
      fsFile.close();
      booSuccess = true;
    }
  }

  return booSuccess;
}

bool file_to_deque_string(string Dir_Filename, deque<string> &qFile)
{
  fstream fsFile;

  bool booSuccess = false;
  bool booActive = false;

  fsFile.open(Dir_Filename, ios::in);

  if (!fsFile)
  {
    booActive = false;
  }
  else 
  {
    booActive = true;
  }

  if (booActive == true)
  {
    string strRead = "";

    while(booActive == true)
    {
      getline(fsFile,strRead);

      qFile.push_back(strRead);

      if(fsFile.eof())
      {
        booActive = false;
        booSuccess = true;
      }
    }
  }

  return booSuccess;
}



#endif