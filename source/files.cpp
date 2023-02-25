// ***************************************************************************************
// *
// *    Core       | Everything within this document is proprietary to Core Dynamics.
// *    Dynamics   | Any unauthorized duplication will be subject to prosecution.
// *
// *    Department : (R+D)^2                        Name: files.cpp
// *       Sub Dept: Programming
// *    Location ID: 856-45B
// *                                                      (c) 2856 - 2858 Core Dynamics
// ***************************************************************************************

#ifndef FILES_CPP
#define FILES_CPP

#include "files.h"

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


bool FILE_TO_STRING::booRead_File(string strFilename, string &File_String)
{
  fstream fsFile;
  bool booSuccess = false;

  bool booActive = false;

  fsFile.open(strFilename, ios::in);


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

  return booSuccess;

}


bool FILE_TO_DEQUE::booRead_File(string strFilename, deque<string> &qFile)
{
  fstream fsFile;
  bool booSuccess = false;

  bool booActive = false;

  fsFile.open(strFilename, ios::in);


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
    
    fsFile.close();
  }

  return booSuccess;

}


bool DEQUE_TO_FILE::booSave_File(string strFilename, deque<string> &qFile)
{
  fstream fsFile;
  bool booSuccess = false;

  bool booActive = false;

  fsFile.open(strFilename, ios::out);

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

  return booSuccess;
}


void SETTING::set(string strSetting, deque<string> &strValue)
{
  ID = strSetting;
  Value = strValue;
}

string SETTING::id()
{
  return ID;
}


string SETTING::value(int at)
{
  if(at < Value.size())
  {
    return Value.at(at);
  }
  else
  {
    return ("");
  }
}


bool SETTING::check(string strSetting)
{
  if(ID == strSetting)
  {
    return true;
  }
  else
  {
    return false;
  }
}


void SETTINGS::set(string strSetting, deque<string> &strValues)
{
  SETTING setNewSetting;
  setNewSetting.set(strSetting, strValues);
  Settings.push_back(setNewSetting);
}

int SETTINGS::size()
{
  return Settings.size();
}

string SETTINGS::id_at(int at)
{
  return Settings.at(at).id();
}

string SETTINGS::value_at(int at, int intIndex)
{
  return Settings.at(at).value(intIndex);
}

int SETTINGS::exits_at(string strSetting)
{
  int at = -1;
  for (int x=0; x<Settings.size(); x++)
  {
    if(Settings.at(x).check(strSetting) == true)
    {
      at = x;
    }
  }
  return at;
}

int SETTINGS::exits_id_at(string strSetting, string strId)
{
  int at = -1;
  for (int x=0; x<Settings.size(); x++)
  {
    if((Settings.at(x).check(strSetting) == true) && (Settings.at(x).value(0) == strId))
    {
      at = x;
    }
  }
  return at;
}

int SETTINGS::exits_id_2_at(string strSetting, string strId1, string strId2)
{
  int at = -1;
  for (int x=0; x<Settings.size(); x++)
  {
    if((Settings.at(x).check(strSetting) == true) && (Settings.at(x).value(0) == strId1) && (Settings.at(x).value(1) == strId2))
    {
      at = x;
    }
  }
  return at;
}

void SETTINGS::store(SETTING &NewSetting)
{   
  Settings.push_back(NewSetting);
}


void SETTINGS::parse_and_save_setting(string strSettingLine)
{
  WORDLINE wlLine;
  SETTING setting;
  string strsetting = "";
  deque<string> values;

  wlLine.storeline(strSettingLine);

  strsetting = wlLine.pop();

  while(wlLine.size() > 0)
  {
    values.push_back(wlLine.pop());
  }

  setting.set(strsetting, values);
  Settings.push_back(setting);
}

// -------------------------------------------------------------------------------------

void dump_qfile(Console &cons, deque<string> &qFile)
// As the name implies.  Clears it out also.  For testing.
{
  while(qFile.empty() == false)
  {
    cons.printi(qFile.front());
    qFile.pop_front();
  }
}

// -------------------------------------------------------------------------------------
//  Running State

// Load Saved State
bool load_saved_running_state(Console &cons, system_data &sdSysData, string strFilename)
{
  FILE_TO_DEQUE ftqFile;
  deque<string> qFile;

  bool success = false;

  // REVISE !!! NEED TO KICK OUT BLANK LINES

  SETTINGS tmpSettings;

  if (ftqFile.booRead_File(strFilename , qFile) == true)
  {
    CRGB color;
    cons.printi("  " + strFilename + " read success");

    // Parse the settings
    while(qFile.empty()==false)
    {
      tmpSettings.parse_and_save_setting(qFile.front());
      qFile.pop_front();
    }

    // Find and load the settings
    int loc = 0;
    // ----

    loc = tmpSettings.exits_at("runningcolor");
    if(loc >= 0)
    {
      color = color.StringtoCRGB(tmpSettings.value_at(loc,0));
      cons.printi("  Setting running color to CRGB(" + to_string(color.r) + "," + to_string(color.g) + "," + to_string(color.b) + "), " + tmpSettings.value_at(loc,1));
      sdSysData.set_running_color(color , tmpSettings.value_at(loc,1));   
    }
    else
    {
      color = CRGB(32,32,32);
      cons.printi("  Creating setting running color to CRGB(" + to_string(color.r) + "," + to_string(color.g) + "," + to_string(color.b) + "), " + "White");
      sdSysData.set_running_color(color , "White");   
    }
    
    // ----

    success = true;
  }
  else
  {
    cons.printi("  " + strFilename + " read error");
    cons.printi("  Setting running color to CRGB(32,32,32), White");
    sdSysData.set_running_color(CRGB(32,32,32), "White");

    success = false;
  }

  return success;
}


// Save Saved State
bool save_running_state(Console &cons, system_data &sdSysData, string strFilename)
{
  DEQUE_TO_FILE qtfFile;
  deque<string> qFile;

  bool success = false;

  // build qFile.
  qFile.push_back("runningcolor " + sdSysData.get_running_color().CRGBtoString() + " " + sdSysData.get_running_color_str());

  if(qtfFile.booSave_File(strFilename, qFile) == true)
  {
    cons.printi("  " + strFilename + " write success");
    success = true;
  }
  else
  {
    cons.printi("  " + strFilename + " write failed.");
    success = false;
  }

  return success;
}

// -------------------------------------------------------------------------------------
// Load Playlist
bool load_playlist(Console &cons, system_data &sdSysData, string strFilename)
{
  FILE_TO_DEQUE ftqFile;
  deque<string> qFile;

  bool success = false;

  // REVISE !!! NEED TO KICK OUT BLANK LINES

  SETTINGS tmpSettings;

  if (ftqFile.booRead_File(strFilename , qFile) == true)
  {
    CRGB color;
    cons.printi("  " + strFilename + " read success");

    // Parse the settings
    while(qFile.empty()==false)
    {
      tmpSettings.parse_and_save_setting(qFile.front());
      qFile.pop_front();
    }

    // Find and load the settings
    int loc = 0;

    loc = tmpSettings.exits_at("playlist");
    if(loc >= 0)
    {
      for(int x=loc+1; x < tmpSettings.size() ; x++)
      {
        //cons.printi(tmpSettings.id_at(x));
        cons.the_player.Play_List.add_to_list(tmpSettings.id_at(x));
      }

      return true;
    }
  }
  else
  {
    cons.printi("  " + strFilename + " read error");
    cons.printi("  Playlist not loaded.");

    success = false;
  }

  return success;
}




#endif