#include <queue>
#include <vector>

using namespace std;

class Solution
{
 public:
  // dp，时间复杂度O(n^2)
  int minJump1(vector<int>& jump)
  {
    int n = jump.size();
    // dp[i]表示从 i 这个位置跳出去最少需要多少步
    vector<int> dp(n);
    dp[n - 1] = 1;
    for (int i = n - 2; i >= 0; i--)
    {
      // 如果 i + jump[i] >= n 说明可以直接跳出去更新 dp[i]
      // 否则考虑向右跳到 i + jump[i] 然后再跳出去
      // +1 表示 i 跳到 i + jump[i] 需要 1 步
      dp[i] = i + jump[i] >= n ? 1 : dp[i + jump[i]] + 1;
      // 一旦 dp[i] 更新了，那么对于所有的 j (i < j < n)，都多了一种选择，就是先往左挑到 i
      // 然后再往右跳。也就是说 dp[i] 一旦更新，对于右边的 dp[j] 可以往左跳，也可以往右跳，两者取小
      for (int j = i + 1; j < n && dp[j] >= dp[i] + 1; j++)
      {
        // 把条件放入循环内会超时
        // if (dp[i] + 1 < dp[j])
        //{
        //  dp[j] = dp[i] + 1;
        //}
        // 注意这点
        // 如果遍历到某dp[j] < dp[i]+1 就不需要向右遍历了，
        // 因为j到n的值会被当前遍历到的dp[j]更新而不是dp[i]+1
        dp[j] = dp[i] + 1;
      }
    }
    return dp[0];
  }

  // bfs
  int minJump2(vector<int>& jump)
  {
    int n = jump.size();
    // 当前位置 idx，按动次数 d
    queue<std::pair<int, int>> q;
    // 初始值：编号为 0 的弹簧  按动次数 为0
    q.emplace(0, 0);
    // 是否被访问
    vector<bool> seen(n, false);
    seen[0] = true;
    int preidx = 1;
    while (!q.empty())
    {
      auto [idx, d] = q.front();
      q.pop();
      // 向右扩展
      int next = idx + jump[idx];
      if (next > n - 1)
      {
        return d + 1;
      }
      if (!seen[next])
      {
        seen[next] = true;
        q.emplace(next, d + 1);
      }
      // 向左扩展：O(n^2)
      // 某一个位置及其之前所有位置都已经被扩展过，那么一定是最短路，不需要再次被扩展
      // preidx：记录某个位置及其之前位置均已被扩展，每次更新preidx 即可
      // for(int i = 0; i < idx; i++) {
      //     if(!seen[i]) {
      //         seen[i] = true;
      //         q.emplace(i, d + 1);
      //     }
      // }

      while (preidx < idx)
      {
        // 最多只会遍历一遍全部位置 ：O(n)
        if (!seen[preidx])
        {
          seen[preidx] = true;
          q.emplace(preidx, d + 1);
        }
        preidx++;
      }
    }
    // 遍历完整个队列，还未返回，说明无法到达
    return -1;
  }
};
