#include <iostream>
#include <vector>

using namespace std;

// 测试链接：https://leetcode.cn/problems/minimum-value-to-get-positive-step-by-step-sum/

class Solution
{
 public:
  static int minStartValue(vector<int> &nums)
  {
    int min = INT32_MAX;
    int sum = 0;
    for (int i = 0; i < nums.size(); i++)
    {
      sum += nums[i];
      min = std::min(min, sum);
    }
    return min < 1 ? 1 - min : 1;
  }
};

int main()
{
  vector<int> nums = {-3, 2, -3, 4, 2};
  cout << Solution::minStartValue(nums) << endl;
  return 0;
}
