#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int maxProduct(vector<int> &nums)
  {
    int a = -1;
    int b = -1;
    for (int i = 0; i < nums.size(); i++)
    {
      if (nums[i] > a)
      {
        b = a;
        a = nums[i];
      }
      else if (nums[i] > b)
      {
        b = nums[i];
      }
    }
    return (a - 1) * (b - 1);
  }
};

void testMaxProduct()
{
  Solution s;
  vector<int> arr1 = {3, 4, 5, 2};
  vector<int> arr2 = {1, 5, 4, 5};
  vector<int> arr3 = {3, 7};
  EXPECT_EQ_INT(12, s.maxProduct(arr1));
  EXPECT_EQ_INT(16, s.maxProduct(arr2));
  EXPECT_EQ_INT(12, s.maxProduct(arr3));
  EXPECT_SUMMARY;
}

int main()
{
  testMaxProduct();
  return 0;
}
