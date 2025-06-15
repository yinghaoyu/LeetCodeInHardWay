#include <string>

using namespace std;

class Solution {
  public:
    // 暴力枚举
    int maxDiff1(int num) {
        // 改变x为y
        auto change = [&](int x, int y) {
            string str = to_string(num);
            for (char &c : str) {
                if (c - '0' == x) {
                    c = '0' + y;
                }
            }
            return str;
        };

        int max = num;
        int min = num;
        // 枚举所有可能的情况
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                string str = change(i, j);
                // 过滤前导零
                if (str[0] != '0') {
                    int res = stoi(str);
                    min = std::min(min, res);
                    max = std::max(max, res);
                }
            }
        }
        return max - min;
    }

    // 贪心
    int maxDiff2(int num) {

        auto change = [](string &s, char x, char y) {
            for (char &c : s) {
                if (c == x) {
                    c = y;
                }
            }
        };

        // 如果要让结果最大，从高位开始往低位，
        // 找到第一个不是9的数字，把这个数字全换成9
        string max = to_string(num);
        string min = max;
        for (char c : max) {
            if (c != '9') {
                change(max, c, '9');
                break;
            }
        }

        // 如果要让结果最小，从高位开始往低位，找到第一个数替换成0，同时避免前导零
        for (int i = 0; i < min.size(); i++) {
            char c = min[i];
            if (i == 0) {
                if (c != '1') {
                    change(min, c, '1');
                    break;
                }
            } else {
                if (c != '0' && c != min[0]) {
                    change(min, c, '0');
                    break;
                }
            }
        }
        return stoi(max) - stoi(min);
    }
};
