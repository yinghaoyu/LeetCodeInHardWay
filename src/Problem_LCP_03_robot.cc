#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

// @sa https://leetcode.cn/problems/programmable-robot/solutions/30229/c-4ms-jie-da-by-yanghk/
class Solution
{
 public:
  bool robot(string command, vector<vector<int>>& obstacles, int x, int y)
  {
    unordered_set<long> set;
    int dx = 0;
    int dy = 0;
    // 机器人从坐标原点开始
    set.insert(0);
    for (auto& c : command)
    {
      if (c == 'U')
      {
        dy++;
      }
      else if (c == 'R')
      {
        dx++;
      }
      // 二维转一维，记录轨迹

      // 注意：这里一定不能省略 long 转换!
      set.insert(((long) dx << 30) | dy);
    }

    // 由于机器人是重复运行指令的，得到最少需要的循环次数
    int loops = std::min(x / dx, y / dy);
    long key = ((long) (x - loops * dx) << 30) | (y - loops * dy);
    if (!set.count(key))
    {
      // 终点不在第一次循环的轨迹内
      return false;
    }

    for (auto& o : obstacles)
    {
      if (o[0] > x || o[1] > y)
      {
        // 过滤一定不在的轨迹内的障碍物
        continue;
      }
      loops = std::min(o[0] / dx, o[1] / dy);
      key = ((long) (o[0] - loops * dx) << 30) | (o[1] - loops * dy);
      if (set.count(key))
      {
        // 障碍物在第一次循环的轨迹内
        return false;
      }
    }
    return true;
  }
};
