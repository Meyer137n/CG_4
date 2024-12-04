#version 330 core

// Выходной цвет фрагмента
out vec4 FragColor;
// Входящие текстурные координаты
in vec2 texCoords;

// Текстура экрана, передаваемая из основной программы
uniform sampler2D screenTexture;
// Параметр гаммы для коррекции
uniform float gamma;

void main()
{
    // Получение цвета из текстуры экрана
    vec4 fragment = texture(screenTexture, texCoords);
    // Применение гамма-коррекции к цвету фрагмента
    FragColor.rgb = pow(fragment.rgb, vec3(1.0f / gamma));
}
