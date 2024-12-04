#ifndef MESH_CLASS_H
#define MESH_CLASS_H

#include<string>
#include"VAO.h"
#include"EBO.h"
#include"Camera.h"
#include"Texture.h"

// Класс для работы с 3D-мешами
class Mesh
{
public:
    // Вершины, индексы и текстуры меша
    std::vector<Vertex> vertices;    // Вектор вершин
    std::vector<GLuint> indices;     // Вектор индексов
    std::vector<Texture> textures;   // Вектор текстур

    // Объект VAO (Vertex Array Object) для хранения состояния вершинного массива
    VAO VAO;

    // Конструктор, инициализирующий меш
    Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, std::vector<Texture>& textures);

    // Отрисовывает меш
    void Draw
    (
        Shader& shader,                 // Шейдер для отрисовки
        Camera& camera,                 // Камера для получения матрицы вида
        glm::mat4 matrix = glm::mat4(1.0f),        // Дополнительная трансформационная матрица
        glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f), // Вектор переноса
        glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f), // Кватернион вращения
        glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f)  // Вектор масштаба
    );
};

#endif
