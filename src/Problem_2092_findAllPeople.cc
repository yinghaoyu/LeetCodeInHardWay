#include <algorithm>
#include <numeric>
#include <string>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 private:
  vector<int> father;

  // 集合的标签信息 : 设置集合的一些属性
  // 属性在哪？secret[代表元素] 代表集合的属性
  vector<bool> secret;

  void build(int n, int first)
  {
    father.resize(n);
    secret.resize(n);
    std::iota(father.begin(), father.end(), 0);
    std::fill(secret.begin(), secret.end(), false);
    // base case
    father[first] = 0;
    secret[0] = true;
  }

  int find(int i)
  {
    if (i != father[i])
    {
      father[i] = find(father[i]);
    }
    return father[i];
  }

  void unions(int x, int y)
  {
    int fx = find(x);
    int fy = find(y);
    if (fx != fy)
    {
      // 让 fy 成为 fx 的父亲
      father[fx] = fy;
      // 同时，把 fx 的秘密传递到 fy
      secret[fy] = secret[fy] | secret[fx];
    }
  }

 public:
  // 会议排序 : m * log m
  // 处理过程 : O(m)
  // 收集答案 : O(n)
  vector<int> findAllPeople(int n, vector<vector<int>>& meetings, int firstPerson)
  {
    build(n, firstPerson);
    // {0 : 专家   1 : 专家   2 : 时刻}
    std::sort(meetings.begin(), meetings.end(), [](auto& x, auto& y) { return x[2] < y[2]; });
    int m = meetings.size();
    for (int l = 0, r; l < m;)
    {
      r = l;
      while (r + 1 < m && meetings[l][2] == meetings[r + 1][2])
      {
        r++;
      }
      // l....r这些会议，一定是一个时刻
      for (int i = l; i <= r; i++)
      {
        unions(meetings[i][0], meetings[i][1]);
      }
      // 有小的撤销行为，但这不是可撤销并查集
      // 只是每一批没有知道秘密的专家重新建立集合而已
      for (int i = l, a, b; i <= r; i++)
      {
        a = meetings[i][0];
        b = meetings[i][1];
        if (!secret[find(a)])
        {
          father[a] = a;
        }
        if (!secret[find(b)])
        {
          father[b] = b;
        }
      }
      l = r + 1;
    }
    vector<int> ans;
    for (int i = 0; i < n; i++)
    {
      if (secret[find(i)])
      {
        ans.push_back(i);
      }
    }
    return ans;
  }
};

void test()
{
  Solution s;
  vector<vector<int>> m1 = {{1, 2, 5}, {2, 3, 8}, {1, 5, 10}};
  vector<int> o1 = {0, 1, 2, 3, 5};
  vector<vector<int>> m2 = {{3, 1, 3}, {1, 2, 2}, {0, 3, 3}};
  vector<int> o2 = {0, 1, 3};
  vector<vector<int>> m3 = {{3, 4, 2}, {1, 2, 1}, {2, 3, 1}};
  vector<int> o3 = {0, 1, 2, 3, 4};
  EXPECT_TRUE(o1 == s.findAllPeople(6, m1, 1));
  EXPECT_TRUE(o2 == s.findAllPeople(4, m2, 3));
  EXPECT_TRUE(o3 == s.findAllPeople(5, m3, 1));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
