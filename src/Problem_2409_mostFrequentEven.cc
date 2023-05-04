#include <iostream>
#include <string>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int countDaysTogether(string arriveAlice, string leaveAlice, string arriveBob, string leaveBob)
  {
    vector<int> daysOfMonths = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int n = daysOfMonths.size();
    vector<int> sum(n + 1);
    for (int i = 0; i < n; i++)
    {
      sum[i + 1] = sum[i] + daysOfMonths[i];
    }
    int arriveAliceDay = stamp(arriveAlice, sum);
    int leaveAliceDay = stamp(leaveAlice, sum);
    int arriveBobDay = stamp(arriveBob, sum);
    int leaveBobDay = stamp(leaveBob, sum);
    return std::max(0, std::min(leaveAliceDay, leaveBobDay) - std::max(arriveAliceDay, arriveBobDay) + 1);
  }

  int stamp(string date, vector<int> &sum)
  {
    int pos = date.find('-');
    int month = std::stoi(date.substr(0, pos + 1));
    int day = std::stoi(date.substr(pos + 1));
    return sum[month - 1] + day;
  }
};

void testCountDaysTogether()
{
  Solution s;
  EXPECT_EQ_INT(3, s.countDaysTogether("08-15", "08-18", "08-16", "08-19"));
  EXPECT_EQ_INT(0, s.countDaysTogether("10-01", "10-31", "11-01", "12-31"));
  EXPECT_EQ_INT(0, s.countDaysTogether("10-20", "12-22", "06-21", "07-05"));
  EXPECT_SUMMARY;
}

int main()
{
  testCountDaysTogether();
  return 0;
}
