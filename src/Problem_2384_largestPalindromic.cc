#include <string>
#include <vector>

using namespace std;

class Solution
{
 public:
  string largestPalindromic(string num)
  {
    int n = num.size();
    // '0' ~ '9'字符对应整数为48 ~ 57
    vector<int> cnts(58);
    for (char c : num)
    {
      cnts[c]++;
    }
    string ans(n, ' ');
    int leftSize = 0;
    char mid = 0;
    for (char i = '9'; i >= '1'; i--)
    {
      if ((cnts[i] & 1) && mid == 0)
      {
        // 记录最大出现奇数次的数字
        mid = i;
      }
      for (int j = cnts[i] / 2; j > 0; j--)
      {
        // 左边从大到小依次填好
        ans[leftSize++] = i;
      }
    }
    // '1'~'9'每一种字符出现的次数 <= 1
    if (leftSize == 0)
    {
      if (mid == 0)
      {
        // '1'~'9'每一种字符出现的次数 == 0
        return "0";
      }
      else
      {
        // '1'~'9' 有若干字符出现次数 == 1，其中最大的字符是mid
        return std::string(1, mid);
      }
    }
    // '1'~'9'有若干字符出现次数 >= 2，左部分已经建立，再考虑把'0'字符填进来
    for (int j = cnts['0'] / 2; j > 0; j--)
    {
      ans[leftSize++] = '0';
    }
    int len = leftSize;
    // 把中点安插进去
    if (mid == 0 && (cnts['0'] & 1) == 1)
    {
      mid = '0';
    }
    if (mid != 0)
    {
      ans[len++] = mid;
    }
    // 左部分逆序拷贝给右部分
    for (int i = leftSize - 1; i >= 0; i--)
    {
      ans[len++] = ans[i];
    }
    return ans.substr(0, len);
  }
};
