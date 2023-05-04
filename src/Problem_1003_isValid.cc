#include <iostream>
#include <string>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  bool isValid(string s)
  {
    string stack;
    // 跟 ()(()) 做法类似，) 进栈时，判断栈顶是不是 (，如果是则出栈
    for (auto &c : s)
    {
      stack.push_back(c);
      if (stack.size() >= 3 && stack.substr(stack.length() - 3, 3) == "abc")
      {
        stack.erase(stack.end() - 3, stack.end());
      }
    }
    return stack.empty();
  }
};

void testIsValid()
{
  Solution s;
  EXPECT_TRUE(s.isValid("aabcbc"));
  EXPECT_TRUE(s.isValid("abcabcababcc"));
  EXPECT_FALSE(s.isValid("abccba"));
  EXPECT_SUMMARY;
}

int main()
{
  testIsValid();
  return 0;
}
