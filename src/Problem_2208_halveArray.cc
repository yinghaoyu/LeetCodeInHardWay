#include <iostream>
#include <queue>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int halveArray(vector<int> &nums)
  {
    double sum = 0;
    priority_queue<double> q;
    for (auto &num : nums)
    {
      q.push(num);
      sum += num;
    }
    double x = 0;
    int cnt = 0;
    while (2 * x < sum)
    {
      double num = q.top();
      q.pop();
      x += num / 2;
      q.push(num / 2);
      cnt++;
    }
    return cnt;
  }
};

void test()
{
  Solution s;
  vector<int> n1 = {5, 19, 8, 1};
  vector<int> n2 = {3, 8, 20};
  EXPECT_EQ_INT(3, s.halveArray(n1));
  EXPECT_EQ_INT(3, s.halveArray(n2));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
