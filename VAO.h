#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include<glad/glad.h>
#include"VBO.h"

// Класс для работы с объектом массива вершин (VAO)
class VAO
{
public:
    // Идентификатор объекта массива вершин
    GLuint ID;

    // Конструктор, генерирующий ID для VAO
    VAO();

    // Связывает атрибут VBO (например, позицию или цвет) с VAO
    void LinkAttrib(
        VBO& VBO,              // Объект VBO
        GLuint layout,         // Номер атрибута в шейдере
        GLuint numComponents,  // Количество компонентов (например, 3 для vec3)
        GLenum type,           // Тип данных (например, GL_FLOAT)
        GLsizeiptr stride,     // Шаг между вершинами
        void* offset           // Смещение от начала данных
    );

    // Привязывает VAO
    void Bind();

    // Отвязывает VAO
    void Unbind();

    // Удаляет VAO
    void Delete();
};

#endif
