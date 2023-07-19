#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  bool isAlienSorted(vector<string> &words, string order)
  {
    vector<int> idx(26);
    for (int i = 0; i < order.length(); i++)
    {
      // 记录字符序
      idx[order[i] - 'a'] = i;
    }
    for (int i = 1; i < words.size(); i++)
    {
      bool valid = false;
      for (int j = 0; j < words[i - 1].size() && j < words[i].size(); j++)
      {
        // 比较相邻两个单词的字符序
        int pre = idx[words[i - 1][j] - 'a'];
        int cur = idx[words[i][j] - 'a'];
        if (pre < cur)
        {
          valid = true;
          break;
        }
        else if (pre > cur)
        {
          return false;
        }
      }
      if (!valid)
      {
        if (words[i - 1].size() > words[i].size())
        {
          return false;
        }
      }
    }

    return true;
  }
};

void test()
{
  Solution s;
  vector<string> w1 = {"hello", "leetcode"};
  vector<string> w2 = {"word", "world", "row"};
  vector<string> w3 = {"apple", "app"};
  EXPECT_TRUE(s.isAlienSorted(w1, "hlabcdefgijkmnopqrstuvwxyz"));
  EXPECT_FALSE(s.isAlienSorted(w2, "worldabcefghijkmnpqstuvxyz"));
  EXPECT_FALSE(s.isAlienSorted(w3, "abcdefghijklmnopqrstuvwxyz"));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
