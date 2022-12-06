#include <cctype>
#include <cstdlib>
#include <iostream>
#include <string>
#include <unordered_set>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int numDifferentIntegers(string word)
  {
    int n = word.size();
    int l = 0;
    int r = 0;
    unordered_set<string> set;
    while (true)
    {
      while (l < n && !std::isdigit(word[l]))
      {
        l++;
      }
      if (l == n)
      {
        break;
      }
      r = l;
      while (r < n && std::isdigit(word[r]))
      {
        r++;
      }
      while (r - l > 1 && word[l] == '0')
      {
        l++;
      }
      set.insert(word.substr(l, r - l));
      l = r;
    }
    return set.size();
  }
};

void testNumDifferentIntegers()
{
  Solution s;
  EXPECT_EQ_INT(3, s.numDifferentIntegers("a123bc34d8ef34"));
  EXPECT_EQ_INT(2, s.numDifferentIntegers("leet1234code234"));
  EXPECT_EQ_INT(1, s.numDifferentIntegers("a1b01c001"));
  EXPECT_SUMMARY;
}

int main()
{
  testNumDifferentIntegers();
  return 0;
}
