#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Trie
{
 public:
  Trie() { root = new Node(); }

  void insert(string word)
  {
    if (word.length() == 0)
    {
      return;
    }
    Node *cur = root;
    cur->pass++;
    for (char &c : word)
    {
      int index = c;
      if (!cur->nexts.count(index))
      {
        cur->nexts.emplace(index, new Node());
      }
      cur = cur->nexts.at(index);
      cur->pass++;
    }
    cur->end++;
  }

  bool search(string word)
  {
    if (word.length() == 0)
    {
      return true;
    }
    Node *cur = root;
    for (char &c : word)
    {
      int index = c;
      if (!cur->nexts.count(index))
      {
        return false;
      }
      cur = cur->nexts.at(index);
    }
    return cur->end > 0;
  }

  bool startsWith(string prefix)
  {
    if (prefix.length() == 0)
    {
      return true;
    }
    Node *cur = root;
    for (char &c : prefix)
    {
      int index = c;
      if (!cur->nexts.count(index))
      {
        return false;
      }
      cur = cur->nexts.at(index);
    }
    return cur->pass > 0;
  }

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
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */
