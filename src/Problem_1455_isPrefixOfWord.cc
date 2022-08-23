#include <iostream>
#include <string>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  bool isPrefix(const string &sentence, int start, int end, const string &searchWord)
  {
    for (int i = 0; i < searchWord.size(); i++)
    {
      if (start + i >= end || sentence[start + i] != searchWord[i])
      {
        return false;
      }
    }
    return true;
  }

  // 双指针
  int isPrefixOfWord(string sentence, string searchWord)
  {
    int n = sentence.size(), index = 1, start = 0, end = 0;
    while (start < n)
    {
      while (end < n && sentence[end] != ' ')
      {
        end++;
      }
      if (isPrefix(sentence, start, end, searchWord))
      {
        return index;
      }

      index++;
      end++;
      start = end;
    }
    return -1;
  }
};

void testIsPrefixOfWord()
{
  string str1 = "i love eating burger";
  string word1 = "burg";

  string str2 = "this problem is an easy problem";
  string word2 = "pro";

  string str3 = "i am tired";
  string word3 = "you";
  Solution s;
  EXPECT_EQ_INT(4, s.isPrefixOfWord(str1, word1));
  EXPECT_EQ_INT(2, s.isPrefixOfWord(str2, word2));
  EXPECT_EQ_INT(-1, s.isPrefixOfWord(str3, word3));
  EXPECT_SUMMARY;
}

int main()
{
  testIsPrefixOfWord();
  return 0;
}
