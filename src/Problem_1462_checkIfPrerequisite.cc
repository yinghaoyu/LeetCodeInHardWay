#include <iostream>
#include <queue>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  // bfs
  vector<bool> checkIfPrerequisite(int numCourses, vector<vector<int>> &prerequisites, vector<vector<int>> &queries)
  {
    vector<vector<int>> g(numCourses);
    vector<int> inDegree(numCourses);
    vector<vector<bool>> isPre(numCourses, vector<bool>(numCourses));
    for (auto &x : prerequisites)
    {
      inDegree[x[1]]++;
      g[x[0]].push_back(x[1]);
    }
    queue<int> q;
    for (int i = 0; i < numCourses; i++)
    {
      if (inDegree[i] == 0)
      {
        q.push(i);
      }
    }
    while (!q.empty())
    {
      auto cur = q.front();
      q.pop();
      for (auto &next : g[cur])
      {
        isPre[cur][next] = true;
        for (int i = 0; i < numCourses; i++)
        {
          isPre[i][next] = isPre[i][next] | isPre[i][cur];
        }
        inDegree[next]--;
        if (inDegree[next] == 0)
        {
          q.push(next);
        }
      }
    }
    vector<bool> ans;
    for (auto &x : queries)
    {
      ans.push_back(isPre[x[0]][x[1]]);
    }
    return ans;
  }

  // dfs
  vector<bool> checkIfPrerequisiteByDfs(int numCourses, vector<vector<int>> &prerequisites, vector<vector<int>> &queries)
  {
    vector<vector<int>> g(numCourses);
    vector<bool> vi(numCourses, false);
    vector<vector<bool>> isPre(numCourses, vector<bool>(numCourses, false));
    for (auto &p : prerequisites)
    {
      g[p[0]].push_back(p[1]);
    }
    for (int i = 0; i < numCourses; i++)
    {
      dfs(g, isPre, vi, i);
    }
    vector<bool> ans;
    for (auto &query : queries)
    {
      ans.push_back(isPre[query[0]][query[1]]);
    }
    return ans;
  }

  void dfs(vector<vector<int>>& g, vector<vector<bool>>& isPre, vector<bool>& vi, int cur)
  {
    if(vi[cur])
    {
      return;
    }
    vi[cur] = true;
    for(auto& next : g[cur])
    {
      dfs(g, isPre, vi, next);
      isPre[cur][next] = true;
      for(int i = 0; i < isPre.size(); i++)
      {
        isPre[cur][i] = isPre[cur][i] | isPre[next][i];
      }
    }
  }
};

void test()
{
  Solution s;
  vector<vector<int>> p1 = {{1, 0}};
  vector<vector<int>> q1 = {{0, 1}, {1, 0}};
  vector<bool> o1 = {false, true};

  vector<vector<int>> p2;
  vector<vector<int>> q2 = {{1, 0}, {0, 1}};
  vector<bool> o2 = {false, false};

  vector<vector<int>> p3 = {{1, 2}, {1, 0}, {2, 0}};
  vector<vector<int>> q3 = {{1, 0}, {1, 2}};
  vector<bool> o3 = {true, true};
  EXPECT_TRUE(o1 == s.checkIfPrerequisite(2, p1, q1));
  EXPECT_TRUE(o2 == s.checkIfPrerequisite(2, p2, q2));
  EXPECT_TRUE(o3 == s.checkIfPrerequisite(3, p3, q3));
  EXPECT_TRUE(o1 == s.checkIfPrerequisiteByDfs(2, p1, q1));
  EXPECT_TRUE(o2 == s.checkIfPrerequisiteByDfs(2, p2, q2));
  EXPECT_TRUE(o3 == s.checkIfPrerequisiteByDfs(3, p3, q3));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
