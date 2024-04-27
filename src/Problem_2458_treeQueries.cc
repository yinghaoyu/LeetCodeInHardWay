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

// 树型dp
// 什么叫dfn序，dfs依次遍历节点并给它分配一个编号
// 比如节点的dfn序为4，有4个节点
// 那么它及子树的dfn序是 4 ~ 7 总共 4 个节点
// 可以确定 dfn 序为 5 的在这个子树内
// @sa https://www.bilibili.com/video/BV1ae411f7AC/
class Solution
{
 public:
  static const int MAXN = 100010;

  // 下标为节点的值
  int dfn[MAXN];

  // 下标为dfn序号
  int deep[MAXN];

  // 下标为dfn序号
  int size[MAXN];

  int maxl[MAXN];

  int maxr[MAXN];

  int dfnCnt;

  vector<int> treeQueries(TreeNode* root, vector<int>& queries)
  {
    dfnCnt = 0;
    f(root, 0);
    // 预处理最大值
    for (int i = 1; i <= dfnCnt; i++)
    {
      maxl[i] = std::max(maxl[i - 1], deep[i]);
    }
    maxr[dfnCnt + 1] = 0;
    for (int i = dfnCnt; i >= 1; i--)
    {
      maxr[i] = std::max(maxr[i + 1], deep[i]);
    }
    int m = queries.size();
    vector<int> ans(m);
    for (int i = 0; i < m; i++)
    {
      int leftMax = maxl[dfn[queries[i]] - 1];
      int rightMax = maxr[dfn[queries[i]] + size[dfn[queries[i]]]];
      ans[i] = std::max(leftMax, rightMax);
    }
    return ans;
  }

  // 来到x节点，从头节点到x节点经过了k条边
  void f(TreeNode* x, int k)
  {
    // 分配 dfn 序号
    int i = ++dfnCnt;
    dfn[x->val] = i;
    deep[i] = k;
    size[i] = 1;
    if (x->left != nullptr)
    {
      f(x->left, k + 1);
      // 加上左孩子的节点数
      size[i] += size[dfn[x->left->val]];
    }
    if (x->right != nullptr)
    {
      f(x->right, k + 1);
      // 加上右孩子的节点数
      size[i] += size[dfn[x->right->val]];
    }
  }
};
