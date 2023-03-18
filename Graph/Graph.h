/**
\file Graph.h
\brief Класс - Граф (неориентированный, невзвешенный)

Граф реализован посредством списков смежности - каждый узел содержит список смежных ему узлов
Каждый узел - объект класса Node.
Узел содержит полезные данные - объект класса Person, а также список указателей на смежные узлы
*/
#pragma once

#include <list>
#include <memory>

#include "../Node/Node.h"

//Классы - обработчики исключений
#include "../Exceptions/EmptyObject_Exception/EmptyObject_Exception.h"
#include "../Exceptions/InputYourself_Exception/InputYourself_Exception.h"



class Graph {
  public:
    /**
    Конструктор по-умолчанию - создать пустой граф без вершин
    */
    Graph();

    /**
    Запрет конструктора копирования
    */
    Graph(const Graph& other) = delete;

    /**
    Запрет конструктор перемещения -
    человек не может быть перемещён в другого
    */
    Graph(Graph&& other) = delete;

    /**
    Запрет оператора присваивания копированием -
    */
    Graph& operator= (const Graph& other) = delete;

    /**
    Запрет оператора присваивания перемещением
    */
    Graph& operator= (Graph&& other) = delete;

    /**
    Деструктор
    */
    ~Graph();

    /**
    Вернуть список указателей на узлы
    \return Список указателей на смежные узлы
    */
    const std::list<std::weak_ptr<Node> >& getListOfNodes() const;

    /**
    Добавить узел
    \param[in] node Указатель на узел
    */
    void addNode(std::shared_ptr<Node> node);

    /**
    Добавить ребро между заданными узлами
    \param[in] node_1 Первый узел
    \param[in] node_2 Второй узел
    */
    void addEdge(std::shared_ptr<Node> node_1, std::shared_ptr<Node> node_2);

    /**
    Проверить существует ли ребро между узлами
    \param[in] node Узел с которым проверить смежность
    */
    bool isExistEdge(std::shared_ptr<Node> node_1,
                     std::shared_ptr<Node> node_2) const;

    /**
    Вывести в консоль содержимое узлов графа (обход в глубину)
    */
    void show() const;

    /**
    Вывести в консоль друзей узла (содержимое смежных ему узлов)
    \param[in] node Узел для которого вывести друзей
    \param[in] levelFriend Уровень отдалённости друга (1-смежный, 2-знакомый друга)
    */
    void showFriends(const std::shared_ptr<Node> node, size_t levelFriend);

    /**
    Вывести в консоль все пары друзей
    \param[in] levelFriend Уровень отдалённости друга (1-смежный, 2-знакомый друга)
    */
    void showFriends(size_t levelFriend);

  private:
    /**
    Зайти в узел для обхода графа в глубину
    \param[in] nodeToVisit Узел в который зайти
    \param[in] visitedNodes Список уже посещённых узлов
    */
    void visit(std::shared_ptr<Node> nodeToVisit,
               std::list<std::weak_ptr<Node> >* visitedNodes) const;

    /**
    Зайти в узел при просмотре друзей узла
    \param[in] nodeToVisit Узел в который зайти
    \param[in] visitedNodes Список уже посещённых узлов
    \param[in] depthCount Счётчик уровня отдалённости от стартового узла
    \param[in] maxDepth Максимальный уровень отдаллённости от стартового узла
    */
    void visit(std::shared_ptr<Node> nodeToVisit,
               std::list<std::weak_ptr<Node> >* visitedNodes,
               size_t& depthCount,
               size_t maxDepth);

    std::list<std::weak_ptr<Node> > nodes_;	///<Узлы графа
};



namespace graph {
  /**
  Запустить тесты класса Graph
  */
  void runTest();
}