#include <stack>

using namespace std;

class MyQueue
{
 private:
  stack<int> stackA;
  stack<int> stackB;

 public:
  MyQueue() {}

  void push(int x) { stackB.push(x); }

  int pop()
  {
    if (stackA.empty())
    {
      while (!stackB.empty())
      {
        int cur = stackB.top();
        stackB.pop();
        stackA.push(cur);
      }
    }
    int cur = stackA.top();
    stackA.pop();
    return cur;
  }

  int peek()
  {
    if (stackA.empty())
    {
      while (!stackB.empty())
      {
        int cur = stackB.top();
        stackB.pop();
        stackA.push(cur);
      }
    }
    return stackA.top();
  }

  bool empty() { return stackA.empty() && stackB.empty(); }
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */
