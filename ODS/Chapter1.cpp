#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>
using namespace std;

int count_lines(string &filename) {
  auto buffer_size = 64 * 1024;
  vector<char> buffer(buffer_size);
  int line_count = 0;
  ifstream fr(filename);
  while (fr.read(buffer.data(), buffer_size) || fr.gcount() > 0) {
    auto bytes = fr.gcount();
    if (bytes > 0) {
      line_count += count(buffer.begin(), buffer.begin() + bytes, '\n');
    }
  }
  return line_count;
}

// dynamic array
template <typename T> class dy_arr {
public:
  int size = 0;
  T *arr;

  dy_arr(int init_size = 0) {
    size = init_size;
    T *new_arr = new T[init_size];
    arr = new_arr;
  }

  void push_back_dy_arr(T k) {
    auto t = size;
    size += 1;
    auto new_dya_ = new T[size];
    memcpy(new_dya_, arr, t * sizeof(T));
    new_dya_[t] = k;
    delete[] (arr);
    arr = new_dya_;
  }

  void set(int index, T sk) {
    for (int i = 0; i < size; i++) {
      if (i == index) {
        arr[i] = sk;
        break;
      }
    }
  }
  void print() {
    cout << "Printing the dynamic array:" << "size:" << size << std::endl;
    for (int k = 0; k < size; k++) {
      std::cout << arr[k] << std::endl;
    }
  }
  void remove(int index) {
    if (index < 0 || index >= size) {
      return;
    }
    T *new_arr = new T[size - 1];
    if (index > 0) {
      std::memcpy(new_arr, arr, index * sizeof(T));
    }
    if (index < size - 1) {
      std::memcpy(new_arr + index, arr + index + 1,
                  (size - index - 1) * sizeof(T));
    }
    delete[] arr;
    arr = new_arr;
    size -= 1;
  }

  int search(T sk) {
    for (int i = 0; i < size; i++) {
      if (arr[i] == sk) {
        return i;
      }
    }
    return -1;
  }
};
struct Pair {
  int k;
  int v;
};
class dy_set {

public:
  dy_arr<Pair> storage;
  bool ordered = false;

  dy_set(bool is_ordered) : ordered(is_ordered) {}
  int search_unordered(int k) {
    for (int i = 0; i < storage.size; i++) {
      if (storage.arr[i].k == k)
        return i;
    }
    return -1;
  }
  int search_ordered(int k) {
    int l = 0;
    int h = storage.size - 1;

    while (l <= h) {
      auto mid = l + (h - l) / 2;
      if (storage.arr[mid].k == k)
        return mid;
      else if (storage.arr[mid].k > k)
        h = mid - 1;
      else
        l = mid + 1;
    }
    return -1;
  }
  int search(int key) {
    return ordered ? search_ordered(key) : search_unordered(key);
  }

  void insert(int key, int value) {
    if (search(key) != -1)
      return;
    if (!ordered) {
      storage.push_back_dy_arr({key, value});
    } else {
      int target_idx = 0;
      while (target_idx < storage.size && storage.arr[target_idx].k < key) {
        target_idx++;
      }
      storage.push_back_dy_arr({0, 0});
      for (int i = storage.size - 1; i > target_idx; i--) {
        storage.arr[i] = storage.arr[i - 1];
      }
      storage.set(target_idx, {key, value});
    }
  }

  void remove(int key) {
    int idx = search(key);
    if (idx != -1) {
      storage.remove(idx);
    }
  }
  void print() {
    for (int i = 0; i < storage.size; i++) {
      std::cout << "[" << storage.arr[i].k << ": " << storage.arr[i].v << "] ";
    }
    std::cout << "\n";
  }
};

int main() {

  // vector<string> vs;
  // ofstream outputStream("input.txt");
  // std::ifstream inputFile("input.txt");
  //
  // for (int i = 0; i <= (1e3 - 20); i++) {
  //   string temp = to_string(i);
  //   outputStream << temp << endl;
  //   if (i % 44 == 0 && i != 0) {
  //     outputStream << "" << endl;
  //   }
  // }
  // Q1.1.2
  // int i = 0;
  // string fn = "input.txt";
  // auto cl = count_lines(fn);
  // while (i <= cl) {
  //   string line;
  //   int d = 0;
  //   while (std::getline(inputFile, line) && d <= 50) {
  //     vs.push_back(line);
  //     d++;
  //   }
  //
  //   if (cl - i >= 50) {
  //     for (int j = 49; j >= 0; j--) {
  //       cout << vs[j + i] << std::endl;
  //     }
  //     i += 50;
  //     cout << "..." << i << "." << d  -1 << "." << cl << endl;
  //   } else {
  //     for (int k = cl - i-1; k >= 0; k--) {
  //       cout << vs[i + k] << endl;
  //     }
  //     break;
  //   }
  // }
  //  Q1.1.3
  // deque<string> q;
  // string str;
  // while (getline(inputFile, str)) {
  //   q.push_back(str);
  //   string temp = q.back();
  //   if (q.size() > 43)
  //     q.pop_front();
  //   if (temp.size() == 0) {
  //     cout << q[q.size() - 2] << endl;
  //     break;
  //   }
  // }
  // Q1 remaining questions can be solved using map or vector .
  // Q1.2 is stack behavious in the form of prefixs
  // Q1.3 stack can be used to check this in O(n)
  // Q1.4 simple pipe of stack elements into queue and print out .
  // Q1.5 use pairs 's unordered set (k,v) where v is count of duplicaes but k
  // is unique resulting in maintaining of unique nature of Uset ... essentially
  // a multiset which allows for duplicates

  // Q1.6

  // 1. Generic array of integers
  dy_arr<int> int_array;
  int_array.push_back_dy_arr(10);
  int_array.push_back_dy_arr(12);
  int_array.push_back_dy_arr(20);
  int_array.push_back_dy_arr(40);
  int_array.remove(3);
  int_array.print();
  // 2. Unordered Set mapping
  dy_set unordered_set(false);
  unordered_set.insert(40, 400);
  unordered_set.insert(10, 100);
  unordered_set.insert(40, 999); // Will be skipped (duplicate key)
  unordered_set.insert(50, 2000);
  unordered_set.insert(80, 9);
  unordered_set.remove(40);
  std::cout << "Unordered Set: ";
  unordered_set.print(); // Output: [40: 400] [10: 100]

  // 3. Ordered Set mapping
  dy_set ordered_set(true);
  ordered_set.insert(40, 400);
  ordered_set.insert(10, 100);
  ordered_set.insert(25, 250);
  ordered_set.remove(25);
  std::cout << "Ordered Set:   ";
  ordered_set.print(); // Output: [10: 100] [25: 250] [40: 400]

  // Q1.7
  //  Note: GPT hepled me figure this out , most problems can be identified by
  //  looking into the pain points directly or complexity itself .... remember
  //  As for improvements , in the dynamic array above we can allocate more mem
  //  block before itself in order to not thrash the CPU , because we copy mem
  //  everytime during insert , implment this a bot for better understanding how
  //  do we this , we have a certain threshold called capacity which is a
  //  upperbound of size of dy_array which gradually increase when we fill up
  //  the array .
  //  Second improvement for Unordered set is use tempaltes first and send right
  //  we always add otu elemt to the end of data struct which makes it look up
  //  complexity O(N) , we can make this constant using hashing and probing to
  //  help us to did faster .

  return 0;
}
