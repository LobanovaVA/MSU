#include <iostream>
#include <vector>

#include <tuple>
#include <map>

using namespace std;

// defs
template <typename T> 
T Sqr (T x);

template <typename T> 
vector <T> operator * (const vector <T> & v1, const vector <T> &);

template <typename F, typename S> 
pair <F, S> operator * (const pair <F, S>& p1, const pair <F, S>& p2);

template <typename Key, typename Value> 
map <Key, Value> operator * (const map <Key, Value> &m1, const map <Key, Value> &);


// realization
template <typename T> 
T Sqr (T x) { return x * x; }

template <typename F, typename S>
pair <F, S> operator * (const pair <F, S>& p1, const pair <F, S>& p2) 
{
  F f = p1.first  * p2.first ;
  S s = p1.second * p2.second ;
  return {f, s};
}

template <typename T>
vector <T> operator * (const vector <T> & v1, const vector <T> &) 
{
  auto ans = v1;
  for (auto &i : ans) 
    i = i * i;
  return ans;
}

template <typename Key, typename Value> // for map
map <Key, Value> operator * (const map <Key, Value> &m1, const map <Key, Value> &) 
{
  auto ans = m1;
  for (auto & [key, value] : ans)
    value = value * value;
  return ans;
}



int main ()
{
  double a =1.0;
    cout<<Sqr(a)<< endl ;
  map<int,vector<int>> maps;
    cout<<Sqr(maps).size() << endl;

  cout << endl;
  vector<int> v = {1, 2, 3};

  cout << "new vector:";
  for (int x : Sqr(v)) 
    cout << ' ' << x;

  cout << endl;

  cout << "old vector:";
  for (int x : v) 
    cout << ' ' << x;

  cout << endl;

  map<int, pair<int, int>> map_of_pairs = {
    {4, {2, 2}},
    {7, {4, 3}}
  };

  cout << "new map of pairs:" << endl;
  for (const auto& x : Sqr(map_of_pairs)) {
    cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
  }

  cout << "old map of pairs:" << endl;
  for (const auto& x : map_of_pairs) {
    cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
  }

  return 0;
}