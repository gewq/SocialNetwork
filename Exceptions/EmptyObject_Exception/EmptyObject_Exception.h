/**
\file EmptyObject_Exception.h
\brief Класс EmptyObject_Exception - для обработки исключения "Попытка добавить пустой объект"

Класс EmptyObject_Exception наследует у класса std::exception и перегружает метод what()
*/

#pragma once

#include <string>
#include <exception>


class EmptyObject_Exception : public std::exception {
  public:
    /**
    Исключение получает на вход строку об ошибке -
    конструктор по-умолчанию не имеет смысла
    */
    EmptyObject_Exception() = delete;

    /**
    Параметризованный конструктор.
    \param[in] errorMessage Сообщение об ошибке
    */
    explicit EmptyObject_Exception(const std::string& errorMessage);

    /**
    Перегруженный метод базового класса std::exception
    \return Указатель на сообщение об ошибке
    */
    virtual const char* what() const noexcept override;

  private:
    std::string errorMessage_;	///<Сообщение об ошибке
};