#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

// @sa
// https://leetcode.cn/problems/langtons-ant-lcci/solutions/180741/28miao-shuang-100nei-bu-lei-san-lie-ji-he-by-1ujin/
// 模拟题
class Solution
{
 private:
  struct Position
  {
    int x, y;

    Position(int x, int y) : x(x), y(y) {}

    // 注意这里必须加 const
    bool operator==(const Position& other) const { return x == other.x && y == other.y; }
  };

  struct PositionHash
  {
    // 改写哈希算法，使两个 Position 对象可以比较坐标而不是内存地址
    // 注意这里必须加 const
    size_t operator()(const Position& pos) const { return hash<int>()(pos.x) ^ hash<int>()(pos.y); }
  };

 public:
  vector<string> printKMoves(int K)
  {
    char direction[] = {'L', 'U', 'R', 'D'};
    // 用“向量”记录方向，顺序与上一行方向的字符顺序保持一致，每个元素的后一个元素都是可以90°向右变换得到
    int offset[][2] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
    // 蚂蚁的位置
    Position antPos(0, 0);
    // 蚂蚁方向的向量序号
    int antDir = 2;
    // 用集合存储所有黑块的坐标，一开始想再定义一个路径的坐标集合，发现可以直接用黑块+蚂蚁位置也能过
    unordered_set<Position, PositionHash> blackSet;

    while (K > 0)
    {
      // 新的坐标对象用于放入集合
      Position t(antPos.x, antPos.y);
      if (blackSet.insert(t).second)
      {
        // 如果黑块集合能存入，说明脚下的块不在集合中，也就意味着是白色，方向序号循环自增1
        antDir = (antDir + 1) % 4;
      }
      else
      {
        // 否则说明脚下的块已经在集合中，也就意味着是黑色，方向序号循环自增3，相当于自减1
        antDir = (antDir + 3) % 4;
        // 别忘了删除，即将黑块变白
        blackSet.erase(t);
      }
      // 蚂蚁移动位置
      antPos.x += offset[antDir][0];
      antPos.y += offset[antDir][1];
      K--;
    }

    // 计算边界，即输出网格的行数和列数
    int left = antPos.x, top = antPos.y, right = antPos.x, bottom = antPos.y;
    for (const auto& pos : blackSet)
    {
      // 因为起始坐标在左上角(0, 0)，所以 left 和 top 取最小，right 和 bottom 取最大才能保证网格有效
      left = min(pos.x, left);
      top = min(pos.y, top);
      right = max(pos.x, right);
      bottom = max(pos.y, bottom);
    }

    // 填充白块
    vector<vector<char>> grid(bottom - top + 1, vector<char>(right - left + 1, '_'));
    // 替换黑块
    for (const auto& pos : blackSet)
    {
      grid[pos.y - top][pos.x - left] = 'X';
    }
    // 替换蚂蚁
    grid[antPos.y - top][antPos.x - left] = direction[antDir];

    vector<string> result;
    // 利用网格生成字符串列表
    for (const auto& row : grid)
    {
      result.emplace_back(row.begin(), row.end());
    }

    return result;
  }
};
