#include <Windows.h>
#include <gl/GL.h>
#include <vector>
#include <iostream>

#include "core/GameObject/GameObject.hpp"

std::vector<GameObject> gameObjects;

// Функция для инициализации игровых объектов
void initializeGameObjects() {
    // Создаем несколько тестовых объектов
    gameObjects.push_back(GameObject(0.0f, 0.0f, 50, 50, "Player", "Main character", 1.0f, 0.0f, 0.0f));
    gameObjects.push_back(GameObject(-0.3f, 0.2f, 30, 30, "Enemy1", "First enemy", 0.0f, 1.0f, 0.0f));
    gameObjects.push_back(GameObject(0.4f, -0.1f, 40, 40, "Crate", "Wooden crate", 0.8f, 0.6f, 0.2f));
    gameObjects.push_back(GameObject(0.1f, 0.3f, 25, 25, "Coin", "Gold coin", 1.0f, 1.0f, 0.0f));
}

// Функция для отрисовки всех игровых объектов
void drawAllGameObjects() {
    for (auto& obj : gameObjects) {
        obj.draw();
    }
}

// Функция для обработки событий окна
LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_KEYDOWN:
        if (wParam == VK_ESCAPE) {
            PostQuitMessage(0);
        }
        break;
    case WM_CLOSE:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int main() {
    // 1. Регистрируем класс окна
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(0);
    wc.lpszClassName = "ChronoForge2D";
    wc.style = CS_OWNDC;

    RegisterClass(&wc);

    // 2. Создаем окно
    HWND window = CreateWindow(
        "ChronoForge2D",
        "ChronoForge2D - The simple 2D Game-Engine!",
        WS_OVERLAPPEDWINDOW,
        100, 100, 1280, 720,
        NULL, NULL, GetModuleHandle(0), NULL
    );

    ShowWindow(window, SW_SHOW);

    // 3. Настраиваем OpenGL
    HDC deviceContext = GetDC(window);

    // Описываем формат пикселей
    PIXELFORMATDESCRIPTOR pfd = {
        sizeof(PIXELFORMATDESCRIPTOR),
        1,
        PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
        PFD_TYPE_RGBA,
        32,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        24,
        8,
        0, 0, 0, 0, 0, 0
    };

    int format = ChoosePixelFormat(deviceContext, &pfd);
    SetPixelFormat(deviceContext, format, &pfd);

    HGLRC renderContext = wglCreateContext(deviceContext);
    wglMakeCurrent(deviceContext, renderContext);

    // Устанавливаем синий цвет фона
    glClearColor(0.2f, 0.3f, 0.5f, 1.0f);

    // Инициализируем игровые объекты
    initializeGameObjects();

    // 4. Главный цикл программы
    MSG msg;
    bool running = true;

    while (running) {
        // Обрабатываем сообщения Windows
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) {
                running = false;
            }
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else {
            // Очищаем экран
            glClear(GL_COLOR_BUFFER_BIT);

            // Рисуем все игровые объекты
            drawAllGameObjects();

            // Показываем нарисованное
            SwapBuffers(deviceContext);
        }
    }

    // 5. Очистка ресурсов
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(renderContext);
    ReleaseDC(window, deviceContext);
    DestroyWindow(window);

    return 0;
}