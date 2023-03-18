/**
\file EmptyString_Exception.h
\brief Класс EmptyString_Exception - для обработки исключения "Пустая строка"

Класс EmptyString_Exception наследует у класса std::exception и перегружает метод what()
*/

#pragma once

#include <string>
#include <exception>


class EmptyString_Exception : public std::exception {
	public:
    /**
    Исключение получает на вход строку об ошибке -
    конструктор по-умолчанию не имеет смысла
    */
    EmptyString_Exception() = delete;

    /**
    Параметризованный конструктор.
    \param[in] errorMessage Сообщение об ошибке
    */
    explicit EmptyString_Exception(const std::string& errorMessage);

    /**
    Перегруженный метод базового класса std::exception
    \return Указатель на сообщение об ошибке
    */
    virtual const char* what() const noexcept override;

  private:
    std::string errorMessage_;	///<Сообщение об ошибке
};