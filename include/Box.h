#ifndef BOX_H
#define BOX_H

#include "PhysicsObject.h"
#include <iostream>
#include "Logger.h"

class Box : public PhysicsObject
{
public:
    Box(Vector2 position, Vector2 velocity, float mass, float width, float height, bool isStatic = false) : PhysicsObject(position, velocity, mass, isStatic)
    {
    }
    ~Box() {};

    void draw() const override
    {
        SPDLOG_INFO(FMT_STRING("Box -> x: {}, y: {}"), position.x, position.y);
    }

private:
    float _width;
    float _height;
};

#endif