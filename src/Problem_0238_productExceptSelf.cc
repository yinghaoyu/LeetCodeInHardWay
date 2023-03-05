#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  vector<int> productExceptSelf(vector<int> &nums)
  {
    int n = nums.size();
    vector<int> ans(n);
    ans[0] = nums[0];
    for (int i = 1; i < n; i++)
    {
      ans[i] = ans[i - 1] * nums[i];
    }
    int right = 1;
    for (int i = n - 1; i > 0; i--)
    {
      ans[i] = ans[i - 1] * right;
      right *= nums[i];
    }
    ans[0] = right;
    return ans;
  }
};

void testProductExceptSelf()
{
  Solution s;
  vector<int> n1 = {1, 2, 3, 4};
  vector<int> o1 = {24, 12, 8, 6};
  vector<int> n2 = {-1, 1, 0, -3, 3};
  vector<int> o2 = {0, 0, 9, 0, 0};
  EXPECT_TRUE(o1 == s.productExceptSelf(n1));
  EXPECT_TRUE(o2 == s.productExceptSelf(n2));
  EXPECT_SUMMARY;
}

int main()
{
  testProductExceptSelf();
  return 0;
}
