#include <assert.h>
#include <iostream>

#include "UnitTest.h"

using namespace std;

class MyLinkedList
{
 private:
  class Node
  {
   public:
    int val;
    Node *pre;
    Node *next;
    Node(int val)
    {
      this->val = val;
      this->pre = nullptr;
      this->next = nullptr;
    }
  };

  Node *head;
  Node *tail;
  size_t size;

 public:
  MyLinkedList()
  {
    head = new Node(0);
    tail = new Node(0);
    head->next = tail;
    tail->pre = head;
    size = 0;
  }

  ~MyLinkedList() {}

  int get(int index)
  {
    if (index < 0 || index >= size)
    {
      return -1;
    }
    Node *anchor;
    if (index + 1 < size - index)  // 多一个头结点 + 1
    {
      anchor = head;
      for (int i = 0; i <= index; i++)  // 因为多一个头结点，所以取 <=
      {
        anchor = anchor->next;
      }
    }
    else
    {
      anchor = tail;
      for (int i = 0; i < size - index; i++)
      {
        anchor = anchor->pre;
      }
    }
    return anchor->val;
  }

  void addAtHead(int val) { addAtIndex(0, val); }

  void addAtTail(int val) { addAtIndex(size, val); }

  void addAtIndex(int index, int val)
  {
    if (index < 0 || index > size)
    {
      return;
    }
    Node *pre, *anchor;
    if (index < size - index)
    {
      pre = head;
      for (int i = 0; i < index; i++)
      {
        pre = pre->next;
      }
      anchor = pre->next;
    }
    else
    {
      anchor = tail;
      for (int i = 0; i < size - index; i++)
      {
        anchor = anchor->pre;
      }
      pre = anchor->pre;
    }
    size++;
    Node *cur = new Node(val);
    cur->pre = pre;
    cur->next = anchor;
    pre->next = cur;
    anchor->pre = cur;
  }

  void deleteAtIndex(int index)
  {
    if (index < 0 || index >= size)
    {
      return;
    }
    Node *pre, *anchor;
    if (index < size - index)
    {
      pre = head;
      for (int i = 0; i < index; i++)
      {
        pre = pre->next;
      }
      anchor = pre->next->next;
    }
    else
    {
      anchor = tail;
      for (int i = 0; i < size - index - 1; i++)
      {
        anchor = anchor->pre;
      }
      pre = anchor->pre->pre;
    }
    size--;
    Node *p = pre->next;
    pre->next = anchor;
    anchor->pre = pre;
    delete p;
  }
};

/**
 * Your MyLinkedList object will be instantiated and called as such:
 * MyLinkedList* obj = new MyLinkedList();
 * int param_1 = obj->get(index);
 * obj->addAtHead(val);
 * obj->addAtTail(val);
 * obj->addAtIndex(index,val);
 * obj->deleteAtIndex(index);
 */

void testMyLinkedList()
{
  MyLinkedList list;
  list.addAtHead(1);
  list.addAtTail(3);
  list.addAtIndex(1, 2);
  EXPECT_EQ_INT(2, list.get(1));
  list.deleteAtIndex(1);
  EXPECT_EQ_INT(3, list.get(1));
  list.deleteAtIndex(2);
  EXPECT_EQ_INT(3, list.get(1));
  list.addAtIndex(1, 4);
  EXPECT_EQ_INT(4, list.get(1));
  list.deleteAtIndex(0);
  EXPECT_EQ_INT(3, list.get(1));
  list.deleteAtIndex(0);
  EXPECT_EQ_INT(3, list.get(0));
  list.deleteAtIndex(0);
  EXPECT_SUMMARY;
}

int main()
{
  testMyLinkedList();
  return 0;
}
