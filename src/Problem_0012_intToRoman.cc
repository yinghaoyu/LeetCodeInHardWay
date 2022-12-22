#include <string>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  // 贪心模拟
  string intToRoman1(int num)
  {
    vector<int> values = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    vector<string> reps = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    string ans;
    for (int i = 0; i < 13; i++)
    {
      while (num >= values[i])
      {
        num -= values[i];
        ans += reps[i];
      }
    }
    return ans;
  }

  // 编码
  string intToRoman2(int num)
  {
    string ans;
    vector<vector<string>> c = {{"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"},
                                {"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"},
                                {"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"},
                                {"", "M", "MM", "MMM"}};
    ans.append(c[3][num / 1000 % 10]);
    ans.append(c[2][num / 100 % 10]);
    ans.append(c[1][num / 10 % 10]);
    ans.append(c[0][num % 10]);
    return ans;
  }
};

void testIntToRoman()
{
  Solution s;
  EXPECT_TRUE("III" == s.intToRoman1(3));
  EXPECT_TRUE("LVIII" == s.intToRoman1(58));
  EXPECT_TRUE("MCMXCIV" == s.intToRoman1(1994));
  EXPECT_TRUE("III" == s.intToRoman2(3));
  EXPECT_TRUE("LVIII" == s.intToRoman2(58));
  EXPECT_TRUE("MCMXCIV" == s.intToRoman2(1994));
  EXPECT_SUMMARY;
}

int main()
{
  testIntToRoman();
  return 0;
}
