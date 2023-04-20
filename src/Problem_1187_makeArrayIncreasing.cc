#include <algorithm>
#include <cstdint>
#include <functional>
#include <iostream>
#include <unordered_map>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  // 递归 + 记忆化搜索
  int makeArrayIncreasing(vector<int> &arr1, vector<int> &arr2)
  {
    std::sort(arr2.begin(), arr2.end());
    int n = arr1.size();
    unordered_map<int, int> map[n];
    std::function<int(int, int)> dfs = [&](int i, int pre) -> int {
      if (i < 0)
      {
        return 0;
      }
      auto it = map[i].find(pre);
      if (it != map[i].end())
      {
        // 记忆化搜索
        return it->second;
      }
      // 不替换 arr1[i]
      int min = arr1[i] < pre ? dfs(i - 1, arr1[i]) : INT32_MAX;
      int k = binSearch(arr2, pre);
      if (k != -1)
      {
        // 选
        int p2 = dfs(i - 1, arr2[k]);
        if (p2 != INT32_MAX)
        {
          min = std::min(min, p2 + 1);
        }
      }
      map[i][pre] = min;
      return min;
    };
    int ans = dfs(n - 1, INT32_MAX);
    return ans < INT32_MAX ? ans : -1;
  }

  int binSearch(vector<int> &arr, int value)
  {
    int index = -1;
    int l = 0;
    int r = arr.size() - 1;
    while (l <= r)
    {
      int m = (r - l) / 2 + l;
      if (arr[m] >= value)
      {
        r = m - 1;
      }
      else
      {
        index = m;
        l = m + 1;
      }
    }
    return index;
  }
  // TODO: dp
};

void testMakeArrayIncreasing()
{
  Solution s;
  vector<int> n1 = {1, 5, 3, 6, 7};
  vector<int> n2 = {1, 3, 2, 4};
  vector<int> n3 = {4, 3, 1};
  vector<int> n4 = {1, 6, 3, 3};
  EXPECT_EQ_INT(1, s.makeArrayIncreasing(n1, n2));
  EXPECT_EQ_INT(2, s.makeArrayIncreasing(n1, n3));
  EXPECT_EQ_INT(-1, s.makeArrayIncreasing(n1, n4));
  EXPECT_SUMMARY;
}

int main()
{
  testMakeArrayIncreasing();
  return 0;
}
