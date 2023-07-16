#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

// 与 leetcode 0067 相同
// https://leetcode.cn/problems/add-binary/
// see at Problem_0067_addBinary.cc

class Solution
{
 public:
  string addBinary(string a, string b)
  {
    int n = a.length();
    int m = b.length();
    int i = n - 1;
    int j = m - 1;
    int carry = 0;
    string ans;
    while (i >= 0 || j >= 0 || carry > 0)
    {
      carry += i >= 0 ? a[i--] - '0' : 0;
      carry += j >= 0 ? b[j--] - '0' : 0;
      ans += std::to_string(carry % 2);
      carry /= 2;
    }
    std::reverse(ans.begin(), ans.end());
    return ans;
  }
};
