#include <queue>
#include <utility>
#include <vector>

#include "UnitTest.h"

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

class Solution
{
 public:
  vector<vector<int>> levelOrder(TreeNode *root)
  {
    vector<vector<int>> ans;
    if (root == nullptr)
    {
      return ans;
    }
    queue<TreeNode *> q;
    q.push(root);
    int n = 0;
    while (!q.empty())
    {
      n = q.size();
      vector<int> tmp;
      for (int i = 0; i < n; i++)
      {
        TreeNode *cur = q.front();
        q.pop();

        if (cur->left != nullptr)
        {
          q.push(cur->left);
        }
        if (cur->right != nullptr)
        {
          q.push(cur->right);
        }
        tmp.push_back(cur->val);
      }
      ans.emplace_back(tmp);
    }
    return ans;
  }
};

void testLevelOrder()
{
  Solution s;
  TreeNode *x5 = new TreeNode(7, nullptr, nullptr);
  TreeNode *x4 = new TreeNode(15, nullptr, nullptr);
  TreeNode *x3 = new TreeNode(20, x4, x5);
  TreeNode *x2 = new TreeNode(9, nullptr, nullptr);
  TreeNode *x1 = new TreeNode(3, x2, x3);
  vector<vector<int>> o1 = {{3}, {9, 20}, {15, 7}};

  TreeNode *y = new TreeNode(1, nullptr, nullptr);
  vector<vector<int>> o2 = {{1}};

  TreeNode *z = nullptr;
  vector<vector<int>> o3;

  EXPECT_TRUE(o1 == s.levelOrder(x1));
  EXPECT_TRUE(o2 == s.levelOrder(y));
  EXPECT_TRUE(o3 == s.levelOrder(z));
  EXPECT_SUMMARY;
}

int main()
{
  testLevelOrder();
  return 0;
}
