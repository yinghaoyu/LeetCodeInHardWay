#include <string>
#include <vector>

using namespace std;

//@sa https://www.bilibili.com/video/BV1pN41157uX/
class Solution
{
 public:
  static const int MAXN = 101;

  static const int MAXC = 26;

  // 字符转成int
  vector<int> ring = vector<int>(MAXN);

  vector<int> key = vector<int>(MAXN);

  // 每种字符多少个
  vector<int> size = vector<int>(MAXC);

  vector<vector<int>> where = vector<vector<int>>(MAXC, vector<int>(MAXN));

  vector<vector<int>> dp = vector<vector<int>>(MAXN, vector<int>(MAXN));

  int n, m;

  void build(string& r, string& k)
  {
    for (int i = 0; i < MAXC; i++)
    {
      size[i] = 0;
    }
    n = r.length();
    m = k.length();
    for (int i = 0, v; i < n; i++)
    {
      v = r[i] - 'a';
      where[v][size[v]++] = i;
      ring[i] = v;
    }
    for (int i = 0; i < m; i++)
    {
      key[i] = k[i] - 'a';
    }
    for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < m; j++)
      {
        dp[i][j] = -1;
      }
    }
  }

  int findRotateSteps(string r, string k)
  {
    build(r, k);
    return f(0, 0);
  }

  // 指针当前指着轮盘i位置的字符，要搞定key[j....]所有字符，最小代价返回
  int f(int i, int j)
  {
    if (j == m)
    {
      // key长度是m
      // 都搞定
      return 0;
    }
    if (dp[i][j] != -1)
    {
      return dp[i][j];
    }
    int ans;
    if (ring[i] == key[j])
    {
      // ring b
      //      i
      // key  b
      //      j
      ans = 1 + f(i, j + 1);
    }
    else
    {
      // 轮盘处在i位置，ring[i] != key[j]
      // jump1 : 顺时针找到最近的key[j]字符在轮盘的什么位置
      // distance1 : 从i顺时针走向jump1有多远
      int jump1 = clock(i, key[j]);
      int distance1 = (jump1 > i ? (jump1 - i) : (n - i + jump1));
      // jump2 : 逆时针找到最近的key[j]字符在轮盘的什么位置
      // distance2 : 从i逆时针走向jump2有多远
      int jump2 = counterClock(i, key[j]);
      int distance2 = (i > jump2 ? (i - jump2) : (i + n - jump2));
      ans = std::min(distance1 + f(jump1, j), distance2 + f(jump2, j));
    }
    dp[i][j] = ans;
    return ans;
  }

  // 从i开始，顺时针找到最近的v在轮盘的什么位置
  int clock(int i, int v)
  {
    int l = 0;
    // size[v] : 属于v这个字符的下标有几个
    int r = size[v] - 1, m;
    // sorted[0...size[v]-1]收集了所有的下标，并且有序
    vector<int> sorted = where[v];
    int find = -1;
    // 有序数组中，找>i尽量靠左的下标
    while (l <= r)
    {
      m = (l + r) / 2;
      if (sorted[m] > i)
      {
        find = m;
        r = m - 1;
      }
      else
      {
        l = m + 1;
      }
    }
    // 找到了就返回
    // 没找到，那i顺指针一定先走到最小的下标
    return find != -1 ? sorted[find] : sorted[0];
  }

  int counterClock(int i, int v)
  {
    int l = 0;
    int r = size[v] - 1, m;
    vector<int> sorted = where[v];
    int find = -1;
    // 有序数组中，找<i尽量靠右的下标
    while (l <= r)
    {
      m = (l + r) / 2;
      if (sorted[m] < i)
      {
        find = m;
        l = m + 1;
      }
      else
      {
        r = m - 1;
      }
    }
    // 找到了就返回
    // 没找到，那i逆指针一定先走到最大的下标
    return find != -1 ? sorted[find] : sorted[size[v] - 1];
  }
};
