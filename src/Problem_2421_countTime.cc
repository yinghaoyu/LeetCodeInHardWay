#include <algorithm>
#include <numeric>
#include <vector>

#include "UnitTest.h"

using namespace std;

// @sa https://www.bilibili.com/video/BV1Ny4y1F71J Code03
// TODO: figure it out.
class Solution
{
 private:
  // 需要保证集合中，代表节点的值，一定是整个集合的最大值
  vector<int> father;
  // 集合中最大值的次数，也就是 集合中代表节点的值有几个
  vector<int> maxcnt;

 private:
  void build(int n)
  {
    father.resize(n);
    maxcnt.resize(n);
    std::iota(father.begin(), father.end(), 0);
    std::fill(maxcnt.begin(), maxcnt.end(), 1);
  }

  // 这个并查集的优化只来自扁平化
  int find(int i)
  {
    if (i != father[i])
    {
      father[i] = find(father[i]);
    }
    return father[i];
  }

  // 核心！
  // 注意以下的写法！
  // 谁的值大，谁做代表节点
  // 同时注意 maxcnt 的更新
  int unions(int x, int y, vector<int>& vals)
  {
    // fx : x所在集团的代表节点，同时也是x所在集团的最大值下标
    int fx = find(x);
    // fy : y所在集团的代表节点，同时也是y所在集团的最大值下标
    int fy = find(y);
    int path = 0;
    if (vals[fx] > vals[fy])
    {
      father[fy] = fx;
    }
    else if (vals[fx] < vals[fy])
    {
      father[fx] = fy;
    }
    else
    {
      // 两个集团最大值一样！
      path = maxcnt[fx] * maxcnt[fy];
      father[fy] = fx;
      maxcnt[fx] += maxcnt[fy];
    }
    return path;
  }

 public:
  int numberOfGoodPaths(vector<int>& vals, vector<vector<int>>& edges)
  {
    int n = vals.size();
    build(n);
    int ans = n;
    // 处理边的时候，依次从小节点往大节点处理
    std::sort(edges.begin(), edges.end(),
              [&](auto& e1, auto& e2)
              { return std::max(vals[e1[0]], vals[e1[1]]) < std::max(vals[e2[0]], vals[e2[1]]); });
    for (auto& edge : edges)
    {
      ans += unions(edge[0], edge[1], vals);
    }
    return ans;
  }
};

void test()
{
  Solution s;
  vector<int> v1 = {1, 3, 2, 1, 3};
  vector<vector<int>> e1 = {{0, 1}, {0, 2}, {2, 3}, {2, 4}};
  vector<int> v2 = {1, 1, 2, 2, 3};
  vector<vector<int>> e2 = {{0, 1}, {1, 2}, {2, 3}, {2, 4}};
  vector<int> v3 = {1};
  vector<vector<int>> e3;
  EXPECT_EQ_INT(6, s.numberOfGoodPaths(v1, e1));
  EXPECT_EQ_INT(7, s.numberOfGoodPaths(v2, e2));
  EXPECT_EQ_INT(1, s.numberOfGoodPaths(v3, e3));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
