#include <vector>

using namespace std;

class Solution
{
 private:
  // limit : 每条边规定的长度
  // status : 表示哪些数字还可以选
  // cur : 当前要解决的这条边已经形成的长度
  // rest : 一共还有几条边没有解决
  // 返回 : 能否用光所有火柴去解决剩下的所有边
  // 因为调用子过程之前，一定保证每条边累加起来都不超过limit
  // 所以status是决定cur和rest的，关键可变参数只有status
  bool f(vector<int>& nums, int limit, int status, int cur, int rest, vector<int>& dp)
  {
    if (rest == 0)
    {
      return status == 0;
    }
    if (dp[status] != 0)
    {
      return dp[status] == 1;
    }
    bool ans = false;
    for (int i = 0; i < nums.size(); i++)
    {
      // 考察每一根火柴，只能使用状态为1的火柴
      if ((status & (1 << i)) != 0 && cur + nums[i] <= limit)
      {
        if (cur + nums[i] == limit)
        {
          ans = f(nums, limit, status ^ (1 << i), 0, rest - 1, dp);
        }
        else
        {
          ans = f(nums, limit, status ^ (1 << i), cur + nums[i], rest, dp);
        }
        if (ans)
        {
          break;
        }
      }
    }
    dp[status] = ans ? 1 : -1;
    return ans;
  }

 public:
  bool makesquare(vector<int>& matchsticks)
  {
    int sum = 0;
    for (int num : matchsticks)
    {
      sum += num;
    }
    if (sum % 4 != 0)
    {
      return false;
    }
    int n = matchsticks.size();
    vector<int> dp(1 << n);
    return f(matchsticks, sum / 4, (1 << n) - 1, 0, 4, dp);
  }
};
