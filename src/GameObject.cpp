#include "GameObject.hpp"
#include <iostream>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <gl/GL.h>

GameObject::GameObject(float posX, float posY, int widthX, int widthY, std::string name, std::string description)
    : position(posX, posY), widthX(widthX), widthY(widthY), name(name), description(description) {
    color[0] = 1.0f; // Красный по умолчанию
    color[1] = 1.0f; // Зеленый
    color[2] = 1.0f; // Синий
}

GameObject::GameObject(float posX, float posY, int widthX, int widthY, std::string name, std::string description, float r, float g, float b)
    : position(posX, posY), widthX(widthX), widthY(widthY), name(name), description(description) {
    color[0] = r;
    color[1] = g;
    color[2] = b;
}

void GameObject::draw() {
    glPushMatrix();
    glTranslatef(position.first, position.second, 0.0f);

    // Рисуем квадрат
    glBegin(GL_QUADS);
    glColor3f(color[0], color[1], color[2]);
    glVertex2f(-widthX / 200.0f, -widthY / 200.0f);
    glVertex2f(widthX / 200.0f, -widthY / 200.0f);
    glVertex2f(widthX / 200.0f, widthY / 200.0f);
    glVertex2f(-widthX / 200.0f, widthY / 200.0f);
    glEnd();

    glPopMatrix();
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