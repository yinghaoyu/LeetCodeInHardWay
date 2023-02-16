#include <string>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  bool process(vector<vector<char>> &board, int i, int j, string &word, int w)
  {
    if (w == word.length())
    {
      return true;
    }
    if (i < 0 || i == board.size() || j < 0 || j == board[0].size())
    {
      return false;
    }
    if (board[i][j] != word[w])
    {
      return false;
    }
    char tmp = board[i][j];
    board[i][j] = 0;
    bool p = process(board, i - 1, j, word, w + 1) || process(board, i + 1, j, word, w + 1) || process(board, i, j - 1, word, w + 1) ||
             process(board, i, j + 1, word, w + 1);
    board[i][j] = tmp;
    return p;
  }

  bool exist(vector<vector<char>> &board, string word)
  {
    for (int i = 0; i < board.size(); i++)
    {
      for (int j = 0; j < board[0].size(); j++)
      {
        if (process(board, i, j, word, 0))
        {
          return true;
        }
      }
    }
    return false;
  }
};

void testExist()
{
  Solution s;
  vector<vector<char>> b1 = {{'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}};
  vector<vector<char>> b2 = {{'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}};
  vector<vector<char>> b3 = {{'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}};
  EXPECT_TRUE(s.exist(b1, "ABCCED"));
  EXPECT_TRUE(s.exist(b2, "SEE"));
  EXPECT_FALSE(s.exist(b2, "ABCB"));
  EXPECT_SUMMARY;
}

int main()
{
  testExist();
  return 0;
}
