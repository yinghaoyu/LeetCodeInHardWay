#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

#include "UnitTest.h"

using namespace std;

class Solution {
public:
    int maxEqualRowsAfterFlips(vector<vector<int>>& matrix) {
       int n = matrix.size();
       int m = matrix[0].size();
        unordered_map<string, int> map;
        for(int i = 0; i < m; i++)
        {
          string s = string(n, '0');
          for(int j = 0; j < n; j++)
          {
            // 如果 matrix[i][j] 为 1，则对元素进行翻转
            s[j] = '0' + (matrix[i][j] ^ matrix[i][0]);
          }
          map[s]++;
        }
        int ans = 0;
        for(auto& [k, v]:map)
        {
          ans = std::max(ans, v);
        }
        return ans;
    }
};

void testMaxEqualRowsAfterFlips()
{
  Solution s;
  vector<vector<int>> n1 = {{0,1},{1,1}};
  vector<vector<int>> n2 = {{0,1},{1,0}};
  vector<vector<int>> n3 = {{0,0,0},{0,0,1},{1,1,0}};
  EXPECT_EQ_INT(1, s.maxEqualRowsAfterFlips(n1));
  EXPECT_EQ_INT(2, s.maxEqualRowsAfterFlips(n2));
  EXPECT_EQ_INT(2, s.maxEqualRowsAfterFlips(n3));
  EXPECT_SUMMARY;
}

int main()
{
  testMaxEqualRowsAfterFlips();
  return 0;
}
