#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  class Node
  {
   public:
    int name;  // 课程编号
    int in;    // 课程入度
    vector<Node *> nexts;
    Node(int n)
    {
      name = n;
      in = 0;
    }
  };

  // 拓扑排序
  bool canFinish(int numCourses, vector<vector<int>> &prerequisites)
  {
    if (prerequisites.size() == 0)
    {
      return true;
    }
    unordered_map<int, Node *> map;
    for (auto &arr : prerequisites)
    {
      int to = arr[0];
      int from = arr[1];
      if (!map.count(to))
      {
        map.emplace(to, new Node(to));
      }
      if (!map.count(from))
      {
        map.emplace(from, new Node(from));
      }
      Node *t = map.at(to);
      Node *f = map.at(from);
      f->nexts.push_back(t);
      t->in++;
    }
    int n = map.size();
    queue<Node *> que;
    for (auto [_, node] : map)
    {
      if (node->in == 0)
      {
        que.push(node);
      }
    }
    int count = 0;
    while (!que.empty())
    {
      Node *cur = que.front();
      que.pop();
      count++;
      for (Node *next : cur->nexts)
      {
        if (--next->in == 0)
        {
          que.push(next);
        }
      }
    }
    return count == n;
  }
};

void testCanFinish()
{
  Solution s;
  vector<vector<int>> p1 = {{1, 0}};
  vector<vector<int>> p2 = {{1, 0}, {0, 1}};
  EXPECT_TRUE(s.canFinish(2, p1));
  EXPECT_FALSE(s.canFinish(2, p2));
  EXPECT_SUMMARY;
}

int main()
{
  testCanFinish();
  return 0;
}
