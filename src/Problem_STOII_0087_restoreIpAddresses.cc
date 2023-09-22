#include <iostream>
#include <vector>

using namespace std;

class Solution
{
 private:
  const int SEG_COUNT = 4;
  vector<int> segments;
  vector<string> ans;

 public:
  void process(string &s, int segId, int index)
  {
    if (segId == SEG_COUNT)
    {
      if (index == s.length())
      {
        string ipAddr;
        for (int i = 0; i < SEG_COUNT; i++)
        {
          ipAddr += std::to_string(segments[i]);
          if (i != SEG_COUNT - 1)
          {
            ipAddr += ".";
          }
        }
        ans.push_back(std::move(ipAddr));
      }
      return;
    }
    if (index == s.length())
    {
      return;
    }
    if (s[index] == '0')
    {
      segments[segId] = 0;
      process(s, segId + 1, index + 1);
      return;
    }
    int num = 0;
    for (int i = index; i < s.length(); i++)
    {
      num = num * 10 + (s[i] - '0');
      if (num > 0 && num <= 0xff)
      {
        segments[segId] = num;
        process(s, segId + 1, i + 1);
      }
      else
      {
        break;
      }
    }
  }

  vector<string> restoreIpAddresses(string s)
  {
    segments.resize(SEG_COUNT);
    process(s, 0, 0);
    return ans;
  }
};
