#include <algorithm>
#include <type_traits>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  // 回溯法
  void process(vector<int> &nums, int index, vector<vector<int>> &ans)
  {
    if (index == nums.size())
    {
      ans.push_back(nums);
      return;
    }
    for (int i = index; i < nums.size(); i++)
    {
      // 假设我们已经填到第 index 个位置
      // 那么 nums 数组中 [0, index - 1] 是已填过的数的集合
      // [index , n - 1] 是待填的数的集合
      // 我们肯定是尝试用 [first, n − 1] 里的数去填第 index 个数
      // 假设待填的数的下标为 i，那么填完以后我们将第 i 个数和第 index 个数交换
      // 即能使得在填第 index + 1 个数的时候，nums 数组的 [0, index] 部分为已填过的数，
      // [index + 1, n−1] 为待填的数，回溯的时候交换回来即能完成撤销操作

      // 举个简单的例子，假设我们有 [2,5,8,9,10]这 5 个数要填入，
      // 已经填到第 3 个位置，已经填了[8,9] 两个数，
      // 那么这个数组目前为 [8,9|2,5,10] 这样的状态，分隔符区分了左右两个部分。
      // 假设这个位置我们要填 10 这个数，为了维护数组，我们将 2 和 10 交换，
      // 即能使得数组继续保持分隔符左边的数已经填过，右边的待填 [8,9,10 | 2,5]

      // 注意：这样生成的全排列并不是按字典序存储在答案数组中

      std::swap(nums[index], nums[i]);
      process(nums, index + 1, ans);
      std::swap(nums[index], nums[i]);
    }
  }

  vector<vector<int>> permute(vector<int> &nums)
  {
    vector<vector<int>> ans;
    process(nums, 0, ans);
    return ans;
  }
};

bool isVectorEqual(vector<vector<int>> a, vector<vector<int>> b)
{
  std::sort(a.begin(), a.end());
  std::sort(b.begin(), b.end());
  return a == b;
}

void testPermute()
{
  Solution s;

  vector<int> n1 = {1, 2, 3};
  vector<vector<int>> o1 = {{1, 2, 3}, {1, 3, 2}, {2, 1, 3}, {2, 3, 1}, {3, 1, 2}, {3, 2, 1}};

  vector<int> n2 = {0, 1};
  vector<vector<int>> o2 = {{0, 1}, {1, 0}};

  vector<int> n3 = {1};
  vector<vector<int>> o3 = {{1}};

  EXPECT_TRUE(isVectorEqual(o1, s.permute(n1)));
  EXPECT_TRUE(isVectorEqual(o2, s.permute(n2)));
  EXPECT_TRUE(isVectorEqual(o3, s.permute(n3)));
  EXPECT_SUMMARY;
}

int main()
{
  testPermute();
  return 0;
}
