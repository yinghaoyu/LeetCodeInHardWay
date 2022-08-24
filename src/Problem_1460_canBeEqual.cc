#include <algorithm>
#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;
class Solution
{
 public:
  bool canBeEqual(vector<int> &target, vector<int> &arr)
  {
    int count[1001] = {0};
    int ancher = 0;
    int len = target.size();
    for (int i = 0; i < len; i++)
    {
      if (++count[target[i]] == 1)
      {
        ancher++;
      }
      if (--count[arr[i]] == 0)
      {
        ancher--;
      }
    }
    return ancher == 0;
  }
};

bool isVectorEqual(vector<int> &lhs, vector<int> &rhs)
{
  if (lhs.size() != rhs.size())
  {
    return false;
  }
  std::sort(lhs.begin(), lhs.end());
  std::sort(rhs.begin(), rhs.end());
  for (int i = 0; i < lhs.size(); i++)
  {
    if (lhs[i] != rhs[i])
    {
      return false;
    }
  }
  return true;
}

void testCanBeEqual()
{
  Solution s;
  vector<int> v1 = {1, 2, 3, 4};
  vector<int> v2 = {2, 4, 3, 1};
  vector<int> v3 = {2, 3, 4};
  vector<int> v4 = {2, 3, 11};
  EXPECT_EQ_INT(s.canBeEqual(v1, v2), isVectorEqual(v1, v2));
  EXPECT_EQ_INT(s.canBeEqual(v3, v4), isVectorEqual(v3, v4));
  EXPECT_SUMMARY;
}

int main()
{
  testCanBeEqual();
  return 0;
}
