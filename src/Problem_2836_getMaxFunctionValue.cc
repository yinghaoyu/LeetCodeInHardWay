#include <vector>

using namespace std;

// TODO: fix it.
class Solution
{
 public:
  static const int MAXN = 100001;

  static const int LIMIT = 34;

  int power;

  // 给定k的二进制位上有几个1
  int m;

  // 收集k的二进制上哪些位有1
  vector<int> kbits = vector<int>(LIMIT);

  vector<vector<int>> stjump = vector<vector<int>>(MAXN, vector<int>(LIMIT));

  vector<vector<long long>> stsum = vector<vector<long long>>(MAXN, vector<long long>(LIMIT));

  void build(long k)
  {
    power = 0;
    while ((1L << power) <= (k >> 1))
    {
      power++;
    }
    m = 0;
    for (int p = power; p >= 0; p--)
    {
      if ((1L << p) <= k)
      {
        kbits[m++] = p;
        k -= 1L << p;
      }
    }
  }

  // 该方法是树上倍增的解法
  // 打败比例很一般但是非常好想
  long getMaxFunctionValue(vector<int>& receiver, long k)
  {
    build(k);
    int n = receiver.size();
    for (int i = 0; i < n; i++)
    {
      stjump[i][0] = receiver.at(i);
      stsum[i][0] = receiver.at(i);
    }
    for (int p = 1; p <= power; p++)
    {
      for (int i = 0; i < n; i++)
      {
        stjump[i][p] = stjump[stjump[i][p - 1]][p - 1];
        stsum[i][p] = stsum[i][p - 1] + stsum[stjump[i][p - 1]][p - 1];
      }
    }
    long sum, ans = 0;
    for (int i = 0, cur; i < n; i++)
    {
      cur = i;
      sum = i;
      for (int j = 0; j < m; j++)
      {
        sum += stsum[cur][kbits[j]];
        cur = stjump[cur][kbits[j]];
      }
      ans = std::max(ans, sum);
    }
    return ans;
  }
};
