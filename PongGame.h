#pragma once
#include "Factory.h"

class PongGame
{
public:
    PongGame(int game_width, int game_height);

    void play();

    void initBall(std::shared_ptr<Ball> ball);

    void initPaddle(std::shared_ptr<Paddle> paddle, float paddle_x);

private:
    BallFactory ballFactory;
    PlayerPaddleFactory playerPaddleFactory;
    AIPaddleFactory aiPaddleFactory;
    int game_width, game_height;
    float ball_radius, paddle_width, paddle_height, paddle_speed, ball_speed;
    sf::Color paddle_color, ball_color;
};
