#include "Texture.h"

// ����������� ������ Texture. ��������� �������� �� �����, ����������� ��������� OpenGL � ������� ������ ��������
Texture::Texture(const char* image, const char* texType, GLuint slot)
{
	// ����������� ��� �������� (��������, "diffuse" ��� "specular") ������� ��������
	type = texType;

	// ���������� ��� �������� ������, ������ � ���������� �������� ������� �����������
	int widthImg, heightImg, numColCh;
	// �������������� ����������� �� ���������, ����� ��� ������������ ���������
	stbi_set_flip_vertically_on_load(true);
	// ��������� ����������� �� ����� � ��������� ��� ������ � ������� ������
	unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);

	// ���������� ������ �������� OpenGL
	glGenTextures(1, &ID);
	// ���������� ���������� ���� � ����������� �������� � ���������������� �����
	glActiveTexture(GL_TEXTURE0 + slot);
	unit = slot;
	glBindTexture(GL_TEXTURE_2D, ID);

	// ����������� ��������� ��������������� �������� (��������� � �������� ������������)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// ����������� ����� ������� �������� (��������, ������ ��� ������� � �������)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// �������������� ��������� ��� GL_CLAMP_TO_BORDER (���� ���������)
	// float flatColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
	// glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, flatColor);

	// ���������� ������ �������� ������� �������� � ��������� ������ � OpenGL
	if (numColCh == 4) // RGBA (4 ������)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB_ALPHA, widthImg, heightImg, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
	else if (numColCh == 3) // RGB (3 ������)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB, widthImg, heightImg, 0, GL_RGB, GL_UNSIGNED_BYTE, bytes);
	else if (numColCh == 1) // ׸���-����� (1 �����)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB, widthImg, heightImg, 0, GL_RED, GL_UNSIGNED_BYTE, bytes);
	else
		throw std::invalid_argument("�������������� ����������� ������� �������� �� �������");

	// ���������� ������� ��� ��������
	glGenerateMipmap(GL_TEXTURE_2D);

	// ����������� ������, ������� ����������� ������������, ��� ��� ������ ��� �������� � OpenGL
	stbi_image_free(bytes);

	// ���������� ������ ��������, ����� ������������� ��������� ���������
	glBindTexture(GL_TEXTURE_2D, 0);
}

// ������������� ���������� ���� ��� �������
void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit)
{
	// �������� �������������� �������� � �������
	GLuint texUni = glGetUniformLocation(shader.ID, uniform);
	// ���������� ������ ����� ���������� �������� ��������
	shader.Activate();
	// ������������� �������� ��������
	glUniform1i(texUni, unit);
}

// ����������� �������� � �������� ��������� OpenGL
void Texture::Bind()
{
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, ID);
}

// ���������� �������� �� �������� ��������� OpenGL
void Texture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

// ������� ������ �������� �� ������ OpenGL
void Texture::Delete()
{
	glDeleteTextures(1, &ID);
}
