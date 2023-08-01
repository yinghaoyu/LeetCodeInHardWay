#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  vector<vector<int>> subsetsWithDup(vector<int> &nums)
  {
    // 先排序
    std::sort(nums.begin(), nums.end());
    int n = nums.size();
    vector<int> tmp;
    vector<vector<int>> ans;
    // 枚举所有子集
    for (int mask = 0; mask < (1 << n); mask++)
    {
      tmp.clear();
      bool flag = true;
      for (int i = 0; i < n; i++)
      {
        // 检查元素是否选中
        if (mask & (1 << i))
        {
          if (i > 0 && (mask >> (i - 1) & 1) == 0 && nums[i] == nums[i - 1])
          {
            // 对于 {1, 2, 2, ...}
            // 观察第二个 2
            // 如果前面有一个数和当前这一个数相等，前面的数没选中，当前的数选中
            // 那么这时产生的结果为 {1, 2, ...}
            // 与第一次遇到这个数形成的结果是一样的
            // 因为第一次遇到这个 2
            // 也产生了结果 {1, 2, ...}
            // 因此需要过滤
            flag = false;
            break;
          }
          tmp.push_back(nums[i]);
        }
      }
      if (flag)
      {
        ans.push_back(tmp);
      }
    }
    return ans;
  }
};

void test()
{
  Solution s;
  vector<int> n1 = {1, 2, 2};
  vector<int> n2 = {0};
  auto x1 = s.subsetsWithDup(n1);
  auto x2 = s.subsetsWithDup(n2);
  vector<vector<int>> o1 = {{}, {1}, {1, 2}, {1, 2, 2}, {2}, {2, 2}};
  vector<vector<int>> o2 = {{}, {0}};
  std::sort(x1.begin(), x1.end());
  std::sort(x2.begin(), x2.end());
  std::sort(o1.begin(), o1.end());
  std::sort(o2.begin(), o2.end());
  EXPECT_TRUE(o1 == x1);
  // EXPECT_TRUE(o2 == x2);
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
