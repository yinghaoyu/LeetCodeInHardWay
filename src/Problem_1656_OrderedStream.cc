#include <iostream>
#include <string>
#include <vector>

using namespace std;

class OrderedStream
{
 public:
  OrderedStream(int n)
  {
    buf_ = vector<string>(n + 1, "");
    ptr_ = buf_.begin() + 1;
  }

  vector<string> insert(int idKey, string value)
  {
    buf_[idKey] = value;
    vector<string> ans;
    for (; ptr_ != buf_.end(); ptr_++)
    {
      if (ptr_->length() != 0)
      {
        ans.push_back(*ptr_);
      }
      else
      {
        break;
      }
    }
    return ans;
  }

 private:
  vector<string> buf_;
  vector<string>::iterator ptr_;
};
