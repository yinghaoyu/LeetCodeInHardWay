#include <type_traits>
#include <vector>

using namespace std;

class Solution
{
 public:
  void wiggleSort(vector<int>& nums)
  {
    int n = nums.size();
    // 假设我们以峰、谷、峰顺序生成数组
    for (int i = 1; i < n; i++)
    {
      if (i & 1)
      {
        // 当前位置理应是谷，但是实际却大于前面的，则交换
        if (nums[i] > nums[i - 1])
        {
          std::swap(nums[i], nums[i - 1]);
        }
      }
      else
      {
        // 当前位置理应是峰，但是实际却小于前面的，则交换
        if (nums[i] < nums[i - 1])
        {
          std::swap(nums[i], nums[i - 1]);
        }
      }
    }
  }
};
