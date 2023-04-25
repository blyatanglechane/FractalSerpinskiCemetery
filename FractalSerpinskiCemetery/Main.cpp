#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h> 
#include <GLFW/glfw3.h>

void drawSerpinskyCemetery(float x, float y, float size, int depth) {
    if (depth == 0) {
        // Рисуем средний квадрат
        glBegin(GL_QUADS);
        glVertex2f(x - size / 2, y - size / 2);
        glVertex2f(x - size / 2, y + size / 2);
        glVertex2f(x + size / 2, y + size / 2);
        glVertex2f(x + size / 2, y - size / 2);
        glEnd();
    }
    else {
        // Разделяем квадрат на 9 подквадратов
        float subSize = size / 3;
        float startX = x - size / 2;
        float startY = y - size / 2;

        // Рисуем 4 угловых квадрата
        for (int i = 0; i < 9; i++) {
            if (i == 3 || i == 4 || i == 5 || i == 7 || i == 1) {
                // Не рисуем квадраты, находящихся в крестовине
                continue;
            }
            else {
                // Рекурсивно рисуем квадраты
                float subX = startX + subSize * (i % 3);
                float subY = startY + subSize * (i / 3);
                drawSerpinskyCemetery(subX + subSize / 2, subY + subSize / 2, subSize, depth - 1);
            }
        }
    }
}

int main(void)
{
    /* Перед вызовом большинства функций GLFW библиотека должна быть инициализирована. 
    Эта инициализация проверяет, какие функции доступны на компьютере, 
    перечисляет мониторы и джойстики, инициализирует таймер и выполняет 
    любую требуемую инициализацию, зависящую от платформы. */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context 
    Окно и его контекст OpenGL или OpenGL ES создаются с помощью 
    glfwCreateWindow, который возвращает дескриптор созданного объекта window.*/
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

    /*Перед завершением работы вашего приложения вы должны завершить 
    работу библиотеки GLFW, если она была инициализирована.
    Это делается с помощью glfwTerminate.*/
    glfwTerminate();
    return 0;
}