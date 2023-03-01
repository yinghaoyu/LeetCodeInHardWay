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
  vector<int> findOrder(int numCourses, vector<vector<int>> &prerequisites)
  {
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
    vector<int> ans;
    for (int i = 0; i < numCourses; i++)
    {
      if (!map.count(i))
      {
        ans.push_back(i);
      }
      else if (map.at(i)->in == 0)
      {
        que.push(map.at(i));
      }
    }
    int count = 0;
    while (!que.empty())
    {
      Node *cur = que.front();
      que.pop();
      count++;
      ans.push_back(cur->name);
      for (Node *next : cur->nexts)
      {
        if (--next->in == 0)
        {
          que.push(next);
        }
      }
    }
    return count == n ? ans : vector<int>{};
  }
};
