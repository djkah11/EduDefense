#include "gameobject.h"

#include "math.h"

GameObject::~GameObject() {}

double GameObject::getX() {
    return x;
}

void GameObject::setX(double x) {
    this->x = x;
}

double GameObject::getY() {
    return y;
}

void GameObject::setY(double y) {
    this->y = y;
}

double GameObject::getRadius() {
    return radius;
}

void GameObject::setRadius(double radius) {
    this->radius = radius;
}

bool GameObject::isCollided(GameObject *gameObject) {
    return distance(gameObject) < radius + gameObject->radius;
}

double GameObject::distance(GameObject *gameObject) {
    return sqrt((x - gameObject->x) * (x - gameObject->x) +
                (y - gameObject->y) * (y - gameObject->y));
}
