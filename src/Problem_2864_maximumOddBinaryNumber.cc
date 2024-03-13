#include <string>
#include <vector>

using namespace std;

class Solution
{
 public:
  string maximumOddBinaryNumber(string s)
  {
    int n = s.length();
    int l = 0, r = 0, last = -1;
    while (r < n)
    {
      if (s[r] == '1')
      {
        // 把所有 1 先移动到最左边
        last = l;
        std::swap(s[l++], s[r++]);
      }
      else
      {
        r++;
      }
    }
    // 把最后的 1 移动到末尾
    std::swap(s[last], s[n - 1]);
    return s;
  }
};
