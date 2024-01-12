#include <algorithm>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  // 贪心算法
  // 时间复杂度O(n * logn)，因为有排序，额外空间复杂度O(
  int findRadius(vector<int>& houses, vector<int>& heaters)
  {
    std::sort(houses.begin(), houses.end());
    std::sort(heaters.begin(), heaters.end());
    int ans = 0;
    for (int i = 0, j = 0; i < houses.size(); i++)
    {
      // i号房屋
      // j号供暖器
      while (!best(houses, heaters, i, j))
      {
        j++;
      }
      ans = std::max(ans, std::abs(heaters[j] - houses[i]));
    }
    return ans;
  }

  // 这个函数含义：
  // 当前的地点houses[i]由heaters[j]来供暖是最优的吗？
  // 当前的地点houses[i]由heaters[j]来供暖，产生的半径是a
  // 当前的地点houses[i]由heaters[j + 1]来供暖，产生的半径是b
  // 如果a < b, 说明是最优，供暖不应该跳下一个位置
  // 如果a >= b, 说明不是最优，应该跳
  bool best(vector<int>& houses, vector<int>& heaters, int i, int j)
  {
    return j == heaters.size() - 1 || std::abs(heaters[j] - houses[i]) < std::abs(heaters[j + 1] - houses[i]);
  }
};

void test()
{
  Solution s;
  vector<int> h1 = {1, 2, 3};
  vector<int> p1 = {2};
  vector<int> h2 = {1, 2, 3, 4};
  vector<int> p2 = {1, 4};
  vector<int> h3 = {1, 5};
  vector<int> p3 = {2};
  EXPECT_EQ_INT(1, s.findRadius(h1, p1));
  EXPECT_EQ_INT(1, s.findRadius(h2, p2));
  EXPECT_EQ_INT(3, s.findRadius(h3, p3));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
