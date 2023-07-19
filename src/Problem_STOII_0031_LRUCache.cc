#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

// seem as 0146
// https://leetcode-cn.com/problems/lru-cache/
// see at Problem_0146_LRUCache.cc
class LRUCache
{
 private:
  class Node
  {
   public:
    Node *pre;
    Node *next;
    int key;
    int val;
    Node() : pre(nullptr), next(nullptr), key(0), val(0) {}
    Node(int k, int v) : pre(nullptr), next(nullptr), key(k), val(v) {}
    Node(Node *p, Node *n, int k, int v) : pre(p), next(n), key(k), val(v) {}
  };

  void addToHead(Node *node)
  {
    node->pre = head;
    node->next = head->next;
    head->next->pre = node;
    head->next = node;
  }

  void removeNode(Node *node)
  {
    node->pre->next = node->next;
    node->next->pre = node->pre;
  }

  void moveToHead(Node *node)
  {
    removeNode(node);
    addToHead(node);
  }

  Node *removeTail()
  {
    Node *node = tail->pre;
    removeNode(node);
    return node;
  }

  Node *head;
  Node *tail;
  int size;
  int capacity;
  unordered_map<int, Node *> map;

 public:
  LRUCache(int capacity)
  {
    // 使用两个伪节点，简化逻辑
    head = new Node();
    tail = new Node();
    head->next = tail;
    tail->pre = head;
    size = 0;
    this->capacity = capacity;
  }

  int get(int key)
  {
    if (!map.count(key))
    {
      return -1;
    }
    Node *node = map.at(key);
    moveToHead(node);
    return node->val;
  }

  void put(int key, int value)
  {
    if (!map.count(key))
    {
      Node *node = new Node(key, value);
      map[key] = node;
      addToHead(node);
      ++size;
      if (size > capacity)
      {
        Node *rmd = removeTail();
        map.erase(rmd->key);
        delete rmd;
        --size;
      }
    }
    else
    {
      Node *node = map[key];
      node->val = value;
      moveToHead(node);
    }
  }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
