#include <vector>

using namespace std;

class Solution
{
 public:
  vector<int> drawLine(int length, int w, int x1, int x2, int y)
  {
    // 注意直线的坐标
    // 实际上需要特殊处理的 只有直线所在的那一行
    // 结果数组从 像素点(0, 0)开始计算
    int per_row = w / 32;
    vector<int> ans(length, 0);
    for (int i = x1; i <= x2 && i < length * 32; i++)
    {
      ans[y * per_row + i / 32] |= 1 << (31 - i % 32);  // 从左到右，先高后低
    }
    return ans;
  }
};
