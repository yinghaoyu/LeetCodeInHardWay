#include <iostream>
#include <list>
#include <queue>
#include <unordered_map>

#include "UnitTest.h"

using namespace std;

class FreqStack
{
 public:
  FreqStack() {}

  void push(int val)
  {
    freq[val]++;
    stack.push_back(val);
    que.push(Info(seq++, freq[val], std::prev(stack.end())));
  }

  int pop()
  {
    if (stack.empty())
    {
      return -1;
    }
    Info p = que.top();
    que.pop();
    int ans = *p.ptr;
    freq[ans]--;
    stack.erase(p.ptr);
    return ans;
  }

 private:
  class Info
  {
   public:
    Info() { count = 0; }

    Info(int s, int c, list<int>::iterator p)
    {
      seq = s;
      count = c;
      ptr = p;
    }

    bool operator<(const Info &other) const { return this->count < other.count || this->count == other.count && this->seq < other.seq; }

    int seq;
    int count;
    list<int>::iterator ptr;
  };
  unordered_map<int, int> freq;
  priority_queue<Info> que;
  list<int> stack;
  int seq = 0;
};

/**
 * Your FreqStack object will be instantiated and called as such:
 * FreqStack* obj = new FreqStack();
 * obj->push(val);
 * int param_2 = obj->pop();
 */

void testFreqStack()
{
  FreqStack s;
  s.push(5);
  s.push(7);
  s.push(5);
  s.push(7);
  s.push(4);
  s.push(5);
  EXPECT_EQ_INT(5, s.pop());
  EXPECT_EQ_INT(7, s.pop());
  EXPECT_EQ_INT(5, s.pop());
  EXPECT_EQ_INT(4, s.pop());
  EXPECT_SUMMARY;
}

int main()
{
  testFreqStack();
  return 0;
}
