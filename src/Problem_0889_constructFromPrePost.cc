#include <unordered_map>
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
 private:
  unordered_map<int, int> map;

  TreeNode* f(int pre_left,
              int pre_right,
              int post_left,
              int post_right,
              vector<int>& preorder,
              vector<int>& postorder)
  {
    if (pre_left > pre_right)
    {
      // 没有节点
      return nullptr;
    }
    if (pre_left == pre_right)
    {
      return new TreeNode(preorder[pre_left]);
    }
    // 前序遍历的第一个节点为根节点
    int root_val = preorder[pre_left];
    // 找到根节点左孩子在后序遍历的下标
    int left_child_idx = map[preorder[pre_left + 1]];

    // 确定当前节点左子树大小
    int left_size = left_child_idx - post_left + 1;

    TreeNode* root = new TreeNode(root_val);
    // 根据左子树、右子树的区间递归求解
    // 前序遍历位置 pre_left 已经是当前根节点，因此要取 pre_left + 1
    root->left = f(pre_left + 1, pre_left + left_size, post_left, post_left + left_size - 1,
                   preorder, postorder);
    // 后序遍历 post_right 已经是当前根节点，因此要取 post_right - 1
    root->right = f(pre_left + left_size + 1, pre_right, post_left + left_size, post_right - 1,
                    preorder, postorder);
    return root;
  }

 public:
  // 思路是，找到当前根节点的左孩子在后序遍历的位置，然后确定左子树和右子树的区间
  TreeNode* constructFromPrePost(vector<int>& preorder, vector<int>& postorder)
  {
    // 建立后序遍历 {值，位置} 索引表
    for (int i = 0; i < postorder.size(); i++)
    {
      map[postorder[i]] = i;
    }
    return f(0, preorder.size() - 1, 0, postorder.size() - 1, preorder, postorder);
  }
};
