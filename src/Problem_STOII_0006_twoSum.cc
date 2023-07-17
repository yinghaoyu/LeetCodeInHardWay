#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// 与 leetcode 0167 相同
// https://leetcode.cn/problems/two-sum-ii-input-array-is-sorted/
// see at Problem_0167_twoSum.cc
class Solution
{
 public:
  vector<int> twoSum(vector<int> &numbers, int target)
  {
    int n = numbers.size();
    int left = 0;
    int right = n - 1;
    while (left < right)
    {
      int sum = numbers[left] + numbers[right];
      if (sum > target)
      {
        right--;
      }
      else if (sum < target)
      {
        left++;
      }
      else
      {
        return {left, right};
      }
    }
    return {};
  }
};
