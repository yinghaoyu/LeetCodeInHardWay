#include <assert.h>
#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

// 问题分析：
// 为了使编程简单，多出1个元素
// 当begin_ == end_ 说明为空
// 当begin_ == (end_ + 1) % capacity_ 说明队列满

class MyCircularDeque
{
 public:
  MyCircularDeque(int k)
  {
    assert(k >= 0);
    capacity_ = k + 1;
    begin_ = 0;
    end_ = 0;
    buf_ = vector<int>(capacity_);
  }

  bool insertFront(int value)
  {
    if (isFull())
    {
      return false;
    }
    begin_ = (begin_ - 1 + capacity_) % capacity_;
    buf_[begin_] = value;
    return true;
  }

  bool insertLast(int value)
  {
    if (isFull())
    {
      return false;
    }
    buf_[end_] = value;
    end_ = (end_ + 1) % capacity_;
    return true;
  }

  bool deleteFront()
  {
    if (isEmpty())
    {
      return false;
    }
    begin_ = (begin_ + 1) % capacity_;
    return true;
  }

  bool deleteLast()
  {
    if (isEmpty())
    {
      return false;
    }
    end_ = (end_ - 1 + capacity_) % capacity_;
    return true;
  }

  int getFront()
  {
    if (isEmpty())
    {
      return -1;
    }
    return buf_[begin_];
  }

  int getRear()
  {
    if (isEmpty())
    {
      return -1;
    }
    return buf_[(end_ - 1 + capacity_) % capacity_];
  }

  bool isEmpty() { return begin_ == end_; }

  bool isFull() { return begin_ == (end_ + 1) % capacity_; }

 private:
  size_t capacity_;
  size_t begin_;
  size_t end_;
  vector<int> buf_;
};

static void testMyCircularDeque()
{
  MyCircularDeque obj(3);
  EXPECT_TRUE(obj.insertFront(1));
  EXPECT_TRUE(obj.insertLast(3));
  EXPECT_TRUE(obj.insertFront(2));
  EXPECT_TRUE(obj.isFull());
  EXPECT_FALSE(obj.isEmpty());

  EXPECT_FALSE(obj.insertFront(2));
  EXPECT_FALSE(obj.insertLast(3));

  EXPECT_TRUE(obj.deleteFront());
  EXPECT_TRUE(obj.deleteLast());
  EXPECT_EQ_INT(1, obj.getFront());
  EXPECT_EQ_INT(1, obj.getRear());
  EXPECT_FALSE(obj.isFull());
  EXPECT_FALSE(obj.isEmpty());
  EXPECT_SUMMARY;
}

int main()
{
  testMyCircularDeque();
  return 0;
}
