#include <algorithm>
#include <vector>

#include "UnitTest.h"

using namespace std;

// https://github.com/yinghaoyu/algorithms/blob/master/sort/CountOfRangeSum.cc

// TODO: figure it out
class Solution
{
 public:
  // 树状数组 + 离散化的解法，理解难度较低
  int countRangeSum(vector<int>& nums, int lower, int upper)
  {
    build(nums);
    long sum = 0;
    int ans = 0;
    for (int i = 0; i < n; i++)
    {
      sum += nums[i];
      ans += sums(rank(sum - lower)) - sums(rank(sum - upper - 1));
      if (lower <= sum && sum <= upper)
      {
        ans++;
      }
      add(rank(sum), 1);
    }
    return ans;
  }

  static constexpr int MAXN = 100002;

  int n, m;

  vector<long> sort = vector<long>(MAXN);

  vector<int> tree = vector<int>(MAXN);

  void build(vector<int>& nums)
  {
    // 生成前缀和数组
    n = nums.size();
    for (int i = 1, j = 0; i <= n; i++, j++)
    {
      sort[i] = sort[i - 1] + nums[j];
    }
    // 前缀和数组排序和去重，最终有m个不同的前缀和
    std::sort(sort.begin() + 1, sort.begin() + n + 1);
    m = 1;
    for (int i = 2; i <= n; i++)
    {
      if (sort[m] != sort[i])
      {
        sort[++m] = sort[i];
      }
    }
    // 初始化树状数组，下标1~m
    std::fill(tree.begin() + 1, tree.begin() + m + 1, 0);
  }

  // 返回 <=v 并且尽量大的前缀和是第几号前缀和
  int rank(long v)
  {
    int left = 1, right = m, mid;
    int ans = 0;
    while (left <= right)
    {
      mid = (left + right) / 2;
      if (sort[mid] <= v)
      {
        ans = mid;
        left = mid + 1;
      }
      else
      {
        right = mid - 1;
      }
    }
    return ans;
  }

  // 树状数组模版代码，没有任何修改
  // i号前缀和，个数增加c个
  void add(int i, int c)
  {
    while (i <= m)
    {
      tree[i] += c;
      i += i & -i;
    }
  }

  // 树状数组模版代码，没有任何修改
  // 查询1~i号前缀和一共有几个
  int sums(int i)
  {
    int ans = 0;
    while (i > 0)
    {
      ans += tree[i];
      i -= i & -i;
    }
    return ans;
  }
};

void testCountRangeSum()
{
  Solution s;
  vector<int> n1 = {-2, 5, -1};
  vector<int> n2 = {0};
  EXPECT_EQ_INT(3, s.countRangeSum(n1, -2, 2));
  EXPECT_EQ_INT(1, s.countRangeSum(n2, 0, 0));
  EXPECT_SUMMARY;
}

int main()
{
  testCountRangeSum();
  return 0;
}
