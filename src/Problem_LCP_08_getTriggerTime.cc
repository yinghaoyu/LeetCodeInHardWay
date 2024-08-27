#include <vector>

using namespace std;

class Solution
{
 public:
  vector<int> getTriggerTime(vector<vector<int>>& increase, vector<vector<int>>& requirements)
  {
    int n = increase.size();
    vector<vector<int>> s(n + 1, vector<int>(3, 0));
    for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < 3; j++)
      {
        // 求每个维度的前缀和
        s[i + 1][j] = s[i][j] + increase[i][j];
      }
    }
    // increase 一定是单调递增的，符合单调性，可以用二分查找
    vector<int> ans;
    for (auto& v : requirements)
    {
      // 注意这里的区间为左闭右开
      int l = 0;
      int r = n;
      while (l < r)
      {
        int m = (r - l) / 2 + l;
        if (s[m][0] >= v[0] && s[m][1] >= v[1] && s[m][2] >= v[2])
        {
          // 由于右边是开区间，当前m已经计算过了，所以令r = m
          r = m;
        }
        else
        {
          // 由于左边是闭区间，当前m已经计算过了，所以令 l = m + 1
          l = m + 1;
        }
      }
      // 下面取 l 或者 r 都行
      if (s[l][0] >= v[0] && s[l][1] >= v[1] && s[l][2] >= v[2])
      {
        ans.push_back(l);
      }
      else
      {
        ans.push_back(-1);
      }
    }
    return ans;
  }
};
