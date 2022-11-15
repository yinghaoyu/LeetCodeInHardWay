#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  string customSortString1(string order, string s)
  {
    int n = order.length();
    int m = s.length();
    int cnt[26] = {0};
    string ans;
    for (int i = 0; i < m; i++)
    {
      cnt[s[i] - 'a']++;
    }
    for (int i = 0; i < n; i++)
    {
      int count = cnt[order[i] - 'a'];
      if (count > 0)
      {
        ans += string(count, order[i]);
        cnt[order[i] - 'a'] = 0;
      }
    }
    for (int i = 0; i < 26; i++)
    {
      if (cnt[i] > 0)
      {
        ans += string(cnt[i], i + 'a');
      }
    }
    return ans;
  }

  string customSortString2(string order, string s)
  {
    vector<int> val(26);
    for (int i = 0; i < order.size(); ++i)
    {
      val[order[i] - 'a'] = i + 1;
    }
    std::sort(s.begin(), s.end(), [&](char c0, char c1) { return val[c0 - 'a'] < val[c1 - 'a']; });
    return s;
  }
};

void testCustomSortString()
{
  Solution s;
  EXPECT_SUMMARY;
}

int main()
{
  testCustomSortString();
  return 0;
}
