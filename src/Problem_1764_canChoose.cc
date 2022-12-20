#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  bool check(vector<int> &groups, vector<int> &nums, int k)
  {
    if (k + groups.size() > nums.size())
    {
      return false;
    }
    for (int i = 0; i < groups.size(); i++)
    {
      if (groups[i] != nums[k + i])
      {
        return false;
      }
    }
    return true;
  }
  bool canChoose(vector<vector<int>> &groups, vector<int> &nums)
  {
    int n = groups.size();
    int m = nums.size();
    int j = 0;
    for (int i = 0; i < m && j < n;)
    {
      if (check(groups[j], nums, i))
      {
        i += groups[j].size();
        j++;
      }
      else
      {
        i++;
      }
    }
    return j == n;
  }
  // TODO: KMP
};

void testCanChoose()
{
  Solution s;
  vector<vector<int>> g1 = {{1, -1, -1}, {3, -2, 0}};
  vector<int> n1 = {1, -1, 0, 1, -1, -1, 3, -2, 0};

  vector<vector<int>> g2 = {{10, -2}, {1, 2, 3, 4}};
  vector<int> n2 = {1, 2, 3, 4, 10, -2};

  vector<vector<int>> g3 = {{1, 2, 3}, {3, 4}};
  vector<int> n3 = {7, 7, 1, 2, 3, 4, 7, 7};

  vector<vector<int>> g4 = {{21, 22, 21, 22, 21, 30}};
  vector<int> n4 = {21, 22, 21, 22, 21, 22, 21, 30};

  EXPECT_TRUE(s.canChoose(g1, n1));
  EXPECT_FALSE(s.canChoose(g2, n2));
  EXPECT_FALSE(s.canChoose(g3, n3));
  EXPECT_TRUE(s.canChoose(g4, n4));
  EXPECT_SUMMARY;
}

int main()
{
  testCanChoose();
  return 0;
}
