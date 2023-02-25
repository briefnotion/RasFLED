// ***************************************************************************************
// *
// *    Core       | Everything within this document is proprietary to Core Dynamics.
// *    Dynamics   | Any unauthorized duplication will be subject to prosecution.
// *
// *    Department : (R+D)^2                        Name: files.h
// *       Sub Dept: Programming
// *    Location ID: 856-45B
// *                                                      (c) 2856 - 2858 Core Dynamics
// ***************************************************************************************

#ifndef FILES_H
#define FILES_H

// Standard Header Files
#include <fstream>
#include <iostream>
#include <string.h>
#include <deque>

// RASFled related header files
#include "helper.h"
#include "LEDstuff.h"
#include "stringthings.h"

#include "consoleanddata.h"

using namespace std;

/*  Notes:
    
    ios::app - Append Mode
    ios::ate - Opens for output then moves read write to end
    ios::in  - Read Mode
    ios::out - Write Mode
    ios::trunk- If exits, Truncate Mode

*/

// I never really commented any of these routines.  I wish I had, may have saved 
//  some time when I created the load playlist routines.  They dont belong here 
//  anyway.  So, Ill move em out later. 

class FILE_TO_STRING
{
  public:

  bool booRead_File(string strFilename, string &File_String);
};

class FILE_TO_DEQUE
{
  public:

  bool booRead_File(string strFilename, deque<string> &qFile);
};

class DEQUE_TO_FILE
{
  public:

  bool booSave_File(string strFilename, deque<string> &qFile);
};

class SETTING
{
  private:
  
  string ID = "";
  deque<string> Value;

  public:

  void set(string strSetting, deque<string> &strValue);

  string id();

  string value(int at);

  bool check(string strSetting);
};

class SETTINGS
{
  private:
  deque<SETTING> Settings;

  public:

  void set(string strSetting, deque<string> &strValues);

  int size();

  string id_at(int at);

  string value_at(int at, int intIndex);

  int exits_at(string strSetting);

  int exits_id_at(string strSetting, string strId);

  int exits_id_2_at(string strSetting, string strId1, string strId2);

  void store(SETTING &NewSetting);
  
  void parse_and_save_setting(string strSettingLine);
};

// -------------------------------------------------------------------------------------

void dump_qfile(Console &cons, deque<string> &qFile);

// -------------------------------------------------------------------------------------
//  Running State

// Load Saved State
bool load_saved_running_state(Console &cons, system_data &sdSysData, string strFilename);

// Save Saved State
bool save_running_state(Console &cons, system_data &sdSysData, string strFilename);

// -------------------------------------------------------------------------------------
// Load Playlist
bool load_playlist(Console &cons, system_data &sdSysData, string strFilename);



#endif