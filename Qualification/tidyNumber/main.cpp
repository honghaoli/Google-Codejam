#include <iostream>
#include <fstream>
#include <vector>

using namespace std;  // since cin and cout are both in namespace std, this saves some text



// convert ASCII to integer
int digit(char c) {
  return c - 48;
}

string max_tidy_number(string str) {
  vector<int> digits;
  vector<int> result;
  for (auto &c : str) {
    digits.push_back(digit(c));
    result.push_back(9);
  }

  bool reverse_check = false;

  int i = 0;
  while (i < digits.size() - 1) {
    result[i] = digits[i];
    if (digits[i] <= digits[i+1]) {
      i++;
    } else {
      reverse_check = true;
      break;
    }
  }

  if (reverse_check) {
    result[i]--;
    result[i + 1] = 9;
    i--;
    while (i >= 0) {
      if (result[i] > result[i+1]) {
        result[i]--;
        result[i + 1] = 9;
      }
      i--;
    }
  } else { // finish the last digits if reverse check is not need
    result[result.size() - 1] = digits[digits.size() - 1];
  }

  string res;
  bool remove_zero = true;
  for (auto &d : result) {
    if (remove_zero && d == 0)
      continue;
    res.push_back(d + 48);
    remove_zero = false;
  }
  return res;
}

// test
void test() {
  string input = "11111111111111111111111111111111110";
  string output = max_tidy_number(input);
  cout << "input string: " << input << endl;
  cout << "output string: " << output << endl;
}

void solve() {
  ifstream input_file;
  input_file.open("B-large.in.txt");
  ofstream output_file;
  output_file.open("B-large.out.txt");
  int t;
  string input_string;
  input_file >> t;  // read t. cin knows that t is an int, so it reads it as such.
  cout << "total cases: " << t << endl;
  for (int i = 1; i <= t; ++i) {
    input_file >> input_string;  // read n and then m.
    cout << "input string: " << input_string << endl;
    string result = max_tidy_number(input_string);
    cout << "Case #" << i << ": " << result << endl;
    output_file << "Case #" << i << ": " << result << endl;
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
