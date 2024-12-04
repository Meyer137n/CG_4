#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include<glad/glad.h>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>

// Функция для чтения содержимого файла в строку
std::string get_file_contents(const char* filename);

class Shader
{
public:
    // Идентификатор программы шейдера
    GLuint ID;

    // Конструктор, создающий программу шейдера из вершинного и фрагментного шейдеров
    Shader(const char* vertexFile, const char* fragmentFile);
    // Перегруженный конструктор, включающий геометрический шейдер
    Shader(const char* vertexFile, const char* fragmentFile, const char* geometryFile);

    // Активирует программу шейдера
    void Activate();
    // Удаляет программу шейдера
    void Delete();

private:
    // Проверяет, успешно ли скомпилирован шейдер
    void compileErrors(unsigned int shader, const char* type);
};

#endif
