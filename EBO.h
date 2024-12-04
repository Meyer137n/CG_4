#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include<glad/glad.h>
#include<vector>

// Класс для управления объектом буфера элементов (EBO)
class EBO
{
public:
    // Идентификатор объекта буфера элементов
    GLuint ID;

    // Конструктор, который создает объект буфера элементов и связывает его с индексами
    EBO(std::vector<GLuint>& indices);

    // Связывает (активирует) объект буфера элементов
    void Bind();
    // Отвязывает объект буфера элементов
    void Unbind();
    // Удаляет объект буфера элементов
    void Delete();
};

#endif
