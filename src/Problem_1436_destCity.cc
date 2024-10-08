#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
  public:
    string destCity(vector<vector<string>> &paths) {
        // A -> B
        // B -> C
        // C -> D
        // 不难发现，在右边集合内的城市，如果是途径城市，那么一定在左边集合内，除了终点城市
        unordered_set<string> A;
        for (auto &p : paths) {
            A.insert(p[0]);
        }
        for (auto &p : paths) {
            if (!A.count(p[1])) {
                return p[1];
            }
        }
        return "";
    }
};
