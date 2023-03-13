#include <iostream>
#include <unordered_map>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
   // 满足(x - y) % p = 0，则称 x 与 y 模 p 同余，记 x ≡ y (mod p)

   // 设所有元素和为x，去掉的元素和为y
   // 要使得 (x - y) % p = 0，等价于 x 与 y 模 p 同余
  int minSubarray(vector<int> &nums, int p)
  {
    int N = nums.size();
    int ans = N;
    vector<int> sum(N + 1);
    for (int i = 0; i < N; i++)
    {
      sum[i + 1] = (sum[i] + nums[i]) % p;
    }

    int x = sum[N];
    unordered_map<int, int> map;
    for (int i = 0; i <= N; i++)
    {
      map[sum[i]] = i;
      // 等价于在前缀数组上找 s[left] 和 s[right]
      // 满足right - left最小，且 s[right] - s[left] ≡ x (mod p)
      // 枚举right = i，尝试找left
      auto it = map.find((sum[i] - x + p) % p);
      if (it != map.end())
      {
        // 如果找到，就取最小区间
        ans = std::min(ans, i - it->second);
      }
    }

    return ans < N ? ans : -1;
  }
};

void testMinSubarray()
{
  Solution s;
  vector<int> n1 = {3, 1, 4, 2};
  vector<int> n2 = {6, 3, 5, 2};
  vector<int> n3 = {1, 2, 3};
  EXPECT_EQ_INT(1, s.minSubarray(n1, 6));
  EXPECT_EQ_INT(2, s.minSubarray(n2, 9));
  EXPECT_EQ_INT(0, s.minSubarray(n3, 3));
  EXPECT_SUMMARY;
}

int main()
{
  testMinSubarray();
  return 0;
}
