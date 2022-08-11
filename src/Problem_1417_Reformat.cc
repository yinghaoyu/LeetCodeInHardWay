#include <iostream>
#include <string>

using namespace std;

// 测试链接：https://leetcode.cn/problems/reformat-the-string/

class Solution
{
 public:
  static string reformat(string s)
  {
    if (s.length() < 2)
    {
      return s;
    }
    string numeric;
    string alpha;
    for (int i = 0; i < s.length(); i++)
    {
      if ('a' <= s[i] && s[i] <= 'z')
      {
        alpha.push_back(s[i]);
      }
      else if ('0' <= s[i] && s[i] <= '9')
      {
        numeric.push_back(s[i]);
      }
    }
    int n = alpha.length();
    int m = numeric.length();
    if (std::abs(n - m) > 1)
    {
      return "";
    }
    int expected = n > m ? 1 : 0;
    int i = 0;
    int j = 0;
    int k = 0;
    while (i < n || j < m)
    {
      if (expected)
      {
        s[k++] = alpha[i++];
        expected = 0;
      }
      else
      {
        s[k++] = numeric[j++];
        expected = 1;
      }
    }
    s[k] = n > m ? alpha[i] : numeric[j];
    return s;
  }
};

int main()
{
  string s1 = "a0b1c2";
  string s2 = "leetcode";
  string s3 = "1229857369";
  cout << Solution::reformat(s1) << endl;
  cout << Solution::reformat(s2) << endl;
  cout << Solution::reformat(s3) << endl;
  return 0;
}
