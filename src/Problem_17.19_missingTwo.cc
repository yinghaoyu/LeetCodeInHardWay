#include <algorithm>
#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int lowBit(int x) { return x & -x; }

  vector<int> missingTwo(vector<int> &nums)
  {
    int xorSum = 0;
    int N = nums.size() + 2;
    for (int n : nums)
    {
      xorSum ^= n;
    }
    for (int i = 1; i <= N; i++)
    {
      xorSum ^= i;
    }
    // xorSum = a ^ b
    int lowbit = lowBit(xorSum);
    int a = 0, b = 0;
    for (int n : nums)
    {
      if (n & lowbit)
      {
        a ^= n;
      }
      else
      {
        b ^= n;
      }
    }
    for (int i = 1; i <= N; i++)
    {
      if (i & lowbit)
      {
        a ^= i;
      }
      else
      {
        b ^= i;
      }
    }
    return {a, b};
  }
};

bool isVectorEqual(vector<int> a, vector<int> b)
{
  if (a.size() != b.size())
  {
    return false;
  }
  std::sort(a.begin(), a.end());
  std::sort(b.begin(), b.end());
  for (int i = 0; i < a.size(); i++)
  {
    if (a[i] != b[i])
    {
      return false;
    }
  }
  return true;
}

void testMissingTwo()
{
  Solution s;
  vector<int> in1 = {1};
  vector<int> out1 = {2, 3};

  vector<int> in2 = {2, 3};
  vector<int> out2 = {1, 4};
  EXPECT_TRUE(isVectorEqual(out1, s.missingTwo(in1)));
  EXPECT_TRUE(isVectorEqual(out2, s.missingTwo(in2)));
  EXPECT_SUMMARY;
}

int main()
{
  testMissingTwo();
  return 0;
}
