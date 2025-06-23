#include <vector>

using namespace std;

class Solution {
  public:
    long long kMirror(int k, int n) {
        auto isPalindrome = [&](long long x) {
            int digit[100] = {0};
            int length = -1;
            while (x) {
                ++length;
                digit[length] = x % k;
                x /= k;
            }
            for (int i = 0, j = length; i < j; ++i, --j) {
                if (digit[i] != digit[j]) {
                    return false;
                }
            }
            return true;
        };

        int left = 1;
        int count = 0;
        long long ans = 0;
        while (count < n) {
            // 折半搜索，分左右两个部分数字
            int right = left * 10;
            // 0表示枚举奇数长度回文，1表示枚举偶数长度回文
            for (int op = 0; op < 2; op++) {
                // 枚举数字
                for (int i = left; i < right && count < n; i++) {
                    long long num = i;
                    int x = op == 0 ? (num / 10) : num;
                    // 拼接数字
                    while (x != 0) {
                        num = num * 10 + x % 10;
                        x /= 10;
                    }
                    // 这样拼接出来的数字一定是10进制下对称，再检验是否k进制下对称
                    if (isPalindrome(num)) {
                        count++;
                        ans += num;
                    }
                }
            }
            left = right;
        }
        return ans;
    }
};
