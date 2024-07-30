#include <vector>

using namespace std;

class Solution
{
  // 快速幂
  int pow(int a, int b, int m)
  {
    int ans = 1;
    while (b != 0)
    {
      if (b & 1)
      {
        ans = ans * a % m;
      }
      a = a * a % m;
      b >>= 1;
    }
    return ans;
  }

 public:
  vector<int> getGoodIndices(vector<vector<int>>& variables, int target)
  {
    int n = variables.size();
    vector<int> ans;
    for (int i = 0; i < n; i++)
    {
      int a = variables[i][0];
      int b = variables[i][1];
      int c = variables[i][2];
      int m = variables[i][3];
      if (pow(pow(a, b, 10), c, m) == target)
      {
        ans.push_back(i);
      }
    }
    return ans;
  }
};
