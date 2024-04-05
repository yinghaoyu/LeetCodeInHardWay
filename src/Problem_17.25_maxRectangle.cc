#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution
{
 public:
  // TODO: complete it.
  vector<string> maxRectangle(vector<string>& words) {}

  class Node
  {
   public:
    int pass;
    int end;
    unordered_map<int, Node*> nexts;

    Node()
    {
      pass = 0;
      end = 0;
    }
  };

  class Trie
  {
    Node* root;

   public:
    Trie() { root = new Node(); }

    void insert(string& word)
    {
      if (word.empty())
      {
        return;
      }
      Node* node = root;
      node->pass++;
      for (int i = 0; i < word.length(); i++)
      {
        char idx = word[i];
        if (!node->nexts.count(idx))
        {
          node->nexts.emplace(idx, new Node);
        }
        node = node->nexts.at(idx);
        node->pass++;
      }
      node->end++;
    }
  };
};
