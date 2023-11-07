#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int vowelStrings(vector<string>& words, int left, int right)
  {
    unordered_set<char> vowels = {'a', 'e', 'i', 'o', 'u'};
    int ans = 0;
    for (int i = left; i <= right; i++)
    {
      ans += (vowels.count(words[i][0]) && vowels.count(words[i].back()));
    }
    return ans;
  }
};

void test()
{
  Solution s;
  vector<string> w1 = {"are", "amy", "u"};
  vector<string> w2 = {"hey", "aeo", "mu", "ooo", "artro"};
  EXPECT_EQ_INT(2, s.vowelStrings(w1, 0, 2));
  EXPECT_EQ_INT(3, s.vowelStrings(w2, 1, 4));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
