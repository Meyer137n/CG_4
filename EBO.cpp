#include "EBO.h"

// Конструктор класса Mesh, который инициализирует меш из вершин, индексов и текстур
EBO::EBO(std::vector<GLuint>& indices)
{
    // Генерация идентификатора буфера
    glGenBuffers(1, &ID);
    // Привязка буфера к целевому массиву элементов
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
    // Копирование данных индексов в буфер
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
}

// Привязывает объект EBO
void EBO::Bind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

// Отвязывает объект EBO
void EBO::Unbind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

// Удаляет объект EBO
void EBO::Delete()
{
    glDeleteBuffers(1, &ID);
}
