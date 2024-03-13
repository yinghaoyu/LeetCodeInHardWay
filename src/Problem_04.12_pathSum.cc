#include <iostream>
#include <unordered_map>

using namespace std;

struct TreeNode
{
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// @sa Problem_0437_pathSum.cc
class Solution
{
 public:
  int f(TreeNode* x, long long cur, int sum, unordered_map<long long, int>& map)
  {
    if (x == nullptr)
    {
      return 0;
    }
    int ans = 0;
    cur += x->val;
    if (map.count(cur - sum))
    {
      ans = map[cur - sum];
    }
    map[cur]++;
    ans += f(x->left, cur, sum, map);
    ans += f(x->right, cur, sum, map);
    map[cur]--;
    return ans;
  }

  int pathSum(TreeNode* root, int sum)
  {
    unordered_map<long long, int> map;
    map[0] = 1;
    return f(root, 0, sum, map);
  }
};
