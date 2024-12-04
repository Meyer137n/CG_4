#include "Camera.h"

// ����������� ������, �������� ������� ���� � ��������� �������
Camera::Camera(int width, int height, glm::vec3 position)
{
    Camera::width = width;
    Camera::height = height;
    Position = position;
}

// ��������� ������� ������ (������� ���� � ��������)
void Camera::updateMatrix(float FOVdeg, float nearPlane, float farPlane)
{
    // ������������� ������ (���������� ��������� �������)
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);

    // ����������� ��� (������ ������� � ����������� Orientation)
    view = glm::lookAt(Position, Position + Orientation, Up);
    // ��������� ����������� � �����
    projection = glm::perspective(glm::radians(FOVdeg), (float)width / height, nearPlane, farPlane);

    // ������������� ����� ������� ������
    cameraMatrix = projection * view;
}

// �������� ������� ������ � ������
void Camera::Matrix(Shader& shader, const char* uniform)
{
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(cameraMatrix));
}

// ������������ ���� � ���������� � ���� ��� ���������� �������
void Camera::Inputs(GLFWwindow* window)
{
    // ����������� ��� �������� ������
    float limitx = 40.0f;
    float limitz = 58.0f;
    float limit_ymax = 34.0f;
    float limit_ymin = 8.0f;

    // ����������� ������ ������
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        glm::vec3 newPos = Position + speed * Orientation;
        if (abs(newPos.x) <= limitx && newPos.y <= limit_ymax && newPos.y >= limit_ymin && abs(newPos.z) <= limitz)
            Position = newPos;
    }
    // ����������� ������ �����
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        glm::vec3 newPos = Position + speed * -glm::normalize(glm::cross(Orientation, Up));
        if (abs(newPos.x) <= limitx && newPos.y <= limit_ymax && newPos.y >= limit_ymin && abs(newPos.z) <= limitz)
            Position = newPos;
    }
    // ����������� ������ �����
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        glm::vec3 newPos = Position + speed * -Orientation;
        if (abs(newPos.x) <= limitx && newPos.y <= limit_ymax && newPos.y >= limit_ymin && abs(newPos.z) <= limitz)
            Position = newPos;
    }
    // ����������� ������ ������
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        glm::vec3 newPos = Position + speed * glm::normalize(glm::cross(Orientation, Up));
        if (abs(newPos.x) <= limitx && newPos.y <= limit_ymax && newPos.y >= limit_ymin && abs(newPos.z) <= limitz)
            Position = newPos;
    }
    // ����������� ������ �����
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        glm::vec3 newPos = Position + speed * Up;
        if (abs(newPos.x) <= limitx && newPos.y <= limit_ymax && newPos.y >= limit_ymin && abs(newPos.z) <= limitz)
            Position = newPos;
    }
    // ����������� ������ ����
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
    {
        glm::vec3 newPos = Position + speed * -Up;
        if (abs(newPos.x) <= limitx && newPos.y <= limit_ymax && newPos.y >= limit_ymin && abs(newPos.z) <= limitz)
            Position = newPos;
    }

    // ���������� �������� ��� ������� SHIFT
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    {
        speed = 1.0f;
    }
    else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
    {
        speed = 0.2f;
    }

    // ��������� ����� ���� ��� ���������� �������
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        // �������� ������
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

        // ������������� ������ ������ ��� ������ �����
        if (firstClick)
        {
            glfwSetCursorPos(window, (width / 2), (height / 2));
            firstClick = false;
        }

        // �������� ���������� �������
        double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);

        // ��������� ��������� � ����������� �� ������ ��������� �������
        float rotX = sensitivity * (float)(mouseY - (height / 2)) / height;
        float rotY = sensitivity * (float)(mouseX - (width / 2)) / width;

        // ��������� ����� ����������� (����������)
        glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(-rotX), glm::normalize(glm::cross(Orientation, Up)));

        // ���������, �� ������� �� ���������� �� ������� ������������� ����
        if (abs(glm::angle(newOrientation, Up) - glm::radians(90.0f)) <= glm::radians(85.0f))
        {
            Orientation = newOrientation;
        }

        // �������� ������ �����/������
        Orientation = glm::rotate(Orientation, glm::radians(-rotY), Up);

        // ���������� ������ � ����� ������
        glfwSetCursorPos(window, (width / 2), (height / 2));
    }
    else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
    {
        // ���������� ������
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        // ���������� ���� ������� �����
        firstClick = true;
    }
}
