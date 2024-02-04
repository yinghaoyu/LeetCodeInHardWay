#include <string>
#include <vector>

using namespace std;

// TODO: figure it out.
class Solution
{
 public:
  // 时间复杂度O(n)
  int maxPalindromes(string str, int k)
  {
    manacherss(str);
    int ans = 0;
    int next = 0;
    while ((next = find(next, k)) != -1)
    {
      next = ss[next] == '#' ? next : (next + 1);
      ans++;
    }
    return ans;
  }

  static const int MAXN = 2001;

  char ss[MAXN << 1];

  int p[MAXN << 1];

  int n;

  void manacherss(string& a)
  {
    n = a.length() * 2 + 1;
    for (int i = 0, j = 0; i < n; i++)
    {
      ss[i] = (i & 1) == 0 ? '#' : a[j++];
    }
  }

  // s[l...]字符串只在这个范围上，且s[l]一定是'#'
  // 从下标l开始，之前都不算，一旦有某个中心回文半径>k，马上返回右边界
  int find(int l, int k)
  {
    for (int i = l, c = l - 1, r = l - 1, len; i < n; i++)
    {
      len = r > i ? std::min(p[2 * c - i], r - i) : 1;
      while (i + len < n && i - len > l - 1 && ss[i + len] == ss[i - len])
      {
        if (++len > k)
        {
          return i + k;
        }
      }
      if (i + len > r)
      {
        r = i + len;
        c = i;
      }
      p[i] = len;
    }
    return -1;
  }
};
