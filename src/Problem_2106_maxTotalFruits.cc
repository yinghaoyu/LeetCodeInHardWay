#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  // 滑动窗口
  int maxTotalFruits(vector<vector<int>> &fruits, int startPos, int k)
  {
    int max = 0;
    for (int i = 0, j = 0, sum = 0; i < fruits.size(); sum -= fruits[i++][1])
    {
      // 先向左走，再向右走
      while (j < fruits.size() && 2 * std::max(startPos - fruits[i][0], 0) + std::max(fruits[j][0] - startPos, 0) <= k)
      {
        max = std::max(max, sum += fruits[j++][1]);
      }
    }
    for (int i = 0, j = 0, sum = 0; i < fruits.size(); sum -= fruits[i++][1])
    {
      // 先向右走，再向左走
      while (j < fruits.size() && std::max(startPos - fruits[i][0], 0) + 2 * std::max(fruits[j][0] - startPos, 0) <= k)
      {
        max = std::max(max, sum += fruits[j++][1]);
      }
    }
    return max;
  }
};

void testMaxTotalFruits()
{
  Solution s;
  vector<vector<int>> n1 = {{2, 8}, {6, 3}, {8, 6}};
  vector<vector<int>> n2 = {{0, 9}, {4, 1}, {5, 7}, {6, 2}, {7, 4}, {10, 9}};
  vector<vector<int>> n3 = {{0, 3}, {6, 4}, {8, 5}};
  EXPECT_EQ_INT(9, s.maxTotalFruits(n1, 5, 4));
  EXPECT_EQ_INT(14, s.maxTotalFruits(n2, 5, 4));
  EXPECT_EQ_INT(0, s.maxTotalFruits(n3, 3, 2));
  EXPECT_SUMMARY;
}

int main()
{
  testMaxTotalFruits();
  return 0;
}
