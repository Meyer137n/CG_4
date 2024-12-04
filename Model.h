#ifndef MODEL_CLASS_H
#define MODEL_CLASS_H

#include<json/json.h>
#include"Mesh.h"

using json = nlohmann::json;

// Класс для работы с 3D-моделями
class Model
{
public:
    // Загружает модель из файла и сохраняет данные в 'data', 'JSON' и 'file'
    Model(const char* file);

    // Отрисовывает модель
    void Draw(Shader& shader, Camera& camera);

private:
    // Переменные для доступа к данным модели
    const char* file;                 // Имя файла
    std::vector<unsigned char> data;  // Данные модели в бинарном виде
    json JSON;                        // JSON-структура с описанием модели

    // Все меши и их трансформации
    std::vector<Mesh> meshes;         // Список мешей
    std::vector<glm::vec3> translationsMeshes; // Список векторов переноса для мешей
    std::vector<glm::quat> rotationsMeshes;    // Список кватернионов вращения для мешей
    std::vector<glm::vec3> scalesMeshes;       // Список векторов масштаба для мешей
    std::vector<glm::mat4> matricesMeshes;     // Список трансформационных матриц для мешей

    // Список загруженных текстур (для предотвращения повторной загрузки)
    std::vector<std::string> loadedTexName;    // Имена загруженных текстур
    std::vector<Texture> loadedTex;           // Сами текстуры

    // Загружает отдельный меш по его индексу
    void loadMesh(unsigned int indMesh);

    // Рекурсивно обходит узлы, чтобы обработать все связанные узлы
    void traverseNode(unsigned int nextNode, glm::mat4 matrix = glm::mat4(1.0f));

    // Извлекает бинарные данные из файла
    std::vector<unsigned char> getData();

    // Интерпретирует бинарные данные в числа с плавающей запятой, индексы и текстуры
    std::vector<float> getFloats(json accessor);
    std::vector<GLuint> getIndices(json accessor);
    std::vector<Texture> getTextures();

    // Собирает все данные вершин в структуру Vertex
    std::vector<Vertex> assembleVertices
    (
        std::vector<glm::vec3> positions,  // Позиции вершин
        std::vector<glm::vec3> normals,    // Нормали
        std::vector<glm::vec2> texUVs      // Координаты текстур
    );

    // Помогает сгруппировать числа с плавающей запятой в векторы нужного размера
    std::vector<glm::vec2> groupFloatsVec2(std::vector<float> floatVec); // Группировка в vec2
    std::vector<glm::vec3> groupFloatsVec3(std::vector<float> floatVec); // Группировка в vec3
    std::vector<glm::vec4> groupFloatsVec4(std::vector<float> floatVec); // Группировка в vec4
};

#endif
