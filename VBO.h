#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include<glm/glm.hpp>
#include<glad/glad.h>
#include<vector>

// Структура для стандартизации вершин, используемых в мешах
struct Vertex
{
    glm::vec3 position; // Позиция вершины
    glm::vec3 normal;   // Нормаль вершины
    glm::vec3 color;    // Цвет вершины
    glm::vec2 texUV;    // Координаты текстуры
};

// Класс для работы с объектом буфера вершин (VBO)
class VBO
{
public:
    // Идентификатор объекта буфера вершин
    GLuint ID;

    // Конструктор, создающий объект буфера вершин и связывающий его с данными вершин
    VBO(std::vector<Vertex>& vertices);

    // Привязывает объект буфера вершин
    void Bind();

    // Отвязывает объект буфера вершин
    void Unbind();

    // Удаляет объект буфера вершин
    void Delete();
};

#endif
