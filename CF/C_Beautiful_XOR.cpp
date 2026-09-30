#include <iostream>
using namespace std;
int get_bites(int x) {
  if (x == 0)
    return 1;
  return 64 - __builtin_clzll(x);
}
void answer_loop(int a, int b) {
  if (get_bites(a) < get_bites(b)) {
    cout << -1 << endl;
    return;
  }

  int t = a ^ b;
  long long ans_1 = (1ULL << (get_bites(t) - 1));
  long long ans_2 = t ^ ans_1;
  if (ans_1 == 0) {
    cout << 0 << "\n";
  } else if (t > a) {
    cout << 2 << endl;
    cout << ans_2 << " " << ans_1 << endl;

  } else {
    cout << 1 << endl << t << endl;
  }
}
int main() {
  int t;
  cin >> t;
  while (t) {
    int a, b;
    cin >> a >> b;
    answer_loop(a, b);
    t--;
  }
  return 0;
}
