#include <vector>

using namespace std;

class Solution
{
 public:
  int findWinningPlayer(vector<int>& skills, int k)
  {
    int max_i = 0, win = 0;
    for (int i = 1; i < skills.size() && win < k; i++)
    {
      if (skills[i] > skills[max_i])
      {
        // 打擂台，发现新的最大值
        max_i = i;
        win = 0;
      }
      // 获胜回合 +1
      win++;
    }
    return max_i;
  }
};
