#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
   // 动态规划
  int longestStrChain(vector<string> &words)
  {
    unordered_map<string, int> map;
    // 按长度排序
    std::sort(words.begin(), words.end(), [](const string &l, const string &r) { return l.size() < r.size(); });
    int ans = 0;
    for (auto &word : words)
    {
      // 每个单词至少能构成长度为 1 的链
      map[word] = 1;
      for (int i = 0; i < word.size(); i++)
      {
        // pre 的字符比当前的 word 少一个字符
        string pre = word.substr(0, i) + word.substr(i + 1);
        if (map.count(pre))
        {
          // 如果 pre 早已经在 map 内，就更新一下
          map[word] = std::max(map[word], map[pre] + 1);
        }
      }
      ans = std::max(ans, map[word]);
    }
    return ans;
  }
};

void testLongestStrChain()
{
  Solution s;
  vector<string> w1 = {"a", "b", "ba", "bca", "bda", "bdca"};
  vector<string> w2 = {"xbc", "pcxbcf", "xb", "cxbc", "pcxbc"};
  vector<string> w3 = {"abcd", "dbqca"};
  EXPECT_EQ_INT(4, s.longestStrChain(w1));
  EXPECT_EQ_INT(5, s.longestStrChain(w2));
  EXPECT_EQ_INT(1, s.longestStrChain(w3));
  EXPECT_SUMMARY;
}

int main()
{
  testLongestStrChain();
  return 0;
}
