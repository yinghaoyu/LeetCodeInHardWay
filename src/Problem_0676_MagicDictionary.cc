#include <functional>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class MagicDictionary
{
 private:
  class Node
  {
   public:
    int pass;
    int end;
    unordered_map<int, Node *> nexts;
    Node()
    {
      pass = 0;
      end = 0;
    }
  };

  Node *root;

 public:
  MagicDictionary() { root = new Node(); }

  void buildDict(vector<string> dictionary)
  {
    for (auto &word : dictionary)
    {
      Node *cur = root;
      for (auto &c : word)
      {
        if (!cur->nexts.count(c))
        {
          cur->nexts[c] = new Node();
        }
        cur = cur->nexts[c];
        cur->pass++;
      }
      cur->end++;
    }
  }

  bool dfs(string &searchWord, Node *cur, int index, bool isModified)
  {
    if (index == searchWord.length())
    {
      return cur->end > 0 && isModified;
    }
    if (cur->nexts.count(searchWord[index]))
    {
      if (dfs(searchWord, cur->nexts[searchWord[index]], index + 1, isModified))
      {
        return true;
      }
    }
    if (!isModified)
    {
      for (auto &[c, node] : cur->nexts)
      {
        if (c != searchWord[index] && dfs(searchWord, node, index + 1, true))
        {
          // c != searchWord[index] 只有字符不相同才算一次更改
          return true;
        }
      }
    }
    return false;
  }

  bool search(string searchWord) { return dfs(searchWord, root, 0, false); }
};

/**
 * Your MagicDictionary object will be instantiated and called as such:
 * MagicDictionary* obj = new MagicDictionary();
 * obj->buildDict(dictionary);
 * bool param_2 = obj->search(searchWord);
 */
