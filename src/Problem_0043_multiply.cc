#include <algorithm>
#include <string>

using namespace std;

class Solution
{
 public:
  // 竖式乘法
  string multiply(string num1, string num2)
  {
    if (num1 == "0" || num2 == "0")
    {
      return "0";
    }
    string ans = "0";
    int m = num1.size();
    int n = num2.size();
    for (int i = n - 1; i >= 0; i--)
    {
      string cur;
      int add = 0;
      for (int j = n - 1; j > i; j--)
      {
        cur.push_back(0);
      }
      int y = num2[i] - '0';
      for (int j = m - 1; j >= 0; j--)
      {
        int x = num1[j] - '0';
        int product = x * y + add;
        cur.push_back(product % 10);
        add = product / 10;
      }
      while (add != 0)
      {
        cur.push_back(add % 10);
        add /= 10;
      }
      std::reverse(cur.begin(), cur.end());
      for (auto& c : cur)
      {
        c += '0';
      }
      ans = addString(ans, cur);
    }
    return ans;
  }

  // 计算两数相加
  string addString(string& num1, string& num2)
  {
    int i = num1.size() - 1, j = num2.size() - 1, add = 0;
    string ans;
    while (i >= 0 || j >= 0 || add != 0)
    {
      int x = i >= 0 ? num1.at(i) - '0' : 0;
      int y = j >= 0 ? num2.at(j) - '0' : 0;
      int result = x + y + add;
      ans.push_back(result % 10);
      add = result / 10;
      i--;
      j--;
    }
    std::reverse(ans.begin(), ans.end());
    for (auto& c : ans)
    {
      c += '0';
    }
    return ans;
  }
};
