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
  int idx;

  TreeNode* f(int left,
              int right,
              vector<int>& inorder,
              vector<int>& postorder,
              unordered_map<int, int>& map)
  {
    if (left > right)
    {
      // 没有节点构造二叉树
      return nullptr;
    }
    // 选择 idx 位置的元素作为当前子树的根节点
    int val = postorder[idx];
    TreeNode* root = new TreeNode(val);

    // 根据 root 所在位置，把中序遍历分成左右两颗子树
    int mid = map[val];
    // 下标减1
    idx--;

    // 注意: 这里需要先创建右子树，再创建左子树的依赖关系。
    // 可以理解为在后序遍历的数组中整个数组是先存储左子树的节点，再存储右子树的节点，最后存储根节点，
    // 如果按每次选择「后序遍历的最后一个节点」为根节点，则先被构造出来的应该为右子树。

    // 构造右子树
    root->right = f(mid + 1, right, inorder, postorder, map);
    // 构造左子树
    root->left = f(left, mid - 1, inorder, postorder, map);
    return root;
  }

 public:
  // 递归法
  TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder)
  {
    // 从后序遍历的最后一个元素开始
    idx = postorder.size() - 1;
    // 建立 {元素，下标} 哈希表
    unordered_map<int, int> map;
    for (int i = 0; i < inorder.size(); i++)
    {
      map[inorder[i]] = i;
    }

    return f(0, inorder.size() - 1, inorder, postorder, map);
  }
  // TODO: 迭代法
};
