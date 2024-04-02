#include <vector>

using namespace std;

class Solution
{
 public:
  // 超级水王问题，摩尔投票问题
  int majorityElement(vector<int>& nums)
  {
    // 血量
    int hp = 0;
    // 候选人
    int candidate = 0;
    for (int num : nums)
    {
      if (hp == 0)
      {
        // 血量为0，重新推举候选人
        candidate = num;
        hp = 1;
      }
      else
      {
        // 不同的数两两相消
        hp += candidate != num ? -1 : 1;
      }
    }

    if (hp == 0)
    {
      return -1;
    }

    // 为什么要重新遍历一遍？
    // 比如 {1,2,1,2,3,3}
    hp = 0;
    for (int num : nums)
    {
      if (num == candidate)
      {
        hp++;
      }
    }
    if (hp > nums.size() / 2)
    {
      return candidate;
    }
    return -1;
  }
};
