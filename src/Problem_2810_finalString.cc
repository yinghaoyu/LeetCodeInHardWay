#include <deque>
#include <string>

using namespace std;

class Solution
{
 public:
  string finalString(string s)
  {
    deque<char> q;
    bool tail = true;
    for (char c : s)
    {
      if (c == 'i')
      {
        tail = !tail;
      }
      else if (tail)
      {
        q.push_back(c);
      }
      else
      {
        q.push_front(c);
      }
    }
    return tail ? string(q.begin(), q.end()) : string(q.rbegin(), q.rend());
  }
};
