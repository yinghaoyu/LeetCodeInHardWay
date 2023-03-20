#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  // 卡特兰数组
  int numTrees(int n)
  {
    if (n < 0)
    {
      return 0;
    }
    if (n < 2)
    {
      return 1;
    }
    long a = 1;
    long b = 1;
    for (int i = 1, j = n + 1; i <= n; i++,j++)
    {
      a *= i;
      b *= j;
      long g = gcd(a, b);
      a /= g;
      b /= g;
    }
    return (b / a) / (n + 1);
  }

  long gcd(long m, long n) { return n == 0 ? m : gcd(n, m % n); }

  // 假设n个节点存在二叉排序树的个数是G(n)，令f(i)为以i为根的二叉搜索树的个数
  // 即有:G(n) = f(1) + f(2) + f(3) + f(4) + ... + f(n)
  // n为根节点，当i为根节点时，其左子树节点个数为[1,2,3,...,i-1]，
  // 右子树节点个数为[i+1,i+2,...n]，所以当i为根节点时，其左子树节点个数为i-1个，
  // 右子树节点为n-i，即f(i) = G(i-1)*G(n-i),
  // 上面两式可得:G(n) = G(0)*G(n-1)+G(1)*(n-2)+...+G(n-1)*G(0)
  int dp(int n)
  {
    vector<int> dp(n + 1);
    // 0个节点二叉树是空树，也算二叉排序树
    dp[0] = 1;
    // 1个节点二叉树只包含根节点
    dp[1] = 1;
    for (int i = 2; i < n + 1; i++)
    {
      for (int j = 1; j <= i; j++)
      {
        // 以j为根节点的树，
        // 左边 j - 1个节点，右边 i - (j + 1) + 1 = i - j个节点
        dp[i] += dp[j - 1] * dp[i - j];
      }
    }
    return dp[n];
  }
};

void testNumTrees()
{
  Solution s;
  EXPECT_EQ_INT(5, s.numTrees(3));
  EXPECT_EQ_INT(1, s.numTrees(1));
  EXPECT_EQ_INT(5, s.dp(3));
  EXPECT_EQ_INT(1, s.dp(1));
  EXPECT_SUMMARY;
}

int main()
{
  testNumTrees();
  return 0;
}
