#include <functional>
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
  vector<int> f(TreeNode* root, int x)
  {
    if (root == nullptr)
    {
      return {-1, -1};
    }
    int L = -1, R = -1;
    TreeNode* cur = root;
    while (cur != nullptr)
    {
      if (cur->val < x)
      {
        L = cur->val;
        cur = cur->right;
      }
      else if (cur->val > x)
      {
        R = cur->val;
        cur = cur->left;
      }
      else
      {
        L = cur->val;
        R = cur->val;
        break;
      }
    }
    return {L, R};
  }

  // 递归解法部分用例超时，题设条件的二叉搜索树不一定是平衡的，存在极端情况时间复杂度为O(N)
  vector<vector<int>> closestNodes1(TreeNode* root, vector<int>& queries)
  {
    vector<vector<int>> ans;
    for (auto& x : queries)
    {
      vector<int> interval = f(root, x);
      ans.push_back(std::move(interval));
    }
    return ans;
  }

  // 中序遍历然后二分查找，时间复杂度O(logN)
  vector<vector<int>> closestNodes2(TreeNode* root, vector<int>& queries)
  {
    vector<int> tree;
    function<void(TreeNode*)> dfs = [&](TreeNode* cur)
    {
      if (cur == nullptr)
      {
        return;
      }
      dfs(cur->left);
      tree.push_back(cur->val);
      dfs(cur->right);
    };
    dfs(root);

    vector<vector<int>> ans;
    for (int x : queries)
    {
      int left = nearLeft(tree, x);
      int right = nearRight(tree, x);
      ans.push_back({left, right});
    }
    return ans;
  }

  int nearLeft(vector<int>& arr, int x)
  {
    int L = 0;
    int R = arr.size() - 1;
    int ans = -1;
    while (L <= R)
    {
      int M = (R - L) / 2 + L;
      if (arr[M] <= x)
      {
        ans = arr[M];
        L = M + 1;
      }
      else
      {
        R = M - 1;
      }
    }
    return ans;
  }

  int nearRight(vector<int>& arr, int x)
  {
    int L = 0;
    int R = arr.size() - 1;
    int ans = -1;
    while (L <= R)
    {
      int M = (R - L) / 2 + L;
      if (x <= arr[M])
      {
        ans = arr[M];
        R = M - 1;
      }
      else
      {
        L = M + 1;
      }
    }
    return ans;
  }
};
