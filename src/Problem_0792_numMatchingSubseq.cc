#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int nearLeftIndex(vector<int> &arr, int value)
  {
    int L = 0;
    int R = arr.size() - 1;
    int index = -1;
    while (L <= R)
    {
      int M = L + (R - L) / 2;
      if (arr[M] > value)
      {
        index = M;
        R = M - 1;
      }
      else
      {
        L = M + 1;
      }
    }
    return index;
  }

  int numMatchingSubseq(string s, vector<string> &words)
  {
    int ans = 0;
    int n = words.size();
    int m = s.length();
    unordered_map<char, vector<int>> map;
    // 记录每个字符在s出现的索引，同一个字符的vector内index一定是递增的
    for (int i = 0; i < m; i++)
    {
      map[s[i]].push_back(i);
    }
    for (string &word : words)
    {
      bool isIncreasing = true;
      int pre = -1;  // 记录上个字符在s出现的位置
      for (int i = 0; i < word.length() && isIncreasing; i++)
      {
        // 针对每一个单词的字符
        char c = word[i];
        vector<int> &idxs = map[c];  // 这里不用引用，LeetCode提交会超时
        // 找到当前字符在s的索引，这个索引必须大于上个字符在s的索引
        int cur = nearLeftIndex(idxs, pre);
        if (cur < 0 || idxs[cur] <= pre)
        {
          // 没有这个索引
          isIncreasing = false;
        }
        else
        {
          // 更新本次的索引
          pre = idxs[cur];
        }
      }
      if (isIncreasing)
      {
        // 单词遍历结束，索引都符合递增条件
        ans++;
      }
    }
    return ans;
  }
};

void testNumMatchingSubseq()
{
  Solution s;
  vector<string> w1 = {"a", "bb", "acd", "ace"};
  vector<string> w2 = {"ahjpjau", "ja", "ahbwzgqnuk", "tnmlanowax"};
  vector<string> w3 = {"wpddkvbnn",
                       "lnagtva",
                       "kvbnnuglnagtvamxkqtwhqgwbqgfbvgkwyuqkdwhzudsxvju",
                       "rwpddkvbnnugln",
                       "gloeofnpjqlkdsqvruvabjrikfwronbrdyyj",
                       "vbgeinupkvgmgxeaaiuiyojmoqkahwvbpwugdainxciedbdkos",
                       "mspuhbykmmumtveoighlcgpcapzczomshiblnvhjzqjlfkpina",
                       "rgmliajkiknongrofpugfgajedxicdhxinzjakwnifvxwlokip",
                       "fhepktaipapyrbylskxddypwmuuxyoivcewzrdwwlrlhqwzikq",
                       "qatithxifaaiwyszlkgoljzkkweqkjjzvymedvclfxwcezqebx"};
  EXPECT_EQ_INT(3, s.numMatchingSubseq("abcde", w1));
  EXPECT_EQ_INT(2, s.numMatchingSubseq("dsahjpjauf", w2));
  EXPECT_EQ_INT(5, s.numMatchingSubseq("rwpddkvbnnuglnagtvamxkqtwhqgwbqgfbvgkwyuqkdwhzudsxvjubjgloeofnpjqlkdsqvruvabjrikfwronbrdyyjnakstqjac", w3));
  EXPECT_SUMMARY;
}

int main()
{
  testNumMatchingSubseq();
  return 0;
}
