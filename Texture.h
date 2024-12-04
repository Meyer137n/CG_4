#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include<glad/glad.h>
#include<stb/stb_image.h>
#include"shaderClass.h"

// Класс для работы с текстурами
class Texture
{
public:
    GLuint ID;              // Идентификатор текстуры
    const char* type;       // Тип текстуры (например, "diffuse" или "specular")
    GLuint unit;            // Текстурный слот (unit)

    // Конструктор, загружающий текстуру из файла
    Texture(const char* image, const char* texType, GLuint slot);

    // Привязывает текстуру к текстурному юниту в шейдере
    void texUnit(Shader& shader, const char* uniform, GLuint unit);

    // Активирует и привязывает текстуру
    void Bind();

    // Отвязывает текстуру
    void Unbind();

    // Удаляет текстуру
    void Delete();
};

#endif
