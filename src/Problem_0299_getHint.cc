#include <string>
#include <vector>

using namespace std;

class Solution
{
 public:
  string getHint(string secret, string guess)
  {
    int A = 0;
    vector<int> cntS(10), cntG(10);
    for (int i = 0; i < secret.length(); ++i)
    {
      if (secret[i] == guess[i])
      {
        // 数字和位置都相同，统计公牛数
        ++A;
      }
      else
      {
        // 数字相同位置不同
        // 统计各字符出现的数目
        ++cntS[secret[i] - '0'];
        ++cntG[guess[i] - '0'];
      }
    }
    int B = 0;
    for (int i = 0; i < 10; ++i)
    {
      // 数字相同的只能取最小值统计母牛数
      B += min(cntS[i], cntG[i]);
    }
    return std::to_string(A) + "A" + std::to_string(B) + "B";
  }
};
