#include <iostream>
#include <string>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  bool isCircularSentence(string sentence)
  {
    if (sentence.back() != sentence.front())
    {
      return false;
    }
    for (int i = 0; i < sentence.size(); i++)
    {
      if (sentence[i] == ' ' && sentence[i + 1] != sentence[i - 1])
      {
        return false;
      }
    }
    return true;
  }
};

void test()
{
  Solution s;
  EXPECT_TRUE(s.isCircularSentence("leetcode exercises sound delightful"));
  EXPECT_TRUE(s.isCircularSentence("eetcode"));
  EXPECT_FALSE(s.isCircularSentence("Leetcode is cool"));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
