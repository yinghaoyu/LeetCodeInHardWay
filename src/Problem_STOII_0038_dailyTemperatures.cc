#include <iostream>
#include <vector>

using namespace std;

// seem as leetcode 0739
// https://leetcode-cn.com/problems/daily-temperatures/
// see at Problem_0739_dailyTemperatures.cc
class Solution
{
 public:
  vector<int> dailyTemperatures(vector<int> &temperatures)
  {
    int n = temperatures.size();
    vector<int> stack;
    vector<int> ans(n);
    for (int i = 0; i < n; i++)
    {
      while (!stack.empty() && temperatures[stack.back()] < temperatures[i])
      {
        ans[stack.back()] = i - stack.back();
        stack.pop_back();
      }
      stack.push_back(i);
    }
    return ans;
  }
};
