#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  // 贪心
  vector<long long> maximumEvenSplit(long long finalSum)
  {
    vector<long long> ans;
    if (finalSum & 1)
    {
      return ans;
    }
    // 拆分成尽可能多的偶数，我们应该尽可能拆份成最小的若干个偶数。
    // 从最小的偶整数 2 开始依次尝试拆分
    for (int i = 2; i <= finalSum; i += 2)
    {
      ans.push_back(i);
      finalSum -= i;
    }
    // 如果此时拆分后剩余的 finalSum 大于零，
    // 则将这个数值加到最大的偶整数上，从而保证所有的数互不相同
    ans.back() += finalSum;
    return ans;
  }
};

void test()
{
  Solution s;
  vector<long long> o1 = {2, 4, 6};
  vector<long long> o2 = {};
  vector<long long> o3 = {2, 4, 6, 16};
  EXPECT_TRUE(o1 == s.maximumEvenSplit(12));
  EXPECT_TRUE(o2 == s.maximumEvenSplit(7));
  EXPECT_TRUE(o3 == s.maximumEvenSplit(28));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
