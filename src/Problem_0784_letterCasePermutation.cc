#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  void process(string s, int index, vector<string> &set)
  {
    if (index == s.length())
    {
      set.push_back(s);
      return;
    }
    if (('a' <= s[index] && s[index] <= 'z') || ('A' <= s[index] && s[index] <= 'Z'))
    {
      s[index] ^= 32;
      process(s, index + 1, set);
      s[index] ^= 32;
    }
    process(s, index + 1, set);
  }
  vector<string> letterCasePermutation(string s)
  {
    vector<string> ans;
    process(s, 0, ans);
    return ans;
  }
};

bool isVectorMemberEqual(vector<string> a, vector<string> b)
{
  if (a.size() != b.size())
  {
    return false;
  }
  std::sort(a.begin(), a.end());
  std::sort(b.begin(), b.end());
  for (int i = 0; i < a.size(); i++)
  {
    if (a[i] != b[i])
    {
      return false;
    }
  }
  return true;
}

void testLetterCasePermutation()
{
  Solution s;
  vector<string> o1 = {"a1b2", "a1B2", "A1b2", "A1B2"};
  vector<string> o2 = {"3z4", "3Z4"};
  EXPECT_TRUE(isVectorMemberEqual(o1, s.letterCasePermutation("a1b2")));
  EXPECT_TRUE(isVectorMemberEqual(o2, s.letterCasePermutation("3z4")));
  EXPECT_SUMMARY;
}

int main()
{
  testLetterCasePermutation();
  return 0;
}
