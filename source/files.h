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
#include <queue>
#include <vector>


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

class FILE_TO_QUEUE
{
    public:

    bool booRead_File(string strFilename, queue<string> &qFile)
    {
        fstream fsFile;
        bool booSucess = false;

        bool booActive = false;

        fsFile.open(strFilename, ios::in);


        if (!fsFile)
        {
            booActive = false;
            booSucess = false;
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
                qFile.push(strRead);

                if(fsFile.eof())
                {
                    booActive = false;
                    booSucess = true;
                }
            }
        }

        return booSucess;

    }
};

class QUEUE_TO_FILE
{
    public:

    bool booSave_File(string strFilename, queue<string> &qFile)
    {
        fstream fsFile;
        bool booSucess = false;

        bool booActive = false;

        fsFile.open(strFilename, ios::out);


        if (!fsFile)
        {
            booActive = false;
            booSucess = false;
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
                qFile.pop();
            }
            fsFile << endl;
            fsFile.close();
            booSucess = true;
        }

        return booSucess;
    }
};

class SETTING
{
    private:
    
    string ID = "";
    vector<string> Value;

    public:

    void set(string strSetting, vector<string> &strValue)
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
    vector<SETTING> Settings;

    public:

    void set(string strSetting, vector<string> &strValues)
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

    void store(SETTING &NewSetting)
    {   
        Settings.push_back(NewSetting);
    }
    
    
    void parse_and_save_setting(string strSettingLine)
    {
        WORDLINE wlLine;
        SETTING setting;
        string strsetting = "";
        vector<string> values;

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
    cons.printi("Checking File System");
    cons.printi("  CHECK NOT IMPLEMENTED");
    string dir = FILES_DIRECTORY;
    cons.printi("    You must manually create " + dir + " if first time run.");
}

void dump_qfile(Console &cons, queue<string> &qFile)
// As the name implies.  Clears it out also.  For testing.
{
    while(qFile.empty() == false)
    {
        cons.printi(qFile.front());
        qFile.pop();
    }
}

// -------------------------------------------------------------------------------------
//  Running State

// Load Saved State
bool load_saved_running_state(Console &cons, system_data &sdSysData, string strFilename)
{
    FILE_TO_QUEUE ftqFile;
    queue<string> qFile;

    bool sucess = false;

    // !!! NEED TO KICK OUT BLANK LINES !!!

    SETTINGS tmpSettings;

    if (ftqFile.booRead_File(strFilename , qFile) == true)
    {
        CRGB color;
        cons.printi("  " + strFilename + " read suceesss");

        // Parse the settings
        while(qFile.empty()==false)
        {
            tmpSettings.parse_and_save_setting(qFile.front());
            qFile.pop();
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

        sucess = true;
    }
    else
    {
        cons.printi("  " + strFilename + " read error");
        cons.printi("  Setting running color to CRGB(32,32,32), White");
        sdSysData.set_running_color(CRGB(32,32,32), "White");

        sucess = false;
    }

    return sucess;
}


// Save Saved State
bool save_running_state(Console &cons, system_data &sdSysData, string strFilename)
{
    QUEUE_TO_FILE qtfFile;
    queue<string> qFile;

    bool sucess = false;

    // build qFile.
    qFile.push("runningcolor " + sdSysData.get_running_color().CRGBtoString() + " " + sdSysData.get_running_color_str());

    if(qtfFile.booSave_File(strFilename, qFile) == true)
    {
        cons.printi("  " + strFilename + " write sucess");
        sucess = true;
    }
    else
    {
        cons.printi("  " + strFilename + " write failed.");
        sucess = false;
    }

    return sucess;
}

// -------------------------------------------------------------------------------------
//  Configuration

// Load Configuration
bool load_configuration(Console &cons, system_data &sdSysData, string strFilename)
{
    FILE_TO_QUEUE ftqFile;
    queue<string> qFile;

    bool sucess = false;

    // !!! NEED TO KICK OUT BLANK LINES !!!

    SETTINGS tmpSettings;

    if (ftqFile.booRead_File(strFilename , qFile) == true)
    {
        CRGB color;
        cons.printi("  " + strFilename + " read suceesss");

        // Parse the settings
        while(qFile.empty()==false)
        {
            tmpSettings.parse_and_save_setting(qFile.front());
            qFile.pop();
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

        sucess = true;
    }
    else
    {
        sucess = false;
    }

    return sucess;
}

// Save Configuration
bool save_configuration(Console &cons, system_data &sdSysData, string strFilename)
{
    QUEUE_TO_FILE qtfFile;
    queue<string> qFile;

    bool sucess = false;

    // build qFile.
    qFile.push("Size_Test_Strip " + to_string(sdSysData.CONFIG.iLED_Size_Test_Strip));
    qFile.push("");

    qFile.push("Size_Door_Back_Driver " + to_string(sdSysData.CONFIG.iLED_Size_Door_Back_Driver));
    qFile.push("Size_Door_Back_Passenger " + to_string(sdSysData.CONFIG.iLED_Size_Door_Back_Passenger));
    qFile.push("Size_Door_Front_Driver " + to_string(sdSysData.CONFIG.iLED_Size_Door_Front_Driver));
    qFile.push("Size_Door_Front_Passenger " + to_string(sdSysData.CONFIG.iLED_Size_Door_Front_Passenger));
    qFile.push("");

    qFile.push("Size_Overhead_Back_Driver " + to_string(sdSysData.CONFIG.iLED_Size_Overhead_Back_Driver));
    qFile.push("Size_Overhead_Back_Passenger " + to_string(sdSysData.CONFIG.iLED_Size_Overhead_Back_Passenger));
    qFile.push("Size_Overhead_Front_Driver " + to_string(sdSysData.CONFIG.iLED_Size_Overhead_Front_Driver));
    qFile.push("Size_Overhead_Front_Passenger " + to_string(sdSysData.CONFIG.iLED_Size_Overhead_Front_Passenger));

    if(qtfFile.booSave_File(strFilename, qFile) == true)
    {
        cons.printi("  " + strFilename + " write sucess");
        sucess = true;
    }
    else
    {
        cons.printi("  " + strFilename + " write failed.");
        sucess = false;
    }

    return sucess;
}




#endif