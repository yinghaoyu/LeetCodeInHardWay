#include <functional>
#include <iostream>
#include <vector>

using namespace std;

struct TreeNode
{
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// seem as leetcode 0173
// https://leetcode-cn.com/problems/binary-search-tree-iterator/
// see at Problem_0173_BSTIterator.cc
class BSTIterator
{
 private:
  vector<int> arr;
  int idx;

 public:
  vector<int> inorder(TreeNode *root)
  {
    vector<int> ans;
    function<void(TreeNode *)> dfs = [&](TreeNode *cur)
    {
      if (cur == nullptr)
      {
        return;
      }
      dfs(cur->left);
      ans.push_back(cur->val);
      dfs(cur->right);
    };
    dfs(root);
    return ans;
  };

  BSTIterator(TreeNode *root)
  {
    arr = inorder(root);
    idx = 0;
  }

  int next() { return arr[idx++]; }

  bool hasNext() { return idx < arr.size(); }
};

/**
 * Your BSTIterator object will be instantiated and called as such:
 * BSTIterator* obj = new BSTIterator(root);
 * int param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */
