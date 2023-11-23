#include <iostream>
#include <string>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
  using Entity = std::pair<string, char>;

 public:
  string entityParser(string text)
  {
    vector<Entity> EntryList = {{"&quot;", '"'}, {"&apos;", '\''}, {"&amp;", '&'}, {"&gt;", '>'}, {"&lt;", '<'}, {"&frasl;", '/'}};
    string ans;
    for (int i = 0; i < text.length();)
    {
      bool isEntity = false;
      if (text[i] == '&')
      {
        for (auto& [e, c] : EntryList)
        {
          if (text.substr(i, e.size()) == e)
          {
            ans.push_back(c);
            i += e.size();
            isEntity = true;
            break;
          }
        }
      }
      if (!isEntity)
      {
        ans.push_back(text[i++]);
      }
    }
    return ans;
  }
};

void test()
{
  Solution s;
  EXPECT_TRUE("& is an HTML entity but &ambassador; is not." == s.entityParser("&amp; is an HTML entity but &ambassador; is not."));
  EXPECT_TRUE("and I quote: \"...\"" == s.entityParser("and I quote: &quot;...&quot;"));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
