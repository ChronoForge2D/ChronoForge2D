#include <Windows.h>
#include <gl/GL.h>

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
        100, 100, 800, 600,
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
        32, // бит на пиксель
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        24, // буфер глубины
        8,  // буфер трафарета
        0, 0, 0, 0, 0, 0
    };

    int format = ChoosePixelFormat(deviceContext, &pfd);
    SetPixelFormat(deviceContext, format, &pfd);

    HGLRC renderContext = wglCreateContext(deviceContext);
    wglMakeCurrent(deviceContext, renderContext);

    // Устанавливаем синий цвет фона
    glClearColor(0.0f, 0.5f, 1.0f, 1.0f);

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

            // Рисуем красный треугольник
            glBegin(GL_TRIANGLES);
            glColor3f(1.0f, 0.0f, 0.0f);  // Красный цвет
            glVertex2f(0.0f, 0.5f);       // Верхняя вершина
            glVertex2f(-0.5f, -0.5f);     // Левая нижняя
            glVertex2f(0.5f, -0.5f);      // Правая нижняя
            glEnd();

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