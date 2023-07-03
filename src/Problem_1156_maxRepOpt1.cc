#include <iostream>
#include <unordered_map>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int maxRepOpt1(string text)
  {
    unordered_map<char, int> count;
    for (auto &c : text)
    {
      count[c]++;
    }
    int ans = 0;
    for (int i = 0; i < text.size();)
    {
      // step1: 找出当前连续的一段[i,j)
      int j = i;
      while (j < text.size() && text[j] == text[i])
      {
        j++;
      }

      {
        // 这一步可以并入step3，为了便于理解，提取出来
        // step2:
        int cur_cnt = j - i;
        // 如果这段长度小于该字符出现的总次数，
        // 并且前面或者后面有空位，可以将其他地方的字符与text[i-1]或text[j]交换，
        // 得到更长的一段字符，则使用 cur_cnt + 1 更新答案
        if (cur_cnt < count[text[i]] && (j < text.size() || i > 0))
        {
          ans = std::max(ans, cur_cnt + 1);
        }
      }

      // step3: 找出这一段后面与之相隔一个不同字符的另一段[j+1, k)
      // 如果不存在则 k = j + 1
      int k = j + 1;
      while (k < text.size() && text[k] == text[i])
      {
        k++;
      }
      ans = std::max(ans, std::min(k - i, count[text[i]]));
      i = j;
    }
    return ans;
  }
};

void test()
{
  Solution s;
  EXPECT_EQ_INT(3, s.maxRepOpt1("ababa"));
  EXPECT_EQ_INT(6, s.maxRepOpt1("aaabaaa"));
  EXPECT_EQ_INT(5, s.maxRepOpt1("aaaaa"));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
