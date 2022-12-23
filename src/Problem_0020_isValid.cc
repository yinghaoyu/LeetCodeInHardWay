#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  bool isValid(string s)
  {
    vector<char> stack;
    unordered_map<char, char> map = {{'(', ')'}, {'[', ']'}, {'{', '}'}};
    for (auto &c : s)
    {
      if (map.count(c))
      {
        stack.push_back(map[c]);
      }
      else
      {
        if (stack.empty())
        {
          return false;
        }
        if (stack.back() != c)
        {
          return false;
        }
        stack.pop_back();
      }
    }
    return stack.empty();
  }
};

void testIsValid()
{
  Solution s;
  EXPECT_TRUE(s.isValid("()"));
  EXPECT_TRUE(s.isValid("()[]{}"));
  EXPECT_FALSE(s.isValid("(]"));
  EXPECT_SUMMARY;
}

int main()
{
  testIsValid();
  return 0;
}
