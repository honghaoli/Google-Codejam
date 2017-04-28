#include <iostream>
#include <fstream>

using namespace std;  // since cin and cout are both in namespace std, this saves some text

void flip(char *c) {
  if (*c == '-') {
    *c = '+';
  } else {
    *c = '-';
  }
}

int min_filp_time(string str, int K) {
  int len = str.length();
  int times = 0;

  int i;
  for (i = 0; i <= len - K; i++) {
    if (str[i] == '-') {
      for (int j = 0; j < K; j++) {
        flip(&str[i + j]);
      }
      times++;
    }
  }
  cout << "after flip string: " << str << ", index at: " << i << endl;
  while (i < len) {
    if (str[i] == '-') {
      return -1;  // impossible
    }
    i++;
  }

  return times;
}

int main() {
  ifstream input_file;
  input_file.open("A-large.in.txt");
  ofstream output_file;
  output_file.open("A-large.out.txt");
  int t;
  int K;
  string input_string;
  input_file >> t;  // read t. cin knows that t is an int, so it reads it as such.
  cout << "total cases: " << t << endl;
  for (int i = 1; i <= t; ++i) {
    input_file >> input_string >> K;  // read n and then m.
    cout << "input string: " << input_string << ", K = " << K << endl;
    int n = min_filp_time(input_string, K);
    cout << "Case #" << i << ": " << n << endl;
    if (n >= 0) {
      output_file << "Case #" << i << ": " << n << endl;
    } else {
      output_file << "Case #" << i << ": IMPOSSIBLE" << endl;
    }
    // cout knows that n + m and n * m are ints, and prints them accordingly.
    // It also knows "Case #", ": ", and " " are strings and that endl ends the line.
  }
  input_file.close();
  output_file.close();
}
