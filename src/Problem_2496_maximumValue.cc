#include <cctype>
#include <iostream>
#include <string>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int maximumValue(vector<string> &strs)
  {
    int ans = 0;
    for (auto &str : strs)
    {
      bool isNumber = true;
      for (auto &c : str)
      {
        if (isalpha(c))
        {
          isNumber = false;
          ans = std::max(ans, static_cast<int>(str.length()));
          break;
        }
      }
      if (isNumber)
      {
        ans = std::max(ans, stoi(str));
      }
    }
    return ans;
  }
};

void test()
{
  Solution s;
  vector<string> n1 = {"alic3", "bob", "3", "4", "00000"};
  vector<string> n2 = {"1", "01", "001", "0001"};
  EXPECT_EQ_INT(5, s.maximumValue(n1));
  EXPECT_EQ_INT(1, s.maximumValue(n2));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
