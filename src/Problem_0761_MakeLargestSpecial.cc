#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// 测试链接：https://leetcode.cn/problems/special-binary-string/

// 1、原字符串一定可以分为不可再分的特殊字符串若干段；
// 2、每一个不可再分的特殊字符串。处理完美后，一定是一个"1" + 中间的字符串处理 +
// "0"。
// 这里的处理，表示的是变成字典序最大的字符串，处理过程是递归进行的，终止于字符串长度为0；
// 3、把这些处理过的字符串按照字典序从大到小排列，就是所求的字符串。

class Solution
{
 public:
  static string makeLargestSpecial(string s)
  {
    int n = s.length();
    if (n == 0)
    {
      return "";
    }
    int count = 0;
    int pre = 0;
    vector<string> subStrList;
    for (int i = 0; i < n; i++)
    {  // 从左往右
      if (s[i] == '1')
      {
        count++;
      }
      else
      {
        count--;
        if (count == 0)
        {
          subStrList.push_back(
              // 这个串的长度pre...i
              // 去除开头的1和结尾的0
              // 对pre + 1 ... i - 1继续递归
              "1" + makeLargestSpecial(s.substr(pre + 1, i - 1 - pre)) + "0");
          pre = i + 1;  // 记录下一个串的开始
        }
      }
    }
    std::sort(subStrList.begin(), subStrList.end());
    string ans;
    for (int i = subStrList.size() - 1; i >= 0; i--)
    {
      ans += subStrList[i];
    }
    return ans;
  }
};
int main()
{
  string s = "11011000";
  cout << Solution::makeLargestSpecial(s) << endl;
  return 0;
}
