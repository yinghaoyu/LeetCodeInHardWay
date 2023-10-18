#include <iostream>
#include <queue>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  long long maxKelements(vector<int> &nums, int k)
  {
    long long ans = 0;
    priority_queue<int> q(nums.begin(), nums.end());
    for (int _ = 0; _ < k; _++)
    {
      int x = q.top();
      q.pop();
      ans += x;
      q.push((x + 2) / 3);
    }
    return ans;
  }
};

void test()
{
  Solution s;
  vector<int> n1 = {10, 10, 10, 10, 10};
  vector<int> n2 = {1, 10, 3, 3, 3};
  EXPECT_EQ_INT(50, s.maxKelements(n1, 5));
  EXPECT_EQ_INT(17, s.maxKelements(n2, 3));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
