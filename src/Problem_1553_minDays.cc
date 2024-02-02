#include <unordered_map>
#include <vector>

using namespace std;

class Solution
{
 private:
  unordered_map<int, int> dp;

 public:
  int minDays(int n)
  {
    if (n <= 1)
    {
      return n;
    }
    if (dp.count(n))
    {
      return dp[n];
    }
    // 1) 吃掉一个橘子
    // 2) 如果n能被2整除，吃掉一半的橘子，剩下一半
    // 3) 如果n能被3正数，吃掉三分之二的橘子，剩下三分之一
    // 因为方法2）和3），是按比例吃橘子，所以必然会非常快
    // 所以，决策如下：
    // 可能性1：为了使用2）方法，先把橘子吃成2的整数倍，然后直接干掉一半，剩下的n/2调用递归
    // 即，n % 2 + 1 + minDays(n/2)
    // 可能性2：为了使用3）方法，先把橘子吃成3的整数倍，然后直接干掉三分之二，剩下的n/3调用递归
    // 即，n % 3 + 1 + minDays(n/3)
    // 至于方法1)，完全是为了这两种可能性服务的，因为能按比例吃，肯定比一个一个吃快(显而易见的贪心)
    int ans = std::min(n % 2 + 1 + minDays(n / 2), n % 3 + 1 + minDays(n / 3));
    dp[n] = ans;
    return ans;
  }
};
