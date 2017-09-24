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
int AC, AJ, C, D, J, K;
int tt[1440] = {};


/////////// functions /////////////////////////
int sumvec(vector<int>& vec) {
  int s = 0;
  for (auto &i : vec)
    s += i;
  return s;
}

int myfunc() {
  int la = -2;
  int last = -2;
  int first = -2;
  vector<int> tt1;
  vector<int> tt2;
  vector<int> share;
  int t1 = 0, t2 = 0;
  int must = 0;
  int extra = 0;
  int tmp = 0;
  int firsttmp = 0;
 //
  for (int i = 0; i < 1440; ++i) {
    if (tt[i] == 1) {
      t1++;
      if (la == -1)
        must++;
      if (last == 0) {
        if (la == 1)
          tt1.push_back(tmp);
        else if (la == -1)
          share.push_back(tmp);
      }
      if (la == -2) {
        first = 1;
        firsttmp = tmp;
      }
      last = 1;
      la = 1;
      tmp = 0;
    }
    else if (tt[i] == -1) {
      t2++;
      if (la == 1)
        must++;
      if (last == 0) {
        if (la == -1)
          tt2.push_back(tmp);
        else if (la == 1)
          share.push_back(tmp);
      }
      if (la == -2) {
        first = -1;
        firsttmp = tmp;
      }
      last = -1;
      la = -1;
      tmp = 0;
    }
    else if (tt[i] == 0) {
      last = 0;
      tmp++;
    }
  }
  //
  if (la != first) {
    share.push_back(tmp + firsttmp);
    must++;
  }
  else if (la == 1)
    tt1.push_back(tmp + firsttmp);
  else if (la == -1)
    tt2.push_back(tmp + firsttmp);
  //
  sort(tt1.begin(), tt1.end());
  sort(tt2.begin(), tt2.end());
  printVector(tt1);
  printVector(tt2);
  //
  int sum1 = t1 + sumvec(tt1);
  int sum2 = t2 + sumvec(tt2);
  if (sum1 <= 720 && sum2 <= 720)
    extra = 0;
  else if (sum1 > 720) {
    int k = tt1.size() - 1;
    while (sum1 > 720) {
      sum1 -=  tt1.at(k);
      k--;
      extra++;
      extra++;
    }
  }
  else if (sum2 > 720) {
    int k = tt2.size() - 1;
    while (sum2 > 720) {
      sum2 -=  tt2.at(k);
      k--;
      extra++;
      extra++;
    }
  }
  return must + extra;

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
  string filename = "B-large";
  ifstream input_file;
  input_file.open(filename + ".in.txt");
  ofstream output_file;
  output_file.open(filename + ".out.txt");

  int t;
  input_file >> t;  // read t. cin knows that t is an int, so it reads it as such.
  cout << "total cases: " << t << endl;

  for (int i = 1; i <= t; ++i) {

    for (int i = 0; i < 1440; ++i) {
      tt[i] = 0;
    }

    input_file >> AC >> AJ;  // read n and then m.
    for (int j = 0; j < AC; ++j) {
      input_file >> C >> D;  // read n and then m.
      for (int k = C; k < D; ++k) {
        tt[k] = 1;
      }
    }
    for (int j = 0; j < AJ; ++j) {
      input_file >> J >> K;  // read n and then m.
      for (int k = J; k < K; ++k) {
        tt[k] = -1;
      }
    }

//    printArray(tt, 1441);
    int num = myfunc();
    output_file << "Case #" << i << ": " << num << endl;
    cout << "Case #" << i << ": " << num << endl;

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
