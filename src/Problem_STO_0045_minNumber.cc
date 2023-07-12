#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  string minNumber(vector<int> &nums)
  {
    auto cmp = [](string &a, string &b) { return a + b < b + a; };
    vector<string> strs;
    strs.reserve(nums.size());
    for (auto& num : nums)
    {
      strs.push_back(std::to_string(num));
    }

    std::sort(strs.begin(), strs.end(), cmp);

    string ans;
    for (auto& str : strs)
    {
      ans += str;
    }
    return ans;
  }
};

void test()
{
  Solution s;
  vector<int> n1 = {10, 2};
  vector<int> n2 = {3, 30, 34, 5, 9};
  EXPECT_TRUE("102" == s.minNumber(n1));
  EXPECT_TRUE("3033459" == s.minNumber(n2));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
