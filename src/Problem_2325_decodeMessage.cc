#include <cctype>
#include <iostream>
#include <string>
#include <unordered_map>
#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  string decodeMessage(string key, string message)
  {
    char c = 'a';
    std::unordered_map<char, char> map;
    for (auto & i: key)
    {
      if (i != ' ' && map.count(i) == 0)
      {
        map[i] = c++;
      }
    }
    for (auto & i:message)
    {
      if (map.count(i))
      {
        i = map[i];
      }
    }
    return message;
  };
};

void testDecodeMessage()
{
  Solution s;
  string k1 = "the quick brown fox jumps over the lazy dog";
  string m1 = "vkbs bs t suepuv";
  string o1 = "this is a secret";
  string k2 = "eljuxhpwnyrdgtqkviszcfmabo";
  string m2 = "zwx hnfx lqantp mnoeius ycgk vcnjrdb";
  string o2 = "the five boxing wizards jump quickly";
  EXPECT_TRUE(o1 == s.decodeMessage(k1, m1));
  EXPECT_TRUE(o2 == s.decodeMessage(k2, m2));
  EXPECT_SUMMARY;
}

int main()
{
  testDecodeMessage();
  return 0;
}
