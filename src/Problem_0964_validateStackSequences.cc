#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  bool validateStackSequences(vector<int> &pushed, vector<int> &popped)
  {
    vector<int> stack;
    int j = 0;
    for (int i = 0; i < pushed.size(); i++)
    {
      stack.push_back(pushed[i]);
      while (!stack.empty() && stack.back() == popped[j])
      {
        stack.pop_back();
        j++;
      }
    }
    return stack.empty();
  }
};

void testValidateStackSequences()
{
  Solution s;
  vector<int> pushed1 = {1, 2, 3, 4, 5};
  vector<int> popped1 = {4, 5, 3, 2, 1};
  vector<int> pushed2 = {1, 2, 3, 4, 5};
  vector<int> popped2 = {4, 3, 5, 1, 2};
  EXPECT_TRUE(s.validateStackSequences(pushed1, popped1));
  EXPECT_FALSE(s.validateStackSequences(pushed2, popped2));
  EXPECT_SUMMARY;
}

int main()
{
  testValidateStackSequences();
  return 0;
}
