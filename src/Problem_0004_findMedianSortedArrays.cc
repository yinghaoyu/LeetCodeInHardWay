#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  // 普通解法思路：先把两个有序数组合并，合并数组长度为奇数，取中点值
  // 合并长度为偶数取(上中位数 + 下中位数) / 2， 时间和空间复杂度都是O(M+N)
  double findMedianSortedArrays1(vector<int> &nums1, vector<int> &nums2)
  {
    int i = 0;
    int j = 0;
    int index = 0;
    int n = nums1.size();
    int m = nums2.size();
    vector<int> num(n + m);
    while (i < n && j < m)
    {
      num[index++] = nums1[i] < nums2[j] ? nums1[i++] : nums2[j++];
    }
    while (i < n)
    {
      num[index++] = nums1[i++];
    }
    while (j < m)
    {
      num[index++] = nums2[j++];
    }
    return median(num);
  }

  double median(vector<int> &arr)
  {
    if (arr.size() & 1)
    {
      return (double) arr[arr.size() / 2];
    }
    else
    {
      return (double) (arr[arr.size() / 2] + arr[arr.size() / 2 - 1]) / 2;
    }
  }

  // 这里提供一个 O(log(M+N)) 的解法
  double findMedianSortedArrays2(vector<int> &nums1, vector<int> &nums2)
  {
    int size = nums1.size() + nums2.size();
    bool even = (size & 1) == 0;
    if (nums1.size() != 0 && nums2.size() != 0)
    {
      if (even)
      {
        // 合并后的数组长度如果是偶数，则返回（上中位数+下中位数）/ 2的值
        return (double) (findKthNum(nums1, nums2, size / 2) + findKthNum(nums1, nums2, size / 2 + 1)) / 2;
      }
      else
      {
        // 合并后的数组长度是奇数，则取中间这个数
        return findKthNum(nums1, nums2, size / 2 + 1);
      }
    }
    else if (nums1.size() != 0)
    {
      if (even)
      {
        return (double) (nums1[(size - 1) / 2] + nums1[size / 2]) / 2;
      }
      else
      {
        return nums1[size / 2];
      }
    }
    else if (nums2.size() != 0)
    {
      if (even)
      {
        return (double) (nums2[(size - 1) / 2] + nums2[size / 2]) / 2;
      }
      else
      {
        return nums2[size / 2];
      }
    }
    else
    {
      return 0;
    }
  }

  // 在O(log(M+N))时间复杂度下找到num1和num2这两个有序数组合并后的第k大的数是什么
  int findKthNum(vector<int> &arr1, vector<int> &arr2, int kth)
  {
    vector<int> longs = arr1.size() >= arr2.size() ? arr1 : arr2;
    vector<int> shorts = arr1.size() < arr2.size() ? arr1 : arr2;
    int l = longs.size();
    int s = shorts.size();
    if (kth <= s)
    {
      // 情况一：k <= shorts.size()
      // 在这种情况下比较简单，我们可以将longs数组取前k个数，shorts数组取前k个数，然后调用getMedian方法，拿到中位数，即是longs和shorts数组合并后的第k小的数。
      // 例如：shorts数组为[1,3,5,7]，longs数组为[2,4,6,8,10,12]
      // 如果要取第2小的数, 客观上第2小的数是2，可能存在的范围是shorts的前2个数中，也可能存在在longs的前2个数中
      // 除此之外，不能是其他范围，超过这个范围，就不止第2小了。
      // 因为两个数组都是有序的，如果在shorts和longs内都不能保证是第k小，合并后就更不可能了
      return getUpMedian(shorts, 0, kth - 1, longs, 0, kth - 1);
    }
    if (kth > l)
    {
      // 情况二：longs.size() < k
      // 例如：shorts数组为[1,3,5,7,9,11] 长度是6
      // longs数组为[2,4,6,8,10,12,14,16,18,20,22,24] 长度是12
      // 假设要求第15小的数，那么在shorts中可以排除掉前面（15 - longs.size() - 1）= 2个数，
      // 因为即便shorts中第1小的数比longs中所有数都大，它也只能算第13小的数，第2小的数即便比longs中所有数都大，也只能算全局第14小的数。
      // longs中可以排除掉第1一直到第8小（即：15 - shorts.size() - 1 = 8）的数，因为longs中第8小的数即便比shorts数所有数都大，也只能是全局第14小的数。
      // 经过排除后，shorts中和longs中可选范围为（以下数组中没打x的数字）
      // shorts中为[x,x,5,7,9,11]
      // longs中为[x,x,x,x,x,x,x,x,18,20,22,24]
      // 先手动判断一下，longs中的18和shorts中的5是否是第15小的数，如果是则直接返回
      // 如果不是，shorts中[7,9,11] 和 longs中 [20,22,24] 使用getUpMedian获取的结果即为答案
      if (shorts[kth - l - 1] >= longs[l - 1])
      {
        return shorts[kth - l - 1];
      }
      if (longs[kth - s - 1] >= shorts[s - 1])
      {
        return longs[kth - s - 1];
      }
      return getUpMedian(shorts, kth - l, s - 1, longs, kth - s, l - 1);
    }
    // short.size() < k <= longs.size()
    // 在这种情况下，shorts数组中的每个数都有可能，longs数组可以排除掉 前(k - shorts.len - 1) 个数
    // 以及[kth + 1......longs.size()]区间的所有数，
    // 但是要手动验证一下long中第(k- shorts.len)位置上的数是不是比shorts最后一个数大，
    // 如果是，longs中第(k - shorts.length)位置上的数即为第k小的数,
    // 如果不是，longs中第(k - shorts.length)位置上的数直接排除掉,
    // longs中剩余数和shorts中所有数用一次getUpMedian方法求得的值即为第k小的数。

    // 例如：shorts数组为[1,3,5,7]，longs数组为[2,4,6,8,10,12,14,16,18]
    // 求第7小的数，此时shorts中的数都有可能是第7小的数，但是，longs中，可以排除如下位置的数
    // 首先：从第8小的数开始一直到第longs.length小的数都可以排除。
    // 其次， 7 - shorts.length - 1 即：7 - 4 - 1 = 3 ，longs中第3小之前的数都可以排除，
    // 排除完毕后，验证一下longs中第3小的数是不是比shorts中最后一个数大，如果是，则longs中第3小的数即位两个数组的第7小的数。
    // 如果不是，则longs中剩余可选的数继续和shorts调用getUpMedian方法。
    if (longs[kth - s - 1] >= shorts[s - 1])
    {
      return longs[kth - s - 1];
    }
    return getUpMedian(shorts, 0, s - 1, longs, kth - s, kth - 1);
  }

  // 获取两个长度相等的有序数组merge后的上中位数
  // 如果是偶数，取上中位数
  // 调用该方法的时候保证[s1...e1] 和 [s2...e2]等长
  int getUpMedian(vector<int> &A, int s1, int e1, vector<int> &B, int s2, int e2)
  {
    int mid1 = 0;
    int mid2 = 0;
    while (s1 < e1)
    {
      mid1 = (s1 + e1) / 2;
      mid2 = (s2 + e2) / 2;
      if (A[mid1] == B[mid2])
      {
        // 如果A和B的中位数值一样，则这个中位数值也是A和B合并后的中位数值
        return A[mid1];
      }
      if (((e1 - s1 + 1) & 1) == 1)
      {
        // 奇数长度
        if (A[mid1] > B[mid2])
        {
          if (B[mid2] >= A[mid1 - 1])
          {
            return B[mid2];
          }
          e1 = mid1 - 1;
          s2 = mid2 + 1;
        }
        else
        {
          // A[mid1] < B[mid2]
          if (A[mid1] >= B[mid2 - 1])
          {
            return A[mid1];
          }
          e2 = mid2 - 1;
          s1 = mid1 + 1;
        }
      }
      else
      {
        // 偶数长度
        if (A[mid1] > B[mid2])
        {
          // 如果A[mid1] > B[mid2]
          // 则全局的中位数只可能在A的[s1..mid1]以及B的[mid2+1..e2]范围内产生
          e1 = mid1;
          s2 = mid2 + 1;
        }
        else
        {
          e2 = mid2;
          s1 = mid1 + 1;
        }
      }
    }
    return std::min(A[s1], B[s2]);
  }
};

void testFindMedianSortedArrays()
{
  Solution s;
  vector<int> n1 = {1, 3};
  vector<int> n2 = {2};

  vector<int> n3 = {1, 2};
  vector<int> n4 = {3, 4};
  EXPECT_EQ_DOUBLE(2.00000, s.findMedianSortedArrays1(n1, n2));
  EXPECT_EQ_DOUBLE(2.50000, s.findMedianSortedArrays1(n3, n4));
  EXPECT_EQ_DOUBLE(2.00000, s.findMedianSortedArrays2(n1, n2));
  EXPECT_EQ_DOUBLE(2.50000, s.findMedianSortedArrays2(n3, n4));

  EXPECT_SUMMARY;
}
int main()
{
  testFindMedianSortedArrays();
  return 0;
}
