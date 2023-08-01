#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

// seem as leetcode 0648
// https://leetcode-cn.com/problems/replace-words/
// see at Problem_0648_replaceWords.cc
class Solution
{
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

    string getRoot(string word)
    {
      Node *cur = root;
      string x;
      for (char c : word)
      {
        if (!cur->nexts.count(c))
        {
          return word;
        }
        cur = cur->nexts[c];
        x.push_back(c);
        if (cur->end > 0)
        {
          return x;
        }
      }
      return x;
    }
  };

 public:
  vector<string> takeWords(string &sentence)
  {
    vector<string> words;
    int start = 0;
    int end = 0;
    for (; end < sentence.length(); end++)
    {
      if (sentence[end] == ' ')
      {
        words.push_back(sentence.substr(start, end - start));
        start = end + 1;
      }
    }
    if (start < sentence.length())
    {
      words.push_back(sentence.substr(start));
    }
    return words;
  }

  string replaceWords(vector<string> &dictionary, string sentence)
  {
    Trie t;
    vector<string> words = takeWords(sentence);
    for (auto &word : dictionary)
    {
      t.insert(word);
    }
    string ans;
    for (auto &word : words)
    {
      ans += t.getRoot(word) + " ";
    }
    ans.pop_back();
    return ans;
  }
};
