#include <vector>

using namespace std;

class Solution
{
 public:
  void f(vector<int>& ans, int cur, int max)
  {
    if (cur > max)
    {
      // 过大，尝试结束
      return;
    }
    if (cur != 0)
    {
      // 题设不包含 0
      ans.push_back(cur);
    }
    ans.push_back(cur);
    for (int i = 0; i < 10; i++)
    {
      if (cur == 0 && i == 0)
      {
        // 过滤不必要的递归
        continue;
      }
      f(ans, cur * 10 + i, max);
    }
  }

  vector<int> lexicalOrder1(int n)
  {
    vector<int> ans;
    f(ans, 0, n);
    return ans;
  }

  // 递归改迭代
  vector<int> lexicalOrder2(int n)
  {
    vector<int> ans(n);
    int num = 1;
    for (int i = 0; i < n; i++)
    {
      ans[i] = num;
      if (num * 10 <= n)
      {
        num *= 10;
      }
      else
      {
        while (num % 10 == 9 || num + 1 > n)
        {
          num /= 10;
        }
        num++;
      }
    }
    return ans;
  }
};
