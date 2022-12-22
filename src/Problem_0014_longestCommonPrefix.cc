#include <string>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  string longestCommonPrefix(vector<string> &strs)
  {
    if (strs.size() == 0)
    {
      return "";
    }
    string s0 = strs[0];
    int min = INT32_MAX;
    for (string &str : strs)
    {
      int index = 0;
      while (index < str.length() && index < s0.length())
      {
        if (s0[index] != str[index])
        {
          break;
        }
        index++;
      }
      min = std::min(index, min);
      if (min == 0)
      {
        return "";
      }
    }
    return strs[0].substr(0, min);
  }
};

void testLongestCommonPrefix()
{
  Solution s;
  vector<string> s1 = {"flower", "flow", "flight"};
  vector<string> s2 = {"dog", "racecar", "car"};
  EXPECT_TRUE("fl" == s.longestCommonPrefix(s1));
  EXPECT_TRUE("" == s.longestCommonPrefix(s2));
  EXPECT_SUMMARY;
}

int main()
{
  testLongestCommonPrefix();
  return 0;
}
