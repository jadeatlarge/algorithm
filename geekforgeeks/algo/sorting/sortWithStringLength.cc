#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

using namespace std;

int main() {
  vector<string> ans{"GeekForGeek", "I", "From"};
  sort(ans.begin(), ans.end(),
       [](string a, string b) { return a.length() < b.length(); });
  copy(ans.begin(), ans.end(), ostream_iterator<string>(cout, ","));
  cout << endl;
}