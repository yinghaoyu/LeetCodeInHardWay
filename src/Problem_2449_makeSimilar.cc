#include <algorithm>
#include <vector>

using namespace std;

// TODO: figure it out.
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
    return ans / 4;
  }
};
