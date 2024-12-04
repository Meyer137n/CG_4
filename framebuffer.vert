#version 330 core

// Входные позиции вершин (x, y)
layout (location = 0) in vec2 inPos;
// Входные текстурные координаты
layout (location = 1) in vec2 inTexCoords;

// Выходные текстурные координаты для фрагментного шейдера
out vec2 texCoords;

void main()
{
    // Устанавливаем позицию вершины в пространстве экрана
    gl_Position = vec4(inPos.x, inPos.y, 0.0, 1.0); 
    // Передаем текстурные координаты во фрагментный шейдер
    texCoords = inTexCoords;
}
