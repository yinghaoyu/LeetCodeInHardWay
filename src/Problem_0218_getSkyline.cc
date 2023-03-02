#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 private:
  class Node
  {
   public:
    int x;       // 横坐标
    bool isAdd;  // true 表示左端点
    int h;       // 高度

    Node(int x, int isAdd, int h)
    {
      this->x = x;
      this->isAdd = isAdd;
      this->h = h;
    }
  };

  class cmp
  {
   public:
    bool operator()(Node *o1, Node *o2)
    {
      // 横坐标从小到大排序
      // 横坐标相同右端点在前，左端点在后
      if (o1->x != o2->x)
      {
        // 注意这里必须不相同才需要调整，否则按插入的顺序排序，减少移动次数
        return o1->x < o2->x;
      }
      if (o1->isAdd != o2->isAdd)
      {
        // 注意这里必须不相同才需要调整，否则按插入的顺序排序，减少移动次数
        return !o1->isAdd;
      }
      return false;
    }
  };

 public:
  vector<vector<int>> getSkyline(vector<vector<int>> &buildings)
  {
    vector<Node *> nodes(2 * buildings.size());
    for (int i = 0; i < buildings.size(); i++)
    {
      nodes[i * 2] = new Node(buildings[i][0], true, buildings[i][2]);
      nodes[i * 2 + 1] = new Node(buildings[i][1], false, buildings[i][2]);
    }
    std::sort(nodes.begin(), nodes.end(), cmp());
    // 有序表，key 代表某个高度，value 代表这个高度出现的次数
    map<int, int> mapHeightTimes;
    // 有序表，key 代表x的值，value 代表处在x位置时的高度
    map<int, int> xMaxHeight;
    for (int i = 0; i < nodes.size(); i++)
    {
      if (nodes[i]->isAdd)
      {
        // 左端点
        if (!mapHeightTimes.count(nodes[i]->h))
        {
          mapHeightTimes.emplace(nodes[i]->h, 1);
        }
        else
        {
          mapHeightTimes.at(nodes[i]->h)++;
        }
      }
      else
      {
        // 右端点
        if (mapHeightTimes.at(nodes[i]->h) == 1)
        {
          mapHeightTimes.erase(nodes[i]->h);
        }
        else
        {
          mapHeightTimes.at(nodes[i]->h)--;
        }
      }
      if (mapHeightTimes.empty())
      {
        // 注意这里不能用emplace，不然过不了例b3
        // 起点和终点特殊考虑
        xMaxHeight[nodes[i]->x] = 0;
      }
      else
      {
        // 注意这里不能用emplace，不然过不了例b2
        // 两个矩形可能共用一条边
        xMaxHeight[nodes[i]->x] = mapHeightTimes.rbegin()->first;
      }
    }
    vector<vector<int>> ans;
    for (auto &[x, height] : xMaxHeight)
    {
      if (ans.empty() || ans.back()[1] != height)
      {
        ans.push_back({x, height});
      }
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
