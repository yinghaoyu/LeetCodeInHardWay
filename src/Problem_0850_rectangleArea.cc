#include <algorithm>
#include <iostream>
#include <tuple>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 private:
  const int mod = 1e9 + 7;
  const int IN = 1;
  const int OUT = -1;

 public:
  // x1 y1 x2 y2 左下角 右上角
  // 垂直线扫描
  int rectangleArea(vector<vector<int>> &rectangles)
  {
    int n = rectangles.size();
    // y轴的水平边界
    vector<int> hBound;
    for (auto &arr : rectangles)
    {
      // 下边界
      hBound.emplace_back(arr[1]);  // y0
      // 上边界
      hBound.emplace_back(arr[3]);  // y1
    }
    std::sort(hBound.begin(), hBound.end());
    // 删除重复的边界
    hBound.erase(std::unique(hBound.begin(), hBound.end()), hBound.end());
    int m = hBound.size();
    // m条边界，只有m-1个区域
    // 每个seg是hBound[i]和hBound[i+1]确定
    vector<int> seg(m - 1);

    // - x轴的垂直边界
    // - 原数组下标
    // - 左右标记
    vector<tuple<int, int, int>> sweep;
    for (int i = 0; i < n; i += 1)
    {
      sweep.emplace_back(rectangles[i][0], i, IN);   // 矩形左边
      sweep.emplace_back(rectangles[i][2], i, OUT);  // 矩形右边
    }
    // 根据横坐标排序，扫描垂直边左向右
    std::sort(sweep.begin(), sweep.end());

    long long ans = 0;
    for (int i = 0; i < sweep.size(); i++)
    {
      int j = i;
      // 重叠的边有多少条 ?
      while (j + 1 < sweep.size() && get<0>(sweep[i]) == get<0>(sweep[j + 1]))
      {
        j++;
      }
      // 经过上面的while后，j是最后一个满足条件的位置
      // 何时会搜索到最后？
      // 所有的边都是右边界的时候
      if (j + 1 == sweep.size())
      {
        break;
      }

      // 累计整个x坐标相同的区间
      for (int k = i; k <= j; k++)
      {
        int idx = get<1>(sweep[k]);   // 重叠边的序号
        int diff = get<2>(sweep[k]);  // 重叠边的类型
        int down = rectangles[idx][1], up = rectangles[idx][3];
        // 遍历所有的y轴构成的线段区间
        for (int x = 0; x < m - 1; x++)
        {
          // 整个区间正好在当前矩形覆盖的y轴区域
          if (down <= hBound[x] && hBound[x + 1] <= up)
          {
            // 类似差分累计
            // 入边+1，出边-1
            seg[x] += diff;
          }
        }
      }

      // 计算当前扫描出来的y轴覆盖大小
      long long cover = 0;
      for (int k = 0; k < m - 1; k++)
      {
        if (seg[k] > 0)
        {
          cover += 1LL * hBound[k + 1] - hBound[k];
          cover %= mod;
        }
      }
      // 高 * 宽
      ans += cover * (get<0>(sweep[j + 1]) - get<0>(sweep[j]));
      ans %= mod;

      // 跨过坐标相同的点
      i = j;
    }

    return ans;
  }
};

void testRectangleArea()
{
  Solution s;
  vector<vector<int>> arr1 = {{0, 0, 2, 2}, {1, 0, 2, 3}, {1, 0, 3, 1}};
  vector<vector<int>> arr2 = {{0, 0, 1000000000, 1000000000}};

  EXPECT_EQ_INT(6, s.rectangleArea(arr1));
  EXPECT_EQ_INT(49, s.rectangleArea(arr2));

  EXPECT_SUMMARY;
}

int main()
{
  testRectangleArea();
  return 0;
}
