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

    // !!! NEED TO KICK OUT BLANK LINES !!!

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

    // !!! NEED TO KICK OUT BLANK LINES !!!

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

        loc = tmpSettings.exits_at("Size_Test_Strip");
        if(loc >= 0)
        {
            sdSysData.CONFIG.iLED_Size_Test_Strip = atoi(tmpSettings.value_at(loc,0).c_str());
        }

        // ----

        loc = tmpSettings.exits_at("Size_Door_Back_Driver");
        if(loc >= 0)
        {
            sdSysData.CONFIG.iLED_Size_Door_Back_Driver = atoi(tmpSettings.value_at(loc,0).c_str());
        }
        
        loc = tmpSettings.exits_at("Size_Door_Back_Passenger");
        if(loc >= 0)
        {
            sdSysData.CONFIG.iLED_Size_Door_Back_Passenger = atoi(tmpSettings.value_at(loc,0).c_str());
        }
        
        loc = tmpSettings.exits_at("Size_Door_Front_Driver");
        if(loc >= 0)
        {
            sdSysData.CONFIG.iLED_Size_Door_Front_Driver = atoi(tmpSettings.value_at(loc,0).c_str());
        }
        
        loc = tmpSettings.exits_at("Size_Door_Front_Passenger");
        if(loc >= 0)
        {
            sdSysData.CONFIG.iLED_Size_Door_Front_Passenger = atoi(tmpSettings.value_at(loc,0).c_str());
        }
        
        // ----

        loc = tmpSettings.exits_at("Size_Overhead_Back_Driver");
        if(loc >= 0)
        {
            sdSysData.CONFIG.iLED_Size_Overhead_Back_Driver = atoi(tmpSettings.value_at(loc,0).c_str());
        }
        
        loc = tmpSettings.exits_at("Size_Overhead_Back_Passenger");
        if(loc >= 0)
        {
            sdSysData.CONFIG.iLED_Size_Overhead_Back_Passenger = atoi(tmpSettings.value_at(loc,0).c_str());
        }
        
        loc = tmpSettings.exits_at("Size_Overhead_Front_Driver");
        if(loc >= 0)
        {
            sdSysData.CONFIG.iLED_Size_Overhead_Front_Driver = atoi(tmpSettings.value_at(loc,0).c_str());
        }
        
        loc = tmpSettings.exits_at("Size_Overhead_Front_Passenger");
        if(loc >= 0)
        {
            sdSysData.CONFIG.iLED_Size_Overhead_Front_Passenger = atoi(tmpSettings.value_at(loc,0).c_str());
        }

        // ----

        loc = tmpSettings.exits_at("Channel_Count");
        if(loc >= 0)
        {
            sdSysData.CONFIG.iNUM_CHANNELS = atoi(tmpSettings.value_at(loc,0).c_str());
        }

        // ----
        // Load Pin Switches

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

  
    // -------------------------------------------------------------------------------------
    // build qFile.
    qFile.push_back("Size_Test_Strip " + to_string(sdSysData.CONFIG.iLED_Size_Test_Strip));
    qFile.push_back("");

    qFile.push_back("Size_Door_Back_Driver " + to_string(sdSysData.CONFIG.iLED_Size_Door_Back_Driver));
    qFile.push_back("Size_Door_Back_Passenger " + to_string(sdSysData.CONFIG.iLED_Size_Door_Back_Passenger));
    qFile.push_back("Size_Door_Front_Driver " + to_string(sdSysData.CONFIG.iLED_Size_Door_Front_Driver));
    qFile.push_back("Size_Door_Front_Passenger " + to_string(sdSysData.CONFIG.iLED_Size_Door_Front_Passenger));
    qFile.push_back("");

    qFile.push_back("Size_Overhead_Back_Driver " + to_string(sdSysData.CONFIG.iLED_Size_Overhead_Back_Driver));
    qFile.push_back("Size_Overhead_Back_Passenger " + to_string(sdSysData.CONFIG.iLED_Size_Overhead_Back_Passenger));
    qFile.push_back("Size_Overhead_Front_Driver " + to_string(sdSysData.CONFIG.iLED_Size_Overhead_Front_Driver));
    qFile.push_back("Size_Overhead_Front_Passenger " + to_string(sdSysData.CONFIG.iLED_Size_Overhead_Front_Passenger));
    qFile.push_back("");

    qFile.push_back("Channel_Count " + to_string(sdSysData.CONFIG.iNUM_CHANNELS));

    qFile.push_back("");
    qFile.push_back("Switch_Count " + to_string(sdSysData.CONFIG.iNUM_SWITCHES));
    for (int x=0; x < sdSysData.CONFIG.iNUM_SWITCHES; x++)
    {
        qFile.push_back("Switch " + to_string(x) + " " + to_string(sdSysData.CONFIG.vSWITCH_PIN_MAP.at(x).pin));
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




#endif