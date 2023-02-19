#include <iostream>
#include <ostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  vector<vector<int>> generate(int numRows)
  {
    // 初始时每行头先填上 1
    vector<vector<int>> ans(numRows, vector<int>(1, 1));
    for (int i = 1; i < numRows; i++)
    {
      for (int j = 1; j < i; j++)
      {
        ans[i].push_back(ans[i - 1][j - 1] + ans[i - 1][j]);
      }
      // 每行尾部填上 1
      ans[i].push_back(1);
    }
    return ans;
  }
};

void testGenerate()
{
  Solution s;
  vector<vector<int>> o1 = {{1}, {1, 1}, {1, 2, 1}, {1, 3, 3, 1}, {1, 4, 6, 4, 1}};
  vector<vector<int>> o2 = {{1}};
  EXPECT_TRUE(o1 == s.generate(5));
  EXPECT_TRUE(o2 == s.generate(1));
  EXPECT_SUMMARY;
}

int main()
{
  testGenerate();
  return 0;
}
