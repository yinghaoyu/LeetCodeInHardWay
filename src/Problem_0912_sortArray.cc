#include <algorithm>
#include <vector>

#include "UnitTest.h"

using namespace std;

// https://www.bilibili.com/video/BV1Lh4y1c7Aw
class Solution
{
 public:
  // 可以设置进制，不一定10进制，随你设置
  int BASE = 10;

  int MAXN = 50001;

  vector<int> help;

  vector<int> cnts;

  // 返回number在BASE进制下有几位
  int bits(int number)
  {
    int ans = 0;
    while (number > 0)
    {
      ans++;
      number /= BASE;
    }
    return ans;
  }

  // 基数排序核心代码
  // arr内要保证没有负数
  // n是arr的长度
  // bits是arr中最大值在BASE进制下有几位
  void radixSort(vector<int>& arr, int n, int bits)
  {
    // 理解的时候可以假设BASE = 10
    for (int offset = 1; bits > 0; offset *= BASE, bits--)
    {
      std::fill(cnts.begin(), cnts.end(), 0);
      for (int i = 0; i < n; i++)
      {
        // 数字提取某一位的技巧
        cnts[(arr[i] / offset) % BASE]++;
      }
      // 处理成前缀次数累加的形式
      for (int i = 1; i < BASE; i++)
      {
        cnts[i] = cnts[i] + cnts[i - 1];
      }
      for (int i = n - 1; i >= 0; i--)
      {
        // 前缀数量分区的技巧
        // 数字提取某一位的技巧
        help[--cnts[(arr[i] / offset) % BASE]] = arr[i];
      }
      for (int i = 0; i < n; i++)
      {
        arr[i] = help[i];
      }
    }
  }

  vector<int> sortArray(vector<int>& arr)
  {
    if (arr.size() > 1)
    {
      help = vector<int>(MAXN, 0);
      cnts = vector<int>(MAXN, 0);
      // 如果会溢出，那么要改用long类型数组来排序
      int n = arr.size();
      // 找到数组中的最小值
      int min = arr[0];
      for (int i = 1; i < n; i++)
      {
        min = std::min(min, arr[i]);
      }
      int max = 0;
      for (int i = 0; i < n; i++)
      {
        // 数组中的每个数字，减去数组中的最小值，就把arr转成了非负数组
        arr[i] -= min;
        // 记录数组中的最大值
        max = std::max(max, arr[i]);
      }
      // 根据最大值在BASE进制下的位数，决定基数排序做多少轮
      radixSort(arr, n, bits(max));
      // 数组中所有数都减去了最小值，所以最后不要忘了还原
      for (int i = 0; i < n; i++)
      {
        arr[i] += min;
      }
    }
    return arr;
  }
};

void test()
{
  Solution s;
  vector<int> n1 = {5, 2, 3, 1};
  vector<int> n2 = {5, 1, 1, 2, 0, 0};

  vector<int> o1 = {1, 2, 3, 5};
  vector<int> o2 = {0, 0, 1, 1, 2, 5};
  EXPECT_TRUE(o1 == s.sortArray(n1));
  EXPECT_TRUE(o2 == s.sortArray(n2));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
