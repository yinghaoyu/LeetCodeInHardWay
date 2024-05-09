#include <vector>

using namespace std;

class Solution
{
 public:
  // 简单模拟题
  int minimumRefill(vector<int>& plants, int capacityA, int capacityB)
  {
    int n = plants.size();
    int ans = 0;
    int restA = capacityA;
    int restB = capacityB;
    for (int i = 0, j = n - 1; i <= j; i++, j--)
    {
      if (i == j)
      {
        if (restB > restA)
        {
          ans += restB < plants[j];
        }
        else
        {
          ans += restA < plants[i];
        }
        break;
      }

      if (restA >= plants[i])
      {
        restA -= plants[i];
      }
      else
      {
        restA = capacityA - plants[i];
        ans++;
      }

      if (restB >= plants[j])
      {
        restB -= plants[j];
      }
      else
      {
        restB = capacityB - plants[j];
        ans++;
      }
    }
    return ans;
  }
};
