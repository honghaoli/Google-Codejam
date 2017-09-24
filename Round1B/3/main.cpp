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


int N, Q, V, U;
vector<vector<long>> D;
vector<long> d;
vector<long> E;
vector<long> S;
double tt[100][100];


/////////// functions /////////////////////////

double mint(int i, int k) {
  if (tt[i][k] > 0 )
    return tt[i][k];
//  if (k == i+1) {
//    if (E[i] >= d[i])
//      return static_cast<double>(d[i]) / static_cast<double>(S[i]);
//    else
//      return 9E10;
//  }
  //
  double m = numeric_limits<double>::infinity();
  long dist = 0;
  for (int j = i; j < k; ++j) {
    dist += d[j];
  }
  if (E[i] >= dist)
    m = static_cast<double>(dist) / static_cast<double>(S[i]);
  //
//  printf("dist: %ld, m: %f\n", dist, m);
  for (int q = i+1; q < k; ++q) {
    double t = mint(i, q) + mint(q, k);
    if (t < m)
      m = t;
  }
  //
  tt[i][k] = m;
//  printf("tt[%d][%d]: %f\n", i, k, m);
  return m;
}

double myfunc() {
  for (int i = 0; i < 100; ++i) {
    for (int j = 0; j < 100; ++j) {
      tt[i][j] = -1;
    }
  }

  return mint(0, N-1);
}


// As analysis suggests, we use Floyd-Warshall algorithm this time
void FW() {
  // initial
  for (int i = 0; i < 100; ++i) {
    for (int j = 0; j < 100; ++j) {
      if (i == j)
        tt[i][j] = 0;
      else
        tt[i][j] = numeric_limits<double>::infinity();
    }
  }
//  print2DVector(D);
//  for (int i = 0; i < N; ++i) {
//    for (int j = 0; j < N; ++j) {
//      if (i == j)
//        D[i][j] = 0;
//      else if (D[i][j] < 0)
//        D[i][j] = numeric_limits<long>::max();
//    }
//  }
//  print2DVector(D);
  // Floyd-Warshall for all pair distances
  for (int k = 0; k < N; ++k) {
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) {
        // must skip when no path there, it's -1. we cannot use long::infinity() which is zero, nor long::max which would cause overflow problem.
        if (D[i][k] < 0 || D[k][j] < 0)
          continue;
        if (D[i][j] > D[i][k] + D[k][j] || D[i][j] < 0)
          D[i][j] = D[i][k] + D[k][j];
      }
    }
  }
//  print2DVector(D);
  // calculate time from distances
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      if (D[i][j] > 0 && D[i][j] <= E[i])
        tt[i][j] = static_cast<double>(D[i][j]) / static_cast<double>(S[i]);
    }
  }
  // Floyd-Warshall for all pair time
  for (int k = 0; k < N; ++k) {
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) {
        if (tt[i][j] > tt[i][k] + tt[k][j])
          tt[i][j] = tt[i][k] + tt[k][j];
      }
    }
  }
//  print2DArray(tt, N, N);
}

double getT(int i, int j) {
  return tt[i][j];
}

//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
//// part test
//void unit_test() {
//}
//
//// test
//void test() {
//  vector<int> vec = {1,2,3,4,5};
//  printVector(vec);
//  vec.resize(10, 0);
//  printVector(vec);
//
//  int arr[4] = {1, 2, 4, 3};
//  printArray(arr, 4);
//
//}


void solve() {
//  string filename = "test";
  string filename = "C-large-practice";
//  string filename = "D-large";
  ifstream input_file;
  input_file.open(filename + ".in.txt");
  ofstream output_file;
  output_file.open(filename + ".out.txt");
  FILE *out;
  out = fopen("out.txt", "w");

  int t;
  input_file >> t;  // read t. cin knows that t is an int, so it reads it as such.
  long e, s, Djk;
  string str;
  char c;
  cout << "total cases: " << t << endl;

  for (int i = 1; i <= t; ++i) {

    E.clear();
    S.clear();
    D.clear();
    d.clear();
    input_file >> N >> Q;  // read n and then m.
//    cout << "input string: " << str << ", N = " << N << endl;
    for (int j = 0; j < N; ++j) {
      input_file >> e >> s;  // read n and then m.
      E.push_back(e);
      S.push_back(s);
    }
    for (int j = 0; j < N; ++j) {
      vector<long> tmp;
      for (int k = 0; k < N; ++k) {
        input_file >> Djk;
        tmp.push_back(Djk);
        if (k == j +1)
          d.push_back(Djk);
      }
      D.push_back(tmp);
    }
    //
    FW();
    // calculate start-end pairs

    output_file << "Case #" << i << ": ";
    fprintf(out, "Case #%d:", i);
    for (int j = 0; j < Q; ++j) {
      input_file >> V >> U;  // read n and then m.
//    printVector(E);
//    printVector(S);
//    printVector(d);
//      double time = myfunc();
      double time = getT(V-1, U-1);

      output_file << time;
      fprintf(out, " %f", time);
      printf("Case #%d: (%d, %d) %f\n", i, V, U, time);
    }
    output_file << endl;
    fprintf(out, "\n");

  }

  input_file.close();
  output_file.close();
  fclose(out);
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
