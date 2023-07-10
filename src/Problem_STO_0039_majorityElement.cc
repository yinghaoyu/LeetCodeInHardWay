#include <iostream>
#include <vector>

using namespace std;

// 与 leetcode 0169 题相同
// https://leetcode.cn/problems/majority-element/

class Solution
{
 public:
  int majorityElement(vector<int> &nums)
  {
    int solider = 0;
    int blood = 0;
    for (auto &num : nums)
    {
      if (blood == 0)
      {
        solider = num;
        blood++;
      }
      else
      {
        blood += solider == num ? 1 : -1;
      }
    }
    return solider;
  }
};
