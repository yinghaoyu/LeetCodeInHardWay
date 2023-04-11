#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  // TODO: figure it out
  int distinctSubseqII(string str)
  {
    if (str.length() == 0)
    {
      return 0;
    }
    int m = 1000000007;
    vector<int> count(26);
    int all = 1;
    for (char x : str)
    {
      int newAdd = (all - count[x - 'a'] + m) % m;
      all = (all + newAdd) % m;
      count[x - 'a'] = (count[x - 'a'] + newAdd) % m;
    }
    return (all - 1 + m) % m;
  }
};

void testDistinctSubseqII()
{
  Solution s;
  EXPECT_EQ_INT(7, s.distinctSubseqII("abc"));
  EXPECT_EQ_INT(6, s.distinctSubseqII("aba"));
  EXPECT_EQ_INT(3, s.distinctSubseqII("aaa"));
  EXPECT_SUMMARY;
}

int main()
{
  testDistinctSubseqII();
  return 0;
}
