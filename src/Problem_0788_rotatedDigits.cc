#include <iostream>
#include <string>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int rotatedDigits(int n)
  {
    int ans = 0;
    vector<int> tag = {0, 0, 1, -1, -1, 1, 1, -1, 0, 1};
    for (int i = 1; i <= n; i++)
    {
      string s = std::to_string(i);
      bool valid = true;
      bool diff = false;
      for (int i = 0; i < s.length(); i++)
      {
        if (tag[s[i] - '0'] == -1)
        {
          valid = false;
          break;
        }
        if (tag[s[i] - '0'] == 1)
        {
          diff = true;
        }
      }
      if (valid && diff)
      {
        ans++;
      }
    }
    return ans;
  }
};

void testRotatedDigits()
{
  Solution s;
  EXPECT_EQ_INT(4, s.rotatedDigits(10));
  EXPECT_EQ_INT(0, s.rotatedDigits(1));
  EXPECT_EQ_INT(1, s.rotatedDigits(2));
  EXPECT_SUMMARY;
}

int main()
{
  testRotatedDigits();
  return 0;
}
