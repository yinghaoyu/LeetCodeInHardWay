#include <string>
#include <unordered_map>

using namespace std;

class Solution {
  public:
    // 单射：对于任意 x ，都有唯一的 y 与之对应
    // 满射：对于任意 y ，至少存在一个 x 与之对应
    // 双射：既是单射又是满射，又称为一一对应
    bool isIsomorphic(string s, string t) {
        unordered_map<char, char> s2t;
        unordered_map<char, char> t2s;
        int n = s.length();
        for (int i = 0; i < n; i++) {
            char x = s[i];
            char y = t[i];
            if ((s2t.count(x) && s2t[x] != y) ||
                (t2s.count(y) && t2s[y] != x)) {
                return false;
            }
            s2t[x] = y;
            t2s[y] = x;
        }
        return true;
    }
};
