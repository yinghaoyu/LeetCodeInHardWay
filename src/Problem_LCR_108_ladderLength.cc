#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

// @sa https://leetcode.cn/problems/om3reC/
// @sa Problem_0127_ladderLength.cc
class Solution
{
 public:
  // 获取这个单词的所有邻接节点
  vector<string> getNext(string word, unordered_set<string>& dict)
  {
    vector<string> ans;
    for (char c = 'a'; c <= 'z'; c++)
    {
      for (int i = 0; i < word.length(); i++)
      {
        if (word[i] != c)
        {
          char tmp = word[i];
          word[i] = c;
          if (dict.count(word))
          {
            ans.push_back(word);
          }
          word[i] = tmp;
        }
      }
    }
    return ans;
  }

  // 建图
  unordered_map<string, vector<string>> getNexts(vector<string>& words)
  {
    unordered_set<string> dict(words.begin(), words.end());
    unordered_map<string, vector<string>> nexts;
    for (auto& word : words)
    {
      nexts.emplace(word, getNext(word, dict));
    }
    return nexts;
  }

  int ladderLength(string beginWord, string endWord, vector<string>& wordList)
  {
    wordList.push_back(beginWord);
    // 建图
    unordered_map<string, vector<string>> nexts = getNexts(wordList);
    // 距离表
    unordered_map<string, int> distanceMap;
    distanceMap.emplace(beginWord, 1);
    // 过滤访问过的单词
    unordered_set<string> set;
    set.emplace(beginWord);
    queue<string> q;
    q.push(beginWord);
    // bfs
    while (!q.empty())
    {
      string cur = q.front();
      q.pop();
      int distance = distanceMap[cur];
      for (auto& next : nexts[cur])
      {
        if (next == endWord)
        {
          return distance + 1;
        }
        if (!set.count(next))
        {
          set.emplace(next);
          q.push(next);
          distanceMap[next] = distance + 1;
        }
      }
    }
    return 0;
  }
};
