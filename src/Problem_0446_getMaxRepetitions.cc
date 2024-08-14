#include <string>
#include <vector>

using namespace std;

// TODO: figure it out
class Solution
{
 public:
  // 最优解
  // 时间复杂度O(s1长度 * s2长度)
  int getMaxRepetitions(string s1, int n1, string s2, int n2)
  {
    int n = s1.length();
    // next[i][j] : 从i位置出发，至少需要多少长度，能找到j字符
    vector<vector<int>> next(n, vector<int>(26));
    // 时间复杂度O(s1长度 + s2长度)
    if (!find(s1, n, next, s2))
    {
      return 0;
    }

    // st[i][p] : 从i位置出发，至少需要多少长度，可以获得2^p个s2
    vector<vector<long>> st(n, vector<long>(30));
    // 时间复杂度O(s1长度 * s2长度)
    for (int i = 0, cur, len; i < n; i++)
    {
      cur = i;
      len = 0;
      for (char c : s2)
      {
        len += next[cur][c - 'a'];
        cur = (cur + next[cur][c - 'a']) % n;
      }
      st[i][0] = len;
    }
    // 时间复杂度O(s1长度)
    for (int p = 1; p <= 29; p++)
    {
      for (int i = 0; i < n; i++)
      {
        st[i][p] = st[i][p - 1] + st[(int) ((st[i][p - 1] + i) % n)][p - 1];
      }
    }
    long ans = 0;
    // 时间复杂度O(1)
    for (int p = 29, start = 0; p >= 0; p--)
    {
      if (st[start % n][p] + start <= n * n1)
      {
        ans += 1 << p;
        start += st[start % n][p];
      }
    }
    return ans / n2;
  }

  // 时间复杂度O(s1长度 + s2长度)
  bool find(string& s1, int n, vector<vector<int>>& next, string& s2)
  {
    vector<int> right(26, -1);
    for (int i = n - 1; i >= 0; i--)
    {
      right[s1[i] - 'a'] = i + n;
    }
    for (int i = n - 1; i >= 0; i--)
    {
      right[s1[i] - 'a'] = i;
      for (int j = 0; j < 26; j++)
      {
        if (right[j] != -1)
        {
          next[i][j] = right[j] - i + 1;
        }
        else
        {
          next[i][j] = -1;
        }
      }
    }
    for (char c : s2)
    {
      if (next[0][c - 'a'] == -1)
      {
        return false;
      }
    }
    return true;
  }
};
