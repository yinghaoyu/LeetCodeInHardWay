#include <vector>

using namespace std;

// TODO: figure it out
class Solution
{
 private:
  static constexpr int MOD = 1000000007;

 public:
  int totalStrength(vector<int>& strength)
  {
    int n = strength.size();
    int pre = strength[0] % MOD;
    vector<int> sumsum(n);
    sumsum[0] = pre;
    for (int i = 1; i < n; i++)
    {
      pre = (pre + strength[i]) % MOD;
      sumsum[i] = (sumsum[i - 1] + pre) % MOD;
    }
    vector<int> stack(n);
    int size = 0;
    int ans = 0;
    for (int i = 0; i < n; i++)
    {
      while (size > 0 && strength[stack[size - 1]] >= strength[i])
      {
        int m = stack[--size];
        int l = size > 0 ? stack[size - 1] : -1;
        ans = (ans + sum(strength, sumsum, l, m, i)) % MOD;
      }
      stack[size++] = i;
    }
    while (size > 0)
    {
      int m = stack[--size];
      int l = size > 0 ? stack[size - 1] : -1;
      ans = (ans + sum(strength, sumsum, l, m, n)) % MOD;
    }
    return ans;
  }

  int sum(vector<int>& arr, vector<int>& sumsum, int l, int m, int r)
  {
    long left = sumsum[r - 1];
    if (m - 1 >= 0)
    {
      left = (left - sumsum[m - 1] + MOD) % MOD;
    }
    left = (left * (m - l)) % MOD;
    long right = 0;
    if (m - 1 >= 0)
    {
      right = (right + sumsum[m - 1]) % MOD;
    }
    if (l - 1 >= 0)
    {
      right = (right - sumsum[l - 1] + MOD) % MOD;
    }
    right = (right * (r - m)) % MOD;
    return (int) (((left - right + MOD) % MOD * arr[m]) % MOD);
  }
};
