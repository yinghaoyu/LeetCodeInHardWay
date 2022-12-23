#include <algorithm>
#include <string>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  vector<vector<int>> threeSum1(vector<int> &nums)
  {
    std::sort(nums.begin(), nums.end());
    vector<vector<int>> ans;
    // 第一个数选了i位置的数
    for (int i = 0; i < nums.size() - 2; i++)
    {
      // nums已经有序了，相同的数计算过一次可以不用计算
      // nums[i - 1] != nums[i]说明当前的数与上一个数不一样
      if (i == 0 || nums[i - 1] != nums[i])
      {
        vector<vector<int>> nexts = twoSum1(nums, i + 1, -nums[i]);
        for (auto &cur : nexts)
        {
          cur.push_back(nums[i]);
          ans.push_back(cur);
        }
      }
    }
    return ans;
  }

  // nums已经有序了
  // nums[begin......]范围上，找到累加和为target的所有二元组
  vector<vector<int>> twoSum1(vector<int> &nums, int begin, int target)
  {
    int L = begin;
    int R = nums.size() - 1;
    vector<vector<int>> ans;
    while (L < R)
    {
      if (nums[L] + nums[R] > target)
      {
        R--;
      }
      else if (nums[L] + nums[R] < target)
      {
        L++;
      }
      else
      {
        if (L == begin || nums[L - 1] != nums[L])
        {
          vector<int> cur;
          cur.push_back(nums[L]);
          cur.push_back(nums[R]);
          ans.emplace_back(cur);
        }
        L++;
      }
    }
    return ans;
  }

  vector<vector<int>> threeSum2(vector<int> &nums)
  {
    std::sort(nums.begin(), nums.end());
    int N = nums.size();
    vector<vector<int>> ans;
    for (int i = N - 1; i > 1; i--)
    {
      if (i == N - 1 || nums[i] != nums[i + 1])
      {
        vector<vector<int>> nexts = twoSum2(nums, i - 1, -nums[i]);
        for (vector<int> cur : nexts)
        {
          cur.push_back(nums[i]);
          ans.emplace_back(cur);
        }
      }
    }
    return ans;
  }

  vector<vector<int>> twoSum2(vector<int> &nums, int end, int target)
  {
    int L = 0;
    int R = end;
    vector<vector<int>> ans;
    while (L < R)
    {
      if (nums[L] + nums[R] > target)
      {
        R--;
      }
      else if (nums[L] + nums[R] < target)
      {
        L++;
      }
      else
      {
        if (L == 0 || nums[L - 1] != nums[L])
        {
          vector<int> cur;
          cur.push_back(nums[L]);
          cur.push_back(nums[R]);
          ans.emplace_back(cur);
        }
        L++;
      }
    }
    return ans;
  }
};

bool isSumEqualZero(vector<vector<int>> res)
{
  for (int i = 0; i < res.size(); i++)
  {
    if (res[i][0] + res[i][1] + res[i][2] != 0)
    {
      return false;
    }
  }
  return true;
}

void testThreeSum()
{
  Solution s;
  vector<int> n1 = {-1, 0, 1, 2, -1, -4};
  vector<int> n2 = {0, 1, 1};
  vector<int> n3 = {0, 0, 0};
  EXPECT_TRUE(isSumEqualZero(s.threeSum1(n1)));
  EXPECT_TRUE(isSumEqualZero(s.threeSum1(n2)));
  EXPECT_TRUE(isSumEqualZero(s.threeSum1(n3)));
  EXPECT_SUMMARY;
}

int main()
{
  testThreeSum();
  return 0;
}
