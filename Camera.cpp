#include "Camera.h"

// Конструктор камеры, задающий размеры окна и начальную позицию
Camera::Camera(int width, int height, glm::vec3 position)
{
    Camera::width = width;
    Camera::height = height;
    Position = position;
}

// Обновляет матрицу камеры (матрицу вида и проекции)
void Camera::updateMatrix(float FOVdeg, float nearPlane, float farPlane)
{
    // Инициализация матриц (изначально единичная матрица)
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);

    // Настраивает вид (камера смотрит в направлении Orientation)
    view = glm::lookAt(Position, Position + Orientation, Up);
    // Добавляет перспективу к сцене
    projection = glm::perspective(glm::radians(FOVdeg), (float)width / height, nearPlane, farPlane);

    // Устанавливает новую матрицу камеры
    cameraMatrix = projection * view;
}

// Передает матрицу камеры в шейдер
void Camera::Matrix(Shader& shader, const char* uniform)
{
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(cameraMatrix));
}

// Обрабатывает ввод с клавиатуры и мыши для управления камерой
void Camera::Inputs(GLFWwindow* window)
{
    // Ограничения для движения камеры
    float limitx = 40.0f;
    float limitz = 58.0f;
    float limit_ymax = 34.0f;
    float limit_ymin = 8.0f;

    // Перемещение камеры вперед
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        glm::vec3 newPos = Position + speed * Orientation;
        if (abs(newPos.x) <= limitx && newPos.y <= limit_ymax && newPos.y >= limit_ymin && abs(newPos.z) <= limitz)
            Position = newPos;
    }
    // Перемещение камеры влево
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        glm::vec3 newPos = Position + speed * -glm::normalize(glm::cross(Orientation, Up));
        if (abs(newPos.x) <= limitx && newPos.y <= limit_ymax && newPos.y >= limit_ymin && abs(newPos.z) <= limitz)
            Position = newPos;
    }
    // Перемещение камеры назад
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        glm::vec3 newPos = Position + speed * -Orientation;
        if (abs(newPos.x) <= limitx && newPos.y <= limit_ymax && newPos.y >= limit_ymin && abs(newPos.z) <= limitz)
            Position = newPos;
    }
    // Перемещение камеры вправо
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        glm::vec3 newPos = Position + speed * glm::normalize(glm::cross(Orientation, Up));
        if (abs(newPos.x) <= limitx && newPos.y <= limit_ymax && newPos.y >= limit_ymin && abs(newPos.z) <= limitz)
            Position = newPos;
    }
    // Перемещение камеры вверх
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        glm::vec3 newPos = Position + speed * Up;
        if (abs(newPos.x) <= limitx && newPos.y <= limit_ymax && newPos.y >= limit_ymin && abs(newPos.z) <= limitz)
            Position = newPos;
    }
    // Перемещение камеры вниз
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
    {
        glm::vec3 newPos = Position + speed * -Up;
        if (abs(newPos.x) <= limitx && newPos.y <= limit_ymax && newPos.y >= limit_ymin && abs(newPos.z) <= limitz)
            Position = newPos;
    }

    // Увеличение скорости при зажатии SHIFT
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    {
        speed = 1.0f;
    }
    else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
    {
        speed = 0.2f;
    }

    // Обработка ввода мыши для управления камерой
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        // Скрывает курсор
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

        // Предотвращает скачки камеры при первом клике
        if (firstClick)
        {
            glfwSetCursorPos(window, (width / 2), (height / 2));
            firstClick = false;
        }

        // Получает координаты курсора
        double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);

        // Вычисляет изменения в направлении на основе положения курсора
        float rotX = sensitivity * (float)(mouseY - (height / 2)) / height;
        float rotY = sensitivity * (float)(mouseX - (width / 2)) / width;

        // Вычисляет новое направление (ориентацию)
        glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(-rotX), glm::normalize(glm::cross(Orientation, Up)));

        // Проверяет, не выходит ли ориентация за пределы вертикального угла
        if (abs(glm::angle(newOrientation, Up) - glm::radians(90.0f)) <= glm::radians(85.0f))
        {
            Orientation = newOrientation;
        }

        // Вращение камеры влево/вправо
        Orientation = glm::rotate(Orientation, glm::radians(-rotY), Up);

        // Сбрасывает курсор в центр экрана
        glfwSetCursorPos(window, (width / 2), (height / 2));
    }
    else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
    {
        // Показывает курсор
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        // Сбрасывает флаг первого клика
        firstClick = true;
    }
}
