#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int averageValue(vector<int> &nums)
  {
    int count = 0;
    int sum = 0;
    for (auto &num : nums)
    {
      if (num % 6 == 0)
      {
        sum += num;
        count++;
      }
    }
    return count > 0 ? sum / count : sum;
  }
};

void testAverageValue()
{
  Solution s;
  vector<int> n1 = {1, 3, 6, 10, 12, 15};
  vector<int> n2 = {1, 2, 4, 7, 10};
  EXPECT_EQ_INT(9, s.averageValue(n1));
  EXPECT_EQ_INT(0, s.averageValue(n2));
  EXPECT_SUMMARY;
}

int main()
{
  testAverageValue();
  return 0;
}
