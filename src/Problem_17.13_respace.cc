#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution
{
 public:
  int respace(vector<string>& dictionary, string sentence)
  {
    Tire t;
    for (auto& word : dictionary)
    {
      t.insert(word);
    }

    int n = sentence.size();
    // dp[i] 表示考虑前 i 个字符最少的未识别的字符数量
    vector<int> dp(n + 1, INT32_MAX);
    // 0个字符当然是0
    dp[0] = 0;
    for (int i = 1; i <= n; i++)
    {
      // 情况一：sentence[i - 1] 未被识别
      dp[i] = dp[i - 1] + 1;
      // 情况二：sentence[j-1 ... i-1] 被识别
      Node* node = t.root;
      for (int j = i; j >= 1; j--)
      {
        int idx = sentence[j - 1];
        if (!node->nexts.count(idx))
        {
          break;
        }
        else if (node->nexts.at(idx)->end)
        {
          // 说明 sentence[j-1 ... i-1]是一个单词
          dp[i] = std::min(dp[i], dp[j - 1]);
        }
        if (dp[i] == 0)
        {
          break;
        }
        node = node->nexts.at(idx);
      }
    }
    return dp[n];
  }

  class Node
  {
   public:
    int pass;
    int end;

    Node()
    {
      pass = 0;
      end = 0;
    }

    unordered_map<int, Node*> nexts;
  };

  class Tire
  {
   public:
    Node* root;

    Tire() { root = new Node(); }

    void insert(string& word)
    {
      if (word.empty())
      {
        return;
      }
      Node* node = root;
      node->pass++;
      int n = word.length();
      // 逆向建树
      for (int i = n - 1; i >= 0; i--)
      {
        int idx = word[i];
        if (!node->nexts.count(idx))
        {
          node->nexts.emplace(idx, new Node());
        }
        node = node->nexts.at(idx);
        node->pass++;
      }
      node->end++;
    }

    int search(string& word)
    {
      if (word.empty())
      {
        return 0;
      }
      Node* node = root;
      int n = word.length();
      for (int i = n - 1; i >= 0; i--)
      {
        int idx = word[i];
        if (!node->nexts.count(idx))
        {
          return 0;
        }
        node = node->nexts.at(idx);
      }
      return node->end;
    }

    void del(string& word)
    {
      if (search(word) != 0)
      {
        Node* node = root;
        node->pass--;
        int n = word.length();
        for (int i = n - 1; i >= 0; i--)
        {
          int idx = word[i];
          if (--node->nexts.at(idx) == 0)
          {
            node->nexts.erase(idx);
            return;
          }
          node = node->nexts.at(idx);
        }
        node->end--;
      }
    }
  };
};
