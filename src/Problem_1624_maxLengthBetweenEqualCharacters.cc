#include <iostream>
#include <string>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int maxLengthBetweenEqualCharacters(string s)
  {
    vector<int> pre(26, -1);
    int ans = -1;
    for (int i = 0; i < s.length(); i++)
    {
      int idx = s[i] - 'a';
      if (pre[idx] != -1)
      {
        ans = std::max(ans, i - pre[idx] - 1);
      }
      else
      {
        pre[idx] = i;
      }
    }
    return ans;
  }
};

void testMaxLengthBetweenEqualCharacters()
{
  Solution s;
  EXPECT_EQ_INT(0, s.maxLengthBetweenEqualCharacters("aa"));
  EXPECT_EQ_INT(2, s.maxLengthBetweenEqualCharacters("abca"));
  EXPECT_EQ_INT(-1, s.maxLengthBetweenEqualCharacters("cbzxy"));
  EXPECT_EQ_INT(18, s.maxLengthBetweenEqualCharacters("mgntdygtxrvxjnwksqhxuxtrv"));
  EXPECT_EQ_INT(18, s.maxLengthBetweenEqualCharacters("mgntdygtxrvxjnwksqhxuxtrv"));
  EXPECT_SUMMARY;
}

int main()
{
  testMaxLengthBetweenEqualCharacters();
  return 0;
}
