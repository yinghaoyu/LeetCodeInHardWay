#include <cstdlib>
#include <iostream>
#include <string>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  bool checkIfPangram(string sentence)
  {
    int mask = 0;
    int n = sentence.length();
    for (int i = 0; i < n; i++)
    {
      mask |= 1 << (sentence[i] - 'a');
    }
    return mask == (1 << 26) - 1;
  }
};

void testCheckIfPangram()
{
  Solution s;
  EXPECT_TRUE(s.checkIfPangram("thequickbrownfoxjumpsoverthelazydog"));
  EXPECT_FALSE(s.checkIfPangram("leetcode"));
  EXPECT_SUMMARY;
}

int main()
{
  testCheckIfPangram();
  return 0;
}
