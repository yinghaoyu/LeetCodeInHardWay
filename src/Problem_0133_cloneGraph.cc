#include <queue>
#include <unordered_map>
#include <vector>

using namespace std;

class Node
{
 public:
  int val;
  vector<Node*> neighbors;
  Node()
  {
    val = 0;
    neighbors = vector<Node*>();
  }
  Node(int _val)
  {
    val = _val;
    neighbors = vector<Node*>();
  }
  Node(int _val, vector<Node*> _neighbors)
  {
    val = _val;
    neighbors = _neighbors;
  }
};

class Solution
{
 public:
  // dfs
  Node* f(Node* node, unordered_map<Node*, Node*>& visited)
  {
    if (node == nullptr)
    {
      return node;
    }
    // 如果该节点已经被访问过了，则直接从哈希表中取出对应的克隆节点返回
    if (visited.count(node))
    {
      return visited[node];
    }
    // 克隆节点，注意到为了深拷贝我们不会克隆它的邻居的列表
    Node* clone = new Node(node->val);
    // 存储
    visited[node] = clone;
    // 遍历该节点的邻居并更新克隆节点的邻居列表
    for (auto& neighbor : node->neighbors)
    {
      clone->neighbors.emplace_back(f(neighbor, visited));
    }
    return clone;
  }

  Node* cloneGraph1(Node* node)
  {
    unordered_map<Node*, Node*> visited;
    return f(node, visited);
  }

  // bfs
  Node* cloneGraph2(Node* node)
  {
    if (node == nullptr)
    {
      return node;
    }
    unordered_map<Node*, Node*> visited;

    queue<Node*> q;
    q.push(node);
    visited[node] = new Node(node->val);

    while (!q.empty())
    {
      auto cur = q.front();
      q.pop();
      for (auto& neighbor : cur->neighbors)
      {
        if (!visited.count(neighbor))
        {
          visited[neighbor] = new Node(neighbor->val);
          q.push(neighbor);
        }
        visited[cur]->neighbors.emplace_back(visited[neighbor]);
      }
    }
    return visited[node];
  }
};
