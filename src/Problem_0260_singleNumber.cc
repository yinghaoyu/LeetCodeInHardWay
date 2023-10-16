#include <iostream>
#include <vector>

using namespace std;

class Solution
{
 public:
  int lowBit(int x)
  {
    // 防止溢出
    return x == INT32_MIN ? x : x & -x;
  }

  vector<int> singleNumber(vector<int> &nums)
  {
    int XOR = 0;
    for (int num : nums)
    {
      XOR ^= num;
    }
    int rightOne = lowBit(XOR);
    int onlyOne = 0;
    for (int num : nums)
    {
      if (num & rightOne)
      {
        onlyOne ^= num;
      }
    }
    return {onlyOne, XOR ^ onlyOne};
  }
};
