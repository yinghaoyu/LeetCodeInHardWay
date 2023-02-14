#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  vector<vector<string>> groupAnagrams1(vector<string> &strs)
  {
    unordered_map<string, vector<string>> map;
    for (auto &s : strs)
    {
      string cur;
      int cnt[256] = {0};
      for (char &c : s)
      {
        cnt[c - 'a']++;
      }
      for (int i = 0; i < 256; i++)
      {
        cur += std::to_string(cnt[i]) + "_";
      }
      map[cur].push_back(s);
    }
    vector<vector<string>> ans;
    for (auto &e : map)
    {
      ans.push_back(e.second);
    }
    return ans;
  }

  vector<vector<string>> groupAnagrams2(vector<string> &strs)
  {
    unordered_map<string, vector<string>> map;
    for (auto &s : strs)
    {
      string cur = s;
      std::sort(cur.begin(), cur.end());
      map[cur].push_back(s);
    }
    vector<vector<string>> ans;
    for (auto &e : map)
    {
      ans.push_back(e.second);
    }
    return ans;
  }
};
