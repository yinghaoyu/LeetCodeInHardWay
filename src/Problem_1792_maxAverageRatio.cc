#include <functional>
#include <iostream>
#include <queue>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  // classes[i]=[passi, totali]
  // 第i个班级总共有totali个学生
  // 其中只有 passi 个学生可以通过考试
  // 额外有extraStudents个聪明的学生
  // 给这extraStudents个学生每人都安排一个班级，使得所有班级的平均通过率最大
  // 返回在安排这extraStudents个学生去对应班级后的最大平均通过率
  double maxAverageRatio(vector<vector<int>>& classes, int extraStudents)
  {
    priority_queue<std::tuple<double, int, int>> q;
    // 如果再来一人，班级通过率提升多少
    auto diff = [](int x, int y) -> double { return (double) (x + 1) / (y + 1) - (double) x / y; };
    double ans = 0;
    for (auto& c : classes)
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
