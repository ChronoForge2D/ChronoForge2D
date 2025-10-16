#pragma once
#include <string>
#include <utility>
#include <vector>

class GameObject {
private:
    std::pair<float, float> position;
    int widthX, widthY;
    std::string name, description;
    float color[3];
    bool isActive = true;

public:
    // ”Ѕ–ј“№ отсюда vector - он должен быть отдельно
    GameObject(float posX, float posY, int widthX, int widthY, std::string name, std::string description, bool isActive = true);
    GameObject(float posX, float posY, int widthX, int widthY, std::string name, std::string description, float r, float g, float b, bool isActive = true);
    void draw();
    void hide();
    void setPosition(float posX, float posY);
    std::pair<float, float> getPosition();
    std::string getName();
    std::string getDescription();
    void setColor(float r, float g, float b);
};

// ƒќЅј¬»“№ глобальный массив дл€ управлени€ объектами
extern std::vector<GameObject*> gameObjects; // указатели дл€ управлени€