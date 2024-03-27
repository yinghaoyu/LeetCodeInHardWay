#include <unordered_set>
#include <vector>

using namespace std;

class Solution
{
 public:
  vector<int> divingBoard(int shorter, int longer, int k)
  {
    if (k == 0)
    {
      return vector<int>();
    }
    if (shorter == longer)
    {
      return vector<int>(1, shorter * k);
    }
    vector<int> length(k + 1);
    for (int i = 0; i <= k; i++)
    {
      // 从小到大排序
      length[i] = shorter * (k - i) + longer * i;
    }
    return length;
  }
};
