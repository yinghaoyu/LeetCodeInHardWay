#include <iostream>
#include <string>
#include <vector>

using namespace std;

// seem as leetcode 0680
// https://leetcode-cn.com/problems/valid-palindrome-ii/
// see at Problem_0680_validPalindrome.cc
class Solution
{
 public:
  bool isPalindrome(string &s, int L, int R)
  {
    for (int i = L, j = R; i < j; i++, j--)
    {
      if (s[i] != s[j])
      {
        return false;
      }
    }
    return true;
  }

  bool validPalindrome(string s)
  {
    int n = s.length();
    int left = 0;
    int right = n - 1;
    while (left < right)
    {
      if (s[left] == s[right])
      {
        left++;
        right--;
      }
      else
      {
        return isPalindrome(s, left + 1, right) || isPalindrome(s, left, right - 1);
      }
    }
    return true;
  }
};
