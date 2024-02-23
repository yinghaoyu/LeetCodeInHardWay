#include <algorithm>
#include <queue>
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
 public:
  long long kthLargestLevelSum(TreeNode* root, int k)
  {
    if (root == nullptr)
    {
      return -1;
    }
    int level = 0;
    queue<TreeNode*> q;
    q.push(root);
    vector<long long> nums;
    while (!q.empty())
    {
      int size = q.size();
      long long sum = 0;
      for (int i = 0; i < size; i++)
      {
        TreeNode* cur = q.front();
        q.pop();
        if (cur->left)
        {
          q.push(cur->left);
        }
        if (cur->right)
        {
          q.push(cur->right);
        }
        sum += cur->val;
      }
      nums.push_back(sum);
    }
    std::sort(nums.begin(), nums.end());
    int idx = nums.size() - k;
    if (idx >= 0)
    {
      return nums[idx];
    }
    return -1;
  }
};
