#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  class MyComparator
  {
   public:
    bool operator()(string o1, string o2) { return (o2 + o1) < (o1 + o2); }
  };

  string largestNumber(vector<int> &nums)
  {
    int n = nums.size();
    vector<string> strs(n);
    for (int i = 0; i < n; i++)
    {
      strs[i] = std::to_string(nums[i]);
    }
    std::sort(strs.begin(), strs.end(), MyComparator());
    string ans;
    for (auto &str : strs)
    {
      ans.append(str);
    }
    int index = -1;
    for (int i = 0; i < ans.length(); i++)
    {
      if (ans[i] != '0')
      {
        index = i;
        break;
      }
    }
    return index == -1 ? "0" : ans.substr(index);
  }
};

void testLargestNumber()
{
  Solution s;
  vector<int> n1 = {10, 2};
  vector<int> n2 = {3, 30, 34, 5, 9};
  EXPECT_TRUE("210" == s.largestNumber(n1));
  EXPECT_TRUE("9534330" == s.largestNumber(n2));
  EXPECT_SUMMARY;
}

int main()
{
  testLargestNumber();
  return 0;
}
