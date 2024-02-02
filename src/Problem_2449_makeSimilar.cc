#include <algorithm>
#include <vector>

using namespace std;

class Solution
{
 private:
  // 把数组分割成左部分全是奇数，右部分全是偶数
  // 返回左部分的长度
  int split(vector<int>& arr)
  {
    int oddSize = 0;
    for (int i = 0; i < arr.size(); i++)
    {
      if (arr[i] & 1)
      {
        std::swap(arr[i], arr[oddSize++]);
      }
    }
    return oddSize;
  }

 public:
  // 首先，+2 和 -2操作不会改变奇偶性
  // 其次，两个数相差的越小，需要的操作数越少
  // 因此可以把奇数和偶数分组，再两两配对
  long long makeSimilar(vector<int>& nums, vector<int>& target)
  {
    int n = nums.size();
    int oddSize = split(nums);
    split(target);
    std::sort(nums.begin(), nums.begin() + oddSize);
    std::sort(nums.begin() + oddSize, nums.end());
    std::sort(target.begin(), target.begin() + oddSize);
    std::sort(target.begin() + oddSize, target.end());
    long ans = 0;
    for (int i = 0; i < n; i++)
    {
      ans += std::abs(nums[i] - target[i]);
    }
    // 1次操作 +2 和 -2 操作使得值相差 4
    return ans / 4;
  }
};
