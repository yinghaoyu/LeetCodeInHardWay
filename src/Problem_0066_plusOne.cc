#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  vector<int> plusOne1(vector<int> &digits)
  {
    vector<int> d = digits;
    int n = d.size();
    int num = d[n - 1] + 1;
    int carry = num / 10;
    d[n - 1] = num % 10;
    int i = n - 2;
    while (i >= 0 && carry != 0)
    {
      int num = d[i] + carry;
      d[i] = num % 10;
      carry = num / 10;
      i--;
    }
    if (carry != 0)
    {
      d.insert(d.begin(), carry);
    }
    return d;
  }

  vector<int> plusOne2(vector<int> &digits)
  {
    int n = digits.size();
    for (int i = n - 1; i >= 0; i--)
    {
      if (digits[i] < 9)
      {
        digits[i]++;
        return digits;
      }
      digits[i] = 0;
    }
    vector<int> ans(n + 1);
    ans[0] = 1;
    return ans;
  }
};

void testPlusOne()
{
  Solution s;
  vector<int> n1 = {1, 2, 3};
  vector<int> o1 = {1, 2, 4};
  vector<int> n2 = {4, 3, 2, 1};
  vector<int> o2 = {4, 3, 2, 2};
  vector<int> n3 = {9};
  vector<int> o3 = {1, 0};
  EXPECT_TRUE(o1 == s.plusOne1(n1));
  EXPECT_TRUE(o2 == s.plusOne1(n2));
  EXPECT_TRUE(o3 == s.plusOne1(n3));
  EXPECT_TRUE(o1 == s.plusOne2(n1));
  EXPECT_TRUE(o2 == s.plusOne2(n2));
  EXPECT_TRUE(o3 == s.plusOne2(n3));
  EXPECT_SUMMARY;
}

int main()
{
  testPlusOne();
  return 0;
}
