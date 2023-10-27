#include <algorithm>
#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 private:
  int getMax(vector<int>& arr, int last)
  {
    int ans = 0;
    int pre = 0;
    for (auto& i : arr)
    {
      ans = std::max(i - pre, ans);
      pre = i;
    }
    return std::max(ans, last - pre);
  }

 public:
  int maxArea(int h, int w, vector<int>& horizontalCuts, vector<int>& verticalCuts)
  {
    static const int mod = 1e9 + 7;
    std::sort(horizontalCuts.begin(), horizontalCuts.end());
    std::sort(verticalCuts.begin(), verticalCuts.end());
    return (long long) getMax(horizontalCuts, h) * getMax(verticalCuts, w) % mod;
  }
};

void test()
{
  Solution s;
  vector<int> h1 = {1, 2, 4};
  vector<int> v1 = {1, 3};
  vector<int> h2 = {3, 1};
  vector<int> v2 = {1};
  vector<int> h3 = {3};
  vector<int> v3 = {3};
  EXPECT_EQ_INT(4, s.maxArea(5, 4, h1, v1));
  EXPECT_EQ_INT(6, s.maxArea(5, 4, h2, v2));
  EXPECT_EQ_INT(9, s.maxArea(5, 4, h3, v3));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
