// ***************************************************************************************
// *
// *    Core       | Everything within this document is proprietary to Core Dynamics.
// *    Dynamics   | Any unauthorized duplication will be subject to prosecution.
// *
// *    Department : (R+D)^2                        Name: stringthings.h
// *       Sub Dept: Programming
// *    Location ID: 856-45B
// *                                                      (c) 2856 - 2858 Core Dynamics
// ***************************************************************************************

#ifndef STRINGTHINGS_H
#define STRINGTHINGS_H

// Standard Header Files
#include <string.h>
#include <deque>

using namespace std;

class WORDLINE
{
  private:
  deque<string> words;

  public:
  bool empty()
  {
    return words.empty();
  }

  int size()
  {
    return words.size();
  }

  string pop()
  {
    string word = "";
    if(words.empty() == false)
    {
      word = words.front();
      words.pop_front();
    }
    return word;
  }


  void storeline(string strLine)
  {
    int c1 = 0;
    string word = "";
    bool juststop = false;

    while((strLine.length() > 0) && (juststop == false))
    {
      c1 = strLine.find(" ");

      if(c1==std::string::npos)
      {
        c1 = strLine.length();
        juststop = true;
      }

      if (c1 > 0)
      {
        word = strLine.substr(0,c1).c_str();
        
        if(word.length()>0)
        {
          words.push_back(word);
        }
      }

      if(juststop == false)
      {
        strLine = strLine.substr(c1+1,strLine.length()-(c1+1));
      }
    }
  }
};

string linefill(int size, string text)
// Returns a space filled line of size with text in center.
{
  string line = "";

  line = line.append(size,' ');

  line.replace(((size/2)-(text.length()/2)), text.length(), text);
  line.resize(size);
  return line;
}

string linemerge(int size, string line, string text)
// Overlaps and centers text onto line.
// Returns value at size. 
{
  int text_size = text.length();
  
  if (text_size > size)
  {
    text.resize(size);
    text_size = text.length();
  }

  line.replace(((size/2)-(text_size/2)), text_size, text);
  line.resize(size);
  return line;
}

string linemerge_left_justify(int size, string line, string text)
// Overlaps and right justifies text onto line.
// Returns value at size. 
{
  string return_string = line;

  if (line.size() > text.size())
  {
    return_string.replace(0, text.size(), text);
  }
  else
  {
    return_string = text;
  }

  if((return_string.size() > size) && (size > 0))
  {
    return_string.erase(size, line.size() - size);
  }

  return return_string;
}

string linemerge_left_justify(string line, string text)
// Overlaps and right justifies text onto line.
// No Truncate.
// Returns value at size. 
{
  return linemerge_left_justify(0, line, text);
}

string linemerge_right_justify(int size, string line, string text)
// Overlaps and right justifies text onto line.
// Returns value at size. 
{
  string return_string = line;

  if (line.size() > text.size())
  {
    return_string.replace(line.size() - text.size(), text.size(), text);
  }
  else
  {
    return_string = text;
  }

  if(return_string.size() > size)
  {
    return_string.erase(0, return_string.size() - size);
  }

  return return_string;
}



#endif