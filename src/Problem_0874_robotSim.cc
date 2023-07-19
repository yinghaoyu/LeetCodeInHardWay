#include <iostream>
#include <set>
#include <utility>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int robotSim(vector<int> &commands, vector<vector<int>> &obstacles)
  {
    const int dirs[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    int x = 0;
    int y = 0;
    int dir = 0;
    int ans = 0;
    set<pair<int, int>> obs;
    for (auto &o : obstacles)
    {
      obs.emplace(o[0], o[1]);
    }
    for (auto &c : commands)
    {
      if (c == -1)
      {
        dir = (dir + 1) % 4;
      }
      else if (c == -2)
      {
        dir = (dir + 3) % 4;
      }
      else
      {
        int dx = dirs[dir][0];
        int dy = dirs[dir][1];
        for (int i = 0; i < c; i++)
        {
          if (obs.find({x + dx, y + dy}) != obs.end())
          {
            break;
          }
          x += dx;
          y += dy;
        }
      }
      ans = std::max(ans, x * x + y * y);
    }
    return ans;
  }
};

void test()
{
  Solution s;
  vector<int> c1 = {4, -1, 3};
  vector<vector<int>> o1 = {};

  vector<int> c2 = {4, -1, 4, -2, 4};
  vector<vector<int>> o2 = {{2, 4}};

  vector<int> c3 = {6, -1, -1, 6};
  vector<vector<int>> o3 = {};

  EXPECT_EQ_INT(25, s.robotSim(c1, o1));
  EXPECT_EQ_INT(65, s.robotSim(c2, o2));
  EXPECT_EQ_INT(36, s.robotSim(c3, o3));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
