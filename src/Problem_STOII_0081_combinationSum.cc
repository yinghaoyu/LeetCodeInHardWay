#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// @sa https://leetcode-cn.com/problems/combination-sum/
// Problem_0039_combinationSum.cc

class Solution
{
 public:
  void process(vector<int> &candidates, int index, int target, vector<int> &selected, vector<vector<int>> &ans)
  {
    if (index == candidates.size())
    {
      if (target == 0)
      {
        ans.push_back(selected);
      }
      return;
    }
    for (int i = 0; i * candidates[index] <= target; i++)
    {
      std::fill_n(std::back_inserter(selected), i, candidates[index]);
      process(candidates, index + 1, target - i * candidates[index], selected, ans);
      selected.erase(std::remove(selected.begin(), selected.end(), candidates[index]), selected.end());
    }
  }

  vector<vector<int>> combinationSum(vector<int> &candidates, int target)
  {
    vector<int> selected;
    vector<vector<int>> ans;
    process(candidates, 0, target, selected, ans);
    return ans;
  }
};
