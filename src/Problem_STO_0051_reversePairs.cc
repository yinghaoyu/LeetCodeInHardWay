#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int merge(vector<int> &arr, int L, int M, int R)
  {
    int len = R - L + 1;
    vector<int> help(len);

    int ans = 0;
    int hi = len - 1;
    int i = M;
    int j = R;

    while (i >= L && j > M)
    {
      // arr[M .. j] 之间的数 < arr[i]
      ans += arr[i] > arr[j] ? (j - M) : 0;
      // arr[i] == arr[j] 时，先拷贝右侧的数组，保证arr[i]还能再次计算
      help[hi--] = arr[i] > arr[j] ? arr[i--] : arr[j--];
    }
    while (i >= L)
    {
      help[hi--] = arr[i--];
    }
    while (j > M)
    {
      help[hi--] = arr[j--];
    }

    for (int i = 0; i < len; i++)
    {
      arr[L + i] = help[i];
    }
    return ans;
  }

  int process(vector<int> &arr, int L, int R)
  {
    if (L == R)
    {
      return 0;
    }
    int M = (R - L) / 2 + L;
    return process(arr, L, M) + process(arr, M + 1, R) + merge(arr, L, M, R);
  }

  int reversePairs(vector<int> &nums) { return process(nums, 0, nums.size() - 1); }
};

void test()
{
  Solution s;
  vector<int> n1 = {7, 5, 6, 4};
  vector<int> n2 = {3, 6, 7, 8, 0, 1, 3, 2};
  EXPECT_EQ_INT(5, s.reversePairs(n1));
  EXPECT_EQ_INT(16, s.reversePairs(n2));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
