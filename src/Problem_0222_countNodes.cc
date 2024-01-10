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
  int countNodes(TreeNode* root)
  {
    if (root == nullptr)
    {
      return 0;
    }
    return f(root, 1, mostLeft(root, 1));
  }

  // cur: 当前来到的节点
  // level: 当前来到的节点在第几层
  // h: 整棵树的高度，不是 cur 这颗子树的高度
  // 求: cur 这颗子树上有多少个节点
  int f(TreeNode* cur, int level, int h)
  {
    if (level == h)
    {
      return 1;
    }
    if (mostLeft(cur->right, level + 1) == h)
    {
      // cur 右树上的最左节点，扎到了最深层
      return (1 << (h - level)) + f(cur->right, level + 1, h);
    }
    else
    {
      // cur 右树上的最左节点，没扎到最深层
      return (1 << (h - level - 1)) + f(cur->left, level + 1, h);
    }
  }

  // 当前节点是 cur，并且它在 level 层
  // 返回从 cur 开始不停往左，能扎到第几层
  int mostLeft(TreeNode* cur, int level)
  {
    while (cur != nullptr)
    {
      level++;
      cur = cur->left;
    }
    return level - 1;
  }
};
