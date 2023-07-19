#include <iostream>
#include <vector>

using namespace std;

class Node
{
 public:
  int val;
  Node *prev;
  Node *next;
  Node *child;
};

// same as leetcode 0430
// https://leetcode-cn.com/problems/flatten-a-multilevel-doubly-linked-list/
// see at Problem_0430_flatten.cc
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
        Node *child_last = dfs(cur->child);

        cur->next = cur->child;
        cur->child->prev = cur;

        if (next)
        {
          child_last->next = next;
          next->prev = child_last;
        }

        cur->child = nullptr;
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
