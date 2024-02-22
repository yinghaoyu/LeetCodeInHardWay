#include <queue>
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
 public:
  vector<vector<int>> levelOrder(Node* root)
  {
    vector<vector<int>> ans;
    if (root == nullptr)
    {
      return ans;
    }
    queue<Node*> q;
    q.push(root);
    while (!q.empty())
    {
      int size = q.size();
      vector<int> nodes;
      for (int i = 0; i < size; i++)
      {
        Node* cur = q.front();
        q.pop();
        nodes.push_back(cur->val);
        for (auto& c : cur->children)
        {
          q.push(c);
        }
      }
      ans.push_back(std::move(nodes));
    }
    return ans;
  }
};
