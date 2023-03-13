#include <iostream>
#include <string>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  vector<string> fizzBuzz(int n)
  {
    vector<string> ans;
    for (int i = 1; i <= n; i++)
    {
      if (i % 15 == 0)
      {
        ans.push_back("FizzBuzz");
      }
      else if (i % 5 == 0)
      {
        ans.push_back("Buzz");
      }
      else if (i % 3 == 0)
      {
        ans.push_back("Fizz");
      }
      else
      {
        ans.push_back(std::to_string(i));
      }
    }
    return ans;
  }
};

void testFizzBuzz()
{
  Solution s;
  vector<string> o1 = {"1", "2", "Fizz"};
  vector<string> o2 = {"1", "2", "Fizz", "4", "Buzz"};
  vector<string> o3 = {"1", "2", "Fizz", "4", "Buzz", "Fizz", "7", "8", "Fizz", "Buzz", "11", "Fizz", "13", "14", "FizzBuzz"};
  EXPECT_TRUE(o1 == s.fizzBuzz(3));
  EXPECT_TRUE(o2 == s.fizzBuzz(5));
  EXPECT_TRUE(o3 == s.fizzBuzz(15));
  EXPECT_SUMMARY;
}

int main()
{
  testFizzBuzz();
  return 0;
}
