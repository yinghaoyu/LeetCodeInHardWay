#include <iostream>
#include <vector>

using namespace std;

class Node
{
 public:
  int val;
  Node *next;

  Node() {}

  Node(int _val)
  {
    val = _val;
    next = NULL;
  }

  Node(int _val, Node *_next)
  {
    val = _val;
    next = _next;
  }
};

// seem as leetcode 0708
// https://leetcode-cn.com/problems/insert-into-a-sorted-circular-linked-list/
// see at Problem_0708_insert.cc
class Solution
{
 public:
  Node *insert(Node *head, int insertVal)
  {
    Node *node = new Node(insertVal);
    if (head == nullptr)
    {
      node->next = node;
      return node;
    }
    if (head->next == head)
    {
      head->next = node;
      node->next = head;
      return head;
    }
    Node *cur = head;
    Node *next = head->next;
    while (next != head)
    {
      if (cur->val <= insertVal && insertVal <= next->val)
      {
        // 夹在中间
        break;
      }
      if (cur->val > next->val)
      {
        if (insertVal > cur->val || insertVal < next->val)
        {
          // 所有数都比 insertVal 大
          // 或
          // 所有数都比 insertVal 小
          break;
        }
      }
      cur = cur->next;
      next = next->next;
    }
    cur->next = node;
    node->next = next;
    return head;
  }
};
