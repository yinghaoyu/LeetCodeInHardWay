#include <string>
#include <vector>

using namespace std;

class Solution {
  public:
    vector<string> divideString(string s, int k, char fill) {
        int n = s.length();
        vector<string> ans;
        for (int i = 0; i < n; i += k) {
            // if (n - i < k) {
            //     ans.push_back(s.substr(i) + string(k - n + i, fill));
            // } else {
            // 这里利用了substr函数的特性，当长度k大于剩余长度时，只会保留剩余长度
            // 减少指令预测
            ans.push_back(s.substr(i, k));
            // }
        }
        // 补充最后一组字符
        ans.back() += string(k - ans.back().size(), fill);

        return ans;
    }
};
