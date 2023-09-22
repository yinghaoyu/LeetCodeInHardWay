#include <iostream>
#include <vector>

using namespace std;

class Solution
{
 public:
  void process(vector<int> &nums, int index, vector<vector<int>> &ans)
  {
    if (index == nums.size())
    {
      ans.push_back(nums);
      return;
    }
    vector<bool> visited(22);
    for (int i = index; i < nums.size(); i++)
    {
      if (!visited[nums[i] + 10])
      {
        visited[nums[i] + 10] = true;
        swap(nums[index], nums[i]);
        process(nums, index + 1, ans);
        swap(nums[index], nums[i]);
      }
    }
  }

  vector<vector<int>> permuteUnique(vector<int> &nums)
  {
    vector<vector<int>> ans;
    process(nums, 0, ans);
    return ans;
  }
};
