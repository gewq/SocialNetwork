#include "Graph.h"

#include <algorithm>
#include <assert.h>
#include <iostream>


Graph::Graph()
{
}



Graph::~Graph()
{
}



const std::list<std::weak_ptr<Node> >& Graph::getListOfNodes() const
{
  return nodes_;
}



void Graph::addNode(std::shared_ptr<Node> node)
{
  //Обработка ошибок
  if (node.get() == nullptr) {
    throw EmptyObject_Exception("Graph::addNode()");
  }

  //Поместить узел в список узлов графа
  nodes_.push_back(node);
}



void Graph::addEdge(std::shared_ptr<Node> node_1, std::shared_ptr<Node> node_2)
{
  //Обработка ошибок
  if (node_1 == nullptr) {
    throw EmptyObject_Exception("Graph::addEdge()");
  }
  if (node_2 == nullptr) {
    throw EmptyObject_Exception("Graph::addEdge()");
  }

  //Взаимно для обоих узлов добавить указатели друг на друга в списки смежных узлов
  node_1->addAdjacentNode(node_2);
  node_2->addAdjacentNode(node_1);
}



bool Graph::isExistEdge(std::shared_ptr<Node> node_1,
                        std::shared_ptr<Node> node_2) const
{
  //Обработка ошибок
  if (node_1.get() == nullptr) {
    throw EmptyObject_Exception("Graph::isExistEdge()");
  }
  if (node_2.get() == nullptr) {
    throw EmptyObject_Exception("Graph::isExistEdge()");
  }

  //Оба узла смежны друг другу
  if ((node_1->isAdjacent(node_2) == true) &&
      (node_2->isAdjacent(node_1) == true)) {
    return true;
  }
  return false;
}



void Graph::show() const
{
  //Обработка ошибок
  if (nodes_.empty()) {
    std::cout << "There is no nodes.\n";
    return;
  }

  std::list<std::weak_ptr<Node> > visitedNodes;	//Список посещённых узлов

  //Посетить в глубину начиная со стартовой вершины
  auto startNode = nodes_.front().lock();

  visit(startNode, &visitedNodes);
  std::cout << std::endl;
}



void Graph::showFriends(const std::shared_ptr<Node> node, size_t levelFriend)
{
  //Обработка ошибок
  if (node.get() == nullptr) {
    throw EmptyObject_Exception("Graph::showFriends()");
  }

  std::list<std::weak_ptr<Node> > visitedNodes;	//Список посещённых узлов
  size_t depthCount = 0;	//Как далеко ушли от исходного узла
  std::cout << "Friends of " << node->getName() << ": ";
  visit(node, &visitedNodes, depthCount, levelFriend);
  std::cout << std::endl;
}



void Graph::showFriends(size_t levelFriend)
{
  //Итератор - const (cbegin() / cend() вместо begin() / end()) поскольку узлы не модифицируем
	for (auto iter = nodes_.cbegin(); iter != nodes_.cend(); ++iter) {
    showFriends(iter->lock(), levelFriend);	//Вывести друзей
  }
}



//----------------------------------------------------------------
void Graph::visit(std::shared_ptr<Node> nodeToVisit,
                  std::list<std::weak_ptr<Node> >* visitedNodes) const
{
  //Обработка ошибок
  if (nodeToVisit.get() == nullptr) {
    throw EmptyObject_Exception("Graph::visit()");
  }

  std::cout << nodeToVisit->getName();
  visitedNodes->push_back(nodeToVisit);	//Поместить текущий узел в список посещённых

  //Пройти по смежным узлам
  for(auto adjacentNodePtr = nodeToVisit->getAdjacentNodes().cbegin();
      adjacentNodePtr != nodeToVisit->getAdjacentNodes().cend();
      ++adjacentNodePtr) {
    //Определить - посещали ли текущий узел (есть ли он в списке посещённых узлов)
    bool isVisited = std::find_if(visitedNodes->cbegin(),
                                  visitedNodes->cend(),
    [&adjacentNodePtr](const std::weak_ptr<Node>& nodePtr) {
      return adjacentNodePtr->lock() == nodePtr.lock();
    }) != visitedNodes->cend();

    //Если не посещали узел -> посетить
    if (!isVisited) {
      std::cout << " -> ";
      visit(adjacentNodePtr->lock(), visitedNodes);
    }
  }
}



void Graph::visit(std::shared_ptr<Node> nodeToVisit,
                  std::list<std::weak_ptr<Node> >* visitedNodes,
                  size_t& depthCount,
                  size_t maxDepth)
{
  //Обработка ошибок
  if (nodeToVisit.get() == nullptr) {
    throw EmptyObject_Exception("Graph::visit()");
  }

  //Находимся дальше максимального удаления от стартового узла
  if (depthCount > maxDepth) {
    return;	//Выйти из узла
  }
  //Выводить имя узлов кроме стартового
  if (depthCount != 0) {
    std::cout << nodeToVisit->getName() << " ";
  }
  visitedNodes->push_back(nodeToVisit);	//Поместить текущий узел в список посещённых
  ++depthCount;

  //Пройти по смежным узлам
  for(auto adjacentNodePtr = nodeToVisit->getAdjacentNodes().cbegin();
      adjacentNodePtr != nodeToVisit->getAdjacentNodes().cend();
      ++adjacentNodePtr) {
    //Определить - посещали ли текущий узел (есть ли он в списке посещённых узлов)
    bool isVisited = std::find_if(visitedNodes->cbegin(),
                                  visitedNodes->cend(),
    [&adjacentNodePtr](const std::weak_ptr<Node>& nodePtr) {
      return adjacentNodePtr->lock() == nodePtr.lock();
    }) != visitedNodes->cend();

    //Если не посещали узел -> посетить
    if (!isVisited) {
      visit(adjacentNodePtr->lock(), visitedNodes, depthCount, maxDepth);
    }
  }
  --depthCount;
}
//================================================================

static void testCtor();
static void testAddNode();
static void testAddEdge();
static void testShowFriends();


void graph::runTest()
{
  testCtor();
  testAddNode();
  testAddEdge();
  testShowFriends();
}



static void testCtor()
{
  Graph socialNetwork;
  //После создания графа узлов нет - список узлов пуст
  assert(socialNetwork.getListOfNodes().empty() == true);

  //Запрет конструктора копирования
//  Graph socialNetwork_2(socialNetwork);

  //Запрет конструктора перемещения
//  Graph socialNetwork_2(std::move(socialNetwork));

  //Запрет оператора присваивания
//  Graph socialNetwork_2;
//  socialNetwork_2 = socialNetwork;

  //Запрет изменения объекта по const ссылке
//  socialNetwork.getListOfNodes().push_back(node_1);
}



static void testAddNode()
{
  Graph socialNetwork;
  //Создать узел для добавления в граф
  auto node_1 = std::make_shared<Node>("node_1");
  socialNetwork.addNode(node_1);
  assert(socialNetwork.getListOfNodes().empty() == false);
  assert(socialNetwork.getListOfNodes().front().lock()->getName() == "node_1");

  //Тест выброс исключения
//  std::shared_ptr<Node> nodeEmpty(nullptr);
//  socialNetwork.addNode(nodeEmpty);	//Добавить пустой объект
}



static void testAddEdge()
{
  Graph socialNetwork;
  auto node_1 = std::make_shared<Node>("node_1");
  auto node_2 = std::make_shared<Node>("node_2");
  socialNetwork.addNode(node_1);
  socialNetwork.addNode(node_1);

  //Узлы добавлены в граф, но не связаны друг с другом - ребро отсутствует
  assert(socialNetwork.isExistEdge(node_1, node_2) == false);
  socialNetwork.addEdge(node_1, node_2);	//Добавить ребро между узлами
  //Узлы связаны ребром
  assert(socialNetwork.isExistEdge(node_1, node_2) == true);

  //Тест выброс исключения
//  std::shared_ptr<Node> nodeEmpty(nullptr);
//  socialNetwork.addEdge(node_1, nodeEmpty);	//Добавить ребро с пустым объектом
//  socialNetwork.addEdge(nodeEmpty, node_1);	//Добавить ребро с пустым объектом
//  socialNetwork.isExistEdge(node_1, nodeEmpty);	//Проверить наличие ребра с пустым объектом
//  socialNetwork.isExistEdge(nodeEmpty, node_1);	//Проверить наличие ребра с пустым объектом
}



static void testShowFriends()
{
  Graph socialNetwork;
  auto node_1 = std::make_shared<Node>("node_1");
  auto node_2 = std::make_shared<Node>("node_2");
  auto node_3 = std::make_shared<Node>("node_3");
  auto node_4 = std::make_shared<Node>("node_4");
  auto node_5 = std::make_shared<Node>("node_5");
  socialNetwork.addNode(node_1);
  socialNetwork.addNode(node_2);
  socialNetwork.addNode(node_3);
  socialNetwork.addNode(node_4);
  socialNetwork.addNode(node_5);
  socialNetwork.addEdge(node_1, node_2);
  socialNetwork.addEdge(node_2, node_3);
  socialNetwork.addEdge(node_3, node_4);
  socialNetwork.addEdge(node_4, node_5);

  socialNetwork.show();
  socialNetwork.showFriends(3);	//Друзья через 3 рукопожатия
}