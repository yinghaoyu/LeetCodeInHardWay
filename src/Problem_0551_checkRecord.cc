#include <string>

using namespace std;

class Solution
{
 public:
  bool checkRecord(string s)
  {
    int A = 0;
    int L = 0;
    for (char c : s)
    {
      if (c == 'L')
      {
        L++;
        if (L == 3)
        {
          return false;
        }
      }
      else
      {
        L = 0;
        if (c == 'A')
        {
          A++;
        }
        if (A == 2)
        {
          return false;
        }
      }
    }
    return true;
  }
};
