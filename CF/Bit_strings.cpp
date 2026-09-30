#include <iostream>
using namespace std;
long long power(long x, long long y, long long mod) {
  long long res = 1;
  x = x % mod;
  while (y > 0) {
    if (y % 2 == 1) {
      res = (res * x) % mod;
    }
    x = (x * x) % mod;
    y = y / 2;
  }
  return res;
}
int main() {
  int n;
  long long mod = 1e9 + 7;
  cin >> n;
  cout << power(2, n, mod);
  return 0;
}
