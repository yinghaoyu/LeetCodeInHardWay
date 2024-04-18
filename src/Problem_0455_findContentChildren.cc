#include <algorithm>
#include <vector>

using namespace std;

class Solution
{
 public:
  int findContentChildren(vector<int>& g, vector<int>& s)
  {
    std::sort(g.begin(), g.end());
    std::sort(s.begin(), s.end());
    int ans = 0;
    int n = g.size();
    int m = s.size();
    int i = n - 1;
    int j = m - 1;
    while (i >= 0 && j >= 0)
    {
      if (g[i] <= s[j])
      {
        j--;
        i--;
        ans++;
      }
      else
      {
        i--;
      }
    }
    return ans;
  }
};
