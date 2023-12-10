#include <unordered_map>

using namespace std;

class Node
{
 public:
  int val;
  Node* next;
  Node* random;

  Node(int _val)
  {
    val = _val;
    next = NULL;
    random = NULL;
  }
};

class Solution
{
 public:
  // 空间复杂度O(N)
  Node* copyRandomList1(Node* head)
  {
    unordered_map<Node*, Node*> map;
    Node* p = head;
    while (p != nullptr)
    {
      Node* node = new Node(p->val);
      node->next = p->next;
      node->random = p->random;
      map.emplace(p, node);
      p = p->next;
    }
    p = map[head];
    while (p != nullptr)
    {
      p->next = map[p->next];
      p->random = map[p->random];
      p = p->next;
    }
    return map[head];
  }

  Node* copyRandomList2(Node* head)
  {
    if (head == nullptr)
    {
      return nullptr;
    }
    Node* cur = head;
    Node* next = nullptr;
    // 1 -> 2 -> 3 -> null
    // 1 -> 1' -> 2 -> 2' -> 3 -> 3'
    while (cur != nullptr)
    {
      next = cur->next;
      cur->next = new Node(cur->val);
      cur->next->next = next;
      cur = next;
    }
    cur = head;
    Node* copy = nullptr;
    // 1 1' 2 2' 3 3'
    // 依次设置 1' 2' 3' random指针
    while (cur != nullptr)
    {
      next = cur->next->next;
      copy = cur->next;
      // cur->random->next这一步相当于查hashmap，跟方法一异曲同工
      copy->random = cur->random != nullptr ? cur->random->next : nullptr;
      cur = next;
    }
    Node* res = head->next;
    cur = head;
    // 老 新 混在一起，next方向上，random正确
    // next方向上，把新老链表分离
    while (cur != nullptr)
    {
      next = cur->next->next;
      copy = cur->next;
      cur->next = next;
      copy->next = next != nullptr ? next->next : nullptr;
      cur = next;
    }
    return res;
  }
};
