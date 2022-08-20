#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class TreeNode
{
 public:
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
  int findMaxIndex(vector<int> &nums, int L, int R)
  {
    int index = L;
    for (int i = L; i <= R; i++)
    {
      if (nums[i] > nums[index])
      {
        index = i;
      }
    }
    return index;
  }

  TreeNode *process(vector<int> &nums, int L, int R)
  {
    if (L > R)
    {
      return nullptr;
    }
    int index = findMaxIndex(nums, L, R);
    TreeNode *cur = new TreeNode(nums[index]);
    cur->left = process(nums, L, index - 1);
    cur->right = process(nums, index + 1, R);
    return cur;
  }

  TreeNode *constructMaximumBinaryTree(vector<int> &nums) { return process(nums, 0, nums.size() - 1); }
};

bool isSameValueStructure(TreeNode *head1, TreeNode *head2)
{
  if (head1 == nullptr && head2 != nullptr)
  {
    return false;
  }
  if (head1 != nullptr && head2 == nullptr)
  {
    return false;
  }
  if (head1 == nullptr && head2 == nullptr)
  {
    return true;
  }
  if (head1->val != head2->val)
  {
    return false;
  }
  return isSameValueStructure(head1->left, head2->left) && isSameValueStructure(head1->right, head2->right);
}

void testConstructMaximumBinaryTree()
{
  Solution s;
  vector<int> arr = {3, 2, 1, 6, 0, 5};
  TreeNode *x6 = new TreeNode(1, nullptr, nullptr);
  TreeNode *x5 = new TreeNode(2, nullptr, x6);
  TreeNode *x4 = new TreeNode(0, nullptr, nullptr);
  TreeNode *x3 = new TreeNode(3, nullptr, x5);
  TreeNode *x2 = new TreeNode(5, x4, nullptr);
  TreeNode *x1 = new TreeNode(6, x3, x2);
  EXPECT_TRUE(isSameValueStructure(x1, s.constructMaximumBinaryTree(arr)));
  EXPECT_SUMMARY;
}

int main()
{
  testConstructMaximumBinaryTree();
  return 0;
}
