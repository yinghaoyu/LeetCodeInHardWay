#include <algorithm>
#include <vector>

using namespace std;

// TODO: figure it out.
class Solution
{
 public:
  long long putMarbles(vector<int>& weights, int k)
  {
    int n = weights.size();
    vector<long> split(n - 1);
    for (int i = 1; i < n; i++)
    {
      split[i - 1] = weights[i - 1] + weights[i];
    }
    std::sort(split.begin(), split.end());
    long small = 0;
    long big = 0;
    for (int i = 0, j = n - 2, p = 1; p < k; i++, j--, p++)
    {
      small += split[i];
      big += split[j];
    }

    return big - small;
  }
};
