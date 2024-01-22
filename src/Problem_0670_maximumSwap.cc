#include <algorithm>
#include <iostream>
#include <string>

#include "UnitTest.h"

using namespace std;

// https://leetcode.cn/problems/maximum-swap/solutions/2614470/yi-ci-bian-li-jian-ji-xie-fa-pythonjavac-c9b1/?envType=daily-question&envId=2024-01-22
// 举例说明，假设 num=9952767。为了得到最大值，我们来看看怎么贪心：
// 1. 从左往右考察 num 的每个数字，如果一个数字右边没有比它大的，那么肯定无需交换它。
// 比如这里的 9，无论它和谁交换都不能让 num 更大。
// 2. 反之，如果一个数字右边有比它大的数，那么肯定要交换它，
// 比如这里的 5，右边有比它大的 7 和 6，为了让 num 尽量大，和 7 交换最优。
// 3. 但是，如果有多个 7 呢？我们应该和哪个 7 交换呢？
//    * 如果和第一个 7 交换，我们得到的是 9972567。
//    * 如果和第二个 7 交换，我们得到的是 9972765。
//    * 和最后一个 7 交换是最优的。
// 设 num 的十进制字符串为 s。算法如下：

// 1. 倒序遍历 s，同时维护最大数的下标
// maxIdx。它只在遇到更大的数字才更新，遇到相同数字不会更新，从而满足上面讨论的「最后一个」。
// 2. 如果发现 s[i] < s[maxIdx]，满足交换要求，我们先把这两个下标保存在变量 p 和 q 中。注：p
// 在遍历前的初始值为 −1。
// 3. 继续向左遍历，如果又遇到 s[i] < s[maxIdx]，就更新 p=i, q=maxIdx，因为 s[i]
// 越靠左越好，我们要交换的是从左到右第一个右边有比它大的数字。
// 4. 遍历结束，如果无需交换，即 p=−1，那么直接返回 num。否则交换 s[p] 和 s[q]，然后把 s
// 转换成数字返回。

class Solution
{
 public:
  // 贪心，时间复杂度log10(num)
  int maximumSwap(int num)
  {
    string str = std::to_string(num);
    int n = str.length();
    int maxIdx = n - 1;
    int idx1 = -1, idx2 = -1;
    for (int i = n - 1; i >= 0; i--)
    {
      // 从低位往高位找最大值
      if (str[i] > str[maxIdx])
      {
        maxIdx = i;
      }
      else if (str[i] < str[maxIdx])
      {
        // 最大值往高位交换能获得最优
        idx1 = i;
        idx2 = maxIdx;
      }
    }
    if (idx1 >= 0)
    {
      std::swap(str[idx1], str[idx2]);
      return stoi(str);
    }
    else
    {
      return num;
    }
  }
};

void testMaximumSwap()
{
  Solution s;
  EXPECT_EQ_INT(-3979, s.maximumSwap(-9973));
  EXPECT_EQ_INT(7236, s.maximumSwap(2736));
  EXPECT_EQ_INT(9973, s.maximumSwap(9973));
  EXPECT_SUMMARY;
}

int main()
{
  testMaximumSwap();
  return 0;
}
