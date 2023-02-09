#include <unordered_map>
#include <vector>
#include "UnitTest.h"

using namespace std;

class AuthenticationManager
{
 public:
  AuthenticationManager(int timeToLive) { ttl = timeToLive; }

  void generate(string tokenId, int currentTime) { items.emplace(tokenId, currentTime); }

  void renew(string tokenId, int currentTime)
  {
    if (items.count(tokenId))
    {
      if (currentTime < items[tokenId] + ttl)
      {
        items[tokenId] = currentTime;
      }
    }
  }

  int countUnexpiredTokens(int currentTime)
  {
    int ans = 0;
    for (auto &[tokenId, time] : items)
    {
      if (time + ttl > currentTime)
      {
        ans++;
      }
    }
    return ans;
  }
  int ttl;
  unordered_map<string, int> items;
};

/**
 * Your AuthenticationManager object will be instantiated and called as such:
 * AuthenticationManager* obj = new AuthenticationManager(timeToLive);
 * obj->generate(tokenId,currentTime);
 * obj->renew(tokenId,currentTime);
 * int param_3 = obj->countUnexpiredTokens(currentTime);
 */
