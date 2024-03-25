#include <algorithm>
#include <string>
#include <vector>

using namespace std;

class Solution
{
 public:
  int smallestDifference(vector<int>& a, vector<int>& b)
  {
    // 遇事不决先排序
    std::sort(a.begin(), a.end());
    std::sort(b.begin(), b.end());
    int i = 0;
    int j = 0;
    int n = a.size();
    int m = b.size();
    long long minDiff = std::numeric_limits<long long>::max();
    // 双指针移动
    while (i < n && j < m)
    {
      minDiff = std::min(abs((long long) a[i] - (long long) b[j]), minDiff);
      if (a[i] < b[j])
      {
        i++;
      }
      else if (a[i] > b[j])
      {
        j++;
      }
      else
      {
        return 0;
      }
    }
    return minDiff;
  }
};
