#include <iostream>
#include <string>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  bool squareIsWhite(string coordinates)
  {
    int x = coordinates[0] - 'a';
    int y = coordinates[1] - '0';
    return !((x + y) & 1);
  }
};

void testSquareIsWhite()
{
  Solution s;
  EXPECT_FALSE(s.squareIsWhite("a1"));
  EXPECT_TRUE(s.squareIsWhite("h1"));
  EXPECT_FALSE(s.squareIsWhite("c7"));
  EXPECT_SUMMARY;
}

int main()
{
  testSquareIsWhite();
  return 0;
}
