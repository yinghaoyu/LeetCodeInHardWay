#include <iostream>
#include <vector>

using namespace std;

// @sa https://leetcode-cn.com/problems/combinations/
// @sa Problem_0077_combine.cc

class Solution
{
 public:
  void process(int n, int i, int k, vector<int> &selected, vector<vector<int>> &ans)
  {
    if (selected.size() + (n - i + 1) < k)
    {
      // 剪枝：selected 长度加上区间 [i, n] 的长度小于 k,
      // 不可能构造出长度为 k 的 selected
      return;
    }
    if (k == 0)
    {
      ans.push_back(selected);
      return;
    }
    if (i > n)
    {
      return;
    }
    selected.push_back(i);
    process(n, i + 1, k - 1, selected, ans);
    selected.pop_back();
    process(n, i + 1, k, selected, ans);
  }
  vector<vector<int>> combine(int n, int k)
  {
    vector<int> selected;
    vector<vector<int>> ans;
    process(n, 1, k, selected, ans);
    return ans;
  }
};
