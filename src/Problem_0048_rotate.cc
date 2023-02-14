#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  void rotate(vector<vector<int>> &matrix)
  {
    // 左上方坐标
    int tR = 0;
    int tC = 0;
    // 右下方坐标
    int dR = matrix.size();
    int dC = matrix[0].size();
    // print(matrix);
    while (tR < dR)
    {
      rotateRectangle(matrix, tR++, tC++, --dR, --dC);
    }
  }

  void rotateRectangle(vector<vector<int>> &matrix, int tR, int tC, int dR, int dC)
  {
    for (int j = 0; j < dC - tC; j++)
    {
      int tmp = matrix[tR][tC + j];
      matrix[tR][tC + j] = matrix[dR - j][tC];
      matrix[dR - j][tC] = matrix[dR][dC - j];
      matrix[dR][dC - j] = matrix[tR + j][dC];
      matrix[tR + j][dC] = tmp;
    }
    // print(matrix);
  }

  void print(vector<vector<int>> &matrix)
  {
    for (int i = 0; i < matrix.size(); i++)
    {
      for (int j = 0; j < matrix[0].size(); j++)
      {
        cout << matrix[i][j] << " ";
      }
      cout << endl;
    }
    cout << endl;
  }
};

bool isVectorEqual(vector<vector<int>> a, vector<vector<int>> b)
{
  return a == b;
}

void testRotate()
{
  Solution s;
  vector<vector<int>> n1 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  vector<vector<int>> o1 = {{7, 4, 1}, {8, 5, 2}, {9, 6, 3}};
  vector<vector<int>> n2 = {{5, 1, 9, 11}, {2, 4, 8, 10}, {13, 3, 6, 7}, {15, 14, 12, 16}};
  vector<vector<int>> o2 = {{15, 13, 2, 5}, {14, 3, 4, 1}, {12, 6, 8, 9}, {16, 7, 10, 11}};
  s.rotate(n1);
  s.rotate(n2);
  EXPECT_TRUE(isVectorEqual(o1, n1));
  EXPECT_TRUE(isVectorEqual(o2, n2));
  EXPECT_SUMMARY;
}

int main()
{
  testRotate();
  return 0;
}
