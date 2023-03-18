/**
\file Person.h
\brief Класс - человек

Объекты класса представляют собой человека, обладающего именем
*/

#pragma once

#include <string>

class Person {
  public:
    /**
    Запрет конструктора по-умолчанию - человек без имени не может быть
    */
    Person() = delete;

    /**
    Параметризованный конструктор.
    \param[in] name Имя человека
    */
    explicit Person(const std::string& name);

    /**
    Конструктор копирования - два разных человека могут иметь одинаковое имя
    \param[in] other Объект класса который скопировать
    */
    Person(const Person& other);

    /**
		Запрет конструктора перемещения -
    человек не может быть перемещён в другого
    */
    Person(Person&& other) = delete;

    /**
		Запрет оператора присваивания копированием -
    после создания имя не может быть изменено
		*/
    Person& operator= (const Person& other) = delete;

    /**
		Запрет оператора присваивания перемещением -
    человек не может быть перемещён в другого
		*/
    Person& operator= (Person&& other) = delete;

    /**
    Деструктор
		*/
    ~Person();

    /**
    Вернуть имя человека
    \return Строку, содержащую имя
    */
    std::string getName() const;

  private:
    std::string name_;	///<Имя человека
};



namespace person {
  /**
  Запустить тесты класса Person
  */
  void runTest();
}