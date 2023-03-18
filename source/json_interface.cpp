// ***************************************************************************************
// *
// *    Core       | Everything within this document is proprietary to Core Dynamics.
// *    Dynamics   | Any unauthorized duplication will be subject to prosecution.
// *
// *    Department : (R+D)^2                        Name: json_interface.cpp
// *       Sub Dept: Programming
// *    Location ID: 856-45B
// *                                                      (c) 2856 - 2858 Core Dynamics
// ***************************************************************************************

#ifndef JSON_INTERFACE_CPP
#define JSON_INTERFACE_CPP

#include "json_interface.h"

using namespace std;

// -------------------------------------------------------------------------------------
//  JSON Class

// Needs:
//  Proper list length.
//  Traverse path.
//  Consolidate setlist setset
//  Quotation recognition for commas in quotes
//  Less error prone.

// -------------------------------------------------------------------------------------
//  Supporting Functions

bool remove_opens_and_closes(string &Entry, char Open, char Close)
{
  bool ret_success = false;

  int start = 0;
  int last = 0;

  // Filter out Brackets.
  start = Entry.find(Open);
  if (start != std::string::npos)
  {
    last = Entry.find_last_of(Close);
    if (last != std::string::npos)
    {
      Entry = Entry.substr(start +1, last -1);
      ret_success = true;
    }
  }

  return ret_success;
}

string parse_label(string Text, int Label_Size)
{
  return Text.substr(0, Label_Size);
}

string parse_value(string Text, int Label_Size)
{
  return Text.erase(0, Label_Size +1);
}

int pos_of_first_non_space(int Start, string Text)
{
  for (int pos = Start; pos < Text.size() && Text[pos] == ' '; pos++)
  {
      Start = pos +1;
  }
  return Start;
}

// -------------------------------------------------------------------------------------
//  JSON Class

int JSON_ENTRY::find_closing(string Text, int Start_Pos, char Opening, char Closing)
{
  int ret_position = 0;
  int counter = 1;
  for (int pos = Start_Pos +1; pos < Text.size() && counter >0; pos++)
  {
    ret_position = pos;

    if (Text[pos] == Opening)
    {
      counter++;
    }
    else if (Text[pos] == Closing)
    {
      counter--;
    }
  }
  return ret_position;
}

bool JSON_ENTRY::check_entry(string &Entry, int &Size_Of_Entry, int &Size_Of_Label, 
                              bool &Is_A_Set, bool &Is_A_List, bool &Is_A_Value)
{
  bool ret_success = false;

  int pos_of_colon = -1;
  int working_pos = 0;

  // Remove leading "," if exist
  working_pos = pos_of_first_non_space(0, Entry);

  if (Entry[working_pos] == ',')
  {
    Entry[working_pos] = ' ';
  }

  // Advance working position
  working_pos = pos_of_first_non_space(working_pos, Entry);

  if (Entry[working_pos] == '{')
  // Entry is a list.
  {
    Size_Of_Entry = 1 + find_closing(Entry, working_pos, '{', '}');
    Is_A_List = true;
  }
  else
  {
    // Entry is a set or value.

    // Remove quotes from first word before ':', if exist.
    if (Entry[working_pos] == '"')
    {
      working_pos = Entry.find('"', working_pos +1);
    }

    // Determine middle seperator positon.
    pos_of_colon = Entry.find(':', working_pos);
    
    if (pos_of_colon != std::string::npos)
    {
      // Move to first word after seperator.
      working_pos = pos_of_first_non_space(pos_of_colon +1, Entry);

      if (Entry[working_pos] == '[')
      // Value is a set.
      {
        Size_Of_Entry = 1 + find_closing(Entry, working_pos, '[', ']');
        Size_Of_Label = pos_of_colon;
        Is_A_Set = true;
      }
      else
      {
        // Value is of value lable type

        if (Entry[working_pos] == '"')
        // Remove quotes from first word after ':', if exist.
        // Get size as pos of first ','.
        {
          Size_Of_Entry = Entry.find('"', working_pos +1);
          Size_Of_Entry = Entry.find(',', Size_Of_Entry);
        }
        else
        {
          // No quotes
          // Get size as pos of first ','.
          Size_Of_Entry = Entry.find(',', working_pos);
        }

        Size_Of_Label = pos_of_colon;
        Is_A_Value = true;
      }
    }
  }

  return true;
}

bool JSON_ENTRY::parse_item_list(string Entry, bool Is_Set, string Set_Name)
{
  bool ret_success = true;

  string sub_entry = "";
  string sub_label = "";
  string sub_value = "";

  int entry_size = 0;
  int label_size = 0;
  int value_size = 0;
  bool is_value_set = false;
  bool is_value_list = false;
  bool is_value_value = false;

  string label = "";
  string value = "";

  Entry = trim(Entry);

  if (Is_Set == true)
  {
    // If Entry is a list, remove closing brackets.
    ret_success = remove_opens_and_closes(Entry, '[', ']');
    if (ret_success == true)
    {
      // remove quotes from set name.
      LABEL = remove_first_and_last_characters('"', Set_Name);
    }
  }
  else
  {
    // If Entry is a list, remove closing braces.
    ret_success = remove_opens_and_closes(Entry, '{', '}');
  }

  if (ret_success == true)
  {

    int errcount = 0;

    // Continue to process Entry as long as info is within
    while (Entry.size() > 0 && errcount < errcountcap)
    {
      entry_size =0;
      label_size =0;
      is_value_set = false;
      is_value_list = false;
      is_value_value = false;

      if (check_entry(Entry, entry_size, label_size, is_value_set, is_value_list, is_value_value))
      {
        JSON_ENTRY new_json_entry;

        // Remove sub portion from Entry to process.
        sub_entry = Entry.substr(0, entry_size);
        Entry = Entry.erase(0, entry_size);

        // Get Label and Value portions
        sub_label = parse_label(sub_entry, label_size);
        sub_value = parse_value(sub_entry, label_size);

        // Store value or data
        if (is_value_value == true)
        {
          // Value is a label and value
          new_json_entry.IS_VALUE = true;
          new_json_entry.IS_LIST = false;
          new_json_entry.IS_SET = false;

          new_json_entry.LABEL = remove_first_and_last_characters('"', sub_label);
          new_json_entry.VALUE = remove_first_and_last_characters('"', sub_value);

          DATA.push_back(new_json_entry);
        }
        else if (is_value_set == true)
        {
          // Value is a set.
          new_json_entry.IS_VALUE = false;
          new_json_entry.IS_LIST = false;
          new_json_entry.IS_SET = true;

          new_json_entry.set_set(sub_value, sub_label);

          DATA.push_back(new_json_entry);
        }
        else if (is_value_list == true)
        {
          // Value is a list.
          new_json_entry.IS_VALUE = false;
          new_json_entry.IS_LIST = true;
          new_json_entry.IS_SET = false;

          new_json_entry.set_list(sub_entry);

          DATA.push_back(new_json_entry);
        }
      }

      // Clear the Entry if unable to determine remaining information type.
      if (is_value_set == false && is_value_list == false && is_value_value == false)
      {
        Entry = "";
      }

      // Curb Runaway
      errcount++;
      trim(Entry);
    }
  }

  return true;
}

void JSON_ENTRY::clear_data()
{
  for (int x = 0; x < DATA.size(); x++)
  {
    DATA[x].clear_data();
  }
  DATA.clear();
}

int JSON_ENTRY::find_label_pos(string Label_In_List)
{
  int ret_pos = -1;

  for (int pos = 0; pos < DATA.size() && ret_pos == -1; pos++)
  {
    if (DATA[pos].label() == Label_In_List)
    {
      ret_pos = pos;
    }
  }

  return ret_pos;
}

int JSON_ENTRY::size_of_set(string Set_Label)
{
  return DATA[find_label_pos(Set_Label)].DATA.size();
}

bool JSON_ENTRY::set_list(string Entry)
{
  bool ret_success = false;

  if (parse_item_list(Entry, false, "") == true)
  {
    ret_success = true;
  }

  return ret_success;
}

bool JSON_ENTRY::set_set(string Entry, string Set_Name)
{
  bool ret_success = false;

  if (parse_item_list(Entry, true, Set_Name) == true)
  {
    ret_success = true;
  }

  return ret_success;
}

string JSON_ENTRY::label()
{
  return LABEL;
}

string JSON_ENTRY::value()
{
  return VALUE;
}

string JSON_ENTRY::value_from_list(string Label_In_List)
{
  string ret_value = "";

  int pos = find_label_pos(Label_In_List);

  if (pos > -1)
  {
    ret_value = DATA[pos].value();
  }

  return ret_value;
}

bool JSON_ENTRY::get_if_is(string Label, int &Value)
{
  if (LABEL == Label)
  {
    Value = string_to_int(VALUE);
    return true;
  }
  else
  {
    return false;
  }
}

bool JSON_ENTRY::get_if_is(string Label, char &Value)
{
  if (LABEL == Label)
  {
    Value = VALUE[0];
    return true;
  }
  else
  {
    return false;
  }
}

bool JSON_ENTRY::get_if_is(string Label, bool &Value)
{
  if (LABEL == Label)
  {
    if (VALUE == "true")
    {
      Value = true;
    }
    else
    {
      Value = false;
    }
    return true;
  }
  else
  {
    return false;
  }
}

bool JSON_ENTRY::get_if_is(string Label, CRGB &Value)
{
  if (LABEL == Label)
  {
    Value = Value.StringtoCRGB(VALUE);
    return true;
  }
  else
  {
    return false;
  }
}

bool JSON_ENTRY::get_if_is(string Label, string &Value)
{
  if (LABEL == Label)
  {
    Value = VALUE;
    return true;
  }
  else
  {
    return false;
  }
}

bool JSON_ENTRY::get_if_is(string Label, STRING_STRING &Value)
{
  if (LABEL == Label)
  {
    Value.store(VALUE);
    return true;
  }
  else
  {
    return false;
  }
}

bool JSON_ENTRY::get_if_is(string Label, STRING_INT &Value)
{
  if (LABEL == Label)
  {
    Value.store(VALUE);
    return true;
  }
  else
  {
    return false;
  }
}

bool JSON_ENTRY::get_if_is(string Label, STRING_FLOAT &Value)
{
  if (LABEL == Label)
  {
    Value.store(VALUE);
    return true;
  }
  else
  {
    return false;
  }
}

void JSON_ENTRY::create_label_value(string Label, string Value)
{
  JSON_ENTRY new_entry;

  new_entry.LABEL = Label;
  new_entry.VALUE = Value;

  new_entry.IS_VALUE = true;
  new_entry.IS_LIST = false;
  new_entry.IS_SET = false;

  DATA.push_back(new_entry);
}

void JSON_ENTRY::put_json_in_list(JSON_ENTRY Entry)
{
  JSON_ENTRY new_list;

  new_list.IS_VALUE = false;
  new_list.IS_LIST = true;
  new_list.IS_SET = false;
  
  new_list.DATA = Entry.DATA;
  
  DATA.push_back(new_list);
}

void JSON_ENTRY::put_json_in_set(string Set_Name, JSON_ENTRY Entry)
{
  JSON_ENTRY new_set;

  new_set.IS_VALUE = false;
  new_set.IS_LIST = false;
  new_set.IS_SET = true;

  new_set.LABEL = Set_Name; // strange access
  new_set.DATA = Entry.DATA;

  DATA.push_back(new_set);
}

void JSON_INTERFACE::json_debug_to_string_deque(deque<string> &JSON_Print_Build, JSON_ENTRY Json_entry, int Level, int Count)
{
  Level++;

  if (Json_entry.IS_VALUE == true)
  {
    JSON_Print_Build.push_back(to_string(Level) + ":V:" + to_string(Count) + ":-" + line_create(Level *3, ' ') + 
                    " [" + Json_entry.label() + "]  [" + Json_entry.value() + "]"); 
  } 
  else if (Json_entry.IS_SET == true)
  {
    JSON_Print_Build.push_back(to_string(Level) + ":S:" + to_string(Count) + ":" + to_string(Json_entry.DATA.size()) + line_create(Level *3, ' ') + 
                    " [" + Json_entry.label() + "]  "); 
  }
  else if (Json_entry.IS_LIST == true)
  {
    JSON_Print_Build.push_back(to_string(Level) + ":L:" + to_string(Count) + ":" + to_string(Json_entry.DATA.size()) + line_create(Level *3, ' ') + 
                    " [" + Json_entry.label() + "]  "); 
  }

  if (Json_entry.IS_VALUE == false)
  {
    if (Json_entry.DATA.size() > 0)
    {
      for (int x = 0; x < Json_entry.DATA.size(); x++)
      {
        {
          json_debug_to_string_deque(JSON_Print_Build, Json_entry.DATA[x], Level, x);
        }
      }
    }
  }
}

void JSON_INTERFACE::json_to_string_deque(deque<string> &JSON_Print_Build, JSON_ENTRY Json_entry, int Level, string Trailing_Seperator)
{
  Level++;

  if (Json_entry.IS_VALUE == true)
  {
    JSON_Print_Build.push_back(line_create(Level *2, ' ') + Json_entry.label() + " : " + Json_entry.value() + Trailing_Seperator); 
  } 
  else if (Json_entry.IS_SET == true)
  {
    JSON_Print_Build.push_back(line_create(Level *2, ' ') + Json_entry.label() + " :"); 
    JSON_Print_Build.push_back(line_create(Level *2, ' ') + "["); 
  } 
  else if (Json_entry.IS_LIST == true)
  {
    JSON_Print_Build.push_back(line_create(Level *2, ' ') + "{"); 
  }

  if (Json_entry.IS_VALUE == false)
  {
    if (Json_entry.DATA.size() > 0)
    {
      for (int x = 0; x < Json_entry.DATA.size(); x++)
      {
        {
          string New_Trailing_Seperator = "";

          if ( x < Json_entry.DATA.size() -1)
          {
            New_Trailing_Seperator = " ,";
          }
          else
          {
            New_Trailing_Seperator = "";
          }
          json_to_string_deque(JSON_Print_Build, Json_entry.DATA[x], Level, New_Trailing_Seperator);
        }
      }
    }
  }

  if (Json_entry.IS_SET == true)
  {
    JSON_Print_Build.push_back(line_create(Level *2, ' ') + "]" + Trailing_Seperator); 
    Level--;
  } 
  else if (Json_entry.IS_LIST == true)
  {
    JSON_Print_Build.push_back(line_create(Level *2, ' ') + "}" + Trailing_Seperator); 
  }
}

bool JSON_INTERFACE::load_json_from_string(string JSON_Text)
{
  bool ret_success = false;

  // Clear Contents
  ROOT.clear_data();

  JSON_Text = trim(JSON_Text);

  if (JSON_Text.size() > 0)
  {
    JSON_ENTRY new_json_entry;

    ROOT.IS_LIST = true;
    if (ROOT.set_list(JSON_Text) == true)
    {
      ret_success = true;
    }
  }
  
  return ret_success;
}

void JSON_INTERFACE::json_debug_build_to_string_deque(deque<string> &JSON_Print_Build)
{
  json_debug_to_string_deque(JSON_Print_Build, ROOT, 0, 0);
}

void JSON_INTERFACE::json_print_build_to_string_deque(deque<string> &JSON_Print_Build)
{
  JSON_Print_Build.push_back("{");
  json_to_string_deque(JSON_Print_Build, ROOT, -1, "");
  JSON_Print_Build.push_back("}");
}


#endif