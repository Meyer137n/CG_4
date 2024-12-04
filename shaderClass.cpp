#include "shaderClass.h"

// Читает текстовый файл и возвращает строку с его содержимым
std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

// Конструктор, создающий шейдерную программу из двух шейдеров
Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	// Чтение файлов вершинного и фрагментного шейдеров и сохранение их содержимого в строках
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	// Преобразование строк с кодом шейдеров в массивы символов
	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	// Создание объекта вершинного шейдера и получение его ссылки
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// Прикрепление исходного кода вершинного шейдера к объекту шейдера
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	// Компиляция вершинного шейдера в машинный код
	glCompileShader(vertexShader);
	// Проверка успешной компиляции шейдера
	compileErrors(vertexShader, "VERTEX");

	// Создание объекта фрагментного шейдера и получение его ссылки
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// Прикрепление исходного кода фрагментного шейдера к объекту шейдера
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	// Компиляция фрагментного шейдера в машинный код
	glCompileShader(fragmentShader);
	// Проверка успешной компиляции шейдера
	compileErrors(fragmentShader, "FRAGMENT");

	// Создание объекта программы шейдеров и получение его ссылки
	ID = glCreateProgram();
	// Прикрепление вершинного и фрагментного шейдеров к программе
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	// Завершение/связывание всех шейдеров в одну шейдерную программу
	glLinkProgram(ID);
	// Проверка успешного связывания шейдеров
	compileErrors(ID, "PROGRAM");

	// Удаление ненужных объектов вершинного и фрагментного шейдеров
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

// Конструктор, создающий шейдерную программу с геометрическим шейдером
Shader::Shader(const char* vertexFile, const char* fragmentFile, const char* geometryFile)
{
	// Чтение файлов вершинного, фрагментного и геометрического шейдеров
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);
	std::string geometryCode = get_file_contents(geometryFile);

	// Преобразование строк с кодом шейдеров в массивы символов
	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();
	const char* geometrySource = geometryCode.c_str();

	// Создание и компиляция вершинного шейдера
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);
	compileErrors(vertexShader, "VERTEX");

	// Создание и компиляция фрагментного шейдера
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);
	compileErrors(fragmentShader, "FRAGMENT");

	// Создание и компиляция геометрического шейдера
	GLuint geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
	glShaderSource(geometryShader, 1, &geometrySource, NULL);
	glCompileShader(geometryShader);
	compileErrors(geometryShader, "GEOMETRY");

	// Создание объекта программы шейдеров
	ID = glCreateProgram();
	// Прикрепление всех шейдеров к программе
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glAttachShader(ID, geometryShader);
	// Связывание всех шейдеров в одну программу
	glLinkProgram(ID);
	// Проверка успешного связывания шейдеров
	compileErrors(ID, "PROGRAM");

	// Удаление ненужных объектов шейдеров
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glDeleteShader(geometryShader);
}

// Активирует шейдерную программу
void Shader::Activate()
{
	glUseProgram(ID);
}

// Удаляет шейдерную программу
void Shader::Delete()
{
	glDeleteProgram(ID);
}

// Проверяет успешность компиляции и связывания шейдеров
void Shader::compileErrors(unsigned int shader, const char* type)
{
	GLint hasCompiled; // Хранит статус компиляции
	char infoLog[1024]; // Массив для хранения сообщения об ошибке
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "Ошибка компиляции шейдера (" << type << "):\n" << infoLog << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "Ошибка связывания программы шейдеров (" << type << "):\n" << infoLog << std::endl;
		}
	}
}
