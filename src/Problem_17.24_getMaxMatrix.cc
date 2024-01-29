#include <algorithm>
#include <cstdint>
#include <vector>

using namespace std;

class Solution
{
 public:
  vector<int> getMaxMatrix(vector<vector<int>>& matrix)
  {
    int n = matrix.size();
    int m = matrix[0].size();
    int max = INT32_MIN;
    int a = 0;
    int b = 0;
    int c = 0;
    int d = 0;
    vector<int> nums(m);
    for (int up = 0; up < n; up++)
    {
      std::fill(nums.begin(), nums.end(), 0);
      for (int down = up; down < n; down++)
      {
        // 如下代码就是题目`Problem_0053_maxSubArray.cc`的附加问题:
        // 子数组中找到拥有最大累加和的子数组
        for (int l = 0, r = 0, pre = INT32_MIN; r < m; r++)
        {
          nums[r] += matrix[down][r];
          if (pre >= 0)
          {
            pre += nums[r];
          }
          else
          {
            pre = nums[r];
            l = r;
          }
          if (pre > max)
          {
            max = pre;
            a = up;
            b = l;
            c = down;
            d = r;
          }
        }
      }
    }
    return {a, b, c, d};
  }
};
