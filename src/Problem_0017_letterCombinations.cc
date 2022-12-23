#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  void dfs(string &digits, int cur, string str, vector<string> &ans, unordered_map<char, vector<char>> &map)
  {
    if (cur == digits.length())
    {
      ans.push_back(str);
    }
    for (auto &c : map[digits[cur]])
    {
      str.push_back(c);
      dfs(digits, cur + 1, str, ans, map);
      str.pop_back();
    }
  }
  vector<string> letterCombinations(string digits)
  {
    unordered_map<char, vector<char>> map = {{'1', {}},
                                             {'2', {'a', 'b', 'c'}},
                                             {'3', {'d', 'e', 'f'}},
                                             {'4', {'g', 'h', 'i'}},
                                             {'5', {'j', 'k', 'l'}},
                                             {'6', {'m', 'n', 'o'}},
                                             {'7', {'p', 'q', 'r', 's'}},
                                             {'8', {'t', 'u', 'v'}},
                                             {'9', {'w', 'x', 'y', 'z'}}};
    vector<string> ans;
    if(digits.length() == 0)
    {
      return ans;
    }
    dfs(digits, 0, "", ans, map);
    return ans;
  }
};

bool isVectorEuqal(vector<string> a, vector<string> b)
{
  return a == b;
}

void testLetterCombinations()
{
  Solution s;
  vector<string> s1 = {"ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"};
  vector<string> s2 = {};
  vector<string> s3 = {"a", "b", "c"};
  EXPECT_TRUE(isVectorEuqal(s1, s.letterCombinations("23")));
  EXPECT_TRUE(isVectorEuqal(s2, s.letterCombinations("")));
  EXPECT_TRUE(isVectorEuqal(s3, s.letterCombinations("2")));
  EXPECT_SUMMARY;
}

int main()
{
  testLetterCombinations();
  return 0;
}
