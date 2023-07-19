#include <iostream>
#include <string>
#include <vector>

using namespace std;

// seem as leetcode 0953
// https://leetcode-cn.com/problems/verifying-an-alien-dictionary/
// see at Problem_0953_isAlienSorted.cc
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
