#version 330 core

// ������� ������� ��������� � ������� ������������
in vec4 FragPos;

// ������� ��������� �����
uniform vec3 lightPos;
// �������� �������� ����� (farPlane) ��� ������������ �������
uniform float farPlane;

void main()
{
    // ������������� �������� ������� ������� � ��������� [0, 1]
    gl_FragDepth = length(FragPos.xyz - lightPos) / farPlane;
}
