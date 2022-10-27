#include <iostream>
#include <string>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  bool checkOnesSegment1(string s)
  {
    int c = 0;
    int i = 0;
    int N = s.length();
    while (i < N && s[i] == '1')
    {
      i++;
      c++;
    }
    while (i < N && s[i] == '0')
    {
      i++;
      c++;
    }
    return c == N;
  }

  bool checkOnesSegment2(string s) { return s.find("01") == string::npos; }
};

void testCheckOnesSegment()
{
  Solution s;
  EXPECT_FALSE(s.checkOnesSegment1("1001"));
  EXPECT_TRUE(s.checkOnesSegment1("110"));
  EXPECT_TRUE(s.checkOnesSegment1("1"));
  EXPECT_FALSE(s.checkOnesSegment2("1001"));
  EXPECT_TRUE(s.checkOnesSegment2("110"));
  EXPECT_TRUE(s.checkOnesSegment2("1"));
  EXPECT_SUMMARY;
}

int main()
{
  testCheckOnesSegment();
  return 0;
}
