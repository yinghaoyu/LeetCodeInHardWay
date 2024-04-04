#include <queue>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution
{
 public:
  vector<string> findLadders(string beginWord, string endWord, vector<string>& wordList)
  {
    unordered_set<string> dict(wordList.begin(), wordList.end());
    if (!dict.count(endWord))
    {
      return {};
    }

    queue<vector<string>> q;
    q.push({beginWord});
    dict.erase(beginWord);

    while (!q.empty())
    {
      int size = q.size();
      while (size-- > 0)
      {
        vector<string> path = q.front();
        q.pop();
        string word = path.back();

        for (int i = 0; i < word.size(); ++i)
        {
          char old = word[i];
          for (char ch = 'a'; ch <= 'z'; ++ch)
          {
            if (ch == old)
            {
              continue;
            }
            word[i] = ch;
            if (dict.count(word))
            {
              // 注意，这里不能直接path.push_back(word)，因为要尝试不同的可能性
              vector<string> next(path);
              next.push_back(word);
              dict.erase(word);
              if (word == endWord)
              {
                return next;
              }
              else
              {
                q.push(next);
              }
            }
          }
          // 不要忘记恢复
          word[i] = old;
        }
      }
    }

    return {};
  }
};
