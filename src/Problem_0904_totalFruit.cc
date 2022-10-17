#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  //找至多包含两种元素的最长子串，返回其长度
  int totalFruit(vector<int> &fruits)
  {
    int left = 0, right = 0, ans = 0;
    // a表示篮子1号，b表示篮子2号
    int a = fruits[left], b = fruits[right];
    int N = fruits.size();
    while (right < N)
    {
      if (fruits[right] == b || fruits[right] == a)
      {
        ans = std::max(ans, right + 1 - left);
        right++;
      }
      else
      {
        // 种类超过2种
        left = right - 1;
        // 更新第1个篮子
        a = fruits[left];
        while (left >= 1 && fruits[left - 1] == a)
        {
          // 符合条件的窗口回退
          left--;
        }
        // 更新第2个篮子
        b = fruits[right];
        ans = std::max(ans, right + 1 - left);
      }
    }
    return ans;
  }
};

void testTotalFruit()
{
  Solution s;
  vector<int> f1 = {1, 2, 1};
  vector<int> f2 = {0, 1, 2, 2};
  vector<int> f3 = {1, 2, 3, 2, 2};

  EXPECT_EQ_INT(3, s.totalFruit(f1));
  EXPECT_EQ_INT(3, s.totalFruit(f2));
  EXPECT_EQ_INT(4, s.totalFruit(f3));

  EXPECT_SUMMARY;
}

int main()
{
  testTotalFruit();
  return 0;
}
