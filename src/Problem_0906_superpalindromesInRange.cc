#include <iostream>
#include <string>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  // L ... R    "123213213" ~ "31283712710381299823"
  int superpalindromesInRange(string left, string right)
  {
    long l = std::stol(left);
    long r = std::stol(right);
    // 限制是根据开方的范围
    // 400 ~ 1 0000 00000 r
    //     ~ 1 0000 r的开方
    long limit = (long) std::sqrt(r);
    int cnt = 0;
    long seed = 1;
    long enlarge = 0;
    do
    {
      // seed : 开方的一半！左半边
      // seed == 1
      // 1)  11
      // 2)  1
      // seed = 123
      // 1) 123321 -> 开方的可能性
      // 2) 12321
      // 10000 是开方的边界
      // seed = 99
      // 1) 99 99
      // 2) 999
      // seed = 100
      // 100001
      // 10001
      // seed 101 .... 不需要了！
      // enlarge2 加工出偶数长度的开方结果
      // 123 -> 123321
      // 123321 的平方，在不在l ~ r上，且是不是回文！
      enlarge = enlarge2(seed);
      if (isValid(enlarge * enlarge, l, r))
      {
        cnt++;
      }
      // enlarge1 加工出奇数长度的开方结果
      enlarge = enlarge1(seed);
      if (isValid(enlarge * enlarge, l, r))
      {
        cnt++;
      }
      // 1 11 1   2 22 2  3 33 3  .... 11 1111 111 12 1221 121 ...
      seed++;
    } while (enlarge < limit);
    return cnt;
  }

  // 123 -> 12321
  long enlarge1(long seed)
  {
    long ans = seed;
    seed /= 10;
    while (seed != 0)
    {
      ans = ans * 10 + seed % 10;
      seed /= 10;
    }
    return ans;
  }

  // 123 -> 123321
  long enlarge2(long seed)
  {
    long ans = seed;
    while (seed != 0)
    {
      ans = ans * 10 + seed % 10;
      seed /= 10;
    }
    return ans;
  }

  bool isValid(long ans, long l, long r) { return isPalindrome(ans) && ans >= l && ans <= r; }

  // 对一个数，不用转成字符串，就判断它是回文数
  // n = 1234321
  // 先找到一个数help，使得刚好和n相同位数
  // 初始时help = 1，依次乘以10
  //    n = 1234321
  // help = 1000000
  // 最高位为 n / help = 1
  // 最低位为 n % 10   = 1
  // 比较后，提除最高位操作n % help，剔除最低为操作 n / 10
  // 然后把 help / 100
  bool isPalindrome(long n)
  {
    // n =    3721837
    // help = 1000000
    long help = 1;
    // 这样写不会溢出！
    while (n / help >= 10)
    {
      help *= 10;
    }
    // n =    72183
    // help = 10000
    while (n >= 10)
    {
      if (n / help != n % 10)
      {
        return false;
      }
      n = (n % help) / 10;
      help /= 100;
    }
    return true;
  }
};

void testSuperpalindromesInRange()
{
  Solution s;
  EXPECT_EQ_INT(4, s.superpalindromesInRange("4", "1000"));
  EXPECT_EQ_INT(1, s.superpalindromesInRange("1", "2"));
  EXPECT_SUMMARY;
}

int main()
{
  testSuperpalindromesInRange();
  return 0;
}
