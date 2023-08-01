#include <iostream>
#include <unordered_map>
#include <vector>

#include "UnitTest.h"

using namespace std;

// seem as leetcode 0208
// https://leetcode-cn.com/problems/implement-trie-prefix-tree/
// see at Problem_0208_Trie.cc
class Trie
{
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
  /** Initialize your data structure here. */
  Trie() { root = new Node(); }

  /** Inserts a word into the trie. */
  void insert(string word)
  {
    if (search(word))
    {
      return;
    }
    Node *cur = root;
    cur->pass++;
    for (char c : word)
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

  /** Returns if the word is in the trie. */
  bool search(string word)
  {
    Node *cur = root;
    for (char c : word)
    {
      if (!cur->nexts.count(c))
      {
        return false;
      }
      cur = cur->nexts[c];
    }
    return cur->end > 0;
  }

  /** Returns if there is any word in the trie that starts with the given prefix. */
  bool startsWith(string prefix)
  {
    Node *cur = root;
    for (char c : prefix)
    {
      if (!cur->nexts.count(c))
      {
        return false;
      }
      cur = cur->nexts[c];
    }
    return cur->pass > 0;
  }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */
