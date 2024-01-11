#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  vector<int> corpFlightBookings(vector<vector<int>>& bookings, int n)
  {
    vector<int> cnt(n + 2);
    // 设置差分数组，每一个操作对应两个设置
    for (auto& book : bookings)
    {
      cnt[book[0]] += book[2];
      cnt[book[1] + 1] -= book[2];
    }
    // 加工前缀和
    for (int i = 1; i < cnt.size(); i++)
    {
      cnt[i] += cnt[i - 1];
    }
    vector<int> ans(n);
    for (int i = 0; i < n; i++)
    {
      ans[i] = cnt[i + 1];
    }
    return ans;
  }
};

void test()
{
  Solution s;
  vector<vector<int>> b1 = {{1, 2, 10}, {2, 3, 20}, {2, 5, 25}};
  vector<vector<int>> b2 = {{1, 2, 10}, {2, 2, 15}};
  vector<int> o1 = {10, 55, 45, 25, 25};
  vector<int> o2 = {10, 25};
  EXPECT_TRUE(o1 == s.corpFlightBookings(b1, 5));
  EXPECT_TRUE(o2 == s.corpFlightBookings(b2, 2));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
