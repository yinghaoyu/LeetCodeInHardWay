class Solution
{
 public:
  int exchangeBits(int num)
  {
    int odd = num & 0x55555555;
    int even = num & 0xaaaaaaaa;
    odd = odd << 1;
    even = (unsigned int) even >> 1;
    return odd | even;
  }
};
