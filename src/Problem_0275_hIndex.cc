#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int hIndex(vector<int>& citations)
  {
    int n = citations.size();
    int left = 0;
    int right = n - 1;
    while (left <= right)
    {
      // TODO: figure it out
      int mid = (right - left) / 2 + left;
      if (citations[mid] >= n - mid)
      {
        right = mid - 1;
      }
      else
      {
        left = mid + 1;
      }
    }
    return n - left;
  }
};

void test()
{
  Solution s;
  vector<int> c1 = {0, 1, 3, 5, 6};
  vector<int> c2 = {1, 2, 100};
  EXPECT_EQ_INT(3, s.hIndex(c1));
  EXPECT_EQ_INT(2, s.hIndex(c2));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
