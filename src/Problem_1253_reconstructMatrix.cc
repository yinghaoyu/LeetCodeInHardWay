#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  // 递归超时
  bool process(vector<vector<int>> &ans, int upper, int lower, vector<int> &colsum, int index)
  {
    if (index == colsum.size())
    {
      return upper == 0 && lower == 0;
    }
    if (colsum[index] == 0)
    {
      ans[0][index] = 0;
      ans[1][index] = 0;
      return process(ans, upper, lower, colsum, index + 1);
    }
    else if (colsum[index] == 2)
    {
      ans[0][index] = 1;
      ans[1][index] = 1;
      return process(ans, upper - 1, lower - 1, colsum, index + 1);
    }
    else
    {
      ans[0][index] = 1;
      ans[1][index] = 0;
      if (process(ans, upper - 1, lower, colsum, index + 1))
      {
        return true;
      }
      ans[0][index] = 0;
      ans[1][index] = 1;
      return process(ans, upper, lower - 1, colsum, index + 1);
    }
  }

  vector<vector<int>> recursive(int upper, int lower, vector<int> &colsum)
  {
    int n = colsum.size();
    vector<vector<int>> ans(2, vector<int>(n));
    bool ret = process(ans, upper, lower, colsum, 0);
    return ret ? ans : vector<vector<int>>{};
  }

  // 贪心
  vector<vector<int>> reconstructMatrix(int upper, int lower, vector<int> &colsum)
  {
    int n = colsum.size();
    int sum = 0;
    int two = 0;
    for (int i = 0; i < n; i++)
    {
      if (colsum[i] == 2)
      {
        ++two;
      }
      sum += colsum[i];
    }
    if (sum != upper + lower || std::min(upper, lower) < two)
    {
      return {};
    }
    upper -= two;
    lower -= two;
    vector<vector<int>> ans(2, vector<int>(n));
    for (int i = 0; i < n; i++)
    {
      if (colsum[i] == 2)
      {
        ans[0][i] = 1;
        ans[1][i] = 1;
      }
      else if (colsum[i] == 1)
      {
        if (upper > 0)
        {
          ans[0][i] = 1;
          --upper;
        }
        else
        {
          ans[1][i] = 1;
        }
      }
    }
    return ans;
  }
};

void test()
{
  Solution s;
  vector<int> c1 = {1, 1, 1};
  vector<vector<int>> o1 = {{1, 1, 0}, {0, 0, 1}};
  vector<int> c2 = {2, 2, 1, 1};
  vector<vector<int>> o2 = {};
  vector<int> c3 = {2, 1, 2, 0, 1, 0, 1, 2, 0, 1};
  vector<vector<int>> o3 = {{1, 1, 1, 0, 1, 0, 0, 1, 0, 0}, {1, 0, 1, 0, 0, 0, 1, 1, 0, 1}};

  EXPECT_TRUE(o1 == s.reconstructMatrix(2, 1, c1));
  EXPECT_TRUE(o2 == s.reconstructMatrix(2, 3, c2));
  EXPECT_TRUE(o3 == s.reconstructMatrix(5, 5, c3));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
