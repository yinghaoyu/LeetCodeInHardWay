#include <algorithm>
#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
   // 间距 >= x ，能够存放 >= m 个小球，返回 true
  bool check(int x, vector<int> &position, int m)
  {
    int pre = position[0];
    int cnt = 1;
    for (int i = 1; i < position.size(); i++)
    {
      if (position[i] - pre >= x)
      {
        pre = position[i];
        cnt++;
      }
    }
    return cnt >= m;
  }

  int maxDistance(vector<int> &position, int m)
  {
    std::sort(position.begin(), position.end());
    int left = 1;
    int right = position.back() - position.front();
    int ans = -1;
    while (left <= right)
    {
      // 二分找到间距
      int mid = (left + right) / 2;
      if (check(mid, position, m))
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
};

void test()
{
  Solution s;
  vector<int> p1 = {1, 2, 3, 4, 7};
  vector<int> p2 = {5, 4, 3, 2, 1, 1000000000};
  EXPECT_EQ_INT(3, s.maxDistance(p1, 3));
  EXPECT_EQ_INT(999999999, s.maxDistance(p2, 2));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
