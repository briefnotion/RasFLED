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

class FILE_TO_DEQUE
{
  public:

  bool booRead_File(string strFilename, deque<string> &qFile)
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

        //strFile = strFile + strRead;
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
};

class DEQUE_TO_FILE
{
  public:

  bool booSave_File(string strFilename, deque<string> &qFile)
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
};

class SETTING
{
  private:
  
  string ID = "";
  deque<string> Value;

  public:

  void set(string strSetting, deque<string> &strValue)
  {
    ID = strSetting;
    Value = strValue;
  }

  string id()
  {
    return ID;
  }

  
  string value(int at)
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
  

  bool check(string strSetting)
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
};

class SETTINGS
{
  private:
  deque<SETTING> Settings;

  public:

  void set(string strSetting, deque<string> &strValues)
  {
    SETTING setNewSetting;
    setNewSetting.set(strSetting, strValues);
    Settings.push_back(setNewSetting);
  }

  int size()
  {
    return Settings.size();
  }

  string id_at(int at)
  {
    return Settings.at(at).id();
  }

  string value_at(int at, int intIndex)
  {
    return Settings.at(at).value(intIndex);
  }

  int exits_at(string strSetting)
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

  int exits_id_at(string strSetting, string strId)
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

  int exits_id_2_at(string strSetting, string strId1, string strId2)
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

  void store(SETTING &NewSetting)
  {   
    Settings.push_back(NewSetting);
  }
  
  
  void parse_and_save_setting(string strSettingLine)
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
};

// -------------------------------------------------------------------------------------

void check_create_working_dir(Console &cons)
{
  cons.printi("  Checking File System");
  cons.printi("    CHECK NOT IMPLEMENTED");
  string dir = FILES_DIRECTORY;
  cons.printi("      You must manually create " + dir + " if first time run.");
}

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
//  Configuration

// Load Configuration
bool load_configuration(Console &cons, system_data &sdSysData, string strFilename)
{
  FILE_TO_DEQUE ftqFile;
  deque<string> qFile;

  bool success = false;

  // !!! REVISE NEED TO KICK OUT BLANK LINES

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

    loc = tmpSettings.exits_at("Switch_Count");
    if(loc >= 0)
    {
      sdSysData.CONFIG.iNUM_SWITCHES = atoi(tmpSettings.value_at(loc,0).c_str());
    }      

    for(int x=0; x<sdSysData.CONFIG.iNUM_SWITCHES; x++)
    {
      loc = tmpSettings.exits_id_at("Switch", to_string(x));
      if (loc >= 0)
      {
        switch_map tmpsm;
        tmpsm.pin = atoi(tmpSettings.value_at(loc,1).c_str());
        
        sdSysData.CONFIG.vSWITCH_PIN_MAP.push_back(tmpsm);
      }
    }

    // ----
    // Load LED Strip Configuration
    loc = tmpSettings.exits_at("LED_Main");
    if(loc >0)
    {
      int mid = 0;
      string mname = tmpSettings.value_at(loc,1);

      v_profile_strip_main tmainstripprofile;
      
      tmainstripprofile.set(mid, mname);
      sdSysData.CONFIG.LED_MAIN.push_back(tmainstripprofile);
      
      loc = tmpSettings.exits_at("LED_Group_Count");
      if(loc >= 0)
      {
        int group_count = atoi(tmpSettings.value_at(loc,0).c_str());
        for(int x=0; x<group_count; x++)
        {
          loc = tmpSettings.exits_id_at("LED_Group_ID", to_string(x));
          if(loc >0)
          {
            int gid = x;
            string gname = tmpSettings.value_at(loc,1);

            sdSysData.CONFIG.LED_MAIN.at(0).add_group(gid, gname);

            loc = tmpSettings.exits_id_at("LED_Strip_Count", to_string(x));
            if(loc >0)
            {   
              int strip_count = atoi(tmpSettings.value_at(loc,1).c_str());
              for(int y=0; y<strip_count; y++)
              {
                loc = tmpSettings.exits_id_2_at("LED_Strip_ID", to_string(x), to_string(y));
                if(loc >0)
                {
                  int sid = y;
                  string sname = tmpSettings.value_at(loc,2);
                  string sposition = tmpSettings.value_at(loc,3);
                  int sledcount = atoi(tmpSettings.value_at(loc,4).c_str());

                  bool sforward = false;
                  bool sbot_at_start = false;

                  if (tmpSettings.value_at(loc,5) == "Forward")
                  {
                    sforward = true;
                  }
                  else
                  {
                    sforward = false;
                  }
                  
                  if (tmpSettings.value_at(loc,6) == "Standing")
                  {
                    sbot_at_start = true;
                  }
                  else
                  {
                    sbot_at_start = false;
                  }

                  sdSysData.CONFIG.LED_MAIN.at(0).vLED_GROUPS.at(x).add_strip(sid, sname, sposition, sledcount, sforward, sbot_at_start);
                }
              }
            }
          }
        }
      }
      sdSysData.CONFIG.LED_MAIN.at(0).update_start_positions();
    }  

    success = true;
  }
  else
  {
    success = false;
  }

  return success;
}

// -------------------------------------------------------------------------------------
// Save Configuration
bool save_configuration(Console &cons, system_data &sdSysData, string strFilename)
// This routine will run only onece. And, only if the configuration file doesnt exist.
{
  DEQUE_TO_FILE qtfFile;
  deque<string> qFile;

  bool success = false;

  // Set Default Settings

  // build pinmap
    // On off buttons, door sensors, switches.
  switch_map  PINs;
  PINs.pin    = 22;      // GPIO.22 - Pin 31 - Hardware Open Close Door Sensor 0
  sdSysData.CONFIG.vSWITCH_PIN_MAP.push_back(PINs);
  PINs.pin    = 23;      // GPIO.23 - Pin 33 - Hardware Open Close Door Sensor 1
  sdSysData.CONFIG.vSWITCH_PIN_MAP.push_back(PINs);
  PINs.pin    = 24;      // GPIO.24 - Pin 35 - Hardware Open Close Door Sensor 2
  sdSysData.CONFIG.vSWITCH_PIN_MAP.push_back(PINs);
  PINs.pin    = 25;      // GPIO.25 - Pin 37 - Hardware Open Close Door Sensor 3
  sdSysData.CONFIG.vSWITCH_PIN_MAP.push_back(PINs);

  // build led main, groups, and strips
  // build led main
  v_profile_strip_main tmp_led_main;
  tmp_led_main.set(0, "Car");
  sdSysData.CONFIG.LED_MAIN.push_back(tmp_led_main);

  // build led groups
  sdSysData.CONFIG.LED_MAIN.at(0).add_group(0, "Back_Driver");
  sdSysData.CONFIG.LED_MAIN.at(0).add_group(1, "Front_Driver");
  sdSysData.CONFIG.LED_MAIN.at(0).add_group(2, "Back_Passenger");
  sdSysData.CONFIG.LED_MAIN.at(0).add_group(3, "Front_Passenger");

  // build led strips

      // Quick Build Reference
  int iLED_Size_Door_Back_Driver          = 70;
  int iLED_Size_Door_Back_Passenger       = 70;
  int iLED_Size_Door_Front_Driver         = 66;
  int iLED_Size_Door_Front_Passenger      = 66;

  int iLED_Size_Overhead_Back_Driver      = 52;
  int iLED_Size_Overhead_Back_Passenger   = 52;
  int iLED_Size_Overhead_Front_Driver     = 52;
  int iLED_Size_Overhead_Front_Passenger  = 52;

      // Back Driver
  sdSysData.CONFIG.LED_MAIN.at(0).vLED_GROUPS.at(0).add_strip(0,"Door", "Back", iLED_Size_Door_Back_Driver, true, true);
  sdSysData.CONFIG.LED_MAIN.at(0).vLED_GROUPS.at(0).add_strip(1,"Overhead", "Back", iLED_Size_Overhead_Back_Driver, true, true);

      // Front Driver
  sdSysData.CONFIG.LED_MAIN.at(0).vLED_GROUPS.at(1).add_strip(0,"Overhead", "Front", iLED_Size_Overhead_Front_Driver, true, false);
  sdSysData.CONFIG.LED_MAIN.at(0).vLED_GROUPS.at(1).add_strip(1,"Door", "Front", iLED_Size_Door_Front_Driver, true, true);
  
      // Back Passenger
  sdSysData.CONFIG.LED_MAIN.at(0).vLED_GROUPS.at(2).add_strip(0,"Door", "Back", iLED_Size_Door_Back_Passenger, true, true);
  sdSysData.CONFIG.LED_MAIN.at(0).vLED_GROUPS.at(2).add_strip(1,"Overhead", "Back", iLED_Size_Overhead_Back_Passenger, true, true);

      // Front Passenger
  sdSysData.CONFIG.LED_MAIN.at(0).vLED_GROUPS.at(3).add_strip(0,"Overhead", "Front", iLED_Size_Overhead_Front_Passenger, true, false);
  sdSysData.CONFIG.LED_MAIN.at(0).vLED_GROUPS.at(3).add_strip(1,"Door", "Front", iLED_Size_Door_Front_Passenger, true, true);
  
  sdSysData.CONFIG.LED_MAIN.at(0).update_start_positions();

  // -------------------------------------------------------------------------------------
  // build qFile.
  qFile.push_back("");
  qFile.push_back("* ------------------------------");
  qFile.push_back("* Switch Configuration");
  qFile.push_back("*   - Switch ID PIN");
  qFile.push_back("Switch_Count " + to_string(sdSysData.CONFIG.iNUM_SWITCHES));
  for (int x=0; x < sdSysData.CONFIG.iNUM_SWITCHES; x++)
  {
      qFile.push_back("Switch " + to_string(x) + " " + to_string(sdSysData.CONFIG.vSWITCH_PIN_MAP.at(x).pin));
  }

  qFile.push_back("");
  qFile.push_back("* ------------------------------");
  qFile.push_back("* Strip Configuration");

  qFile.push_back("LED_Main " + to_string(sdSysData.CONFIG.LED_MAIN.at(0).intID) + " " + sdSysData.CONFIG.LED_MAIN.at(0).strNAME);
  qFile.push_back("");

  qFile.push_back("LED_Group_Count " + to_string(sdSysData.CONFIG.LED_MAIN.at(0).vLED_GROUPS.size()));
  for(int x=0; x<sdSysData.CONFIG.LED_MAIN.at(0).vLED_GROUPS.size(); x++)
  {
    qFile.push_back("  LED_Group_ID " + to_string(sdSysData.CONFIG.LED_MAIN.at(0).vLED_GROUPS.at(x).intID)+ " " + 
                        sdSysData.CONFIG.LED_MAIN.at(0).vLED_GROUPS.at(x).strNAME);

    qFile.push_back("    LED_Strip_Count " + to_string(x) + " " +
                        to_string(sdSysData.CONFIG.LED_MAIN.at(0).vLED_GROUPS.at(x).vLED_STRIPS.size()));
    for(int y=0; y<sdSysData.CONFIG.LED_MAIN.at(0).vLED_GROUPS.at(x).vLED_STRIPS.size(); y++)
    {
      //set(int intId, string strName, string strPosition, int intStart_Pos, bool forward, bool bot_at_start)
      v_profile_strip strip;
      string write;
      strip = sdSysData.CONFIG.LED_MAIN.at(0).strip_info(x,y);

      write = "      LED_Strip_ID " + to_string(x) + " " + to_string(strip.intID);
      write = write + " " + strip.strNAME + " " + strip.strPOSITION;
      write = write + " " + to_string(strip.led_count());

      // Forward or Backward
      if(strip.booFORWARD == true )
      {
        write = write + " Forward";
      }
      else
      {
        write = write + " Backward";
      }

      // Standing or Hanging
      if(strip.booBOT_AT_START == true )
      {
        write = write + " Standing";
      }
      else
      {
        write = write + " Hanging";
      }

      qFile.push_back(write);
    }
  }


  // -------------------------------------------------------------------------------------
  // Save qFile
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


// -------------------------------------------------------------------------------------
class FILE_LOG_READER
// Watches a log file and returns lines added through the get_next_line function.
//  !!! If the first character in the returned line is cr then the first 2 characters 
//        will be removed in the get line return statement.
{
  private:
  ifstream LOG_FILE;

  string FILENAME = "";

  int REMAINING = 0;
  bool LINE_AVAIL = false;

  streampos POSITION;

  void close_then_reopen()
  {
    close();
    open(FILENAME);
  }

  void reset()
  {
    close();
    REMAINING = 0;
    LINE_AVAIL = false;
    POSITION = 0;
    open(FILENAME);
  }

  bool remaining_changed()
  // Returns true if remaining charateres value changed.
  {
    streampos end;

    LOG_FILE.seekg (0, ios::end);
    end = LOG_FILE.tellg();

    REMAINING = end - POSITION;
    
    LOG_FILE.seekg(POSITION);

    if ((REMAINING <0) || (LOG_FILE.fail() == true))
    {
      reset();
      return false;
    }
    else if (REMAINING > 0)
    {
      LINE_AVAIL = true;
      return true;
    }
    else
    {
      return false;
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
    LINE_AVAIL = remaining_changed();
    
    return LINE_AVAIL;
  }

  string get_next_line()
  // Returns the newly added line of the watch file.
  {
    string str_read_line = "";
    if (LINE_AVAIL == true)
    {
      LOG_FILE.seekg(POSITION);
      getline(LOG_FILE, str_read_line);
      POSITION = LOG_FILE.tellg();
    }

    /*
    if (str_read_line.back() == 0)
    {
      POSITION = (int)POSITION -1;
    }
    */

    if (LOG_FILE.eof())
    {
      //str_read_line = "EOF " + to_string((int)str_read_line.back()) + " " + to_string(POSITION) + " " + str_read_line;
      LINE_AVAIL = false;
      close_then_reopen();
    }
    else if (LOG_FILE.fail())
    {
      reset();
    }
    else
    {
      //str_read_line = "--- " + to_string((int)str_read_line.back()) + " " + to_string(POSITION) + " " + str_read_line;
    }
    
    //return to_string((int)str_read_line.back()) + " " + to_string(POSITION) + " " + str_read_line;
    return str_read_line;
  }

};



#endif