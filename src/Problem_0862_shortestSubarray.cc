#include <cstdint>
#include <iostream>
#include <queue>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  // 暴力解
  int shortestSubarray1(vector<int> &nums, int k)
  {
    if (nums.size() == 0)
    {
      return -1;
    }
    int N = nums.size();
    int min = INT32_MAX;
    // 前缀和多出一个元素，让逻辑更简单
    vector<int> pre(N + 1);
    for (int i = 0; i < N; i++)
    {
      pre[i + 1] = pre[i] + nums[i];
    }
    for (int i = 0; i < N; i++)
    {
      for (int j = i + 1; j < N + 1; j++)
      {
        if (pre[j] - pre[i] >= k)
        {
          min = std::min(min, j - i);
        }
      }
    }
    return min == INT32_MAX ? -1 : min;
  }

  int shortestSubarray2(vector<int> &nums, int k)
  {
    if (nums.size() == 0)
    {
      return -1;
    }
    int N = nums.size();
    int min = INT32_MAX;
    deque<int> que;
    vector<int> pre(N + 1);
    // 前缀和多出一个元素，让逻辑更简单
    for (int i = 0; i < N; i++)
    {
      pre[i + 1] = pre[i] + nums[i];
    }
    for (int j = 0; j < N + 1; j++)
    {
      // 利用单调性剪枝
      // 考虑队列内的元素 >= 当前遍历的元素
      // 由题设条件 k >= 1
      // x表示在队列中，*表示当前遍历，-表示后续遍历的元素
      // x x x x x * - - - -
      //         ↑ ↑     ↑
      //         i j     k
      // 假设pre[i] >= pre[j]，那么pre[j] - pre[i] <= 0，显然不符合pre[j] - pre[i] >= k
      // 如果后续有k位置，使得pre[k] - pre[i] >= k成立，那么pre[k] - pre[j] >= k也成立，取的是更小的区间k - j
      // 所以pre[i] >= pre[j]，pre[i]可以不保留
      while (!que.empty() && pre[que.back()] >= pre[j])
      {
        que.pop_back();
      }
      while (!que.empty() && pre[j] - pre[que.front()] >= k)
      {
        min = std::min(min, j - que.front());
        que.pop_front();
      }
      que.push_back(j);
    }
    return min == INT32_MAX ? -1 : min;
  }
};

void testShortestSubarray()
{
  Solution s;
  vector<int> n1 = {1};
  vector<int> n2 = {1, 2};
  vector<int> n3 = {2, -1, 2};
  vector<int> n4 = {17, 85, 93, -45, -21};
  EXPECT_EQ_INT(1, s.shortestSubarray1(n1, 1));
  EXPECT_EQ_INT(-1, s.shortestSubarray1(n2, 4));
  EXPECT_EQ_INT(3, s.shortestSubarray1(n3, 3));
  EXPECT_EQ_INT(2, s.shortestSubarray1(n4, 150));
  EXPECT_EQ_INT(1, s.shortestSubarray2(n1, 1));
  EXPECT_EQ_INT(-1, s.shortestSubarray2(n2, 4));
  EXPECT_EQ_INT(3, s.shortestSubarray2(n3, 3));
  EXPECT_EQ_INT(2, s.shortestSubarray2(n4, 150));
  EXPECT_SUMMARY;
}

int main()
{
  testShortestSubarray();
  return 0;
}
