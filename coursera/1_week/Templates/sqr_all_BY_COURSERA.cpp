#include <iostream>
#include <vector>

#include <tuple>
#include <map>

using namespace std;

// Для простых типов
template<typename T>
T Sqr(T value);

// Для вектора
template<typename T>
vector<T> Sqr(const vector<T>& value);

// Для словаря
template<typename K, typename V>
map<K, V> Sqr(const map<K, V>& value);

// Для пары
template<typename K, typename V>
pair<K, V> Sqr(const pair<K, V>& value);

// Теперь реализуем их в соответствии с заданием
template<typename T>
T Sqr(T value) {
  return value * value;
}

template<typename T>
vector<T> Sqr(const vector<T>& value) {
  vector<T> result;
  for (const T& x : value) {
    // Здесь важно, что вместо x * x вызывается функция Sqr:
    // это позволяет возводить в квадрат составные объекты
    result.push_back(Sqr(x));
  }

  return result;
}

template<typename K, typename V>
map<K, V> Sqr(const map<K, V>& value) {
  map<K, V> result;
  for (const auto& element : value) {
    result[element.first] = Sqr(element.second);
  }
  return result;
}

template<typename K, typename V>
pair<K, V> Sqr(const pair<K, V>& value) {
  return {Sqr(value.first), Sqr(value.second)};
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