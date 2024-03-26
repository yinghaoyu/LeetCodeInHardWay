#include <string>
#include <vector>

using namespace std;

class Solution
{
 private:
  vector<string> singles = {"",     "One", "Two",   "Three", "Four",
                            "Five", "Six", "Seven", "Eight", "Nine"};
  vector<string> teens = {"Ten",     "Eleven",  "Twelve",    "Thirteen", "Fourteen",
                          "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
  vector<string> tens = {"",      "Ten",   "Twenty",  "Thirty", "Forty",
                         "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
  vector<string> thousands = {"", "Thousand", "Million", "Billion"};

 public:
  string numberToWords(int num)
  {
    if (num == 0)
    {
      // 直接返回 0
      return "Zero";
    }
    string ans;
    // 从高位到低位分 4 组，每组单位依次是 10^9, 10^6, 10^3, 1
    // 除了最低组外，每一组都有对应的单词，分别是 "Billion"，"Million"，"Thousand"
    for (int i = 3, unit = 1e9; i >= 0; i--, unit /= 1e3)
    {
      int curNum = num / unit;
      if (curNum != 0)
      {
        num -= curNum * unit;
        string cur;
        f(cur, curNum);
        cur += thousands[i] + " ";
        ans += cur;
      }
    }
    while (ans.back() == ' ')
    {
      ans.pop_back();
    }
    return ans;
  }

  void f(string& cur, int num)
  {
    if (num == 0)
    {
      return;
    }
    else if (num < 10)
    {
      cur += singles[num] + " ";
    }
    else if (num < 20)
    {
      cur += teens[num - 10] + " ";
    }
    else if (num < 100)
    {
      cur += tens[num / 10] + " ";
      f(cur, num % 10);
    }
    else
    {
      cur += singles[num / 100] + " Hundred ";
      f(cur, num % 100);
    }
  }
};
