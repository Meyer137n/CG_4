#version 330 core

// Позиции/координаты
layout (location = 0) in vec3 aPos;
// Нормали (не обязательно нормализованы)
layout (location = 1) in vec3 aNormal;
// Цвета
layout (location = 2) in vec3 aColor;
// Текстурные координаты
layout (location = 3) in vec2 aTex;

// Передача текущей позиции для фрагментного шейдера
out vec3 crntPos;
// Передача нормали для фрагментного шейдера
out vec3 Normal;
// Передача цвета для фрагментного шейдера
out vec3 color;
// Передача текстурных координат для фрагментного шейдера
out vec2 texCoord;
// Передача позиции фрагмента относительно света для фрагментного шейдера
out vec4 fragPosLight;

// Импорт матрицы камеры
uniform mat4 camMatrix;
// Импорт матриц трансформации
uniform mat4 model;
uniform mat4 translation;
uniform mat4 rotation;
uniform mat4 scale;
// Импорт матрицы света
uniform mat4 lightProjection;

void main()
{
	// Вычисление текущей позиции
	crntPos = vec3(model * translation * rotation * scale * vec4(aPos, 1.0f));
	// Присвоение нормалей из данных вершин в переменную "Normal"
	Normal = aNormal;
	// Присвоение цвета из данных вершин в переменную "color"
	color = aColor;
	// Присвоение текстурных координат из данных вершин в переменную "texCoord"
	texCoord = mat2(0.0, -1.0, 1.0, 0.0) * aTex;
	// Вычисление позиции фрагмента относительно света для фрагментного шейдера
	fragPosLight = lightProjection * vec4(crntPos, 1.0f);
	
	// Передача позиции/координат всех вершин
	gl_Position = camMatrix * vec4(crntPos, 1.0);
}
