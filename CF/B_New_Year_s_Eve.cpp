#include <iostream>
using namespace std;
int get_bites(unsigned long long x) {
  if (x == 0)
    return 1;
  return 64 - __builtin_clzll(x);
}
unsigned long long power(unsigned long long x, unsigned long long y) {
  unsigned long long res = 1;
  unsigned long long base = x;
  while (y != 0) {
    if (y & 1) {
      res = res * base;
    }
    base = base * base;
    y = y >> 1;
  }
  return res;
}
int main() {
  unsigned long long n, k;
  cin >> n >> k;
  auto b = get_bites(n);
  if (k > b) {
    k = b;
  }
  unsigned long long res;
  if (k == 1) {
    cout << n;
  } else {
    res = (b == 64) ? (~0ULL) : (1ULL << b) - 1;
    cout << res;
  }

  return 0;
}
