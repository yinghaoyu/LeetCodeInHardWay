#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

// 动态规划中得到具体决策方案

// @sa https://www.bilibili.com/video/BV1L94y1w72w/
class Solution
{
 public:
  vector<int> smallestSufficientTeam(vector<string>& req_skills, vector<vector<string>>& people)
  {
    int n = req_skills.size();
    int m = people.size();
    unordered_map<string, int> map;
    int cnt = 0;
    for (string& s : req_skills)
    {
      // 把所有必要技能依次编号
      map.emplace(s, cnt++);
    }
    // arr[i] : 第i号人掌握必要技能的状况，用位信息表示
    vector<int> arr(m);
    for (int i = 0, status; i < m; i++)
    {
      status = 0;
      for (string& skill : people.at(i))
      {
        if (map.count(skill))
        {
          // 如果当前技能是必要的
          // 才设置status
          status |= 1 << map.at(skill);
        }
      }
      arr[i] = status;
    }
    vector<vector<int>> dp(m, vector<int>(1 << n, -1));
    int size = f(arr, m, n, 0, 0, dp);
    vector<int> ans(size);
    for (int j = 0, i = 0, s = 0; s != (1 << n) - 1; i++)
    {
      // s还没凑齐
      if (i == m - 1 || dp[i][s] != dp[i + 1][s])
      {
        // 当初的决策是选择了i号人
        ans[j++] = i;
        s |= arr[i];
      }
    }
    return ans;
  }

  // arr : 每个人所掌握的必要技能的状态
  // m : 人的总数
  // n : 必要技能的数量
  // i : 当前来到第几号人
  // s : 必要技能覆盖的状态
  // 返回 : i....这些人，把必要技能都凑齐，至少需要几个人
  int f(vector<int>& arr, int m, int n, int i, int s, vector<vector<int>>& dp)
  {
    if (s == (1 << n) - 1)
    {
      // 所有技能已经凑齐了
      return 0;
    }
    // 没凑齐
    if (i == m)
    {
      // 人已经没了，技能也没凑齐
      // 无效
      return INT32_MAX;
    }
    if (dp[i][s] != -1)
    {
      return dp[i][s];
    }
    // 可能性1 : 不要i号人
    int p1 = f(arr, m, n, i + 1, s, dp);
    // 可能性2 : 要i号人
    int p2 = INT32_MAX;
    int next2 = f(arr, m, n, i + 1, s | arr[i], dp);
    if (next2 != INT32_MAX)
    {
      // 后续有效
      p2 = 1 + next2;
    }
    int ans = std::min(p1, p2);
    dp[i][s] = ans;
    return ans;
  }
};
