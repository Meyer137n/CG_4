#include "VAO.h"

// �����������, ������� ���������� ID ��� VAO (Vertex Array Object)
VAO::VAO()
{
	glGenVertexArrays(1, &ID); // �������� ������� VAO � ���������� ��� ����������� ��������������
}

// ��������� ������� VBO (��������, ������� ��� ����) � VAO
void VAO::LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset)
{
	// ����������� VBO (Vertex Buffer Object)
	VBO.Bind();
	// ����������, ��� ������ �� VBO ������ ���� ���������������� (��������, ���������� ������, ����� � �. �.)
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
	// �������� ������� ������� ������ ��� �������������
	glEnableVertexAttribArray(layout);
	// ���������� VBO, ����� �������� ��������� ���������
	VBO.Unbind();
}

// ����������� VAO
void VAO::Bind()
{
	glBindVertexArray(ID); // �������� VAO � �������� ��������� OpenGL
}

// ���������� VAO
void VAO::Unbind()
{
	glBindVertexArray(0); // ���������� �������� VAO, ����� ������������� ��������� ���������
}

// ������� VAO
void VAO::Delete()
{
	glDeleteVertexArrays(1, &ID); // ������� ������ VAO �� ������ OpenGL
}
