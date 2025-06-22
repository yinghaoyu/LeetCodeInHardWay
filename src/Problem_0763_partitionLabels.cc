#include <string>
#include <vector>

using namespace std;

class Solution {
  public:
    vector<int> partitionLabels(string s) {
        int last[26] = {0};
        int n = s.length();
        for (int i = 0; i < n; i++) {
            last[s[i] - 'a'] = i;
        }
        vector<int> ans;
        int start = 0;
        int end = 0;
        for (int i = 0; i < n; i++) {
            end = std::max(end, last[s[i] - 'a']);
            if (i == end) {
                ans.push_back(end - start + 1);
                start = end + 1;
            }
        }
        return ans;
    }
};
