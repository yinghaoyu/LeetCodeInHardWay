#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
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

 public:
  // 根据目标单词构造字典树
  void fillWord(Node *node, string &word)
  {
    node->pass++;
    for (auto &c : word)
    {
      int index = c;
      if (!node->nexts.count(index))
      {
        node->nexts.emplace(index, new Node());
      }
      node = node->nexts.at(index);
      node->pass++;
    }
    node->end++;
  }

  int process(vector<vector<char>> &board, int i, int j, string &path, Node *cur, vector<string> &ans)
  {
    char c = board[i][j];
    if (c == 0)
    {
      // 这个位置之前走过
      return 0;
    }
    int index = c;
    if (!cur->nexts.count(index) || cur->nexts.at(index)->pass == 0)
    {
      // 没有路，或者这条路上最终的字符串之前加入过结果里面
      return 0;
    }
    cur = cur->nexts.at(index);
    // 当前字符加入路径
    path.push_back(c);
    // 从i和j位置出发，后续一共搞定了多少答案
    int fix = 0;
    if (cur->end > 0)
    {
      // 当我来到i j位置，如果决定不往后走了。是不是已经搞定了某个字符串了
      ans.push_back(path);
      cur->end--;
      fix++;
    }
    // 往上、下、左、右，四个方向尝试
    board[i][j] = 0;
    if (i > 0)
    {
      fix += process(board, i - 1, j, path, cur, ans);
    }
    if (i < board.size() - 1)
    {
      fix += process(board, i + 1, j, path, cur, ans);
    }
    if (j > 0)
    {
      fix += process(board, i, j - 1, path, cur, ans);
    }
    if (j < board[0].size() - 1)
    {
      process(board, i, j + 1, path, cur, ans);
    }
    // 回溯
    board[i][j] = c;
    path.pop_back();
    cur->pass -= fix;
    return fix;
  }

  vector<string> findWords(vector<vector<char>> &board, vector<string> &words)
  {
    Node *root = new Node();
    unordered_set<string> set;
    for (auto &word : words)
    {
      if (!set.count(word))
      {
        fillWord(root, word);
        set.emplace(word);
      }
    }

    vector<string> ans;
    string path;
    for (int i = 0; i < board.size(); i++)
    {
      for (int j = 0; j < board[0].size(); j++)
      {
        // 枚举在board中的所有位置
        // 每一个位置出发的情况下，答案都收集
        process(board, i, j, path, root, ans);
      }
    }
    return ans;
  }
};

bool isVectorEqual(vector<string> a, vector<string> b)
{
  std::sort(a.begin(), a.end());
  std::sort(b.begin(), b.end());
  return a == b;
}

void testFindWords()
{
  Solution s;
  vector<vector<char>> b1 = {{'o', 'a', 'a', 'n'}, {'e', 't', 'a', 'e'}, {'i', 'h', 'k', 'r'}, {'i', 'f', 'l', 'v'}};
  vector<vector<char>> b2 = {{'a', 'b'}, {'c', 'd'}};
  vector<string> w1 = {"oath", "pea", "eat", "rain"};
  vector<string> w2 = {"abcb"};
  vector<string> o1 = {"eat", "oath"};
  vector<string> o2;
  EXPECT_TRUE(isVectorEqual(o1, s.findWords(b1, w1)));
  EXPECT_TRUE(isVectorEqual(o2, s.findWords(b2, w2)));
  EXPECT_SUMMARY;
}

int main()
{
  testFindWords();
  return 0;
}
