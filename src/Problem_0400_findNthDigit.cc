#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int findNthDigit(int n)
  {
    int low = 1;
    int high = 9;
    while (low < high)
    {
      int mid = (high - low) / 2 + low;
      if (totalDigits(mid) < n)
      {
        low = mid + 1;
      }
      else
      {
        high = mid;
      }
    }
    // 二分找到第 n 位所对应的数的长度
    int d = low;
    // 前面有多少个数
    int pre = totalDigits(d - 1);
    // 第 n 位在所有 d 位数的 位 序列中下标是 idx (0-indexed)
    int idx = n - pre - 1;
    // start 是 长度为 d 的第一个数
    int start = pow(10, d - 1);
    // 得到所在的数
    int num = start + idx / d; 
    // 在数内的 idx
    int digitsIdx = idx % d;
    // 得到具体的位
    int digit = (num / static_cast<int>(pow(10, d - digitsIdx - 1))) % 10;
    return digit;
  }

  // 计算长度为 [1,len] 之间所有数的位数之和
  // 例如，长度为 1 有 1 2 3 ... 9 总共 9 个数，每个数占 1 位， 总共占 1 * 9 位
  //       长度为 2 有 10 11 12 ... 99 总共 90个数，每个数占 2 位，总共占 2 * 90 位
  int totalDigits(int len)
  {
    int sum = 0;
    int curLen = 1;
    int curCount = 9;
    while (curLen <= len)
    {
      sum += curLen * curCount;
      curLen++;
      curCount *= 10;
    }
    return sum;
  }
};

void test()
{
  Solution s;
  EXPECT_EQ_INT(3, s.findNthDigit(3));
  EXPECT_EQ_INT(0, s.findNthDigit(11));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
