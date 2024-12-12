#include <vector>

#include "UnitTest.h"

using namespace std;

// 摩尔投票
class Solution
{
 public:
  int majorityElement(vector<int>& nums)
  {
    int hp = 0;
    int candidate = 0;
    for (auto& num : nums)
    {
      // 一次删掉两个不同的数
      if (hp == 0)
      {
        candidate = num;
        hp++;
      }
      else
      {
        hp += num == candidate ? 1 : -1;
      }
    }
    // 剩下的数不一定是多数元素，需要检查
    // {2, 3, 2, 3} 这种是不存在出现次数大于 n/2 的元素的
    if (hp == 0)
    {
      // 没数剩下来
      return -1;
    }
    // {1, 2, 3, 1, 2, 3, 1} 这种情况 hp > 0，但是 1 的出现次数显然没有大于 7/2 = 3 个
    // 验证出现的次数
    hp = 0;
    for (auto& num : nums)
    {
      if (num == candidate)
      {
        hp++;
      }
    }
    return hp > nums.size() / 2 ? candidate : -1;
  }
};

void testMajorityElement()
{
  Solution s;
  vector<int> n1 = {3, 2, 3};
  vector<int> n2 = {2, 2, 1, 1, 1, 2, 2};
  EXPECT_EQ_INT(3, s.majorityElement(n1));
  EXPECT_EQ_INT(2, s.majorityElement(n2));
  EXPECT_SUMMARY;
}

int main()
{
  testMajorityElement();
  return 0;
}
