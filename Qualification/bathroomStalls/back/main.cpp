#include <iostream>
#include <fstream>
#include <vector>
#include <queue>


using namespace std;  // since cin and cout are both in namespace std, this saves some text

// unsigned big integer
// digits stored in reversed sequence
class BigInt {
 public:

  BigInt() = default;

  BigInt(string str) {
    for (int i = str.length()-1; i >=0; i--) {
      char c = str[i];
      if (c < 48 || c > 57) {
        throw runtime_error("Input string can not be converted into integer!!!\n");
      }
      data.push_back(c - 48);
    }
  }

  BigInt(vector<int> vec) {
    // TODO: generally should check if each int is only one digit
    data = vec;
  }

  BigInt(BigInt const &bint) {
    data = bint.data;
  }

  bool isLessThan(BigInt &other) {
    if (data.size() < other.data.size()) {
      return true;  // smaller
    } else if (data.size() > other.data.size()) {
      return false; // larger
    } else {
      for (int i = data.size()-1; i >= 0; i--) {
        int d1 = data[i];
        int d2 = other.data[i];
        if (d1 < d2 ) {
          return true;  // smaller
        } else if (d1 > d2 ) {
          return false;   // larger
        }
      }
      return false;   // equal ????
    }
  }

  bool isLargerThan(BigInt &other) {
    if (data.size() < other.data.size()) {
      return false;  // larger
    } else if (data.size() > other.data.size()) {
      return true; // smaller
    } else {
      for (int i = data.size()-1; i >= 0; i--) {
        int d1 = data[i];
        int d2 = other.data[i];
        if (d1 < d2 ) {
          return false;  // larger
        } else if (d1 > d2 ) {
          return true;   // smaller
        }
      }
      return false;   // equal ????
    }
  }

  void decreaseByOne() {
    int i = 0;
    bool borrow = false;
    while (i < data.size()) {
      data[i]--;
      if (data[i] < 0) {
        data[i] = 9;
        borrow = true;
      } else {
        borrow = false;
      }
      if (borrow) {
        i++;
        continue;
      } else {
        break;
      }
    }
    removeTrailingZero();
  }

  void increaseByOne() {
    int i = 0;
    bool carry = false;
    while (i < data.size()) {
      data[i]++;
      if (data[i] > 9) {
        data[i] = 0;
        carry = true;
      } else {
        carry = false;
      }
      if (carry) {
        i++;
        continue;
      } else {
        break;
      }
    }
    // increase size
    if (carry)
      data.push_back(1);
  }

  bool isOdd() {
    if (data.size() == 0)
      throw runtime_error("BigInt has no digit, so cannot determine if it's odd number!\n");
    return data[0] % 2 != 0;
  }

  BigInt divideByTwo() {
    BigInt result = BigInt(data);
    int reminder = 0;
    for (int i = data.size()-1; i >= 0; i--) {
      int n = reminder * 10 + result.data[i];
      result.data[i] = n / 2;
      reminder = n % 2;
    }
    result.removeTrailingZero();
    return result;
  }

  string toString() {
    string s;
    for (int i = data.size()-1; i >= 0; i--) {
      s.push_back(data[i] + 48);
    }
    return s;
  }

 private:
  vector<int> data; // reversed order digits

  void removeTrailingZero() {
    // only keep the last zero
    for (int i = data.size()-1; i > 0; i--) {
      if (data[i] == 0) {
        data.pop_back();
      } else {
        break;
      }
    }
  }

};


// convert ASCII to integer
int digit(char c) {
  return c - 48;
}

void max_and_min(string &N, string &K, string *maxs, string *mins) {
  BigInt stalls = BigInt(N);
  BigInt users = BigInt(K);

  // Using lambda to compare elements.
  auto cmp = [](BigInt left, BigInt right) { return left.isLessThan(right);};
  // use priority queue to store consecutive empty space region, the big integer is the number of un-occupied stalls minus one.
  priority_queue<BigInt, vector<BigInt>, decltype(cmp)> empty_regions(cmp);
  // initial setup
  stalls.decreaseByOne();
  empty_regions.push(stalls);

  // start loop
  BigInt zero = BigInt("0");
  BigInt one = BigInt("1");
  BigInt new_min, new_max, max_current;
  while (!empty_regions.empty()) {
    max_current = empty_regions.top();
    empty_regions.pop();

    if (max_current.isOdd()) {
      new_min = max_current.divideByTwo();
      new_max = BigInt(new_min);
      new_max.increaseByOne();
    } else {
      new_min = max_current.divideByTwo();
      new_max = BigInt(new_min);
    }

    users.decreaseByOne();
    // all users finish
    if (!users.isLargerThan(zero))
      break;

    // add new regions only if N - 1 > 0, non-zero regions
    if (new_min.isLargerThan(one)) {
      new_min.decreaseByOne();
      empty_regions.push(new_min);
    }
    if (new_max.isLargerThan(one)) {
      new_max.decreaseByOne();
      empty_regions.push(new_max);
    }
  }

  // no space with min >= 1 left, all (0, 0) from now on
  if (users.isLargerThan(zero)) {
    *mins = "0";
    *maxs = "0";
  } else {
    *mins = new_min.toString();
    *maxs = new_max.toString();
  }

}

// test
void test() {
  string stalls = "4";
  string users = "1";
  string maxs, mins;
  max_and_min(stalls, users, &maxs, &mins);
  cout << "input stalls number:\t" << stalls << endl;
  cout << " input users number:\t" << users << endl;
  cout << "         output max:\t" << maxs << endl;
  cout << "         output min:\t" << mins << endl;
}

void solve() {
  string filename = "C-small-2-attempt0";
  ifstream input_file;
  input_file.open(filename + ".in.txt");
  ofstream output_file;
  output_file.open(filename + ".out.txt");
  int t;
  string input_N, input_K;
  input_file >> t;  // read t. cin knows that t is an int, so it reads it as such.
  string out_min, out_max;
  cout << "total cases: " << t << endl;
  for (int i = 1; i <= t; ++i) {
    input_file >> input_N >> input_K;  // read n and then m.
    cout << "input string: " << input_N << " " << input_K << endl;
    max_and_min(input_N, input_K, &out_max, &out_min);
    cout << "Case #" << i << ": " << out_max << " " << out_min << endl;
    output_file << "Case #" << i << ": " << out_max << " " << out_min << endl;
    // cout knows that n + m and n * m are ints, and prints them accordingly.
    // It also knows "Case #", ": ", and " " are strings and that endl ends the line.
  }
  input_file.close();
  output_file.close();
}

int main() {
//  test();
  solve();
}
