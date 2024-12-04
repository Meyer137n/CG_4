#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include<glad/glad.h>
#include"VBO.h"

// ����� ��� ������ � �������� ������� ������ (VAO)
class VAO
{
public:
    // ������������� ������� ������� ������
    GLuint ID;

    // �����������, ������������ ID ��� VAO
    VAO();

    // ��������� ������� VBO (��������, ������� ��� ����) � VAO
    void LinkAttrib(
        VBO& VBO,              // ������ VBO
        GLuint layout,         // ����� �������� � �������
        GLuint numComponents,  // ���������� ����������� (��������, 3 ��� vec3)
        GLenum type,           // ��� ������ (��������, GL_FLOAT)
        GLsizeiptr stride,     // ��� ����� ���������
        void* offset           // �������� �� ������ ������
    );

    // ����������� VAO
    void Bind();

    // ���������� VAO
    void Unbind();

    // ������� VAO
    void Delete();
};

#endif
