#include "VBO.h"

// �����������, ������� ������� ������ VBO (Vertex Buffer Object) � ��������� ��� � ���������
VBO::VBO(std::vector<Vertex>& vertices)
{
	// ���������� ���������� ������������� ��� VBO
	glGenBuffers(1, &ID);
	// ����������� VBO ��� ������� ����� ������
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	// ��������� ������ ������ � �����������
	// GL_STATIC_DRAW ���������, ��� ������ ����� �������������� ����� � ������ ��� ������
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
}

// ����������� VBO
void VBO::Bind()
{
	// ������������� VBO ������� ������� ��� ������ � ������� ������
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

// ���������� VBO
void VBO::Unbind()
{
	// ���������� ������� �����, ������������ ��������� ���������
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// ������� VBO
void VBO::Delete()
{
	// ������� ������ VBO �� ������ OpenGL
	glDeleteBuffers(1, &ID);
}
