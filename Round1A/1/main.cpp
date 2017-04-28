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



//void fill(vector<vector<char>> &m, int R, int C, int num) {
//  while (num > 0) {
//    // right
//    for (int i = 0; i < R; i++) {
//      for (int j = 0; j < C-1; j++) {
//
//        if ( m[i][j] != '?') continue;
//
//        // find right
//        if (m[i][j+1] == '?') continue;
//        //
//        char c = m[i][j+1];
//        int q = i, u = i;
//        while (q+1 <= R-1 && m[q+1][j+1] == c)
//          q++;
//        while (u-1 >= 0 && m[u-1][j+1] == c)
//          u--;
//        //
//        bool copy = true;
//        for (int r = u; r <=q; r++) {
//          if (m[r][j] != '?')
//            copy = false;
//        }
//        if (!copy) continue;
//        for (int r = u; r <=q; r++) {
//          m[r][j] =  c;
//          num--;
//        }
//        if (num == 0) break;
//      }
//    }
//
//    // left
//    for (int i = 0; i < R; i++) {
//      for (int j = 1; j < C; j++) {
//
//        if ( m[i][j] != '?') continue;
//
//        if (m[i][j-1] == '?') continue;
//        //
//        char c = m[i][j-1];
//        int q = i, u = i;
//        while (q+1 <= R-1 && m[q+1][j-1] == c )
//          q++;
//        while (u-1 >= 0 && m[u-1][j-1] == c )
//          u--;
//        //
//        bool copy = true;
//        for (int r = u; r <=q; r++) {
//          if (m[r][j] != '?')
//            copy = false;
//        }
//        if (!copy) continue;
//        for (int r = u; r <=q; r++) {
//          m[r][j] =  c;
//          num--;
//        }
//        if (num == 0) break;
//      }
//    }
//
//    // up
//    for (int i = 0; i < R-1; i++) {
//      for (int j = 0; j < C; j++) {
//
//        if ( m[i][j] != '?') continue;
//
//        if (m[i+1][j] == '?') continue;
//        //
//        char c = m[i+1][j];
//        int q = j, u = j;
//        while (q+1 <= C-1 && m[i+1][q+1] == c )
//          q++;
//        while (u-1 >= 0 && m[i+1][u-1] == c)
//          u--;
//        //
//        bool copy = true;
//        for (int r = u; r <=q; r++) {
//          if (m[i][r] != '?')
//            copy = false;
//        }
//        if (!copy) continue;
//        for (int r = u; r <=q; r++) {
//          m[i][r] =  c;
//          num--;
//        }
//        if (num == 0) break;
//      }
//    }
//
//    // down
//    for (int i = 1; i < R; i++) {
//      for (int j = 0; j < C; j++) {
//
//        if ( m[i][j] != '?') continue;
//
//        if (m[i-1][j] == '?') continue;
//        //
//        char c = m[i-1][j];
//        int q = j, u = j;
//        while (q+1 <= C-1 && m[i-1][q+1] == c )
//          q++;
//        while (u-1 >= 0 && m[i-1][u-1] == c )
//          u--;
//        //
//        bool copy = true;
//        for (int r = u; r <=q; r++) {
//          if (m[i][r] != '?')
//            copy = false;
//        }
//        if (!copy) continue;
//        for (int r = u; r <=q; r++) {
//          m[i][r] =  c;
//          num--;
//        }
//        if (num == 0) break;
//      }
//    }
//
//  }
//
//
//
//}


void fill(vector<vector<char>> &m, int R, int C, int num) {
  // fill right-wards first
  for (int i = 0; i < R; ++i) {
    char cc = '\0';
    bool set1st = false;
    char c1st = '\0';
    int empty = 0;
    for (int j = 0; j < C; ++j) {
      char &c = m[i][j];
      // find the 1st
      if (!set1st) {
        if (c == '?') {
          empty++;
        } else {
          c1st = c;
          set1st = true;
        }
      }
      // replace tails
      if (c != '?')
        cc = c;
      else if (cc != '\0')
        c = cc;
    }
    // replace head
    if (c1st != '\0')
      for (int k = 0; k < empty; ++k) {
        m[i][k] = c1st;
      }
  }

  // fill down-wards
  int r1 = 0;
  bool setr = false;
  for (int i = 0; i < R-1; ++i) {
    if (m[i][0] == '?') {
      if (!setr)
        r1++;
      continue;
    } else {
      setr = true;
    }
    //
    if (m[i+1][0] != '?')
      continue;
    //
    for (int j = 0; j < C; ++j) {
      m[i+1][j] = m[i][j];
    }
  }
  // up wards
  for (int i = 0; i < r1; ++i) {
    for (int j = 0; j < C; ++j) {
      m[i][j] = m[r1][j];
    }
  }
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
//  string filename = "test";
  string filename = "A-large";
  ifstream input_file;
  input_file.open(filename + ".in.txt");
  ofstream output_file;
  output_file.open(filename + ".out.txt");

  int t;
  input_file >> t;  // read t. cin knows that t is an int, so it reads it as such.
  int R, C;
  string str;
  char c;
  cout << "total cases: " << t << endl;

  for (int i = 1; i <= t; ++i) {

    input_file >> R >> C;  // read n and then m.

    vector<vector<char>> matrix;
    int num = 0;
    for (int k = 0; k < R; k++) {
      vector<char> row;
      for (int kk = 0; kk < C; kk++) {
        input_file >> c;
        row.push_back(c);
        if (c == '?')
          num++;
      }
      matrix.push_back(row);
    }

    fill(matrix, R, C, num);

    output_file << "Case #" << i << ": " << endl;
    for (int k = 0; k < R; k++) {
      for (int kk = 0; kk < C; kk++) {
        output_file << matrix[k][kk] ;
      }
      output_file << endl;
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
