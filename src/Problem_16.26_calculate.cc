#include <algorithm>
#include <numeric>
#include <string>
#include <vector>

using namespace std;

// @sa Problem_0227_calculate.cc
class Solution
{
 public:
  int calculate(string s)
  {
    vector<int> stk;
    char presign = '+';
    int num = 0;
    int n = s.length();
    for (int i = 0; i < n; i++)
    {
      if (isdigit(s[i]))
      {
        // num = num * 10 + s[i] - '0';
        // 这种写法从左到右计算，当 num = 2147483647，会溢出！
        num = num * 10 + int(s[i] - '0');
      }
      if (!isdigit(s[i]) && s[i] != ' ' || i == n - 1)
      {
        switch (presign)
        {
        case '+':
          stk.push_back(num);
          break;
        case '-':
          stk.push_back(-num);
          break;
          // 先计算 * 和 /
        case '*':
          stk.back() *= num;
          break;
        default:
          stk.back() /= num;
        }
        presign = s[i];
        num = 0;
      }
    }
    return accumulate(stk.begin(), stk.end(), 0);
  }
};
