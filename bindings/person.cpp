#include "person.h"
#include <string>
#include <iostream>

using namespace std;

Person::Person(){
  this->name="Aaron";
  this->year=2000;
  this->id = 1;
}

Person::Person(string name,int year){
  this->name = name;
  this->year = year;
}

int Person::getYear(){
  return year;
}
