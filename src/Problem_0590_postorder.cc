#include <algorithm>
#include <stack>
#include <vector>

using namespace std;

class Node
{
 public:
  int val;
  vector<Node*> children;

  Node() {}

  Node(int _val) { val = _val; }

  Node(int _val, vector<Node*> _children)
  {
    val = _val;
    children = _children;
  }
};

class Solution
{
 private:
  void f(Node* cur, vector<int>& ans)
  {
    if (cur == nullptr)
    {
      return;
    }
    for (auto& c : cur->children)
    {
      f(c, ans);
    }
    ans.push_back(cur->val);
  }

 public:
  // 递归
  vector<int> postorder(Node* root)
  {
    vector<int> ans;
    f(root, ans);
    return ans;
  }

  // 非递归
  vector<int> iterative(Node* root)
  {
    if (root == nullptr)
    {
      return {};
    }
    vector<int> ans;
    stack<Node*> stA;
    stack<Node*> stB;
    stA.push(root);
    while (!stA.empty())
    {
      Node* cur = stA.top();
      stA.pop();
      // 根 右 左
      stB.push(cur);
      for (auto& c : cur->children)
      {
        stA.push(c);
      }
    }

    while (!stB.empty())
    {
      // 左 右 根
      Node* cur = stB.top();
      stB.pop();
      ans.push_back(cur->val);
    }
    return ans;
  }
};
