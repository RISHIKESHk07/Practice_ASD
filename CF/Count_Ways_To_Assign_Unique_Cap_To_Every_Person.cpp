#include <iostream>
#include <map>
#include <vector>

using namespace std;

void rec_func(int &cur_n, int size_n, map<int, bool> &m,
              vector<vector<int>> &ans, vector<int> &cur_ans,
              vector<int> &per_item_cursor, vector<vector<int>> v) {
  cout << cur_n << "_" << cur_ans.size() << ans.size() << endl;
  for (auto i : cur_ans) {
    cout << i << endl;
  }
  int l_cur_n = cur_n;
  for (auto i = 0; i < v[l_cur_n].size(); i++) {

    auto t = v[l_cur_n][i];
    if (!m[t]) {
      cur_ans.push_back(t);

      m[t] = 1;
      if (cur_n < size_n - 1) {
        cur_n++;
        rec_func(cur_n, size_n, m, ans, cur_ans, per_item_cursor, v);
        // this two lines remove the current ' instance for moving sideways to
        // next option in vector
        cur_n = l_cur_n;
        m[t] = 0;
        cur_ans.pop_back();
      } else if (cur_n == size_n - 1) {
        ans.push_back(cur_ans);
        cur_ans.pop_back();
        m[t] = 0;
      }
    }
  }

  // remove the layers addition here , saying we have looked at possible for
  // this instance

  if (l_cur_n > 0) {
    cur_n = l_cur_n - 1;
  }
  return;
};

void recursive_answer(vector<vector<int>> v, vector<vector<int>> &ans) {
  int size_n = v.size();
  map<int, bool> m;
  vector<int> cur_ans = {};
  vector<int> per_item_cursor(size_n, 0);
  int cur_n = 0;
  rec_func(cur_n, size_n, m, ans, cur_ans, per_item_cursor, v);
}

int mem_recv(vector<vector<int>> &c, int cap, int asigned_mask,
             vector<vector<int>> &m, int n) {
  if (asigned_mask == ((1 << c[0].size()) - 1)) {
    return 1;
  }
  if (cap > 100)
    return 0;
  if (m[cap][asigned_mask] != -1) {
    return m[cap][asigned_mask];
  }
  int ways = mem_recv(c, cap + 1, asigned_mask, m, n);
  for (auto s : c[cap]) {
    if ((asigned_mask & (1 << n)) == 0) {
      ways += mem_recv(c, cap + 1, (asigned_mask | (1 << s)), m, n);
    }
  }
  m[cap][asigned_mask] = ways;

  return ways;
}

int dp_mem(vector<vector<int>> v) {
  vector<vector<int>> captp;
  int allmask = (1 << v.size()) - 1;

  for (auto i = 0; i < v.size(); i++) {
    for (auto j : v[i]) {
      captp[j].push_back(i);
    }
  }
  int cap = 1;
  int asigned_mask = 0;
  vector<vector<int>> m(101, vector<int>(1 << v.size(), -1));

  return mem_recv(captp, cap, asigned_mask, m, v.size());
}

int dp_solution(vector<vector<int>> v) {
  vector<vector<int>> captp(101);
  int allmask = (1 << v.size()) - 1;

  for (auto i = 0; i < v.size(); i++) {
    for (auto j : v[i]) {
      captp[j].push_back(i);
    }
  }
  vector<vector<int>> dp(102, vector<int>(1 << v.size(), 0));
  dp[0][0] = 1;
  for (int y = 1; y <= 100; y++) {
    for (int l = 0; l <= allmask; l++) {
      if (dp[y - 1][l] == 0) {
        continue;
      }
      // skip current cap
      dp[y][l] += dp[y - 1][l];
      // take any person for this cap for this particular state l; its in bits
      // rep
      for (auto k : captp[y]) {
        if ((l & (1 << k)) == 0) {
          dp[y][l | (1 << k)] += dp[y - 1][l];
        }
      }
    }
  }
  return dp[100][allmask];
}

int main() {

  vector<vector<int>> caps = {{1, 2, 3}, {1, 2}, {3, 4}, {4, 5}};
  // vector<vector<int>> ans;
  // recursive_answer(caps, ans);
  // int c = 0;
  // for (auto i : ans) {
  //   cout << "---- " << c << endl;
  //   for (auto j : i) {
  //     cout << j << " ";
  //   }
  //   cout << "-----" << endl;
  //   c++;
  // }
  auto d = dp_solution(caps);
  cout << d << endl;
  return 0;
}
