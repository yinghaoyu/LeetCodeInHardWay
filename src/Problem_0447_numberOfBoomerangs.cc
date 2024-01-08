#include <unordered_map>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int numberOfBoomerangs(vector<vector<int>>& points)
  {
    int ans = 0;
    for (auto& p : points)
    {
      unordered_map<int, int> cnt;
      // 统计所有点到点 p 的距离
      for (auto& q : points)
      {
        int distance = (p[0] - q[0]) * (p[0] - q[0]) + (p[1] - q[1]) * (p[1] - q[1]);
        ++cnt[distance];
      }
      // 假设 p 是 点组合 [i, j, k] 中的 j，
      // 需要从 m 个距离相等的点中选 2 个作为 i 和 k
      for (auto& [_, m] : cnt)
      {
        ans += m * (m - 1);
      }
    }
    return ans;
  }
};

void test()
{
  Solution s;
  vector<vector<int>> p1 = {{0, 0}, {1, 0}, {2, 0}};
  vector<vector<int>> p2 = {{1, 1}, {2, 2}, {3, 3}};
  vector<vector<int>> p3 = {{1, 1}};
  EXPECT_EQ_INT(2, s.numberOfBoomerangs(p1));
  EXPECT_EQ_INT(2, s.numberOfBoomerangs(p2));
  EXPECT_EQ_INT(2, s.numberOfBoomerangs(p3));
}

int main()
{
  test();
  return 0;
}
