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

        for(int led_group=0; led_group < configuration_json.ROOT.DATA[leds_pos].DATA[led_group_pos].DATA[led_group].DATA.size(); led_group++)  // why -1
        {
          sdSysData.CONFIG.LED_MAIN.at(0).add_group(
            string_to_int(configuration_json.ROOT.DATA[leds_pos].DATA[led_group_pos].DATA[led_group].value_from_list("LED_Group_ID")), 
            configuration_json.ROOT.DATA[leds_pos].DATA[led_group_pos].DATA[led_group].value_from_list("LED_Group_Name"));

          // Strip List
          int led_strip_group_pos = configuration_json.ROOT.DATA[leds_pos].DATA[led_group_pos].DATA[led_group].find_label_pos("Strip Group");

          for (int led_strip_pos = 0; led_strip_pos < configuration_json.ROOT.DATA[leds_pos].DATA[led_group_pos].DATA[led_group].DATA[led_strip_group_pos].DATA[led_strip_pos].DATA.size(); led_strip_pos++)  // why -1
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
  deque<string> configuration_file_dq_string_debug;

  JSON_INTERFACE configuration_json;

  JSON_ENTRY switches;
  JSON_ENTRY strips;
  JSON_ENTRY strip_group;
  JSON_ENTRY strip_list;
  JSON_ENTRY led_group;
  JSON_ENTRY car_group;

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
  ret_success = deque_string_to_file(Directory+ Filename, configuration_file_dq_string);


  return ret_success;
}



#endif