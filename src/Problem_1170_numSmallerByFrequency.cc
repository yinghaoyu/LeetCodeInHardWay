#include <iostream>
#include <string>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int f(string &s)
  {
    int cnt = 0;
    char ch = 'z';
    for (auto &c : s)
    {
      if (c < ch)
      {
        ch = c;
        cnt = 1;
      }
      else if (c == ch)
      {
        cnt++;
      }
    }
    return cnt;
  }

  vector<int> numSmallerByFrequency(vector<string> &queries, vector<string> &words)
  {
    vector<int> count(12);
    for (auto &w : words)
    {
      // 统计 f(w)
      count[f(w)]++;
    }
    for (int i = 9; i >= 1; i--)
    {
      // 后缀和
      count[i] += count[i + 1];
    }
    vector<int> ans;
    for (auto &s : queries)
    {
      // 满足 f(s) < f(w) 的个数
      // 若 f(s) = 10，f(s) < f(w) 的个数在 count[11]，因此 count 长度至少为 12
      ans.push_back(count[f(s) + 1]);
    }
    return ans;
  }
};

void test()
{
  Solution s;
  vector<string> q1 = {"cbd"};
  vector<string> w1 = {"zaaaz"};
  vector<int> o1 = {1};
  vector<string> q2 = {"bbb", "cc"};
  vector<string> w2 = {"a", "aa", "aaa", "aaaa"};
  vector<int> o2 = {1, 2};
  EXPECT_TRUE(o1 == s.numSmallerByFrequency(q1, w1));
  EXPECT_TRUE(o2 == s.numSmallerByFrequency(q2, w2));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
