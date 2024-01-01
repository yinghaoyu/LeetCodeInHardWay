#include <map>
#include <set>
#include <string>

#include "UnitTest.h"

using namespace std;

class AllOne
{
 public:
  AllOne()
  {
    // dummy node for coding easy
    head = new Bucket("", 0);
    tail = new Bucket("", INT32_MAX);
    head->next = tail;
    tail->last = head;
  }

  void inc(string key)
  {
    if (!map_.count(key))
    {
      if (head->next->cnt == 1)
      {
        map_[key] = head->next;
        head->next->set_.emplace(key);
      }
      else
      {
        Bucket* newBucket = new Bucket(key, 1);
        map_[key] = newBucket;
        insert(head, newBucket);
      }
    }
    else
    {
      Bucket* bucket = map_[key];
      if (bucket->next->cnt == bucket->cnt + 1)
      {
        map_[key] = bucket->next;
        bucket->next->set_.emplace(key);
      }
      else
      {
        Bucket* newBucket = new Bucket(key, bucket->cnt + 1);
        map_[key] = newBucket;
        insert(bucket, newBucket);
      }
      bucket->set_.erase(key);
      if (bucket->set_.empty())
      {
        remove(bucket);
      }
    }
  }

  void dec(string key)
  {
    Bucket* bucket = map_[key];
    if (bucket->cnt == 1)
    {
      map_.erase(key);
    }
    else
    {
      if (bucket->last->cnt == bucket->cnt - 1)
      {
        map_[key] = bucket->last;
        bucket->last->set_.emplace(key);
      }
      else
      {
        Bucket* newBucket = new Bucket(key, bucket->cnt - 1);
        map_[key] = newBucket;
        insert(bucket->last, newBucket);
      }
    }
    bucket->set_.erase(key);
    if (bucket->set_.empty())
    {
      remove(bucket);
    }
  }

  string getMaxKey() { return *tail->last->set_.begin(); }

  string getMinKey() { return *head->next->set_.begin(); }

 private:
  class Bucket
  {
   public:
    set<string> set_;
    int cnt;
    Bucket* last;
    Bucket* next;
    Bucket(const string& s, int c)
    {
      set_.emplace(s);
      cnt = c;
    }
  };

  void insert(Bucket* cur, Bucket* pos)
  {
    cur->next->last = pos;
    pos->next = cur->next;
    cur->next = pos;
    pos->last = cur;
  }

  void remove(Bucket* cur)
  {
    cur->last->next = cur->next;
    cur->next->last = cur->last;
  }

  Bucket* head;
  Bucket* tail;
  map<string, Bucket*> map_;
};

/**
 * Your AllOne object will be instantiated and called as such:
 * AllOne* obj = new AllOne();
 * obj->inc(key);
 * obj->dec(key);
 * string param_3 = obj->getMaxKey();
 * string param_4 = obj->getMinKey();
 */

void test()
{
  AllOne allOne;
  allOne.inc("hello");
  allOne.inc("hello");
  EXPECT_TRUE("hello" == allOne.getMaxKey());  // 返回 "hello"
  EXPECT_TRUE("hello" == allOne.getMinKey());  // 返回 "hello"
  allOne.inc("leet");
  EXPECT_TRUE("hello" == allOne.getMaxKey());  // 返回 "hello"
  EXPECT_TRUE("leet" == allOne.getMinKey());   // 返回 "leet"
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
