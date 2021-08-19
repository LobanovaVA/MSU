#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Human
{
private:
  const string Type;
  const string Name;

public:
  Human (
    const string & type = "Human", 
    const string & name = "Noname") 
    : Type (type), Name (name) {}

  const string Get_Type () const { return Type; }
  const string Get_Name () const { return Name; }

  // Type + split + ": " + Name  
  // Only for Policeman's check split with "'s name is"
  const string Log_Type_Name (const string & split = "") const
  {
    ostringstream os;
    os << Get_Type () << split << ": " << Get_Name ();
    return os.str();
  }

  // Action + split + Object  
  // Only for Policeman's check split without ":"
  const string Log_Action_Object (
    const string & action, 
    const string & object = "", const string & split = ": ") const
  {
    ostringstream os;

    os << action;
    if (object != "")
      os << split << object;
    
    return os.str();
  }

  virtual void Walk (const string & destination) const
  {
    cout << Log_Type_Name () << " " 
         << Log_Action_Object ("walks to", destination) << endl;
  }

  virtual ~Human () = default;
};


class Student : public Human
{
private:
  const string FavouriteSong;

public:
  Student (
    const string & name, 
    const string & favourite_song,
    const string & type = "Student") 
      : Human (type, name), FavouriteSong (favourite_song) {}

  void Learn () const
  {
    cout << Log_Type_Name () << " " 
         << Log_Action_Object ("learns") << endl;
  }

  void SingSong () const
  {
    cout << Log_Type_Name () << " " 
         << Log_Action_Object ("sings a song", FavouriteSong) << endl;
  }

  void Walk (const string & destination) const override 
  {
    cout << Log_Type_Name () << " " 
         << Log_Action_Object ("walks to", destination) << endl;
    SingSong ();
  }
};


class Teacher : public Human
{
private:
  const string Subject;

public:
  Teacher (
    const string & name, 
    const string & subject,
    const string & type = "Teacher") 
      : Human (type, name), Subject (subject) {}

  void Teach () const
  {
    cout << Log_Type_Name () << " " 
         << Log_Action_Object ("teaches", Subject) << endl;
  }
};


class Policeman : public Human
{
public:
  Policeman (
    const string & name, 
    const string & type = "Policeman") 
    : Human (type, name) {}

  void Check (const Human & human) const
  {
    cout << Log_Type_Name () << " " 
         << Log_Action_Object ("checks", human.Get_Type (), " "/*split*/) << ". "
         << human.Log_Type_Name ("'s name is") << endl;
  }
};


void VisitPlaces (const Human & human, const vector<string> & places) 
{
  for (const auto p : places) 
    human.Walk (p);
}


int main () 
{
  vector<string> places = {"Moscow", "London"};
  string town = "New-York";

  Student s ("Ann", "We will rock you");
  s.Learn ();
  s.SingSong ();
  s.Walk (town);

  Teacher t ("Jim", "Math");
  t.Teach ();
  t.Walk (town);

  Policeman p ("Bob");
  p.Check (s);
  p.Check (t);
  p.Check (p);
  p.Walk (town);

  VisitPlaces (s, places);
  VisitPlaces (t, places);
  VisitPlaces (p, places);

  return 0;
}
