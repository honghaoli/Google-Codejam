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
int N = 0, K = 0;
vector<long> R;
vector<long> H;
vector<long> RH;
vector<long> RHs;


/////////// functions /////////////////////////

long idofRH(long last) {
  long m = 0;
  for (long i = 0; i < RHs.size(); i++) {
    if (RHs[i] == last && R[i] > m) {
      m = R[i];
    }
  }
  return m;
}

long double myfunc() {
  sort(RH.begin(), RH.end());
  vector<long> Rmax;
  long double sum2 = 0;
  for (int i = 0; i < K; ++i) {
    long last = RH[RH.size()-1-i];
    sum2 += static_cast<double>(last);
    long m = idofRH(last);
    Rmax.push_back(m);
    printf("Rmax %ld\n", m);
  }
  //
  sort(Rmax.begin(), Rmax.end());
  long m = Rmax.back();
  //
  long double sum1 = static_cast<double>(m) * static_cast<double>(m);
  printf("%Lf, %Lf\n", sum1, sum2);
  return M_PI * sum1 + M_PI * 2 * sum2;
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
  string filename = "A-small-attempt8";
  ifstream input_file;
  input_file.open(filename + ".in.txt");
  ofstream output_file;
  output_file.open(filename + ".out.txt");
  FILE *out;
  out = fopen("fprint-out.txt", "w");

  int t;
  input_file >> t;  // read t. cin knows that t is an int, so it reads it as such.
//  int N, K;
//  string str;
//  char c;
  cout << "total cases: " << t << endl;

  for (int i = 1; i <= t; ++i) {

    R.clear();
    H.clear();
    RH.clear();
    RHs.clear();

    input_file >> N >> K;  // read n and then m.

    for (int j = 0; j < N; ++j) {
      long r, h;
      input_file >> r >> h;  // read n and then m.
      R.push_back(r);
      H.push_back(h);
      RH.push_back(r*h);
      RHs.push_back(r*h);
    }
//    output_file << "Case #" << i << ": " << N << endl;
//    cout << "Case #" << i << ": " << N << endl;
//    printVector(R);
//    printVector(H);
//    printVector(RH);
//    printVector(RHs);
    long double area = myfunc();
    printf("Case #%d: %.9Lf\n", i, area);
    fprintf(out, "Case #%d: %.9Lf\n", i, area);

  }

  input_file.close();
  output_file.close();
}

int main() {
  cout << "=====================================" << endl;
  cout << "maximum long long:\t" << numeric_limits<long long>::max() << endl;
  cout << "maximum long double:\t" << numeric_limits<long double>::max() << endl;
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
