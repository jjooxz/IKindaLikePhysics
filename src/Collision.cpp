#include "Collision.h"
#include <algorithm>

void Collision::checkCollision(PhysicsObject *object1, PhysicsObject *object2)
{
    ObjectType obj1Type = object1->getType();
    ObjectType obj2Type = object2->getType();

    if (obj1Type == ObjectType::BOX && obj2Type == ObjectType::BOX)
    {
        if (checkBoxBoxCollision(static_cast<Box *>(object1), static_cast<Box *>(object2)))
        {
            CollisionResolution::ResolveCollisionBoxBox(static_cast<Box *>(object1), static_cast<Box *>(object2));
        }
    }
    // Adicionar verificações para outros tipos de objetos se necessário
}

bool Collision::checkBoxBoxCollision(Box *box1, Box *box2)
{
    Vector2 vertices1[4];
    Vector2 vertices2[4];

    std::copy(box1->getVertices(), box1->getVertices() + 4, vertices1);
    std::copy(box2->getVertices(), box2->getVertices() + 4, vertices2);

    // Verificar se há colisão entre as linhas dos dois retângulos
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            if (checkLineCollision(vertices1[i], vertices1[(i + 1) % 4], vertices2[j], vertices2[(j + 1) % 4]))
            {
                return true;
            }
        }
    }

    return false;
}

bool Collision::checkLineCollision(Vector2 p1, Vector2 p2, Vector2 p3, Vector2 p4)
{
    float d1 = (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
    float d2 = (p2.x - p1.x) * (p4.y - p1.y) - (p2.y - p1.y) * (p4.x - p1.x);
    float d3 = (p4.x - p3.x) * (p1.y - p3.y) - (p4.y - p3.y) * (p1.x - p3.x);
    float d4 = (p4.x - p3.x) * (p2.y - p3.y) - (p4.y - p3.y) * (p2.x - p3.x);

    return (d1 * d2 < 0 && d3 * d4 < 0);
}
