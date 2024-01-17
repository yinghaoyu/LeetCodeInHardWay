#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  // TODO: figure it out.
  int minSwapsCouples(vector<int>& row)
  {
    int n = row.size();
    build(n / 2);
    for (int i = 0; i < n; i += 2)
    {
      unionXY(row[i] / 2, row[i + 1] / 2);
    }
    return n / 2 - nums;
  }

 private:
  void build(int m)
  {
    father = vector<int>(m);
    for (int i = 0; i < m; i++)
    {
      father[i] = i;
    }
    nums = m;
  }

  int find(int i)
  {
    if (i != father[i])
    {
      father[i] = find(father[i]);
    }
    return father[i];
  }

  void unionXY(int x, int y)
  {
    int fx = find(x);
    int fy = find(y);
    if (fx != fy)
    {
      father[fx] = fy;
      nums--;
    }
  }
  int nums;
  vector<int> father;
};

void test()
{
  Solution s;
  vector<int> r1 = {0, 2, 1, 3};
  vector<int> r2 = {3, 2, 0, 1};
  EXPECT_EQ_INT(1, s.minSwapsCouples(r1));
  EXPECT_EQ_INT(0, s.minSwapsCouples(r2));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
