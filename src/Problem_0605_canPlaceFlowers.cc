#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  bool canPlaceFlowers(vector<int> &flowerbed, int n)
  {
    int m = flowerbed.size();
    for (int i = 0; i < m; i++)
    {
      // 种花需要满足 flowerbed[i-1] flowerbed[i] flowerbed[i+1] 均为 0
      if ((i == 0 || flowerbed[i - 1] == 0) && flowerbed[i] == 0 && (i == m - 1 || flowerbed[i + 1] == 0))
      {
        n--;
        i++;  // 下一个位置肯定不能种花，直接跳过
      }
    }
    return n <= 0;
  }
};

void test()
{
  Solution s;
  vector<int> f1 = {1, 0, 0, 0, 1};
  vector<int> f2 = {1, 0, 0, 0, 1};
  EXPECT_TRUE(s.canPlaceFlowers(f1, 1));
  EXPECT_FALSE(s.canPlaceFlowers(f1, 2));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
