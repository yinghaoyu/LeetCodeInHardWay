#include <string>

using namespace std;

// TODO: figure it out.
class Solution
{
 public:
  static const int MAXN = 2001;

  static const int MAXV = 26;

  static int n;

  static string s;

  // 所有字符的位置列表
  int end[MAXV];
  int pre[MAXN];

  // 树状数组
  int tree[MAXN];

  // 归并分治
  int arr[MAXN];
  int help[MAXN];

  void build()
  {
    std::fill_n(end, MAXV, 0);
    std::fill_n(arr, n + 1, 0);
    std::fill_n(tree, n + 1, 0);
    for (int i = 1; i <= n; i++)
    {
      add(i, 1);
    }
  }

  // 字符v把下标j加入列表
  void push(int v, int j)
  {
    pre[j] = end[v];
    end[v] = j;
  }

  // 弹出当前v字符最后的下标
  int pop(int v)
  {
    int ans = end[v];
    end[v] = pre[end[v]];
    return ans;
  }

  int lowbit(int i) { return i & -i; }

  void add(int i, int v)
  {
    while (i <= n)
    {
      tree[i] += v;
      i += lowbit(i);
    }
  }

  int sum(int i)
  {
    int ans = 0;
    while (i > 0)
    {
      ans += tree[i];
      i -= lowbit(i);
    }
    return ans;
  }

  // 时间复杂度O(n * logn)
  int minMovesToMakePalindrome(string str)
  {
    s = str;
    n = s.length();
    build();
    for (int i = 0, j = 1; i < n; i++, j++)
    {
      push(s[i] - 'a', j);
    }
    // arr[i]记录每个位置的字符最终要去哪
    for (int i = 0, l = 1, r, k; i < n; i++, l++)
    {
      if (arr[l] == 0)
      {
        r = pop(s[i] - 'a');
        if (l < r)
        {
          k = sum(l);
          arr[l] = k;
          arr[r] = n - k + 1;
        }
        else
        {
          arr[l] = (1 + n) / 2;
        }
        add(r, -1);
      }
    }
    return number(1, n);
  }

  int number(int l, int r)
  {
    if (l >= r)
    {
      return 0;
    }
    int m = (l + r) / 2;
    return number(l, m) + number(m + 1, r) + merge(l, m, r);
  }

  int merge(int l, int m, int r)
  {
    int ans = 0;
    for (int i = m, j = r; i >= l; i--)
    {
      while (j >= m + 1 && arr[i] <= arr[j])
      {
        j--;
      }
      ans += j - m;
    }
    int i = l;
    int a = l;
    int b = m + 1;
    while (a <= m && b <= r)
    {
      help[i++] = arr[a] <= arr[b] ? arr[a++] : arr[b++];
    }
    while (a <= m)
    {
      help[i++] = arr[a++];
    }
    while (b <= r)
    {
      help[i++] = arr[b++];
    }
    for (i = l; i <= r; i++)
    {
      arr[i] = help[i];
    }
    return ans;
  }
};
