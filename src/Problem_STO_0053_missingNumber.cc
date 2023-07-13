#include <vector>
#include <iostream>

#include "UnitTest.h"

using namespace std;

class Solution {
public:
    int missingNumber(vector<int>& nums) {
      int left = 0;
      int right = nums.size() - 1;
      while(left <= right)
      {
        int mid = (right - left) / 2 + left;
        if(nums[mid] == mid)
        {
          left = mid + 1;
        }
        else
        {
          right = mid - 1;
        }
      }
      return left;
    }
};

void test()
{
  Solution s;
  vector<int> n1 = {0,1,3};
  vector<int> n2 = {0};
  EXPECT_EQ_INT(2, s.missingNumber(n1));
  EXPECT_EQ_INT(1, s.missingNumber(n2));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
