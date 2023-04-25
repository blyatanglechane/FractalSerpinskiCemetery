#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h> 
#include <GLFW/glfw3.h>

void drawSerpinskyCemetery(float x, float y, float size, int depth) {
    if (depth == 0) {
        // ������ ������� �������
        glBegin(GL_QUADS);
        glVertex2f(x - size / 2, y - size / 2);
        glVertex2f(x - size / 2, y + size / 2);
        glVertex2f(x + size / 2, y + size / 2);
        glVertex2f(x + size / 2, y - size / 2);
        glEnd();
    }
    else {
        // ��������� ������� �� 9 ������������
        float subSize = size / 3;
        float startX = x - size / 2;
        float startY = y - size / 2;

        // ������ 4 ������� ��������
        for (int i = 0; i < 9; i++) {
            if (i == 3 || i == 4 || i == 5 || i == 7 || i == 1) {
                // �� ������ ��������, ����������� � ����������
                continue;
            }
            else {
                // ���������� ������ ��������
                float subX = startX + subSize * (i % 3);
                float subY = startY + subSize * (i / 3);
                drawSerpinskyCemetery(subX + subSize / 2, subY + subSize / 2, subSize, depth - 1);
            }
        }
    }
}

int main(void)
{
    /* ����� ������� ����������� ������� GLFW ���������� ������ ���� ����������������. 
    ��� ������������� ���������, ����� ������� �������� �� ����������, 
    ����������� �������� � ���������, �������������� ������ � ��������� 
    ����� ��������� �������������, ��������� �� ���������. */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context 
    ���� � ��� �������� OpenGL ��� OpenGL ES ��������� � ������� 
    glfwCreateWindow, ������� ���������� ���������� ���������� ������� window.*/
    GLFWwindow* window = glfwCreateWindow(400, 400, "Fractal: Serpinsky cemetery 2", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        drawSerpinskyCemetery(0.0f, 0.0f, 2.0f, 5);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    /*����� ����������� ������ ������ ���������� �� ������ ��������� 
    ������ ���������� GLFW, ���� ��� ���� ����������������.
    ��� �������� � ������� glfwTerminate.*/
    glfwTerminate();
    return 0;
}