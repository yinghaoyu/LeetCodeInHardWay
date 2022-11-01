#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  vector<string> subdomainVisits(vector<string> &cpdomains)
  {
    int n = cpdomains.size();
    unordered_map<string, int> map;
    vector<string> ans;
    for (int i = 0; i < n; i++)
    {
      string m = cpdomains[i];
      int space = m.find(' ');
      int value = atoi(m.substr(0, space).c_str());
      string key = m.substr(space + 1);
      map[key] += value;
      int dot = key.find_last_of('.');
      string pre;
      while (dot != string::npos)
      {
        pre = key.substr(dot) + pre;
        map[pre.substr(1)] += value;
        key = key.substr(0, dot);
        dot = key.find_last_of('.');
      }
    }
    for (auto entry : map)
    {
      ans.push_back(std::to_string(entry.second) + " " + entry.first);
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

void testsubdomainVisits()
{
  Solution s;
  vector<string> n1 = {"9001 discuss.leetcode.com"};
  vector<string> o1 = {"9001 leetcode.com", "9001 discuss.leetcode.com", "9001 com"};
  vector<string> n2 = {"900 google.mail.com", "50 yahoo.com", "1 intel.mail.com", "5 wiki.org"};
  vector<string> o2 = {"901 mail.com", "50 yahoo.com", "900 google.mail.com", "5 wiki.org", "5 org", "1 intel.mail.com", "951 com"};
  EXPECT_TRUE(isVectorEqual(o1, s.subdomainVisits(n1)));
  EXPECT_TRUE(isVectorEqual(o2, s.subdomainVisits(n2)));
  EXPECT_SUMMARY;
}

int main()
{
  testsubdomainVisits();
  return 0;
}
