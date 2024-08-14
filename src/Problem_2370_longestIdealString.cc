#include <string>
#include <vector>

using namespace std;

// TODO: figure it out
class Solution
{
 public:
  // 数据量太小，线段树的优势不明显
  // 时间复杂度O(n * log e)，n为字符串长度，e为字符集大小
  int longestIdealString(string s, int k)
  {
    std::fill(max.begin(), max.end(), 0);
    int v, p;
    int ans = 0;
    for (char cha : s)
    {
      v = cha - 'a' + 1;
      p = getMax(std::max(v - k, 1), std::min(v + k, n), 1, n, 1);
      ans = std::max(ans, p + 1);
      update(v, p + 1, 1, n, 1);
    }
    return ans;
  }

 private:
  static constexpr int n = 26;

  vector<int> max = vector<int>((n + 1) << 2);

  void up(int i) { max[i] = std::max(max[i << 1], max[i << 1 | 1]); }

  // 只有单点更新不需要定义down方法
  // 因为单点更新的任务一定会从线段树头节点直插到某个叶节点
  // 根本没有懒更新这回事
  void update(int jobi, int jobv, int l, int r, int i)
  {
    if (l == r && jobi == l)
    {
      max[i] = jobv;
    }
    else
    {
      int m = (l + r) >> 1;
      if (jobi <= m)
      {
        update(jobi, jobv, l, m, i << 1);
      }
      else
      {
        update(jobi, jobv, m + 1, r, i << 1 | 1);
      }
      up(i);
    }
  }

  int getMax(int jobl, int jobr, int l, int r, int i)
  {
    if (jobl <= l && r <= jobr)
    {
      return max[i];
    }
    int m = (l + r) >> 1;
    int ans = 0;
    if (jobl <= m)
    {
      ans = std::max(ans, getMax(jobl, jobr, l, m, i << 1));
    }
    if (jobr > m)
    {
      ans = std::max(ans, getMax(jobl, jobr, m + 1, r, i << 1 | 1));
    }
    return ans;
  }
};
