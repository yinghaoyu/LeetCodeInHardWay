#include <string>
#include <unordered_map>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  char firstUniqChar(string s)
  {
    unordered_map<char, int> map;
    for (auto &c : s)
    {
      map[c]++;
    }
    for (auto &c : s)
    {
      if (map[c] == 1)
      {
        return c;
      }
    }
    return ' ';
  }
};

void test()
{
  Solution s;
  EXPECT_TRUE('b' == s.firstUniqChar("abaccdeff"));
  EXPECT_TRUE(' ' == s.firstUniqChar(""));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
