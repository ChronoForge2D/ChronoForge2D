#include <Windows.h>
#include <gl/GL.h>
#include <vector>
#include <iostream>
#include <algorithm> // для удаления объектов

#include "core/GameObject/GameObject.hpp"
#include "config/WindowConfig.hpp"

// Объявляем глобальный массив для управления объектами
extern std::vector<GameObject*> gameObjects;

void initializeTestGameObjects() {
    // Объекты автоматом добавляются в gameObjects при создании
    new GameObject(0.0f, 0.0f, 50, 50, "Player", "Main character", 1.0f, 0.0f, 0.0f);
    new GameObject(-0.3f, 0.2f, 30, 30, "Enemy1", "First enemy", 0.0f, 1.0f, 0.0f);
    new GameObject(0.4f, -0.1f, 40, 40, "Crate", "Wooden crate", 0.8f, 0.6f, 0.2f);
    new GameObject(0.1f, 0.3f, 25, 25, "Coin", "Gold coin", 1.0f, 1.0f, 0.0f);
}

void drawAllGameObjects() {
    for (auto& obj : gameObjects) {
        obj->draw(); // используем указатели -> вместо .
    }
}

// ФУНКЦИИ ДЛЯ УПРАВЛЕНИЯ ОБЪЕКТАМИ:

// Найти объект по имени
GameObject* findObjectByName(const std::string& name) {
    for (auto obj : gameObjects) {
        if (obj->getName() == name) {
            return obj;
        }
    }
    return nullptr;
}

// Удалить объект по имени
void deleteObjectByName(const std::string& name) {
    gameObjects.erase(
        std::remove_if(gameObjects.begin(), gameObjects.end(),
            [&name](GameObject* obj) {
                if (obj->getName() == name) {
                    delete obj; // освобождаем память
                    return true;
                }
                return false;
            }),
        gameObjects.end()
    );
}

// Получить все объекты определенного типа
std::vector<GameObject*> getObjectsByDescription(const std::string& desc) {
    std::vector<GameObject*> result;
    for (auto obj : gameObjects) {
        if (obj->getDescription() == desc) {
            result.push_back(obj);
        }
    }
    return result;
}

// Показать все объекты в консоли (для отладки)
void showAllObjects() {
    std::cout << "=== All Game Objects ===" << std::endl;
    for (auto obj : gameObjects) {
        std::cout << "Name: " << obj->getName()
            << ", Desc: " << obj->getDescription()
            << ", Position: (" << obj->getPosition().first
            << ", " << obj->getPosition().second << ")" << std::endl;
    }
    std::cout << "Total objects: " << gameObjects.size() << std::endl;
}

// Очистить все объекты
void clearAllGameObjects() {
    for (auto obj : gameObjects) {
        delete obj;
    }
    gameObjects.clear();
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_KEYDOWN:
        if (wParam == VK_ESCAPE) {
            PostQuitMessage(0);
        }
        // Добавляем управление объектами с клавиатуры
        else if (wParam == 'P') {
            // При нажатии P создаем новый объект
            new GameObject(0.0f, 0.0f, 15, 15, "PowerUp", "Bonus item", 1.0f, 0.0f, 1.0f);
            std::cout << "Created new PowerUp object!" << std::endl;
        }
        else if (wParam == 'D') {
            // При нажатии D удаляем первый врага
            deleteObjectByName("Enemy1");
            std::cout << "Deleted Enemy1 object!" << std::endl;
        }
        else if (wParam == 'S') {
            // При нажатии S показываем все объекты
            showAllObjects();
        }
        else if (wParam == 'M') {
            // При нажатии M двигаем игрока
            GameObject* player = findObjectByName("Player");
            if (player) {
                auto pos = player->getPosition();
                player->setPosition(pos.first + 0.1f, pos.second);
                std::cout << "Moved player to: (" << pos.first + 0.1f << ", " << pos.second << ")" << std::endl;
            }
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

    // Инициализируем игровые объекты
    initializeTestGameObjects();

    // Покажем начальное состояние объектов
    std::cout << "=== ChronoForge2D Started ===" << std::endl;
    std::cout << "Controls:" << std::endl;
    std::cout << "P - Create new PowerUp" << std::endl;
    std::cout << "D - Delete Enemy1" << std::endl;
    std::cout << "M - Move Player" << std::endl;
    std::cout << "S - Show all objects" << std::endl;
    std::cout << "ESC - Exit" << std::endl;
    showAllObjects();

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

    // Очищаем память перед выходом
    clearAllGameObjects();

    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(renderContext);
    ReleaseDC(window, deviceContext);
    DestroyWindow(window);

    std::cout << "=== ChronoForge2D Shutdown ===" << std::endl;
    return 0;
}