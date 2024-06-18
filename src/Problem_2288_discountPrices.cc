#include <cstdio>
#include <string>

using namespace std;

class Solution
{
 public:
  // TODO: optimize it.
  string discountPrices(string sentence, int discount)
  {
    int n = sentence.size();
    string ans;
    for (int i = 0; i < n; i++)
    {
      // 保证必须是单字符 '$' 或者 ' $' 开始
      if (sentence[i] == '$' && (i == 0 || sentence[i - 1] == ' '))
      {
        int start = i;
        bool isdig = true;
        while (i + 1 < n && sentence[i + 1] != ' ')
        {
          i++;
          if (!isdigit(sentence[i]))
          {
            // 保证这个区间全是数字
            isdig = false;
          }
        }
        if (i != start && isdig && (i + 1 == n || sentence[i + 1] == ' '))
        {
          double price = stod(sentence.substr(start + 1, i - start)) * (1.0 - discount / 100.0);
          char buf[64];
          std::snprintf(buf, sizeof(buf), "%.2f", price);
          ans += "$" + std::string(buf);
        }
        else
        {
          ans += sentence.substr(start, i - start + 1);
        }
      }
      else
      {
        ans.push_back(sentence[i]);
      }
    }
    return ans;
  }
};
