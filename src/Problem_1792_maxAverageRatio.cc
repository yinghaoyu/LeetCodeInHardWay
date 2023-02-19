#include <functional>
#include <iostream>
#include <queue>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  double maxAverageRatio(vector<vector<int>> &classes, int extraStudents)
  {
    priority_queue<std::tuple<double, int, int>> q;
    auto diff = [](int x, int y) -> double { return (double) (x + 1) / (y + 1) - (double) x / y; };
    double ans = 0;
    for (auto &c : classes)
    {
      int x = c[0];
      int y = c[1];
      ans += (double) x / y;
      q.push({diff(x, y), x, y});
    }

    for (int _ = 0; _ < extraStudents; _++)
    {
      auto [d, x, y] = q.top();
      q.pop();
      ans += d;
      q.push({diff(x + 1, y + 1), x + 1, y + 1});
    }

    return ans / classes.size();
  }
};

void testMaxAverageRatio()
{
  Solution s;
  vector<vector<int>> c1 = {{1, 2}, {3, 5}, {2, 2}};
  vector<vector<int>> c2 = {{2, 4}, {3, 9}, {4, 5}, {2, 10}};
  EXPECT_EQ_DOUBLE(0.78333, s.maxAverageRatio(c1, 2));
  EXPECT_EQ_DOUBLE(0.53485, s.maxAverageRatio(c2, 4));
  EXPECT_SUMMARY;
}

int main()
{
  testMaxAverageRatio();
  return 0;
}
