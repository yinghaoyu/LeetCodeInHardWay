#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  vector<vector<int>> queensAttacktheKing(vector<vector<int>> &queens, vector<int> &king)
  {
    int kx = king[0];
    int ky = king[1];
    auto sgn = [](int x) { return x > 0 ? 1 : (x == 0 ? 0 : -1); };
    unordered_map<int, std::pair<vector<int>, int>> map;
    for (auto &queen : queens)
    {
      int qx = queen[0];
      int qy = queen[1];
      int x = qx - kx;
      int y = qy - ky;
      if (x == 0 || y == 0 || std::abs(x) == std::abs(y))
      {
        int dx = sgn(x);
        int dy = sgn(y);
        // 把 8 个方向离散
        int key = dx * 10 + dy;
        if (!map.count(key) || map[key].second > std::abs(x) + abs(y))
        {
          // 差值最小则更新
          map[key] = {queen, std::abs(x) + std::abs(y)};
        }
      }
    }
    vector<vector<int>> ans;
    for (auto &[_, value] : map)
    {
      ans.push_back(value.first);
    }
    return ans;
  }
};

void test()
{
  Solution s;
  vector<vector<int>> q1 = {{0, 1}, {1, 0}, {4, 0}, {0, 4}, {3, 3}, {2, 4}};
  vector<int> k1 = {0, 0};
  vector<vector<int>> o1 = {{0, 1}, {1, 0}, {3, 3}};

  vector<vector<int>> q2 = {{0, 0}, {1, 1}, {2, 2}, {3, 4}, {3, 5}, {4, 4}, {4, 5}, {5, 5}};
  vector<int> k2 = {3, 3};
  vector<vector<int>> o2 = {{2, 2}, {3, 4}, {4, 4}};

  vector<vector<int>> x1 = s.queensAttacktheKing(q1, k1);
  vector<vector<int>> x2 = s.queensAttacktheKing(q2, k2);
  std::sort(o1.begin(), o1.end());
  std::sort(o2.begin(), o2.end());
  std::sort(x1.begin(), x1.end());
  std::sort(x2.begin(), x2.end());
  EXPECT_TRUE(o1 == x1);
  EXPECT_TRUE(o2 == x2);
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
