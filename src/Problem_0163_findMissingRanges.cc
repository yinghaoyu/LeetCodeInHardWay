#include <iostream>
#include <string>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  vector<string> findMissingRanges(vector<int> &nums, int lower, int upper)
  {
    vector<string> ans;
    for (int num : nums)
    {
      if (num > lower)
      {
        // 相邻的数，差值1以上
        ans.push_back(generate(lower, num - 1));
      }
      if (num == upper)
      {
        return ans;
      }
      lower = num + 1;
    }
    if (lower <= upper)
    {
      ans.push_back(generate(lower, upper));
    }
    return ans;
  }

  // 生成"lower->upper"的字符串，如果lower==upper，只用生成"lower"
  string generate(int lower, int upper)
  {
    string left = std::to_string(lower);
    string right = "";
    if (upper > lower)
    {
      right = "->" + std::to_string(upper);
    }
    return left + right;
  }
};

void testFindMissingRanges()
{
  Solution s;
  vector<int> n1 = {0, 1, 3, 50, 75};
  vector<string> o1 = {"2", "4->49", "51->74", "76->99"};
  vector<int> n2 = {-1};
  vector<string> o2;
  vector<int> n3;
  vector<string> o3 = {"1"};
  vector<int> n4;
  vector<string> o4 = {"50->100"};
  vector<int> n5 = {1, 2, 3, 4, 6, 8};
  vector<string> o5 = {"-1->0", "5", "7", "9->20"};
  EXPECT_TRUE(o1 == s.findMissingRanges(n1, 0, 99));
  EXPECT_TRUE(o2 == s.findMissingRanges(n2, -1, -1));
  EXPECT_TRUE(o3 == s.findMissingRanges(n3, 1, 1));
  EXPECT_TRUE(o4 == s.findMissingRanges(n4, 50, 100));
  EXPECT_TRUE(o5 == s.findMissingRanges(n5, -1, 20));
  EXPECT_SUMMARY;
}

int main()
{
  testFindMissingRanges();
  return 0;
}
