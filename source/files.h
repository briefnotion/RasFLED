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


// RASFled related header files
#include "helper.h"
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
                qFile.pop();
            }
            fsFile << endl;
            fsFile.close();
            booSucess = true;
        }

        return booSucess;
    }
};

// -------------------------------------------------------------------------------------

void dump_qfile(Console &cons, queue<string> &qFile)
// As the name implies.  Clears it out also.  For testing.
{
    while(qFile.empty() == false)
    {
        cons.printi(qFile.front());
        qFile.pop();
    }
}

// Load Saved State
bool load_saved_running_state(Console &cons, system_data &sdSysData, string strFilename)
{
    FILE_TO_QUEUE ftqFile;
    queue<string> qFile;

    if (ftqFile.booRead_File(strFilename , qFile) == true)
    {
        CRGB color;
        cons.printi("  " + strFilename + " read suceesss");

        color = color.StringtoCRGB(qFile.front());

        cons.printi("  Setting running color to CRGB(" + to_string(color.r) + "," + to_string(color.g) + "," + to_string(color.b) + "), Unknown");
        sdSysData.set_running_color(color , "Unknown");   
    }
    else
    {
        cons.printi("  " + strFilename + " read error");
        cons.printi("  Setting running color to CRGB(32,32,32), White");
        sdSysData.set_running_color(CRGB(32,32,32), "White");
    }

    return true;
}

bool save_running_state(Console &cons, system_data &sdSysData, string strFilename)
{
    QUEUE_TO_FILE qtfFile;
    queue<string> qFile;

    // build qFile.
    qFile.push(sdSysData.get_running_color().CRGBtoString());

    if(qtfFile.booSave_File(strFilename, qFile) == true)
    {
        cons.printi("  " + strFilename + " write sucess");
    }
    else
    {
        cons.printi("  " + strFilename + " write unknown");
    }

    return true;
}




#endif