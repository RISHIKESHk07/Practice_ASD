#include <iostream>

using namespace std;

const long long MOD = 998244353;
long long count_rem(long long N, long long rem) {
  if (N < rem)
    return 0;
  if (rem == 0)
    return N / 4;
  return (N - rem) / 4 + 1;
}

void solve() {
  long long n, x;
  cin >> n >> x;
  long long left_cat0 = (1 + count_rem(x, 0)) % MOD;
  long long right_cat0 = (count_rem(n, 3) - count_rem(x - 1, 3) + MOD) % MOD;

  long long ans_cat0 = (left_cat0 * right_cat0) % MOD;
  long long left_cat1 = count_rem(x, 2) % MOD;
  long long right_cat1 = (count_rem(n, 1) - count_rem(x - 1, 1) + MOD) % MOD;

  long long ans_cat1 = (left_cat1 * right_cat1) % MOD;

  long long total = (ans_cat0 + ans_cat1) % MOD;
  cout << total << "\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int t;
  cin >> t;
  while (t--) {
    solve();
  }

  return 0;
}
