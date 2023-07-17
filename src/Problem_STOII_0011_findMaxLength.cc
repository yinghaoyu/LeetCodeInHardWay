#include <vector>
#include <unordered_map>
#include <iostream>

#include "UnitTest.h"

using namespace std;

// 与 leetcode 0525 相同
// https://leetcode-cn.com/problems/contiguous-array/
// see at Problem_0525_findMaxLength.cc
class Solution {
public:
    int findMaxLength(vector<int>& nums) {
      int n = nums.size();
      unordered_map<int, int> map;
      map.emplace(0, -1);
      int sum = 0;
      int ans = 0;
      for (int i = 0; i < n; i++)
      {
        sum += nums[i] == 1 ? 1 : -1;
        if (map.count(sum))
        {
          ans = std::max(ans, i - map[sum]);
        }
        else
        {
          map.emplace(sum, i);
        }
      }
      return ans;
    }
};
