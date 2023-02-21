#include "PongGame.h"

PongGame::PongGame(int game_width, int game_height)
    : game_width(game_width), game_height(game_height), ball_radius(10.f), ball_speed(400.f), paddle_width(10.f), paddle_height(150.f),
      paddle_speed(250.f), ball_color(sf::Color(230, 60, 60)), paddle_color(sf::Color(30, 120, 150))
{
}

void PongGame::play()
{
    std::shared_ptr<Ball> ball = std::dynamic_pointer_cast<Ball>(ballFactory.createGameObject());
    std::shared_ptr<PlayerPaddle> playerPaddle = std::dynamic_pointer_cast<PlayerPaddle>(playerPaddleFactory.createGameObject());
    std::shared_ptr<AIPaddle> aiPaddle = std::dynamic_pointer_cast<AIPaddle>(aiPaddleFactory.createGameObject());

    ball->addObserver(std::dynamic_pointer_cast<PlayerPaddle>(playerPaddle));
    ball->addObserver(std::dynamic_pointer_cast<AIPaddle>(aiPaddle));

    initBall(ball);
    initPaddle(playerPaddle, 70.f);
    initPaddle(aiPaddle, game_width - 70.f - paddle_width);

    std::vector<std::shared_ptr<GameObject>> gameObjects;

    gameObjects.push_back(ball);
    gameObjects.push_back(playerPaddle);
    gameObjects.push_back(aiPaddle);

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(game_width, game_height), "Pong Game");

    sf::Clock clock;

    sf::Font font;
    font.loadFromFile("resources/sansation.ttf");

    sf::Text pauseMessage;
    pauseMessage.setFont(font);
    pauseMessage.setCharacterSize(40);
    pauseMessage.setPosition(170.f, 150.f);
    pauseMessage.setFillColor(sf::Color::Magenta);
    pauseMessage.setString("Press space to start the game");

    bool isPlaying = false;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Space))
            {
                if (!isPlaying)
                {
                    isPlaying = true;
                    for (auto& gameObject : gameObjects)
                    {
                        gameObject->resetObject();
                    }
                    clock.restart();
                }
            }
        }

        if (isPlaying)
        {
            window.clear(sf::Color(250, 220, 100, 0));
            float delta_time = clock.restart().asSeconds();

            for (auto& gameObject : gameObjects)
            {
                gameObject->move(delta_time, window);
                gameObject->draw(window);
            }

            if (ball->getX() <= 0)
            {
                pauseMessage.setFillColor(sf::Color::Red);
                pauseMessage.setString("You Lose");
                isPlaying = false;
            }
            if (ball->getX() + ball_radius * 2 >= game_width)
            {
                pauseMessage.setFillColor(sf::Color::Blue);
                pauseMessage.setString("You Win");
                isPlaying = false;
            }
        }
        else
        {
            window.clear(sf::Color(250, 220, 100, 0));
            window.draw(pauseMessage);
        }
        window.display();
    }
}

void PongGame::initBall(std::shared_ptr<Ball> ball)
{
    ball->setRadius(ball_radius);
    ball->setSpeed(ball_speed);
    ball->setStartPosition(game_width / 2 + ball_radius, game_height / 2 + ball_radius);
    ball->setColor(ball_color);
}

void PongGame::initPaddle(std::shared_ptr<Paddle> paddle, float paddle_x)
{
    paddle->setSizes(paddle_width, paddle_height);
    paddle->setSpeed(paddle_speed);
    paddle->setStartPosition(paddle_x, game_height / 2 - paddle_height / 2);
    paddle->setColor(paddle_color);
}