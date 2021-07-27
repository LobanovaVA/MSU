#include <iostream>
#include <vector>

#include <tuple>
#include <map>

using namespace std;

/* Реализуйте шаблонную функцию GetRefStrict, которая на вход принимает: map и значение ключа k. 
 * Если элемент по ключу k в коллекции отсутствует, то функция должна бросить исключение runtime_error,
 * иначе вернуть ссылку на элемент в коллекции. */

template <typename Key, typename Value>
Value & GetRefStrict (map <Key, Value> &m, Key k)
{
  auto it = m.find (k);
  if (it != m.end())
    return it->second;
  else 
    throw std::runtime_error ("no element");
}

#ifdef COURSERA
template<typename KeyType, typename ValueType>
ValueType& GetRefStrict(map<KeyType, ValueType>& input_map, KeyType key) {
    if (input_map.count(key) == 0) {
        throw runtime_error("no such key in dictionary");
    }
    return input_map[key];
}
#endif

int main ()
{
  map<int, string> m = {{0, "value"}};
  string& item = GetRefStrict(m, 0);
  item = "newvalue";
  cout << m[0] << " " << endl; // выведет newvalue

  return 0;
}