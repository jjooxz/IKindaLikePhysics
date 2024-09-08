#include "CollisionResolution.h"

Vector2 CalculateCollisionImpulse(Vector2 relativeVelocity, float mass1, float mass2, float restitution, Vector2 smallestAxis)
{
    float relativeVelocityAlongNormal = relativeVelocity.dotProduct(smallestAxis);
    float impulseMagnitude = (-(1 + restitution) * relativeVelocityAlongNormal) / (1 / mass1 + 1 / mass2);
    return smallestAxis * impulseMagnitude;
}

void ProjectVertices(Vector2 *vertices, Vector2 axis, float &min, float &max)
{
    float projection = vertices[0].dotProduct(axis);
    min = max = projection;

    for (int i = 1; i < 4; i++)
    {
        projection = vertices[i].dotProduct(axis);
        if (projection < min)
            min = projection;
        if (projection > max)
            max = projection;
    }
}

// Função para encontrar o eixo separador usando a normal de um vetor de aresta
Vector2 FindEdgeNormal(const Vector2 &p1, const Vector2 &p2)
{
    Vector2 edge = p2 - p1;
    return Vector2(-edge.y, edge.x).getNormal();
}

// Função para verificar a sobreposição em um eixo
bool OverlapOnAxis(Vector2 *vertices1, Vector2 *vertices2, Vector2 axis, float &overlap)
{
    float min1, max1, min2, max2;

    ProjectVertices(vertices1, axis, min1, max1);
    ProjectVertices(vertices2, axis, min2, max2);

    // Checa se há sobreposição
    if (max1 < min2 || max2 < min1)
        return false; // Não há sobreposição

    // Encontra a sobreposição mínima
    float overlap1 = max1 - min2;
    float overlap2 = max2 - min1;
    overlap = std::min(overlap1, overlap2);

    return true;
}

void CollisionResolution::ResolveCollisionBoxBox(Box *box1, Box *box2)
{
    SPDLOG_INFO("Correção De Colisão");

    // Obtém os vértices dos boxes
    Vector2 vertices1[4];
    Vector2 vertices2[4];
    std::copy(box1->getVertices(), box1->getVertices() + 4, vertices1);
    std::copy(box2->getVertices(), box2->getVertices() + 4, vertices2);

    Vector2 axes[8];
    float minOverlap = std::numeric_limits<float>::max();
    Vector2 smallestAxis;

    // Obtém os eixos separadores dos dois boxes
    for (int i = 0; i < 4; ++i)
    {
        Vector2 edge1 = vertices1[(i + 1) % 4] - vertices1[i];
        Vector2 edge2 = vertices2[(i + 1) % 4] - vertices2[i];
        axes[i * 2] = FindEdgeNormal(vertices1[i], vertices1[(i + 1) % 4]);
        axes[i * 2 + 1] = FindEdgeNormal(vertices2[i], vertices2[(i + 1) % 4]);
    }

    // Verifica a sobreposição em cada eixo separador
    for (const Vector2 &axis : axes)
    {
        float overlap;
        if (!OverlapOnAxis(vertices1, vertices2, axis, overlap))
        {
            SPDLOG_INFO("Sem colisão detectada.");
            return; // Não há colisão se não houver sobreposição em algum eixo
        }

        if (overlap < minOverlap)
        {
            minOverlap = overlap;
            smallestAxis = axis;
        }
    }

    // Calcula a correção de posição
    Vector2 correction;
    if (!box1->isStatic() && box2->isStatic())
    {
        correction = smallestAxis * minOverlap;
        box1->setPos(box1->getPos() - correction);
        box1->setVel(Vector2(0, 0)); // Reseta a velocidade de box1, pois box2 é estático
    }
    else if (box1->isStatic() && !box2->isStatic())
    {
        correction = smallestAxis * minOverlap;
        box2->setPos(box2->getPos() + correction);
        box2->setVel(Vector2(0, 0)); // Reseta a velocidade de box2, pois box1 é estático
    }
    else if (!box1->isStatic() && !box2->isStatic())
    {
        correction = smallestAxis * (minOverlap * 0.5f);
        box1->setPos(box1->getPos() - correction);
        box2->setPos(box2->getPos() + correction);

        // Ajusta as velocidades para refletir a correção de posição
        Vector2 relativeVelocity = box1->getVel() - box2->getVel();
        Vector2 impulse = CalculateCollisionImpulse(relativeVelocity, box1->getMass(), box2->getMass(), 0.5f, smallestAxis); // Rebate simples
        box1->setVel(box1->getVel() - impulse / box1->getMass());
        box2->setVel(box2->getVel() + impulse / box2->getMass());
    }

    // Atualiza a rotação dos objetos
    if (!box1->isStatic() && !box2->isStatic())
    {
        // Calcula o impulso normal
        Vector2 normalImpulse = CalculateCollisionImpulse(Vector2(0, 0), box1->getMass(), box2->getMass(), 0.5f, smallestAxis);
        float normalImpulseMagnitude = normalImpulse.magnitude();
        float momentOfInertia1 = box1->getMass() * 0.5f; // Aproximação para o momento de inércia
        float momentOfInertia2 = box2->getMass() * 0.5f;

        box1->applyTorque(normalImpulseMagnitude / momentOfInertia1);
        box2->applyTorque(-normalImpulseMagnitude / momentOfInertia2);
    }

    SPDLOG_INFO("Colisão resolvida com correção de sobreposição: {}", minOverlap);
}