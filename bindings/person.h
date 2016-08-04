#include <string>

using namespace std;

class Person{
public:
  Person();
  Person(string name,int year);
  string name;
  int year;
  int getYear();
private:
  int id;
};
