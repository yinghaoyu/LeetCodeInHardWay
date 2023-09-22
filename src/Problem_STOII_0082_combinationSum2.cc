#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// @sa https://leetcode-cn.com/problems/combination-sum-ii/
// @sa Problem_0040_combinationSum2.cc

class Solution
{
 public:
  void process(vector<std::pair<int, int>> &freq, int index, int target, vector<int> &selected, vector<vector<int>> &ans)
  {
    if (target == 0)
    {
      ans.push_back(selected);
      return;
    }
    if (index == freq.size() || target < freq[index].first)
    {
      return;
    }
    for (int i = 0; i * freq[index].first <= target && i <= freq[index].second; i++)
    {
      std::fill_n(std::back_inserter(selected), i, freq[index].first);
      process(freq, index + 1, target - i * freq[index].first, selected, ans);
      selected.erase(std::remove(selected.begin(), selected.end(), freq[index].first), selected.end());
    }
  }

  vector<vector<int>> combinationSum2(vector<int> &candidates, int target)
  {
    std::sort(candidates.begin(), candidates.end());
    vector<std::pair<int, int>> freq;
    for (auto &num : candidates)
    {
      if (freq.empty() || num != freq.back().first)
      {
        freq.emplace_back(num, 1);
      }
      else
      {
        ++freq.back().second;
      }
    }
    vector<int> selected;
    vector<vector<int>> ans;
    process(freq, 0, target, selected, ans);
    return ans;
  }
};
