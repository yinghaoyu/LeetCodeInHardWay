#include <vector>

using namespace std;

class Solution
{
 public:
  int findClosest(int x, int y, int z)
  {
    int dx = abs(x - z);
    int dy = abs(y - z);
    if (dx < dy)
    {
      return 1;
    }
    else if (dy < dx)
    {
      return 2;
    }
    else
    {
      return 0;
    }
  }
};
