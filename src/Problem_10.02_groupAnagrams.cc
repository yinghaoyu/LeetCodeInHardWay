#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution
{
 public:
  // 排序
  vector<vector<string>> groupAnagrams1(vector<string>& strs)
  {
    unordered_map<string, vector<string>> map;
    for (auto& s : strs)
    {
      string key = s;
      std::sort(key.begin(), key.end());
      map[key].push_back(s);
    }
    vector<vector<string>> ans;
    for (auto& [key, value] : map)
    {
      ans.emplace_back(value);
    }
    return ans;
  }

  // 计数
  vector<vector<string>> groupAnagrams2(vector<string>& strs)
  {
    // 26 个质数
    vector<int> prim = {2,  3,  5,  7,  11, 13, 17, 19, 23, 29, 31, 37, 41,
                        43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101};
    unordered_map<double, vector<string>> map;
    for (auto& s : strs)
    {
      // 考虑到方法一排序比较耗时，这里借用26个质素任意相乘结果不一，实现 hash 功能
      double key = 1.0;
      for (char& c : s)
      {
        key *= (prim[c - 'a']);
      }
      map[key].push_back(s);
    }
    vector<vector<string>> ans;
    for (auto& [key, value] : map)
    {
      ans.push_back(value);
    }
    return ans;
  }
};
