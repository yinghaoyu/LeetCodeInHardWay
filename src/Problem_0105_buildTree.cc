#include <queue>
#include <unordered_map>
#include <utility>
#include <vector>

#include "UnitTest.h"

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
  int root_idx;
  unordered_map<int, int> map;

  // 与 Problem_0106_buildTree.cc 类似
  TreeNode* f(int in_left, int in_right, vector<int>& preorder, vector<int>& inorder)
  {
    if (in_left > in_right)
    {
      return nullptr;
    }
    int val = preorder[root_idx];
    TreeNode* root = new TreeNode(val);

    root_idx++;
    int in_root = map[val];

    // 根据前序遍历的性质，根左右
    // 需严格先构造左子树，再构造右子树
    root->left = f(in_left, in_root - 1, preorder, inorder);
    root->right = f(in_root + 1, in_right, preorder, inorder);
    return root;
  }

 public:
  TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder)
  {
    root_idx = 0;
    for (int i = 0; i < inorder.size(); i++)
    {
      map[inorder[i]] = i;
    }
    return f(0, inorder.size() - 1, preorder, inorder);
  }
};

bool isSameTree(TreeNode* head1, TreeNode* head2)
{
  if (head1 == nullptr && head2 == nullptr)
  {
    return true;
  }
  if (head1 != nullptr && head2 != nullptr)
  {
    return head1->val == head2->val && isSameTree(head1->left, head2->left) &&
           isSameTree(head1->right, head2->right);
  }
  return false;
}

void testZigzagLevelOrder()
{
  Solution s;
  TreeNode* x5 = new TreeNode(7, nullptr, nullptr);
  TreeNode* x4 = new TreeNode(15, nullptr, nullptr);
  TreeNode* x3 = new TreeNode(20, x4, x5);
  TreeNode* x2 = new TreeNode(9, nullptr, nullptr);
  TreeNode* x1 = new TreeNode(3, x2, x3);
  vector<int> p1 = {3, 9, 20, 15, 7};
  vector<int> i1 = {9, 3, 15, 20, 7};

  TreeNode* y = new TreeNode(-1);
  vector<int> p2 = {-1};
  vector<int> i2 = {-1};

  EXPECT_TRUE(isSameTree(x1, s.buildTree(p1, i1)));
  EXPECT_TRUE(isSameTree(y, s.buildTree(p2, i2)));
  EXPECT_SUMMARY;
}

int main()
{
  testZigzagLevelOrder();
  return 0;
}
