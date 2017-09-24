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
void print2DVector(vector<vector<T> > &vec) {
  cout << "vector: \n";
  for (auto &v1 : vec) {
    for (auto &v : v1) {
      cout << v << " ";
    }
    cout << endl;
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

template<typename T>
void print2DArray(T* a, long r, long c) {
  cout << "array:\n";
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      cout << a[i][j] << " ";
    }
    cout << endl;
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
//////////      Solution       ///////////////////
////////////////////////////////////////////////////
////////////////////////////////////////////////////

/////////// Public variables //////////////////
//int N = 0, M = 0;
//string str = "";
//char c = '\0';


/////////// functions /////////////////////////

int find_min(int n, unordered_map<int, int> &hash) {
  if (n == 0) return 0;
  if (n == 1) return 1;

  if (hash.count(n) > 0)
    return hash[n];

  int big = static_cast<int>( floor( sqrt( static_cast<double>(n) ) ) );
  int m = n;
  for (int i = big; i >= 1; --i) {
    m = min(m, 1 + find_min(n - i * i, hash));
    if (m == 1) break;
  }

  hash[n] = m;
  return m;
}

int myfunc(int N) {
  unordered_map<int, int> hash;
  return find_min(N, hash);
}


////////////////////////////////////////////////////
////////////////////////////////////////////////////
////////////////////////////////////////////////////
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
//  string filename = "test";
  string filename = "D-large";
//  string filename = "D-large";
  ifstream input_file;
  input_file.open(filename + ".in.txt");
  ofstream output_file;
  output_file.open(filename + ".out.txt");

  int t;
  input_file >> t;  // read t. cin knows that t is an int, so it reads it as such.
  int N, M;
  string str;
  char c;
  cout << "total cases: " << t << endl;

  for (int i = 1; i <= t; ++i) {

    input_file >> N;  // read n and then m.
    cout << ", N = " << N << endl;

    int res = myfunc(N);

    output_file << "Case #" << i << ": " << res << endl;
    cout << "Case #" << i << ": " << res << endl;

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
  cout << "infinity value of long:\t" << numeric_limits<long>::infinity() << endl;
  cout << "infinity value of double:\t" << numeric_limits<double>::infinity() << endl;
  cout << "=====================================\n" << endl;

//  unit_test();
//  test();
  solve();
}
