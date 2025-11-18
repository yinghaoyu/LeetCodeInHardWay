#include <vector>

using namespace std;

class Solution
{
 public:
  bool f(int i, vector<int>& bits)
  {
    if (i == bits.size())
    {
      return false;
    }

    if (i == bits.size() - 1)
    {
      return bits[i] == 0;
    }

    if (bits[i] == 0)
    {
      return f(i + 1, bits);
    }
    else
    {
      return f(i + 2, bits);
    }
  }

  // 暴力递归
  // bool isOneBitCharacter(vector<int>& bits) { return f(0, bits); }

  bool isOneBitCharacter(vector<int>& bits)
  {
    int n = bits.size(), i = 0;
    while (i < n - 1)
    {
      i += bits[i] + 1;
    }
    return i == n - 1;
  }
};
