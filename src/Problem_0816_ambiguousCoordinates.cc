#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  vector<string> getPos(string s)
  {
    vector<string> pos;
    if (s[0] != '0' || s == "0")
    {
      // 只有一个0字符，或者没有前导0
      pos.push_back(s);
    }
    for (int p = 1; p < s.length(); ++p)
    {
      if ((p != 1 && s[0] == '0') || s.back() == '0')
      {
        // 如果有前导0，或者最后一个字符是0
        // 这样就不能插入小数点
        continue;
      }
      pos.push_back(s.substr(0, p) + "." + s.substr(p));
    }
    return pos;
  }

  vector<string> ambiguousCoordinates(string s)
  {
    vector<string> ans;
    int n = s.length() - 2;
    s = s.substr(1, n);
    for (int k = 1; k < n; k++)
    {
      vector<string> l = getPos(s.substr(0, k));
      if (l.empty())
      {
        continue;
      }
      vector<string> r = getPos(s.substr(k));
      if (r.empty())
      {
        continue;
      }
      for (auto &i : l)
      {
        for (auto &j : r)
        {
          ans.push_back("(" + i + ", " + j + ")");
        }
      }
    }
    return ans;
  }
};

bool isVectorEqual(vector<string> a, vector<string> b)
{
  if (a.size() != b.size())
  {
    return false;
  }
  std::sort(a.begin(), a.end());
  std::sort(b.begin(), b.end());
  for (int i = 0; i < a.size(); i++)
  {
    if (a[i] != b[i])
    {
      return false;
    }
  }
  return true;
}

void testAmbiguousCoordinates()
{
  Solution s;
  vector<string> o1 = {"(1, 2.3)", "(1, 23)", "(1.2, 3)", "(12, 3)"};
  vector<string> o2 = {"(0, 1.23)", "(0, 12.3)", "(0, 123)", "(0.1, 2.3)", "(0.1, 23)", "(0.12, 3)"};
  vector<string> o3 = {"(0, 0.011)", "(0.001, 1)"};
  EXPECT_TRUE(isVectorEqual(o1, s.ambiguousCoordinates("(123)")));
  EXPECT_TRUE(isVectorEqual(o2, s.ambiguousCoordinates("(0123)")));
  EXPECT_TRUE(isVectorEqual(o3, s.ambiguousCoordinates("(00011)")));
  EXPECT_SUMMARY;
}

int main()
{
  testAmbiguousCoordinates();
  return 0;
}
