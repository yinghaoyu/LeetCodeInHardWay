#include <algorithm>
#include <vector>

using namespace std;

class Solution
{
 public:
  vector<bool> distanceLimitedPathsExist(int n,
                                         vector<vector<int>>& edgeList,
                                         vector<vector<int>>& queries)
  {
    // 边长从小到大排序
    std::sort(edgeList.begin(), edgeList.end(), [](auto& a, auto& b) { return a[2] < b[2]; });
    int m = edgeList.size();
    int k = queries.size();
    // 记录索引，用于后续填充答案
    for (int i = 0; i < k; i++)
    {
      questions[i][0] = queries[i][0];
      questions[i][1] = queries[i][1];
      questions[i][2] = queries[i][2];
      questions[i][3] = i;
    }
    // 问题的限制从小到大排序
    std::sort(questions.begin(), questions.begin() + k,
              [](auto& a, auto& b) { return a[2] < b[2]; });
    build(n);
    vector<bool> ans(k);
    // 由于我们依次遍历问题，每次的限制都是从小到大排序
    // 只要把每次小于限制的边加入集合，再检查两个点是否连通即可
    for (int i = 0, j = 0; i < k; i++)
    {
      // i : 问题编号
      // j : 边的编号
      for (; j < m && edgeList[j][2] < questions[i][2]; j++)
      {
        unions(edgeList[j][0], edgeList[j][1]);
      }
      ans[questions[i][3]] = isSameSet(questions[i][0], questions[i][1]);
    }
    return ans;
  }

 private:
  static const int MAXN = 100001;

  vector<vector<int>> questions = vector<vector<int>>(MAXN, vector<int>(4));

  vector<int> father = vector<int>(MAXN);

  void build(int n)
  {
    for (int i = 0; i < n; i++)
    {
      father[i] = i;
    }
  }

  int find(int i)
  {
    if (i != father[i])
    {
      father[i] = find(father[i]);
    }
    return father[i];
  }

  bool isSameSet(int x, int y) { return find(x) == find(y); }

  void unions(int x, int y) { father[find(x)] = find(y); }
};
