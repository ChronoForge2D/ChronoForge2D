#include "GameObject.hpp"
#include <iostream>
#include <vector>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <gl/GL.h>

// ”Ѕ–ј“№ эту строку - неправильно
// GameObject::std::vector<GameObject> gameObjects;

// ƒќЅј¬»“№ глобальный массив
std::vector<GameObject*> gameObjects;

GameObject::GameObject(float posX, float posY, int widthX, int widthY, std::string name, std::string description, bool isActive)
    : position(posX, posY), widthX(widthX), widthY(widthY), name(name), description(description), isActive(isActive) {
    color[0] = 1.0f;
    color[1] = 1.0f;
    color[2] = 1.0f;

    // ј¬“ќћј“»„≈— » добавл€ем объект в массив при создании
    gameObjects.push_back(this);
}

GameObject::GameObject(float posX, float posY, int widthX, int widthY, std::string name, std::string description, float r, float g, float b, bool isActive)
    : position(posX, posY), widthX(widthX), widthY(widthY), name(name), description(description), isActive(isActive) {
    color[0] = r;
    color[1] = g;
    color[2] = b;

    // ј¬“ќћј“»„≈— » добавл€ем объект в массив при создании
    gameObjects.push_back(this);
}

void GameObject::draw() {

    if (!this->isActive) return;

    glPushMatrix();
    glTranslatef(position.first, position.second, 0.0f);

    // –исуем квадрат
    glBegin(GL_QUADS);
    glColor3f(color[0], color[1], color[2]);
    glVertex2f(-widthX / 200.0f, -widthY / 200.0f);
    glVertex2f(widthX / 200.0f, -widthY / 200.0f);
    glVertex2f(widthX / 200.0f, widthY / 200.0f);
    glVertex2f(-widthX / 200.0f, widthY / 200.0f);
    glEnd();

    glPopMatrix();
}

void GameObject::hide() {
    this->isActive = false;
    /*
        ¬ будущем дополнить, чтобы было полное удаление объекта, а не просто скрытие его из экрана
    */
}

void GameObject::setPosition(float posX, float posY) {
    this->position = { posX, posY };
}

std::pair<float, float> GameObject::getPosition() {
    return this->position;
}

std::string GameObject::getName() {
    return this->name;
}

std::string GameObject::getDescription() {
    return this->description;
}

void GameObject::setColor(float r, float g, float b) {
    color[0] = r;
    color[1] = g;
    color[2] = b;
}