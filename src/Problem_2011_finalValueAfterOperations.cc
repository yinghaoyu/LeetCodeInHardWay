#include <vector>
#include <string>

#include "UnitTest.h"

using namespace std;

class Solution {
public:
    int finalValueAfterOperations(vector<string>& operations) {
      int ans = 0;
      for(auto&op :operations)
      {
        if(op == "X++" || op == "++X")
        {
          ans++;
        }
        else
        {
          ans--;
        }
      }
      return ans;
    }
};

void testFinalValueAfterOperations()
{
  Solution s;
  vector<string> o1 = {"--X","X++","X++"};
  vector<string> o2 = {"++X","++X","X++"};
  vector<string> o3 = {"X++","++X","--X","X--"};
  EXPECT_EQ_INT(1, s.finalValueAfterOperations(o1));
  EXPECT_EQ_INT(3, s.finalValueAfterOperations(o2));
  EXPECT_EQ_INT(0, s.finalValueAfterOperations(o3));
  EXPECT_SUMMARY;
}

int main()
{
  testFinalValueAfterOperations();
  return 0;
}
