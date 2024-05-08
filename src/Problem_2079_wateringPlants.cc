#include <vector>

using namespace std;

class Solution
{
 public:
  // 简单模拟
  int wateringPlants(vector<int>& plants, int capacity)
  {
    int n = plants.size();
    int ans = 0;
    int rest = capacity;
    for (int i = 0; i < n; ++i)
    {
      if (rest >= plants[i])
      {
        // 剩余水量够用
        ++ans;
        rest -= plants[i];
      }
      else
      {
        // 不够用，回去取水 i*2 步，加上当前浇水往前 1 步
        ans += i * 2 + 1;
        rest = capacity - plants[i];
      }
    }
    return ans;
  }
};
