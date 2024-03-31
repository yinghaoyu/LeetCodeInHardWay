#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  //   原数组row      [6, 0, 1, 5, 2, 3, 8, 4, 7, 9]
  // 对应的情侣编号    3  0  0  2  1  1  4  2  3  4
  // 让相邻的情侣编号两两 union 得到 {3, 0, 2, 4} 和 {1}
  // 每个情侣编号集合需要 k - 1次交换(k为集合元素数量)，才能满足题设条件
  // 比如{3,0,2,4}需要 3 次交换，{1} 需要 0 次交换，总共需要 3 + 0 = 4 次交换
  // 怎么理解？ {1} 表示原数组row内的 2, 3 情侣，这两人位置已满足条件，需要 0 次交换
  //            {3, 0, 2, 4} 表示 {6, 0, 1, 5, _, _, 8, 4, 7, 9}，把满足的 2,3 用_代替
  //                      交换1次 {6, 7, 1, 5, _, _, 8, 4, 0, 9}
  //                      交换2次 {6, 7, 1, 5, _, _, 0, 4, 8, 9}
  //                      交换3次 {6, 7, 1, 4, _, _, 0, 1, 8, 9} 全部元素满足条件
  // 一般性，
  // 总共有n对情侣，把相邻的情侣两两 union 后，得到 x 个情侣编号集合，
  // 每个集合各有 a,b,c ... f,g 个元素，
  // 那么需要交换的次数有 (a - 1) + (b - 1) + (c - 1) + ... + (f - 1) + (g - 1)，
  // 优化
  // 由于 a + b + c + d + ... + f + g = n
  // 因此需要交换的次数  (a - 1) + (b - 1) + (c - 1) + ... + (f - 1) + (g - 1) = n - x
  int minSwapsCouples(vector<int>& row)
  {
    int n = row.size();
    // 一共有 n / 2 对情侣
    build(n / 2);
    for (int i = 0; i < n; i += 2)
    {
      // 把每队情侣合并
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
