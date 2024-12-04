#include "Mesh.h"

// Конструктор класса Mesh, который инициализирует меш из вершин, индексов и текстур
Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, std::vector<Texture>& textures)
{
    // Сохраняем вершины, индексы и текстуры
    Mesh::vertices = vertices;
    Mesh::indices = indices;
    Mesh::textures = textures;

    // Привязываем VAO (Vertex Array Object)
    VAO.Bind();

    // Создаем VBO (Vertex Buffer Object) и связываем его с вершинами
    VBO VBO(vertices);
    // Создаем EBO (Element Buffer Object) и связываем его с индексами
    EBO EBO(indices);

    // Связываем атрибуты VBO (координаты, нормали, цвета, текстурные координаты) с VAO
    VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);                 // Позиция
    VAO.LinkAttrib(VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float))); // Нормаль
    VAO.LinkAttrib(VBO, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float))); // Цвет
    VAO.LinkAttrib(VBO, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)(9 * sizeof(float))); // Координаты текстуры

    // Отвязываем VAO, VBO и EBO, чтобы избежать случайных изменений
    VAO.Unbind();
    VBO.Unbind();
    EBO.Unbind();
}

// Метод для отрисовки меша
void Mesh::Draw(
    Shader& shader,
    Camera& camera,
    glm::mat4 matrix,
    glm::vec3 translation,
    glm::quat rotation,
    glm::vec3 scale
)
{
    // Активируем шейдер для работы с униформами
    shader.Activate();
    VAO.Bind();

    // Счетчики для диффузных и зеркальных текстур
    unsigned int numDiffuse = 0;
    unsigned int numSpecular = 0;

    // Привязываем текстуры и назначаем их юниты
    for (unsigned int i = 0; i < textures.size(); i++)
    {
        std::string num;
        std::string type = textures[i].type;
        if (type == "diffuse")
        {
            num = std::to_string(numDiffuse++); // Счетчик для диффузных текстур
        }
        else if (type == "specular")
        {
            num = std::to_string(numSpecular++); // Счетчик для зеркальных текстур
        }
        // Назначаем текстурный юнит шейдеру
        textures[i].texUnit(shader, (type + num).c_str(), i);
        textures[i].Bind();
    }

    // Передаем позицию камеры в шейдер
    glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
    // Передаем матрицу камеры в шейдер
    camera.Matrix(shader, "camMatrix");

    // Инициализация матриц трансформаций
    glm::mat4 trans = glm::mat4(1.0f);
    glm::mat4 rot = glm::mat4(1.0f);
    glm::mat4 sca = glm::mat4(1.0f);

    // Применяем трансформации: перенос, вращение и масштаб
    trans = glm::translate(trans, translation); // Перенос
    rot = glm::mat4_cast(rotation);             // Вращение (из кватерниона)
    sca = glm::scale(sca, scale);               // Масштаб

    // Передаем матрицы трансформаций в вершинный шейдер
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "translation"), 1, GL_FALSE, glm::value_ptr(trans));
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "rotation"), 1, GL_FALSE, glm::value_ptr(rot));
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "scale"), 1, GL_FALSE, glm::value_ptr(sca));
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(matrix));

    // Рисуем меш, используя индексы
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}
