#pragma once

#define _USE_MATH_DEFINES

#include "Observer.h"

#include <SFML/Graphics.hpp>
#include <cmath>

class GameObject
{
public:
    virtual ~GameObject() {}

    virtual void move(float delta_time, sf::RenderWindow& window) = 0;

    virtual void resetObject() = 0;

    virtual void setStartPosition(float x, float y);

    virtual void draw(sf::RenderWindow& window) = 0;

protected:
    float start_x, start_y;
};

class Ball : public GameObject, public Subject
{
public:
    Ball();
    virtual void move(float delta_time, sf::RenderWindow& window) override;

    void changeAngleY();

    void changeAngleX(float luft);

    float getX() const;

    float getY() const;

    float getRadius() const;

    void setPosition(float x, float y);

    void setRadius(float radius);

    void setAngle(float angle);

    void setSpeed(float speed);

    virtual void resetObject() override;

    void setColor(sf::Color col);

    virtual void draw(sf::RenderWindow& window) override;

private:
    sf::CircleShape ball;
    float speed, angle;
};

class Paddle : public GameObject, public Observer
{
public:
    Paddle();

    virtual void update(Subject* subject) override;

    void setPosition(float x, float y);

    void setSizes(float x, float y);

    void setSpeed(float speed);

    virtual void resetObject() override;

    void setColor(sf::Color col);

    virtual void draw(sf::RenderWindow& window) override;

protected:
    float speed;
    sf::RectangleShape paddle;
};

class PlayerPaddle : public Paddle
{
public:
    PlayerPaddle();

    virtual void move(float delta_time, sf::RenderWindow& window) override;
};

class AIPaddle : public Paddle
{
public:
    AIPaddle();

    virtual void move(float delta_time, sf::RenderWindow& window) override;

    virtual void update(Subject* subject) override;

private:
    float ball_y;
};
