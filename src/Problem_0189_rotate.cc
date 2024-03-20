#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

// 旋转数组
class Solution
{
 public:
  // 利用库函数
  void rotate1(vector<int>& nums, int k)
  {
    for (int i = 0; i < k; i++)
    {
      nums.insert(nums.begin(), nums.back());
      nums.pop_back();
    }
  }

  void rotate2(vector<int>& nums, int k)
  {
    int n = nums.size();
    k = k % n;
    // 1 2 3 4 5 6 7
    reverse(nums, 0, n - k - 1);
    // 3 2 1 7 6 5 4
    reverse(nums, n - k, n - 1);
    // 4 5 6 7 1 2 3
    reverse(nums, 0, n - 1);
  }

  void reverse(vector<int>& nums, int L, int R)
  {
    while (L < R)
    {
      int tmp = nums[L];
      nums[L++] = nums[R];
      nums[R--] = tmp;
    }
  }

  void rotate3(vector<int>& nums, int k)
  {
    // TODO: figure it out
    int n = nums.size();
    k = k % n;
    if (k == 0)
    {
      return;
    }
    int L = 0;
    int R = n - 1;
    int lpart = n - k;
    int rpart = k;
    int same = std::min(lpart, rpart);
    int diff = lpart - rpart;
    exchange(nums, L, R, same);
    while (diff != 0)
    {
      if (diff > 0)
      {
        L += same;
        lpart = diff;
      }
      else
      {
        R -= same;
        rpart = -diff;
      }
      same = std::min(lpart, rpart);
      diff = lpart - rpart;
      exchange(nums, L, R, same);
    }
  }

  void exchange(vector<int>& nums, int start, int end, int size)
  {
    int i = end - size + 1;
    int tmp = 0;
    while (size-- != 0)
    {
      tmp = nums[start];
      nums[start] = nums[i];
      nums[i] = tmp;
      start++;
      i++;
    }
  }

  // 利用额外数组
  void rotate4(vector<int>& nums, int k)
  {
    int n = nums.size();
    vector<int> ext(n);
    for (int i = 0; i < n; i++)
    {
      ext[(i + k) % n] = nums[i];
    }
    nums.swap(ext);
  }
};

void testRotate()
{
  Solution s;
  vector<int> n1 = {1, 2, 3, 4, 5, 6, 7};
  vector<int> o1 = {5, 6, 7, 1, 2, 3, 4};
  vector<int> n2 = {-1, -100, 3, 99};
  vector<int> o2 = {3, 99, -1, -100};
  s.rotate1(n1, 3);
  s.rotate1(n2, 2);
  EXPECT_TRUE(o1 == n1);
  EXPECT_TRUE(o2 == n2);
  EXPECT_SUMMARY;
}

int main()
{
  testRotate();
  return 0;
}
