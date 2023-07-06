#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  bool check(vector<vector<bool>> &rect, int x, int y, int k)
  {
    for (int i = x; i < x + k; i++)
    {
      for (int j = y; j < y + k; j++)
      {
        if (rect[i][j])
        {
          return false;
        }
      }
    }
    return true;
  }

  void fill(vector<vector<bool>> &rect, int x, int y, int k, bool val)
  {
    for (int i = x; i < x + k; i++)
    {
      for (int j = y; j < y + k; j++)
      {
        rect[i][j] = val;
      }
    }
  }

  void process(int x, int y, vector<vector<bool>> &rect, int cnt, int &ans)
  {
    int n = rect.size();
    int m = rect[0].size();
    if (cnt >= ans)
    {
      return;
    }
    if (x >= n)
    {
      // 铺完所有
      ans = cnt;
      return;
    }
    if (y >= m)
    {
      // 这一行铺完了，换下一行
      process(x + 1, 0, rect, cnt, ans);
      return;
    }
    if (rect[x][y])
    {
      // 已经被覆盖，则直接尝试下一个位置
      process(x, y + 1, rect, cnt, ans);
      return;
    }
    // 理论上正方形的最大边长
    int len = std::min(n - x, m - y);
    while (len >= 1 && !check(rect, x, y, len))
    {
      // 找到能铺的最大边长
      len--;
    }
    for (int k = len; k >= 1; k--)
    {
      // 尝试不同的正方形瓷砖
      fill(rect, x, y, k, true);
      process(x, y + k, rect, cnt + 1, ans);
      fill(rect, x, y, k, false);
    }
  }

  int tilingRectangle(int n, int m)
  {
    int ans = std::max(m, n);
    vector<vector<bool>> rect(n, vector<bool>(m));
    process(0, 0, rect, 0, ans);
    return ans;
  }
};

void test()
{
  Solution s;
  EXPECT_EQ_INT(3, s.tilingRectangle(2, 3));
  EXPECT_EQ_INT(5, s.tilingRectangle(5, 8));
  EXPECT_EQ_INT(6, s.tilingRectangle(11, 13));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
