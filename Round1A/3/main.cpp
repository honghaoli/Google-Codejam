#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <limits>

using namespace std;  // since cin and cout are both in namespace std, this saves some text

////////////////////////////////////////////////////
////////////////////////////////////////////////////
////////////////////////////////////////////////////
/// Common Templates and Functions
////////////////////////////////////////////////////
////////////////////////////////////////////////////
////////////////////////////////////////////////////
template<typename T>
void printVector(vector<T> &vec) {
  cout << "vector: ";
  for (auto &v : vec) {
    cout << v << " ";
  }
  cout << endl;
}

template<typename T>
void printArray(T* a, long n) {
  cout << "array: ";
  for (int i = 0; i < n; i++) {
    cout << a[i] << " ";
  }
  cout << endl;
}


// convert ASCII to integer
int digitToChar(char c) {
  return c - 48;
}
char charToDigit(int i) {
  return i + 48;
}
////////////////////////////////////////////////////
////////////////////////////////////////////////////
////////////////////////////////////////////////////

int findn(int hk, int ad, int b) {
  int n = 0;
  while (true) {
    double l = ceil(static_cast<double>(hk) / static_cast<double>(ad + (n-1) * b));
    double r = ceil(static_cast<double>(hk) / static_cast<double>(ad + (n+1) * b));
    double m = ceil(static_cast<double>(hk) / static_cast<double>(ad + (n) * b));
    if (l - m >= 1 && m - r <= 1) {
      break;
    } else {
      n++;
    }
  }
  return n;
}


int cal(int hd, int ad, int hk, int ak, int b, int d) {
  if (ad >= hk) return 1;
  if (2*ak - 3*d >= hd) return -1;

  int attack;
  if (b == 0) {
    attack = hk / ad;
    if (hk % ad != 0)
      attack++;
  } else {
    attack = findn(hk, ad, b);
  }

  int free;
  if (d == 0) {
    free = ceil((double)hd / (double)ak) - 1;
  } else {
    //
  }

  int loop = attack / free;
  int num;
  if (loop >= 1)
    num = attack / free * (free + 1) - 1;
  else
    num = attack;

  return num;
}


// part test
void unit_test() {
}

// test
void test() {
  vector<int> vec = {1,2,3,4,5};
  printVector(vec);
  vec.resize(10, 0);
  printVector(vec);

  int arr[4] = {1, 2, 4, 3};
  printArray(arr, 4);

}


void solve() {
  string filename = "test";
//  string filename = "D-large";
  ifstream input_file;
  input_file.open(filename + ".in.txt");
  ofstream output_file;
  output_file.open(filename + ".out.txt");

  int t;
  input_file >> t;  // read t. cin knows that t is an int, so it reads it as such.
  int hd, ad, hk, ak, b, d;
  string str;
  char c;
  cout << "total cases: " << t << endl;

  for (int i = 1; i <= t; ++i) {

    input_file >> hd >> ad >> hk >> ak >> b >> d;  // read n and then m.

    int m = cal(hd, ad, hk, ak, b, d);

    if ( m < 0) {
      output_file << "Case #" << i << ": IMPOSSIBLE" << endl;
    } else {
      output_file << "Case #" << i << ": " << m << endl;
    }

  }

  input_file.close();
  output_file.close();
}

int main() {
  cout << "=====================================" << endl;
  cout << "maximum long long:\t" << numeric_limits<long long>::max() << endl;
  cout << "maximum long:\t" << numeric_limits<long>::max() << endl;
  cout << "maximum int:\t" << numeric_limits<int>::max() << endl;
  cout << "maximum short:\t" << numeric_limits<short>::max() << endl;
  cout << "=====================================\n" << endl;

//  unit_test();
//  test();
  solve();
}
