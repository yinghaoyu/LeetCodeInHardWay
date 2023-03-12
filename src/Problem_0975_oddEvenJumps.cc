#include <cmath>
#include <iostream>
#include <map>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int oddEvenJumps(vector<int> &arr)
  {
    int N = arr.size();
    // odd[i] : 如果来到i位置，处在奇数规则下，该去哪个位置！
    vector<int> odd(N);
    // even[i] : 如果来到i位置，处在偶数规则下，该去哪个位置！
    vector<int> even(N);
    // key : 值！
    // value : 这个值出现的最左下标！
    map<int, int> map;
    for (int i = N - 1; i >= 0; i--)
    {
      // lower_bound的含义是找到第一个 >= arr[i]的数
      // 奇数跳，找到下一步索引，第一个 >= arr[i]的数
      auto ito = map.lower_bound(arr[i]);
      odd[i] = (ito == map.end() ? -1 : ito->second);
      // upper_bound的含义是找到第一个 > arr[i]的数
      auto ite = map.upper_bound(arr[i]);
      // 偶数跳，找到下一步索引，第一个 <= arr[i]的数
      if (ite == map.begin())
      {
        even[i] = -1;
      }
      else
      {
        --ite;
        even[i] = ite->second;
      }
      // 从右往左，这样才能符合跳到最小的索引上
      map[arr[i]] = i;
    }
    // dp[i][0] : 如果来到i位置，并且是奇数规则，能不能去往数组最终位置
    // dp[i][1] : 如果来到i位置，并且是偶数规则，能不能去往数组最终位置
    vector<vector<bool>> dp(N, vector<bool>(2));
    dp[N - 1][0] = true;
    dp[N - 1][1] = true;
    // n-1位置一定良好的！ans = 1
    int ans = 1;
    for (int i = N - 2; i >= 0; i--)
    {
      dp[i][0] = odd[i] != -1 && dp[odd[i]][1];
      dp[i][1] = even[i] != -1 && dp[even[i]][0];
      // 为什么这里只需要计算dp[i][0]？
      // 以该点为起点能跳到终点(也就是第1次开始跳，1为奇数）
      ans += dp[i][0] ? 1 : 0;
    }
    return ans;
  }
};

void testOddEvenJumps()
{
  Solution s;
  vector<int> n1 = {10, 13, 12, 14, 15};
  vector<int> n2 = {2, 3, 1, 1, 4};
  vector<int> n3 = {5, 1, 3, 4, 2};
  EXPECT_EQ_INT(2, s.oddEvenJumps(n1));
  EXPECT_EQ_INT(3, s.oddEvenJumps(n2));
  EXPECT_EQ_INT(3, s.oddEvenJumps(n3));
  EXPECT_SUMMARY;
}

int main()
{
  testOddEvenJumps();
  return 0;
}
