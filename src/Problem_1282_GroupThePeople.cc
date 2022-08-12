#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

// 测试链接：https://leetcode.cn/problems/group-the-people-given-the-group-size-they-belong-to/

class Solution
{
 public:
  static vector<vector<int>> groupThePeople(vector<int> &groupSizes)
  {
    vector<vector<int>> ans;
    unordered_map<int, vector<int>> m;
    for (int i = 0; i < groupSizes.size(); i++)
    {
      m[groupSizes[i]].push_back(i);
    }
    for (auto entry : m)
    {
      for (auto cur = entry.second.begin(); cur != entry.second.end(); cur += entry.first)
      {
        // 根据题意，这里cur+ entry.first刚好不越界
        ans.push_back(vector<int>(cur, cur + entry.first));
      }
    }
    return ans;
  }
};

int main()
{
  vector<int> arr = {3, 3, 3, 3, 3, 1, 3};
  vector<vector<int>> ans = Solution::groupThePeople(arr);
  for (int i = 0; i < ans.size(); i++)
  {
    for (int j = 0; j < ans[i].size(); j++)
    {
      cout << ans[i][j] << " ";
    }
    cout << endl;
  }
  return 0;
}
