#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int busyStudent(vector<int> &startTime, vector<int> &endTime, int queryTime)
  {
    int ans = 0;
    for (int i = 0; i < startTime.size(); i++)
    {
      if (startTime[i] <= queryTime && queryTime <= endTime[i])
      {
        ans++;
      }
    }
    return ans;
  }
};

void testBusyStudent()
{
  Solution s;
  vector<int> start = {1, 2, 3};
  vector<int> end = {3, 2, 7};
  int queryTime = 4;
  EXPECT_EQ_INT(1, s.busyStudent(start, end, queryTime));
  EXPECT_SUMMARY;
}

int main()
{
  testBusyStudent();
  return 0;
}
