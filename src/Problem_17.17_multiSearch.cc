#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution
{
 public:
  vector<vector<int>> multiSearch(string big, vector<string>& smalls)
  {
    int n = smalls.size();
    Trie t;
    for (int i = 0; i < n; i++)
    {
      // 建立字典树，单词末尾保存 index
      t.insert(smalls[i], i);
    }

    int m = big.length();
    vector<vector<int>> ans(n);
    for (int i = 0; i < m; i++)
    {
      // 检查必须以 big[i] 开头，big[i...m]中有多少个符合的单词
      // 即检查后缀字符串
      string str = big.substr(i);
      t.search(str, ans, i);
    }
    return ans;
  }

  class Node
  {
   public:
    int pass;
    int end;
    int idx;
    unordered_map<int, Node*> nexts;

    Node()
    {
      pass = 0;
      end = 0;
      idx = -1;
    }
  };

  class Trie
  {
   public:
    Node* root;

    Trie() { root = new Node(); }

    void insert(string& word, int idx)
    {
      if (word.empty())
      {
        return;
      }
      int n = word.length();
      Node* node = root;
      node->pass++;
      for (int i = 0; i < n; i++)
      {
        int key = word[i];
        if (!node->nexts.count(key))
        {
          node->nexts.emplace(key, new Node());
        }
        node = node->nexts.at(key);
        node->pass++;
      }
      node->end++;
      node->idx = idx;
    }

    void search(string& word, vector<vector<int>>& ans, int bidx)
    {
      if (word.empty())
      {
        return;
      }
      int n = word.length();
      Node* node = root;
      for (int i = 0; i < n; i++)
      {
        int key = word[i];
        if (!node->nexts.count(key))
        {
          return;
        }
        else if (node->nexts.at(key)->idx >= 0)
        {
          ans[node->nexts.at(key)->idx].push_back(bidx);
        }
        node = node->nexts.at(key);
      }
    }
  };
};
