#include <queue>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  // 应该根据具体数据状况决定用什么来找邻居
  // 1)如果字符串长度比较短，字符串数量比较多，以下方法适合
  // 2)如果字符串长度比较长，字符串数量比较少，以下方法不适合
  vector<string> getNext(string word, unordered_set<string>& dict)
  {
    vector<string> res;
    for (char cur = 'a'; cur <= 'z'; cur++)
    {
      for (int i = 0; i < word.length(); i++)
      {
        if (word[i] != cur)
        {
          // current word such as "dog"
          // then list all d?g
          char tmp = word[i];
          word[i] = cur;
          if (dict.count(word))
          {
            res.push_back(word);
          }
          word[i] = tmp;
        }
      }
    }
    return res;
  }

  unordered_map<string, vector<string>> getNexts(vector<string>& words)
  {
    unordered_set<string> dict(words.begin(), words.end());
    unordered_map<string, vector<string>> nexts;
    for (int i = 0; i < words.size(); i++)
    {
      // save next words only one char difference with current word
      nexts.emplace(words[i], getNext(words[i], dict));
    }
    return nexts;
  }

  // 普通 bfs
  int ladderLength1(string beginWord, string endWord, vector<string>& wordList)
  {
    wordList.push_back(beginWord);
    unordered_map<string, vector<string>> nexts = getNexts(wordList);
    unordered_map<string, int> distanceMap;
    distanceMap.emplace(beginWord, 1);
    unordered_set<string> set;
    set.emplace(beginWord);
    queue<string> queue;
    queue.push(beginWord);
    // bfs
    while (!queue.empty())
    {
      string cur = queue.front();
      queue.pop();
      int distance = distanceMap.at(cur);
      for (string next : nexts.at(cur))
      {
        if (next == endWord)
        {
          return distance + 1;
        }
        // filter visited word
        if (!set.count(next))
        {
          set.emplace(next);
          queue.push(next);
          distanceMap.emplace(next, distance + 1);
        }
      }
    }
    return 0;
  }

  // 针对普通 bfs，利用双向 bfs，降低常数复杂度
  // begin -> {10单词}
  //   end -> {5单词} 明显这一轮从单词 end 进行 bfs 的分支更少
  int ladderLength2(string beginWord, string endWord, vector<string>& wordList)
  {
    // 总词表
    unordered_set<string> dict(wordList.begin(), wordList.end());
    if (!dict.count(endWord))
    {
      return 0;
    }
    // 数量小的一侧
    unordered_set<string> smallLevel;
    // 数量大的一侧
    unordered_set<string> bigLevel;
    // 由数量小的一侧，所扩展出的下一层
    unordered_set<string> nextLevel;
    smallLevel.emplace(beginWord);
    bigLevel.emplace(endWord);
    for (int len = 2; !smallLevel.empty(); len++)
    {
      for (auto word : smallLevel)
      {
        // 从小侧扩展
        for (int i = 0; i < word.length(); i++)
        {
          // 每一位字符都尝试
          char old = word[i];
          for (char c = 'a'; c <= 'z'; c++)
          {
            if (c == old)
            {
              continue;
            }
            word[i] = c;
            if (bigLevel.count(word))
            {
              return len;
            }
            if (dict.count(word))
            {
              dict.erase(word);
              nextLevel.emplace(word);
            }
          }
          word[i] = old;
        }
      }
      if (nextLevel.size() <= bigLevel.size())
      {
        smallLevel = std::move(nextLevel);
      }
      else
      {
        smallLevel = std::move(bigLevel);
        bigLevel = std::move(nextLevel);
      }
    }
    return 0;
  }
};

void testLadderLength()
{
  Solution s;
  vector<string> w1 = {"hot", "dot", "dog", "lot", "log", "cog"};
  vector<string> w2 = {"hot", "dot", "dog", "lot", "log"};
  EXPECT_EQ_INT(5, s.ladderLength1("hit", "cog", w1));
  EXPECT_EQ_INT(0, s.ladderLength1("hit", "cog", w2));
  EXPECT_SUMMARY;
}

int main()
{
  testLadderLength();
  return 0;
}
