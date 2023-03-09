#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  void reverseString(vector<char> &s)
  {
    int l = 0;
    int r = s.size();
    while (l < r)
    {
      swap(s, l++, --r);
    }
  }

  void swap(vector<char> &s, int i, int j)
  {
    char tmp = s[i];
    s[i] = s[j];
    s[j] = tmp;
  }
};

void testReverseString()
{
  Solution s;
  vector<char> s1 = {'h', 'e', 'l', 'l', 'o'};
  vector<char> o1 = {'o', 'l', 'l', 'e', 'h'};
  vector<char> s2 = {'H', 'a', 'n', 'n', 'a', 'h'};
  vector<char> o2 = {'h', 'a', 'n', 'n', 'a', 'H'};
  s.reverseString(s1);
  s.reverseString(s2);
  EXPECT_TRUE(o1 == s1);
  EXPECT_TRUE(o2 == s2);
  EXPECT_SUMMARY;
}

int main()
{
  testReverseString();
  return 0;
}
