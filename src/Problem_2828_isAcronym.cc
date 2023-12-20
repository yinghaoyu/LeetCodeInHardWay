#include <string>
#include <vector>

#include "UnitTest.h"

using namespace std;
class Solution
{
 public:
  bool isAcronym(vector<string>& words, string s)
  {
    if (s.size() != words.size())
    {
      return false;
    }
    for (int i = 0; i < s.size(); i++)
    {
      if (words[i][0] != s[i])
      {
        return false;
      }
    }
    return true;
  }
};

void test()
{
  Solution s;
  vector<string> w1 = {"alice", "bob", "charlie"};
  vector<string> w2 = {"an", "apple"};
  vector<string> w3 = {"never", "gonna", "give", "up", "on", "you"};
  EXPECT_TRUE(s.isAcronym(w1, "abc"));
  EXPECT_FALSE(s.isAcronym(w2, "a"));
  EXPECT_TRUE(s.isAcronym(w3, "ngguoy"));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
