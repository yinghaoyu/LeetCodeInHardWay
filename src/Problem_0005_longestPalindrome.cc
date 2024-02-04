#include <iostream>
#include <string>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  // 第一眼想到的是暴力解
  // 以每个字符为中心向左右两边扩，直到扩不动为止，记录下每个字符对应能扩的范围大小。
  // 因为有每个位置左右两边能扩的最大范围，我们可以很方便还原出最长回文子串是什么。
  // 比如：AB1234321CD 这个字符串，以4字符为中心向左右两边能扩的位置最大，1234321 为最长回文子串。
  // 如上解法有个问题，即针对类似1ABBA2这样的字符串，如上算法会错过最长回文子串ABBA,
  // 因为ABBA不是以任何一个字符串向左右两边扩散得到的。
  // 所以，需要预处理一下原始字符串，预处理的方式如下：
  // 在字符串的每两个位置之间插入一个特殊字符，变成一个预处理后的字符串，比如我们可以以#作为特殊字符（特殊字符选哪个无所谓，不必非要是原始串中不含有的字符），将1ABBA2这个字符串预处理成1#A#B#B#A#2，用预处理串来跑这个暴力解法，会得到#A#B#B#A#这个是预处理串的最长回文子串，我们可以很方便把这个串还原成原始串的最长回文子串。

  // 暴力解法时间复杂度为O(N^2)
  string longestPalindrome1(string s)
  {
    if (s.length() == 1)
    {
      return s;
    }
    string m = manacherString(s);
    int max = 1;  // 最大回文长度至少是1
    int lM = 0;   // 记录最长回文的左边界的上一个位置
    int rM = 0;   // 记录最长回文的右边界的下一个位置
    for (int i = 1; i < m.length(); i++)
    {
      int curMax = 1;  // 当前的最大回文长度至少是1
      int l = i - 1;
      int r = i + 1;
      while (l >= 0 && r < m.length())
      {
        if (m[l] == m[r])
        {
          // 暴力扩充
          l--;
          r++;
        }
        else
        {
          break;
        }
      }
      curMax = r - l - 1;
      if (curMax > max)
      {
        // 当前最长回文长度已经超过了max了
        // 更新中心值
        // 更新max值
        max = curMax;
        lM = l;
        rM = r;
      }
    }
    string ans;
    // 当m[l] == m[r]的时候，l多减了一次，所以m[lM+1]是'#'，m[lM+2]才是需要的字符
    for (int i = lM + 2; i < rM; i += 2)
    {
      ans.push_back(m[i]);
    }
    return ans;
  }

  // Manacher算法用O(N)复杂度解决这个问题
  string longestPalindrome2(string s)
  {
    if (s.length() == 0)
    {
      return "";
    }
    string m = manacherString(s);
    // 存每个位置最长回文半径是多少
    // 比如#A#B#B#A#这个字符串，
    // 位于数组2号位置的A的回文半径是A#或者#A, 长度为2，则radius[2] = 2，
    // 位于数组4号位置的#的回文半径是#B#A#或者#A#B#, 长度为5，则radius[4] = 5
    vector<int> radius(m.length());
    int index = -1;
    // 回文最右边界，只要某个位置能扩到超过这个位置，就更新r这个值，初始值为0，因为一个字符串回文字符串至少是1，可以以第0个字符为中心且以0为最右边界(即：第0个字符本身作为一个回文串)
    int R = -1;
    int max = INT32_MIN;
    int mid = 0;
    for (int i = 0; i != m.length(); i++)
    {
      // radius[i] 至少不需要扩的大小
      radius[i] = R > i ? std::min(radius[index - (i - index)], R - i) : 1;
      // 暴力扩
      while (i + radius[i] < m.length() && i - radius[i] > -1)
      {
        if (m[i + radius[i]] == m[i - radius[i]])
        {
          radius[i]++;
        }
        else
        {
          break;
        }
      }
      // 扩散的位置能否更新回文有边界R
      // 如果可以更新，则更新R，且把index置于当前的i，因为是当前的i让回文右边界扩散的
      if (i + radius[i] > R)
      {
        R = i + radius[i];
        index = i;
      }
      // 定位最大回文有边界的回文中心是哪个
      if (max < radius[i])
      {
        max = radius[i];
        mid = i;
      }
    }
    mid = (mid - 1) / 2;
    max = max - 1;
    int begin = (max & 1) == 0 ? mid - (max / 2) + 1 : mid - (max / 2);
    int end = mid + (max / 2) + 1;
    return s.substr(begin, end - begin);
  }

  // 把字符串 1AABBCC2 处理为 #1#A#A#B#B#C#C#2#
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

bool isStringEuqal(string a, string b)
{
  return a == b;
}

void testLongestPalindrome()
{
  Solution s;
  EXPECT_TRUE(isStringEuqal("bab", s.longestPalindrome1("babad")));
  EXPECT_TRUE(isStringEuqal("bb", s.longestPalindrome1("cbbd")));
  EXPECT_TRUE(isStringEuqal("bab", s.longestPalindrome2("babad")));
  EXPECT_TRUE(isStringEuqal("bb", s.longestPalindrome2("cbbd")));
  EXPECT_SUMMARY;
}

int main()
{
  testLongestPalindrome();
  return 0;
}
