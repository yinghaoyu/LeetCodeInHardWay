#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  vector<int> twoSum(vector<int> &numbers, int target)
  {
    int n = numbers.size();
    int L = 0;
    int R = n - 1;
    vector<int> ans;
    while (L < R)
    {
      int sum = numbers[L] + numbers[R];
      if (sum < target)
      {
        L++;
      }
      else if (sum > target)
      {
        R--;
      }
      else
      {
        ans.push_back(L + 1);
        ans.push_back(R + 1);
        break;
      }
    }
    return ans;
  }
};

void test()
{
  Solution s;
  vector<int> n1 = {2, 7, 11, 15};
  vector<int> n2 = {2, 3, 4};
  vector<int> n3 = {-1, 0};
  vector<int> o1 = {1, 2};
  vector<int> o2 = {1, 3};
  vector<int> o3 = {1, 2};
  EXPECT_TRUE(o1 == s.twoSum(n1, 9));
  EXPECT_TRUE(o2 == s.twoSum(n2, 6));
  EXPECT_TRUE(o3 == s.twoSum(n3, -1));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
