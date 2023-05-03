#pragma warning(disable : 4996)
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <fstream>

using namespace std;

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    static double lastX = xpos, lastY = ypos;
    static bool isDragging = false;
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        if (!isDragging)
        {
            isDragging = true;
            lastX = xpos;
            lastY = ypos;
        }
        else
        {
            float deltaX = (float)(xpos - lastX) / 100.0f;
            float deltaY = (float)(ypos - lastY) / 100.0f;
            glTranslatef(deltaX, -deltaY, 0.0f);
            lastX = xpos;
            lastY = ypos;
        }
    }
    else
    {
        isDragging = false;
    }
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    float scaleFactor = 1.0f - yoffset * 0.1f;
    glScalef(scaleFactor, scaleFactor, scaleFactor);
}

void drawSerpinskyCemeteryQuadrilateral(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, int depth)
{
    if (depth == 0)
    {
        // ������ ������� �������
        glBegin(GL_QUADS);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        glVertex2f(x3, y3);
        glVertex2f(x4, y4);
        glVertex2f(x1, y1);
        glEnd();
    }
    else
    {
        // ��������� �������������� �� 9 �������������������
        // ���������� ����� x1 � x2 � ��� �� y1 � y2. � ���������� ����� �������� ���������� � ��������� ����������� �� ������� �� 3
        float subSize1_2_x = sqrt(pow(x2 - x1, 2)) / 3;
        float subSize1_2_y = sqrt(pow(y2 - y1, 2)) / 3;

        float subSize2_3_x = sqrt(pow(x3 - x2, 2)) / 3;
        float subSize2_3_y = sqrt(pow(y3 - y2, 2)) / 3;

        float subSize3_4_x = sqrt(pow(x4 - x3, 2)) / 3;
        float subSize3_4_y = sqrt(pow(y4 - y3, 2)) / 3;

        float subSize4_1_x = sqrt(pow(x1 - x4, 2)) / 3;
        float subSize4_1_y = sqrt(pow(y1 - y4, 2)) / 3;

        //float startX = x - size / 2;
        //float startY = y - size / 2;

        // ������ 4 ������� ���������������
        for (int i = 0; i < 9; ++i)
        {
            if (i == 3 || i == 4 || i == 5 || i == 7 || i == 1) {
                // �� ������ ���������������, ����������� � ����������
                continue;
            }
            else
            {
                // ���������� ������ ���������������
                if (i == 0) drawSerpinskyCemeteryQuadrilateral
                (x1, y1,
                    x1 + subSize1_2_x, y1,
                    x1 + subSize4_1_x + subSize1_2_x, y1 - subSize4_1_y,
                    x1 + subSize4_1_x, y1 - subSize4_1_y,
                    depth - 1);
                else if (i == 2) drawSerpinskyCemeteryQuadrilateral
                (x1 + (subSize1_2_x * 2), y1,
                    x2, y2,
                    x2 + subSize2_3_x, y2 - subSize4_1_y,
                    x1 + subSize4_1_x + (2 * subSize1_2_x), y1 - subSize4_1_y,
                    depth - 1);
                else if (i == 6) drawSerpinskyCemeteryQuadrilateral
                (x1 + (subSize4_1_x * 2), y1 - (subSize4_1_y * 2) ,
                    (x1 + subSize1_2_x) + (subSize4_1_x * 2), y1 - (subSize4_1_y * 2),
                    (x1 + subSize1_2_x) + (subSize4_1_x * 3), y1 - (subSize4_1_y * 3) - (subSize3_4_y),
                    x4, y4,
                    depth - 1);
                else if (i == 8) drawSerpinskyCemeteryQuadrilateral
                (x1 + (subSize1_2_x * 2) + (subSize4_1_x * 2), y1 - (subSize4_1_y * 2),
                    x1 + (subSize1_2_x * 3), y1 - (subSize4_1_y * 2),
                    x3, y3,
                    x1 + (subSize1_2_x * 2) + (subSize4_1_x * 3), y1 - ((subSize4_1_y * 3) + (subSize3_4_y * 2)),
                    depth - 1);
            }
        }
    }
}


void drawSerpinskyCemetery(float x, float y, float size, int depth) 
{
    if (depth == 0) 
    {
        // ������ ������� �������
        glBegin(GL_QUADS);
        glVertex2f(x - size / 2, y - size / 2);
        glVertex2f(x - size / 2, y + size / 2);
        glVertex2f(x + size / 2, y + size / 2);
        glVertex2f(x + size / 2, y - size / 2);
        glEnd();
    }
    else 
    {
        // ��������� ������� �� 9 ������������
        float subSize = size / 3;
        float startX = x - size / 2;
        float startY = y - size / 2;

        // ������ 4 ������� ��������
        for (int i = 0; i < 9; i++) 
        {
            if (i == 3 || i == 4 || i == 5 || i == 7 || i == 1) {
                // �� ������ ��������, ����������� � ����������
                continue;
            }
            else 
            {
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
    setlocale(LC_ALL, "Russian");
    /* ����� ������� ����������� ������� GLFW ���������� ������ ���� ����������������.
    ��� ������������� ���������, ����� ������� �������� �� ����������,
    ����������� �������� � ���������, �������������� ������ � ���������
    ����� ��������� �������������, ��������� �� ���������. */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context
    ���� � ��� �������� OpenGL ��� OpenGL ES ��������� � �������
    glfwCreateWindow, ������� ���������� ���������� ���������� ������� window.*/
    GLFWwindow* window = glfwCreateWindow(900, 900, "Fractal: Serpinsky cemetery 2", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwSetCursorPosCallback(window, cursor_position_callback);

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    int UserInput;
    bool UserChoice;
    cout << "����� �������������� ������ �� ������ ����� �� ������ �������� �������� ����������� 2?\n" <<
        "1. �������\n" << 
        "2. �������������� (��������� ������ ���������� �������)\n";
    cin >> UserInput;
    float x1, y1, x2, y2, x3, y3, x4, y4, iteration;
    if (UserInput == 1) {
        UserChoice = true;
        cout << "������� ����� ��������\n";
        cin >> iteration;
    }
    else if (UserInput == 2) {
        cout << "������� ����������:\nx1, y1, x2, y2, x3, y3, x4, y4\n";
        cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;
        cout << "������� ����� ��������\n";
        cin >> iteration;
        UserChoice = false;
    }

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);


        if (UserChoice) drawSerpinskyCemetery(0.0f, 0.0f, 1.0f, iteration);
        else {
            drawSerpinskyCemeteryQuadrilateral(x1, y1, x2, y2, x3, y3, x4, y4, iteration);
        }
            /*-0.75 0.75 0.75 0.75 0.75 -0.75 -0.5 -0.5 4*/

        // ������������� ������������� ������� ����
        glfwSetScrollCallback(window, scroll_callback);

        
        glfwSetCursorPosCallback(window, cursor_position_callback);

        // ��� ������� ������ ������� �������� � ������ �����
        glfwSwapBuffers(window);

        // ������������ ��� �������, ������������ � ���� - ����������� ���� ��� ������� ������
        glfwPollEvents();
    }

    // ����� ������� (R, G, B)
    int channels = 3;


    vector<unsigned char> pixels(900 * 900 * channels);

    // ��������� ���������� ������ �������� � ������ pixels
    glReadPixels(0, 0, 900, 900, GL_RGB, GL_UNSIGNED_BYTE, pixels.data());

    // ����������� ����������� (��� ��� OpenGL ������� ������ ����� ���� ������� ���������, � ����������� ������� ����������� - ������� �����)
    vector<unsigned char> inverted_pixels(900 * 900 * channels);


    for (int y = 0; y < 900; ++y) 
    {
        for (int x = 0; x < 900; ++x) 
        {
            for (int c = 0; c < channels; ++c) 
            {
                inverted_pixels[(900 - y - 1) * 900 * channels + x * channels + c] = pixels[y * 900 * channels + x * channels + c];
            }
        }
    }

    // ��������� ����������� � ������� JPEG �� ������� ����
    string filename = "C:\\Users\\Admin\\Desktop\\SerpinskiCemetery.jpg";

    int result = stbi_write_jpg(filename.c_str(), 900, 900, channels, inverted_pixels.data(), 100);

    if (result == 0) cout << "������ ���������� �����" << "\n";

    /*����� ����������� ������ ������ ���������� �� ������ ���������
    ������ ���������� GLFW, ���� ��� ���� ����������������.
    ��� �������� � ������� glfwTerminate.*/
    glfwTerminate();
    return 0;
}