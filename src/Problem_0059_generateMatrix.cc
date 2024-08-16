#include <vector>

using namespace std;

class Solution
{
 public:
  vector<vector<int>> generateMatrix(int n)
  {
    vector<vector<int>> ans(n, vector<int>(n));
    int a = 0;
    int b = 0;
    int c = ans.size();
    int d = ans[0].size();
    int x = 1;
    while (a < c && b < d)
    {
      rectangle(ans, a++, b++, --c, --d, x);
    }
    return ans;
  }

  // 从外往内按矩形填
  void rectangle(vector<vector<int>>& ans, int a, int b, int c, int d, int& x)
  {
    for (int i = b; i <= d; i++)
    {
      ans[a][i] = x++;
    }
    for (int i = a + 1; i <= c; i++)
    {
      ans[i][d] = x++;
    }
    for (int i = d - 1; i >= b; i--)
    {
      ans[c][i] = x++;
    }
    for (int i = c - 1; i > a; i--)
    {
      ans[i][b] = x++;
    }
  }
};
