#include <iostream>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

class Solution
{
 public:
  vector<int> bestLine(vector<vector<int>>& points)
  {
    int n = points.size();
    int max = 0;
    vector<int> ans(2);
    for (int i = 0; i < n - 1; i++)
    {
      // {A, B, C, i, j, cnt}
      unordered_map<int, unordered_map<int, unordered_map<int, tuple<int, int, int>>>> map;
      for (int j = i + 1; j < n; j++)
      {
        // 已知一条直线可以表示为：y = kx + b
        // 如果直接计算k的话，k不一定是整数
        // 我们可以转成 Ay + Bx + C = 0 的直线一般形式
        long long A = points[i][0] - points[j][0];
        long long B = points[j][1] - points[i][1];
        long long C = A * points[i][1] + B * points[i][0];
        long long g = gcd(gcd(A, B), C);
        A /= g;
        B /= g;
        C /= g;
        if (!map.count(A))
        {
          map.emplace(A, unordered_map<int, unordered_map<int, tuple<int, int, int>>>());
        }
        if (!map.at(A).count(B))
        {
          map.at(A).emplace(B, unordered_map<int, tuple<int, int, int>>());
        }
        if (!map.at(A).at(B).count(C))
        {
          map.at(A).at(B).emplace(C, tuple<int, int, int>(i, j, 0));
        }
        auto& [a, b, cnt] = map[A][B][C];
        cnt++;
        if (cnt >= max)
        {
          if (cnt > max || a < ans[0] || (a == ans[0] && b < ans[1]))
          {
            // 取索引小的点
            max = cnt;
            ans = {a, b};
          }
        }
      }
    }
    return ans;
  }

  long long gcd(long long a, long long b) { return b == 0 ? a : gcd(b, a % b); }
};
