#include <iostream>

using namespace std;

int main() 
{
  unsigned N, R;
  cin >> N >> R;

  uint64_t w, h, d;
  uint64_t sum_volume = 0; 

  for (size_t i = 0 ; i < N; i++)
    {
      cin >> w >> h >> d;
      sum_volume += w * h * d;
    }

  cout << sum_volume * R << endl;
  return 0;
}
