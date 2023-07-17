#include <vector>
#include <unordered_map>
#include <iostream>

#include "UnitTest.h"

using namespace std;

// 与 leetcode 0560 相同
// https://leetcode.cn/problems/subarray-sum-equals-k/
// see at Problem_0560_subarraySum.cc
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
      unordered_map<int, int> map;
      map.emplace(0, 1);
      int sum = 0;
      int ans = 0;
      for(auto& num : nums)
      {
        sum += num;
        if(map.count(sum - k))
        {
          ans += map[sum - k];
        }
        if(map.count(sum))
        {
          map[sum]++;
        }
        else
        {
          map.emplace(sum, 1);
        }
      }
      return ans;
    }
};
