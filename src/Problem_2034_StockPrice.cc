#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

using namespace std;

class StockPrice
{
  using pii = std::pair<int, int>;
  int maxTimestamp;
  unordered_map<int, int> cur;
  priority_queue<pii, vector<pii>, greater<pii>> min;
  priority_queue<pii, vector<pii>, less<pii>> max;

 public:
  StockPrice() { maxTimestamp = 0; }

  void update(int timestamp, int price)
  {
    maxTimestamp = std::max(maxTimestamp, timestamp);
    cur[timestamp] = price;
    // max 和 min 在同一时间戳下会有不同的价格
    max.emplace(price, timestamp);
    min.emplace(price, timestamp);
  }

  int current() { return cur[maxTimestamp]; }

  int maximum()
  {
    while (true)
    {
      auto [price, timestamp] = max.top();
      if (cur[timestamp] == price)
      {
        // 当这个价格和实际价格相等，说明是有效值最大值
        // 就算同一时间戳下，存在更小的价格没有 pop，也没有关系，下次会 pop
        return price;
      }
      max.pop();
    }
  }

  int minimum()
  {
    while (true)
    {
      auto [price, timestamp] = min.top();
      if (cur[timestamp] == price)
      {
        return price;
      }
      min.pop();
    }
  }
};

/**
 * Your StockPrice object will be instantiated and called as such:
 * StockPrice* obj = new StockPrice();
 * obj->update(timestamp,price);
 * int param_2 = obj->current();
 * int param_3 = obj->maximum();
 * int param_4 = obj->minimum();
 */
