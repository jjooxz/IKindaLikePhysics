#ifndef PHYSICSOBJECT_H
#define PHYSICSOBJECT_H

#include "Vector2.h"

class PhysicsObject
{

public:
    PhysicsObject(Vector2 position, Vector2 velocity, float mass, bool isStatic) : position(position), velocity(velocity), acceleration(0, 0), mass(mass), Static(isStatic) {};
    virtual ~PhysicsObject();

    Vector2 getPos() { return position; }
    Vector2 getVel() { return velocity; }

    void applyForce(Vector2 force)
    {
        acceleration += force / mass;
    };

    bool isStatic() { return isStatic; }

    void update(float dt)
    {
        velocity += acceleration * dt;
        position += velocity * dt;
        acceleration = Vector2(0, 0);
    }

    virtual void draw() = 0;

protected:
    Vector2 position;
    Vector2 velocity;
    Vector2 acceleration;
    float mass;
    bool Static;
};

#endif