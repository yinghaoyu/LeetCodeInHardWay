#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution
{
 public:
  vector<int> successfulPairs(vector<int>& spells, vector<int>& potions, long long success)
  {
    int n = spells.size();
    int m = potions.size();
    vector<int> idx(n);
    for (int i = 0; i < n; i++)
    {
      idx[i] = i;
    }
    // 根据咒语强度从小到大排序
    std::sort(idx.begin(), idx.end(), [&](int i, int j) { return spells[i] < spells[j]; });
    std::sort(potions.begin(), potions.end());
    vector<int> pairs(n);
    int left = 0;
    int right = n - 1;
    int mid = 0;
    while (left <= right)
    {
      mid = left + (right - left) / 2;
      // 如果 咒语强度 * 药水最大强度 < 成功阈值的话，说明这个咒语永远达不到要求
      if ((long long) spells[idx[mid]] * potions[m - 1] < success)
      {
        left = mid + 1;
      }
      else
      {
        right = mid - 1;
      }
    }
    for (int i = 0; i < left; i++)
    {
      // 小于这个强度的咒语都是达不到要求的
      pairs[idx[i]] = 0;
    }
    for (int i = left; i < n; i++)
    {
      left = 0;
      right = m - 1;
      while (left <= right)
      {
        mid = left + (right - left) / 2;
        // 找到药水强度的阈值，>= 这个阈值的药水都符合
        if ((long long) spells[idx[i]] * potions[mid] < success)
        {
          left = mid + 1;
        }
        else
        {
          right = mid - 1;
        }
      }
      pairs[idx[i]] = m - left;
    }
    return pairs;
  }
};
