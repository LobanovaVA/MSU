#include <iostream>

using namespace std;

class Animal 
{
public:
  Animal (string init_name) : Name (init_name) {}

  const string Name;
};


class Dog : public Animal
{
public:
  Dog (string init_name) : Animal (init_name) {}

  void Bark () { cout << Name << " barks: woof!" << endl; }
};
