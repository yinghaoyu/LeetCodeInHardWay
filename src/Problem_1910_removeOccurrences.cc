#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  string removeOccurrences(string s, string part)
  {
    string stack;
    int n = part.length();
    for (auto &c : s)
    {
      stack.push_back(c);
      if (stack.size() >= n && stack.substr(stack.length() - n, n) == part)
      {
        stack.erase(stack.end() - n, stack.end());
      }
    }
    return stack;
  }
};

void testRemoveOccurrences()
{
  Solution s;
  EXPECT_TRUE("dab" == s.removeOccurrences("daabcbaabcbc", "abc"));
  EXPECT_TRUE("ab" == s.removeOccurrences("axxxxyyyyb", "xy"));
  EXPECT_SUMMARY;
}

int main()
{
  testRemoveOccurrences();
  return 0;
}
