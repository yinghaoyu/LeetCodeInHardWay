#include <assert.h>
#include <algorithm>
#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int search(vector<int> &arr, int value)
  {
    int l = 0;
    int r = arr.size() - 1;
    int index = -1;
    while (l <= r)
    {
      int m = l + (r - l) / 2;
      // 当有连续一串大于value时，右窗口左移
      if (arr[m] > value)
      {
        index = m;
        r = m - 1;
      }
      else
      {
        l = m + 1;
      }
    }
    return index;
  }

  // 超时
  vector<int> advantageCount1(vector<int> nums1, vector<int> nums2)
  {
    vector<int> ans;
    std::sort(nums1.begin(), nums1.end());
    for (int i = 0; i < nums2.size(); i++)
    {
      // 针对num2的每个元素，从num1中二分找最优解
      int index = search(nums1, nums2[i]);
      if (index != -1)
      {
        ans.push_back(nums1[index]);
        nums1.erase(nums1.begin() + index);
      }
      else
      {
        ans.push_back(nums1[0]);
        nums1.erase(nums1.begin());
      }
    }
    return ans;
  }

  vector<int> advantageCount2(vector<int> nums1, vector<int> nums2)
  {
    int N = nums1.size();
    vector<int> idx(N);  // nums2的索引
    for (int i = 0; i < N; i++)
    {
      idx[i] = i;
    }
    std::sort(nums1.begin(), nums1.end());
    // 根据nums2升序，对索引排序
    std::sort(idx.begin(), idx.end(), [&](int i, int j) { return nums2[i] < nums2[j]; });
    int L = 0;
    int R = N - 1;
    for (int i = 0; i < N; i++)
    {
      if (nums1[i] > nums2[idx[L]])
      {
        // 贪心
        // 先匹配小的nums2，那么后面可以得到的优势更大
        nums2[idx[L++]] = nums1[i];
      }
      else
      {
        // idx根据nums2升序排序，若存在不匹配项
        // nums2中不匹配的元素实际上是原先nums2的一个后缀，因为后面的元素更大
        // 因此当nums1的首个元素无法配对时，我们给它配对一个nums2的尾元素即可
        nums2[idx[R--]] = nums1[i];
      }
    }
    return nums2;
  }
};

int checkAdvantage(vector<int> a, vector<int> b)
{
  int ans = 0;
  assert(a.size() == b.size());
  for (int i = 0; i < a.size(); i++)
  {
    if (a[i] > b[i])
    {
      ans++;
    }
  }
  return ans;
}

void testAdvantageCount()
{
  Solution s;
  vector<int> nums1 = {2, 7, 11, 15};
  vector<int> nums2 = {1, 10, 4, 11};

  vector<int> nums3 = {12, 24, 8, 32};
  vector<int> nums4 = {13, 25, 32, 11};

  EXPECT_EQ_INT(4, checkAdvantage(s.advantageCount1(nums1, nums2), nums2));
  EXPECT_EQ_INT(3, checkAdvantage(s.advantageCount1(nums3, nums4), nums4));

  EXPECT_EQ_INT(4, checkAdvantage(s.advantageCount2(nums1, nums2), nums2));
  EXPECT_EQ_INT(3, checkAdvantage(s.advantageCount2(nums3, nums4), nums4));
  EXPECT_SUMMARY;
}

int main()
{
  testAdvantageCount();
  return 0;
}
