#include <vector>

using namespace std;

class Solution
{
 public:
  int maximum(int a, int b)
  {
    long diff = (long) a - (long) b;
    int sign = (diff >> 63) & 0x01;
    return (sign ^ 1) * a + sign * b;
  }
};
