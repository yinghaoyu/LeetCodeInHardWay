#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

// @sa https://leetcode-cn.com/problems/relative-sort-array/
// @sa Problem_1122_relativeSortArray.cc

class Solution
{
 public:
  vector<int> relativeSortArray(vector<int> &arr1, vector<int> &arr2)
  {
    unordered_map<int, int> map;
    for (int i = 0; i < arr2.size(); i++)
    {
      map[arr2[i]] = i;
    }
    vector<int> ans = arr1;
    std::sort(ans.begin(), ans.end(),
              [&](int x, int y)
              {
                if (map.count(x))
                {
                  return map.count(y) ? map[x] < map[y] : true;
                }
                else
                {
                  return map.count(y) ? false : x < y;
                }
              });
    return ans;
  }
};
