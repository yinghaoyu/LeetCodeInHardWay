#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
  struct Trie
  {
    Trie() : ref(-1) {}

    unordered_map<string, Trie *> children;
    int ref;
  };

 public:
  vector<string> removeSubfolders(vector<string> &folder)
  {
    auto split = [](const string &s) -> vector<string> {
      vector<string> ret;
      string cur;
      for (char ch : s)
      {
        if (ch == '/')
        {
          ret.push_back(move(cur));
          cur.clear();
        }
        else
        {
          cur.push_back(ch);
        }
      }
      ret.push_back(move(cur));
      return ret;
    };

    Trie *root = new Trie();
    for (int i = 0; i < folder.size(); ++i)
    {
      vector<string> path = split(folder[i]);
      Trie *cur = root;
      for (const string &name : path)
      {
        if (!cur->children.count(name))
        {
          cur->children[name] = new Trie();
        }
        cur = cur->children[name];
      }
      cur->ref = i;
    }

    vector<string> ans;

    function<void(Trie *)> dfs = [&](Trie *cur) {
      if (cur->ref != -1)
      {
        ans.push_back(folder[cur->ref]);
        return;
      }
      for (auto &&[_, child] : cur->children)
      {
        dfs(child);
      }
    };

    dfs(root);
    return ans;
  }
};

bool isVectorEqual(vector<string> a, vector<string> b)
{
  std::sort(a.begin(), a.end());
  std::sort(b.begin(), b.end());
  return a == b;
}

void testRemoveSubfolders()
{
  Solution s;
  vector<string> f1 = {"/a", "/a/b", "/c/d", "/c/d/e", "/c/f"};
  vector<string> o1 = {"/a", "/c/d", "/c/f"};
  vector<string> f2 = {"/a", "/a/b/c", "/a/b/d"};
  vector<string> o2 = {"/a"};
  vector<string> f3 = {"/a/b/c", "/a/b/ca", "/a/b/d"};
  vector<string> o3 = {"/a/b/c", "/a/b/ca", "/a/b/d"};
  EXPECT_TRUE(isVectorEqual(o1, s.removeSubfolders(f1)));
  EXPECT_TRUE(isVectorEqual(o2, s.removeSubfolders(f2)));
  EXPECT_TRUE(isVectorEqual(o3, s.removeSubfolders(f3)));
  EXPECT_SUMMARY;
}

int main()
{
  testRemoveSubfolders();
  return 0;
}
