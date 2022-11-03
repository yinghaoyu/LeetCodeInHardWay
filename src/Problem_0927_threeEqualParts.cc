#include <iostream>
#include <numeric>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  vector<int> threeEqualParts(vector<int> &arr)
  {
    int sum = std::accumulate(arr.begin(), arr.end(), 0);
    if (sum % 3 != 0)
    {
      return {-1, -1};
    }
    if (sum == 0)
    {
      return {0, 2};
    }
    int avg = sum / 3;
    int l = 0;
    int m = 0;
    int r = 0;
    int cur = 0;
    int n = arr.size();
    for (int i = 0; i < n; i++)
    {
      if (arr[i] == 1)
      {
        if (cur == 0)
        {
          l = i;
        }
        else if (cur == avg)
        {
          m = i;
        }
        else if (cur == 2 * avg)
        {
          r = i;
        }
        cur++;
      }
    }
    int len = n - r;
    if (l + len <= m && m + l <= r)
    {
      int i = 0;
      while (r + i < n)
      {
        if (arr[l + i] != arr[m + i] || arr[l + i] != arr[r + i])
        {
          return {-1, -1};
        }
        i++;
      }
      return {l + len - 1, m + len};
    }
    return {-1, -1};
  }
};

bool isVectorEqual(vector<int> a, vector<int> b)
{
  if (a.size() != b.size())
  {
    return false;
  }
  for (int i = 0; i < a.size(); i++)
  {
    if (a[i] != b[i])
    {
      return false;
    }
  }
  return true;
}

void testThreeEqualParts()
{
  Solution s;
  vector<int> n1 = {1, 0, 1, 0, 1};
  vector<int> n2 = {1, 1, 0, 1, 1};
  vector<int> n3 = {1, 1, 0, 0, 1};
  vector<int> n4 = {0, 0, 0, 0, 0};
  vector<int> n5 = {1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0,
                    1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0};
  vector<int> o1 = {0, 3};
  vector<int> o2 = {-1, -1};
  vector<int> o3 = {0, 2};
  vector<int> o4 = {0, 2};
  vector<int> o5 = {15, 32};
  EXPECT_TRUE(isVectorEqual(o1, s.threeEqualParts(n1)));
  EXPECT_TRUE(isVectorEqual(o2, s.threeEqualParts(n2)));
  EXPECT_TRUE(isVectorEqual(o3, s.threeEqualParts(n3)));
  EXPECT_TRUE(isVectorEqual(o4, s.threeEqualParts(n4)));
  EXPECT_TRUE(isVectorEqual(o5, s.threeEqualParts(n5)));
  EXPECT_SUMMARY;
}

int main()
{
  testThreeEqualParts();
  return 0;
}
