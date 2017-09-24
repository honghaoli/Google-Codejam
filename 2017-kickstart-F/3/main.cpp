#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <limits>
#include <iomanip>

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

void find_min(int N, vector<vector<int>> &path) {
  // Floyd–Warshall algorithm
  for (int k = 0; k < N; k++) {
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < i; j++) {
        if (k == i || k == j) continue;
        if (path[i][k] < 0 || path[j][k] < 0) continue;
        if (path[i][j] < 0)
          path[i][j] = path[i][k] + path[j][k];
        else
          path[i][j] = min(path[i][j], path[i][k] + path[j][k]);

        path[j][i] = path[i][j];
      }
    }
  }

//  print2DVector(path);
}

double myfunc(int N, int P, vector<vector<int>> &path) {
  find_min(N, path);

  double ave1 = 0;
  for (int i = 1; i < N; i++) {
    ave1 += path[0][i];
  }
  ave1 /= static_cast<double>(N - 1);

  if (P == 1) return ave1;

  double ave = 0;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < i; ++j) {
      ave += path[i][j];
    }
  }

  ave *= 2.0;
  ave /= static_cast<double>(N * (N - 1));

  double ave2 = (ave * N - ave1) / static_cast<double>(N - 1);
  if (P == 2) return ave1 + ave2;

//  return (P - 2) * ave + ave1 + ave2;

//  cout << "ave1: " << ave1 << ", ave2: " << ave2 << endl;

  // odd and even P is different, it's oscillating!
  double ave_i = 0;
  double count = 0;

//  int total = 0;
//  double result = 0;
  // skip first 2 P
  int total = (N - 1);
  double result = ave1 + ave2;

  int i;
  for (i = 3; i <= P; i++) {
//    if (i == 1)
//      total = 1;
//    else
//      total *= (N - 1);

    // skip first 2 P
    total *= (N - 1);

    if (i % 2 == 1) {
      count = static_cast<double>(total - 1) / static_cast<double>(N);
      ave_i = (ave1 * (count + 1) + count * ave2 * (N - 1) ) / total;
    } else {
      count = static_cast<double>(total + 1) / static_cast<double>(N);
      ave_i = (ave1 * (count - 1) + count * ave2 * (N - 1) ) / total;
    }
    result += ave_i;

//    cout << count << ", " << total << endl;
//    cout << "ave_i: " << ave_i << endl;
    if (abs(ave_i - ave) / ave < 1E-6)
      break;
  }

  cout << "breaking i: " << i << endl;

  while (++i <= P) {
    result += ave;
  }

  return result;
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

vector<vector<int>> initial_path(int N) {
  vector<vector<int>> result(N, vector<int>(N, -1));
  for (int i = 0; i < N; i++) {
    result[i][i] = 0;
  }
  return result;
}

void solve() {
//  string filename = "test";
  string filename = "C-large";
//  string filename = "D-large";
  ifstream input_file;
  input_file.open(filename + ".in.txt");
  ofstream output_file;
  output_file.open(filename + ".out.txt");

  int t;
  input_file >> t;  // read t. cin knows that t is an int, so it reads it as such.
  int N, M, P;
  int ui, vi, di;
  string str;
  char c;
  cout << "total cases: " << t << endl;

  for (int i = 1; i <= t; ++i) {

    input_file >> N >> M >> P;  // read n and then m.
    cout << "N = " << N << ",  P = " << P << endl;
    vector<vector<int>> path = initial_path(N);
    for (int j = 0; j < M; ++j) {
      input_file >> ui >> vi >> di;
      path[ui-1][vi-1] = di;
      path[vi-1][ui-1] = di;
    }

    double ave = myfunc(N, P, path);

    output_file << "Case #" << i << ": "<< std::fixed << std::setprecision(6) << ave << endl;
    cout << "Case #" << i << ": " << std::fixed << std::setprecision(6) << ave << endl;

  }

  input_file.close();
  output_file.close();
}

int main() {
//  cout << "=====================================" << endl;
//  cout << "maximum long long:\t" << numeric_limits<long long>::max() << endl;
//  cout << "maximum long:\t" << numeric_limits<long>::max() << endl;
//  cout << "maximum int:\t" << numeric_limits<int>::max() << endl;
//  cout << "maximum short:\t" << numeric_limits<short>::max() << endl;
//  cout << "infinity value of long:\t" << numeric_limits<long>::infinity() << endl;
//  cout << "infinity value of double:\t" << numeric_limits<double>::infinity() << endl;
//  cout << "=====================================\n" << endl;

//  unit_test();
//  test();

  solve();

}
