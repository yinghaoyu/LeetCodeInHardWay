#include <iostream>
#include <numeric>  // std::accumulate
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int countStudents(vector<int> &students, vector<int> &sandwiches)
  {
    // 1的数量
    int a = std::accumulate(students.begin(), students.end(), 0);  // 累加初始值为0
    // 0的数量
    int b = students.size() - a;
    for (int i = 0; i < sandwiches.size(); i++)
    {
      if (sandwiches[i] == 0 && b > 0)
      {
        b--;
      }
      else if (sandwiches[i] == 1 && a > 0)
      {
        a--;
      }
      else
      {
        // sandwiches是模拟栈
        break;
      }
    }
    return b + a;
  }
};

void testCountStudents()
{
  Solution s;
  vector<int> st1 = {1, 1, 0, 0};
  vector<int> sa1 = {0, 1, 0, 1};

  vector<int> st2 = {1, 1, 1, 0, 0, 1};
  vector<int> sa2 = {1, 0, 0, 0, 1, 1};

  EXPECT_EQ_INT(0, s.countStudents(st1, sa1));
  EXPECT_EQ_INT(3, s.countStudents(st2, sa2));
  EXPECT_SUMMARY;
}

int main()
{
  testCountStudents();
  return 0;
}
