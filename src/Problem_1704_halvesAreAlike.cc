#include <iostream>
#include <string>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  bool isVowel(char c)
  {
    bool p1 = c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
    bool p2 = c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U';
    return p1 || p2;
  }

  bool halvesAreAlike(string s)
  {
    int n = s.length();
    if (n & 1)
    {
      return false;
    }
    int vowels = 0;
    for (int i = 0; i < n / 2; i++)
    {
      if (isVowel(s[i]))
      {
        vowels++;
      }
    }
    for (int i = n / 2; i < n; i++)
    {
      if (isVowel(s[i]))
      {
        vowels--;
      }
    }
    return vowels == 0;
  }
};

void testHalvesAreAlike()
{
  Solution s;
  EXPECT_TRUE(s.halvesAreAlike("book"));
  EXPECT_FALSE(s.halvesAreAlike("textbook"));
  EXPECT_SUMMARY;
}

int main()
{
  testHalvesAreAlike();
  return 0;
}
