#ifndef BOX_H
#define BOX_H

#include "PhysicsObject.h"
#include <iostream>
#include "Logger.h"
#include "Window.h"
#include "SDL2/SDL2_gfxPrimitives.h"

class Box : public PhysicsObject
{
public:
    /*
        @param position - The position of the box
        @param velocity - The velocity of the box
        @param mass - The mass of the box
        @param _width - The _width of the box
        @param _height - The _height of the box
        @param isStatic - Whether the box is static
        @param color - The color of the box
    */
    Box(Vector2 position, Vector2 velocity, float mass, float width, float height, float angle = 0, bool isStatic = false, SDL_Color color = {255, 255, 255, 255})
        : PhysicsObject(position, velocity, mass, isStatic, angle), _width(width), _height(height), color(color)
    {
        calculateVertices();
    }
    ~Box() {};

    float getWidth() const { return _width; }
    float getHeight() const { return _height; }

    ObjectType getType() const override { return ObjectType::BOX; }

    void Box::draw(Window *window)
    {
        SPDLOG_INFO("Box: x: {}, y: {}", position.x, position.y);
        SDL_Rect camera = *window->camera;

        Sint16* x = new Sint16[4];
        Sint16* y = new Sint16[4];
        for (int i = 0; i < 4; i++)
        {
            x[i] = vertices[i].x - camera.x;
            y[i] = -vertices[i].y + camera.y;
        }

        filledPolygonRGBA(window->getRenderer(), x, y, 4, color.r, color.g, color.b, color.a);
        SDL_SetRenderDrawColor(window->getRenderer(), 0, 0, 0, 255);
    }

    void update(float dt) override {
        PhysicsObject::update(dt);
        calculateVertices();
    }

    Vector2 *getVertices()
    {
        calculateVertices();
        return vertices;
    }

private:
    float _width;
    float _height;
    SDL_Color color;
    Vector2 vertices[4];

    void calculateVertices()
    {
        // Calcular vértices sem rotação e depois rotacioná-los (como no exemplo anterior)
        // Atualiza a array vertices[] com os valores rotacionados
        vertices[0] = Vector2(position.x, position.y);                    // Canto superior esquerdo
        vertices[1] = Vector2(position.x + _width, position.y);           // Canto superior direito
        vertices[2] = Vector2(position.x + _width, position.y + _height); // Canto inferior direito
        vertices[3] = Vector2(position.x, position.y + _height);          // Canto inferior esquerdo

        Vector2 center = position + Vector2(_width / 2, _height / 2);
        for (int i = 0; i < 4; ++i)
        {
            vertices[i] = rotatePoint(vertices[i], center, angle);
        }
    }

    Vector2 rotatePoint(const Vector2 &point, const Vector2 &center, float angle)
    {
        float s = std::sin(angle);
        float c = std::cos(angle);
        Vector2 translated = point - center;
        float xNew = translated.x * c - translated.y * s;
        float yNew = translated.x * s + translated.y * c;
        return Vector2(xNew, yNew) + center;
    }
};

#endif
