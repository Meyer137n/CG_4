#include "Texture.h"

// Конструктор класса Texture. Загружает текстуру из файла, настраивает параметры OpenGL и создает объект текстуры
Texture::Texture(const char* image, const char* texType, GLuint slot)
{
	// Присваивает тип текстуры (например, "diffuse" или "specular") объекту текстуры
	type = texType;

	// Переменные для хранения ширины, высоты и количества цветовых каналов изображения
	int widthImg, heightImg, numColCh;
	// Переворачивает изображение по вертикали, чтобы оно отображалось правильно
	stbi_set_flip_vertically_on_load(true);
	// Загружает изображение из файла и сохраняет его данные в массиве байтов
	unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);

	// Генерирует объект текстуры OpenGL
	glGenTextures(1, &ID);
	// Активирует текстурный юнит и привязывает текстуру к соответствующему слоту
	glActiveTexture(GL_TEXTURE0 + slot);
	unit = slot;
	glBindTexture(GL_TEXTURE_2D, ID);

	// Настраивает алгоритмы масштабирования текстуры (мипмапинг и линейная интерполяция)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Настраивает режим повтора текстуры (например, повтор или зажатие к границе)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Дополнительные настройки для GL_CLAMP_TO_BORDER (если требуется)
	// float flatColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
	// glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, flatColor);

	// Определяет формат цветовых каналов текстуры и загружает данные в OpenGL
	if (numColCh == 4) // RGBA (4 канала)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB_ALPHA, widthImg, heightImg, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
	else if (numColCh == 3) // RGB (3 канала)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB, widthImg, heightImg, 0, GL_RGB, GL_UNSIGNED_BYTE, bytes);
	else if (numColCh == 1) // Чёрно-белое (1 канал)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB, widthImg, heightImg, 0, GL_RED, GL_UNSIGNED_BYTE, bytes);
	else
		throw std::invalid_argument("Автоматическое определение формата текстуры не удалось");

	// Генерирует мипмапы для текстуры
	glGenerateMipmap(GL_TEXTURE_2D);

	// Освобождает память, занятую загруженным изображением, так как данные уже переданы в OpenGL
	stbi_image_free(bytes);

	// Отвязывает объект текстуры, чтобы предотвратить случайное изменение
	glBindTexture(GL_TEXTURE_2D, 0);
}

// Устанавливает текстурный юнит для шейдера
void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit)
{
	// Получает местоположение униформы в шейдере
	GLuint texUni = glGetUniformLocation(shader.ID, uniform);
	// Активирует шейдер перед изменением значения униформы
	shader.Activate();
	// Устанавливает значение униформы
	glUniform1i(texUni, unit);
}

// Привязывает текстуру к текущему контексту OpenGL
void Texture::Bind()
{
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, ID);
}

// Отвязывает текстуру из текущего контекста OpenGL
void Texture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

// Удаляет объект текстуры из памяти OpenGL
void Texture::Delete()
{
	glDeleteTextures(1, &ID);
}
