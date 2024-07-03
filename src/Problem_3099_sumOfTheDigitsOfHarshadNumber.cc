#include <vector>

using namespace std;

class Solution
{
 public:
  int sumOfTheDigitsOfHarshadNumber(int x)
  {
    int bitSum = 0;
    int cur = x;
    while (cur != 0)
    {
      bitSum += cur % 10;
      cur /= 10;
    }
    return x % bitSum == 0 ? bitSum : -1;
  }
};
