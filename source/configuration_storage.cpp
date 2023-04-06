// ***************************************************************************************
// *
// *    Core       | Everything within this document is proprietary to Core Dynamics.
// *    Dynamics   | Any unauthorized duplication will be subject to prosecution.
// *
// *    Department : (R+D)^2                        Name: configuration_storage.cpp
// *       Sub Dept: Programming
// *    Location ID: 856-45B
// *                                                      (c) 2856 - 2858 Core Dynamics
// ***************************************************************************************


#ifndef CONFIGURATION_STORAGE_CPP
#define CONFIGURATION_STORAGE_CPP

#include "configuration_storage.h"

using namespace std;

// -------------------------------------------------------------------------------------

// Load Configuration
bool load_json_configuration(Console &cons, system_data &sdSysData, string Directory, string Filename)
{
  JSON_INTERFACE configuration_json;

  bool ret_success = false;

  string json_configuration_file = file_to_string(Directory + Filename, ret_success);

  if (ret_success == true)
  {
    ret_success = configuration_json.load_json_from_string(json_configuration_file);

    if (ret_success == true)
    {
      int switches_pos = configuration_json.ROOT.find_label_pos("Switches");

      sdSysData.CONFIG.iNUM_SWITCHES = configuration_json.ROOT.DATA[switches_pos].DATA.size();
      
      for (int pos = 0; pos < sdSysData.CONFIG.iNUM_SWITCHES; pos++)
      {
        //cons.printwait("switches parse");
        switch_map tmpsm;
        tmpsm.pin = string_to_int(configuration_json.ROOT.DATA[switches_pos].DATA[pos].value());
        sdSysData.CONFIG.vSWITCH_PIN_MAP.push_back(tmpsm);
      }

      int leds_pos = configuration_json.ROOT.find_label_pos("LEDs");
      
      // LED 
      if (leds_pos > -1)
      { 
        // System
        int mid = 0;
        string mname;
        v_profile_strip_main tmainstripprofile;

        // clear preloads
        sdSysData.CONFIG.LED_MAIN.clear();

        tmainstripprofile.set(string_to_int(configuration_json.ROOT.DATA[leds_pos].value_from_list("SyStem_ID")), 
                              configuration_json.ROOT.DATA[leds_pos].value_from_list("SyStem_Name"));
        sdSysData.CONFIG.LED_MAIN.push_back(tmainstripprofile);

        // LED Groups
        int led_group_pos = configuration_json.ROOT.DATA[leds_pos].find_label_pos("LED Groups");

        for(int led_group=0; led_group < configuration_json.ROOT.DATA[leds_pos].DATA[led_group_pos].DATA.size(); led_group++)
        {
          sdSysData.CONFIG.LED_MAIN.at(0).add_group(
            string_to_int(configuration_json.ROOT.DATA[leds_pos].DATA[led_group_pos].DATA[led_group].value_from_list("LED_Group_ID")), 
            configuration_json.ROOT.DATA[leds_pos].DATA[led_group_pos].DATA[led_group].value_from_list("LED_Group_Name"));

          // Strip List
          int led_strip_group_pos = configuration_json.ROOT.DATA[leds_pos].DATA[led_group_pos].DATA[led_group].find_label_pos("Strip Group");

          for (int led_strip_pos = 0; led_strip_pos < configuration_json.ROOT.DATA[leds_pos].DATA[led_group_pos].DATA[led_group].DATA[led_strip_group_pos].DATA.size(); led_strip_pos++)
          {
            int sid = led_strip_pos;
            string sname = configuration_json.ROOT.DATA[leds_pos].DATA[led_group_pos].DATA[led_group].DATA[led_strip_group_pos].DATA[led_strip_pos].value_from_list("LED_Strip_Name");
            string sposition = configuration_json.ROOT.DATA[leds_pos].DATA[led_group_pos].DATA[led_group].DATA[led_strip_group_pos].DATA[led_strip_pos].value_from_list("Position");
            int sledcount = string_to_int(configuration_json.ROOT.DATA[leds_pos].DATA[led_group_pos].DATA[led_group].DATA[led_strip_group_pos].DATA[led_strip_pos].value_from_list("LED_Count"));
            
            bool sforward = false;
            bool sbot_at_start = false;

            if (configuration_json.ROOT.DATA[leds_pos].DATA[led_group_pos].DATA[led_group].DATA[led_strip_group_pos].DATA[led_strip_pos].value_from_list("Direction") == "Forward")
            {
              sforward = true;
            }
            else
            {
              sforward = false;
            }
            
            if (configuration_json.ROOT.DATA[leds_pos].DATA[led_group_pos].DATA[led_group].DATA[led_strip_group_pos].DATA[led_strip_pos].value_from_list("Type") == "Standing")
            {
              sbot_at_start = true;
            }
            else
            {
              sbot_at_start = false;
            }

            sdSysData.CONFIG.LED_MAIN.at(0).vLED_GROUPS.at(led_group).add_strip(sid, sname, sposition, sledcount, sforward, sbot_at_start);
          }
        }

        sdSysData.CONFIG.LED_MAIN.at(0).update_start_positions();

      }
    }
  }
  return ret_success;
}

// -------------------------------------------------------------------------------------
// Save Configuration
bool save_json_configuration(Console &cons, system_data &sdSysData, string Directory, string Filename)
{
  bool ret_success = false;

  deque<string> configuration_file_dq_string;

  JSON_INTERFACE configuration_json;

  JSON_ENTRY switches;
  JSON_ENTRY strips;
  JSON_ENTRY strip_group;
  JSON_ENTRY strip_list;
  JSON_ENTRY led_group;
  JSON_ENTRY car_group;

  // -------------------------------------------------------------------------------------

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
  
  // Create JSON Entry based on current settings

  // Switches
  for (int x=0; x < sdSysData.CONFIG.iNUM_SWITCHES; x++)
  {
    switches.create_label_value(quotify("Switch " + to_string(x)), to_string(sdSysData.CONFIG.vSWITCH_PIN_MAP.at(x).pin));
  }

  configuration_json.ROOT.put_json_in_set(quotify("Switches"), switches);
  switches.clear_data();
 
  // LEDs
  car_group.create_label_value(quotify("SyStem_Name"), quotify(sdSysData.CONFIG.LED_MAIN.at(0).strNAME));
  car_group.create_label_value(quotify("SyStem_ID"), to_string(sdSysData.CONFIG.LED_MAIN.at(0).intID));

  // Groups
  for(int x=0; x<sdSysData.CONFIG.LED_MAIN.at(0).vLED_GROUPS.size(); x++)
  {
    strip_group.clear_data();
    strip_group.create_label_value(quotify("LED_Group_Name"), quotify(sdSysData.CONFIG.LED_MAIN.at(0).vLED_GROUPS.at(x).strNAME));
    strip_group.create_label_value(quotify("LED_Group_ID"), to_string(sdSysData.CONFIG.LED_MAIN.at(0).vLED_GROUPS.at(x).intID));

    // Strips
    for(int y=0; y<sdSysData.CONFIG.LED_MAIN.at(0).vLED_GROUPS.at(x).vLED_STRIPS.size(); y++)
    {
      v_profile_strip strip;
      string write;
      strip = sdSysData.CONFIG.LED_MAIN.at(0).strip_info(x,y);

      //strips.clear_data();
      strips.create_label_value(quotify("LED_Strip_ID"), to_string(strip.intID));
      strips.create_label_value(quotify("LED_Strip_Name"), quotify(strip.strNAME));
      strips.create_label_value(quotify("Position"), quotify(strip.strPOSITION));
      strips.create_label_value(quotify("LED_Count"), to_string(strip.led_count()));

     // Forward or Backward
      if(strip.booFORWARD == true )
      {
        strips.create_label_value(quotify("Direction"), quotify("Forward"));
      }
      else
      {
        strips.create_label_value(quotify("Direction"), quotify("Forward"));
      }

      // Standing or Hanging
      if(strip.booBOT_AT_START == true )
      {
        strips.create_label_value(quotify("Type"), quotify("Standing"));
      }
      else
      {
        strips.create_label_value(quotify("Type"), quotify("Hanging"));
      }

      strip_list.put_json_in_list(strips);
      strips.clear_data();
    }

    strip_group.put_json_in_set(quotify("Strip Group"), strip_list);
    strip_list.clear_data();

    led_group.put_json_in_list(strip_group);
    strip_group.clear_data();
  }

  car_group.put_json_in_set(quotify("LED Groups"), led_group);
  led_group.clear_data();

  configuration_json.ROOT.put_json_in_set(quotify("LEDs"), car_group);
  car_group.clear_data();

  // Create string list of file
  configuration_json.json_print_build_to_string_deque(configuration_file_dq_string);
  
  // Write string list of file
  ret_success = deque_string_to_file(Directory+ Filename, configuration_file_dq_string, false);

  return ret_success;
}


// -------------------------------------------------------------------------------------
//  Running State

// Load Saved State
bool load_saved_running_state_json(Console &cons, system_data &sdSysData, string strFilename)
{
  JSON_INTERFACE state_json;

  CRGB color;

  string red = "";
  string green = "";
  string blue = "";

  string color_string = "";

  string color_desc = "";

  bool ret_success = false;

  string json_state_file = file_to_string(strFilename, ret_success);

  if (ret_success == true)
  {
    ret_success = state_json.load_json_from_string(json_state_file);

    if (ret_success == true)
    {
      cons.printi("  " + strFilename + " read success");
    
      // Parse the settings
      red = state_json.ROOT.value_from_list("red");
      green = state_json.ROOT.value_from_list("green");
      blue = state_json.ROOT.value_from_list("blue");

      color_string = red + "," + green + "," + blue;

      color = color.StringtoCRGB(color_string);

      color_desc = state_json.ROOT.value_from_list("description");

      cons.printi("  Setting running color to CRGB(" + color.CRGBtoString() + 
                                                  "), " + color_desc);                                          

      sdSysData.set_running_color(color , color_desc);
    }
  }

  if (ret_success == false)
  {
    cons.printi("  " + strFilename + " read error");
    cons.printi("  Setting running color to CRGB(32,32,32), White");
    color = CRGB(32,32,32);
    color_desc = "White";
    sdSysData.set_running_color(color , color_desc);
  }

  return ret_success;
}


// Save Saved State
bool save_running_state_json(Console &cons, system_data &sdSysData, string strFilename)
{
  JSON_INTERFACE state_json;
  deque<string> state_dq_string;

  bool ret_success = false;

  CRGB color = sdSysData.get_running_color();

  state_json.ROOT.create_label_value(quotify("red"), quotify(to_string((int)(color.r))));
  state_json.ROOT.create_label_value(quotify("green"), quotify(to_string((int)(color.g))));
  state_json.ROOT.create_label_value(quotify("blue"), quotify(to_string((int)(color.b))));
  state_json.ROOT.create_label_value(quotify("description"), quotify(sdSysData.get_running_color_str()));

  state_json.json_print_build_to_string_deque(state_dq_string);
  ret_success = deque_string_to_file(strFilename, state_dq_string, false);

  return ret_success;
}

// -------------------------------------------------------------------------------------
// Load Playlist
bool load_playlist_json(Console &cons, system_data &sdSysData, string strFilename)
{
  JSON_INTERFACE movies_json;

  bool ret_success = false;

  string json_movie_file = file_to_string(strFilename, ret_success);
  
  if (ret_success == true)
  {
    ret_success = movies_json.load_json_from_string(json_movie_file);

    if (ret_success == true)
    {
      cons.printi("  " + strFilename + " read success");

      for (int list = 0; list < movies_json.ROOT.DATA.size(); list++)
      {
        cons.the_player.Play_List.add_to_list(movies_json.ROOT.DATA[list].value());
      }
    }
  }

  if (ret_success == false)
  {
    cons.printi("  " + strFilename + " read error");
    cons.printi("  Playlist not loaded.");
  }

  return ret_success;
}



#endif