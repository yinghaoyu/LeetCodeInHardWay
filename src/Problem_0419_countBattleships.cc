#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int countBattleships(vector<vector<char>> &board)
  {
    int ans = 0;
    for (int i = 0; i < board.size(); i++)
    {
      for (int j = 0; j < board[0].size(); j++)
      {
        if (board[i][j] == 'X' && (i == 0 || board[i - 1][j] != 'X') && (j == 0 || board[i][j - 1] != 'X'))
        {
          // 找到战舰头即可
          ans++;
        }
      }
    }
    return ans;
  }
};

void testCountBattleships()
{
  Solution s;
  vector<vector<char>> n1 = {{'X', '.', '.', 'X'}, {'.', '.', '.', 'X'}, {'.', '.', '.', 'X'}};
  vector<vector<char>> n2 = {{'.'}};
  EXPECT_EQ_INT(2, s.countBattleships(n1));
  EXPECT_EQ_INT(0, s.countBattleships(n2));
  EXPECT_SUMMARY;
}

int main()
{
  testCountBattleships();
  return 0;
}
