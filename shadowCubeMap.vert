#version 330 core

// Входные позиции вершин
layout (location = 0) in vec3 aPos;

// Униформа матрицы модели
uniform mat4 model;

void main()
{
    // Преобразуем позицию вершины через матрицу модели
    gl_Position = model * vec4(aPos, 1.0);
}
