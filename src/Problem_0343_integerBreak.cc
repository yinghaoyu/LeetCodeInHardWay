class Solution
{
 private:
  static const int mod = 1e9 + 7;

  long fastPower(long x, int n)
  {
    long ans = 1;
    while (n > 0)
    {
      if (n & 1)
      {
        ans = (ans * x) % mod;
      }
      x = (x * x) % mod;
      n >>= 1;
    }
    return ans;
  }

 public:
  int integerBreak(int n)
  {
    if (n == 2)
    {
      return 1;
    }
    if (n == 3)
    {
      return 2;
    }
    // n = 4  -> 2 * 2
    // n = 5  -> 3 * 2
    // n = 6  -> 3 * 3
    // n = 7  -> 3 * 2 * 2
    // n = 8  -> 3 * 3 * 2
    // n = 9  -> 3 * 3 * 3
    // n = 10 -> 3 * 3 * 2 * 2
    // n = 11 -> 3 * 3 * 3 * 2
    // n = 12 -> 3 * 3 * 3 * 3
    int tail = n % 3 == 0 ? 1 : (n % 3 == 1 ? 4 : 2);
    int power = (tail == 1 ? n : n - tail) / 3;
    return fastPower(3, power) * tail % mod;
  }
};
