#include "Node.h"

#include <iostream>
#include <algorithm>
#include <assert.h>

//Классы - обработчики исключений
#include "../Exceptions/EmptyObject_Exception/EmptyObject_Exception.h"
#include "../Exceptions/InputYourself_Exception/InputYourself_Exception.h"


Node::Node(const std::string& personName): person_(personName)
{
}



Node::~Node()
{
}



std::string Node::getName() const
{
  return person_.getName();
}



const std::list<std::weak_ptr<Node> >& Node::getAdjacentNodes() const
{
  return adjacentNodes_;
}



void Node::addAdjacentNode(const std::weak_ptr<Node> node)
{
  //Обработка ошибок
  if (node.lock().get() == nullptr) {
    throw EmptyObject_Exception("Node::addAdjacentNode()");
  }
  if (this == node.lock().get()) {
    throw InputYourself_Exception("Node::addAdjacentNode()");
  }

  adjacentNodes_.push_back(node);
}



bool Node::isAdjacent(const std::shared_ptr<Node> node) const
{
  //Обработка ошибок
  if (node.get() == nullptr) {
    throw EmptyObject_Exception("Node::isAdjacent()");
  }
  if (node.get() == this) {
  	throw InputYourself_Exception("Node::isAdjacent()");
  }

  //Признак наличия узла в списке смежных узлов
  bool isFound = std::find_if(adjacentNodes_.cbegin(),
                              adjacentNodes_.cend(),
  [&node](const std::weak_ptr<Node>& nodePtr) {
    return node == nodePtr.lock();
  }) != adjacentNodes_.cend();

  return isFound;
}
//================================================================

static void testCtor();
static void testAddNode();


void node::runTest()
{
  testCtor();
  testAddNode();
}



static void testCtor()
{
  std::string testName = "Node_1";
  auto node = std::make_shared<Node>(testName);
  assert(node->getName() == testName);
  //После создания у узла нет смежных узлов - список смежных узлов пуст
  assert(node->getAdjacentNodes().empty() == true);

  //Запрет конструктора по-умолчанию
//	Node node;

  //Запрет конструктора копирования
//  Node nodeCopy("Test");
//  Node node(nodeCopy);

  //Запрет конструктора перемещения
//  Node nodeCopy("Test");
//  Node node(std::move(nodeCopy));

  //Запрет оператора присваивания
//  Node node_1("node_1");
//  Node node_2("node_2");
//  node_1 = node_2;
}



static void testAddNode()
{
  std::string testName_1 = "Node_1";
  std::string testName_2 = "Node_2";
  auto node_1 = std::make_shared<Node>(testName_1);
  auto node_2 = std::make_shared<Node>(testName_2);
  //Узлы не смежные
  assert(node_1->isAdjacent(node_2) == false);
  assert(node_2->isAdjacent(node_1) == false);

  //Добавить смежный узел друг другу
  node_1->addAdjacentNode(node_2);
  node_2->addAdjacentNode(node_1);

  //Узлы смежные
  assert(node_1->isAdjacent(node_2) == true);
  assert(node_2->isAdjacent(node_1) == true);
  assert(node_1->getAdjacentNodes().empty() == false);
  assert(node_2->getAdjacentNodes().empty() == false);

  //Тест выброс исключения
//  std::shared_ptr<Node> nodeEmpty(nullptr);
//  node_1->addAdjacentNode(nodeEmpty);	//Добавить пустой объект
//  node_1->isAdjacent(nodeEmpty);			//Проверить смежность с пустым объектом
//  node_1->addAdjacentNode(node_1);	//Добавить себя в качестве смежного узла
//  node_1->isAdjacent(node_1);				//Проверить на смежность с самим собой
}