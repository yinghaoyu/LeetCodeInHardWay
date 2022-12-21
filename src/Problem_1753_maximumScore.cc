#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  // 模拟
  int maximumScore1(int a, int b, int c)
  {
    priority_queue<int> que;
    que.push(a);
    que.push(b);
    que.push(c);
    int ans = 0;
    while (!que.empty())
    {
      int x = que.top();
      que.pop();
      int y = que.top();
      que.pop();
      if (x == 0 || y == 0)
      {
        break;
      }
      ans++;
      que.push(x - 1);
      que.push(y - 1);
    }
    return ans;
  }

  int maximumScore2(int a, int b, int c)
  {
    // 设 a <= b <= c
    // 当 a + b <= c，这时用a、b去匹配c，答案为a + b
    // 当 a + b > c，将c优先匹配a或b中较大的那个，然后剩下的a和b两两配对
    // 设a与c配对x次，b与c配对y次，答案为x + y + ((a - x) + (b - y)) / 2，简化为(a + b + c) / 2
    int sum = a + b + c;
    int maxVal = std::max({a, b, c});
    if (sum - maxVal < maxVal)
    {
      return sum - maxVal;
    }
    else
    {
      return sum / 2;
    }
  }
};

void testMaximumScore()
{
  Solution s;
  EXPECT_EQ_INT(6, s.maximumScore1(2, 4, 6));
  EXPECT_EQ_INT(7, s.maximumScore1(4, 4, 6));
  EXPECT_EQ_INT(8, s.maximumScore1(1, 8, 8));
  EXPECT_EQ_INT(6, s.maximumScore2(2, 4, 6));
  EXPECT_EQ_INT(7, s.maximumScore2(4, 4, 6));
  EXPECT_EQ_INT(8, s.maximumScore2(1, 8, 8));
  EXPECT_SUMMARY;
}

int main()
{
  testMaximumScore();
  return 0;
}
