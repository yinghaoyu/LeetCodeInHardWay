#include <string>
#include <vector>

using namespace std;

class Solution
{
 public:
  int longestPalindrome(string s)
  {
    vector<int> cnts(256);
    for (char c : s)
    {
      cnts[c]++;
    }
    int ans = 0;
    for (int freq : cnts)
    {
      // 左右各分配 freq / 2 个字符
      ans += freq / 2 * 2;
      if ((freq & 1) && !(ans & 1))
      {
        // 奇数字符直接当中间字符
        ans++;
      }
    }
    return ans;
  }
};
