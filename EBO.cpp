#include "EBO.h"

// ����������� ������ Mesh, ������� �������������� ��� �� ������, �������� � �������
EBO::EBO(std::vector<GLuint>& indices)
{
    // ��������� �������������� ������
    glGenBuffers(1, &ID);
    // �������� ������ � �������� ������� ���������
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
    // ����������� ������ �������� � �����
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
}

// ����������� ������ EBO
void EBO::Bind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

// ���������� ������ EBO
void EBO::Unbind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

// ������� ������ EBO
void EBO::Delete()
{
    glDeleteBuffers(1, &ID);
}
