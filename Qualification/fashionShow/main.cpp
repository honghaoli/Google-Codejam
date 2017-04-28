#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;  // since cin and cout are both in namespace std, this saves some text

class Matrix {

 public:

  Matrix() = default;

  Matrix(int n) : n(n) {
    allocate();
  }

  ~Matrix() {
    deallocate();
  }

  unordered_map<int, char> result;
  int score = 0;

  void placeStyleAt(char c, int row, int col) {
    // input index start from 1, convert to 0.
    row--;
    col--;
    if (c == 'x') {
      a[row][col][0] = true;
      row_can_add_x[row] = false;
      col_can_add_x[col] = false;
      score++;
    } else if (c == '+') {
      a[row][col][1] = true;
//      disable_diag_add_plus(row, col);
      diagleft_can_add_plus[indexDiagleft(row, col)] = false;
      diagright_can_add_plus[indexDiagright(row, col)] = false;
      score++;
    } else if (c == 'o') {      // o at i, j is equivalent to  x and + are both at i, j.
      a[row][col][0] = true;
      row_can_add_x[row] = false;
      col_can_add_x[col] = false;
      a[row][col][1] = true;
//      disable_diag_add_plus(row, col);
      diagleft_can_add_plus[indexDiagleft(row, col)] = false;
      diagright_can_add_plus[indexDiagright(row, col)] = false;
      score += 2;
    }
  }

//  void calculateScore() {
//    int score = 0;
//    for (int i = 0; i < n; i++) {
//      for (int j = 0; j < n; j++) {
//        if (a[i][j][0])
//          score++;
//        if (a[i][j][1])
//          score++;
//      }
//    }
//  }

  inline int convertRowColToInt(int row, int col) {
    return row * n + col;
  }

  inline int convertIntToRow(int index) {
    return index / n + 1;   // convert back to "index start from 1"
  }
  inline int convertIntToCol(int index) {
    return index % n + 1;   // convert back to "index start from 1"
  }

  vector<tuple<int, int>> find_places_for_x() {
    int row = 0, col = 0;
    vector<tuple<int, int>> places;
    while (row < n && col < n) {
      if (!row_can_add_x[row]) {
        row++;
        continue;
      }
      if (!col_can_add_x[col]) {
        col++;
        continue;
      }
      auto p = tuple<int, int>(row + 1, col + 1); // convert back to "index start from 1"
      places.push_back(p);
      a[row][col][0] = true;
      score++;
      int index = convertRowColToInt(row, col);
      if (a[row][col][1])
        result[index] = 'o';
      else
        result[index] = 'x';
      row_can_add_x[row++] = false;
      col_can_add_x[col++] = false;
    }
    return places;
  }

//  vector<tuple<int, int>> find_places_for_plus() {
//    int idleft;
//    int d1, d2;
//    int first_right = 0;
//
//    find_first_diag_right(first_right);
//    bool found;
//
//    vector<tuple<int, int>> places;
//    for (idleft = 0; idleft < 2*n-1; idleft++) {
//      if (!diagleft_can_add_plus[idleft])
//        continue;
//      d1 = idleft - n + 1;
//
//      found = false;
//      for (d2 = first_right; d2 < 2*n-1; d2++) {
//        if (!diagright_can_add_plus[d2])
//          continue;
//        bool b1 = (d1 + d2) % 2 == 0;
//        bool b2 = (d1 + d2) >=0 && (d1 + d2) < 2*n-1;
//        bool b3 = (d2 - d1) >=0 && (d2 - d1) < 2*n-1;
//        if (b1 && b2 && b3) {
//          int row = (d2 - d1) / 2;
//          int col = (d2 + d1) / 2;
////          cout << "diag debug: " << d1 << " " << d2 << endl;
//          auto p = tuple<int, int>(row + 1, col + 1);
//          places.push_back(p);  // convert back to "index start from 1"
//          a[row][col][1] = true;
//          score++;
//          int index = convertRowColToInt(row, col);
//          if (a[row][col][0])
//            result[index] = 'o';
//          else
//            result[index] = '+';
//          diagleft_can_add_plus[idleft] = false;
//          diagright_can_add_plus[d2] = false;
//          found = true;
//          find_first_diag_right(first_right);
//          break;
//        }
//      }
//
//      if (first_right == 2*n-1) {
//        break;    // diag right is empty now
//      }
//    }
//
//    return places;
//  }

//  void find_first_diag_right(int &r) {
//    while (!diagright_can_add_plus[r])
//      r++;
//  }

  vector<tuple<int, int>> find_places_for_plus() {
    int idleft = 0;
    int d1, d2;
    int first_right = 0;

    find_first_diag_right(first_right);

    vector<tuple<int, int>> places;
    while (idleft >= 0) {
//      cout << "idleft: " << idleft << endl;
      if (!diagleft_can_add_plus[idleft]) {
        idleft = nextIndex(idleft);
        continue;
      }

      d1 = idleft - n + 1;

      d2 = first_right;
      while (d2 >= 0) {
//        cout << "d2: " << d2 << endl;
        if (!diagright_can_add_plus[d2]) {
          d2 = nextIndex(d2);
          continue;
        }
        bool b1 = (d1 + d2) % 2 == 0;
        bool b2 = (d1 + d2) >= 0 && (d1 + d2) < 2 * n - 1;
        bool b3 = (d2 - d1) >= 0 && (d2 - d1) < 2 * n - 1;
        if (b1 && b2 && b3) {
          int row = (d2 - d1) / 2;
          int col = (d2 + d1) / 2;
//          cout << "diag debug: " << d1 << " " << d2 << endl;
          auto p = tuple<int, int>(row + 1, col + 1);
          places.push_back(p);  // convert back to "index start from 1"
          a[row][col][1] = true;
          score++;
          int index = convertRowColToInt(row, col);
          if (a[row][col][0])
            result[index] = 'o';
          else
            result[index] = '+';
          diagleft_can_add_plus[idleft] = false;
          diagright_can_add_plus[d2] = false;
          find_first_diag_right(first_right);
          break;
        }
        d2 = nextIndex(d2);
      }

      if (first_right < 0) {
        break;    // diag right is empty now
      }
      idleft = nextIndex(idleft);

    }

    return places;
  }

  void find_first_diag_right(int &r) {
    while (r > 0 && !diagright_can_add_plus[r])
      r = nextIndex(r);
  }

  // the mechanism is treat all diagonal site with their strength, see below for details
  int nextIndex(int current) {
    // middle diagonal is n-1
    if (current < n-1)
      return 2*n-2 - current;
    else if (current > n-1)
      return 2*n-1 - current;
    else    // == n-1, do not change anymore
      return -1;    // stop signal
  }

  // important, all diagonal sites are not equivalent, some site blocks more choices.
  int strengthOfDiagSite(int row, int col) {
    int strength = 1;   // self

    if (row <= col)
      strength += n - 1 - col + row;
    else
      strength += n - 1 + col - row;

    if (row + col <= n -1)
      strength += row + col;
    else
      strength += 2 * (n-1) - row - col;

    return strength;
  }


 private:

  int n = 0;
  bool ***a;
  bool *row_can_add_x;
  bool *col_can_add_x;
  bool **matrix_can_add_plus;    // easier to implement
  bool *diagleft_can_add_plus;    // j - i = XXX   diag with direction "\\\\\"
  bool *diagright_can_add_plus;   // j + i = XXX   diag with direction "/////"

  inline int indexDiagleft(int row, int col) {
    return leftDiag(row, col) + n - 1;
  }
  inline int indexDiagright(int row, int col) {
    return rightDiag(row, col);
  }
  inline int leftDiag(int row, int col) {
    return col - row;
  }
  inline int rightDiag(int row, int col) {
    return col + row;
  }

  void allocate() {
    a = new bool**[n];
    for (int i = 0; i < n; i++) {
      a[i] = new bool*[n];
      for (int j = 0; j < n; j++) {
        a[i][j] = new bool[2];    // 0 for x and 1 for +
        a[i][j][0] = false;       // no x character in a[i][j]
        a[i][j][1] = false;       // no + character in a[i][j]
      }
    }

    row_can_add_x = new bool[n];
    col_can_add_x = new bool[n];
    for (int i = 0; i < n; i++) {
      row_can_add_x[i] = true;
      col_can_add_x[i] = true;
    }

    matrix_can_add_plus = new bool*[n];
    for (int i = 0; i < n; i++) {
      matrix_can_add_plus[i] = new bool [n];
      for (int j = 0; j < n; j++) {
        matrix_can_add_plus[i][j] = true;
      }
    }

    diagleft_can_add_plus = new bool[2*n-1];
    diagright_can_add_plus = new bool[2*n-1];
    for (int i = 0; i < 2*n-1; i++) {
      diagleft_can_add_plus[i] = true;
      diagright_can_add_plus[i] = true;
    }
  }

  void deallocate() {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        delete [] a[i][j];
      }
      delete [] a[i];
    }
    delete[] a;

    delete [] row_can_add_x;
    delete [] col_can_add_x;

    for (int i = 0; i < n; i++) {
      delete [] matrix_can_add_plus[i];
    }
    delete [] matrix_can_add_plus;

    delete [] diagleft_can_add_plus;
    delete [] diagright_can_add_plus;
  }


};

void print_places(vector<tuple<int, int>> vec) {
  for (auto &v : vec) {
    cout << get<0>(v) << " " << get<1>(v) << endl;
  }
}


// part test
void unit_test() {
  Matrix m = Matrix(5);
  cout << "strength:\t" << m.strengthOfDiagSite(1, 1) << endl;
}

// test
void test() {
  cout << "=====================================" << endl;
  cout << "maximum long long:\t" << numeric_limits<long long>::max() << endl;
  cout << "maximum long:\t" << numeric_limits<long>::max() << endl;
  cout << "maximum int:\t" << numeric_limits<int>::max() << endl;
  cout << "maximum short:\t" << numeric_limits<short>::max() << endl;
  cout << "=====================================\n" << endl;
  int N = 3;
  int M = 4;
  Matrix m = Matrix(N);
  m.placeStyleAt('+', 2, 1);
  m.placeStyleAt('+', 2, 2);
  m.placeStyleAt('+', 2, 3);
  m.placeStyleAt('x', 3, 1);
  cout << "places for x:\n";
  vector<tuple<int, int>> place_x = m.find_places_for_x();
  print_places(place_x);
  cout << "places for +:\n";
  vector<tuple<int, int>> place_plus = m.find_places_for_plus();
  print_places(place_plus);
}


void solve() {
//  string filename = "test";
  string filename = "D-large";
  ifstream input_file;
  input_file.open(filename + ".in.txt");
  ofstream output_file;
  output_file.open(filename + ".out.txt");

  int t;
  input_file >> t;  // read t. cin knows that t is an int, so it reads it as such.
  int N, M, row, col;
  char c;
  cout << "total cases: " << t << endl;

  for (int i = 1; i <= t; ++i) {
    input_file >> N >> M;  // read n and then m.
    cout << "Case #" << i << " " << N << " " << M << endl;
    Matrix mat = Matrix(N);

    for (int j = 0; j < M; j++) {
      input_file >> c >> row >> col;
//      cout << "\t" << c << " " << row << " " << col << endl;
      mat.placeStyleAt(c, row, col);
    }

    auto place_x = mat.find_places_for_x();
    auto place_plus = mat.find_places_for_plus();
//    cout << "places for x:\n";
//    print_places(place_x);
//    cout << "places for +:\n";
//    print_places(place_plus);
    int score = mat.score;
    int actions = mat.result.size();
    output_file << "Case #" << i << ": " << score << " " << actions << endl;
    for (auto &r : mat.result) {
      output_file << r.second << " " << mat.convertIntToRow(r.first) << " " << mat.convertIntToCol(r.first) << endl;
    }

//    cout << "Case #" << i << ": " << out_max << " " << out_min << endl;
    // cout knows that n + m and n * m are ints, and prints them accordingly.
    // It also knows "Case #", ": ", and " " are strings and that endl ends the line.
  }

  input_file.close();
  output_file.close();
}

int main() {
//  unit_test();
//  test();
  solve();
}
