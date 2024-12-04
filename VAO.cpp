#include "VAO.h"

// Конструктор, который генерирует ID для VAO (Vertex Array Object)
VAO::VAO()
{
	glGenVertexArrays(1, &ID); // Создание объекта VAO и присвоение ему уникального идентификатора
}

// Связывает атрибут VBO (например, позицию или цвет) с VAO
void VAO::LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset)
{
	// Привязывает VBO (Vertex Buffer Object)
	VBO.Bind();
	// Определяет, как данные из VBO должны быть интерпретированы (например, координаты вершин, цвета и т. д.)
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
	// Включает атрибут массива вершин для использования
	glEnableVertexAttribArray(layout);
	// Отвязывает VBO, чтобы избежать случайных изменений
	VBO.Unbind();
}

// Привязывает VAO
void VAO::Bind()
{
	glBindVertexArray(ID); // Привязка VAO к текущему контексту OpenGL
}

// Отвязывает VAO
void VAO::Unbind()
{
	glBindVertexArray(0); // Сбрасывает привязку VAO, чтобы предотвратить случайные изменения
}

// Удаляет VAO
void VAO::Delete()
{
	glDeleteVertexArrays(1, &ID); // Удаляет объект VAO из памяти OpenGL
}
