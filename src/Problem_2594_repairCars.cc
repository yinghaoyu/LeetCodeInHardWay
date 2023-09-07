#include <cmath>
#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  // 在规定时间 time 内，所有机械工能完成多少辆车
  bool check(vector<int> &ranks, int cars, long long time)
  {
    long long ans = 0;
    for (auto &x : ranks)
    {
      ans += sqrt(time / x);
    }
    return ans >= cars;
  }

  long long repairCars(vector<int> &ranks, int cars)
  {
    long long left = 1;
    // 为什么可以用二分？因为时间越长，机械工能制作的汽车越多，符合单调递增规律
    // 任取一个工人完成所有车辆需要的时间，作为上界
    // 如果 ranks[0] 最大，那么 right 一定不是最大值，从[left, right]必能找符合条件的时间
    // 如果 ranks[0] 最小，那么 right 可能是最小值，从[left, right]一定能找到 right 满足条件
    long long right = 1LL * ranks[0] * cars * cars;
    while (left < right)
    {
      // 枚举时间
      long long mid = (right - left) / 2 + left;
      if (check(ranks, cars, mid))
      {
        // 满足条件记录，right 一直左移
        right = mid;
      }
      else
      {
        left = mid + 1;
      }
    }
    return right;
  }
};

void test()
{
  Solution s;
  vector<int> r1 = {4, 2, 3, 1};
  vector<int> r2 = {5, 1, 8};
  EXPECT_EQ_INT(16, s.repairCars(r1, 10));
  EXPECT_EQ_INT(16, s.repairCars(r2, 6));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
