#include <iostream>
#include <string>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  // 检查时间是否合法
  bool check(string &time)
  {
    int hh = std::stoi(time);
    int mm = std::stoi(time.substr(3));
    return hh < 24 && mm < 60;
  }

  int process(string &time, int index)
  {
    if (index == time.length())
    {
      return check(time);
    }
    int ans = 0;
    if (time[index] == '?')
    {
      // 尝试每一种情况
      for (int i = 0; i <= 9; i++)
      {
        time[index] = '0' + i;
        ans += process(time, index + 1);
        time[index] = '?';
      }
    }
    else
    {
      ans = process(time, index + 1);
    }
    return ans;
  }

  int countTime(string time) { return process(time, 0); }
};

void testCountTime()
{
  Solution s;
  EXPECT_EQ_INT(2, s.countTime("?5:00"));
  EXPECT_EQ_INT(100, s.countTime("0?:0?"));
  EXPECT_EQ_INT(1440, s.countTime("??:??"));
  EXPECT_SUMMARY;
}

int main()
{
  testCountTime();
  return 0;
}
