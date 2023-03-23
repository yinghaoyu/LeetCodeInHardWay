#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  vector<int> dailyTemperatures(vector<int> &temperatures)
  {
    int N = temperatures.size();
    vector<int> ans(N);
    vector<int> stack;
    for (int i = 0; i < temperatures.size(); ++i)
    {
      while (!stack.empty() && temperatures[i] > temperatures[stack.back()])
      {
        auto t = stack.back();
        stack.pop_back();
        ans[t] = i - t;
      }
      stack.push_back(i);
    }
    return ans;
  }
};

void testDailyTemperatures()
{
  Solution s;
  vector<int> t1 = {73, 74, 75, 71, 69, 72, 76, 73};
  vector<int> o1 = {1, 1, 4, 2, 1, 1, 0, 0};
  vector<int> t2 = {30, 40, 50, 60};
  vector<int> o2 = {1, 1, 1, 0};
  vector<int> t3 = {30, 60, 90};
  vector<int> o3 = {1, 1, 0};
  EXPECT_TRUE(o1 == s.dailyTemperatures(t1));
  EXPECT_TRUE(o2 == s.dailyTemperatures(t2));
  EXPECT_TRUE(o3 == s.dailyTemperatures(t3));
  EXPECT_SUMMARY;
}

int main()
{
  testDailyTemperatures();
  return 0;
}
