#include <iostream>

using namespace std;

class Solution
{
 public:
  static string solveEquation(string s)
  {
    string ans;
    int op = 1;  // 符号位
    int x = 0;   // x的系数
    int y = 0;   // 值的和
    for (int i = 0; i < s.length();)
    {
      if (s[i] == '-')
      {
        op = -1;
        i++;
      }
      else if (s[i] == '+')
      {
        op = 1;
        i++;
      }
      else if (s[i] == '=')
      {
        x = -x;  // 相当于把x从等号左边移动到右边
        y = -y;
        op = 1;
        i++;
      }
      else
      {
        int j = i;
        while (j < s.length() && s[j] != '+' && s[j] != '-' && s[j] != '=')
        {
          j++;
        }
        if (s[j - 1] == 'x')  // 123x 或者 x
        {
          // j-1 > i 说明x项前有系数 > 1
          x += (j - 1 > i ? atoi(s.substr(i, j - i - 1).c_str()) : 1) * op;
        }
        else
        {
          int number = atoi(s.substr(i, j - i).c_str());
          y += number * op;
        }
        i = j;
      }
    }
    if (x == 0)
    {
      if (y == 0)
      {
        ans = "Infinite solutions";
      }
      else
      {
        ans = "No solution";
      }
    }
    else
    {
      ans = "x=" + std::to_string(-y / x);
    }
    return ans;
  }
};

int main()
{
  string s1 = "x+5-3+x=6+x-2";
  string s2 = "x=x";
  string s3 = "2x=x";
  cout << Solution::solveEquation(s1) << endl;
  cout << Solution::solveEquation(s2) << endl;
  cout << Solution::solveEquation(s3) << endl;
  return 0;
}
