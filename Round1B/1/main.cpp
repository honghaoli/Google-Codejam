#include <stdio.h>
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
//////////      Solution       ///////////////////
////////////////////////////////////////////////////
////////////////////////////////////////////////////

/////////// Public variables //////////////////
//long N = 0, M = 0;
//string str = "";
//char c = '';


/////////// functions /////////////////////////

void func() {

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
  ifstream input_file;
  input_file.open(filename + ".in");
//  ofstream output_file;
//  output_file.open(filename + ".out.txt");
  FILE *file;
  string outname = filename + ".out.txt";
  file = fopen("test.out.txt", "w");


  int t;
  input_file >> t;  // read t. cin knows that t is an int, so it reads it as such.
  long D, N, K, S;
  long double min_time;
  string str;
  char c;
  cout << "total cases: " << t << endl;

  for (int i = 1; i <= t; ++i) {

    input_file >> D >> N;  // read n and then m.
//    cout << "input string: " << str << ", N = " << N << endl;


    min_time = 0;
    for (long h = 0; h < N; ++h) {
      input_file >> K >> S;  // read n and then m.
      long double time = static_cast<long double>(D - K) / static_cast<long double>(S);
      if (time > min_time)
        min_time = time;
    }

    long double speed = static_cast<long double>(D) / min_time;


//    cout.precision(10);
//    ofstream.precision(10);
//    output_file << "Case #" << i << ": "   << speed << endl;
//    cout << "Case #" << i << ": " << speed << endl;
    fprintf(file, "Case #%d: %Lf\n", i, speed);

  }

  input_file.close();

//  output_file.close();
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
