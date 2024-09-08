#ifndef PHYSICSOBJECT_H
#define PHYSICSOBJECT_H

#include "Vector2.h"

class Window;

// object types
enum ObjectType
{
    BOX
};

class PhysicsObject
{

public:
    PhysicsObject(Vector2 position, Vector2 velocity, float mass, bool isStatic, float angle = 0) : position(position), velocity(velocity), acceleration(0, 0), mass(mass), isStaticFlag(isStatic), angle(angle) {};
    virtual ~PhysicsObject() = default;

    virtual ObjectType getType() const = 0;

    float getMass() const { return mass; }

    Vector2 getPos() const { return position; }
    void setPos(Vector2 pos) { position = pos; }

    Vector2 getVel() { return velocity; }
    void setVel(Vector2 vel) { velocity = vel; }

    void translate(Vector2 translation) {
        position += translation;
    }

    float getAngle() const { return angle; }

    void applyForce(Vector2 force)
    {
        acceleration += force / mass;
    };

    bool isStatic() const { return isStaticFlag; }

    virtual void update(float dt)
    {
        if (!isStatic())
        {
            // Atualizar movimento linear
            velocity += acceleration * dt;
            position += velocity * dt;
            acceleration = Vector2(0, 0); // Resetar aceleração

            // Atualizar rotação (caso esteja usando torque/rotação)
            angularVelocity += angularAcceleration * dt;
            angle += angularVelocity * dt;
            angularAcceleration = 0; // Resetar aceleração angular
        }
    }

    void applyTorque(float torque)
    {
        // A fórmula simplificada para aceleração angular é torque / momento de inércia.
        // Aqui, "mass" é usada como proxy para o momento de inércia (para simplificação)
        angularAcceleration += torque / mass;
    }

    void updateRotation(float dt)
    {
        angularVelocity += angularAcceleration * dt;
        angle += angularVelocity * dt;
        angularAcceleration = 0; // Resetar para a próxima iteração
    }

    void setAngularVelocity(float velocity)
    {
        angularVelocity = velocity;
    }

    virtual void draw(Window *window) = 0;

protected:
    Vector2 position;
    Vector2 velocity;
    Vector2 acceleration;
    float angularVelocity = 0;
    float angularAcceleration = 0;
    float mass;
    float angle;
    bool isStaticFlag;
};

#endif