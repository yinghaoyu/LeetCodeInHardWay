#include <vector>

using namespace std;

struct ListNode
{
  int val;
  ListNode* next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode* next) : val(x), next(next) {}
};

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
  bool dfs(TreeNode* rt, ListNode* head)
  {
    if (head == NULL)
    {
      // 链表已经全部匹配完，匹配成功
      return true;
    }
    if (rt == NULL)
    {
      // 二叉树访问到了空节点，匹配失败
      return false;
    }
    if (rt->val != head->val)
    {
      // 当前匹配的二叉树上节点的值与链表节点的值不相等，匹配失败
      return false;
    }
    return dfs(rt->left, head->next) || dfs(rt->right, head->next);
  }

  bool isSubPath1(ListNode* head, TreeNode* root)
  {
    if (root == NULL)
    {
      return false;
    }
    return dfs(root, head) || isSubPath1(head, root->left) || isSubPath1(head, root->right);
  }

  // KMP变种
  bool isSubPath2(ListNode* head, TreeNode* root)
  {
    int m = 0;
    ListNode* tmp = head;
    while (tmp != nullptr)
    {
      m++;
      tmp = tmp->next;
    }
    vector<int> s2(m);
    m = 0;
    while (head != nullptr)
    {
      s2[m++] = head->val;
      head = head->next;
    }
    vector<int> next = nextArray(s2, m);
    return find(s2, next, root, 0);
  }

  // 二叉树来到cur节点了
  // 链表比对的位置来到i位置
  // 利用链表的next数组加速匹配
  // 返回是否能把链表整体匹配出来
  bool find(vector<int>& s2, vector<int>& next, TreeNode* cur, int i)
  {
    if (i == s2.size())
    {
      return true;
    }
    if (cur == nullptr)
    {
      return false;
    }
    // 当前来到cur节点, 一开始的i是父亲节点给的
    // 但是要修正，找到配成的位置
    // 均摊下来，时间复杂度O(1)
    while (i >= 0 && cur->val != s2[i])
    {
      i = next[i];
    }
    return find(s2, next, cur->left, i + 1) || find(s2, next, cur->right, i + 1);
  }

  vector<int> nextArray(vector<int>& s, int m)
  {
    if (m == 1)
    {
      return {-1};
    }
    vector<int> next(m);
    next[0] = -1;
    next[1] = 0;
    int i = 2, cn = 0;
    while (i < m)
    {
      if (s[i - 1] == s[cn])
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
