// ***************************************************************************************
// *
// *    Core       | Everything within this document is proprietary to Core Dynamics.
// *    Dynamics   | Any unauthorized duplication will be subject to prosecution.
// *
// *    Department : (R+D)^2                        Name: animations_handler.cpp
// *       Sub Dept: Programming
// *    Location ID: 856-45B
// *                                                      (c) 2856 - 2858 Core Dynamics
// ***************************************************************************************

#ifndef ANIMATIONS_HANDLER_CPP
#define ANIMATIONS_HANDLER_CPP

#include "animations_handler.h"


using namespace std;

// -------------------------------------------------------------------------------------
// Functions


/*
void call_animation(Console &cons, system_data &sdSysData, unsigned long tmeCurrentTime, 
                    timed_event teEvent[],                   
                    string Collection_Name, string Animation_Name)
{
  cons.printwait("Animation");
}
*/

bool ANIMATION_HANDLER::load_collections(string Directory, string Filename)
{
  return COLLECTION.load_collections(Directory, Filename);
}

void call_animation(Console &cons, system_data &sdSysData, 
                    unsigned long tmeCurrentTime, timed_event teEvent[],                   
                      string Collection_Name, string Animation_Name)
{

}

//call_animation(cons, sdSystem, tmeCurrentMillis, teEvents, "data" , "data");
 

#endif