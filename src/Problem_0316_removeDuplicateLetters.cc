#include <iterator>
#include <string>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  string removeDuplicateLetters(string s)
  {
    vector<int> cnt(26);
    vector<bool> enter(26);
    string ans;
    int r = 0;
    for (char c : s)
    {
      cnt[c - 'a']++;
    }
    for (char c : s)
    {
      if (!enter[c - 'a'])
      {
        // 如果当前的字符比单调栈顶的字典序小，并且单调栈顶的字符后面还有
        // 那就出栈，反正后面还有这个字符进栈
        while (!ans.empty() && ans.back() > c && cnt[ans.back() - 'a'] > 0)
        {
          enter[ans.back() - 'a'] = false;
          ans.pop_back();
        }
        ans.push_back(c);
        enter[c - 'a'] = true;
      }
      cnt[c - 'a']--;
    }
    return ans;
  }
};

void test()
{
  Solution s;
  EXPECT_TRUE("abc" == s.removeDuplicateLetters("bcabc"));
  EXPECT_TRUE("acdb" == s.removeDuplicateLetters("cbacdcbc"));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
