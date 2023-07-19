#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Node
{
 public:
  int val;
  Node *prev;
  Node *next;
  Node *child;
};

class Solution
{
 public:
  Node *dfs(Node *node)
  {
    Node *cur = node;
    Node *last = nullptr;
    while (cur)
    {
      Node *next = cur->next;
      if (cur->child)
      {
        // 优先处理子节点
        Node *child_last = dfs(cur->child);
        // cur 与 child 相连
        cur->next = cur->child;
        cur->child->prev = cur;
        if (next)
        {
          // 如果有 next，将 child_last 与 next 相连
          child_last->next = next;
          next->prev = child_last;
        }
        // 清空 child 指针
        cur->child = nullptr;
        // 记录最后一个节点
        last = child_last;
      }
      else
      {
        last = cur;
      }
      cur = next;
    }
    return last;
  }

  Node *flatten(Node *head)
  {
    dfs(head);
    return head;
  }
};
