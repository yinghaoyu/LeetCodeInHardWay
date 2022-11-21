#include <iostream>
#include <string>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  string interpret(string command)
  {
    string res;
    int n = command.length();
    int state = 0;
    for (int i = 0; i < n; i++)
    {
      char c = command[i];
      if (c == 'G')
      {
        res.push_back('G');
      }
      else if (c == '(')
      {
        state = 1;
      }
      else if (c == ')')
      {
        if (state == 1)
        {
          res.push_back('o');
        }
        else
        {
          res.push_back('a');
          res.push_back('l');
        }
        state = 0;
      }
      else
      {
        state = 2;
      }
    }
    return res;
  }
};

bool isStringEqual(string a, string b)
{
  return a == b;
}

void testInterpret()
{
  Solution s;
  EXPECT_TRUE(isStringEqual("Goal", s.interpret("G()(al)")));
  EXPECT_TRUE(isStringEqual("Gooooal", s.interpret("G()()()()(al)")));
  EXPECT_TRUE(isStringEqual("alGalooG", s.interpret("(al)G(al)()()G")));
  EXPECT_SUMMARY;
}

int main()
{
  testInterpret();
  return 0;
}
