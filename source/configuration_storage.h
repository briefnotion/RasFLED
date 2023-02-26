// ***************************************************************************************
// *
// *    Core       | Everything within this document is proprietary to Core Dynamics.
// *    Dynamics   | Any unauthorized duplication will be subject to prosecution.
// *
// *    Department : (R+D)^2                        Name: configuration_storage.h
// *       Sub Dept: Programming
// *    Location ID: 856-45B
// *                                                      (c) 2856 - 2859 Core Dynamics
// ***************************************************************************************

#ifndef CONFIGURATION_STORAGE_H
#define CONFIGURATION_STORAGE_H

// Standard Header Files
#include <deque>

#include "json_interface.h"
#include "consoleanddata.h"
#include "LEDstuff.h"

using namespace std;

// -------------------------------------------------------------------------------------
//  Configuration

// Load Configuration
bool load_json_configuration(Console &cons, system_data &sdSysData, string Directory, string Filename);

// -------------------------------------------------------------------------------------
// Save Configuration
bool save_json_configuration(Console &cons, system_data &sdSysData, string Directory, string Filename);

// -------------------------------------------------------------------------------------
//  Running State

// Load Saved State
bool load_saved_running_state_json(Console &cons, system_data &sdSysData, string strFilename);

// Save Saved State
bool save_running_state_json(Console &cons, system_data &sdSysData, string strFilename);

// -------------------------------------------------------------------------------------
// Load Playlist
bool load_playlist_json(Console &cons, system_data &sdSysData, string strFilename);




#endif