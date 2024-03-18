#include <vector>

using namespace std;

class Solution
{
 public:
  vector<vector<int>> subsets(vector<int>& nums)
  {
    int n = nums.size();
    int mask = 1 << n;
    vector<vector<int>> ans;
    for (int i = 0; i < mask; i++)
    {
      vector<int> cur;
      for (int j = 0; j < 32; j++)
      {
        if (i & (1 << j))
        {
          cur.emplace_back(nums[j]);
        }
      }
      ans.emplace_back(cur);
    }
    return ans;
  }

  void dfs(vector<int>& nums, int index, vector<int>& cur, vector<vector<int>>& ans)
  {
    if (index == nums.size())
    {
      ans.push_back(cur);
      return;
    }
    cur.push_back(nums[index]);
    dfs(nums, index + 1, cur, ans);
    cur.pop_back();
    dfs(nums, index + 1, cur, ans);
  }
};
