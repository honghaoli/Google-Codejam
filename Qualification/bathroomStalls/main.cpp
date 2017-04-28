#include <iostream>
#include <fstream>
#include <vector>
#include <queue>


using namespace std;  // since cin and cout are both in namespace std, this saves some text

// estimate the first person K that starts with min = max = 0, so skip heavy computations.
long long estimate_first_zero(long long N) {
  if (N == 2)
    return 2;
  if (N == 1)
    return 1;
  if (N % 2 != 0)
    return 2 * estimate_first_zero( (N-1) / 2 );
  else
    return estimate_first_zero( (N-1) / 2 ) + estimate_first_zero( (N+1) / 2 );
}


void max_and_min(long long stalls, long long users, long long *maxs, long long *mins) {
  if (users > stalls/2 && users >= estimate_first_zero(stalls)) {
    *maxs = 0;
    *mins = 0;
    return;
  }
  // Using lambda to compare elements.
//  auto cmp = [](long long left, long long right) { return left <= right ;};
  // use priority queue to store consecutive empty space region, the big integer is the number of un-occupied stalls minus one.
//  priority_queue<long long, vector<long long>, decltype(cmp)> empty_regions(cmp);
  priority_queue<long long> empty_regions;
  // initial setup
  empty_regions.push(--stalls);

  // start loop
  long long new_min, new_max, max_current;
  while (!empty_regions.empty()) {
    max_current = empty_regions.top();
    empty_regions.pop();

    if (max_current % 2 != 0 ) {
      new_min = max_current / 2;
      new_max = new_min + 1;
    } else {
      new_min = max_current / 2;
      new_max = new_min;
    }

    users--;
    // all users finish
    if (users == 0)
      break;

    // add new regions only if N - 1 > 0, non-zero regions
    if (new_min > 1) {
      empty_regions.push(--new_min);
    }
    if (new_max > 1) {
      empty_regions.push(--new_max);
    }
  }

  // no space with min >= 1 left, all (0, 0) from now on
  if (users > 0) {
    *mins = 0;
    *maxs = 0;
  } else {
    *mins = new_min;
    *maxs = new_max;
  }

}

// test
void test() {
  cout << "maximum long long:\t" << numeric_limits<long long>::max() << endl;
  long long stalls = 1000000000000000000;
  long long users = 1;
  long long maxs, mins;
  max_and_min(stalls, users, &maxs, &mins);
  cout << "input stalls number:\t" << stalls << endl;
  cout << " input users number:\t" << users << endl;
  cout << "         output max:\t" << maxs << endl;
  cout << "         output min:\t" << mins << endl;
}

void solve() {
  string filename = "C-large";
  ifstream input_file;
  input_file.open(filename + ".in.txt");
  ofstream output_file;
  output_file.open(filename + ".out.txt");
  int t;
  input_file >> t;  // read t. cin knows that t is an int, so it reads it as such.
  long long input_N, input_K;
  long long out_min, out_max;
  cout << "total cases: " << t << endl;
  for (int i = 1; i <= t; ++i) {
    input_file >> input_N >> input_K;  // read n and then m.
    cout << "input string: " << input_N << " " << input_K << endl;
    max_and_min(input_N, input_K, &out_max, &out_min);
    cout << "Case #" << i << ": " << out_max << " " << out_min << endl;
    output_file << "Case #" << i << ": " << out_max << " " << out_min << endl;
    // cout knows that n + m and n * m are ints, and prints them accordingly.
    // It also knows "Case #", ": ", and " " are strings and that endl ends the line.
  }
  input_file.close();
  output_file.close();
}

int main() {
//  test();
  solve();
}
