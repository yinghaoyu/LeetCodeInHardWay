#include <numeric>
#include <unordered_map>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 private:
  // key: 某行
  // value: 第一次遇到石头的编号
  unordered_map<int, int> rowFirst;

  unordered_map<int, int> colFirst;

  vector<int> father;

  int number;

 private:
  void build(int n)
  {
    rowFirst.clear();
    colFirst.clear();
    father.resize(n);
    std::iota(father.begin(), father.end(), 0);
    number = n;
  }

  int find(int i)
  {
    if (i != father[i])
    {
      father[i] = find(father[i]);
    }
    return father[i];
  }

  void unions(int x, int y)
  {
    int fx = find(x);
    int fy = find(y);
    if (fx != fy)
    {
      father[fx] = fy;
      number--;
    }
  }

 public:
  int removeStones(vector<vector<int>>& stones)
  {
    int n = stones.size();
    build(n);
    for (int i = 0; i < n; i++)
    {
      int row = stones[i][0];
      int col = stones[i][1];
      if (!rowFirst.count(row))
      {
        rowFirst[row] = i;
      }
      else
      {
        unions(i, rowFirst[row]);
      }
      if (!colFirst.count(col))
      {
        colFirst[col] = i;
      }
      else
      {
        unions(i, colFirst[col]);
      }
    }
    return n - number;
  }
};

void test()
{
  Solution s;
  vector<vector<int>> s1 = {{0, 0}, {0, 1}, {1, 0}, {1, 2}, {2, 1}, {2, 2}};
  vector<vector<int>> s2 = {{0, 0}, {0, 2}, {1, 1}, {2, 0}, {2, 2}};
  vector<vector<int>> s3 = {{0, 0}};
  EXPECT_EQ_INT(5, s.removeStones(s1));
  EXPECT_EQ_INT(3, s.removeStones(s2));
  EXPECT_EQ_INT(0, s.removeStones(s3));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
