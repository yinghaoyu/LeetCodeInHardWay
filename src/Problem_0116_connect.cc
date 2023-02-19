#include <iostream>
#include <queue>

using namespace std;

class Node
{
 public:
  int val;
  Node *left;
  Node *right;
  Node *next;

  Node() : val(0), left(NULL), right(NULL), next(NULL) {}

  Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

  Node(int _val, Node *_left, Node *_right, Node *_next) : val(_val), left(_left), right(_right), next(_next) {}
};

class Solution
{
 public:
  Node *connect(Node *root)
  {
    if (root == nullptr)
    {
      return root;
    }
    queue<Node *> q;
    q.push(root);
    while (!q.empty())
    {
      int n = q.size();
      for (int i = 0; i < n; i++)
      {
        Node *cur = q.front();
        q.pop();
        if (i < n - 1)
        {
          cur->next = q.front();
        }
        if (cur->left != nullptr)
        {
          q.push(cur->left);
        }
        if (cur->right != nullptr)
        {
          q.push(cur->right);
        }
      }
    }
    return root;
  }
};
