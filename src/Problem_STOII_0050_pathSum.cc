#include <functional>
#include <iostream>
#include <unordered_map>

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

// seem as leetcode 0437
// https://leetcode-cn.com/problems/path-sum-iii/
// Problem_0437_pathSum.cc

class Solution
{
 public:
  int pathSum(TreeNode *root, int targetSum)
  {
    if (root == nullptr)
    {
      return 0;
    }
    unordered_map<long long, int> map;
    // 保证单个节点也满足条件
    map.emplace(0LL, 1);
    std::function<int(TreeNode *, long long)> dfs = [&](TreeNode *cur, long long sum)
    {
      if (cur == nullptr)
      {
        return 0;
      }
      sum += cur->val;
      int ans = 0;
      if (map.count(sum - targetSum))
      {
        ans = map[sum - targetSum];
      }
      map[sum]++;
      ans += dfs(cur->left, sum);
      ans += dfs(cur->right, sum);
      // 恢复的意义：路径和必须是向下的
      // https://leetcode.cn/problems/path-sum-iii/solution/dui-qian-zhui-he-jie-fa-de-yi-dian-jie-s-dey6/
      map[sum]--;
      return ans;
    };

    return dfs(root, 0);
  }
};
