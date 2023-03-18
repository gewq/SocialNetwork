/**
\file Node.h
\brief Класс - узел графа

Объект класса представляет собой узел графа.
Каждый объект содержит:
- полезные данные - класс Person
- список смежных ему узлов
*/
#pragma once

#include <list>
#include <memory>
#include <string>

#include "../Person/Person.h"


class Node {
  public:
    /**
    Запрет конструктора по-умолчанию
    */
    Node() = delete;

    /**
    Параметризованный конструктор
    \param[in] personName Имя человека который содержится в узле
    */
    explicit Node(const std::string& personName);

    /**
    Запрет конструктора копирования
    */
    Node(const Node& other) = delete;

    /**
    Запрет конструктор перемещения -
    человек не может быть перемещён в другого
    */
    Node(Node&& other) = delete;

    /**
    Запрет оператора присваивания копированием -
    */
    Node& operator= (const Node& other) = delete;

    /**
    Запрет оператора присваивания перемещением
    */
    Node& operator= (Node&& other) = delete;

    /**
    Деструктор
    */
    ~Node();

    /**
    Вернуть имя человека, содержащегося в узле
    \return Строку, содержащую имя
    */
    std::string getName() const;

    /**
    Вернуть список указателей на смежные узлы
    \return Ссылку на список указателей на смежные узлы
    */
    const std::list<std::weak_ptr<Node> >& getAdjacentNodes() const;

    /**
    Добавить смежный узел
    \param[in] node Смежный узел
    */
    void addAdjacentNode(const std::weak_ptr<Node> node);

    /**
    Проверить существует ли ребро между текущим и заданным узлами
    \param[in] node Узел с которым проверить смежность
    */
    bool isAdjacent(const std::shared_ptr<Node> node) const;

  private:
    Person person_;	///<Полезные данные
    //weak_ptr - чтобы срабатывали деструкторы узлов
		//даже если их указатели указывают друг на друга
    std::list<std::weak_ptr<Node> > adjacentNodes_;	///<Список указателей на смежные узлы
};



namespace node {
  /**
  Запустить тесты класса Node
  */
  void runTest();
};