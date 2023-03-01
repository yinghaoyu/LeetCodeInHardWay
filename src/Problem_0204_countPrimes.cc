#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  //埃式筛法
  int countPrimes(int n)
  {
    if (n < 3)
    {
      return 0;
    }
    // f[i] true表示被筛选过
    vector<bool> f(n);
    // 首先排除一半的数，因为偶数一定不是质数
    int count = n / 2;
    // 筛选所有的奇数
    for (int i = 3; i * i < n; i += 2)
    {
      if (f[i])
      {
        continue;
      }
      // 筛选所有能被i整除的奇数
      // 为什么 j 从 i*i 开始 ？
      // 首先，(i-1)*i 是偶数(因为i-1是偶数)，前面已经排除
      // 其次，(i-2)*i 在枚举上一个数i-2时， (i-2)*(i-2)、(i-2)*i、(i-2)*(3i - 2) ... 已经枚举过了
      // 同理，(i-3)*i，(i-4)*i，... 都在前面枚举过
      for (int j = i * i; j < n; j += 2 * i)
      {
        if (!f[j])
        {
          count--;
          f[j] = true;
        }
      }
    }
    return count;
  }
};

void testCountPrimes()
{
  Solution s;
  EXPECT_EQ_INT(0, s.countPrimes(1));
  EXPECT_EQ_INT(4, s.countPrimes(10));
  EXPECT_EQ_INT(0, s.countPrimes(0));
  EXPECT_SUMMARY;
}

int main()
{
  testCountPrimes();
  return 0;
}
