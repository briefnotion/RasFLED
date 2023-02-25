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

string JSON_ENTRY::parse_label(string Text, int Label_Size)
{
  return Text.substr(0, Label_Size);
}

string JSON_ENTRY::parse_value(string Text, int Label_Size)
{
  return Text.erase(0, Label_Size +1);
  //return Text;
}

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


bool JSON_ENTRY::remove_brackets(string &Entry)
{
  bool ret_success = false;

  int start = 0;
  int last = 0;

  // Filter out Brackets.
  start = Entry.find('[');
  if (start != std::string::npos)
  {
    last = Entry.find_last_of(']');
    if (last != std::string::npos)
    {
      Entry = Entry.substr(start +1, last -1);

      ret_success = true;
    }
  }

  return ret_success;
}

bool JSON_ENTRY::remove_curls(string &Entry)
{
  bool ret_success = false;

  int start = 0;
  int last = 0;

  // Filter out Brackets.
  start = Entry.find('{');
  if (start != std::string::npos)
  {
    last = Entry.find_last_of('}');
    if (last != std::string::npos)
    {
      Entry = Entry.substr(start +1, last -1);

      ret_success = true;
    }
  }

  return ret_success;
}

bool JSON_ENTRY::check_entry(string &Entry, int &Size_Of_Entry, int &Size_Of_Label, int &Size_Of_Value, 
                              bool &Is_A_Set, bool &Is_A_List)
{
  bool ret_success = false;

  int label_size = 0;
  int value_size = 0;
  int entry_size = 0;

  bool a_set = false;
  bool a_list = false;

  int value_start_pos = 0;
  int value_end_pos = 0;

  int pos_of_colon = -1;
  int pos_of_bracket_open = -1;
  int pos_of_curly_open = -1;

  bool complete = false;

  // Remove leading "," if exist
  int entry_start = 0;
  complete = false;
  for (int pos = 0; pos < Entry.size() && complete == false; pos++)
  {
    entry_start = pos;

    if (Entry[pos] != ' ')
    {
      if (Entry[pos] == ',')
      {
        Entry[pos] = ' ';
      }
      else
      {
        complete = true;
      }
    }
  }

  pos_of_colon = Entry.find(':');
  if (pos_of_colon != std::string::npos)
  {
    label_size = pos_of_colon;
    value_start_pos = pos_of_colon +1;
  }

  // Determine if value is a value or set
  complete = false;
  for (int pos = value_start_pos; pos < Entry.size() && complete == false; pos++)
  {
    if (Entry[pos] != ' ')
    {
      if (Entry[pos] == '[')
      {
        a_set = true;
        pos_of_bracket_open = pos;
        complete = true;
      }
      else
      {
        complete = true;
      }
    }
  }

  // Determine if value is a list
  complete = false;
  for (int pos = 0; pos < Entry.size() && complete == false; pos++)
  {
    if (Entry[pos] != ' ')
    {
      if (Entry[pos] == '{')
      {
        a_list = true;
        pos_of_curly_open = pos;
        complete = true;
      }
      else
      {
        complete = true;
      }
    }
  }

  // If not a list && not a set
  if (a_set == false && a_list == false)
  {
    // Look for End comma pos
    complete = false;
    for (int pos = value_start_pos; pos < Entry.size() && complete == false; pos++)
    {
      value_end_pos = pos;

      if (Entry[pos] == ',')
      {
        value_end_pos--;
        complete = true;
      }
    }
  }
  else if (a_list == true) // if a_list == true
  {
    value_end_pos = find_closing(Entry, pos_of_curly_open, '{', '}');
  }
  else // if (a_set == true)
  {
    value_end_pos = find_closing(Entry, pos_of_bracket_open, '[', ']');
  }

  Size_Of_Entry = value_end_pos +1;
  Size_Of_Label = label_size;
  Size_Of_Value = value_size;
  Is_A_Set = a_set;
  Is_A_List = a_list;

  return true;
}

bool JSON_ENTRY::parse_item_list(string Entry)
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

  string label = "";
  string value = "";

  Entry = trim(Entry);

  if (remove_curls(Entry) == true)
  {

    int errcount = 0;

    while (Entry.size() > 0 && errcount < errcountcap)
    {if (check_entry(Entry, entry_size, label_size, value_size, is_value_set, is_value_list))
      {
        JSON_ENTRY new_json_entry;

        // Remove processing portion
        sub_entry = Entry.substr(0, entry_size);
        Entry = Entry.erase(0, entry_size);

        // Get Label and Value
        sub_label = parse_label(sub_entry, label_size);
        sub_value = parse_value(sub_entry, label_size);

        // Store value or data
        if (is_value_set == false && is_value_list == false)
        {
          new_json_entry.IS_VALUE = true;
          new_json_entry.IS_LIST = false;
          new_json_entry.IS_SET = false;

          new_json_entry.LABEL = remove_first_and_last_characters('"', sub_label);
          new_json_entry.VALUE = remove_first_and_last_characters('"', sub_value);
        }
        else if (is_value_set == true)
        {
          new_json_entry.IS_VALUE = false;
          new_json_entry.IS_LIST = false;
          new_json_entry.IS_SET = true;

          new_json_entry.set_set(sub_value, sub_label);
        }
        else
        // if (is_value_list == true)
        {
          new_json_entry.IS_VALUE = false;
          new_json_entry.IS_LIST = true;
          new_json_entry.IS_SET = false;

          new_json_entry.set_list(sub_entry);
        }

        DATA.push_back(new_json_entry);
      }

      // Curb Runaway
      errcount++;
      trim(Entry);
      
    }
  }
  return true;
}


bool JSON_ENTRY::parse_item_set(string Entry, string Set_Name)
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

  string label = "";

  Entry = trim(Entry);

  if (remove_brackets(Entry) == true)
  {
    LABEL = remove_first_and_last_characters('"', Set_Name);

    int errcount = 0;

    while (Entry.size() > 0 && errcount < errcountcap)
    {if (check_entry(Entry, entry_size, label_size, value_size, is_value_set, is_value_list))
      {
        JSON_ENTRY new_json_entry;

        // Remove processing portion
        sub_entry = Entry.substr(0, entry_size);
        Entry = Entry.erase(0, entry_size);

        // Get Label and Value
        sub_label = parse_label(sub_entry, label_size);
        sub_value = parse_value(sub_entry, label_size);

        // Store value or data
        if (is_value_set == false && is_value_list == false)
        {
          new_json_entry.IS_VALUE = true;
          new_json_entry.IS_LIST = false;
          new_json_entry.IS_SET = false;

          new_json_entry.LABEL = remove_first_and_last_characters('"', sub_label);
          new_json_entry.VALUE = remove_first_and_last_characters('"', sub_value);
        }
        else if (is_value_set == true)
        {
          new_json_entry.IS_VALUE = false;
          new_json_entry.IS_LIST = false;
          new_json_entry.IS_SET = true;

          new_json_entry.set_set(sub_value, sub_label);
        }
        else
        // if (is_value_list == true)
        {
          new_json_entry.IS_VALUE = false;
          new_json_entry.IS_LIST = true;
          new_json_entry.IS_SET = false;

          new_json_entry.set_list(sub_entry);
        }

        DATA.push_back(new_json_entry);
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

  if (parse_item_list(Entry) == true)
  {
    ret_success = true;
  }

  return ret_success;
}

bool JSON_ENTRY::set_set(string Entry, string Set_Name)
{
  bool ret_success = false;

  if (parse_item_set(Entry, Set_Name) == true)
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
  json_to_string_deque(JSON_Print_Build, ROOT, -1, "");
}


#endif