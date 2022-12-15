#include <string>
#include <iostream>

#include "UnitTest.h"

using namespace std;

class Solution {
public:
    int getLucky(string s, int k) {
      int n = s.length();
      string dummy;
      for(int i = 0; i < n; i++)
      {
        dummy += std::to_string(s[i]-'a' + 1);
      }
      do
      {
        int sum = 0;
        for(int i = 0; i < dummy.length(); i++)
        {
          sum += dummy[i] - '0';
        }
        dummy = std::to_string(sum);
      }while(--k && dummy.length() > 1);
      return std::stoi(dummy);
    }
};

void testGetLucky()
{
  Solution s;
  EXPECT_EQ_INT(36, s.getLucky("iiii", 1));
  EXPECT_EQ_INT(6, s.getLucky("leetcode", 2));
  EXPECT_EQ_INT(8, s.getLucky("zbax", 2));
  EXPECT_SUMMARY;
}

int main()
{
  testGetLucky();
  return 0;
}
