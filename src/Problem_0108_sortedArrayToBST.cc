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
       TreeNode* process(vector<int>& nums, int l , int r)
    {
      if(l > r)
      {
        return nullptr;
      }
      int m = (r - l) / 2 + l;
      TreeNode *head = new TreeNode(nums[m]);
      if(l == r)
      {
        return head; 
      }
      head->left = process(nums, l, m - 1);
      head->right = process(nums, m + 1, r);
      return head;
    }

    TreeNode* sortedArrayToBST(vector<int>& nums) {
      return process(nums, 0, nums.size() - 1);
    }
};

bool isSameTree(TreeNode *head1, TreeNode *head2)
{
  if (head1 == nullptr && head2 == nullptr)
  {
    return true;
  }
  if (head1 != nullptr && head2 != nullptr)
  {
    return head1->val == head2->val && isSameTree(head1->left, head2->left) && isSameTree(head1->right, head2->right);
  }
  return false;
}

void testSortedArrayToBST()
{
  Solution s;
  TreeNode *x5 = new TreeNode(9, nullptr, nullptr);
  TreeNode *x4 = new TreeNode(-3, nullptr, nullptr);
  TreeNode *x3 = new TreeNode(5, nullptr, x5);
  TreeNode *x2 = new TreeNode(-10, nullptr, x4);
  TreeNode *x1 = new TreeNode(0, x2, x3);
  vector<int> n1 = {-10,-3, 0, 5, 9};

  TreeNode *y2 = new TreeNode(3, nullptr, nullptr);
  TreeNode *y1 = new TreeNode(1, nullptr, y2);
  vector<int> n2 = {1,3};

  EXPECT_TRUE(isSameTree(x1, s.sortedArrayToBST(n1)));
  EXPECT_TRUE(isSameTree(y1, s.sortedArrayToBST(n2)));
  EXPECT_SUMMARY;
}

int main()
{
  testSortedArrayToBST();
  return 0;
}
