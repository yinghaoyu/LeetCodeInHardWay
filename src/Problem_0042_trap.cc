#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int trap(vector<int> &height)
  {
    int ans = 0;
    vector<int> stack;
    int n = height.size();
    for (int i = 0; i < n; i++)
    {
      while (!stack.empty() && height[stack.back()] < height[i])
      {
        int x = stack.back();
        stack.pop_back();
        if (stack.empty())
        {
          break;
        }
        int left = stack.back();
        int curWidth = i - left - 1;
        int curHeight = std::min(height[left], height[i]) - height[x];
        ans += curWidth * curHeight;
      }
      stack.push_back(i);
    }
    return ans;
  }
};

void testTrap()
{
  Solution s;
  vector<int> h1 = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
  vector<int> h2 = {4, 2, 0, 3, 2, 5};
  EXPECT_EQ_INT(6, s.trap(h1));
  EXPECT_EQ_INT(9, s.trap(h2));
  EXPECT_SUMMARY;
}

int main()
{
  testTrap();
  return 0;
}
