#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;
class LFUCache
{
 private:
  class Node
  {
   public:
    int key;
    int val;
    int times;   // 节点访问的次数
    Node *pre;   // 节点双向链表的上一节点
    Node *next;  // 节点双向链表的下一节点

    Node(int k, int v, int t)
    {
      key = k;
      val = v;
      times = t;
    }
  };

  class Bucket
  {
   public:
    Node *head;      // 桶的头结点
    Node *tail;      // 桶的尾节点
    Bucket *up;      // 桶间双向链表的前一个桶
    Bucket *down;    // 桶间双向链表的后一个桶

    Bucket(Node *node)
    {
      head = node;
      tail = node;
      up = nullptr;
      down = nullptr;
    }

    // 把一个新的节点加入这个桶，新的节点都放在顶端变成新的头部
    void addNodeFromHead(Node *newHead)
    {
      newHead->next = head;
      head->pre = newHead;
      head = newHead;
    }

    // 判断这个桶是不是空的
    bool isEmpty() { return head == nullptr; }

    // 删除node节点并保证node的上下环境重新连接
    void deleteNode(Node *node)
    {
      if (head == tail)
      {
        head = nullptr;
        tail = nullptr;
      }
      else
      {
        if (node == head)
        {
          head = node->next;
          head->pre = nullptr;
        }
        else if (node == tail)
        {
          tail = node->pre;
          tail->next = nullptr;
        }
        else
        {
          node->pre->next = node->next;
          node->next->pre = node->pre;
        }
      }
      node->pre = nullptr;
      node->next = nullptr;
    }
  };

  // removeBucket：刚刚减少了一个节点的桶
  // 这个函数的功能是，判断刚刚减少了一个节点的桶是不是已经空了。
  // 1）如果不空，什么也不做
  //
  // 2)如果空了，removeBucket还是整个缓存结构最左的桶(headList)。
  // 删掉这个桶的同时也要让最左的桶变成removeBucket的下一个。
  //
  // 3)如果空了，removeBucket不是整个缓存结构最左的桶(headList)。
  // 把这个桶删除，并保证上一个的桶和下一个桶之间还是双向链表的连接方式
  //
  // 函数的返回值表示刚刚减少了一个节点的桶是不是已经空了，空了返回true；不空返回false
  bool modifyHeadList(Bucket *removeBucket)
  {
    if (removeBucket->isEmpty())
    {
      if (headBucket == removeBucket)
      {
        headBucket = removeBucket->down;
        if (headBucket != nullptr)
        {
          headBucket->up = nullptr;
        }
      }
      else
      {
        removeBucket->up->down = removeBucket->down;
        if (removeBucket->down != nullptr)
        {
          removeBucket->down->up = removeBucket->up;
        }
      }
      return true;
    }
    return false;
  }

  int capacity;                             // 缓存大小限制
  int size;                                 // 缓存目前有多少个节点
  unordered_map<int, Node *> records;       // 表示 key 由哪个 Node 代表
  unordered_map<Node *, Bucket *> heads;    // 表示 Node 在哪个 Bucket 里
  Bucket *headBucket;                       // 整个结构中最左的桶

 public:
  LFUCache(int capacity)
  {
    this->capacity = capacity;
    size = 0;
    headBucket = nullptr;
  }

  // 函数的功能
  // node这个节点的次数+1了，这个节点原来在oldBucket里。
  // 把node从oldBucket删掉，然后放到次数+1的桶中
  // 整个过程既要保证桶之间仍然是双向链表，也要保证节点之间仍然是双向链表
  void move(Node *node, Bucket *oldBucket)
  {
    // 先从旧桶删除
    oldBucket->deleteNode(node);
    // preList表示次数+1的桶的前一个桶是谁
    // 如果oldBucket删掉node之后还有节点，oldBucket就是次数+1的桶的前一个桶
    // 如果oldBucket删掉node之后空了，oldBucket是需要删除的，所以次数+1的桶的前一个桶，是oldBucket的前一个
    Bucket *preList = modifyHeadList(oldBucket) ? oldBucket->up : oldBucket;
    // nextList表示次数+1的桶的后一个桶是谁
    Bucket *nextList = oldBucket->down;
    if (nextList == nullptr)
    {
      Bucket *newList = new Bucket(node);
      if (preList != nullptr)
      {
        preList->down = newList;
      }
      newList->up = preList;
      if (headBucket == nullptr)
      {
        headBucket = newList;
      }
      heads[node] = newList;
    }
    else
    {
      if (nextList->head->times == node->times)
      {
        nextList->addNodeFromHead(node);
        heads[node] = nextList;
      }
      else
      {
        Bucket *newList = new Bucket(node);
        if (preList != nullptr)
        {
          preList->down = newList;
        }
        newList->up = preList;
        newList->down = nextList;
        nextList->up = newList;
        if (headBucket == nextList)
        {
          headBucket = newList;
        }
        heads[node] = newList;
      }
    }
  }

  int get(int key)
  {
    if (!records.count(key))
    {
      return -1;
    }
    Node *node = records.at(key);
    node->times++;
    Bucket *curBucket = heads.at(node);
    move(node, curBucket);
    return node->val;
  }

  void put(int key, int value)
  {
    if (capacity == 0)
    {
      return;
    }
    if (records.count(key))
    {
      // 缓存中存在这个 key
      Node *node = records.at(key);
      node->val = value;
      node->times++;
      Bucket *curBucket = heads.at(node);
      move(node, curBucket);
    }
    else
    {
      if (size == capacity)
      {
        // 缓存已满，淘汰掉最不常使用的节点
        Node *node = headBucket->tail;
        headBucket->deleteNode(node);
        modifyHeadList(headBucket);
        records.erase(node->key);
        heads.erase(node);
        size--;
      }
      // 添加新节点
      Node *node = new Node(key, value, 1);
      if (headBucket == nullptr)
      {
        // 初始如果没有桶，则新建桶
        headBucket = new Bucket(node);
      }
      else
      {
        if (headBucket->head->times == node->times)
        {
          // 如果和最近访问的桶的次数相同，则添加到桶里
          headBucket->addNodeFromHead(node);
        }
        else
        {
          // 否则新建桶，头插法插入
          Bucket *newList = new Bucket(node);
          newList->down = headBucket;
          headBucket->up = newList;
          headBucket = newList;
        }
      }
      records[key] = node;
      heads[node] = headBucket;
      size++;
    }
  }
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
