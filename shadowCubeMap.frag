#version 330 core

// Входная позиция фрагмента в мировом пространстве
in vec4 FragPos;

// Позиция источника света
uniform vec3 lightPos;
// Значение дальнего плана (farPlane) для нормализации глубины
uniform float farPlane;

void main()
{
    // Устанавливаем значение глубины вручную в диапазоне [0, 1]
    gl_FragDepth = length(FragPos.xyz - lightPos) / farPlane;
}
