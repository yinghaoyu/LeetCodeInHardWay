#include <algorithm>
#include <memory>
#include <optional>
#include <vector>

using namespace std;

class Solution
{
 public:
  vector<double> cutSquares(vector<int>& square1, vector<int>& square2)
  {
    // 第一个正方形的中心点
    double x1 = square1[0] + square1[2] / 2.0;
    double y1 = square1[1] + square1[2] / 2.0;
    int d1 = square1[2];
    // 第二个正方形的中心点
    double x2 = square2[0] + square2[2] / 2.0;
    double y2 = square2[1] + square2[2] / 2.0;
    int d2 = square2[2];
    // 结果集
    vector<double> ans(4);
    if (x1 == x2)
    {
      // 两个中心坐标在同一条x轴上，此时两条直线的斜率都是无穷大
      ans[0] = x1;
      ans[1] = std::min(square1[1], square2[1]);
      ans[2] = x1;
      ans[3] = std::max(square1[1] + d1, square2[1] + d2);
    }
    else
    {
      // 斜率存在，则计算斜率和系数， y = kx + b
      double k = (y1 - y2) / (x1 - x2);
      double b = y1 - k * x1;
      // 斜率绝对值 > 1，说明与正方形的上边和下边相交
      if (std::abs(k) > 1)
      {
        // 先计算底边，也就是两个正方形左下坐标y的最小值
        ans[1] = std::min(square1[1], square2[1]);
        ans[0] = (ans[1] - b) / k;
        // 在计算顶边，也就是两个正方形左下坐标+边长的最大值
        ans[3] = std::max(square1[1] + d1, square2[1] + d2);
        ans[2] = (ans[3] - b) / k;
      }
      else
      {
        // 斜率绝对值小于等于1，说明与正方形的左边和右边相交，同理
        ans[0] = std::min(square1[0], square2[0]);
        ans[1] = ans[0] * k + b;
        ans[2] = std::max(square1[0] + d1, square2[0] + d2);
        ans[3] = ans[2] * k + b;
      }
    }
    // 题设要求 x1 < x2
    if (ans[0] > ans[2])
    {
      std::swap(ans[0], ans[2]);
      std::swap(ans[1], ans[3]);
    }
    return ans;
  }
};
