#include <string>

using namespace std;

class Solution
{
 public:
  string capitalizeTitle(string title)
  {
    int n = title.length();
    int l = 0;
    int r = 0;
    while (r < n)
    {
      while (r < n && title[r] != ' ')
      {
        r++;
      }
      if (r - l > 2)
      {
        title[l++] = toupper(title[l]);
      }
      while (l < r)
      {
        title[l++] = tolower(title[l]);
      }
      l = ++r;
    }
    return title;
  }
};
