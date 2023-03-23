#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

// TODO: figure it out
// Manacher 算法
class Solution
{
 public:
  int countSubstrings(string s)
  {
    if (s.length() == 0)
    {
      return 0;
    }
    vector<int> dp = getManacherDP(s);
    int ans = 0;
    for (int i = 0; i < dp.size(); i++)
    {
      ans += (dp[i] >> 1);
    }
    return ans;
  }

  vector<int> getManacherDP(string s)
  {
    string str = manacherString(s);
    vector<int> pArr(str.length());
    int C = -1;
    int R = -1;
    for (int i = 0; i < str.length(); i++)
    {
      pArr[i] = R > i ? std::min(pArr[2 * C - i], R - i) : 1;
      while (i + pArr[i] < str.size() && i - pArr[i] > -1)
      {
        if (str[i + pArr[i]] == str[i - pArr[i]])
          pArr[i]++;
        else
        {
          break;
        }
      }
      if (i + pArr[i] > R)
      {
        R = i + pArr[i];
        C = i;
      }
    }
    return pArr;
  }

  string manacherString(string str)
  {
    string res(str.length() * 2 + 1, ' ');
    int index = 0;
    for (int i = 0; i != res.length(); i++)
    {
      res[i] = (i & 1) == 0 ? '#' : str[index++];
    }
    return res;
  }
};

void testCountSubstrings()
{
  Solution s;
  EXPECT_EQ_INT(3, s.countSubstrings("abc"));
  EXPECT_EQ_INT(6, s.countSubstrings("aaa"));
  EXPECT_SUMMARY;
}

int main()
{
  testCountSubstrings();
  return 0;
}
