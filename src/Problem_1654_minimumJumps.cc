#include <algorithm>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int process(vector<bool> &seen, int a, int b, int x, int cur, int step, bool lastBack)
  {
    if (cur == x)
    {
      return step;
    }
    if (cur < 0 || cur >= seen.size() || seen[cur])
    {
      // 注意这里判断 seen[cur] 是错误的！！！
      // 因为某一步走到 cur，有可能是后退走到的，也有可能是前进走到的，
      // 如果是第一步没找到，那么第二步就再也没机会了
      // 只判断 seen[cur] 一次会漏掉!!!
      return INT32_MAX;
    }
    seen[cur] = true;
    int ans = INT32_MAX;
    if (cur + a < seen.size() && !seen[cur + a])
    {
      ans = process(seen, a, b, x, cur + a, step + 1, false);
    }
    if (!lastBack && cur - b >= 0 && !seen[cur - b])
    {
      ans = std::min(ans, process(seen, a, b, x, cur - b, step + 1, true));
    }
    return ans;
  }

  // 递归错误解
  int minimumJumps1(vector<int> &forbidden, int a, int b, int x)
  {
    int f = *max_element(forbidden.begin(), forbidden.end());
    // 最远距离
    int bound = std::max(f + a + b, x + b);
    vector<bool> seen(bound + 1);
    for (auto &x : forbidden)
    {
      seen[x] = true;
    }
    int ans = process(seen, a, b, x, 0, 0, false);
    return ans == INT32_MAX ? -1 : ans;
  }

  // TODO: figure it out
  int minimumJumps2(vector<int> &forbidden, int a, int b, int x)
  {
    int f = *max_element(forbidden.begin(), forbidden.end());
    // 最远距离
    int bound = std::max(f + a + b, x + b);
    vector<bool> visited(bound + 1);
    for (auto &x : forbidden)
    {
      visited[x] = true;
    }
    // dist[i][0] 上一次前跳，dist[i][1]上一次后跳
    vector<vector<int>> dist(bound + 1, vector<int>(2, INT32_MAX >> 1));
    dist[0][0] = 0;
    queue<std::pair<int, int>> q;
    q.push({0, 0});
    while (!q.empty())
    {
      auto [i, pre] = q.front();
      q.pop();
      if (i == x)
      {
        return dist[i][pre];
      }
      if (pre == 0 && i - b >= 0 && !visited[i - b] && dist[i][pre] + 1 < dist[i - b][1])
      {
        // 可以后跳，pre == 0 保证上次一定是前跳
        // 并且上一次前跳 < 当前，更新当前
        dist[i - b][1] = dist[i][pre] + 1;
        q.emplace(i - b, 1);
      }
      if (i + a <= bound && !visited[i + a] && dist[i][pre] + 1 < dist[i + a][0])
      {
        // 可以前跳，
        // 并且上一次跳 < 当前，更新当前
        dist[i + a][0] = dist[i][pre] + 1;
        q.emplace(i + a, 0);
      }
    }
    return -1;
  }
};

void test()
{
  Solution s;
  vector<int> f1 = {14, 4, 18, 1, 15};
  vector<int> f2 = {8, 3, 16, 6, 12, 20};
  vector<int> f3 = {1, 6, 2, 14, 5, 17, 4};
  vector<int> f4 = {128, 178, 147, 165, 63, 11, 150, 20, 158, 144, 136};
  vector<int> f5 = {162, 118, 178, 152, 167, 100, 40,  74, 199, 186, 26,  73, 200, 127, 30,  124, 193, 84,  184, 36,  103, 149, 153, 9,   54, 154, 133,
                    95,  45,  198, 79,  157, 64,  122, 59, 71,  48,  177, 82, 35,  14,  176, 16,  108, 111, 6,   168, 31,  134, 164, 136, 72, 98};
  EXPECT_EQ_INT(3, s.minimumJumps1(f1, 3, 15, 9));
  EXPECT_EQ_INT(-1, s.minimumJumps1(f2, 15, 13, 11));
  EXPECT_EQ_INT(2, s.minimumJumps1(f3, 16, 9, 7));
  EXPECT_EQ_INT(6, s.minimumJumps1(f4, 61, 170, 135));
  EXPECT_EQ_INT(121, s.minimumJumps1(f5, 29, 98, 80));
  EXPECT_EQ_INT(3, s.minimumJumps2(f1, 3, 15, 9));
  EXPECT_EQ_INT(-1, s.minimumJumps2(f2, 15, 13, 11));
  EXPECT_EQ_INT(2, s.minimumJumps2(f3, 16, 9, 7));
  EXPECT_EQ_INT(6, s.minimumJumps2(f4, 61, 170, 135));
  EXPECT_EQ_INT(121, s.minimumJumps2(f5, 29, 98, 80));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
