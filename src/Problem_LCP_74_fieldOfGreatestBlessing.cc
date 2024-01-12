#include <algorithm>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  // TODO: figure it out
  // 时间复杂度O(n^2)，额外空间复杂度O(n^2)，n是力场的个数
  int fieldOfGreatestBlessing(vector<vector<int>>& forceField)
  {
    int n = forceField.size();
    vector<long> xs(n << 1);
    vector<long> ys(n << 1);
    for (int i = 0, k = 0, p = 0; i < n; i++)
    {
      long x = forceField[i][0];
      long y = forceField[i][1];
      long r = forceField[i][2];
      xs[k++] = (x << 1) - r;
      xs[k++] = (x << 1) + r;
      ys[p++] = (y << 1) - r;
      ys[p++] = (y << 1) + r;
    }
    // xs数组中，排序了且相同值只留一份，返回有效长度
    int sizex = sort(xs);
    // ys数组中，排序了且相同值只留一份，
    int sizey = sort(ys);
    vector<vector<int>> diff(sizex + 2, vector<int>(sizey + 2));
    for (int i = 0, a, b, c, d; i < n; i++)
    {
      long x = forceField[i][0];
      long y = forceField[i][1];
      long r = forceField[i][2];
      a = rank(xs, (x << 1) - r, sizex);
      b = rank(ys, (y << 1) - r, sizey);
      c = rank(xs, (x << 1) + r, sizex);
      d = rank(ys, (y << 1) + r, sizey);
      add(diff, a, b, c, d);
    }
    int ans = 0;
    // O(n^2)
    for (int i = 1; i < diff.size(); i++)
    {
      for (int j = 1; j < diff[0].size(); j++)
      {
        diff[i][j] += diff[i - 1][j] + diff[i][j - 1] - diff[i - 1][j - 1];
        ans = std::max(ans, diff[i][j]);
      }
    }
    return ans;
  }

  // [50,70,30,70,30,60] 长度6
  // [30,30,50,60,70,70]
  // [30,50,60,70] 60 -> 3
  //  1  2  3  4
  // 长度4，
  int sort(vector<long>& nums)
  {
    std::sort(nums.begin(), nums.end());
    int size = 1;
    for (int i = 1; i < nums.size(); i++)
    {
      if (nums[i] != nums[size - 1])
      {
        nums[size++] = nums[i];
      }
    }
    return size;
  }

  // nums 有序数组，有效长度是size，0~size-1范围上无重复值
  // 已知v一定在nums[0~size-1]，返回v所对应的编号
  int rank(vector<long>& nums, long v, int size)
  {
    int l = 0;
    int r = size - 1;
    int m, ans = 0;
    while (l <= r)
    {
      m = (l + r) / 2;
      if (nums[m] >= v)
      {
        ans = m;
        r = m - 1;
      }
      else
      {
        l = m + 1;
      }
    }
    return ans + 1;
  }

  // 二维差分
  void add(vector<vector<int>>& diff, int a, int b, int c, int d)
  {
    diff[a][b] += 1;
    diff[c + 1][d + 1] += 1;
    diff[c + 1][b] -= 1;
    diff[a][d + 1] -= 1;
  }
};

void test()
{
  Solution s;
  vector<vector<int>> f1 = {{0, 0, 1}, {1, 0, 1}};
  vector<vector<int>> f2 = {{4, 4, 6}, {7, 5, 3}, {1, 6, 2}, {5, 6, 3}};
  EXPECT_EQ_INT(2, s.fieldOfGreatestBlessing(f1));
  EXPECT_EQ_INT(3, s.fieldOfGreatestBlessing(f2));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
