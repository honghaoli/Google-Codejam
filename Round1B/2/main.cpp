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


/////////// functions /////////////////////////

char last = '\0';

void addR(string &str, int &R) {
  str += 'R';
  last = 'R';
  R--;
}
void addO(string &str, int &O) {
  str += 'O';
  last = 'O';
  O--;
}
void addY(string &str, int &Y) {
  str += 'Y';
  last = 'Y';
  Y--;
}
void addG(string &str, int &G) {
  str += 'G';
  last = 'G';
  G--;
}
void addB(string &str, int &B) {
  str += 'B';
  last = 'B';
  B--;
}
void addV(string &str, int &V) {
  str += 'V';
  last = 'V';
  V--;
}

bool addBest(string &str, int &R, int &O, int &Y, int &G, int &B, int &V) {
  printf("%d %d %d %d %d %d\n", R,O,Y,G,B,V);
  printf("string: %s, last char: %c\n", str.c_str(), last);
  if (O > B && last != 'B')
    return false;
  if (G > R && last != 'R')
    return false;
  if (V > Y && last != 'Y')
    return false;
  //
  if (last == 'R') {
    if (G > 0) {
      addG(str, G);
    } else {
      if (B - O > Y - V)
        addB(str, B);
      else if (Y - V > 0)
        addY(str, Y);
      else
        return false;
    }
  }
  else
  if (last == 'Y') {
    if (V > 0) {
      addV(str, V);
    } else {
      if (B - O > R - V)
        addB(str, B);
      else if (R - V > 0)
        addR(str, R);
      else
        return false;
    }
  }
  else
  if (last == 'B') {
    if (O > 0) {
      addO(str, O);
    } else {
      if (R - O > Y - V)
        addR(str, R);
      else if (Y - V > 0)
        addY(str, Y);
      else
        return false;
    }
  }
  else
  if (last == 'O') {
    if (B > 0) {
      addB(str, B);
    } else {
        return false;
    }
  }
  else
  if (last == 'G') {
    if (R > 0) {
      addR(str, R);
    } else {
        return false;
    }
  }
  else
  if (last == 'V') {
    if (Y > 0) {
      addY(str, Y);
    } else {
        return false;
    }
  }

  printf("string: %s, last char: %c\n", str.c_str(), last);
  return true;
}

string myfunc(int &N, int &R, int &O, int &Y, int &G, int &B, int &V) {
  int half = N / 2;
  if (R > half)
    return "IMPOSSIBLE";
  if (O > half || O > B)
    return "IMPOSSIBLE";
  if (Y > half)
    return "IMPOSSIBLE";
  if (G > half || G > R)
    return "IMPOSSIBLE";
  if (B > half)
    return "IMPOSSIBLE";
  if (V > half || V > Y)
    return "IMPOSSIBLE";
  //
  string r = "";
  // 1st char
  if (R > 0)
    addR(r, R);
  else if (O > 0)
    addO(r, O);
  else if (Y > 0)
    addY(r, Y);
  else if (G > 0)
    addG(r, G);
  else if (B > 0)
    addB(r, B);
  else if (V > 0)
    addV(r, V);
  else
    return "IMPOSSIBLE";
  //
  for (int i = 1; i < N; ++i) {
    if (addBest(r,R,O,Y,G,B,V))
      continue;
    else
      return "IMPOSSIBLE";
  }
  //
  if (r[N-1] == r[0])
    return "IMPOSSIBLE";
  else
    return r;
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
//  string filename = "B-small-attempt0";
  string filename = "B-large";
  ifstream input_file;
  input_file.open(filename + ".in");
  ofstream output_file;
  output_file.open(filename + ".out.txt");

  int t;
  input_file >> t;  // read t. cin knows that t is an int, so it reads it as such.
  int N, R, O, Y, G, B, V;
  string str;
  char c;
  cout << "total cases: " << t << endl;

  for (int i = 1; i <= t; ++i) {

    input_file >>  N >> R >> O >> Y >> G >> B >> V;  // read n and then m.
    cout <<  N << R << O << Y << G << B << V << endl;  // read n and then m.

    string result = myfunc(N, R, O, Y, G, B, V);
    output_file << "Case #" << i << ": " << result << endl;
    cout << "Case #" << i << ": " << result << endl;

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
