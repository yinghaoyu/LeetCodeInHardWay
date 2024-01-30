#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

const int MAXN = 501;
const int MAXX = 100001;

// 对于"一定要买的商品"，直接买！
// 只把"需要考虑的商品"放入cost、val数组
int cost[MAXN];
long long val[MAXN];
long long dp[MAXX];

int n, m, x;

long long compute()
{
  memset(dp, 0, sizeof(dp));
  // dp[j]的含义为，在总预算j的情况下，买到游戏的最大快乐值
  for (int i = 1; i <= m; i++)
  {
    for (int j = x; j >= cost[i]; j--)
    {
      dp[j] = std::max(dp[j], dp[j - cost[i]] + val[i]);
    }
  }
  return dp[x];
}

int main()
{
  // n个游戏，总预算x
  while (cin >> n >> x)
  {
    m = 1;
    long long ans = 0;
    long long happy = 0;
    for (int i = 1, pre, cur, well; i <= n; i++)
    {
      // 原价 现价 快乐值
      cin >> pre >> cur >> happy;
      well = pre - cur - cur;
      // 如下是一件"一定要买的商品"
      // 预算 = 100，商品原价 = 10，打折后 = 3
      // 那么好处(well) = (10 - 3) - 3 = 4
      // 所以，可以认为这件商品把预算增加到了104！一定要买！
      // 如下是一件"需要考虑的商品"
      // 预算 = 104，商品原价 = 10，打折后 = 8
      // 那么好处(well) = (10 - 8) - 8 = -6
      // 所以，可以认为这件商品就花掉6元！
      // 也就是说以后花的不是打折后的值，是"坏处"
      if (well >= 0)
      {
        x += well;
        ans += happy;
      }
      else
      {
        cost[m] = -well;
        val[m++] = happy;
      }
    }
    ans += compute();
    cout << ans << endl;
  }
  return 0;
}
