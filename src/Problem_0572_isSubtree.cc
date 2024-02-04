#include <string>
#include <vector>

using namespace std;

struct TreeNode
{
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

class Solution
{
 public:
  // 暴力递归
  // 时间复杂度O(n * m)
  bool isSubtree1(TreeNode* root, TreeNode* subRoot)
  {
    if (root != nullptr && subRoot != nullptr)
    {
      return same(root, subRoot) || isSubtree1(root->left, subRoot) ||
             isSubtree1(root->right, subRoot);
    }
    return subRoot == nullptr;
  }

  // 判断a和b这两棵树是否完全一样
  bool same(TreeNode* a, TreeNode* b)
  {
    if (a == nullptr && b == nullptr)
    {
      return true;
    }
    if (a != nullptr && b != nullptr)
    {
      return a->val == b->val && same(a->left, b->left) && same(a->right, b->right);
    }
    return false;
  }

  // 二叉树先序序列化 + KMP算法匹配
  // 时间复杂度O(n + m)
  bool isSubtree2(TreeNode* root, TreeNode* subRoot)
  {
    if (root != nullptr && subRoot != nullptr)
    {
      vector<string> s1;
      vector<string> s2;
      serial(root, s1);
      serial(subRoot, s2);
      return kmp(s1, s2) != -1;
    }
    return subRoot == nullptr;
  }

  void serial(TreeNode* head, vector<string>& path)
  {
    if (head == nullptr)
    {
      path.push_back(",");
    }
    else
    {
      path.push_back(std::to_string(head->val));
      serial(head->left, path);
      serial(head->right, path);
    }
  }

  int kmp(vector<string>& s, vector<string>& m)
  {
    if (s.size() < m.size())
    {
      return -1;
    }
    if (m.size() == 0)
    {
      return 0;
    }
    int x = 0;
    int y = 0;
    vector<int> next = getNextArray(m);
    while (x < s.size() && y < m.size())
    {
      if (s[x] == m[y])
      {
        x++;
        y++;
      }
      else if (next[y] == -1)
      {
        x++;
      }
      else
      {
        y = next[y];
      }
    }
    return y == m.size() ? x - y : -1;
  }

  vector<int> getNextArray(vector<string>& ms)
  {
    if (ms.size() == 1)
    {
      return {-1};
    }
    vector<int> next(ms.size());
    next[0] = -1;
    next[1] = 0;
    int i = 2;
    // cn代表，cn位置的字符，是当前和i-1位置比较的字符
    int cn = 0;
    while (i < next.size())
    {
      if (ms[i - 1] == ms[cn])
      {
        next[i++] = ++cn;
      }
      else if (cn > 0)
      {
        cn = next[cn];
      }
      else
      {
        next[i++] = 0;
      }
    }
    return next;
  }
};
