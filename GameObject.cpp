#include "GameObject.h"

void GameObject::setStartPosition(float x, float y)
{
    start_x = x;
    start_y = y;
}

Ball::Ball() : speed(400), ball(30) {}

void Ball::move(float delta_time, sf::RenderWindow& window)
{
    sf::Vector2u window_size = window.getSize();

    ball.move(delta_time * speed * std::sin(angle), delta_time * speed * std::cos(angle));

    if (ball.getPosition().y <= 0)
    {
        changeAngleY();
        ball.setPosition(ball.getPosition().x, 0.1f);
    }

    if (ball.getPosition().y + 2 * ball.getRadius() >= window_size.y)
    {
        changeAngleY();
        ball.setPosition(ball.getPosition().x, window_size.y - 2 * ball.getRadius() - 0.1f);
    }

    notify(this);
}

void Ball::changeAngleY()
{
    angle = static_cast<float>(M_PI) - angle;
}

void Ball::changeAngleX(float luft)
{
    angle = -(angle + luft);
}

float Ball::getX() const
{
    return ball.getPosition().x;
}

float Ball::getY() const
{
    return ball.getPosition().y;
}

float Ball::getRadius() const
{
    return ball.getRadius();
}

void Ball::setPosition(float x, float y)
{
    ball.setPosition(x, y);
}

void Ball::resetObject()
{
    ball.setPosition(start_x, start_y);
    int sign = std::rand() % 2 == 0 ? -1 : -1;
    setAngle(sign * (rand() % 120 + 30.f) * 2.f * static_cast<float>(M_PI) / 360.f);
}

void Ball::setSpeed(float speed)
{
    this->speed = speed;
}

void Ball::setRadius(float radius)
{
    ball.setRadius(radius);
}

void Ball::setAngle(float angle)
{
    this->angle = angle;
}

void Ball::setColor(sf::Color col)
{
    ball.setFillColor(col);
}

void Ball::draw(sf::RenderWindow& window)
{
    window.draw(ball);
}

Paddle::Paddle() : speed(400), paddle(sf::Vector2f(50.f, 200.f)) {}

void Paddle::update(Subject* subject)
{
    Ball* ball = dynamic_cast<Ball*>(subject);
    int sign;
    float closest_x;
    if (ball->getX() < paddle.getPosition().x)
    {
        sign = -1;
        closest_x = ball->getX() + 2 * ball->getRadius();
    }
    else
    {
        sign = 1;
        closest_x = ball->getX();
    }

    if (closest_x <= paddle.getPosition().x + paddle.getSize().x && closest_x >= paddle.getPosition().x &&
        ball->getY() - ball->getRadius() < paddle.getPosition().y + paddle.getSize().y &&
        ball->getY() + ball->getRadius() > paddle.getPosition().y)
    {
        if (sign == 1)
        {
            ball->setPosition(paddle.getPosition().x + paddle.getSize().x + 0.1f, ball->getY());
        }
        else
        {
            ball->setPosition(paddle.getPosition().x - 2 * ball->getRadius() - 0.1f, ball->getY());
        }

        if (ball->getY() - ball->getRadius() > paddle.getPosition().y + paddle.getSize().y / 2)
        {
            ball->changeAngleX(sign * (rand() % 13) * static_cast<float>(M_PI) / 180);
        }
        else
        {
            ball->changeAngleX(-1 * sign * (rand() % 13) * static_cast<float>(M_PI) / 180);
        }
    }
}

void Paddle::setPosition(float x, float y)
{
    paddle.setPosition(x, y);
}

void Paddle::resetObject()
{
    paddle.setPosition(start_x, start_y);
}

void Paddle::setSizes(float x, float y)
{
    paddle.setSize({x, y});
}

void Paddle::setSpeed(float speed)
{
    this->speed = speed;
}

void Paddle::setColor(sf::Color col)
{
    paddle.setFillColor(col);
}

void Paddle::draw(sf::RenderWindow& window)
{
    window.draw(paddle);
}

PlayerPaddle::PlayerPaddle() : Paddle() {}

void PlayerPaddle::move(float delta_time, sf::RenderWindow& window)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && paddle.getPosition().y > 0)
    {
        paddle.move(0, delta_time * speed * -1);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && paddle.getPosition().y + paddle.getSize().y < window.getSize().y)
    {
        paddle.move(0, delta_time * speed);
    }
}

AIPaddle::AIPaddle() : Paddle() {}

void AIPaddle::move(float delta_time, sf::RenderWindow& window)
{
    if (ball_y < paddle.getPosition().y && paddle.getPosition().y > 0)
    {
        paddle.move(0, delta_time * speed * -1);
    }

    if (ball_y > paddle.getPosition().y + paddle.getSize().y && paddle.getPosition().y + paddle.getSize().y < window.getSize().y)
    {
        paddle.move(0, delta_time * speed);
    }
}

void AIPaddle::update(Subject* subject)
{
    ball_y = dynamic_cast<Ball*>(subject)->getY() - dynamic_cast<Ball*>(subject)->getRadius();
    Paddle::update(subject);
}