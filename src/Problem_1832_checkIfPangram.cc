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
    int cnt[26] = {0};
    int n = sentence.length();
    for (int i = 0; i < n; i++)
    {
      cnt[sentence[i] - 'a']++;
    }
    for (int i = 0; i < 26; i++)
    {
      if (cnt[i] == 0)
      {
        return false;
      }
    }
    return true;
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
