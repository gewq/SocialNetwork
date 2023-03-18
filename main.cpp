/**
\file main.cpp
\brief Программа выводит все пары людей, знакомых через 3 рукопожатия (друзья и друзья друзей).

Исходными данными является граф социальных связей людей.
Граф 				- неориентированный, невзвешенный - ребра не имеют весов и направлений.
Узел графа 	- человек, характеризующийся именем
Ребро графа	- признак знакомства двух людей. Есть ребро - знакомы, нет ребра - не знакомы.
*/

#include <iostream>

#include "Person/Person.h"
#include "Node/Node.h"
#include "Graph/Graph.h"



int main(int argc, char** argv)
{
  try {
    person::runTest();
    node::runTest();
    graph::runTest();
  }
  catch (const std::exception& error) {
    std::cerr << error.what() << std::endl;
  }
  catch (...) {
    std::cerr << "Undefined exception" << std::endl;
  }

  return EXIT_SUCCESS;
}