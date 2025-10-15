#include <Windows.h>
#include <gl/GL.h>
#include <vector>
#include <iostream>

#include "core/GameObject/GameObject.hpp"
#include "config/WindowConfig.hpp"

std::vector<GameObject> gameObjects;

void initializeGameObjects() {
    gameObjects.push_back(GameObject(0.0f, 0.0f, 50, 50, "Player", "Main character", 1.0f, 0.0f, 0.0f));
    gameObjects.push_back(GameObject(-0.3f, 0.2f, 30, 30, "Enemy1", "First enemy", 0.0f, 1.0f, 0.0f));
    gameObjects.push_back(GameObject(0.4f, -0.1f, 40, 40, "Crate", "Wooden crate", 0.8f, 0.6f, 0.2f));
    gameObjects.push_back(GameObject(0.1f, 0.3f, 25, 25, "Coin", "Gold coin", 1.0f, 1.0f, 0.0f));
}

void drawAllGameObjects() {
    for (auto& obj : gameObjects) {
        obj.draw();
    }
}

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
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(0);
    wc.lpszClassName = "ChronoForge2D";
    wc.style = CS_OWNDC;

    RegisterClass(&wc);

    HWND window = CreateWindow(
        "ChronoForge2D",
        "ChronoForge2D - The simple 2D Game-Engine!",
        WS_OVERLAPPEDWINDOW,
        100, 100, WindowConfig["sizeX"], WindowConfig["sizeY"],
        NULL, NULL, GetModuleHandle(0), NULL
    );

    ShowWindow(window, SW_SHOW);

    HDC deviceContext = GetDC(window);

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
    glClearColor(0.2f, 0.3f, 0.5f, 1.0f);
    initializeGameObjects();

    MSG msg;
    bool running = true;

    while (running) {

        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) {
                running = false;
            }
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else {

            glClear(GL_COLOR_BUFFER_BIT);
            drawAllGameObjects();
            SwapBuffers(deviceContext);
        }
    }


    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(renderContext);
    ReleaseDC(window, deviceContext);
    DestroyWindow(window);

    return 0;
}