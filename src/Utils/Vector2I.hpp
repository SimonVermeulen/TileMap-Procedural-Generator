#pragma once

class Vector2I {
    private:
        int _x;
        int _y;
    public:
        Vector2I();
        Vector2I(int x, int y);
        Vector2I operator+(Vector2I &vector);
        Vector2I operator-(Vector2I &vector);
        int getX();
        int getY();
};