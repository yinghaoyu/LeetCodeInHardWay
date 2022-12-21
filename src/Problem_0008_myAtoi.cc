#include <cctype>
#include <cstdint>
#include <algorithm>
#include <iostream>
#include <string>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
   	int myAtoi(string s) {
		if (s.length() == 0) {
			return 0;
		}
    s = trim(s); 
		s = removeHeadZero(s);
		if (s.length() == 0) {
			return 0;
		}
		if (!isValid(s)) {
			return 0;
		}
		// str 是符合日常书写的，正经整数形式
		bool posi = s[0] == '-' ? false : true;
		int minq = INT32_MIN / 10;
		int minr = INT32_MIN % 10;
		int res = 0;
		int cur = 0;
		for (int i = (s[0] == '-' || s[0] == '+') ? 1 : 0; i < s.length(); i++) {
			cur = '0' - s[i];
			if ((res < minq) || (res == minq && cur < minr)) {
				return posi ? INT32_MAX : INT32_MIN;
			}
			res = res * 10 + cur;
		}
		// res 负
		if (posi && res == INT32_MIN) {
			return INT32_MAX;
		}
		return posi ? -res : res;
	}

    // string.length() > 0
	string removeHeadZero(string str) {
		bool r = str[0] == '+' || str[0] == '-';
    int s = r ? 1 : 0;
    for (; s < str.length(); s++)
    {
      if (str[s] != '0')
      {
        break;
      }
    }
    // s 到了第一个不是'0'字符的位置
		int e = -1;
		// 左<-右
		for (int i = str.length() - 1; i >= (r ? 1 : 0); i--) {
			if (str[i] < '0' || str[i] > '9') {
				e = i;
			}
		}
		// e 到了最左的 不是数字字符的位置
		return (r ? str.substr(0,1) : "") + str.substr(s, e == -1 ? str.length() - s : e - s);
	}

std::string trim(const std::string &s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && isspace(*it))
        it++;

    std::string::const_reverse_iterator rit = s.rbegin();
    while (rit.base() != it && isspace(*rit))
        rit++;

    return std::string(it, rit.base());
}
	bool isValid(string s) {
		if (s[0] != '-' && s[0] != '+' && (s[0] < '0' || s[0] > '9')) {
			return false;
		}
		if ((s[0] == '-' || s[0] == '+') && s.length() == 1) {
			return false;
		}
		// 0 +... -... num
		for (int i = 1; i < s.length(); i++) {
			if (s[i] < '0' || s[i] > '9') {
				return false;
			}
		}
		return true;
	}
};

void testMyAtoi()
{
  Solution s;
  EXPECT_EQ_INT(42, s.myAtoi("42"));
  EXPECT_EQ_INT(-42, s.myAtoi("     -42"));
  EXPECT_EQ_INT(4193, s.myAtoi("4193 with words"));
  EXPECT_EQ_INT(0, s.myAtoi("words and 987"));
  EXPECT_EQ_INT(~(1<<31), s.myAtoi("2147483648"));
  EXPECT_EQ_INT(1 << 31, s.myAtoi("-2147483649"));
  EXPECT_SUMMARY;
}

int main()
{
  testMyAtoi();
  return 0;
}
