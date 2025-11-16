#include <string>

using namespace std;

// 贪心
class Solution
{
 public:
  // 1. 从左到右遍历 s，同时用一个变量 cnt 1维护遍历到的 1 的个数。
  // 2. 如果 s[i] 是 1，把 cnt 1 增加 1。
  // 3. 如果 s[i] 是 0 且 s[i−1] 是 1，意味着我们找到了一段道路，可以让 i
  //    左边的每辆车都操作一次，把答案增加 cnt1
  int maxOperations(string s)
  {
    int ans = 0;
    int cnt1 = 0;
    int n = s.length();
    for (int i = 0; i < n; i++)
    {
      if (s[i] == '1')
      {
        cnt1++;
      }
      else if (i > 0 && s[i - 1] == '1')
      {
        ans += cnt1;
      }
    }
    return ans;
  }
};
