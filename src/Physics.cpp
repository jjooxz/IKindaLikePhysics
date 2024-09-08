#include "Physics.h"

void Physics::update(float deltaTime)
{
    for (auto &object : objects)
    {
        if (!object->isStatic())
        {
            // Aplica a gravidade
            object->setVel(object->getVel() + Vector2(0, gravity * deltaTime));

            // Atualiza a posição com base na velocidade
            Vector2 newPos = object->getPos() + object->getVel() * deltaTime;
            object->setPos(newPos);

            // Atualiza os vértices da caixa
            object->update(deltaTime);
            object->updateRotation(deltaTime);
        }
    }
}

void Physics::addObject(PhysicsObject *object)
{
    objects.push_back(object); // Supondo que 'objects' é um vetor que armazena os objetos físicos
}