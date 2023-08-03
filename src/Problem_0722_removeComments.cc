#include <iostream>
#include <string>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  vector<string> removeComments(vector<string> &source)
  {
    vector<string> ans;
    string new_ine;
    bool inBlock = false;
    for (auto &line : source)
    {
      for (int i = 0; i < line.size(); i++)
      {
        if (inBlock)
        {
          // 在注释块 /**/ 内
          if (i + 1 < line.size() && line[i] == '*' && line[i + 1] == '/')
          {
            inBlock = false;
            i++;
          }
        }
        else
        {
          if (i + 1 < line.size() && line[i] == '/' && line[i + 1] == '*')
          {
            inBlock = true;
            i++;
          }
          else if (i + 1 < line.size() && line[i] == '/' && line[i + 1] == '/')
          {
            // 在注释行 // ，全是注释
            break;
          }
          else
          {
            // 非注释
            new_ine += line[i];
          }
        }
      }
      if (!inBlock && new_ine != "")
      {
        ans.push_back(new_ine);
        new_ine = "";
      }
    }
    return ans;
  }
};

void test()
{
  Solution s;
  vector<string> s1 = {
      "/*Test program */", "int main()", "{ ", "  // variable declaration ", "int a, b, c;", "/* This is a test", "   multiline  ", "   comment for ",
      "   testing */",     "a = b + c;", "}"};
  vector<string> o1 = {"int main()", "{ ", "  ", "int a, b, c;", "a = b + c;", "}"};
  EXPECT_TRUE(o1 == s.removeComments(s1));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
