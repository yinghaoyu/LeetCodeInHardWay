#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int maxArea(vector<int> &height)
  {
    int l = 0;
    int r = height.size() - 1;
    int ans = 0;
    while (l <= r)
    {
      int cur = std::min(height[r], height[l]) * (r - l);
      ans = std::max(ans, cur);
      if (height[l] > height[r])
      {
        r--;
      }
      else
      {
        l++;
      }
    }
    return ans;
  }
};

void testMaxArea()
{
  Solution s;
  vector<int> h1 = {1, 8, 6, 2, 5, 4, 8, 3, 7};
  vector<int> h2 = {1, 1};
  EXPECT_EQ_INT(49, s.maxArea(h1));
  EXPECT_EQ_INT(1, s.maxArea(h2));
  EXPECT_SUMMARY;
}

int main()
{
  testMaxArea();
  return 0;
}
