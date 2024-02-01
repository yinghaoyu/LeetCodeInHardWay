#include <algorithm>
#include <iostream>
#include <tuple>
#include <vector>
#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  // job[0...i]范围上，找到结束时间 <= start，最右的下标
  int nearLeftIndex(vector<vector<int>> jobs, int i, int j)
  {
    int L = i;
    int R = j;
    int index = -1;
    while (L <= R)
    {
      int M = L + (R - L) / 2;
      if (jobs[M][1] <= jobs[j][0])
      {
        // 当job[mid]结束时间 <= job[j]的开始时间
        // 左窗口一直右移
        index = M;
        L = M + 1;
      }
      else
      {
        R = M - 1;
      }
    }
    return index + 1;  // +1 是因为dp的下标需要增加1
  }

  int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit)
  {
    int n = startTime.size();
    vector<vector<int>> jobs(n);
    for (int i = 0; i < n; i++)
    {
      jobs[i] = {startTime[i], endTime[i], profit[i]};
    }
    // 将job按照结束时间排序
    sort(jobs.begin(), jobs.end(),
         [](const vector<int>& job1, const vector<int>& job2) -> bool
         { return job1[1] < job2[1]; });
    vector<int> dp(n + 1);
    // dp[i]表示前i份工作可以获得的最大报酬
    for (int i = 1; i <= n; i++)
    {
      int k = nearLeftIndex(jobs, 0, i - 1);
      dp[i] = max(dp[i - 1], dp[k] + jobs[i - 1][2]);
    }
    return dp[n];
  }
};

void testJobScheduling()
{
  Solution s;
  vector<int> s1 = {1, 2, 3, 3};
  vector<int> e1 = {3, 4, 5, 6};
  vector<int> p1 = {50, 10, 40, 70};

  vector<int> s2 = {1, 2, 3, 4, 6};
  vector<int> e2 = {3, 5, 10, 6, 9};
  vector<int> p2 = {20, 20, 100, 70, 60};

  vector<int> s3 = {1, 1, 1};
  vector<int> e3 = {2, 3, 4};
  vector<int> p3 = {5, 6, 4};

  vector<int> s4 = {6, 15, 7, 11, 1, 3, 16, 2};
  vector<int> e4 = {19, 18, 19, 16, 10, 8, 19, 8};
  vector<int> p4 = {2, 9, 1, 19, 5, 7, 3, 19};

  EXPECT_EQ_INT(120, s.jobScheduling(s1, e1, p1));
  EXPECT_EQ_INT(150, s.jobScheduling(s2, e2, p2));
  EXPECT_EQ_INT(6, s.jobScheduling(s3, e3, p3));
  EXPECT_EQ_INT(41, s.jobScheduling(s4, e4, p4));
  EXPECT_SUMMARY;
}

int main()
{
  testJobScheduling();
  return 0;
}
