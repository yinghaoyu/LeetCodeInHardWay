#include <string>
#include <unordered_map>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  string fractionToDecimal(int numerator, int denominator)
  {
    if (numerator == 0)
    {
      return "0";
    }
    string ans;
    // '+' or '-'
    if ((numerator ^ denominator) < 0)
    {
      ans.append("-");
    }
    // * 1ll avoid -2147483648
    long long num = std::abs(numerator * 1ll);
    long long den = std::abs(denominator * 1ll);
    // integer part
    ans.append(std::to_string(num / den));
    num %= den;
    if (num == 0)
    {
      return ans;
    }
    // fraction part
    ans.append(".");
    unordered_map<long long, int> map;
    map.emplace(num, ans.length());
    while (num != 0)
    {
      num *= 10;
      ans.append(std::to_string(num / den));
      num %= den;
      if (map.count(num))
      {
        int index = map.at(num);
        ans.insert(index, "(");
        ans.append(")");
        break;
      }
      else
      {
        map[num] = ans.length();
      }
    }
    return ans;
  }
};

void testFractionToDecimal()
{
  Solution s;
  EXPECT_TRUE("0.5" == s.fractionToDecimal(1, 2));
  EXPECT_TRUE("2" == s.fractionToDecimal(2, 1));
  EXPECT_TRUE("0.(012)" == s.fractionToDecimal(4, 333));
  EXPECT_SUMMARY;
}

int main()
{
  testFractionToDecimal();
  return 0;
}
