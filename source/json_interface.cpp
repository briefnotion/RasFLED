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
//  Panel Class

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
    else
    if (Text[pos] == Closing)
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

          new_json_entry.LABEL = trim(sub_label);
          new_json_entry.VALUE = trim(sub_value);
        }
        else
        if (is_value_set == true)
        {
          new_json_entry.IS_SET = true;

          new_json_entry.set_set(sub_value, sub_label);
        }
        else
        // if (is_value_list == true)
        {
          new_json_entry.IS_LIST = true;

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
    LABEL = trim(Set_Name);

    int errcount = 0;

    while (Entry.size() > 0 && errcount < errcountcap)
    {
      if (check_entry(Entry, entry_size, label_size, value_size, is_value_set, is_value_list))
      {
        JSON_ENTRY new_json_entry;

        if (is_value_list == true)
        {
        // Remove processing portion
          sub_entry = Entry.substr(0, entry_size);
          Entry = Entry.erase(0, entry_size);

          new_json_entry.IS_LIST = true;

          new_json_entry.set_list(sub_entry);

          DATA.push_back(new_json_entry);

        }
        else
        if (is_value_set == true)
        {
          //VALUE = "a set" + Entry;
        }
        else
        {
          //VALUE = "a value - " + Entry;
        }
      }
      
      errcount++;

    }

    // Curb Runaway
    errcount++;
    trim(Entry);

  }
  return true;
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

bool JSON_INTERFACE::load_json()
{
  bool ret_success = false;

  string file_text = "";

  if (FILE_JSON.booRead_File(PROP.FILENAME, file_text) == true)
  {
    file_text = trim(file_text);

    if (file_text.size() > 0)
    {
      JSON_ENTRY new_json_entry;

      ROOT.IS_LIST = true;
      if (ROOT.set_list(file_text) == true)
      {
        ret_success = true;
      }
    }
  }

  return ret_success;
}

#endif