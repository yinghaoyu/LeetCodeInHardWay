#include <algorithm>
#include <vector>

using namespace std;

// 每次操作既可以理解为使 n−1 个元素增加 1，也可以理解使 1 个元素减少 1
class Solution
{
 public:
  int minMoves(vector<int>& nums)
  {
    int minNum = *min_element(nums.begin(), nums.end());
    int ans = 0;

    for (int num : nums)
    {
      ans += num - minNum;
    }

    return ans;
  }
};
