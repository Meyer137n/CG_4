#include "VBO.h"

// Конструктор, который создает объект VBO (Vertex Buffer Object) и связывает его с вершинами
VBO::VBO(std::vector<Vertex>& vertices)
{
	// Генерирует уникальный идентификатор для VBO
	glGenBuffers(1, &ID);
	// Привязывает VBO как текущий буфер вершин
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	// Загружает данные вершин в видеопамять
	// GL_STATIC_DRAW указывает, что данные будут использоваться редко и только для чтения
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
}

// Привязывает VBO
void VBO::Bind()
{
	// Устанавливает VBO текущим буфером для работы с данными вершин
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

// Отвязывает VBO
void VBO::Unbind()
{
	// Сбрасывает текущий буфер, предотвращая случайные изменения
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// Удаляет VBO
void VBO::Delete()
{
	// Удаляет объект VBO из памяти OpenGL
	glDeleteBuffers(1, &ID);
}
