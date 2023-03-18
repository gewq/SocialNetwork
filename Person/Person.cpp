#include "Person.h"
#include <assert.h>
#include <iostream>

//Классы - обработчики исключений
#include "../Exceptions/EmptyString_Exception/EmptyString_Exception.h"


Person::Person(const std::string& name): name_(name)
{
  if (name.empty()) {
  	throw EmptyString_Exception("Person::constructor");
  }
}



Person::Person(const Person& other): name_(other.name_)
{
}



Person::~Person()
{
}



std::string Person::getName() const
{
  return name_;
}



//================================================================
void person::runTest()
{
  //Тест параметризованного конструктора
  std::string testName = "Test";
  Person p(testName);
  assert(p.getName() == testName);

  //Тест конструктора копирования
  Person p1(p);
  Person p2 = p;
  assert(p1.getName() == testName);
  assert(p2.getName() == testName);

  //Тест выброс исключения
//	Person personEmptyName("");	//Пустое имя

  //Запрет конструктора по-умолчанию
//	Person p;

  //Запрет конструктора перемещения
//  Person p3(std::move(p));

  //Запрет неявного преобразования типа
//  Person P3 = testName;

  //Запрет оператора присваивания
//  Person PP("PP");
//  Person PL("PL");
//  PP = PL;
}