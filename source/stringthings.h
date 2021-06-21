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



#endif