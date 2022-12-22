#include <string>
#include <unordered_map>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int romanToInt(string s)
  {
    unordered_map<char, int> map = {{'I',1},{'V',5},{'X',10},{'L',50},{'C',100},{'D',500},{'M',1000}};
    int n = s.length();
    int ans = 0;
    for(int i = 0; i < n -1; i ++)
    {
      if(map[s[i]]<map[s[i+1]])
      {
        ans -= map[s[i]];
      }
      else
      {
        ans += map[s[i]];
      }
    }
    return ans + map[s[n-1]];
  }

};

void testRomanToInt()
{
  Solution s;
  EXPECT_EQ_INT(3, s.romanToInt("III"));
  EXPECT_EQ_INT(58, s.romanToInt("LVIII"));
  EXPECT_EQ_INT(1994, s.romanToInt("MCMXCIV"));
  EXPECT_SUMMARY;
}

int main()
{
  testRomanToInt();
  return 0;
}
