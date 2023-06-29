#include <algorithm>
#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

// 此题与 https://leetcode.cn/problems/magnetic-force-between-two-balls/ 相同
class Solution
{
 public:
  bool check(vector<int> &price, int k, int tastiness)
  {
    int prev = INT32_MIN >> 1;
    int cnt = 0;
    for (auto &p : price)
    {
      // 当前的糖果价格比上一个选中的糖果价格差 > tastiness
      // 则选中当前糖果
      if (p - prev >= tastiness)
      {
        cnt++;
        prev = p;
      }
    }
    // 价格差 > tastiness 的糖果有 >= k 个
    return cnt >= k;
  }

  int maximumTastiness(vector<int> &price, int k)
  {
    int n = price.size();
    std::sort(price.begin(), price.end());
    int left = 0;
    int right = price[n - 1] - price[0];
    while (left < right)
    {
      // 先假设一个甜蜜度 mid
      int mid = (left + right + 1) >> 1;
      if (check(price, k, mid))
      {
        // 说明可以找到更大的甜蜜度
        left = mid;
      }
      else
      {
        right = mid - 1;
      }
    }
    return left;
  }
};

void test()
{
  Solution s;
  vector<int> n1 = {13, 5, 1, 8, 21, 2};
  vector<int> n2 = {1, 3, 1};
  vector<int> n3 = {7, 7, 7, 7};
  EXPECT_EQ_INT(8, s.maximumTastiness(n1, 3));
  EXPECT_EQ_INT(2, s.maximumTastiness(n2, 2));
  EXPECT_EQ_INT(0, s.maximumTastiness(n3, 2));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
