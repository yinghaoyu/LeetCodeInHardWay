#include <iostream>
#include <queue>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 private:
  class Node
  {
   public:
    int value;
    int row;
    int col;

    Node()
    {
      value = -1;
      row = -1;
      col = -1;
    }

    Node(int v, int r, int c)
    {
      value = v;
      row = r;
      col = c;
    }

    bool operator<(const Node &other) const { return this->value > other.value; }
  };

  class Info
  {
   public:
    int near;
    int num;

    Info()
    {
      near = -1;
      num = -1;
    }

    Info(int n1, int n2)
    {
      near = n1;
      num = n2;
    }
  };

 public:
  int kthSmallest1(vector<vector<int>> &matrix, int k)
  {
    int N = matrix.size();
    int M = matrix[0].size();
    priority_queue<Node> q;
    vector<vector<bool>> set(N, vector<bool>(M));
    q.push(Node(matrix[0][0], 0, 0));
    set[0][0] = true;
    int count = 0;
    Node ans;
    while (!q.empty())
    {
      ans = q.top();
      q.pop();
      if (++count == k)
      {
        break;
      }
      int row = ans.row;
      int col = ans.col;
      if (row + 1 < N && !set[row + 1][col])
      {
        q.push(Node(matrix[row + 1][col], row + 1, col));
        set[row + 1][col] = true;
      }
      if (col + 1 < M && !set[row][col + 1])
      {
        q.push(Node(matrix[row][col + 1], row, col + 1));
        set[row][col + 1] = true;
      }
    }
    return ans.value;
  }

  int kthSmallest2(vector<vector<int>> &matrix, int k)
  {
    int N = matrix.size();
    int M = matrix[0].size();
    int left = matrix[0][0];
    int right = matrix[N - 1][M - 1];
    int ans = 0;
    while (left <= right)
    {
      int mid = left + (right - left) / 2;
      Info info = noMoreNum(matrix, mid);
      if (info.num < k)
      {
        left = mid + 1;
      }
      else
      {
        ans = info.near;
        right = mid - 1;
      }
    }
    return ans;
  }

  Info noMoreNum(vector<vector<int>> &matrix, int value)
  {
    int near = INT32_MIN;
    int num = 0;
    int N = matrix.size();
    int M = matrix[0].size();
    int row = 0;
    int col = M - 1;
    while (row < N && col >= 0)
    {
      if (matrix[row][col] <= value)
      {
        near = std::max(near, matrix[row][col]);
        num += col + 1;
        row++;
      }
      else
      {
        col--;
      }
    }
    return Info(near, num);
  }
};

void testKthSmallest()
{
  Solution s;
  vector<vector<int>> m1 = {{1, 5, 9}, {10, 11, 13}, {12, 13, 15}};
  vector<vector<int>> m2 = {{-5}};
  EXPECT_EQ_INT(13, s.kthSmallest1(m1, 8));
  EXPECT_EQ_INT(-5, s.kthSmallest1(m2, 1));
  EXPECT_EQ_INT(13, s.kthSmallest2(m1, 8));
  EXPECT_EQ_INT(-5, s.kthSmallest2(m2, 1));
  EXPECT_SUMMARY;
}

int main()
{
  testKthSmallest();
  return 0;
}
