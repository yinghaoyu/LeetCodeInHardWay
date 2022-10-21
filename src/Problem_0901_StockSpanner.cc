#include <iostream>
#include <vector>

using namespace std;

class StockSpanner
{
 private:
  vector<std::pair<int, int>> stack;
  int idx;

 public:
  StockSpanner()
  {
    idx = -1;
    stack.push_back(std::pair<int, int>(idx, INT32_MAX));
  }

  int next(int price)
  {
    idx++;
    while (!stack.empty() && stack.back().second <= price)
    {
      stack.pop_back();
    }
    int ans = idx - stack.back().first;
    stack.push_back(std::pair<int, int>(idx, price));
    return ans;
  }
};

/**
 * Your StockSpanner object will be instantiated and called as such:
 * StockSpanner* obj = new StockSpanner();
 * int param_1 = obj->next(price);
 */

int main()
{
  return 0;
}
