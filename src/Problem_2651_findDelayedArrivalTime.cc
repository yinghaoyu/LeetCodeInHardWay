#include <iostream>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int findDelayedArrivalTime(int arrivalTime, int delayedTime) { return (arrivalTime + delayedTime) % 24; }
};

void test()
{
  Solution s;
  EXPECT_EQ_INT(20, s.findDelayedArrivalTime(15, 5));
  EXPECT_EQ_INT(0, s.findDelayedArrivalTime(13, 11));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
