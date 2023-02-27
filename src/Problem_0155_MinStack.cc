#include <iostream>
#include <vector>

using namespace std;

// 空间复杂度O(N)
class MinStack1
{
 public:
  MinStack1() {}

  void push(int val)
  {
    if (min.empty())
    {
      min.push_back(val);
    }
    else
    {
      min.push_back(std::min(val, min.back()));
    }
    data.push_back(val);
  }

  void pop()
  {
    data.pop_back();
    min.pop_back();
  }

  int top() { return data.back(); }

  int getMin() { return min.back(); }

  vector<int> data;
  vector<int> min;
};

// 链表实现
class MinStack2
{
 private:
  class Node
  {
   public:
    int val;
    int min;
    Node *next;

    Node(int val, int min)
    {
      this->val = val;
      this->min = min;
      this->next = nullptr;
    }

    Node(int val, int min, Node *next)
    {
      this->val = val;
      this->min = min;
      this->next = next;
    }
  };
  Node *head;

 public:
  void push(int x)
  {
    if (head == nullptr)
      head = new Node(x, x);
    else
      head = new Node(x, std::min(x, head->min), head);
  }

  void pop() { head = head->next; }

  int top() { return head->val; }

  int getMin() { return head->min; }
};

// 空间复杂度O(1)
class MinStack3
{
 public:
  MinStack3() {}

  void push(int val)
  {
    if (diff.empty())
    {
      // 压入第一个元素
      min = val;
      diff.push_back(0LL);
    }
    else
    {
      // 进栈元素与当前栈内最小值的差值
      diff.push_back((long long) val - min);
      min = std::min(min, (long long) val);
    }
  }

  void pop()
  {
    long long pop = diff.back();
    diff.pop_back();
    if (pop < 0)
    {
      // 当弹出元素小于0时，说明弹出元素是当前栈中的最小值，要更新最小值
      long long lastMin = min;
      min = lastMin - pop;
    }
    // 若大于等于0，不会对min有影响
  }

  int top()
  {
    long long peek = diff.back();
    // 若当前栈顶小于等于0，说明最小值就是栈顶元素
    return peek <= 0 ? min : min + peek;
  }

  int getMin() { return min; }

  // 记录每个进栈元素，与栈中最小元素的差值
  vector<long long> diff;
  // 栈内元素的最小值
  long long min;
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */
