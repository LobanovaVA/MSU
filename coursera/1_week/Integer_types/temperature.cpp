#include <iostream>
#include <vector>

using namespace std;

int main() {

  size_t N;
  cin >> N;

  vector<int> temp (N);
  int64_t sum = 0; 

  for (size_t i = 0 ; i < N; i++)
  {
    cin >> temp.at (i);
    sum += temp.at (i);
  }

  int avg = sum /  static_cast<int> (N);

  vector<unsigned> ans;
  for (size_t i = 0 ; i < N; i++)
  {
    if (temp.at (i) > avg)
      ans.push_back (i);
  }

  cout << ans.size () << endl;
  for (size_t a : ans)
    cout << a << " ";
  cout << endl;
  
  return 0;
}
