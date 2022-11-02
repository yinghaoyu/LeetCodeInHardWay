#include <iostream>
#include <string>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  vector<string> buildArray(vector<int> &target, int n)
  {
    int m = target.size();
    vector<string> ans;
    for (int i = 1, j = 0; i <= n && j < m; i++)
    {
      ans.push_back("Push");
      if (target[j] != i)
      {
        ans.push_back("Pop");
      }
      else
      {
        j++;
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
  for (int i = 0; i < a.size(); i++)
  {
    if (a[i] != b[i])
    {
      return false;
    }
  }
  return true;
}

void testBuildArray()
{
  Solution s;
  vector<int> n1 = {1, 3};
  vector<string> o1 = {"Push", "Push", "Pop", "Push"};
  vector<int> n2 = {1, 2, 3};
  vector<string> o2 = {"Push", "Push", "Push"};
  vector<int> n3 = {1, 2};
  vector<string> o3 = {"Push", "Push"};
  EXPECT_TRUE(isVectorEqual(o1, s.buildArray(n1, 3)));
  EXPECT_TRUE(isVectorEqual(o2, s.buildArray(n2, 3)));
  EXPECT_TRUE(isVectorEqual(o3, s.buildArray(n3, 4)));
  EXPECT_SUMMARY;
}

int main()
{
  testBuildArray();
  return 0;
}
