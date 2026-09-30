#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

int main() {
  long long int n;
  cin >> n;
  long long int len;
  std::string str = std::to_string(n);
  len = str.length();
  if (len % 2 == 1) {
    len++;
  }
  long long res = -1;
  for (int l = len; l <= 10; l += 2) {
    std::string s = string(l / 2, '4') + string(l / 2, '7');
    do {
      long long val = stoll(s);
      if (val >= n) {
        cout << val << endl;
        res = val;
        return 0;
      }
    } while (next_permutation(s.begin(), s.end()));
  }

  return 0;
}
