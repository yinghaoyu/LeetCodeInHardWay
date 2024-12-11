#include <algorithm>
#include <queue>
#include <vector>

#include "UnitTest.h"

using namespace std;

// 天际线问题
// 与扫描线问题相似 @sa Problem_1851_minInterval.cc
// 离散化 + 扫描线 + 堆 + 延迟删除
// @sa https://www.bilibili.com/video/BV16x4y1a7Ro/
class Solution
{
 private:
  static const int MAXN = 100001;

  vector<int> xsort = vector<int>(MAXN);

  vector<int> height = vector<int>(MAXN);

  // 准备工作如下
  // 1) 收集大楼左边界、右边界-1、右边界的值
  // 2) 收集的所有值排序、去重
  // 3) 大楼的左边界和右边界，修改成排名值
  // 4) 大楼根据左边界排序
  // 5) 清空height数组
  // 6) 返回离散值的个数
  int prepare(vector<vector<int>>& arr, int n)
  {
    int size = 0;
    // 大楼的左边界、右边界-1、右边界，三个值都去离散化
    for (int i = 0; i < n; i++)
    {
      xsort[++size] = arr[i][0];
      xsort[++size] = arr[i][1] - 1;
      xsort[++size] = arr[i][1];
    }
    std::sort(xsort.begin() + 1, xsort.begin() + size + 1);
    // 排序之后去重，去重后的数值有m个
    int m = 1;
    for (int i = 1; i <= size; i++)
    {
      if (xsort[m] != xsort[i])
      {
        xsort[++m] = xsort[i];
      }
    }
    // 修改大楼影响到的左右边界，都变成排名值
    for (int i = 0; i < n; i++)
    {
      arr[i][0] = rank(m, arr[i][0]);
      // 大楼影响到的右边界，减少1！
      // 课上重点说明的内容
      arr[i][1] = rank(m, arr[i][1] - 1);
    }
    // 所有大楼根据左边界排序
    std::sort(arr.begin(), arr.begin() + n, [](auto& a, auto& b) { return a[0] < b[0]; });
    // 高度数组清空
    std::fill(height.begin() + 1, height.begin() + m + 1, 0);
    // 返回有多少个不同的离散值
    return m;
  }

  // 查询数值v的排名(离散值)
  int rank(int n, int v)
  {
    int ans = 0;
    int l = 1, r = n, mid;
    while (l <= r)
    {
      mid = (l + r) >> 1;
      if (xsort[mid] >= v)
      {
        ans = mid;
        r = mid - 1;
      }
      else
      {
        l = mid + 1;
      }
    }
    return ans;
  }

 public:
  vector<vector<int>> getSkyline(vector<vector<int>>& buildings)
  {
    int n = buildings.size();
    int m = prepare(buildings, n);
    // 0 : 高度
    // 1 : 影响到的位置
    priority_queue<vector<int>> heap;
    for (int i = 1, j = 0; i <= m; i++)
    {
      for (; j < n && buildings[j][0] <= i; j++)
      {
        heap.push({buildings[j][2], buildings[j][1]});
      }
      while (!heap.empty() && heap.top()[1] < i)
      {
        // 可能有脏数据不在堆顶也没关系，延迟删除
        heap.pop();
      }
      if (!heap.empty())
      {
        height[i] = heap.top()[0];
      }
    }
    vector<vector<int>> ans;
    for (int i = 1, pre = 0; i <= m; i++)
    {
      if (pre != height[i])
      {
        ans.push_back({xsort[i], height[i]});
      }
      pre = height[i];
    }
    return ans;
  }
};

void testGetSkyline()
{
  Solution s;
  vector<vector<int>> b1 = {{2, 9, 10}, {3, 7, 15}, {5, 12, 12}, {15, 20, 10}, {19, 24, 8}};
  vector<vector<int>> o1 = {{2, 10}, {3, 15}, {7, 12}, {12, 0}, {15, 10}, {20, 8}, {24, 0}};
  vector<vector<int>> b2 = {{0, 2, 3}, {2, 5, 3}};
  vector<vector<int>> o2 = {{0, 3}, {5, 0}};
  vector<vector<int>> b3 = {{1, 2, 1}, {1, 2, 2}, {1, 2, 3}};
  vector<vector<int>> o3 = {{1, 3}, {2, 0}};
  EXPECT_TRUE(o1 == s.getSkyline(b1));
  EXPECT_TRUE(o2 == s.getSkyline(b2));
  EXPECT_TRUE(o3 == s.getSkyline(b3));
  EXPECT_SUMMARY;
}

int main()
{
  testGetSkyline();
  return 0;
}
