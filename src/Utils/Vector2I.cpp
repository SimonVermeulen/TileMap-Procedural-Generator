#include "Vector2I.hpp"

Vector2I::Vector2I() {
    this->_x = 0;
    this->_y = 0;
}

Vector2I::Vector2I(int x, int y) {
    this->_x = x;
    this->_y = y;
}

Vector2I Vector2I::operator+(Vector2I &vector) {
    return Vector2I(this->getX() + vector.getX(), this->getY() + vector.getY());
}

Vector2I Vector2I::operator-(Vector2I &vector) {
    return Vector2I(this->getX() - vector.getX(), this->getY() - vector.getY());
}

int Vector2I::getX() {
    return this->_x;
}

int Vector2I::getY() {
    return this->_y;
}