#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  string replaceSpace1(string s)
  {
    int space = 0;
    int len = s.length();
    for (auto &c : s)
    {
      if (c == ' ')
      {
        space++;
      }
    }
    s.resize(len + 2 * space);
    for (int i = len - 1, j = s.length() - 1; i >= 0; i--, j--)
    {
      if (s[i] != ' ')
      {
        s[j] = s[i];
      }
      else
      {
        s[j - 2] = '%';
        s[j - 1] = '2';
        s[j] = '0';
        j -= 2;
      }
    }
    return s;
  }

  string replaceSpace2(string s)
  {
    int pos = 0;
    while ((pos = s.find(" ")) != string::npos)
    {
      s.replace(pos, 1, "%20");
    }
    return s;
  }
};

void testReplaceSpace()
{
  Solution s;
  EXPECT_TRUE("We%20are%20happy." == s.replaceSpace1("We are happy."));
  EXPECT_TRUE("We%20are%20happy." == s.replaceSpace2("We are happy."));
  EXPECT_SUMMARY;
}

int main()
{
  testReplaceSpace();
  return 0;
}
