#include <vector>

using namespace std;

//@sa https://www.bilibili.com/video/BV1qu4y187Xn/
// 子数组最大累加和 扩展题
class Solution
{
 public:
  vector<int> maxSumOfThreeSubarrays(vector<int>& nums, int k)
  {
    int n = nums.size();
    // sums[i] : 以i开头并且长度为k的子数组的累加和
    vector<int> sums(n);
    for (int l = 0, r = 0, sum = 0; r < n; r++)
    {
      // l....r
      sum += nums[r];
      if (r - l + 1 == k)
      {
        sums[l] = sum;
        sum -= nums[l];
        l++;
      }
    }
    // prefix[i] :
    // 0~i范围上所有长度为k的子数组中，拥有最大累加和的子数组，是以什么位置开头的
    vector<int> prefix(n);
    for (int l = 1, r = k; r < n; l++, r++)
    {
      if (sums[l] > sums[prefix[r - 1]])
      {
        // 注意>，为了同样最大累加和的情况下，最小的字典序
        prefix[r] = l;
      }
      else
      {
        prefix[r] = prefix[r - 1];
      }
    }
    // suffix[i] :
    // i~n-1范围上所有长度为k的子数组中，拥有最大累加和的子数组，是以什么位置开头的
    vector<int> suffix(n);
    suffix[n - k] = n - k;
    for (int l = n - k - 1; l >= 0; l--)
    {
      if (sums[l] >= sums[suffix[l + 1]])
      {
        // 注意>=，为了同样最大累加和的情况下，最小的字典序
        suffix[l] = l;
      }
      else
      {
        suffix[l] = suffix[l + 1];
      }
    }
    int a = 0, b = 0, c = 0, max = 0;
    // 0...i-1    i...j    j+1...n-1
    //   左     中(长度为k)     右
    for (int p, s, i = k, j = 2 * k - 1, sum; j < n - k; i++, j++)
    {
      // 0.....i-1   i.....j  j+1.....n-1
      // 最好开头p      i开头     最好开头s
      p = prefix[i - 1];
      s = suffix[j + 1];
      sum = sums[p] + sums[i] + sums[s];
      if (sum > max)
      {
        // 注意>，为了同样最大累加和的情况下，最小的字典序
        max = sum;
        a = p;
        b = i;
        c = s;
      }
    }
    return {a, b, c};
  }
};
