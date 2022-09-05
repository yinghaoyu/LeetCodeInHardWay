#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int numSpecial(vector<vector<int>> &mat)
  {
    int N = mat.size();
    int M = mat[0].size();
    vector<int> rowSum(N);
    vector<int> colSum(M);
    int ans = 0;
    for (int i = 0; i < N; i++)
    {
      for (int j = 0; j < M; j++)
      {
        rowSum[i] += mat[i][j];
        colSum[j] += mat[i][j];
      }
    }
    for (int i = 0; i < N; i++)
    {
      for (int j = 0; j < M; j++)
      {
        if (mat[i][j] == 1 && rowSum[i] == 1 && colSum[j] == 1)
        {
          ans++;
        }
      }
    }
    return ans;
  }
};

void testNumSpecial()
{
  Solution s;
  vector<vector<int>> mat1 = {{1, 0, 0}, {0, 0, 1}, {1, 0, 0}};
  vector<vector<int>> mat2 = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
  EXPECT_EQ_INT(1, s.numSpecial(mat1));
  EXPECT_EQ_INT(3, s.numSpecial(mat2));
  EXPECT_SUMMARY;
}

int main()
{
  testNumSpecial();
  return 0;
}
