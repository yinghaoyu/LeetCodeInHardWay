#include <algorithm>
#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int earliestFullBloom(vector<int> &plantTime, vector<int> &growTime)
  {
    int n = growTime.size();
    vector<int> ids(n);
    for (int i = 0; i < n; i++)
    {
      ids[i] = i;
    }
    // 因为在植物生长期间，可以进行植物种植。因此尽量让生长时间和种植时间重合，减少总时间
    // 根据 growTime 从大到小排序
    std::sort(ids.begin(), ids.end(), [&](int i, int j) { return growTime[i] > growTime[j]; });

    int ans = 0;
    int pre = 0;
    for (int i : ids)
    {
      // 因为种植时间不能重叠，不考虑生长时间，理论上的最小值是:所有种植时间累加
      // 考虑到某一植物的生长时间可能是正无穷，因此要枚举求出最大值
      ans = std::max(ans, pre + plantTime[i] + growTime[i]);
      pre += plantTime[i];
    }
    return ans;
  }
};

void test()
{
  Solution s;
  vector<int> p1 = {1, 4, 3};
  vector<int> g1 = {2, 3, 1};
  vector<int> p2 = {1, 2, 3, 2};
  vector<int> g2 = {2, 1, 2, 1};
  vector<int> p3 = {1};
  vector<int> g3 = {1};
  EXPECT_EQ_INT(9, s.earliestFullBloom(p1, g1));
  EXPECT_EQ_INT(9, s.earliestFullBloom(p2, g2));
  EXPECT_EQ_INT(2, s.earliestFullBloom(p3, g3));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
