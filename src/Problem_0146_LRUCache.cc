#include <iostream>
#include <unordered_map>

#include "UnitTest.h"

using namespace std;
class LRUCache
{
 public:
  LRUCache(int capacity) { cache = new MyCache<int, int>(capacity); }

  int get(int key) { return cache->get(key); }

  void put(int key, int value) { cache->set(key, value); }

 private:
  template <typename K, typename V>
  class Node
  {
   public:
    K key;
    V value;
    Node *last;
    Node *next;

    Node(K k, V v)
    {
      key = k;
      value = v;
    }
  };

  template <typename K, typename V>
  class DoubleLinkedList
  {
   private:
    Node<K, V> *head;
    Node<K, V> *tail;

   public:
    DoubleLinkedList()
    {
      head = nullptr;
      tail = nullptr;
    }

    void addNode(Node<K, V> *newNode)
    {
      if (newNode == nullptr)
      {
        return;
      }
      if (head == nullptr)
      {
        head = newNode;
        tail = newNode;
      }
      else
      {
        tail->next = newNode;
        newNode->last = tail;
        tail = newNode;
      }
    }

    void moveNodeToTail(Node<K, V> *node)
    {
      if (tail == node)
      {
        return;
      }
      if (head == node)
      {
        head = node->next;
        head->last = nullptr;
      }
      else
      {
        node->last->next = node->next;
        node->next->last = node->last;
      }
      node->last = tail;
      node->next = nullptr;
      tail->next = node;
      tail = node;
    }

    Node<K, V>* removeHead()
    {
      if (head == nullptr)
      {
        return nullptr;
      }
      Node<K, V>* ans = head;
      if (head == tail)
      {
        // 链表只有一个节点
        head = nullptr;
        tail = nullptr;
      }
      else
      {
        head = ans->next;
        ans->next = nullptr;
        head->last = nullptr;
      }
      return ans;
    }
  };

  template <typename K, typename V>
  class MyCache
  {
   private:
    unordered_map<K, Node<K, V>*> keyNodeMap;
    DoubleLinkedList<K, V> nodeList;
    int capacity;

   public:
    MyCache(int cap) { capacity = cap; }

    V get(K key)
    {
      if (keyNodeMap.count(key))
      {
        Node<K, V> *ans = keyNodeMap.at(key);
        nodeList.moveNodeToTail(ans);
        return ans->value;
      }
      return V(-1);
    }

    void set(K key, V value)
    {
      if (keyNodeMap.count(key))
      {
        Node<K, V>* node = keyNodeMap.at(key);
        node->value = value;
        nodeList.moveNodeToTail(node);
      }
      else
      {
        if (keyNodeMap.size() == capacity)
        {
          Victim();
        }
        Node<K, V>* newNode = new Node<K, V>(key, value);
        keyNodeMap.emplace(key, newNode);
        nodeList.addNode(newNode);
      }
    }

    void Victim()
    {
      Node<K, V>* removeNode = nodeList.removeHead();
      keyNodeMap.erase(removeNode->key);
    }
  };

 private:
  MyCache<int, int> *cache;
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
