#include <unordered_map>
#include <vector>

using namespace std;

class Solution
{
 public:
  long long numberOfPairs(vector<int>& nums1, vector<int>& nums2, int k)
  {
    unordered_map<int, int> map1;
    unordered_map<int, int> map2;
    int max1 = 0;
    for (int num : nums1)
    {
      // 记录 nums1 数组内的最大值
      max1 = std::max(num, max1);
      // 统计 nums1 频次
      map1[num]++;
    }
    for (int num : nums2)
    {
      // 统计 nums2 频次
      map2[num]++;
    }
    long long ans = 0;
    for (auto& [a, cnt] : map2)
    {
      // 枚举在 num2 数组内的数
      // 检查对应的 a * k 倍数是否在 nums1 数组内，检查范围由 num1 数组的最大值限制
      // 这里主要是把 O(m * n) 的时间复杂度降下来
      for (int b = a * k; b <= max1; b += a * k)
      {
        if (map1.count(b) > 0)
        {
          ans += 1L * map1[b] * cnt;
        }
      }
    }
    return ans;
  }
};
