#include <cstdio>
#include <unordered_map>
#include <vector>

using namespace std;

class LRUCache
{
 public:
  LRUCache(int capacity) { cache = new MyCache<int, int>(capacity); }

  int get(int key) { return cache->get(key); }

  void put(int key, int value) { cache->set(key, value); }

  template <typename K, typename V>
  struct Node
  {
    K key;
    V value;
    Node* pre;
    Node* next;

    Node(K key, V value)
    {
      this->key = key;
      this->value = value;
    }
  };

  template <typename K, typename V>
  class DoubleLikedList
  {
   private:
    Node<K, V>* head;
    Node<K, V>* tail;

   public:
    DoubleLikedList()
    {
      head = nullptr;
      tail = nullptr;
    }

    void addNode(Node<K, V>* node)
    {
      if (node == nullptr)
      {
        return;
      }
      if (head == nullptr)
      {
        head = node;
        tail = node;
      }
      else
      {
        tail->next = node;
        node->pre = tail;
        tail = node;
      }
    }

    void moveNodeToTail(Node<K, V>* node)
    {
      if (node == tail)
      {
        return;
      }
      if (node == head)
      {
        head = head->next;
        head->pre = nullptr;
      }
      else
      {
        node->pre->next = node->next;
        node->next->pre = node->pre;
      }
      node->pre = tail;
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
        head = nullptr;
        tail = nullptr;
      }
      else
      {
        head = head->next;
        ans->next = nullptr;
        head->pre = nullptr;
      }
      return ans;
    }
  };

  template <typename K, typename V>
  class MyCache
  {
   public:
    MyCache(int capacity) { this->capacity = capacity; }

    void set(K key, V value)
    {
      if (map.count(key))
      {
        map[key]->value = value;
        list.moveNodeToTail(map[key]);
      }
      else
      {
        if (capacity == map.size())
        {
          Node<K, V>* rm = list.removeHead();
          map.erase(rm->key);
        }
        Node<K, V>* node = new Node<K, V>(key, value);
        map[key] = node;
        list.addNode(node);
      }
    }

    V get(K key)
    {
      if (map.count(key))
      {
        list.moveNodeToTail(map[key]);
        return map[key]->value;
      }
      return V(-1);
    }

   private:
    unordered_map<K, Node<K, V>*> map;
    // 双向非环形链表
    DoubleLikedList<K, V> list;
    int capacity;
  };

 private:
  MyCache<int, int>* cache;
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
