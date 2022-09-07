#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  vector<string> takeWords(const string &text)
  {
    int N = text.length();
    int pre = 0;
    vector<string> words;
    int state = 1;
    for (int i = 0; i < N; i++)
    {
      // 状态1：空格字符阶段
      // 状态2：非空格字符阶段
      if (state == 1 && text[i] != ' ')
      {
        // 状态1遇到非空格字符，记录单词开始位置，转到状态2
        pre = i;
        state = 2;
      }
      if (state == 2 && text[i] == ' ')
      {
        // 状态2遇到空格字符，结算单词，转到状态1
        words.push_back(string(text.begin() + pre, text.begin() + i));
        state = 1;
      }
    }
    // 最后一次如果在状态2，说明没有遇到空格
    if (state == 2)
    {
      words.push_back(string(text.begin() + pre, text.end()));
    }
    return words;
  }

  int spaceCount(const string &text)
  {
    int N = text.length();
    int spaces = 0;
    for (int i = 0; i < N; i++)
    {
      if (text[i] == ' ')
      {
        spaces++;
      }
    }
    return spaces;
  }

  string reorder(int spaces, const vector<string> &words)
  {
    string ans;
    int spc = words.size() > 1 ? spaces / (words.size() - 1) : 0;
    for (int i = 0; i < words.size(); i++)
    {
      if (i != words.size() - 1)
      {
        ans += words[i] + string(spc, ' ');
        spaces -= spc;
      }
      else
      {
        ans += words[i] + string(spaces, ' ');
      }
    }
    return ans;
  }

  string reorderSpaces(string text)
  {
    int spaces = spaceCount(text);
    vector<string> words = takeWords(text);
    return reorder(spaces, words);
  }
};

bool isEqualString(string s1, string s2)
{
  return s1 == s2;
}

void testReorderSpaces()
{
  Solution s;
  string test1 = "  this   is  a sentence ";
  string out1 = "this   is   a   sentence";

  string test2 = " practice   makes   perfect";
  string out2 = "practice   makes   perfect ";

  string test3 = " hello";
  string out3 = "hello ";

  EXPECT_TRUE(isEqualString(out1, s.reorderSpaces(test1)));
  EXPECT_TRUE(isEqualString(out2, s.reorderSpaces(test2)));
  EXPECT_TRUE(isEqualString(out3, s.reorderSpaces(test3)));
  EXPECT_SUMMARY;
}

int main()
{
  testReorderSpaces();
  return 0;
}
