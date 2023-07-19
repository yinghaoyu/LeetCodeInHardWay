#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

// seem as leetcode 0049
// https://leetcode-cn.com/problems/group-anagrams/
// see at Problem_0049_groupAnagrams.cc
class Solution
{
 public:
  vector<vector<string>> groupAnagrams(vector<string> &strs)
  {
    unordered_map<string, vector<string>> map;
    for (auto &str : strs)
    {
      string key = str;
      std::sort(key.begin(), key.end());
      map[key].emplace_back(str);
    }
    vector<vector<string>> ans;
    for (auto &e : map)
    {
      ans.push_back(e.second);
    }
    return ans;
  }
};
